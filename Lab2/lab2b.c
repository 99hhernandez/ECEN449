#include <xparameters.h>
#include <xgpio.h>
#include <xstatus.h>
#include <xil_printf.h>

// Definitions
#define GPIO_DEVICE_ID_LEDS XPAR_LED_DEVICE_ID     // GPIO device that LEDs are connected to
#define GPIO_DEVICE_ID_BTNS XPAR_SWBTNS_DEVICE_ID     // GPIO device ID for buttons and switches
#define WAIT_VAL 10000000
#define boolean _Bool
#define false 0
#define true 1

// Slow system clock from 100MHz to 1MHz
int delay(void);

int main() {
    int count = 0;          	// count number of iterations of loop
    int count_masked = 0xFF;  	// bit counter for LEDs
    XGpio leds;             	// GPIO output of LEDs
    XGpio swbtns;           	// GPIO input of switches and buttons
    int statusOut;          	// verify GPIO output device initialization
    
    statusOut = XGpio_Initialize(&leds,GPIO_DEVICE_ID_LEDS);
    XGpio_SetDataDirection(&leds,1,0x00);           // set data direction to output 
    if(statusOut != XST_SUCCESS) {
        xil_printf("LEDs Initialization failed");
    }
    
    // Track change in buttons and switches
    statusOut = XGpio_Initialize(&swbtns,GPIO_DEVICE_ID_BTNS);
	XGpio_SetDataDirection(&swbtns,1,0x01);           // set data direction to input
	if(statusOut != XST_SUCCESS) {
		xil_printf("Input Initialization failed");
	}
    int swValue = 0;                                // track status of switches
    boolean b0 = false;
    boolean b1 = false;
    boolean b2 = false;
    boolean b3 = false;
    
    while(1) {           // loop iterates until terminated by user
        // only button0 is pressed and overrides other buttons
        boolean btn0 = ((XGpio_DiscreteRead(&swbtns,1) & 0x01) == 0x01)
            && !((XGpio_DiscreteRead(&swbtns,1) & 0x04) == 0x04)
            && !((XGpio_DiscreteRead(&swbtns,1) & 0x08) == 0x08);
        
        // only button1 is pressed
        boolean btn1 = ((XGpio_DiscreteRead(&swbtns,1) & 0x02) == 0x02)
            && !((XGpio_DiscreteRead(&swbtns,1) & 0x04) == 0x04)
            && !((XGpio_DiscreteRead(&swbtns,1) & 0x08) == 0x08);
            
        // button2 is pressed
        boolean btn2 = ((XGpio_DiscreteRead(&swbtns,1) & 0x04) == 0x04);
        
        // button3 us pressed
        boolean btn3 = ((XGpio_DiscreteRead(&swbtns,1) & 0x08) == 0x08);
        
        // turn off LEDs when not being used
        if(!btn2 && btn3)
            XGpio_DiscreteWrite(&leds,1,0x00);
        
        // increment counter and track bit counter when btn0 is pressed
        if(btn0) {
            if(!b0) {
                xil_printf("Button[0] has been pressed.\n");
                b0 = true;
            }
            if(b1) {
                b1 = false;
                xil_printf("Button[1] has been released.\n");
            }
            if(b2) {
                b2 = false;
                xil_printf("Button[2] has been released.\n");
            }
            if(b3) {
                b3 = false;
                xil_printf("Button[3] has been released.\n");
            }
        }
        // decrement counter and track bit counter when btn1 is pressed
        else if(btn1) {
            count--;
            if(!b1) {
                b1 = true;
                xil_printf("Button[1] has been pressed.\n");
            }
            if(b0) {
                b0 = false;
                xil_printf("Button[0] has been released.\n");
            }
            if(b2) {
                b2 = false;
                xil_printf("Button[2] has been released.\n");
            }
            if(b3) {
                b3 = false;
                xil_printf("Button[3] has been released.\n");
            }
            count_masked = count & 0xF;     // update bitwise counter
            xil_printf("Value of LEDs = 0x%x\n\r",count_masked);
            delay();
        }
        // show status of switches
        else if(btn2) {
            if(b1) {
                b1 = false;
                xil_printf("Button[1] has been released.\n");
            }
            if(b0) {
                b0 = false;
                xil_printf("Button[0] has been released.\n");
            }
            if(!b2) {
                b2 = true;
                xil_printf("Button[2] has been pressed.\n");
            }
            if(b3) {
                b3 = false;
                xil_printf("Button[3] has been released.\n");
            }
            
            if((XGpio_DiscreteRead(&swbtns,1) & 0xF0) != swValue) {
                swValue = XGpio_DiscreteRead(&swbtns,1) & 0xF0;
                xil_printf("Switch has been moved. Switch Value: %d\n", swValue >> 4);
            }
            XGpio_DiscreteWrite(&leds,1, swValue >> 4);     // display switch value with LEDs
            // button0 and button2 are pressed
            if((XGpio_DiscreteRead(&swbtns,1) & 0x01) == 0x01) {
                if(!b0) {
                    b0 = true;
                    xil_printf("Button[0] has been pressed.\n");
                }
                count++;
                count_masked = count & 0xf;
                xil_printf("Value of LEDs = 0x%x\n\r",count_masked);
                delay();
            }
            // button1 and button2 are pressed
            else if((XGpio_DiscreteRead(&swbtns,1) & 0x02) == 0x02) {
                if(!b1) {
                    b2 = true;
                    xil_printf("Button[1] has been pressed.\n");
                }
                count--;
                count_masked = count & 0xF;
                xil_printf("Value of LEDs = 0x%x\n\r",count_masked);
                delay();
            }
        }
        // show count on LEDs
        else if(btn3) {
            if(b1) {
                b1 = false;
                xil_printf("Button[1] has been released.\n");
            }
            if(b0) {
                b0 = false;
                xil_printf("Button[0] has been released.\n");
            }
            if(b2) {
                b2 = false;
                xil_printf("Button[2] has been released.\n");
            }
            if(!b3) {
                b3 = true;
                xil_printf("Button[3] has been pressed.\n");
            }
            // button0 and button3 are pressed
            if((XGpio_DiscreteRead(&swbtns,1) & 0x01) == 0x01) {
                count++;
                count_masked = count & 0xF;
                XGpio_DiscreteWrite(&leds,1,count_masked);
                xil_printf("Value of LEDs = 0x%x\n\r",count_masked);
                delay();
            }
            // button1 and button3 are pressed
            else if((XGpio_DiscreteRead(&swbtns,1) & 0x02) == 0x02) {
                if(!b1) {
                    b1 = true;
                    xil_printf("Button[1] has been pressed.\n");
                }
                count--;
                count_masked = count & 0xF;
                XGpio_DiscreteWrite(&leds,1,count_masked);
                xil_printf("Value of LEDs = 0x%x\n\r",count_masked);
                delay();
            }
            // only button3 is pressed
            else {
                XGpio_DiscreteWrite(&leds,1,count_masked);
            }
        }
    }
}


// Slow system clock from 100MHz to 1MHz
int delay(void) {
    volatile int delay_count = 0;
    while(delay_count < WAIT_VAL) {
        delay_count++;
    }
    return(0);
}
