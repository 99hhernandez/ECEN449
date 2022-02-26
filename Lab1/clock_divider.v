`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/03/2022 09:57:13 PM
// Design Name: 
// Module Name: clock_divider
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

module clock_divider(CLK_out, CLK_in, reset);
    output reg CLK_out;     // output port as reg to drive it with a behavioral statement
    input CLK_in, reset;
    
    // Parameter can be changed at compile time
    parameter n = 31;   // count up to 32-bit number
    reg [n:0] Count;    // n-bit number that will count up
    
    // Trigger with every posedge of ZYBO clock
    always@(posedge CLK_in) begin
        if(reset)                   // reset count to 0 if reset enabled
            begin
                CLK_out <= 1;
                Count <= 0;
            end
//        else if(Count == 125000000) // if ZYBO clock frequency reaches 125Mhz
        else if(Count == 10000000) // uncomment for jackpot module
            begin
                CLK_out <= 1;
                Count <= 0;
            end
        else                    // if clock frequency isn't reached keep CLK_out low
            begin
                CLK_out <= 0;
                Count <= Count + 1;
            end
    end
endmodule