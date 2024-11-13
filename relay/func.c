#if RelayConnection == 1 // relay
#define RELAY_NUM_OF_CHANNELS 8

#define Relay_ch1_Port GPIOB
#define Relay_ch1_Pin GPIO_Pin_5
#define Relay_ch2_Port GPIOB
#define Relay_ch2_Pin GPIO_Pin_4
#define Relay_ch3_Port GPIOB
#define Relay_ch3_Pin GPIO_Pin_3
#define Relay_ch4_Port GPIOA
#define Relay_ch4_Pin GPIO_Pin_15
#define Relay_ch5_Port GPIOB
#define Relay_ch5_Pin GPIO_Pin_6
#define Relay_ch6_Port GPIOB
#define Relay_ch6_Pin GPIO_Pin_7
#define Relay_ch7_Port GPIOB
#define Relay_ch7_Pin GPIO_Pin_8
#define Relay_ch8_Port GPIOB
#define Relay_ch8_Pin GPIO_Pin_9

#define DISABLE_JTAG 1

#elif RelayConnection == 2 // ventilation
#define RELAY_NUM_OF_CHANNELS 6

#define Relay_ch1_Port GPIOA
#define Relay_ch1_Pin GPIO_Pin_2
#define Relay_ch2_Port GPIOA
#define Relay_ch2_Pin GPIO_Pin_1
#define Relay_ch3_Port GPIOA
#define Relay_ch3_Pin GPIO_Pin_0
#define Relay_ch4_Port GPIOC
#define Relay_ch4_Pin GPIO_Pin_15
#define Relay_ch5_Port GPIOC
#define Relay_ch5_Pin GPIO_Pin_14
#define Relay_ch6_Port GPIOC
#define Relay_ch6_Pin GPIO_Pin_13

#elif RelayConnection == 3 // lights
#define RELAY_NUM_OF_CHANNELS 8
#define RELAY_AS_LIGHT 1

#define Relay_ch1_Port GPIOB
#define Relay_ch1_Pin GPIO_Pin_1
#define Relay_ch2_Port GPIOB
#define Relay_ch2_Pin GPIO_Pin_0
#define Relay_ch3_Port GPIOA
#define Relay_ch3_Pin GPIO_Pin_2
#define Relay_ch4_Port GPIOA
#define Relay_ch4_Pin GPIO_Pin_1
#define Relay_ch5_Port GPIOA
#define Relay_ch5_Pin GPIO_Pin_0
#define Relay_ch6_Port GPIOC
#define Relay_ch6_Pin GPIO_Pin_15
#define Relay_ch7_Port GPIOC
#define Relay_ch7_Pin GPIO_Pin_14
#define Relay_ch8_Port GPIOC
#define Relay_ch8_Pin GPIO_Pin_13

#elif RelayConnection == 4 // access, watering
#define RELAY_NUM_OF_CHANNELS 5

#define Relay_ch1_Port GPIOB
#define Relay_ch1_Pin GPIO_Pin_7
#define Relay_ch2_Port GPIOB
#define Relay_ch2_Pin GPIO_Pin_6
#define Relay_ch3_Port GPIOB
#define Relay_ch3_Pin GPIO_Pin_5
#define Relay_ch4_Port GPIOB
#define Relay_ch4_Pin GPIO_Pin_4
#define Relay_ch5_Port GPIOB
#define Relay_ch5_Pin GPIO_Pin_3
#elif RelayConnection == 5 // waterleaks
#define RELAY_NUM_OF_CHANNELS 2

#define Relay_ch1_Port GPIOA
#define Relay_ch1_Pin GPIO_Pin_9
#define Relay_ch2_Port GPIOA
#define Relay_ch2_Pin GPIO_Pin_10
#elif RelayConnection == 6 // FSCD, movesensors
#define RELAY_NUM_OF_CHANNELS 2

#define Relay_ch1_Port GPIOB
#define Relay_ch1_Pin GPIO_Pin_3 // reset
#define Relay_ch2_Port GPIOB
#define Relay_ch2_Pin GPIO_Pin_4 // alarm

#define DISABLE_JTAG 1
#endif

#ifndef RELAY_IMPULSE_LONG
#define RELAY_IMPULSE_LONG 1000
#endif

uint8_t relay_state[RELAY_NUM_OF_CHANNELS], relay_target[RELAY_NUM_OF_CHANNELS];
uint16_t relay_impulse[RELAY_NUM_OF_CHANNELS];

