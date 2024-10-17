// Функции для генерирования программной задержки с использованием DWT
// Не забывайте, что разные прерывания могу мешать точному отсчёту времени
 __INLINE uint32_t DWT_delta(uint32_t t0, uint32_t t1) { return (t1 - t0); }

// Функция задержки в мкс (можно от 1 мкс). Получите: задержка + 1 мкс.
 __INLINE void delay_us(uint32_t us) {
static volatile uint32_t n;
n =  us * (SystemCoreClock / 1000000); // SystemCoreClock/1000000 = 72
DWT_CYCCNT = 0; while (DWT_CYCCNT < n) ;
}

// Функция задержки в мс от 1 мс до 59 сек. (дальше переполнение)
 __INLINE void delay_ms(uint32_t ms) {
static volatile uint32_t n;
n =  ms * (SystemCoreClock / 1000); DWT_CYCCNT = 0; while (DWT_CYCCNT < n) ;
}
// Функция программной задержки
void Pause() {
static volatile uint32_t i;
for(i = 0; i < 10000; i++) {};
}

/// @brief Analog of atoi i can't import because of memory lack
/// @param s symbol
/// @return symbol-48 (digit)
int my_atoi(char s){
    return s-48;
}

/// @brief Returns position of substring in string
/// @param str string in which searching
/// @param substr  string which want to find in str
/// @return position of substr in str, if not found returns -1
int16_t str_get_pos(char* str, char* substr){
    char *substring_ptr = strstr(str, substr);
    if(substring_ptr) return substring_ptr - str;
    else return -1;
}

/// @brief Reads string from start and converts symbols to digit, stops when found non-digit
/// @param str string which contains digit
/// @return converted integer or 0 if no digits found
int16_t get_int_from_str(char* str){
    int16_t length = 0, multiplier = 1, result = 0;
    while(1){
        if((str[length] < '0' || str[length] > '9') && str[length] != '-') break;
        length++;
    }
    if (length == 0) return length;

    --length;
    for(; length >= 0; length--){
        if(length == 0 && str[length] == '-'){
            result *= (-1);
        } else {
            result += my_atoi(str[length]) * multiplier;
            multiplier *= 10;
        }
	}
    return result;
}

void collect_system_info(char *body){
    xsprintf(body, "{\"device_index\":%d,\"version\":%d,",device_index, MODULES_VERSION);

    uint8_t modules = 0;
    #ifdef RelayConnection
    relay_add_info_to_str(body);
    strcat(body,",");
    modules++;
	#endif

	#ifdef InputConnection
	input_add_info_to_str(body);
    strcat(body,",");
    modules++;
	#endif

    #ifdef DS18B20Connection
	ds18b20_add_info_to_str(body);
    strcat(body,",");
    modules++;
	#endif

    virtual_add_info_to_str(body);
    modules++;


	strcat(body,"}");
}

void collect_state(char *body){
    strcat(body, "{");

    uint8_t modules = 0;
    #ifdef RelayConnection
	relay_add_data_to_str(body);
    strcat(body,",");
    modules++;
	#endif

	#ifdef InputConnection
	input_add_data_to_str(body);
    strcat(body,",");
    modules++;
	#endif

    #ifdef DS18B20Connection
	ds18b20_add_data_to_str(body);
    strcat(body,",");
    modules++;
	#endif

    virtual_add_data_to_str(body);
    modules++;


	strcat(body,"}");
}

// КОНЕЦ

