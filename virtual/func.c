#ifndef VIRTUAL_NUM_OF_SWITCH
	#define VIRTUAL_NUM_OF_SWITCH 0
#endif

#ifndef VIRTUAL_NUM_OF_BUTTON
	#define VIRTUAL_NUM_OF_BUTTON 0
#endif

#ifndef VIRTUAL_NUM_OF_BINARY_SENSOR
	#define VIRTUAL_NUM_OF_BINARY_SENSOR 0
#endif

#ifndef VIRTUAL_NUM_OF_NUMERIC
	#define VIRTUAL_NUM_OF_NUMERIC 0
#endif


uint8_t virtual_switch_state[VIRTUAL_NUM_OF_SWITCH], virtual_button_state[VIRTUAL_NUM_OF_BUTTON], virtual_binary_sensor_state[VIRTUAL_NUM_OF_BINARY_SENSOR]; 
int16_t virtual_numeric[VIRTUAL_NUM_OF_NUMERIC]; 

/// @brief Interruptions, called every millisecond
void virtual_int(){
	return;
}

/// @brief Initialization of virtual entities. Insert before main loop.
void virtual_ini(){
    for(uint8_t i=0;i < VIRTUAL_NUM_OF_SWITCH;i++){
        virtual_switch_state[i] = 0;
    }
	for(uint8_t i=0;i < VIRTUAL_NUM_OF_BUTTON;i++){
        virtual_button_state[i] = 0;
    }
	for(uint8_t i=0;i < VIRTUAL_NUM_OF_BINARY_SENSOR;i++){
        virtual_binary_sensor_state[i] = 0;
    }
	for(uint8_t i=0;i < VIRTUAL_NUM_OF_NUMERIC;i++){
        virtual_numeric[i] = 0;
    }
}

/// @brief Turns virtual_switch ON
/// @param virtual_switch number of virtual_switch (1...VIRTUAL_NUM_OF_SWITCH)
void VIRTUAL_SWITCH_ON(uint8_t virtual_switch){
	if (virtual_switch > 0 && virtual_switch <= VIRTUAL_NUM_OF_SWITCH) virtual_switch_state[virtual_switch - 1] = 1;
}

/// @brief Turns relay OFF
/// @param virtual_switch number of virtual_switch (1...VIRTUAL_NUM_OF_SWITCH)
void VIRTUAL_SWITCH_OFF(uint8_t virtual_switch){
	if (virtual_switch > 0 && virtual_switch <= VIRTUAL_NUM_OF_SWITCH) virtual_switch_state[virtual_switch - 1] = 0;
}

/// @brief Toggle virtual_switch (ON->OFF / OFF->ON)
/// @param virtual_switch number of virtual_switch (1...VIRTUAL_NUM_OF_SWITCH)
void VIRTUAL_SWITCH_TOGGLE(uint8_t virtual_switch){
	if (virtual_switch > 0 && virtual_switch <= VIRTUAL_NUM_OF_SWITCH){
		if(virtual_switch_state[virtual_switch - 1]) virtual_switch_state[virtual_switch - 1] = 0;
		else virtual_switch_state[virtual_switch - 1] = 1;
	}
}

/// @brief Returns 1 if virtual_switch is ON at this moment.
/// @param virtual_switch 
/// @return 1 / 0
uint8_t virtual_switch_get_state(uint8_t virtual_switch){
	if (virtual_switch < 1 || virtual_switch > VIRTUAL_NUM_OF_SWITCH) return 0;
	if (virtual_switch_state[virtual_switch - 1] == 1) return 1;
	else return 0;
}

/// @brief Press button
/// @param virtual_button number of virtual_button (1...VIRTUAL_NUM_OF_BUTTON)
void VIRTUAL_BUTTON_PRESS(uint8_t virtual_button){
	if (virtual_button > 0 && virtual_button <= VIRTUAL_NUM_OF_BUTTON) virtual_button_state[virtual_button - 1] = 1;
}

/// @brief Returns 1 if virtual_button is pressed.
/// @param virtual_button 
/// @return 1 / 0
uint8_t virtual_button_get_state(uint8_t virtual_button){
	if (virtual_button < 1 || virtual_button > VIRTUAL_NUM_OF_BUTTON) return 0;
	if (virtual_button_state[virtual_button - 1] == 1) return 1;
	else return 0;
}

