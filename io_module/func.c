#if IOModuleConnection == 1 // relay, sensors, leaks
	#define IOModule_clockPort GPIOA
	#define IOModule_clockPin GPIO_Pin_8
	#define IOModule_MOSIPort GPIOB
	#define IOModule_MOSIPin GPIO_Pin_15
	#define IOModule_latchPort GPIOB 
	#define IOModule_latchPin GPIO_Pin_14 
	#define IOModule_checkPort GPIOB 
	#define IOModule_checkPin GPIO_Pin_13 
	#define IOModule_MISOPort GPIOB
	#define IOModule_MISOPin GPIO_Pin_12
#elif IOModuleConnection == 2 // ventilation, light, access, watering
	#define IOModule_clockPort GPIOB
	#define IOModule_clockPin GPIO_Pin_12
	#define IOModule_MOSIPort GPIOB
	#define IOModule_MOSIPin GPIO_Pin_13
	#define IOModule_latchPort GPIOB 
	#define IOModule_latchPin GPIO_Pin_14 
	#define IOModule_checkPort GPIOB 
	#define IOModule_checkPin GPIO_Pin_15
	#define IOModule_MISOPort GPIOA
	#define IOModule_MISOPin GPIO_Pin_8
#elif IOModuleConnection == 3 // FSCD, movesensors
	#define IOModule_clockPort GPIOA
	#define IOModule_clockPin GPIO_Pin_15
	#define IOModule_MOSIPort GPIOA
	#define IOModule_MOSIPin GPIO_Pin_12
	#define IOModule_latchPort GPIOA 
	#define IOModule_latchPin GPIO_Pin_11 
	#define IOModule_checkPort GPIOA
	#define IOModule_checkPin GPIO_Pin_1
	#define IOModule_MISOPort GPIOA
	#define IOModule_MISOPin GPIO_Pin_9
#endif

volatile uint8_t io_module_r[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, io_module_w[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t io_module_timer = 0;

/// @brief Interruptions, called every millisecond
void io_panel_int(){
    // indicator in/out process
	GPIO_SetBits(IOModule_checkPort, IOModule_checkPin);
	GPIO_ResetBits(IOModule_latchPort, IOModule_latchPin);
	for(int a = 0; a< 16;a++){
		io_module_r[a] <<= 1;
		if(GPIO_ReadInputDataBit(IOModule_MISOPort, IOModule_MISOPin) == 1){ 
			io_module_r[a] |= 1;
		} 

		if(io_module_w[a] == 1) GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin); else if(io_module_w[a] == 0) GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
		else if(io_module_w[a] == 2){//blink
			if(io_module_timer < 250){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer >= 250){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			}
		} else if(io_module_w[a] == 3){// fast blink
			if(io_module_timer < 50){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 100){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 150){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 200){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 250){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 300){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 350){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 400){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 450){
				GPIO_SetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			} else if(io_module_timer < 500){
				GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);
			}
		}
		GPIO_ResetBits(IOModule_clockPort, IOModule_clockPin);
		GPIO_SetBits(IOModule_clockPort, IOModule_clockPin);
	}
	GPIO_SetBits(IOModule_latchPort, IOModule_latchPin);
	GPIO_ResetBits(IOModule_checkPort, IOModule_checkPin);

    io_module_timer++;
    if(io_module_timer >= 500) io_module_timer = 0;


}

/// @brief Make LED blink
/// @param led 
void LEDBLINK(uint8_t led){
	if (led > 0 && led < 17) io_module_w[16 - led] = 2;
}

/// @brief Make LED blink fast
/// @param led 
void LEDBLINKFAST(uint8_t led){
	if (led > 0 && led < 17) io_module_w[16 - led] = 3;
}

/// @brief Turn ON LED 
/// @param led 
void LEDON(uint8_t led){
	if (led > 0 && led < 17) io_module_w[16 - led] = 1;
}

/// @brief Turn OFF LED
/// @param led 
void LEDOFF(uint8_t led){
	if (led > 0 && led < 17) io_module_w[16 - led] = 0;
}

/// @brief Returns 1 if button pressed at this moment.
/// @param button 
/// @return 1/0
uint8_t io_module_button_pressed(uint8_t button){
	if (button < 1 || button > 16) return 0;
	uint8_t key;
	if (button <= 8){
		key = 8 - button;
	} else {
		key = 24 - button;
	}
	if (io_module_r[key] == 0xFF) return 1;
	else return 0;
}

/// @brief Returns device index, used in communication with server (DIP switch 1-6 pins)
/// @return index
uint8_t io_module_get_device_index(){
	uint8_t index = 0;
	if(io_module_button_pressed(12)) index += 1;
	if(io_module_button_pressed(11)) index += 2;
	if(io_module_button_pressed(10)) index += 4;
	if(io_module_button_pressed(9)) index += 8;
	if(io_module_button_pressed(16)) index += 16;
	if(io_module_button_pressed(15)) index += 32;

	return index;
}