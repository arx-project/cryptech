//------------------------------------------------------------------------------
//
// x25519_fpga_curve_abstract.cpp
// ---------------------------------------------------
// Elliptic curve arithmetic procedures for Curve25519
//
// Authors: Pavel Shatov
//
// Copyright (c) 2015-2016, 2018 NORDUnet A/S
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// - Neither the name of the NORDUnet nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdint.h>
#include "x25519_fpga_model.h"


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
FPGA_BUFFER X25519_G_X;		// x-coordinate of the base point
FPGA_BUFFER X25519_A24;		// coefficient (A + 2) / 4


//------------------------------------------------------------------------------
void fpga_curve_init()
//------------------------------------------------------------------------------
{
	int w_src, w_dst;	// word counters

	FPGA_WORD TMP_G_X[FPGA_OPERAND_NUM_WORDS]	= X25519_G_X_INIT;
	FPGA_WORD TMP_A24[FPGA_OPERAND_NUM_WORDS]	= X25519_A24_INIT;

		/* fill buffers for large multi-word integers */
	for (	w_src = 0, w_dst = FPGA_OPERAND_NUM_WORDS - 1;
			w_src < FPGA_OPERAND_NUM_WORDS;
			w_src++, w_dst--)
	{
		X25519_G_X.words[w_dst]	= TMP_G_X[w_src];
		X25519_A24.words[w_dst] = TMP_A24[w_src];
	}
}


//------------------------------------------------------------------------------
//
// Elliptic curve point scalar multiplication routine.
//
// This uses the Montgomery ladder to do the multiplication and then
// converts the result to affine coordinates.
//
// The algorithm is based on Algorithm 3 from "How to (pre-)compute a ladder"
// https://eprint.iacr.org/2017/264.pdf
//
//------------------------------------------------------------------------------
void fpga_curve_scalar_multiply_abstract(FPGA_BUFFER *PX, FPGA_BUFFER *K, FPGA_BUFFER *QX)
//------------------------------------------------------------------------------
{
	int word_count, bit_count;	// counters

		// temporary buffers
	FPGA_BUFFER R0_X;
	FPGA_BUFFER R0_Z;
	FPGA_BUFFER R1_X;
	FPGA_BUFFER R1_Z;

	FPGA_BUFFER T0_X;
	FPGA_BUFFER T0_Z;
	FPGA_BUFFER T1_X;
	FPGA_BUFFER T1_Z;

		// initialization
	fpga_multiword_copy(&X25519_ONE,  &R0_X);
	fpga_multiword_copy(&X25519_ZERO, &R0_Z);
	fpga_multiword_copy(PX,           &R1_X);
	fpga_multiword_copy(&X25519_ONE,  &R1_Z);

		// handy vars
	FPGA_WORD k_word;
	bool k_bit, r_swap = false;

		// multiply
	for (word_count=FPGA_OPERAND_NUM_WORDS; word_count>0; word_count--)
	{
		for (bit_count=FPGA_WORD_WIDTH; bit_count>0; bit_count--)
		{
				// get current bit of K
			k_word = K->words[word_count - 1] >> (bit_count - 1);
			k_bit = (k_word & (FPGA_WORD)1) == 1;

				// we feed either R0, R1 or R1, R0 into the ladder
			fpga_multiword_copy(r_swap == k_bit ? &R0_X : &R1_X, &T0_X);
			fpga_multiword_copy(r_swap == k_bit ? &R0_Z : &R1_Z, &T0_Z);
			fpga_multiword_copy(r_swap == k_bit ? &R1_X : &R0_X, &T1_X);
			fpga_multiword_copy(r_swap == k_bit ? &R1_Z : &R0_Z, &T1_Z);

				// remember whether we did swapping
			r_swap = k_bit;

				// montgomery ladder step
			fpga_curve_ladder_step(	PX,
									&T0_X, &T0_Z, &T1_X, &T1_Z,
									&R0_X, &R0_Z, &R1_X, &R1_Z);
		}
	}

		// since the lower three bits of the private key are always ...000,
		// the result is in R0_X, R0_Z and 

		// now conversion to affine coordinates
	fpga_curve_to_affine(&R0_X, &R0_Z, &T0_X);

		// so far we've done everything modulo 2*P, we now need
		// to do final reduction modulo P, this can be done using
		// our modular adder this way:
	fpga_modular_add(&T0_X, &X25519_ZERO, QX, &X25519_1P);
}


//------------------------------------------------------------------------------
//
// Montgomery Ladder Step
//
// There are many papers describing Montgomery ladder, this particular
// implementation is based on Algorithm 2 from "Fast elliptic-curve
// cryptography on the Cell Broadband Engine" by Neil Costigan and Peter
// Schwabe
// https://cryptojedi.org/papers/celldh-20090107.pdf
//
//------------------------------------------------------------------------------
void fpga_curve_ladder_step	(FPGA_BUFFER *PX,
							 FPGA_BUFFER *R0X_in,  FPGA_BUFFER *R0Z_in,
							 FPGA_BUFFER *R1X_in,  FPGA_BUFFER *R1Z_in,
							 FPGA_BUFFER *R0X_out, FPGA_BUFFER *R0Z_out,
							 FPGA_BUFFER *R1X_out, FPGA_BUFFER *R1Z_out)
