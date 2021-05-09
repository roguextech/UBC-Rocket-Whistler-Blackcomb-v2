/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_uart.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Definition of peripheral ID */
#define UART0_PERIPHERAL UART0
/* Definition of the clock source frequency */
#define UART0_CLOCK_SOURCE CLOCK_GetFreq(UART0_CLK_SRC)
/* Definition of peripheral ID */
#define UART1_PERIPHERAL UART1
/* Definition of the clock source frequency */
#define UART1_CLOCK_SOURCE CLOCK_GetFreq(UART1_CLK_SRC)
/* Definition of peripheral ID */
#define UART2_PERIPHERAL UART2
/* Definition of the clock source frequency */
#define UART2_CLOCK_SOURCE CLOCK_GetFreq(UART2_CLK_SRC)

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const uart_config_t UART0_config;
extern const uart_config_t UART1_config;
extern const uart_config_t UART2_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
