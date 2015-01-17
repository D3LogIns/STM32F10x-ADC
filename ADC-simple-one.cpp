#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void adc_tune()
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

 ADC_InitTypeDef ADC_InitStructure;
 ADC_StructInit(&ADC_InitStructure);
 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //  одиночный, независимый
 ADC_InitStructure.ADC_ScanConvMode = DISABLE; // just measuring | измерить один канал
 ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 
 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // without external trigger | без внешнего триггера
 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //how it write the bits | выравнивание битов. прижатие вправо
 ADC_InitStructure.ADC_NbrOfChannel = 2; //number of the chanels | количество каналов 
 ADC_Init(ADC1, &ADC_InitStructure);
 
 ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_1Cycles5);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_7Cycles5);
 ADC_Cmd(ADC1, ENABLE);
 
 ADC_ResetCalibration(ADC1);
 while (ADC_GetResetCalibrationStatus(ADC1));
 ADC_StartCalibration(ADC1);
 while (ADC_GetCalibrationStatus(ADC1));
}

void main()
{
 adc_tune();
 int* i = new int(); 
 int* j = new int(); // this one is for the debugging. That's why you can delete it.
 while(1){
   ADC_SoftwareStartConvCmd(ADC1, ENABLE);
   while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
   *i = ADC_GetConversionValue(ADC1); // returns the ADC value | выводит значение регистра 
   *j = ADC_GetConversionValue(ADC1);
 }
}