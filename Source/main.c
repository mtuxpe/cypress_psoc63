/***************************************************************************//**
* \file main.c
* \version 1.0
*
* \brief
*
* File Name: main.c
*
* Version: 1.0
*
* Description: This example project demonstrates the basic operation of the I2C
* master resource using low level APIs. The I2C master SCB sends the
* command packets to the I2C slave.
* \copyright
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
*******************************************************************************/

#include "cy_device_headers.h"
#include "cycfg.h"
#include "debug.h"
#include "i2cmaster.h"
#include "cy_sysint.h"
#include "tsl2561.h"


#if 0
uint8_t veml_wr_word( uint8_t reg, uint16_t val)
{
	uint8_t err = TRANSFER_ERROR;
	uint8_t retry = 3;
	uint8_t data[3];
	data[0] = reg;
	data[1] = (uint8_t)(val & 0xFF);
	data[2] = (uint8_t)((val & 0xFF00) >> 8);

	while (retry--)
	{
		err = WritePacket(data, 3);
		if (TRANSFER_CMPLT == err)
			break;
	}
	return err;
}

void ShowError(void)
{
    Cy_GPIO_Write(KIT_RGB_R_PORT,KIT_RGB_R_PIN, LED_ON);
    /* Halt CPU */
    CY_ASSERT(0u != 0u);
}
#endif

/*******************************************************************************
* Function Name: powerCtl
****************************************************************************//**
*
* Enable/disable power control register
* high level APIs are used to control I2C SCB to send data.
* Errors are handled depend on the return value from the appropriate function.
*
* \param ctl
*
*
* \return
* returns the status after command is written to slave.
* TRANSFER_ERROR is returned if any error occurs.
* TRANSFER_CMPLT is returned if write is successful.
* \ref uint32_t
*
*******************************************************************************/

uint8_t powerCtl (uint8_t ctl )
{
	uint8_t buffer [2];
    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] =  ctl;

    return WritePacket(buffer, 2);

}

uint8_t setIntegTime (uint8_t it)
{
	uint8_t buffer [2];
	uint8_t status = TRANSFER_ERROR;
    uint8_t gain = 0;

    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWERON;

    // power on
    status = WritePacket(buffer, 2);
    if (TRANSFER_CMPLT != status)
    	return(status);

    buffer[0] = COMMAND_BIT | REGISTER_TIMING;
    buffer[1] = INTEGRATIONTIME_402MS|gain;

    status = WritePacket(buffer, 2);
    if (TRANSFER_CMPLT != status)
       	return(status);

    // power off
    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWEROFF;

    status = WritePacket(buffer, 2);
    return status;

}

uint8_t setGain (uint8_t gain)
{
	uint8_t buffer [2];
	uint8_t status = TRANSFER_ERROR;

    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWERON;

    // power on
    status = WritePacket(buffer, 2);
    if (TRANSFER_CMPLT != status)
    	return(status);

    buffer[0] = COMMAND_BIT | REGISTER_TIMING;
    buffer[1] = INTEGRATIONTIME_402MS|gain;

    status = WritePacket(buffer, 2);
    if (TRANSFER_CMPLT != status)
       	return(status);

    // power off
    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWEROFF;

    status = WritePacket(buffer, 2);
    return status;

}

uint8_t getData (uint8_t lux[])
{
	uint8_t buffer [2];
	uint8_t status = TRANSFER_ERROR;

    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWERON;

    // power on
    status = WritePacket(buffer, 2);
    if (TRANSFER_CMPLT != status)
    	return(status);

    Cy_SysLib_Delay(500);

    buffer[0] = COMMAND_BIT | WORD_BIT | REGISTER_ADC0_LO;
    status = WritePacket(buffer, 1);
    if (TRANSFER_CMPLT != status)
       	return(status);

    status = ReadStatusPacket(lux,2 );
    if (TRANSFER_CMPLT != status)
    	return(status);

    buffer[0] = COMMAND_BIT | WORD_BIT | REGISTER_ADC1_LO;
    status = WritePacket(buffer, 1);
    if (TRANSFER_CMPLT != status)
       	return(status);

    status = ReadStatusPacket(lux+2,2 );
    if (TRANSFER_CMPLT != status)
    	return(status);

    // power off
    buffer[0] = COMMAND_BIT | REGISTER_CONTROL;
    buffer[1] = CONTROL_POWEROFF;

    status = WritePacket(buffer, 2);
    return status;
}

