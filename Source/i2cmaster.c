/*
 * i2cmaster.c
 *
 *  Created on: 31 de mai de 2019
 *      Author: msam
 *
* \file i2cmaster.c
* \version 1.0
*
* \brief
*
* * Related Document: CE220818_PSoC6_I2CMaster.pdf
*
*******************************************************************************
* Copyright (2018-19), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death (“High Risk Product”). By
* including Cypress’s product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

#include "cy_device_headers.h"
#include "cy_syslib.h"
#include "cy_sysint.h"
#include "cy_scb_i2c.h"

//#include "cy_syspm.h"
//#include "cy_scb_uart.h"

#include "cycfg.h"

#include "i2cmaster.h"


#ifdef I2C_INTERRUPT


void I2C_Isr(void)
{
    Cy_SCB_I2C_Interrupt(SCB6, &i2cContext);
}

#endif

/*******************************************************************************
* Function Name: initMaster
********************************************************************************
*
* This function initiates and enables Master SCB
*
* \param None
*
* \return
* Status of initialization
*
*******************************************************************************/
uint32_t initMaster(void)
{
	cy_en_scb_i2c_status_t initStatus;
	cy_en_sysint_status_t sysStatus;
	cy_stc_sysint_t mI2C_SCB_IRQ_cfg =
	{
		.intrSrc      = I2C_INTR_NUM,
		.intrPriority = I2C_INTR_PRIORITY,

	};
    Cy_SCB_I2C_Disable(SCB6, &i2cContext);

	/* Initialize and enable the I2C in master mode. */
	initStatus = Cy_SCB_I2C_Init(SCB6, &i2cConfig, &i2cContext);
	if(initStatus != CY_SCB_I2C_SUCCESS)
	{
		return I2C_FAILURE;
	}

	/* Hook interrupt service routine. */
	sysStatus = Cy_SysInt_Init(&mI2C_SCB_IRQ_cfg, I2C_Isr);
	if(sysStatus != CY_SYSINT_SUCCESS)
	{
		return I2C_FAILURE;
	}

	/* Enable interrupt in NVIC. */
	NVIC_EnableIRQ((IRQn_Type) mI2C_SCB_IRQ_cfg.intrSrc);

	/* Enable I2C master hardware. */
	Cy_SCB_I2C_Enable(SCB6);
	return I2C_SUCCESS;
}

/*******************************************************************************
* Function Name: WritePacket
****************************************************************************//**
*
* Buffer is assigned with data to be sent to slave.
* high level APIs are used to control I2C SCB to send data.
* Errors are handled depend on the return value from the appropriate function.
*
* \param buffer
*
* \param bufferSize
*
* \return
* returns the status after command is written to slave.
* TRANSFER_ERROR is returned if any error occurs.
* TRANSFER_CMPLT is returned if write is successful.
* \ref uint32_t
*
*******************************************************************************/
uint8_t WritePacket(uint8_t* buffer, uint32_t bufferSize)
{
    uint8_t status = TRANSFER_ERROR;
    cy_en_scb_i2c_status_t  errorStatus;
    uint32_t masterStatus;
    /* Timeout 1 sec (one unit is us) */
    uint32_t timeout = 1000000UL;

    /* Setup transfer specific parameters. */
    masterTransferCfg.buffer     = buffer;
    masterTransferCfg.bufferSize = bufferSize;
    masterTransferCfg.xferPending = false;

    /* Initiate write transaction. */
    errorStatus = Cy_SCB_I2C_MasterWrite(SCB6, &masterTransferCfg, &i2cContext);
    if(errorStatus == CY_SCB_I2C_SUCCESS)
    {
        /* Wait until master complete read transfer or time out has occurred */
        do
        {
            masterStatus  = Cy_SCB_I2C_MasterGetStatus(SCB6, &i2cContext);
            Cy_SysLib_DelayUs(CY_SCB_WAIT_1_UNIT);
            timeout--;
        } while ((0UL != (masterStatus & CY_SCB_I2C_MASTER_BUSY)) && (timeout > 0));

        if (timeout <= 0)
        {
            /* Timeout recovery */
            Cy_SCB_I2C_Disable(SCB6, &i2cContext);
            Cy_SCB_I2C_Enable (SCB6);
        }
        else
        {
            if ((0u == (MASTER_ERROR_MASK & masterStatus)) &&
                (bufferSize == Cy_SCB_I2C_MasterGetTransferCount(SCB6, &i2cContext)))
            {
                status = TRANSFER_CMPLT;
            }
        }
    }

    return (status);
}

/*******************************************************************************
* Function Name: ReadStatusPacket
****************************************************************************//**
*
*  Master initiates to read status packet from the slave.
*  The status of the transfer is returned.
*
* \return
* Checks the status packet and returns the status.
* ref uint32_t
*
* \note
* * If the status packet read is correct function returns TRANSFER_CMPLT and
*   if status packet is incorrect function returns TRANSFER_ERROR.
*
*******************************************************************************/
uint8_t ReadStatusPacket(uint8_t rxBuffer[],uint8_t rxsize)
{
    uint8_t status = TRANSFER_ERROR;
    cy_en_scb_i2c_status_t errorStatus;
    uint32_t masterStatus;
    /* Timeout 1 sec (one unit is us) */
    uint32_t timeout = 1000000UL;
 //   uint8_t  rxBuffer[RX_PACKET_SIZE];

    /* Setup transfer specific parameters */
    masterTransferCfg.buffer     = rxBuffer;
    masterTransferCfg.bufferSize = rxsize;
    masterTransferCfg.xferPending = false;

    /* Initiate read transaction */
    errorStatus = Cy_SCB_I2C_MasterRead(SCB6, &masterTransferCfg, &i2cContext);
    if(errorStatus == CY_SCB_I2C_SUCCESS)
    {
        /* Wait until master complete read transfer or time out has occured */
        do
        {
            masterStatus  = Cy_SCB_I2C_MasterGetStatus(SCB6, &i2cContext);
            Cy_SysLib_DelayUs(CY_SCB_WAIT_1_UNIT);
            timeout--;

        } while ((0UL != (masterStatus & CY_SCB_I2C_MASTER_BUSY)) && (timeout > 0));

       if (timeout <= 0)
        {
            /* Timeout recovery */
            Cy_SCB_I2C_Disable(SCB6, &i2cContext);
            Cy_SCB_I2C_Enable (SCB6);
        }
        else
        {
            /* Check transfer status */
            if (0u == (MASTER_ERROR_MASK & masterStatus))
            {

                    status = TRANSFER_CMPLT;
            }
        }
    }
    return (status);
}
