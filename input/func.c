/* 
There are 4 types of input:
* Button (0/1) - simple button or state (on/off). Maximum: 8. By default pulled-up to +3.3v
* Counter - counts times state of input changed. Can be used for power/water meters etc. Maximum: 4
* Binary_Sensor (0/1) - simple state (on/off). Maximum: 8. By default pulled-up to +3.3v
* Analog_input (0..100) ADC. Maximum: 10.
*/
#if InputConnection == 1 // access, watering
	#define INPUT_NUM_OF_BUTTON 5
	
	#define Button_ch1_Port GPIOA
	#define Button_ch1_Pin GPIO_Pin_15
	#define Button_ch1_Inverted 1

	#define Button_ch2_Port GPIOA
	#define Button_ch2_Pin GPIO_Pin_12
	#define Button_ch2_Inverted 1

	#define Button_ch3_Port GPIOA
	#define Button_ch3_Pin GPIO_Pin_11
	#define Button_ch3_Inverted 1

	#define Button_ch4_Port GPIOA
	#define Button_ch4_Pin GPIO_Pin_10
	#define Button_ch4_Inverted 1

	#define Button_ch5_Port GPIOA
	#define Button_ch5_Pin GPIO_Pin_9
	#define Button_ch5_Inverted 1

	#define INPUT_NUM_OF_BINARY_SENSOR 5

	#define BinarySensor_ch1_Port GPIOC
	#define BinarySensor_ch1_Pin GPIO_Pin_13
	#define BinarySensor_ch1_Inverted 0

	#define BinarySensor_ch2_Port GPIOC
	#define BinarySensor_ch2_Pin GPIO_Pin_14
	#define BinarySensor_ch2_Inverted 0

	#define BinarySensor_ch3_Port GPIOC
	#define BinarySensor_ch3_Pin GPIO_Pin_15
	#define BinarySensor_ch3_Inverted 0

	#define BinarySensor_ch4_Port GPIOA
	#define BinarySensor_ch4_Pin GPIO_Pin_0
	#define BinarySensor_ch4_Inverted 0

	#define BinarySensor_ch5_Port GPIOA
	#define BinarySensor_ch5_Pin GPIO_Pin_1
	#define BinarySensor_ch5_Inverted 0
#elif InputConnection == 2 // waterleaks
	#define INPUT_NUM_OF_BINARY_SENSOR 6

	#define BinarySensor_ch1_Port GPIOA
	#define BinarySensor_ch1_Pin GPIO_Pin_1
	#define BinarySensor_ch1_Inverted 1
	#define BinarySensor_ch1_NeedPullDown 0

	#define BinarySensor_ch2_Port GPIOA
	#define BinarySensor_ch2_Pin GPIO_Pin_2
	#define BinarySensor_ch2_Inverted 1
	#define BinarySensor_ch2_NeedPullDown 0

	#define BinarySensor_ch3_Port GPIOB
	#define BinarySensor_ch3_Pin GPIO_Pin_0
	#define BinarySensor_ch3_Inverted 1
	#define BinarySensor_ch3_NeedPullDown 0

	#define BinarySensor_ch4_Port GPIOB
	#define BinarySensor_ch4_Pin GPIO_Pin_1
	#define BinarySensor_ch4_Inverted 1
	#define BinarySensor_ch4_NeedPullDown 0

	#define BinarySensor_ch5_Port GPIOB
	#define BinarySensor_ch5_Pin GPIO_Pin_10
	#define BinarySensor_ch5_Inverted 1
	#define BinarySensor_ch5_NeedPullDown 0

	#define BinarySensor_ch6_Port GPIOB
	#define BinarySensor_ch6_Pin GPIO_Pin_11
	#define BinarySensor_ch6_Inverted 1
	#define BinarySensor_ch6_NeedPullDown 0
