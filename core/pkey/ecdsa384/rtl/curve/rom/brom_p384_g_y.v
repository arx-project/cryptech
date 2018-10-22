//======================================================================
//
// Copyright (c) 2016, NORDUnet A/S All rights reserved.
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

`timescale 1ns / 1ps

module brom_p384_g_y
  (
   input wire 		clk,
   input wire [ 4-1:0] 	b_addr,
   output wire [32-1:0] b_out
   );


   //
   // Output Registers
   //
   reg [31:0] 		bram_reg_b;

   assign b_out = bram_reg_b;


   //
   // Read-Only Port B
   //
   always @(posedge clk)
     //
     case (b_addr)
       4'b0000:	bram_reg_b <= 32'h90ea0e5f;
       3'b0001:	bram_reg_b <= 32'h7a431d7c;
       4'b0010:	bram_reg_b <= 32'h1d7e819d;
       4'b0011:	bram_reg_b <= 32'h0a60b1ce;
       4'b0100:	bram_reg_b <= 32'hb5f0b8c0;
       4'b0101:	bram_reg_b <= 32'he9da3113;
       4'b0110:	bram_reg_b <= 32'h289a147c;
       4'b0111:	bram_reg_b <= 32'hf8f41dbd;
       4'b1000:	bram_reg_b <= 32'h9292dc29;
       4'b1001:	bram_reg_b <= 32'h5d9e98bf;
       4'b1010:	bram_reg_b <= 32'h96262c6f;
       4'b1011:	bram_reg_b <= 32'h3617de4a;
     endcase


endmodule