//------------------------------------------------------------------------------
{
	FPGA_BUFFER S0, S1;
	FPGA_BUFFER D0, D1;
	FPGA_BUFFER QS0, QD0;
	FPGA_BUFFER S0D1, S1D0;
	FPGA_BUFFER TS, TD;
	FPGA_BUFFER QTD;
	FPGA_BUFFER T0, TA, T1;

	fpga_modular_add(R0X_in, R0Z_in,      &S0,     &X25519_2P);
	fpga_modular_add(R1X_in, R1Z_in,      &S1,     &X25519_2P);
	fpga_modular_sub(R0X_in, R0Z_in,      &D0,     &X25519_2P);
	fpga_modular_sub(R1X_in, R1Z_in,      &D1,     &X25519_2P);
	//
	fpga_modular_mul(&S0,    &S0,         &QS0,    &X25519_2P);
	fpga_modular_mul(&D0,    &D0,         &QD0,    &X25519_2P);
	fpga_modular_mul(&S0,    &D1,         &S0D1,   &X25519_2P);
	fpga_modular_mul(&S1,    &D0,         &S1D0,   &X25519_2P);
	//
	fpga_modular_add(&S1D0,  &S0D1,       &TS,     &X25519_2P);
	fpga_modular_sub(&S1D0,  &S0D1,       &TD,     &X25519_2P);
	//
	fpga_modular_mul(&TD,    &TD,         &QTD,    &X25519_2P);
	//
	fpga_modular_sub(&QS0,   &QD0,        &T0,     &X25519_2P);
	fpga_modular_mul(&T0,    &X25519_A24, &TA,     &X25519_2P);
	fpga_modular_add(&TA,    &QD0,        &T1,     &X25519_2P);
	//
	fpga_modular_mul(&QS0,   &QD0,        R0X_out, &X25519_2P);
	fpga_modular_mul(&T0,    &T1,         R0Z_out, &X25519_2P);
	fpga_modular_mul(&TS,    &TS,         R1X_out, &X25519_2P);
	fpga_modular_mul(PX,     &QTD,        R1Z_out, &X25519_2P);
}


//------------------------------------------------------------------------------
//
// Convertion to affine coordinates.
//
// This uses Fermat's little theorem to calculate Q_X = P_X * P_Z ^ -1.
//
// The corresponding addition chain which Bernstein calls "straightforward
// sequence of 254 squarings and 11 multiplications" in his original paper was
// taken from here:
// https://briansmith.org/ecc-inversion-addition-chains-01
//
//------------------------------------------------------------------------------
void fpga_curve_to_affine	(FPGA_BUFFER *P_X, FPGA_BUFFER *P_Z,
							 FPGA_BUFFER *Q_X)
//------------------------------------------------------------------------------
{
	int cyc_count;	// counter

		// temporary variables
	FPGA_BUFFER R1, R2;
	FPGA_BUFFER T_1;
	FPGA_BUFFER T_10;
	FPGA_BUFFER T_1001;
	FPGA_BUFFER T_1011;
	FPGA_BUFFER T_X5;
	FPGA_BUFFER T_X10;
	FPGA_BUFFER T_X20;
	FPGA_BUFFER T_X40;
	FPGA_BUFFER T_X50;
	FPGA_BUFFER T_X100;

		// let's go
	fpga_multiword_copy(P_Z, &T_1);
	//
	fpga_modular_mul(&T_1, &T_1, &T_10, &X25519_2P);
	//
	fpga_modular_mul(&T_10, &T_10, &R1, &X25519_2P);
	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
	fpga_modular_mul(&R2, &T_1, &T_1001, &X25519_2P);
	//
	fpga_modular_mul(&T_1001, &T_10, &T_1011, &X25519_2P);
	//
	fpga_modular_mul(&T_1011, &T_1011, &R1, &X25519_2P);
	fpga_modular_mul(&R1, &T_1001, &T_X5, &X25519_2P);
	//
	fpga_multiword_copy(&T_X5, &R1);
	for (cyc_count=0; cyc_count<5; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	fpga_modular_mul(&R2, &T_X5, &T_X10, &X25519_2P);
	//
	fpga_multiword_copy(&T_X10, &R1);
	for (cyc_count=0; cyc_count<10; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	fpga_modular_mul(&R1, &T_X10, &T_X20, &X25519_2P);
	//
	fpga_multiword_copy(&T_X20, &R1);
	for (cyc_count=0; cyc_count<20; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	fpga_modular_mul(&R1, &T_X20, &T_X40, &X25519_2P);
	//
	fpga_multiword_copy(&T_X40, &R1);
	for (cyc_count=0; cyc_count<10; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	fpga_modular_mul(&R1, &T_X10, &T_X50, &X25519_2P);
	//
	fpga_multiword_copy(&T_X50, &R1);
	for (cyc_count=0; cyc_count<50; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	fpga_modular_mul(&R1, &T_X50, &T_X100, &X25519_2P);
	//
	fpga_multiword_copy(&T_X100, &R1);
	for (cyc_count=0; cyc_count<100; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	//
	fpga_modular_mul(&R1, &T_X100, &R2, &X25519_2P);
	//
	for (cyc_count=0; cyc_count<50; cyc_count++)
	{	if ((cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);	// inverse order here!
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	//
	fpga_modular_mul(&R2, &T_X50, &R1, &X25519_2P);
	//
	for (cyc_count=0; cyc_count<5; cyc_count++)
	{	if (!(cyc_count % 2))	fpga_modular_mul(&R1, &R1, &R2, &X25519_2P);
		else					fpga_modular_mul(&R2, &R2, &R1, &X25519_2P);
	}
	//
	fpga_modular_mul(&R2, &T_1011, &R1, &X25519_2P);
	//
	fpga_modular_mul(P_X, &R1, Q_X, &X25519_2P);
}


//------------------------------------------------------------------------------
// End-of-File
//------------------------------------------------------------------------------