#elif InputConnection == 3 // FSCD, movesensors
	#define INPUT_NUM_OF_ANALOG_INPUT 10

	#define AnalogInput_ch1_Port GPIOA
	#define AnalogInput_ch1_Pin GPIO_Pin_0
	#define AnalogInput_ch1_ADC_Channel ADC_Channel_0

	#define AnalogInput_ch2_Port GPIOA
	#define AnalogInput_ch2_Pin GPIO_Pin_1
	#define AnalogInput_ch2_ADC_Channel ADC_Channel_1

	#define AnalogInput_ch3_Port GPIOA
	#define AnalogInput_ch3_Pin GPIO_Pin_2
	#define AnalogInput_ch3_ADC_Channel ADC_Channel_2

	#define AnalogInput_ch4_Port GPIOA
	#define AnalogInput_ch4_Pin GPIO_Pin_3
	#define AnalogInput_ch4_ADC_Channel ADC_Channel_3
	
	#define AnalogInput_ch5_Port GPIOA
	#define AnalogInput_ch5_Pin GPIO_Pin_4
	#define AnalogInput_ch5_ADC_Channel ADC_Channel_4

	#define AnalogInput_ch6_Port GPIOA
	#define AnalogInput_ch6_Pin GPIO_Pin_5
	#define AnalogInput_ch6_ADC_Channel ADC_Channel_5

	#define AnalogInput_ch7_Port GPIOA
	#define AnalogInput_ch7_Pin GPIO_Pin_6
	#define AnalogInput_ch7_ADC_Channel ADC_Channel_6

	#define AnalogInput_ch8_Port GPIOA
	#define AnalogInput_ch8_Pin GPIO_Pin_7
	#define AnalogInput_ch8_ADC_Channel ADC_Channel_7

	#define AnalogInput_ch9_Port GPIOB
	#define AnalogInput_ch9_Pin GPIO_Pin_0
	#define AnalogInput_ch9_ADC_Channel ADC_Channel_8

	#define AnalogInput_ch10_Port GPIOB
	#define AnalogInput_ch10_Pin GPIO_Pin_1
	#define AnalogInput_ch10_ADC_Channel ADC_Channel_9

#endif

#ifndef INPUT_NUM_OF_COUNTER
	#define INPUT_NUM_OF_COUNTER 0
#endif

#ifndef INPUT_NUM_OF_BUTTON
	#define INPUT_NUM_OF_BUTTON 0
#endif

#ifndef INPUT_NUM_OF_BINARY_SENSOR
	#define INPUT_NUM_OF_BINARY_SENSOR 0
#endif

#ifndef INPUT_NUM_OF_ANALOG_INPUT
	#define INPUT_NUM_OF_ANALOG_INPUT 0
#endif

uint8_t input_button_state[INPUT_NUM_OF_BUTTON], input_button_released[INPUT_NUM_OF_BUTTON];
uint8_t input_binary_sensor_state[INPUT_NUM_OF_BINARY_SENSOR], input_binary_sensor_released[INPUT_NUM_OF_BINARY_SENSOR];

uint8_t input_counter_state[INPUT_NUM_OF_COUNTER], input_counter_released[INPUT_NUM_OF_COUNTER];
uint32_t input_counter_ticks[INPUT_NUM_OF_COUNTER], input_counter_ticks_freeze[INPUT_NUM_OF_COUNTER];

uint16_t input_analog_ADC_buffer[INPUT_NUM_OF_ANALOG_INPUT];

