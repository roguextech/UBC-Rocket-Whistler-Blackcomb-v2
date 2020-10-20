
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "stdio_controller.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "console.h"
#include "hal_uart.h"
#include "board.h"

#include <stdio.h>
#include <pthread.h>
#include <time.h>

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* TODO: update for all sensors */
static hal_uart_handle_t *uart_handles[1];

/*******************************************************************************
 * Declarations
 ******************************************************************************/

static void inputLoop(void * pv);
static void generateImuLoop(void * pv);

/*******************************************************************************
 * Implementations
 ******************************************************************************/

/**
 * Loop for interacting with ground station interface
 */
static void inputLoop(void *pv){
    int t = 5;
    printf("Print something, quick!");
    vTaskDelay(pdMS_TO_TICKS(5000));
    if(scanf("%d", &t)){
        printf("read");
    }
    for(;;){
        console_print("stdio polling...%d\n", t);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void generateImuLoop(void *pv){

}

void stdioInit(){
    /* Thread safe output */
    console_init();

    /* For generation of normal threads if needed for testing */
    // pthread_t ioThread;
    // pthread_create( &ioThread, NULL, inputLoop, NULL);

    if (xTaskCreate( 
			inputLoop, 
			"stdio controller",
			200/sizeof(StackType_t),
			(void*)NULL,
			tskIDLE_PRIORITY+2,
			(TaskHandle_t*)NULL
			) != pdPASS) {
    	for(;;);
    }

    if (xTaskCreate( 
			generateImuLoop, 
			"imu generator controller",
			200/sizeof(StackType_t),
			(void*)NULL,
			tskIDLE_PRIORITY+2,
			(TaskHandle_t*)NULL
			) != pdPASS) {
    	for(;;);
    }
}

void stdioAssignUart(hal_uart_handle_t *handle){
    if(handle->base == IMU_UART){
		uart_handles[0] = handle;
	}
}