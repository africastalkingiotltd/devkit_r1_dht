/*
 * dht.h
 *
 *  Created on: 27 Feb 2020
 *      Author: kennedyotieno
 */

#ifndef DHT_H_
#define DHT_H_

#include "gpio.h"

/**
 * @brief Set a specified pin peripheral-number pair as input
 * It takes the pin peripheral to set as input example GPIOA,GPIOB,GPIOC
 * It takes the pin number to set as input example PB12
 */
void setpinInput();

/**
 * @brief Set a specified pin peripheral-numbeer pair as output
 * It takes the pin peripheral to set as output example GPIOA,GPIOB,GPIOC
 * It takes the pin number to set as input example PB12
 */
void setpinOutput();

/**
 * @brief Initialize the DHT Pin by pulling the pin low then toggling the state
 * 
 */
void dhtInitialize(void);


void dhtAwaitResponse(void);
uint8_t dhtGetData(void);

#endif /* DHT_H_ */
