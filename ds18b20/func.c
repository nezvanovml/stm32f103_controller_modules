#if DS18B20Connection == 1 // relay, sensors
#define DS18B20_dataPort GPIOA
#define DS18B20_dataPin GPIO_Pin_10
#elif DS18B20Connection == 2 // ventilation
#define DS18B20_dataPort GPIOA
#define DS18B20_dataPin GPIO_Pin_9
#endif

#ifndef DS18B20_MAX_DEVICES
#define DS18B20_MAX_DEVICES 10
#endif

#ifndef DS18B20_NEED_SCAN
#define DS18B20_NEED_SCAN 1
#endif

uint8_t ds18b20_ids[DS18B20_MAX_DEVICES][8];
uint8_t ds18b20_search_finished = 0;
uint8_t ds18b20_total_sensors = 0;

uint8_t LastDeviceFlag;
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;

// default period between measures (seconds)
#ifndef DS18B20Period
#define DS18B20Period 30
#endif

uint16_t ds18b20_timer = 0;

/// @brief Interruptions, called every millisecond
void ds18b20_int()
{
    ds18b20_timer++;
    if (ds18b20_timer >= DS18B20Period * 1000)
    {
        // run converting temperature on sensors
        ds18b20_StartMeasure();
        ds18b20_timer = 0;
    }
}

static uint8_t Scratchpad[8]; // буфер с результатами
// Scratchpad[0] - младший байт температуры, [1] - старший.

static __INLINE void D0() { GPIO_ResetBits(DS18B20_dataPort, DS18B20_dataPin); }
static __INLINE void D1() { GPIO_SetBits(DS18B20_dataPort, DS18B20_dataPin); }

/// @brief Send reset command to 1Wire
/// @param
/// @return 1 if have any sensors on wire
uint8_t ds18b20_Reset(void)
{
    static uint16_t status;
    D0();
    delay_us(500); // min 480 us
    D1();
    delay_us(70);
    status = GPIO_ReadInputDataBit(DS18B20_dataPort, DS18B20_dataPin);
    D1();
    delay_us(430);
    return status;
}

/// @brief Read bit from 1Wire
/// @param
/// @return byte, which can be 1/0
uint8_t ds18b20_ReadBit(void)
{
    static uint8_t bit;
    D0();
    delay_us(3);
    D1();
    delay_us(7);
    bit = GPIO_ReadInputDataBit(DS18B20_dataPort, DS18B20_dataPin);
    delay_us(55);
    return bit;
}

/// @brief Read byte from 1Wire
/// @param
/// @return byte
uint8_t ds18b20_ReadByte(void)
{
    static uint8_t data;
    data = 0;
    for (uint8_t i = 0; i <= 7; i++)
        data += ds18b20_ReadBit() << i;
    return data;
}

/// @brief Write bit to 1Wire
/// @param bit bit
void ds18b20_WriteBit(uint8_t bit)
{
    D0();
    delay_us(bit ? 3 : 70);
    D1();
    delay_us(bit ? 70 : 3);
}

/// @brief Write byte to 1Wire
/// @param dt byte
void ds18b20_WriteByte(uint8_t dt)
{
    for (uint8_t i = 0; i < 8; i++)
        ds18b20_WriteBit(dt >> i & 1);
}

/// @brief Send to 1Wire command to convert temperature
void ds18b20_StartMeasure()
{
    __disable_irq();
    ds18b20_Reset();
    ds18b20_WriteByte(0xCC); // SKIP_ROM
    ds18b20_WriteByte(0x44); // CONVERT T
    __enable_irq();
}

/// @brief Read bytes from 1Wire
/// @param n number of bytes to read
void ds18b20_ReadStratcpad(uint8_t n)
{
    static uint8_t i;
    __disable_irq();
    ds18b20_Reset();
    ds18b20_WriteByte(0xCC);
    ds18b20_WriteByte(0xBE); // READ SCRATCHPAD
    for (i = 0; i < n; i++)
        Scratchpad[i] = ds18b20_ReadByte();
    __enable_irq();
}

/// @brief Read bytes from 1Wire sensor with address
/// @param n number of bytes to read
/// @param addr address of 1Wire sensor
void ds18b20_ReadStratcpadAddr(uint8_t n, uint8_t addr[])
{
    static uint8_t i;
    __disable_irq();
    ds18b20_Reset();
    ds18b20_WriteByte(0x55);
    for (uint8_t a = 0; a < 8; a++)
        ds18b20_WriteByte(addr[a]);
    ds18b20_WriteByte(0xBE); // READ SCRATCHPAD
    for (i = 0; i < n; i++)
        Scratchpad[i] = ds18b20_ReadByte();
    __enable_irq();
}

