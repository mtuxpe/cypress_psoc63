/*
 * tsl2561.h
 *
 *  Created on: 30 de mai de 2019
 *      Author: msam
 */

#ifndef SOURCE_TSL2561_H_
#define SOURCE_TSL2561_H_

#define TSL2561_REGISTER_ID	0x0A // TSL2561 identification setting
#define COMMAND_BIT       (0x80)    // Must be 1
#define CLEAR_BIT         (0x40)    // Clears any pending interrupt (write 1 to clear)
#define WORD_BIT          (0x20)    // 1 = read/write word (rather than byte)
#define BLOCK_BIT         (0x10)    // 1 = using block read/write

#define CONTROL_POWERON   (0x03)
#define CONTROL_POWEROFF  (0x00)

#define REGISTER_CONTROL    (0x00)      // Access control register
#define REGISTER_TIMING     (0x01)      // Access timing register
#define REGISTER_ID         (0x0A)      // Access product ID register
#define REGISTER_ADC0_LO    (0x0C)      // LSB of sensor's two-byte ADC value
#define REGISTER_ADC0_HI    (0x0D)      // MSB of sensor's two-byte ADC value
#define REGISTER_ADC1_LO    (0x0E)      // LSB of sensor's two-byte ADC value
#define REGISTER_ADC1_HI    (0x0F)      // LSB of sensor's two-byte ADC value
#define GAIN_LOW_INT_10     (0x01)      // Gain to low, integration timing to 101ms
#define GAIN_LOW_INT_13     (0x00)      // Gain to low, integration timing to 13.7ms
#define GAIN_HI_INT_10      (0x11)      // Gain to low, integration timing to 101ms
#define GAIN_HI_INT_13      (0x10)      // Gain to low, integration timing to 13.7ms

#define INTEGRATIONTIME_13MS (0x0) 		// 13.7ms
#define INTEGRATIONTIME_101MS (0x01) 	// 101 ms
#define INTEGRATIONTIME_402MS (0x02) 	// 402ms


#endif /* SOURCE_TSL2561_H_ */