/// @brief Interruptions, called every millisecond
void relay_int()
{
	uint8_t current_relay;

#ifdef Relay_ch1_Port
	current_relay = 0;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch1_Port, Relay_ch1_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch1_Port, Relay_ch1_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch2_Port
	current_relay = 1;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch2_Port, Relay_ch2_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch2_Port, Relay_ch2_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch3_Port
	current_relay = 2;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch3_Port, Relay_ch3_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch3_Port, Relay_ch3_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch4_Port
	current_relay = 3;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch4_Port, Relay_ch4_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch4_Port, Relay_ch4_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch5_Port
	current_relay = 4;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch5_Port, Relay_ch5_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch5_Port, Relay_ch5_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch6_Port
	current_relay = 5;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch6_Port, Relay_ch6_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch6_Port, Relay_ch6_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch7_Port
	current_relay = 6;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch7_Port, Relay_ch7_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch7_Port, Relay_ch7_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

#ifdef Relay_ch8_Port
	current_relay = 7;
	if (relay_state[current_relay] != relay_target[current_relay])
	{
		if (relay_target[current_relay] == 0)
		{
			GPIO_ResetBits(Relay_ch8_Port, Relay_ch8_Pin);
			LEDOFF(current_relay + 1);
		}
		else
		{
			GPIO_SetBits(Relay_ch8_Port, Relay_ch8_Pin);
			LEDON(current_relay + 1);
		}
		relay_state[current_relay] = relay_target[current_relay];
	}
#endif

	// handling pulses
	for (uint8_t i = 0; i < RELAY_NUM_OF_CHANNELS; i++)
	{
		if (relay_impulse[i] > 0)
		{
			LEDBLINK(i + 1);
			if (relay_impulse[i] <= 1)
			{
				relay_target[i] = 0;
				relay_impulse[i] = 0;
				LEDOFF(i + 1);
			}
			else
			{
				relay_impulse[i]--;
			}
		}
	}
}

/// @brief Initialization of relays. Insert before main loop.
void relay_ini()
{
	for (uint8_t i = 0; i < RELAY_NUM_OF_CHANNELS; i++)
	{
		relay_state[i] = 0;
		relay_target[i] = 0;
		relay_impulse[i] = 0;
	}
}

/// @brief Turn relay ON
/// @param relay number of relay (1...RELAY_NUM_OF_CHANNELS)
void RELAY_ON(uint8_t relay)
{
	if (relay > 0 && relay <= RELAY_NUM_OF_CHANNELS)
		relay_target[relay - 1] = 1;
}

/// @brief Turn relay OFF
/// @param relay number of relay (1...RELAY_NUM_OF_CHANNELS)
void RELAY_OFF(uint8_t relay)
{
	if (relay > 0 && relay <= RELAY_NUM_OF_CHANNELS)
		relay_target[relay - 1] = 0;
}

/// @brief Toggle relay (ON->OFF / OFF->ON)
/// @param relay number of relay (1...RELAY_NUM_OF_CHANNELS)
void RELAY_TOGGLE(uint8_t relay)
{
	if (relay > 0 && relay <= RELAY_NUM_OF_CHANNELS)
	{
		if (relay_state[relay - 1])
			relay_target[relay - 1] = 0;
		else
			relay_target[relay - 1] = 1;
	}
}

/// @brief Turn relay ON for ms milliseconds
/// @param relay number of relay (1...RELAY_NUM_OF_CHANNELS)
void RELAY_IMPULSE(uint8_t relay)
{
	if (relay > 0 && relay <= RELAY_NUM_OF_CHANNELS)
	{
		relay_target[relay - 1] = 1;
		relay_impulse[relay - 1] = RELAY_IMPULSE_LONG;
	}
}

/// @brief Returns 1 if relay is ON at this moment.
/// @param relay
/// @return 1 / 0
uint8_t relay_get_state(uint8_t relay)
{
	if (relay < 1 || relay > RELAY_NUM_OF_CHANNELS)
		return 0;
	if (relay_state[relay - 1] == 1)
		return 1;
	else
		return 0;
}

/// @brief Appends input data
/// @param body string where to append input data
void relay_add_data_to_str(char *body)
{
	#ifndef RELAY_AS_LIGHT
	strcat(body, "\"relay\":[");
	#else
	strcat(body, "\"light\":[");
	#endif
	for (uint8_t i = 0; i < RELAY_NUM_OF_CHANNELS; i++)
	{
		char temp[5];
		xsprintf(temp, "%d,", relay_get_state(i + 1));
		strcat(body, temp);
		if ((i + 1) == RELAY_NUM_OF_CHANNELS)
			body[strlen(body) - 1] = '\0';
	}
	strcat(body, "]");
}

/// @brief Appends input data
/// @param body string where to append input data
void relay_add_info_to_str(char *body)
{
	char temp[20];
	#ifndef RELAY_AS_LIGHT
	xsprintf(temp, "\"relay\":%d", RELAY_NUM_OF_CHANNELS);
	#else
	xsprintf(temp, "\"light\":%d", RELAY_NUM_OF_CHANNELS);
	#endif
	strcat(body, temp);
}