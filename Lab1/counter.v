`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/27/2022 01:23:46 PM
// Design Name: 
// Module Name: btnCounter
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module btnCounter(LEDS, CLK, RST, BTN);
    output [3:0] LEDS;
    input CLK, RST;
    input [1:0] BTN;
    
    wire newCLK;                // slowed clock
    reg [3:0] count;            // count from 0 to 15 and displayed with LEDs
    clock_divider slowClock(newCLK, CLK, RST);    // call for divider module    
    
    always @ (posedge newCLK)   // execute every second
        begin
            if(RST) begin           // set count to 0 if RST is pressed
                count <= 0;
            end
            else begin
                if(BTN[0])          // count up if BTN0 is pressed
                    count <= count + 1;
                if(BTN[1])          // count down if BTN1 is pressed
                    count <= count - 1;
            end
        end
        
        assign LEDS[3:0] = count[3:0];  // continuous assign count value to LEDS
endmodule