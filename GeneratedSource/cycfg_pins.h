/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define KIT_BTN1_PORT GPIO_PRT0
#define KIT_BTN1_PIN 4U
#define KIT_BTN1_NUM 4U
#define KIT_BTN1_DRIVEMODE CY_GPIO_DM_PULLUP
#define KIT_BTN1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_0_pin_4_HSIOM
	#define ioss_0_port_0_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define KIT_BTN1_HSIOM ioss_0_port_0_pin_4_HSIOM
#define KIT_BTN1_IRQ ioss_interrupts_gpio_0_IRQn
#define KIT_UART_RX_PORT GPIO_PRT5
#define KIT_UART_RX_PIN 0U
#define KIT_UART_RX_NUM 0U
#define KIT_UART_RX_DRIVEMODE CY_GPIO_DM_HIGHZ
#define KIT_UART_RX_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_0_HSIOM
	#define ioss_0_port_5_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define KIT_UART_RX_HSIOM ioss_0_port_5_pin_0_HSIOM
#define KIT_UART_RX_IRQ ioss_interrupts_gpio_5_IRQn
#define KIT_UART_TX_PORT GPIO_PRT5
#define KIT_UART_TX_PIN 1U
#define KIT_UART_TX_NUM 1U
#define KIT_UART_TX_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define KIT_UART_TX_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_1_HSIOM
	#define ioss_0_port_5_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define KIT_UART_TX_HSIOM ioss_0_port_5_pin_1_HSIOM
#define KIT_UART_TX_IRQ ioss_interrupts_gpio_5_IRQn
#define KIT_RGB_R_PORT GPIO_PRT6
#define KIT_RGB_R_PIN 3U
#define KIT_RGB_R_NUM 3U
#define KIT_RGB_R_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define KIT_RGB_R_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_3_HSIOM
	#define ioss_0_port_6_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define KIT_RGB_R_HSIOM ioss_0_port_6_pin_3_HSIOM
#define KIT_RGB_R_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_4_PORT GPIO_PRT6
#define ioss_0_port_6_pin_4_PIN 4U
#define ioss_0_port_6_pin_4_NUM 4U
#define ioss_0_port_6_pin_4_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define ioss_0_port_6_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_4_HSIOM
	#define ioss_0_port_6_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_4_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_5_PORT GPIO_PRT6
#define ioss_0_port_6_pin_5_PIN 5U
#define ioss_0_port_6_pin_5_NUM 5U
#define ioss_0_port_6_pin_5_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define ioss_0_port_6_pin_5_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_5_HSIOM
	#define ioss_0_port_6_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_5_IRQ ioss_interrupts_gpio_6_IRQn
#define SWDIO_PORT GPIO_PRT6
#define SWDIO_PIN 6U
#define SWDIO_NUM 6U
#define SWDIO_DRIVEMODE CY_GPIO_DM_PULLUP
#define SWDIO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
	#define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define SWDIO_HSIOM ioss_0_port_6_pin_6_HSIOM
#define SWDIO_IRQ ioss_interrupts_gpio_6_IRQn
#define SWCLK_PORT GPIO_PRT6
#define SWCLK_PIN 7U
#define SWCLK_NUM 7U
#define SWCLK_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define SWCLK_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
	#define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define SWCLK_HSIOM ioss_0_port_6_pin_7_HSIOM
#define SWCLK_IRQ ioss_interrupts_gpio_6_IRQn
#define KIT_RGB_G_PORT GPIO_PRT7
#define KIT_RGB_G_PIN 1U
#define KIT_RGB_G_NUM 1U
#define KIT_RGB_G_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define KIT_RGB_G_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_1_HSIOM
	#define ioss_0_port_7_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define KIT_RGB_G_HSIOM ioss_0_port_7_pin_1_HSIOM
#define KIT_RGB_G_IRQ ioss_interrupts_gpio_7_IRQn

extern const cy_stc_gpio_pin_config_t KIT_BTN1_config;
extern const cy_stc_gpio_pin_config_t KIT_UART_RX_config;
extern const cy_stc_gpio_pin_config_t KIT_UART_TX_config;
extern const cy_stc_gpio_pin_config_t KIT_RGB_R_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_5_config;
extern const cy_stc_gpio_pin_config_t SWDIO_config;
extern const cy_stc_gpio_pin_config_t SWCLK_config;
extern const cy_stc_gpio_pin_config_t KIT_RGB_G_config;

void init_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
