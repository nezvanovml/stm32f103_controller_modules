// MISO
Init_PORT.GPIO_Pin = IOModule_MISOPin;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
GPIO_Init(IOModule_MISOPort, &Init_PORT);
GPIO_ResetBits(IOModule_MISOPort, IOModule_MISOPin);

// MOSI
Init_PORT.GPIO_Pin = IOModule_MOSIPin;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(IOModule_MOSIPort, &Init_PORT);
GPIO_ResetBits(IOModule_MOSIPort, IOModule_MOSIPin);

// latch
Init_PORT.GPIO_Pin = IOModule_latchPin;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(IOModule_latchPort, &Init_PORT);
GPIO_ResetBits(IOModule_latchPort, IOModule_latchPin);

// check
Init_PORT.GPIO_Pin = IOModule_checkPin;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(IOModule_checkPort, &Init_PORT);
GPIO_ResetBits(IOModule_checkPort, IOModule_checkPin);

// clock
Init_PORT.GPIO_Pin = IOModule_clockPin;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(IOModule_clockPort, &Init_PORT);
GPIO_ResetBits(IOModule_clockPort, IOModule_clockPin);