/// @brief Returns temperature got from bytes from DS18B20
/// @param a 1st byte
/// @param b 2nd byte
/// @return temperature
float bytes_to_temp(uint8_t a, uint8_t b)
{
    float temp = 0;
    if (((1 << 4) & a))
    {
        temp = ((~((a << 4) | ((b >> 4) & 0xF)) & 0x7F) + 1) * (-1);
    }
    else
    {
        temp = ((a << 4) | ((b >> 4) & 0xF));
    }
    if (((1 << 0) & (b & 0x0F)))
        temp += 0.0625;
    if (((1 << 1) & (b & 0x0F)))
        temp += 0.125;
    if (((1 << 2) & (b & 0x0F)))
        temp += 0.250;
    if (((1 << 3) & (b & 0x0F)))
        temp += 0.500;
    return temp;
}

/// @brief Returns integer part of temperature
/// @param input temperature
/// @return integer part
int8_t get_integer(float input)
{
    if (input < 0)
        return (uint8_t)(input * -1);
    return (uint8_t)input;
}

/// @brief Returns fraction part of temperature
/// @param input temperature
/// @return fraction part
int8_t get_fraction(float input)
{
    if (input < 0)
        input *= -1;
    return (int8_t)((input - (int8_t)(input)) * 10);
}

/// @brief Convert temperature from float to str
/// @param input temperature
/// @param temp address of string where to save result
void temperature_to_str(float input, char *temp)
{
    // TODO: returns -0.0 if unavailable, target = null
    uint8_t integer_part = get_integer(input), fraction_part = get_fraction(input);
    if ((input < 0 && integer_part == 0 && fraction_part == 0) || (integer_part == 85 && fraction_part == 0))
    { // 1st variant - sensor not connected, 2nd cariant -  sensor just turned on, no temperature meaured
        xsprintf(temp, "null");
    }
    else if (input < 0)
    {
        xsprintf(temp, "-%d.%d", integer_part, fraction_part);
    }
    else
    {
        xsprintf(temp, "%d.%d", integer_part, fraction_part);
    }
}

/// @brief Function to run over 1Wire bus. (got from https://narodstream.ru/stm-urok-94-ds18b20-podklyuchaem-neskolko-datchikov-na-provod-chast-1/)
/// @param Addr 8 bytes (uint8_t)
/// @return 1 if address found, 0 if not found
uint8_t ds18b20_search_rom(uint8_t *Addr)
{

    uint8_t id_bit_number;
    uint8_t last_zero, rom_byte_number, search_result;
    uint8_t id_bit, cmp_id_bit;
    uint8_t rom_byte_mask, search_direction;
    uint8_t ROM_NO[8];
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;
    if (!LastDeviceFlag)
    {
        ds18b20_Reset();
        ds18b20_WriteByte(0xF0);
    }
    do
    {
        id_bit = ds18b20_ReadBit();
        cmp_id_bit = ds18b20_ReadBit();
        if ((id_bit == 1) && (cmp_id_bit == 1))
            break;
        else
        {
            if (id_bit != cmp_id_bit)
                search_direction = id_bit; // bit write value for search
            else
            {
                if (id_bit_number < LastDiscrepancy)
                    search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
                else
                    search_direction = (id_bit_number == LastDiscrepancy);
                if (search_direction == 0)
                {
                    last_zero = id_bit_number;
                    if (last_zero < 9)
                        LastFamilyDiscrepancy = last_zero;
                }
            }
            if (search_direction == 1)
                ROM_NO[rom_byte_number] |= rom_byte_mask;
            else
                ROM_NO[rom_byte_number] &= ~rom_byte_mask;
            ds18b20_WriteBit(search_direction);
            id_bit_number++;
            rom_byte_mask <<= 1;
            if (rom_byte_mask == 0)
            {
                rom_byte_number++;
                rom_byte_mask = 1;
            }
        }
    } while (rom_byte_number < 8); // ��������� ����� � 0 �� 7 � �����
    if (!(id_bit_number < 65))
    {
        LastDiscrepancy = last_zero;
        if (LastDiscrepancy == 0)
            LastDeviceFlag = 1;
        search_result = 1;
    }
    if (!search_result || !ROM_NO[0])
    {
        LastDiscrepancy = 0;
        LastDeviceFlag = 0;
        LastFamilyDiscrepancy = 0;
        search_result = 0;
    }
    else
    {
        for (int i = 0; i < 8; i++)
            Addr[i] = ROM_NO[i];
    }
    return search_result;
}

