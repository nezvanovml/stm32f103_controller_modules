#ifdef Button_ch1_Port
Init_PORT.GPIO_Pin = Button_ch1_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch1_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch1_Port, &Init_PORT);
GPIO_ResetBits(Button_ch1_Port, Button_ch1_Pin);
#endif

#ifdef Button_ch2_Port
Init_PORT.GPIO_Pin = Button_ch2_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch2_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch2_Port, &Init_PORT);
GPIO_ResetBits(Button_ch2_Port, Button_ch2_Pin);
#endif

#ifdef Button_ch3_Port
Init_PORT.GPIO_Pin = Button_ch3_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch3_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch3_Port, &Init_PORT);
GPIO_ResetBits(Button_ch3_Port, Button_ch3_Pin);
#endif

#ifdef Button_ch4_Port
Init_PORT.GPIO_Pin = Button_ch4_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch4_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch4_Port, &Init_PORT);
GPIO_ResetBits(Button_ch4_Port, Button_ch4_Pin);
#endif

#ifdef Button_ch5_Port
Init_PORT.GPIO_Pin = Button_ch5_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch5_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch5_Port, &Init_PORT);
GPIO_ResetBits(Button_ch5_Port, Button_ch5_Pin);
#endif

#ifdef Button_ch6_Port
Init_PORT.GPIO_Pin = Button_ch6_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch6_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch6_Port, &Init_PORT);
GPIO_ResetBits(Button_ch6_Port, Button_ch6_Pin);
#endif

#ifdef Button_ch7_Port
Init_PORT.GPIO_Pin = Button_ch7_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch7_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch7_Port, &Init_PORT);
GPIO_ResetBits(Button_ch7_Port, Button_ch7_Pin);
#endif

#ifdef Button_ch8_Port
Init_PORT.GPIO_Pin = Button_ch8_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Button_ch8_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Button_ch8_Port, &Init_PORT);
GPIO_ResetBits(Button_ch8_Port, Button_ch8_Pin);
#endif


#ifdef Counter_ch1_Port
Init_PORT.GPIO_Pin = Counter_ch1_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Counter_ch1_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Counter_ch1_Port, &Init_PORT);
GPIO_ResetBits(Counter_ch1_Port, Counter_ch1_Pin);
#endif

#ifdef Counter_ch2_Port
Init_PORT.GPIO_Pin = Counter_ch2_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Counter_ch2_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Counter_ch2_Port, &Init_PORT);
GPIO_ResetBits(Counter_ch2_Port, Counter_ch2_Pin);
#endif

#ifdef Counter_ch3_Port
Init_PORT.GPIO_Pin = Counter_ch3_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Counter_ch3_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Counter_ch3_Port, &Init_PORT);
GPIO_ResetBits(Counter_ch3_Port, Counter_ch3_Pin);
#endif

#ifdef Counter_ch4_Port
Init_PORT.GPIO_Pin = Counter_ch4_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if Counter_ch4_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(Counter_ch4_Port, &Init_PORT);
GPIO_ResetBits(Counter_ch4_Port, Counter_ch4_Pin);
#endif


#ifdef BinarySensor_ch1_Port
Init_PORT.GPIO_Pin = BinarySensor_ch1_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch1_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch1_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch1_Port, BinarySensor_ch1_Pin);
#endif

#ifdef BinarySensor_ch2_Port
Init_PORT.GPIO_Pin = BinarySensor_ch2_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch2_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch2_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch2_Port, BinarySensor_ch2_Pin);
#endif

#ifdef BinarySensor_ch3_Port
Init_PORT.GPIO_Pin = BinarySensor_ch3_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch3_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch3_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch3_Port, BinarySensor_ch3_Pin);
#endif

#ifdef BinarySensor_ch4_Port
Init_PORT.GPIO_Pin = BinarySensor_ch4_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch4_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch4_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch4_Port, BinarySensor_ch4_Pin);
#endif

#ifdef BinarySensor_ch5_Port
Init_PORT.GPIO_Pin = BinarySensor_ch5_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch5_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch5_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch5_Port, BinarySensor_ch5_Pin);
#endif

#ifdef BinarySensor_ch6_Port
Init_PORT.GPIO_Pin = BinarySensor_ch6_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch6_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch6_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch6_Port, BinarySensor_ch6_Pin);
#endif

#ifdef BinarySensor_ch7_Port
Init_PORT.GPIO_Pin = BinarySensor_ch7_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch7_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch7_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch7_Port, BinarySensor_ch7_Pin);
#endif

#ifdef BinarySensor_ch8_Port
Init_PORT.GPIO_Pin = BinarySensor_ch8_Pin;
Init_PORT.GPIO_Speed = GPIO_Speed_10MHz;
#if BinarySensor_ch8_NeedPullDown == 1
Init_PORT.GPIO_Mode = GPIO_Mode_IPD;
#else
Init_PORT.GPIO_Mode = GPIO_Mode_IPU;
#endif
GPIO_Init(BinarySensor_ch8_Port, &Init_PORT);
GPIO_ResetBits(BinarySensor_ch8_Port, BinarySensor_ch8_Pin);
#endif

#if INPUT_NUM_OF_ANALOG_INPUT > 0
DMA_InitStructure.DMA_BufferSize = INPUT_NUM_OF_ANALOG_INPUT;
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)input_analog_ADC_buffer;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
DMA_Init(DMA1_Channel1, &DMA_InitStructure);
DMA_Cmd(DMA1_Channel1 , ENABLE) ;

ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
ADC_InitStructure.ADC_NbrOfChannel = INPUT_NUM_OF_ANALOG_INPUT;
ADC_InitStructure.ADC_ScanConvMode = ENABLE;
ADC_Init(ADC1, &ADC_InitStructure);

#ifdef AnalogInput_ch1_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch1_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch1_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch1_ADC_Channel, 1, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch2_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch2_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch2_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch2_ADC_Channel, 2, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch3_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch3_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch3_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch3_ADC_Channel, 3, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch4_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch4_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch4_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch4_ADC_Channel, 4, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch5_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch5_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch5_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch5_ADC_Channel, 5, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch6_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch6_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch6_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch6_ADC_Channel, 6, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch7_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch7_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch7_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch7_ADC_Channel, 7, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch8_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch8_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch8_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch8_ADC_Channel, 8, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch9_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch9_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch9_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch9_ADC_Channel, 9, ADC_SampleTime_7Cycles5);
#endif

#ifdef AnalogInput_ch10_Pin
Init_PORT.GPIO_Pin = AnalogInput_ch10_Pin;
Init_PORT.GPIO_Mode = GPIO_Mode_AIN;
GPIO_Init(AnalogInput_ch10_Port, &Init_PORT);
ADC_RegularChannelConfig(ADC1, AnalogInput_ch10_ADC_Channel, 10, ADC_SampleTime_7Cycles5);
#endif

ADC_Cmd(ADC1 , ENABLE ) ;
ADC_DMACmd(ADC1 , ENABLE ) ;

ADC_ResetCalibration(ADC1);
 
while(ADC_GetResetCalibrationStatus(ADC1));
ADC_StartCalibration(ADC1);
 
while(ADC_GetCalibrationStatus(ADC1));
ADC_SoftwareStartConvCmd ( ADC1 , ENABLE ) ;
#endif