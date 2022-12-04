/*
 * mod_ppm.v
 *
 *  Created on: Nov 29, 2022
 *      Author: gianfranco
 */


 module mod_ppm #(
    parameter N = 4
 )(
    input i_clk,
    input i_rst,
    input i_start,
    input [N-1:0] i_data,
    output o_ppm,
    output o_busy
 );
    localparam SAWTOOTH_MAX = 2**(N - 1) - 1;
    localparam SAWTOOTH_MIN = -(2**(N - 1));

    reg signed [N-1:0] sawtooth;
    reg signed [N-1:0] data;
    reg is_ready;
    reg is_running;
    reg ppm;


    always @(posedge i_clk) begin
        if (i_rst) begin
            data <= 0;
            is_running <= 0;
            is_ready <= 0;
        end else if (!is_running && !is_ready && i_start) begin
            data <= i_data;
            is_running <= 1;
            is_ready <= 0;
        end else if (sawtooth == SAWTOOTH_MAX) begin
            is_running <= 0;
            is_ready <= 1;
        end
    end

    always @(posedge i_clk) begin
        if (i_rst) begin
            sawtooth <= SAWTOOTH_MIN;
        end else if (is_running) begin
            sawtooth <= sawtooth + 1;
        end
    end

    always @(posedge i_clk) begin
        if (i_rst) begin
            ppm <= 0;
        end else if (is_running) begin
            if (sawtooth == data) begin
                ppm <= 1;
            end else begin
                ppm <= 0;
            end
        end else begin
           ppm <= 0; 
        end
    end

    assign o_ppm = ppm;
    assign o_busy = is_running;

 endmodule
