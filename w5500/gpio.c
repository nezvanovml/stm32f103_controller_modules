//reset pin 
Init_PORT.GPIO_Pin = W5500_resetPin;
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
Init_PORT.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(W5500_resetPort, &Init_PORT);
GPIO_SetBits(W5500_resetPort, W5500_resetPin); 

//cs
Init_PORT.GPIO_Pin = (W5500_csPin);
Init_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_Init(W5500_csPort , &Init_PORT);

//miso
Init_PORT.GPIO_Pin = W5500_MISOPin ;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
GPIO_Init(W5500_MISOPort, &Init_PORT);


//mosi
Init_PORT.GPIO_Pin = W5500_MOSIPin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_Init(W5500_MOSIPort, &Init_PORT);

//clock
Init_PORT.GPIO_Pin = W5500_clockPin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
Init_PORT.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_Init(W5500_clockPort, &Init_PORT);

#if W5500_SPI == 1
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
SPI_I2S_DeInit( SPI1 ); 
#elif W5500_SPI == 2
RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
SPI_I2S_DeInit( SPI2 ); 
#endif


SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; 
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
SPI_InitStructure.SPI_CRCPolynomial = 0x7;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;  
for(int a = 0; a < 65536;a++) for(int b = 0; b < 65536; b++);


#if W5500_SPI == 1
SPI_Init(SPI1, &SPI_InitStructure); 
SPI_Cmd(SPI1, ENABLE);
#elif W5500_SPI == 2
SPI_Init(SPI2, &SPI_InitStructure); 
SPI_Cmd(SPI2, ENABLE);
#endif