/// @brief Interruptions, called every millisecond
void input_int(){
	#ifdef Button_ch1_Port
	input_button_state[0] <<= 1;
	if( (Button_ch1_Inverted && (GPIO_ReadInputDataBit(Button_ch1_Port, Button_ch1_Pin) == 0)) || (!Button_ch1_Inverted && (GPIO_ReadInputDataBit(Button_ch1_Port, Button_ch1_Pin) == 1))) input_button_state[0] |= 1;
	#endif
	#ifdef Button_ch2_Port
	input_button_state[1] <<= 1;
	if( (Button_ch2_Inverted && (GPIO_ReadInputDataBit(Button_ch2_Port, Button_ch2_Pin) == 0)) || (!Button_ch2_Inverted && (GPIO_ReadInputDataBit(Button_ch2_Port, Button_ch2_Pin) == 1))) input_button_state[1] |= 1;
	#endif
	#ifdef Button_ch3_Port
	input_button_state[2] <<= 1;
	if( (Button_ch3_Inverted && (GPIO_ReadInputDataBit(Button_ch3_Port, Button_ch3_Pin) == 0)) || (!Button_ch3_Inverted && (GPIO_ReadInputDataBit(Button_ch3_Port, Button_ch3_Pin) == 1))) input_button_state[2] |= 1;
	#endif
	#ifdef Button_ch4_Port
	input_button_state[3] <<= 1;
	if( (Button_ch4_Inverted && (GPIO_ReadInputDataBit(Button_ch4_Port, Button_ch4_Pin) == 0)) || (!Button_ch4_Inverted && (GPIO_ReadInputDataBit(Button_ch4_Port, Button_ch4_Pin) == 1))) input_button_state[3] |= 1;
	#endif
	#ifdef Button_ch5_Port
	input_button_state[4] <<= 1;
	if( (Button_ch5_Inverted && (GPIO_ReadInputDataBit(Button_ch5_Port, Button_ch5_Pin) == 0)) || (!Button_ch5_Inverted && (GPIO_ReadInputDataBit(Button_ch5_Port, Button_ch5_Pin) == 1))) input_button_state[4] |= 1;
	#endif
	#ifdef Button_ch6_Port
	input_button_state[5] <<= 1;
	if( (Button_ch6_Inverted && (GPIO_ReadInputDataBit(Button_ch6_Port, Button_ch6_Pin) == 0)) || (!Button_ch6_Inverted && (GPIO_ReadInputDataBit(Button_ch6_Port, Button_ch6_Pin) == 1))) input_button_state[5] |= 1;
	#endif
	#ifdef Button_ch7_Port
	input_button_state[6] <<= 1;
	if( (Button_ch7_Inverted && (GPIO_ReadInputDataBit(Button_ch7_Port, Button_ch7_Pin) == 0)) || (!Button_ch7_Inverted && (GPIO_ReadInputDataBit(Button_ch7_Port, Button_ch7_Pin) == 1))) input_button_state[6] |= 1;
	#endif
	#ifdef Button_ch8_Port
	input_button_state[7] <<= 1;
	if( (Button_ch8_Inverted && (GPIO_ReadInputDataBit(Button_ch8_Port, Button_ch8_Pin) == 0)) || (!Button_ch8_Inverted && (GPIO_ReadInputDataBit(Button_ch8_Port, Button_ch8_Pin) == 1))) input_button_state[7] |= 1;
	#endif

	for(uint8_t i = 0; i < INPUT_NUM_OF_BUTTON; i++){
		if (input_button_state[i] == 0xFF){
			if(input_button_released[i] == 1){
				input_button_released[i] = 0;
			}
		} else {
			input_button_released[i] = 1;
		}
	}

	#ifdef Counter_ch1_Port
	input_counter_state[0] <<= 1;
	if(GPIO_ReadInputDataBit(Counter_ch1_Port, Counter_ch1_Pin) == 1) input_counter_state[0] |= 1;
	#endif
	#ifdef Counter_ch2_Port
	input_counter_state[1] <<= 1;
	if(GPIO_ReadInputDataBit(Counter_ch2_Port, Counter_ch2_Pin) == 1) input_counter_state[1] |= 1;
	#endif
	#ifdef Counter_ch3_Port
	input_counter_state[2] <<= 1;
	if(GPIO_ReadInputDataBit(Counter_ch3_Port, Counter_ch3_Pin) == 1) input_counter_state[2] |= 1;
	#endif
	#ifdef Counter_ch4_Port
	input_counter_state[3] <<= 1;
	if(GPIO_ReadInputDataBit(Counter_ch3_Port, Counter_ch4_Pin) == 1) input_counter_state[3] |= 1;
	#endif

	for(uint8_t i = 0; i < INPUT_NUM_OF_COUNTER; i++){
		if (input_counter_state[i] == 0xFF){
			if(input_counter_released[i] == 1){
				input_counter_released[i] = 0;
				input_counter_ticks[i]++;
			} 
		} else {
			input_counter_released[i] = 1;
		}
	}

	#ifdef BinarySensor_ch1_Port
	input_binary_sensor_state[0] <<= 1;
	if( (BinarySensor_ch1_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch1_Port, BinarySensor_ch1_Pin) == 0)) || (!BinarySensor_ch1_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch1_Port, BinarySensor_ch1_Pin) == 1))) input_binary_sensor_state[0] |= 1;
	#endif
	#ifdef BinarySensor_ch2_Port
	input_binary_sensor_state[1] <<= 1;
	if( (BinarySensor_ch2_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch2_Port, BinarySensor_ch2_Pin) == 0)) || (!BinarySensor_ch2_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch2_Port, BinarySensor_ch2_Pin) == 1))) input_binary_sensor_state[1] |= 1;
	#endif
	#ifdef BinarySensor_ch3_Port
	input_binary_sensor_state[2] <<= 1;
	if( (BinarySensor_ch3_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch3_Port, BinarySensor_ch3_Pin) == 0)) || (!BinarySensor_ch3_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch3_Port, BinarySensor_ch3_Pin) == 1))) input_binary_sensor_state[2] |= 1;
	#endif
	#ifdef BinarySensor_ch4_Port
	input_binary_sensor_state[3] <<= 1;
	if( (BinarySensor_ch4_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch4_Port, BinarySensor_ch4_Pin) == 0)) || (!BinarySensor_ch4_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch4_Port, BinarySensor_ch4_Pin) == 1))) input_binary_sensor_state[3] |= 1;
	#endif
	#ifdef BinarySensor_ch5_Port
	input_binary_sensor_state[4] <<= 1;
	if( (BinarySensor_ch5_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch5_Port, BinarySensor_ch5_Pin) == 0)) || (!BinarySensor_ch5_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch5_Port, BinarySensor_ch5_Pin) == 1))) input_binary_sensor_state[4] |= 1;
	#endif
	#ifdef BinarySensor_ch6_Port
	input_binary_sensor_state[5] <<= 1;
	if( (BinarySensor_ch6_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch6_Port, BinarySensor_ch6_Pin) == 0)) || (!BinarySensor_ch6_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch6_Port, BinarySensor_ch6_Pin) == 1))) input_binary_sensor_state[5] |= 1;
	#endif
	#ifdef BinarySensor_ch7_Port
	input_binary_sensor_state[6] <<= 1;
	if( (BinarySensor_ch7_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch7_Port, BinarySensor_ch7_Pin) == 0)) || (!BinarySensor_ch7_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch7_Port, BinarySensor_ch7_Pin) == 1))) input_binary_sensor_state[6] |= 1;
	#endif
	#ifdef BinarySensor_ch8_Port
	input_binary_sensor_state[7] <<= 1;
	if( (BinarySensor_ch8_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch8_Port, BinarySensor_ch8_Pin) == 0)) || (!BinarySensor_ch8_Inverted && (GPIO_ReadInputDataBit(BinarySensor_ch8_Port, BinarySensor_ch8_Pin) == 1))) input_binary_sensor_state[7] |= 1;
	#endif

	for(uint8_t i = 0; i < INPUT_NUM_OF_BINARY_SENSOR; i++){
		if (input_binary_sensor_state[i] == 0xFF){
			if(input_binary_sensor_released[i] == 1){
				input_binary_sensor_released[i] = 0;
			}
		} else {
			input_binary_sensor_released[i] = 1;
		}
	}
	
}

