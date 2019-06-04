/*
 * i2cmaster.h
 *
 *  Created on: 31 de mai de 2019
 *      Author: msam
 */

#ifndef SOURCE_I2CMASTER_H_
#define SOURCE_I2CMASTER_H_

#include "cy_device_headers.h"
#include "cycfg.h"

/* Assign pins for I2C on SCB6: P6[0] and P6[1] */
#define I2C_PORT      (GPIO_PRT6)
#define I2C_SCL_NUM   (P6_4_NUM)
#define I2C_SDA_NUM   (P6_5_NUM)

#define I2C_SUCCESS 		(0UL)
#define I2C_FAILURE 		(1UL)

/* Allocate buffers for I2C operation */
#define BUFFER_SIZE (128UL)

/* I2C master desired data rate in Hz */
#define I2C_DESIRED_DATA_RATE_HZ    (100000U)
#define I2C_CLK_FREQ_HZ       (1562500U)

#define I2C_INTERRUPT
/* Populate configuration structure (code specific for CM4) */
#ifdef I2C_INTERRUPT
/* Assign I2C interrupt number and priority */
#define I2C_INTR_NUM        scb_6_interrupt_IRQn
#define I2C_INTR_PRIORITY   (2UL)

#endif // I2C_INTERRUPT

/* Command valid status */
#define TRANSFER_ERROR        (0xFFUL)
#define READ_ERROR            (TRANSFER_ERROR)

#define I2C_TIMEOUT           (200UL)
#define TRANSFER_CMPLT        (0x00UL)
#define READ_CMPLT            (TRANSFER_CMPLT)

/* Combine master error statuses in single mask  */
#define MASTER_ERROR_MASK  (CY_SCB_I2C_MASTER_DATA_NAK | CY_SCB_I2C_MASTER_ADDR_NAK    | \
                            CY_SCB_I2C_MASTER_ARB_LOST | CY_SCB_I2C_MASTER_ABORT_START | \
                            CY_SCB_I2C_MASTER_BUS_ERR)

/* Command valid status */
#define TRANSFER_ERROR        (0xFFUL)
#define READ_ERROR            (TRANSFER_ERROR)

#define I2C_TIMEOUT           (200UL)
#define TRANSFER_CMPLT        (0x00UL)
#define READ_CMPLT            (TRANSFER_CMPLT)

/* Combine master error statuses in single mask  */
#define MASTER_ERROR_MASK  (CY_SCB_I2C_MASTER_DATA_NAK | CY_SCB_I2C_MASTER_ADDR_NAK    | \
                            CY_SCB_I2C_MASTER_ARB_LOST | CY_SCB_I2C_MASTER_ABORT_START | \
                            CY_SCB_I2C_MASTER_BUS_ERR)


uint32_t initMaster(void);
uint8_t ReadStatusPacket(uint8_t rxBuffer[],uint8_t rxsize);
uint8_t WritePacket(uint8_t* buffer, uint32_t bufferSize);

/* Allocate context for I2C operation */
static cy_stc_scb_i2c_context_t i2cContext;
/* Structure for master transfer configuration */
static cy_stc_scb_i2c_master_xfer_config_t masterTransferCfg =
{
    .slaveAddress = 0x39,
    .buffer       = NULL,
    .bufferSize   = 0U,
    .xferPending  = false
};

static const cy_stc_scb_i2c_config_t i2cConfig =
{
	.i2cMode = CY_SCB_I2C_MASTER,
	.useRxFifo = true,
	.useTxFifo = true,
	.slaveAddress = 0U,
	.slaveAddressMask = 0U,
	.acceptAddrInFifo = false,
	.ackGeneralAddr = false,
	.enableWakeFromSleep = false,
	.enableDigitalFilter = false,
	.lowPhaseDutyCycle = 15,
	.highPhaseDutyCycle = 9,
};


#endif /* SOURCE_I2CMASTER_H_ */
