#define MODULES_VERSION 10

/*

Version 1: First version 
Version 2: Fixed bug when device_index does not complete.
Version 3: Multi-socket server
Version 4: Critical fix for connection pins
Version 5: Added short/long differentiation for input button
Version 6: Added caching for temperature data. Now it read data from sensors one time after converting and store in array.
Version 7: Added posibility to expose relay as light
Version 8: Added value diapason for virtual_numeric
Version 9: Added auto re-init w5500 module if no any connections more then 15 seconds
Version 10: Added auto reboot MCU if no any connections more then 30*5 (150) seconds

*/

// Counting working time
uint32_t seconds_since_start = 0; // Counts how many seconds controller is online
uint16_t interruption_counter = 0;
// End counting working time

#include "utils.c"
#include "Libraries/xprintf/xprintf.c"

#ifdef IOModuleConnection
#include "modules/io_module/func.c"
#endif

#ifdef W5500Connection
#include "modules/w5500/func.c"
#endif

#ifdef DS18B20Connection
#include "modules/ds18b20/func.c"
#endif

#ifdef RelayConnection
#include "modules/relay/func.c"
#endif

#ifdef InputConnection
#include "modules/input/func.c"
#endif

#include "modules/virtual/func.c"

void modules_init()
{

#if USE_WATCHDOG == 1
    IWDG_WriteAccessCmd(IWDG_Prescaler_4);
    IWDG_SetReload(0x0FFF);
    IWDG_ReloadCounter();
    IWDG_Enable();
#endif

#if DISABLE_JTAG == 1
    delay_ms(5000);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
#endif

#ifdef IOModuleConnection
#include "modules/io_module/gpio.c"
#endif

#ifdef DEVICE_INDEX
    device_index = (uint8_t)DEVICE_INDEX;
#else
    device_index = io_module_get_device_index();
#endif

#ifdef RelayConnection
#include "modules/relay/gpio.c"
    relay_ini();
#endif

#ifdef W5500Connection
#include "modules/w5500/gpio.c"
    w5500_ini();
#endif

#ifdef DS18B20Connection
#include "modules/ds18b20/gpio.c"
    ds18b20_ini();
#endif

#ifdef InputConnection
#include "modules/input/gpio.c"
    input_ini();
#endif

    virtual_ini();

    // modules initialized
    system_loaded = 1;
    LEDBLINK(16);
    return;
}

void modules_interruptions()
{
#if USE_WATCHDOG == 1
    IWDG_ReloadCounter();
#endif

    // Counting working time
    interruption_counter++;
    if (interruption_counter >= 1000)
    {
        seconds_since_start++;
        interruption_counter = 0;
    }
    // End counting working time

#ifdef IOModuleConnection
    io_panel_int();
#endif

#ifdef W5500Connection
    w5500_int();
#endif

#ifdef DS18B20Connection
    ds18b20_int();
#endif

#ifdef RelayConnection
    relay_int();
#endif

#ifdef InputConnection
    input_int();
#endif

    virtual_int();

    return;
}
