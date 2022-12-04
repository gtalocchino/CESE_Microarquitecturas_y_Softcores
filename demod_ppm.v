/*
 * demod_ppm.v
 *
 *  Created on: Nov 29, 2022
 *      Author: gianfranco
 */


 module demod_ppm #(
    parameter N = 4
 )(
    input i_clk,
    input i_rst,
    input i_ppm,
    input i_start,
    output [N-1:0] o_data,
    output o_ready
 );

    localparam SAWTOOTH_MAX = 2**(N - 1) - 1;
    localparam SAWTOOTH_MIN = -(2**(N - 1));

    reg signed [N-1:0] sawtooth;
    reg signed [N-1:0] data;
    reg is_running;
    reg is_equal;
    reg ppm;


    always @(posedge i_clk) begin
        if (i_rst) begin
            is_running <= 0;          
        end else if (i_start) begin
            is_running <= 1;
        end else if (sawtooth == SAWTOOTH_MAX) begin
            is_running <= 0;
        end
    end

    always @(posedge i_clk) begin
        if (i_rst) begin
            ppm <= 0;
        end else if (is_running) begin
            ppm <= i_ppm;
        end
    end

    always @(posedge i_clk) begin
        if (i_rst) begin
            sawtooth <= SAWTOOTH_MAX;
        end else if (is_running) begin
            sawtooth <= sawtooth + 1;
        end
    end

    always @(posedge i_clk) begin
        if (i_rst) begin
            data <= 0;
        end else if (is_running) begin
            if (ppm) begin
                data <= sawtooth;
            end
        end
    end
    
    assign o_data = data;
    assign o_ready =  ~is_running;

 endmodule
 