int main(void)
{

	uint8_t status;
    /* Set up the device based on configurator selections */
    init_cycfg_all();

    UART_DEBUG_START();
    DEBUG_PRINTF("ProtoKitApp Example \r\n");

    __enable_irq();
 
    status = initMaster();
    if(status == I2C_FAILURE)
 	{
    	DEBUG_PRINTF("Error init i2c master\r\n");
    	/* Enable interrupt in NVIC. */
    	cy_stc_sysint_t mI2C_SCB_IRQ_cfg =
    	{
    		.intrSrc      = I2C_INTR_NUM,
    		.intrPriority = I2C_INTR_PRIORITY,

    	};
    	NVIC_DisableIRQ((IRQn_Type) mI2C_SCB_IRQ_cfg.intrSrc);
    	ShowError();
 	}

#if 0
    uint16_t veml_conf = VEML6075_CONF_DEFAULT | VEML6075_CONF_SD;
    status = veml_wr_word(VEML6075_CONF_REG, veml_conf);
    if (TRANSFER_CMPLT != status)
    	ShowError();
    veml_conf = VEML6075_CONF_DEFAULT;
    status = veml_wr_word(VEML6075_CONF_REG, veml_conf);
    if (TRANSFER_CMPLT != status)
     	ShowError();
#endif

    uint8_t buffer[2];
	uint8_t lux[4];

    buffer[0] = REGISTER_ID;
    if (TRANSFER_CMPLT == WritePacket(buffer, 1))
    {

      	lux[0] = 0;
      	status = ReadStatusPacket(lux,1 );

      	if ( status == TRANSFER_CMPLT )
      		DEBUG_PRINTF("Leu id %x\r\n",lux[0]);
      	else
      	{
      		DEBUG_PRINTF("Err ID\r\n");
      		ShowError();
      	}

    }
    else
    {
  		DEBUG_PRINTF("Err not initialized\r\n");
  		ShowError();
    }

    status = setIntegTime(INTEGRATIONTIME_402MS);
    if (TRANSFER_CMPLT != status)
    {
    	DEBUG_PRINTF("Err Intg time\r\n");
    	ShowError();
    }

    status = setGain(0);
    if (TRANSFER_CMPLT != status)
    {
    	DEBUG_PRINTF("Err set gain\r\n");
    	ShowError();
    }

    status = getData(lux);
/*
    if (TRANSFER_CMPLT == status)
    {

     	float ch0 = (lux[1] <<8) + lux[0];
     	float ch1 = (lux[3] <<8) + lux[2];

     			// Output data to screen
     	DEBUG_PRINTF("Full Spectrum(IR + Visible) : %.2f lux \r\n", ch0);
     	DEBUG_PRINTF("Infrared Value : %.2f lux \r\n", ch1);
     	DEBUG_PRINTF("Visible Value : %.2f lux \r\n", (ch0 - ch1));

    }
*/
    for(;;)
    {
    	Cy_GPIO_Inv(KIT_RGB_G_PORT, KIT_RGB_G_PIN); /* toggle the pin */
    	status = getData(lux);
    	if (TRANSFER_CMPLT == status) {

    		float ch0 = (lux[1] <<8) + lux[0];
    	    float ch1 = (lux[3] <<8) + lux[2];

    	     			// Output data to screen
    	    DEBUG_PRINTF("Full Spectrum(IR + Visible) : %.2f lux \r\n", ch0);
    	    DEBUG_PRINTF("Infrared Value : %.2f lux \r\n", ch1);
    	    DEBUG_PRINTF("Visible Value : %.2f lux \r\n", (ch0 - ch1));

    	}

        Cy_GPIO_Inv(KIT_RGB_G_PORT, KIT_RGB_G_PIN); /* toggle the pin */
        Cy_SysLib_Delay(500/*msec*/);

    }
}
