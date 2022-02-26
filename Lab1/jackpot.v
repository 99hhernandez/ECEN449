`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/04/2022 05:58:43 PM
// Design Name: 
// Module Name: jackpot
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


module jackpot(LEDS, SWITCHES, CLK, RST);
    output [3:0] LEDS;
    input CLK, RST;
    input [3:0] SWITCHES;
    
    wire newCLK;                        // slowed clock
    reg [3:0] lights = 4'b1000;         // initial state of the lights will be left-most on
    
    clock_divider slowCLK(newCLK, CLK, RST);    // call for clock divider
    
    always@(posedge newCLK) begin       // execute at every cycle of slowed clock
        if(RST) begin                   // reset condition
            lights <= 4'b1000;
        end
        else begin                      // change the state of the LEDs based on its current state                
            if(lights == 4'b1000 & ~SWITCHES[3]) begin
                lights <= 4'b0100;
            end
            else if(lights == 4'b0100 & ~SWITCHES[2]) begin
                lights <= 4'b0010;
            end
            else if(lights == 4'b0010 & ~SWITCHES[1]) begin
                lights <= 4'b0001;
            end
            else if(lights == 4'b0001 & ~SWITCHES[0]) begin
                lights <= 4'b1000;
            end
            else begin                  // all lights turn on when switch and light correspond
                lights <= 4'b1111;
            end
        end
    end
    assign LEDS[3:0] = lights[3:0];     // continuous assign LEDs to lights
endmodule