/// @brief Initialization of input. Insert before main loop.
void input_ini(){
	for(uint8_t i; i < INPUT_NUM_OF_BUTTON; i++){
		input_button_state[i] = 0;
		input_button_released[i] = 0;
	}
	for(uint8_t i; i < INPUT_NUM_OF_COUNTER; i++){
		input_counter_ticks[i] = 0;
		input_counter_ticks_freeze[i] = 0;
		input_counter_released[i] = 0;
		input_counter_state[i] = 0;
	}
}

/// @brief Returns 1 if button pressed at this moment.
/// @param button 
/// @return 1 / 0
uint8_t input_button_pressed(uint8_t button){
	if (button < 1 || button > INPUT_NUM_OF_BUTTON) return 0;
	if (input_button_state[button - 1] == 0xFF) {
		return 1;
	} else return 0;
}

/// @brief Returns how many ticks got from input.
/// @param counter 
/// @return ticks
uint32_t input_counter_get_ticks(uint8_t counter){
	if (counter < 1 || counter > INPUT_NUM_OF_COUNTER) return 0;
	input_counter_ticks_freeze[counter-1] = input_counter_ticks[counter-1];
	return input_counter_ticks[counter-1];
}

/// @brief Returns how many ticks got from input.
/// @param counter 
void input_counter_ticks_commit(uint8_t counter){
	if (counter < 1 || counter > INPUT_NUM_OF_COUNTER) return 0;
	input_counter_ticks[counter-1] -= input_counter_ticks_freeze[counter-1];
}

