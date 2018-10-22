//======================================================================
//
// fmc_arbiter_cdc.v
// -----------------
// The actual clock domain crossing handler of the FMC arbiter
// for the Cryptech Novena FPGA framework.
//
//
// Author: Pavel Shatov
// Copyright (c) 2015, NORDUnet A/S All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// - Neither the name of the NORDUnet nor the names of its contributors may
//   be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//======================================================================

module fmc_arbiter_cdc #
  (
   parameter NUM_ADDR_BITS = 22
   )
   (
    input wire                           fmc_clk, // fmc clock
    input wire                           fmc_req, // fmc transaction request
    output wire                          fmc_ack, // fmc transaction acknowledge
    input wire [NUM_ADDR_BITS+32+2-1: 0] fmc_din, // data from cpu to fpga (write access)
    output wire [31: 0]                  fmc_dout, // data from fpga to cpu (read access)

    input wire                           sys_clk, // user internal clock
    output wire [NUM_ADDR_BITS-1: 0]     sys_addr, // user access address
    output wire                          sys_wren, // user write flag
    output wire [31: 0]                  sys_data_out, // user write data
    output wire                          sys_rden, // user read flag
    input wire [31: 0]                   sys_data_in   // user read data
    );


   //
   // FMC_CLK -> SYS_CLK Request
   //
   wire                                  sys_req;         // request pulse in sys_clk clock domain
   wire [NUM_ADDR_BITS+32+2-1: 0]        sys_dout;        // transaction data in sys_clk clock domain

   cdc_bus_pulse #
     (
      .DATA_WIDTH(NUM_ADDR_BITS+32+2)   // {write, read, addr, data}
      )
   cdc_fmc_sys
     (
      .src_clk(fmc_clk),
      .src_din(fmc_din),
      .src_req(fmc_req),

      .dst_clk(sys_clk),
      .dst_dout(sys_dout),
      .dst_pulse(sys_req)
      );


   //
   // Output Registers
   //
   reg                                   sys_wren_reg     = 1'b0;
   reg                                   sys_rden_reg     = 1'b0;
   reg [NUM_ADDR_BITS-1: 0]              sys_addr_reg     = {NUM_ADDR_BITS{1'bX}};
   reg [31: 0]                           sys_data_out_reg = {32{1'bX}};

   assign sys_wren      = sys_wren_reg;
   assign sys_rden      = sys_rden_reg;
   assign sys_addr      = sys_addr_reg;
   assign sys_data_out  = sys_data_out_reg;


   //
   // System (User) Clock Access Handler
   //
   always @(posedge sys_clk)
     //
     if (sys_req)                               // request detected?
       begin
          sys_wren_reg     <= sys_dout[32+NUM_ADDR_BITS+1];     // set write flag if needed
          sys_rden_reg     <= sys_dout[32+NUM_ADDR_BITS+0];     // set read flag if needed
          sys_addr_reg     <= sys_dout[32+NUM_ADDR_BITS-1:32];  // set operation address
          sys_data_out_reg <= sys_dout[31: 0];  // set data to write
       end
     else                                       // no request active
       begin
          sys_wren_reg  <=  1'b0;               // clear write flag
          sys_rden_reg  <=  1'b0;               // clear read flag
       end


   //
   // System Request 2-cycle delay to compensate registered mux delay in user-side logic
   //
   reg  [ 1: 0] sys_req_dly     = 2'b00;

   always @(posedge sys_clk)
     sys_req_dly <= {sys_req_dly[0], sys_req};

   //
   // SYS_CLK -> FMC_CLK Acknowledge
   //
   cdc_bus_pulse #
     (
      .DATA_WIDTH(32)
      )
   cdc_sys_fmc
     (
      .src_clk(sys_clk),
      .src_din(sys_data_in),
      .src_req(sys_req_dly[1]),

      .dst_clk(fmc_clk),
      .dst_dout(fmc_dout),
      .dst_pulse(fmc_ack)
      );

endmodule

//======================================================================
// EOF fmc_arbiter_cdc.v
//======================================================================
