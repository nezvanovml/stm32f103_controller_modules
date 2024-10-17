#ifdef Relay_ch1_Port
Init_PORT.GPIO_Pin = Relay_ch1_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch1_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch1_Port, Relay_ch1_Pin);
#endif

#ifdef Relay_ch2_Port
Init_PORT.GPIO_Pin = Relay_ch2_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch2_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch2_Port, Relay_ch2_Pin);
#endif

#ifdef Relay_ch3_Port
Init_PORT.GPIO_Pin = Relay_ch3_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch3_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch3_Port, Relay_ch3_Pin);
#endif

#ifdef Relay_ch4_Port
Init_PORT.GPIO_Pin = Relay_ch4_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch4_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch4_Port, Relay_ch4_Pin);
#endif

#ifdef Relay_ch5_Port
Init_PORT.GPIO_Pin = Relay_ch5_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch5_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch5_Port, Relay_ch5_Pin);
#endif

#ifdef Relay_ch6_Port
Init_PORT.GPIO_Pin = Relay_ch6_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch6_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch6_Port, Relay_ch6_Pin);
#endif

#ifdef Relay_ch7_Port
Init_PORT.GPIO_Pin = Relay_ch7_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch7_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch7_Port, Relay_ch7_Pin);
#endif

#ifdef Relay_ch8_Port
Init_PORT.GPIO_Pin = Relay_ch8_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(Relay_ch8_Port, &Init_PORT);
GPIO_ResetBits(Relay_ch8_Port, Relay_ch8_Pin);
#endif