/// @brief Initialization of module ds18b20. Insert before main loop.
void ds18b20_ini()
{
    if (DS18B20_NEED_SCAN)
    {
        if (!ds18b20_search_finished)
        {
            uint8_t dt[8];

            for (uint8_t i = 1; i <= DS18B20_MAX_DEVICES; i++)
            {
                if (ds18b20_search_rom(dt))
                {
                    ds18b20_total_sensors++;
                    memcpy(ds18b20_ids[ds18b20_total_sensors - 1], dt, sizeof(dt));
                }
                else
                    break;
            }
            ds18b20_search_finished = 1;
        }
    }
}

/// @brief Get temperature on sensor by index. Example: ds18b20_get_temperature_by_index(1)
/// @param id - index (uint8_t)
/// @return float, if error ocured returns -100.0
float ds18b20_get_temperature_by_index(uint8_t id)
{
    float temp = -100.0;
    if (id > ds18b20_total_sensors)
        return temp;
    ds18b20_ReadStratcpadAddr(2, ds18b20_ids[id - 1]); //
    return bytes_to_temp(Scratchpad[1], Scratchpad[0]);
}

/// @brief Get temperature on sensor by address. Example: ds18b20_get_temperature_by_address((uint8_t[]){0x28,0x48,0xE8,0x43,0xD4,0xE1,0x3C,0x6D})
/// @param id - address (HEX), 8 bytes (uint8_t)
/// @return float, if error ocured returns -100.0
float ds18b20_get_temperature_by_address(uint8_t id[8])
{
    float temp = -100.0;
    ds18b20_ReadStratcpadAddr(2, id);
    return bytes_to_temp(Scratchpad[1], Scratchpad[0]);
}

/// @brief Appends temperature sensors data
/// @param body string where to append temperature sensors data
void ds18b20_add_data_to_str(char *body)
{
    strcat(body, "\"temperature\":{");
    for (uint8_t i = 0; i < ds18b20_total_sensors; i++)
    {
        char tmp[7];
        temperature_to_str(ds18b20_get_temperature_by_index(i + 1), tmp);
        char temp[25];
        xsprintf(temp, "\"%02X%02X%02X%02X%02X%02X%02X%02X\":%s,",
                 ds18b20_ids[i][0], ds18b20_ids[i][1], ds18b20_ids[i][2], ds18b20_ids[i][3], ds18b20_ids[i][4], ds18b20_ids[i][5], ds18b20_ids[i][6], ds18b20_ids[i][7], tmp);
        strcat(body, temp);
        if ((i + 1) == ds18b20_total_sensors)
            body[strlen(body) - 1] = '\0';
    }
    strcat(body, "}");
}

/// @brief Appends info about temperature sensors
/// @param body string where to append input data
void ds18b20_add_info_to_str(char *body)
{
    char tmp[3];
    xsprintf(tmp, "%d", ds18b20_total_sensors);
    strcat(body, "\"temperature\":{\"total\":");
    strcat(body, tmp);
    strcat(body, ",\"addr\":[");

    for (uint8_t i = 0; i < ds18b20_total_sensors; i++)
    {
        char temp[20];
        xsprintf(temp, "\"%02X%02X%02X%02X%02X%02X%02X%02X\",",
                 ds18b20_ids[i][0], ds18b20_ids[i][1], ds18b20_ids[i][2], ds18b20_ids[i][3], ds18b20_ids[i][4], ds18b20_ids[i][5], ds18b20_ids[i][6], ds18b20_ids[i][7]);
        strcat(body, temp);
        if ((i + 1) == ds18b20_total_sensors)
            body[strlen(body) - 1] = '\0';
    }

    strcat(body, "]}");
}

/// @brief Adds address of sensor to use. Example: ds18b20_manual_add_id((uint8_t[]){0x28,0x00,0x4A,0x2E,0x3B,0x47,0x05,0xFA});
/// @param id
void ds18b20_manual_add_id(uint8_t id[8])
{
    if (ds18b20_total_sensors < DS18B20_MAX_DEVICES)
    {
        for (uint8_t i = 0; i < 8; i++)
            ds18b20_ids[ds18b20_total_sensors][i] = id[i];
        ds18b20_total_sensors++;
    }
}