/*
 * dht.c
 *
 *  Created on: 27 Feb 2020
 *      Author: kennedyotieno
 */

#include "dht.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include <stdint.h>
#include "main.h"

uint8_t relativeHumidityByte1, relativeHumidityByte2, temperatureByte1, temperatureByte2;
uint16_t sum, relativeHumidity, temperature;
int lowTemperatureMark, highTemepratureMark, lowRelativeHumidityMark, highRelativeHumidityMark;
char temperatureArray[2], temperatureBucket, relativeHumidityArray[2], relativeHumidityBucket;
uint8_t flag = 0;

GPIO_InitTypeDef GPIO_InitStruct;

void setpinInput()
{
    GPIO_InitStruct.Pin  = DHT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT_PERIPHERAL, &GPIO_InitStruct);
}

void setpinOutput()
{
    GPIO_InitStruct.Pin   = DHT_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT_PERIPHERAL, &GPIO_InitStruct);
}

void dhtInitialize(void)
{
    setpinOutput();
    HAL_GPIO_WritePin(DHT_PERIPHERAL, DHT_PIN, RESET);
    HAL_Delay(18);
    setpinInput();
}

void dhtAwaitResponse(void)
{
    delayMicroseconds(40);
    if (!(HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN)))
    {
        delayMicroseconds(80);
        if(HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN)) flag = 1;
    }
    while(HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN));   
}

uint8_t dhtGetData(void)
{
    int j;
    for (int i = 0; i < 8; i++)
    {
        while(!(HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN)));
        delayMicroseconds(40);
        if (HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN) == 0)
        {
            j &= ~(1<<(7 - i));
        }
        else
        {
            j |= (1<<(7 - i));
        }
        while(HAL_GPIO_ReadPin(DHT_PERIPHERAL, DHT_PIN));
    }
    return j;
}