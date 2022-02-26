#include <xparameters.h>
#include <xgpio.h>
#include <xstatus.h>
#include <xil_printf.h>

/* Definitions */
#define GPIO_DEVICE_ID XPAR_LED_DEVICE_ID   // GPIO device that LEDs are connected to
#define WAIT_VAL 10000000					// wait value used for clock divider

int delay(void);

int main() {
    int count;				// count the number of iterations in while-loop
    int count_masked;		// bit counter for LEDs
    XGpio leds;				// GPIO output of led port
    int status;				// detects whether the GPIO device successfully initialized
    
    status = XGpio_Initialize(&leds,GPIO_DEVICE_ID);
    XGpio_SetDataDirection(&leds,1,0x00);		// data direction input:1 output:0
    if(status != XST_SUCCESS) {
        xil_printf("Initialized failed");
    }
    count = 0;		// define count before loop
    while(1) {		// loop iterates until terminated by user
        count_masked = count & 0xF;		// bitwise count with logical AND 15 to count 4-bits
        XGpio_DiscreteWrite(&leds,1,count_masked);		// give values (bitwise count) to outputs (LEDs)
        xil_printf("Value of LEDs = 0x%x\n\r",count_masked);	// console output
        delay();		// delay by certain amount of clock cycles
        count++;		// increment count
    }
    return(0);
}

int delay(void) {
    volatile int delay_count = 0;
    while(delay_count < WAIT_VAL)
        delay_count++;		// loop untilWAIT_VAL is reached
    return(0);
}
