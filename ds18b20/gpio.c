// initializing data port
Init_PORT.GPIO_Pin = DS18B20_dataPin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_OD;
GPIO_Init(DS18B20_dataPort, &Init_PORT);