/// @brief Turns virtual_binary_sensor ON
/// @param virtual_binary_sensor number of virtual_binary_sensor (1...VIRTUAL_NUM_OF_BINARY_SENSOR)
void VIRTUAL_BINARY_SENSOR_ON(uint8_t virtual_binary_sensor){
	if (virtual_binary_sensor > 0 && virtual_binary_sensor <= VIRTUAL_NUM_OF_BINARY_SENSOR) virtual_binary_sensor_state[virtual_binary_sensor - 1] = 1;
}

/// @brief Turns virtual_binary_sensor OFF
/// @param virtual_binary_sensor number of virtual_binary_sensor (1...VIRTUAL_NUM_OF_BINARY_SENSOR)
void VIRTUAL_BINARY_SENSOR_OFF(uint8_t virtual_binary_sensor){
	if (virtual_binary_sensor > 0 && virtual_binary_sensor <= VIRTUAL_NUM_OF_BINARY_SENSOR) virtual_binary_sensor_state[virtual_binary_sensor - 1] = 0;
}

/// @brief Returns 1 if virtual_binary_sensor is ON.
/// @param virtual_binary_sensor 
/// @return 1 / 0
uint8_t virtual_binary_sensor_get_state(uint8_t virtual_binary_sensor){
	if (virtual_binary_sensor < 1 || virtual_binary_sensor > VIRTUAL_NUM_OF_BINARY_SENSOR) return 0;
	if (virtual_binary_sensor_state[virtual_binary_sensor - 1] == 1) return 1;
	else return 0;
}

/// @brief Set virtual numeric
/// @param index index of numeric
/// @param value value to set
void virtual_numeric_set_value(uint8_t index, int16_t value){
	if (index < 1 || index > VIRTUAL_NUM_OF_NUMERIC) return;
	virtual_numeric[index - 1] = value;
}

/// @brief Get virtual numeric
/// @param index index of numeric
int16_t virtual_numeric_get_value(uint8_t index){
	if (index < 1 || index > VIRTUAL_NUM_OF_NUMERIC) return 0;
	return virtual_numeric[index - 1];
}

/// @brief Appends input data
/// @param body string where to append input data
void virtual_add_data_to_str(char *body){
	strcat(body, "\"v_switch\":[");
    for(uint8_t i = 0; i < VIRTUAL_NUM_OF_SWITCH; i++){
			char temp[5];
			xsprintf(temp, "%d,", virtual_switch_get_state(i+1));
			strcat(body, temp);
			if((i+1) == VIRTUAL_NUM_OF_SWITCH) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "],\"v_button\":[");
	for(uint8_t i = 0; i < VIRTUAL_NUM_OF_BUTTON; i++){
			char temp[5];
			xsprintf(temp, "%d,", virtual_button_get_state(i+1));
			strcat(body, temp);
			if((i+1) == VIRTUAL_NUM_OF_BUTTON) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "],\"v_binary_sensor\":[");
	for(uint8_t i = 0; i < VIRTUAL_NUM_OF_BINARY_SENSOR; i++){
			char temp[5];
			xsprintf(temp, "%d,", virtual_binary_sensor_get_state(i+1));
			strcat(body, temp);
			if((i+1) == VIRTUAL_NUM_OF_BINARY_SENSOR) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "],\"v_numeric\":[");
	for(uint8_t i = 0; i < VIRTUAL_NUM_OF_NUMERIC; i++){
			char temp[5];
			xsprintf(temp, "%d,", virtual_numeric_get_value(i+1));
			strcat(body, temp);
			if((i+1) == VIRTUAL_NUM_OF_NUMERIC) body[strlen(body) - 1] = '\0';
        }
	strcat(body, "]");

}

/// @brief Appends input data
/// @param body string where to append input data
void virtual_add_info_to_str(char *body){
	char temp[100];
	xsprintf(temp, "\"v_switch\":%d,\"v_button\":%d,\"v_sensor\":%d,\"v_numeric\":%d",VIRTUAL_NUM_OF_SWITCH,VIRTUAL_NUM_OF_BUTTON,VIRTUAL_NUM_OF_BINARY_SENSOR, VIRTUAL_NUM_OF_NUMERIC);
	strcat(body, temp);
}