/// @brief Returns 1 if binary sensor is pressed at this moment.
/// @param sensor 
/// @return 1 / 0
uint8_t input_binary_sensor_pressed(uint8_t sensor){
	if (sensor < 1 || sensor > INPUT_NUM_OF_BINARY_SENSOR) return 0;
	if (input_binary_sensor_state[sensor - 1] == 0xFF) {
		return 1;
	} else return 0;
}

/// @brief Returns mapped value from analog input
/// @param input
/// @return 0..100
uint8_t input_analog_get_value(uint8_t input){
	if (input < 1 || input > INPUT_NUM_OF_ANALOG_INPUT) return 0;
	return (uint8_t)(input_analog_ADC_buffer[input - 1] / 40.96);
}

/// @brief Appends input data
/// @param body string where to append input data
void input_add_data_to_str(char *body){
	strcat(body, "\"button\":[");
    for(uint8_t i = 0; i < INPUT_NUM_OF_BUTTON; i++){

			char temp[5];
			xsprintf(temp, "%d,", input_button_pressed(i+1));
			strcat(body, temp);
			if((i+1) == INPUT_NUM_OF_BUTTON) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "], \"counter\":[");
	for(uint8_t i = 0; i < INPUT_NUM_OF_COUNTER; i++){

			char temp[5];
			xsprintf(temp, "%d,", input_counter_get_ticks(i+1));
			strcat(body, temp);
			if((i+1) == INPUT_NUM_OF_COUNTER) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "], \"binary_sensor\":[");
	for(uint8_t i = 0; i < INPUT_NUM_OF_BINARY_SENSOR; i++){

			char temp[5];
			xsprintf(temp, "%d,", input_binary_sensor_pressed(i+1));
			strcat(body, temp);
			if((i+1) == INPUT_NUM_OF_BINARY_SENSOR) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "], \"analog_in\":[");
	for(uint8_t i = 0; i < INPUT_NUM_OF_ANALOG_INPUT; i++){

			char temp[5];
			xsprintf(temp, "%d,", input_analog_get_value(i+1)); // xsprintf(temp, "%d,", map_value(0,4096,0,100,input_analog_ADC_buffer[i]));
			strcat(body, temp);
			if((i+1) == INPUT_NUM_OF_ANALOG_INPUT) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "]");

}

/// @brief Appends input data
/// @param body string where to append input data
void input_add_info_to_str(char *body){
	char temp[20];
	xsprintf(temp, "\"button\":%d,",INPUT_NUM_OF_BUTTON);
	strcat(body, temp);
	xsprintf(temp, "\"counter\":%d,",INPUT_NUM_OF_COUNTER);
	strcat(body, temp);
	xsprintf(temp, "\"binary_sensor\":%d,",INPUT_NUM_OF_BINARY_SENSOR);
	strcat(body, temp);
	xsprintf(temp, "\"analog_in\":%d",INPUT_NUM_OF_ANALOG_INPUT);
	strcat(body, temp);
}