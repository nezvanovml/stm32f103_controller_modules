#define MODULES_VERSION 1

// Counting working time
uint32_t seconds_since_start = 0; // Counts how seconds controller is online
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


void modules_init(){

    #ifdef IOModuleConnection
    #include "modules/io_module/gpio.c"
    #endif

    #ifdef DEVICE_INDEX
    device_index = (uint8_t)DEVICE_INDEX;
    #else
    delay_ms(1000); // needed for convert DIP switch to device_index
    device_index = io_module_get_device_index();
    #endif
    
    #if DISABLE_JTAG == 1
	delay_ms(5000);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
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
	LEDBLINK(16);
    return;
}



void modules_interruptions(){
    // Counting working time
    interruption_counter++;
    if(interruption_counter >= 1000){
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
