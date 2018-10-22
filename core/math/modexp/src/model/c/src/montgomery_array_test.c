#include <stdio.h>
#include <stdlib.h>
#include "montgomery_array.h"
#include "bignum_uint32_t.h"

const uint32_t TEST_CONSTANT_PRIME_15_1 = 65537;
const uint32_t TEST_CONSTANT_PRIME_31_1 = 2147483647u; // eighth Mersenne prime

void testShiftRight() {
	printf("=== Test shift right ===\n");
	uint32_t a[] = { 0x01234567, 0x89abcdef };
	shift_right_1_array(2, a, a);
	shift_right_1_array(2, a, a);
	shift_right_1_array(2, a, a);
	shift_right_1_array(2, a, a);
	uint32_t expected[] = { 0x00123456, 0x789abcde };
	assertArrayEquals(2, expected, a);
}

void testAdd() {
	printf("=== Test add ===\n");
	uint32_t a[] = { 0x01234567, 0x89abcdef };
	uint32_t b[] = { 0x12000002, 0x77000001 };
	uint32_t c[2];
	add_array(2, a, b, c);
	uint32_t expected[] = { 0x1323456a, 0x00abcdf0 };
	assertArrayEquals(2, expected, c);
}

void testSub() {
	printf("=== Test sub ===\n");
	uint32_t a[] = { 0x01234567, 0x89abcdef };
	uint32_t b[] = { 0x00200000, 0x8a001001 };
	uint32_t c[2];

	sub_array(2, a, b, c);
	uint32_t expected1[] = { 0x1034566, 0xffabbdee };
	assertArrayEquals(2, expected1, c);

	sub_array(2, b, a, c);
	uint32_t expected2[] = { 0xfefcba99u, 0x00544212u };
	assertArrayEquals(2, expected2, c);

	uint32_t aa[] = { 0, 0x01234567, 0x89abcdef };
	uint32_t bb[] = { 0, 0x00200000, 0x8a001001 };
	uint32_t cc[3];

	sub_array(3, aa, bb, cc);
	uint32_t expected3[] = { 0, 0x1034566, 0xffabbdee };
	assertArrayEquals(2, expected3, cc);

	sub_array(3, bb, aa, cc);
	uint32_t expected4[] = { 0xffffffff, 0xfefcba99u, 0x00544212u };
	assertArrayEquals(3, expected4, cc);
}

uint32_t m_residue(uint32_t A, uint32_t M) {
	uint64_t x = A & 0xFFFFFFFFFL;
	uint64_t m = M & 0xFFFFFFFFFL;
	x <<= 32;
	x %= m;
	return (uint32_t) x;
}

void test_montgomery_a_b_m(uint32_t A, uint32_t B, uint32_t M) {
	//int prodMod = (A * B) % M;
	uint32_t productModulus = A % M;
	productModulus *= B % M;
	productModulus %= M;
	uint32_t MM[] = { M };
	uint32_t Ar[] = { m_residue(A, M) };
	uint32_t Br[] = { m_residue(B, M) };
	uint32_t s[1];
	mont_prod_array(1, Ar, Br, MM, s);
	uint32_t ONE[] = { 1 };
	uint32_t monProd[1];
	mont_prod_array(1, ONE, s, MM, monProd);
	uint32_t productModulusMontgomery = monProd[0];
	uint32_t success = productModulus == productModulusMontgomery;
	printf("%c A=%3x B=%3x M=%3x A*B=%3x Ar=%3x Br=%3x Ar*Br=%3x A*B=%3x\n",
			success ? '*' : ' ', A, B, M, productModulus, Ar[0], Br[0], s[0],
			productModulusMontgomery);
}

void test_montgomery_modulus() {
	printf("=== Test mod ===\n");
	//printf("%lx\n", 2305843009213693951ul % 0x7ffffffful );
	uint32_t A[] = { 0, (1 << (61 - 32)) - 1, 0xffffffff }; //2^61-1 Ivan Mikheevich Pervushin
	uint32_t B[] = { (1 << (89 - 64)) - 1, 0xffffffff, 0xffffffff }; //2^89-1 R. E. Powers
	uint32_t M[] = { 0, 0, (1 << 31) - 1 }; //Leonhard Euler
	uint32_t temp[3];
	uint32_t actual1[3];
	uint32_t actual2[3];
	modulus_array(3, A, M, temp, actual1);
	modulus_array(3, B, M, temp, actual2);
	uint32_t expected1[] = { 0, 0, 1073741823 };
	uint32_t expected2[] = { 0, 0, 134217727 };
	assertArrayEquals(3, expected1, actual1);
	assertArrayEquals(3, expected2, actual2);
}

/*
 @Test
 public void test_huge_numbers() {
 int[] A = { 0, (1<<(61-32)) - 1, 0xffff_ffff }; //2^61-1 Ivan Mikheevich Pervushin
 int[] B = { (1<<(89-64)) - 1,  0xffff_ffff, 0xffff_ffff }; //2^89-1 R. E. Powers
 int[] M = { 0, 0, (1<<31)-1 }; //Leonhard Euler
 int[] Ar = new int[3];
 int[] Br = new int[3];
 int[] s = new int[3];
 int[] ONE = { 0, 0, 1 };
 int[] monProd = new int[3];
 MontgomeryArray.m_residue(3, A, M, Ar);
 MontgomeryArray.m_residue(3, B, M, Br);
 MontgomeryArray.mont_prod_array(3, Ar, B, M, s);
 MontgomeryArray.mont_prod_array(3, ONE, s, M, monProd);
 System.out.printf("The solution: %8x %8x %8x\n", monProd[0], monProd[1], monProd[2]);
 }
 */

void test_montgomery_one_item_array() {
	printf("=== test_montgomery_one_item_array ===\n");
	test_montgomery_a_b_m(11, 17, 19);
	test_montgomery_a_b_m(11, 19, 17);
	test_montgomery_a_b_m(17, 11, 19);
	test_montgomery_a_b_m(17, 19, 11);
	test_montgomery_a_b_m(19, 11, 17);
	test_montgomery_a_b_m(19, 17, 11);

	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_15_1, 17, 19);
	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_15_1, 19, 17);
	test_montgomery_a_b_m(17, TEST_CONSTANT_PRIME_15_1, 19);
	test_montgomery_a_b_m(17, 19, TEST_CONSTANT_PRIME_15_1);
	test_montgomery_a_b_m(19, TEST_CONSTANT_PRIME_15_1, 17);
	test_montgomery_a_b_m(19, 17, TEST_CONSTANT_PRIME_15_1);

	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_15_1, 17,
			TEST_CONSTANT_PRIME_31_1);
	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_15_1, TEST_CONSTANT_PRIME_31_1,
			17);
	test_montgomery_a_b_m(17, TEST_CONSTANT_PRIME_15_1,
			TEST_CONSTANT_PRIME_31_1);
	test_montgomery_a_b_m(17, TEST_CONSTANT_PRIME_31_1,
			TEST_CONSTANT_PRIME_15_1);
	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_31_1, TEST_CONSTANT_PRIME_15_1,
			17);
	test_montgomery_a_b_m(TEST_CONSTANT_PRIME_31_1, 17,
			TEST_CONSTANT_PRIME_15_1);
}

void test_montgomery_modexp() {
	printf("=== test_montgomery_modexp ===\n");
	uint32_t X[] = { 0, (1 << (61 - 32)) - 1, 0xffffffff }; //2^61-1 Ivan Mikheevich Pervushin
	uint32_t M[] = { (1 << (89 - 64)) - 1, 0xffffffff, 0xffffffff }; //2^89-1 R. E. Powers
	uint32_t E[] = { 0, 0, (1 << 31) - 1 }; //Leonhard Euler

	uint32_t ONE[] = { 0, 0, 1 };
	uint32_t Z[] = { 0, 0, 0 };

	mod_exp_array(3, ONE, ONE, M, Z);
	assertArrayEquals(3, ONE, Z);

	mod_exp_array(3, ONE, E, M, Z);
	assertArrayEquals(3, ONE, Z);

	mod_exp_array(3, X, E, M, Z);
	uint32_t expected[] = { 0x0153db9b, 0x314b8066, 0x3462631f };
	assertArrayEquals(3, expected, Z);
}

void test_modExp_4096bit_e65537() {
	printf("=== test_modExp_4096bit_e65537 ===\n");
	uint32_t M[] = { 0x00000000, 0xecc9307c, 0x57a39970, 0x7e9e2569, 0x872cd790,
			0x0d4dddcc, 0x704fd131, 0x9395388d, 0x07e63a16, 0x37ea6fae,
			0x3873a01e, 0x0df4a57b, 0xb90bc708, 0xa05ade61, 0x91ef3868,
			0x58db06db, 0x893e2d41, 0xc75bb93d, 0x0c7f3be8, 0x8f57c9f9,
			0x477efa62, 0xf509e077, 0x568d59aa, 0x28552ee8, 0xa042f88d,
			0xf776a12d, 0x19f3685b, 0x1205c3f7, 0xfb7db6c5, 0x354908b1,
			0x099640c0, 0x709ab3e8, 0xe76149de, 0x6bc111d2, 0x95210730,
			0xbab8e493, 0x95168d09, 0x5242aba5, 0x4b98da8a, 0xb755eb64,
			0x246c6732, 0xc8fd54f4, 0xf6ed5686, 0x6ca61ceb, 0x239f1133,
			0x1abdc477, 0x24a35c02, 0xbaef93b4, 0x6b856235, 0xb34318c6,
			0x420da1a7, 0xa94a7298, 0x53141662, 0x0bfb5c3d, 0x183fa12c,
			0x5c4b3e4a, 0x6cd2f7cd, 0xc5446327, 0x6e90cf3e, 0x07fe2e20,
			0x78fe3b26, 0x73419d8f, 0xe5c5666d, 0xce01b1c7, 0xc45ce6da,
			0x9ca6e8ed, 0x42ec9161, 0x5ec6d3ec, 0x72921ad2, 0x8f4a9496,
			0xb146e974, 0xc9ca5c00, 0xfdea07f5, 0xd8a27ee8, 0x42507619,
			0x6ee518c8, 0x4a626aaf, 0xe099db09, 0xb2d44800, 0x44ca5299,
			0x74b3edd3, 0xbafd6615, 0x042e345d, 0xa39c8000, 0xbc42f7b0,
			0x1d8fc65b, 0x02a73859, 0xf1bf3dac, 0x33473f8a, 0xccd0d5c8,
			0x4e355e77, 0x008b1ae1, 0x77c43bde, 0xf2fa7e9a, 0x1828147e,
			0x2dca431f, 0x612fc4c0, 0x2c652d44, 0x55996f19, 0xb367f72e,
			0x9958b270, 0xa96f7b1f, 0xfbb230e3, 0xe70791fd, 0x6e9d6402,
			0x98dbd1dd, 0xea7f1494, 0x65a4602d, 0x93726a54, 0x53876bb3,
			0x57c6041b, 0x7a83ee09, 0x244588ce, 0xd4cf9317, 0xd77add56,
			0xc7e63f59, 0xc2b65e19, 0xb3982427, 0xcfc4c9a1, 0x8bef7de2,
			0xaddc6cad, 0xb4bee49f, 0x46edae94, 0xf3dba909, 0xc74d8a1c,
			0xbd470d28, 0x7f0dc6b1, 0xa5cc5313, 0xd47ef6b3 };
	uint32_t X[] = { 0x00000000, 0xffa525f2, 0x526335dd, 0xc145f9fd, 0xed720382,
			0x934b737a, 0x81cda0a4, 0x45e2aa14, 0x0089273f, 0x7a4c646c,
			0x183b156c, 0x92204c68, 0x865e5c35, 0x9ec60d43, 0x32b9a26c,
			0x2fbc9c6e, 0x37d61a87, 0x6e90f966, 0x3ff81ce1, 0x809cc453,
			0x2a48fc23, 0x82884020, 0xa6a5ace8, 0x245f7e64, 0x73d00956,
			0x4c23c4ff, 0x6c0e00d1, 0x522a138e, 0xeae0e578, 0xa9b77c44,
			0x4d69a705, 0xcb187201, 0xc2548a67, 0x1885d9ba, 0x8a2efeaf,
			0x1c0b04a0, 0x9317b984, 0xff667ee1, 0xad8f39d4, 0x3423e001,
			0x1be36670, 0xfd77ba6a, 0x325aa26e, 0x934d0eb6, 0x1b0a7066,
			0x41d6d679, 0x747bdbe1, 0x0eaa9370, 0xef8b3a3f, 0x695a3a93,
			0x3a615ff1, 0x222788e2, 0x0300db2a, 0xefbd5465, 0xed895ac5,
			0x993c94cc, 0x4ac55161, 0xe8cb628d, 0x8d8560ab, 0x51f8aa94,
			0x3f2e3412, 0x00adef44, 0x3faa81ef, 0xdacf51df, 0x9f908687,
			0x9fc8334f, 0x0dd0ae1d, 0x1bad0826, 0x93a55bcf, 0x1f74d9ba,
			0x448e9393, 0x7115db19, 0x9667b337, 0xd62700a3, 0x1ab551aa,
			0xf50113b3, 0xb9dbe164, 0x3241e264, 0x030de43d, 0x96fecc68,
			0x19d27dac, 0xd375d9c9, 0xedec942c, 0x3e574a2d, 0xcb9667f7,
			0x0c448d73, 0x60488187, 0x12177ef5, 0xfd07c0e8, 0x2753cf63,
			0xf9c1bac6, 0x856b05c6, 0x36d24921, 0x41bd5246, 0x2598118f,
			0x49e857cd, 0xc9692afc, 0x64d28a5b, 0x52aba529, 0xd6ef02ca,
			0x5b72b03c, 0x5cc04b9f, 0xf423b253, 0xf84c2697, 0x11b2cc10,
			0xa822c3b4, 0x3d581533, 0xaf3c56b7, 0x15d734b3, 0x93abdc84,
			0x970a504b, 0x8a867419, 0x8a4d46c8, 0x18c62d83, 0x088ff310,
			0x26f7808d, 0x7369e2d7, 0xa4a2cf6d, 0xc5efce92, 0xd6668160,
			0x5d1c3cae, 0xf62b2bd7, 0x9397ec83, 0x4577de0a, 0x4df48770,
			0x66203ab7, 0x27ba7480, 0x96bd4c9e, 0xc6f82263 };
	uint32_t E[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00010001 };
	uint32_t expected[] = { 0, 0x41e92995, 0x9f90fac9, 0xd092a89b, 0xe906f13a,
			0x7dda3812, 0x8f580431, 0xed685e65, 0x6975838a, 0xc04c500a,
			0x440c8dc1, 0xdf61f134, 0x72111481, 0x438a0ad4, 0xd1901dbe,
			0x130b1261, 0x190a1cc9, 0xffb5def5, 0xabf8d5e5, 0x8e6c445b,
			0x7348af60, 0xc46a967a, 0x760bba83, 0x6eaec513, 0x9ad339fc,
			0x6b1d7f32, 0x42d7ca96, 0x39e76281, 0xc679ae04, 0xa961a991,
			0x54dd9103, 0x53c21900, 0xc305deeb, 0x8fc0707b, 0xe73cf97e,
			0xfe9199e6, 0x7d2fc3fe, 0xac909b86, 0x183c05b3, 0xe9c4c177,
			0x3bfbe011, 0x9fba913b, 0xa3b9cfeb, 0xd644a5d9, 0xb2e2e65d,
			0xca19686b, 0x246e180f, 0x8c5afaa5, 0xeb637e86, 0x8d646f80,
			0x319e795c, 0xcf0ac0d2, 0xcf2eb4fb, 0x1fd1ecf2, 0xd5cdb147,
			0xbbe06322, 0x7867ac67, 0xbe1e04e7, 0xfb987b8f, 0x0eac7562,
			0x2d1224c5, 0x6ca25b32, 0x4ffc44ce, 0x3ad6e3f0, 0xafff53ca,
			0x39ebd8cf, 0x0a428629, 0x4626403e, 0x6281df65, 0x52f47f9f,
			0x60c67231, 0xaa4d50e8, 0x1175a6be, 0x75326395, 0xce45d310,
			0x7e90216f, 0xef2c8b25, 0x755488f0, 0xe58ebd71, 0x8d47760e,
			0xd06aa6e5, 0x713a592c, 0x25a28fab, 0xaee62686, 0xf26ed6e9,
			0x7305f55a, 0x1231a3ac, 0x10823b96, 0x08934288, 0x58aa1a18,
			0x51a89325, 0x7de9ba06, 0xac9541e7, 0x4db4a59d, 0xa33cfaba,
			0xb2e4a7ee, 0x099c895c, 0x77e7f6a5, 0x922b9001, 0xd835a66b,
			0xdf594547, 0x4f6855c7, 0xe3f24218, 0xfe65e99f, 0x7e921b6e,
			0x8dac463e, 0x73b82b77, 0x24ef9883, 0x6ae91fee, 0xc55c4206,
			0x073ed7bc, 0xb780c3fe, 0x07a2f0d9, 0x3f8deace, 0x1332373b,
			0xd2a2c63c, 0xc674af4e, 0xd0aee696, 0x614b3969, 0x8fcac805,
			0x58fa13ff, 0x6cf0a5c2, 0x0ac24bf4, 0xd7901e58, 0x9b616f55,
			0x2517443d, 0xb00a5613, 0x217b8957, 0x5a4ba6c4 };

	//output
	uint32_t Z[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	mod_exp_array(129, X, E, M, Z);
	assertArrayEquals(129, expected, Z);
}

void test_modExp_8192_e65537() {
	printf(" ----- test_modExp_8192_e65537 -----\n");
	uint32_t M[] = { 0x00000000, 0x9985a7f5, 0xb471b248, 0xd13838a3, 0x75e22fc7,
			0x0e0d72b0, 0x6ea72eb3, 0x958b1b8e, 0x431cb10d, 0x72421e7e,
			0xb0e33fa3, 0xc5b6d437, 0xb7c1ce28, 0xe4960b94, 0x7c36159e,
			0xc98580a1, 0x2c98a45e, 0x8c0a5d37, 0x65bdbb62, 0x707d3cec,
			0x03d2d25e, 0xd8e420e8, 0xec24c78b, 0xec2f2dbe, 0x97572117,
			0x5933fa87, 0x01440858, 0xcf4e5a64, 0xe6a0f624, 0x59c0e042,
			0x83d52d2c, 0x6c4144c0, 0x112769f5, 0x86b85e44, 0x434015d2,
			0xb4473787, 0x1f33a844, 0x0c717bf3, 0xea8228f0, 0x7b46cbc4,
			0x28c15ea0, 0xa4bdda03, 0x27314b2f, 0x6ea6856e, 0xec9cbd40,
			0x40cfea29, 0xf5fab20a, 0x3726bdc0, 0x74eb6930, 0x52cf502a,
			0xf77f8d47, 0xf27acfeb, 0x901c570d, 0xda0c86f6, 0x96bd21c3,
			0xe0c42ff8, 0x3244ae66, 0x490c9e5e, 0x32abf7ad, 0x9f467988,
			0xa2bd97e5, 0x7b053c1c, 0x9dfd9bf0, 0x836a6d08, 0x7f7f12e8,
			0x13ac2747, 0x79fc03b1, 0xf452cd02, 0x78662a82, 0xf67bab98,
			0xa4a6bf69, 0xba098c38, 0x6f3b14b0, 0x92dc6f3e, 0x4a71c587,
			0x8e901015, 0xcfa583b6, 0xf8af38f2, 0x3ac2f6ed, 0xd433f6c4,
			0x214cb499, 0x0e2bb7b1, 0xff121c3d, 0x70c8567e, 0x5ee2a3b0,
			0x926fc6d1, 0x2ed64fed, 0xb34139d8, 0x01357ef6, 0x011edb10,
			0x08253a72, 0x09549e5f, 0x6f2efebd, 0x7f0c8957, 0x92579f0c,
			0x0b7af9de, 0xa74e4d78, 0x6623c204, 0x01df02fb, 0x3f5b2a7a,
			0xc32accc1, 0xe4ee37d3, 0x6a31107c, 0xa6b0cc97, 0x38378a05,
			0xd20b36a5, 0x64a71a1a, 0x371e20d6, 0x5802ab92, 0xaff5961b,
			0xdcdac5d3, 0x7ae73afc, 0x66d7a7a0, 0xeca201a5, 0x8f1bd259,
			0xd1210db9, 0x2a9e3e13, 0xff238682, 0xa5951228, 0xc54e9667,
			0x85db95b2, 0x34a56c30, 0x3535ebce, 0xdbc90290, 0x4a29445b,
			0x92c0d1a4, 0x1575edf7, 0xd9fa0ff9, 0xf56b1e63, 0xc4a193ac,
			0xf5184572, 0xb6496b0c, 0x6f91242f, 0x46026714, 0xadb65332,
			0x3514bbea, 0x9e41a9d7, 0x4f6b34ef, 0xaa807f4e, 0x4a0aed66,
			0x456c5a4f, 0x21b6283c, 0x704b7670, 0xf3d1bbb1, 0xe3f7c1ab,
			0xc52b5fe0, 0x7ab11f42, 0xc6dcc8b2, 0x5547689d, 0x4c4808f0,
			0x353d809f, 0x4c670bc0, 0xbc3d6825, 0x3262efce, 0xf692ffe6,
			0x216f842a, 0xa0a75fc7, 0x3ff0874b, 0x6e8b2052, 0x3aff2ef1,
			0xe095eca1, 0x23cbceeb, 0xa0303b50, 0x5cf66579, 0x5d359223,
			0x86cc19c0, 0x59b365fa, 0xd8246c23, 0xa615adb6, 0xe5d7eee5,
			0xc9749976, 0x9e7ea208, 0xacfcb6cf, 0x23803b8c, 0x65eeb750,
			0xbcb3c4a0, 0xf99a6721, 0xbcb8d46f, 0xe0a4c149, 0x18e18f68,
			0x4916c065, 0x5c492551, 0x3ecb0227, 0x48714459, 0x55b47877,
			0xb6e40f75, 0x64bb763c, 0x82be2c06, 0x2023ba3f, 0x9f1b2958,
			0x163af75a, 0xf0f63eba, 0xe8c7ad30, 0x91437810, 0xbc78b73f,
			0xd0ef4e44, 0x211b41e1, 0x656707b4, 0x6f4c916d, 0x10aa0301,
			0x258ac87e, 0xcc39eefe, 0x5f332447, 0xd645e269, 0xcb2d162a,
			0x9a587c06, 0x7852e9f0, 0xc5d24de9, 0x8dc5227d, 0x13605de1,
			0x63444a09, 0x87bd3b72, 0xe1873b32, 0xb9d62892, 0x4d76782f,
			0x5310b181, 0x60336fc9, 0x7cc2fe76, 0xa51c80f0, 0x0bc4fb31,
			0xee659283, 0xef3c1b61, 0xa1861d2a, 0x82c69517, 0x2283a0e2,
			0x048cb25e, 0x5ae032a5, 0xab454efa, 0x21c999ea, 0x7e711d04,
			0x87637f43, 0xee2ad2d6, 0x7b681e4d, 0xf5a45708, 0x207c634b,
			0xd997f0fb, 0xa59fcf3f, 0xbb096b59, 0x57f96720, 0xfe0108cb,
			0xf2ae1bc7, 0xf460f10b, 0x9767fe9c, 0xd2e48ba7, 0x6c23f61a,
			0x0d82f70f, 0xda11f4b3, 0xc506afb4, 0xb42316fb, 0x0188f9c8,
			0xcea8efbc, 0xb0ec2877, 0x5201df13, 0x93c7f871, 0x1400e066,
			0xdbe6df0f, 0xd212da97 };
	uint32_t X[] = { 0x00000000, 0xb6653f16, 0x10eb1705, 0x1a79f4f5, 0xee134b76,
			0xbb8b7df0, 0xc382f8d0, 0x6f5c5e73, 0x1bed452d, 0x4b427a86,
			0x2ab146eb, 0xf5896a94, 0xed72bb1b, 0x998221a6, 0x6bf43791,
			0xb5c0d609, 0xe8b9ea1c, 0x39ea3a97, 0xcbcce608, 0xa61e5689,
			0xe5e466b7, 0x07483ab5, 0x4e2432b5, 0xda9ee0d7, 0x0b59c87d,
			0xc8b63d97, 0xecdbaeda, 0x10650120, 0x2bae9e4c, 0x6ea19ac0,
			0xc912f31c, 0xf71fdbd7, 0x347bdbdf, 0xc6c8cafa, 0x5aec4f86,
			0xa1f42467, 0x63b4dc7a, 0x0064f555, 0x50ead199, 0x90ad93df,
			0x352c1b1a, 0xdaf04f38, 0x72be7e10, 0x948c2aee, 0xc58d6167,
			0x7c59371e, 0x9e497f65, 0x777544c1, 0xcbf3a7fe, 0x54afb8ed,
			0x1ac30914, 0xd25a535a, 0x5a4d5e2a, 0x64317436, 0x2c5f0b42,
			0x1eed47d6, 0x589250d2, 0xbd7a2091, 0x16c096ba, 0x176a7203,
			0x1ab196f7, 0x73cfe57d, 0x4ea2fb45, 0x30d05daf, 0x6547fbd8,
			0xe846a73e, 0xff88cd8a, 0xbdfe932b, 0xa84f24e3, 0x2ef9e600,
			0x0ec48b52, 0x97984ff6, 0x331c65f3, 0x5f4bc560, 0xb1c52093,
			0x9256a520, 0x9ac407e8, 0xa0e5b9d3, 0x4244ec44, 0x0fe8cb15,
			0x20e2c16b, 0x5e3ab44e, 0xc6c80e5a, 0x03b41505, 0xd846ab1f,
			0x22c9b2e7, 0xe1ac0b06, 0x9e0f2f01, 0x27d013a0, 0xb4bd171c,
			0x56902dbc, 0xef2e37bb, 0x7ffa4c2a, 0x3fe2d892, 0x32adbdf1,
			0x47ab2361, 0x77b9ebcf, 0xbe0b7f56, 0x8f6fcce1, 0xbf274a2b,
			0x5aa9cc50, 0x3f5ea127, 0x76b41504, 0x34acd7ae, 0x6dd78597,
			0xf01d3adc, 0xa62281dd, 0x5ba5d603, 0x6ad38579, 0x80b7d394,
			0x2522670e, 0x7cb751f9, 0xe9f00f53, 0x4c479b55, 0x0c59f9ac,
			0x427be6f5, 0xfdc1b07a, 0xdbf83a9d, 0x73893597, 0x479a4da5,
			0xada621a5, 0x69d17cad, 0x336b24d7, 0xbeaa48c8, 0xd536b856,
			0x5312a7f2, 0xce23749b, 0x2f60380c, 0x6a8519fb, 0x73bb0c63,
			0xe9af0477, 0x8f4dbea7, 0x96130cb9, 0xfdd23e84, 0x98b23dd4,
			0x664f494f, 0x30d5092d, 0x6c8f11ec, 0xd8ca635c, 0xdb1aa708,
			0xd5f240df, 0xc16a9c52, 0x67eb246f, 0x5fbcd9fb, 0x69547a8a,
			0xba679293, 0xb72708e9, 0x465927d4, 0x7fc978f6, 0x394e179a,
			0x966099a1, 0x85e96016, 0x0d0cd37a, 0x2c1f76e4, 0x5252c4b1,
			0xad6d937e, 0x1ab76b50, 0xc0e389cc, 0xef54099d, 0xd664487b,
			0x7ea335b9, 0xe271debd, 0xaab759f2, 0x106cfdc9, 0x971fee79,
			0x02203413, 0xd557bd16, 0x134e31ff, 0x7d7e2366, 0xcb35a02a,
			0x4df05eee, 0xc5ef9267, 0x461c27ec, 0x90df6170, 0x90341d6b,
			0x81498b1e, 0xd97acd5d, 0x5a7e54f7, 0x4d404564, 0x5df9fb75,
			0x84a9b368, 0x24136b34, 0xdfb89872, 0x503ceca1, 0xf7b5cdd8,
			0x87d0a492, 0x4c2e1ad8, 0xc9fcfa56, 0xbf8f9ed1, 0x0f96b732,
			0x487cd30a, 0x0e036063, 0x5f07ff78, 0x66e1dede, 0x0eb8cc0a,
			0x8fbdcbdb, 0x9d5ea41b, 0xe33e1b85, 0xd93b5cd7, 0xc4fc0b99,
			0x0128e02c, 0x60a6b1ac, 0xe67d1c8d, 0xed4dc097, 0xe8a30cd6,
			0x842155d7, 0x34b01d4d, 0x7cad62eb, 0xa5045158, 0xab4a7efa,
			0x90e545ec, 0x065e394b, 0x1081fa2e, 0x6d0c82ed, 0x1a31afa6,
			0x14cfec80, 0xc4968aea, 0x43cb7a4b, 0xfb0c6c61, 0x98fe235a,
			0x414651df, 0xd38de848, 0xba6af557, 0x4aaa318b, 0x176dc111,
			0x103e444b, 0xe77243be, 0x10d40959, 0xc663ee7d, 0x5b534ee1,
			0x5cbd52dd, 0x285e7a83, 0x26180641, 0x30725b39, 0xf1a3bf2c,
			0x1558d063, 0x212e8671, 0x6caaf8af, 0x2bc05f16, 0x1e217957,
			0x43e5fefe, 0x7dd900ee, 0xfe9fac2c, 0x71e7f6e4, 0xd30c6738,
			0x93713c93, 0xab488e64, 0x18bfd074, 0x00bf5c1f, 0x0f58c72b,
			0xaea7c0a4, 0x5b425720, 0x9b7638f8, 0x0b0cc33d, 0x2cf425f4,
			0x56663cb9, 0xa1af9d3d };
	uint32_t E[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0x00010001 };
	uint32_t expected[] = { 0x00000000, 0x912634a1, 0x6ec3c9f3, 0x64f529ff,
			0xf09df29a, 0x3e840673, 0xb0e7d486, 0xac86e264, 0x532c59cf,
			0xc9bbafed, 0xe7c9c9fe, 0xced851cd, 0x8e0bd166, 0x4742de23,
			0xc40fa105, 0x7f347439, 0x5077b16a, 0x25c71cf4, 0x697434df,
			0x46a182bd, 0xd4d6d55e, 0x6a14b83b, 0xb6759387, 0xf610bed9,
			0x5042c45f, 0x10f897b2, 0x54033cd7, 0x3a7fbe03, 0xf181b113,
			0x30e72d45, 0x0ff3c192, 0x4f28a187, 0xa7d3e445, 0x562d3d19,
			0x1a9692b4, 0x4fb671ef, 0x2f3b0f7e, 0xff42b088, 0xfc1813b5,
			0x52fd1c53, 0xfde5d4e8, 0x4e5b6495, 0x849b3866, 0x78ee0c44,
			0x6cdd6990, 0x1e4da747, 0x4af19d60, 0x6aa59b09, 0x575ff40f,
			0xf9ba88f5, 0x64989bd2, 0x19c4d6fb, 0x1e0afe1e, 0xe4649ae3,
			0x3302ca5f, 0x29ccc977, 0x8e5bcbf9, 0x99e89edb, 0x3cf4a6cc,
			0x73f3ad7e, 0xd6bab2dc, 0x8f9f44e5, 0x03f3a4f7, 0xed08dd2e,
			0x3d87341c, 0xf8f906eb, 0x0bd7960c, 0x2cba9907, 0x1dca61ba,
			0xe38d9c17, 0x2110fbee, 0x53873496, 0xddd1d25a, 0xe42783d0,
			0x8884140e, 0x949c1c4a, 0x4f22df84, 0x62a16619, 0x722163a3,
			0xf28a3f22, 0x05ede7e1, 0x8d35f28f, 0x851e2246, 0xa7650d4b,
			0x3e2ff03e, 0xab9ca6b9, 0x90e1e8a6, 0xee849181, 0x53b6a7e9,
			0x544c21da, 0xf5b953fb, 0xba2c4477, 0x79f64cb3, 0x3b7be276,
			0xe252186c, 0x8f8ac75e, 0xd0bc439d, 0xdcca752f, 0xc46c74c4,
			0xcf19d301, 0xa44cdc10, 0xeb8d1952, 0xeb27ece5, 0x7d9d3152,
			0xd2102585, 0x3dabff69, 0xf927628e, 0x385984f2, 0x70e226ac,
			0x4f69aeb5, 0xdd4ef8d0, 0x17d69524, 0x48167653, 0x69a340ea,
			0x5ecc3161, 0xe24809b2, 0x64273436, 0xcd8e402f, 0xd2d6633a,
			0x1150bf01, 0x1613ae5e, 0xb8d7cd92, 0x5870206e, 0xa4680b36,
			0x4b698cf9, 0x57aec32f, 0xd4c01477, 0xda8bc259, 0x1faa3e61,
			0x45b299f0, 0x76b85e78, 0xf4ed88a3, 0xebde7410, 0x6f57b05c,
			0xb9b0d27e, 0x608bcf50, 0xc701f534, 0xfc3cb7f6, 0x4ee41552,
			0x3a8f0bfa, 0x6457cdac, 0xa4e6c28e, 0x4c64a3c6, 0x9e96d588,
			0x3f31c05f, 0x608afa65, 0xdbca5fe6, 0x1830a1e4, 0x7c01325c,
			0xbcd198af, 0xb09575d4, 0x85067883, 0x9398fa4b, 0xbb509e25,
			0x3753b43a, 0x9b512998, 0x7c875047, 0xf0b5225d, 0x663c7bd9,
			0x5de63d02, 0xd84928ee, 0xabf3c032, 0x2ba78eac, 0x5b87defa,
			0x2a8dd94d, 0x895efba0, 0xc47c1b58, 0x67cba7d7, 0x48c9f627,
			0x955da846, 0xe8d992be, 0xc29189c9, 0xfdc71783, 0x21f59e5c,
			0x41ce11ec, 0x53f75d55, 0x3cf39ae9, 0x06e42926, 0x89ec6f1f,
			0x9d7df09d, 0x4ffa3639, 0xdec70e3e, 0x15301aa6, 0x8f645e50,
			0x30db1949, 0x6ddd17b8, 0xc79fada0, 0xf55f366e, 0xacaead59,
			0x73821e0f, 0xc9c05565, 0xc7a968ff, 0x83343217, 0xc3b8da12,
			0x75ba4edd, 0x391ddaa2, 0x550321ad, 0x8c068ed7, 0xd54c3fe7,
			0x80ba758a, 0x076dd81d, 0xca2a4b53, 0x15e02ed9, 0x2df6c1d7,
			0xfa8aa819, 0x9e22e464, 0xe882909d, 0x5e6a1041, 0x6efd63e3,
			0x3d8c999a, 0x2b283e94, 0x48cd0faa, 0x5eb02976, 0xe025f917,
			0xaf9a14ca, 0x2b483b11, 0x67f1ff2c, 0x9fdeed63, 0x225192f4,
			0x3a53430d, 0xd02695f9, 0x75cdbe59, 0x3443cd6b, 0xdff1bd0a,
			0xc718361f, 0xfe5df3ef, 0x4a8b5a74, 0x63f1eff5, 0x085c1309,
			0x58e51129, 0xb36159bb, 0x11fdb41e, 0x1d71870f, 0x17a7e68f,
			0xc851d8f7, 0xdda158c6, 0x191d6728, 0xb18c552c, 0x7562b425,
			0x287e1066, 0x493cb409, 0x92874c6f, 0xc296d920, 0x7740927d,
			0x00d6651b, 0x5c6e98c8, 0xafb1896d, 0x41a1ca8a, 0x25baa894,
			0x5e6b03ab, 0x89fc8de9, 0x554365e2, 0x63f40c6c, 0x1246d838,
			0x054a15e6, 0x9b8fdd15, 0x346ae73d };

	// output
	uint32_t Z[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0 };

	mod_exp_array(257, X, E, M, Z);
	assertArrayEquals(257, expected, Z);
}

void test_modExp_8192bit() {
	printf("=== test_modExp_8192bit ===\n");
	uint32_t M[] = { 0x00000000, 0x86ad85ba, 0x6b9fa483, 0x25cb106f, 0xcf6cc989,
			0x911b28f0, 0x1ffd3ef8, 0x30a310db, 0x8851dea4, 0x0b16eba5,
			0x7cb2e8a5, 0x86729373, 0x37af6f23, 0x81fd1e6c, 0x3372378b,
			0xf96a2650, 0x42e123b5, 0x8bd46899, 0x0279f2de, 0x86af6d84,
			0xfbb68d9c, 0x5eba0c14, 0xd07f668d, 0x540bb4e3, 0xfc6fe1ef,
			0xe7200b10, 0x3e83851d, 0x840bc907, 0xb02a53e4, 0x2ce98544,
			0xf1c2ed89, 0x0393d845, 0x8798af50, 0xb643566f, 0xb883f180,
			0x1bc13e4c, 0x65313872, 0x14407175, 0x97edfde2, 0x9cae23ed,
			0x6c191326, 0x60ca5eef, 0x8a20b205, 0x36d3ae1b, 0x2829a6a1,
			0x441eb400, 0x1a64097f, 0x7827120d, 0xd5aee730, 0xb9e4db3e,
			0x08f37694, 0xdd13ae34, 0x61d7d990, 0xda0823d5, 0x998f3344,
			0x9d8f2c46, 0x50e9d076, 0xe9ad6206, 0x2a34f3be, 0xafb54011,
			0xc6c900ba, 0xc0926836, 0x6bd8966c, 0x7eb44909, 0x6423d068,
			0xe1ebaeeb, 0x05b5fbae, 0x5af4fcf8, 0x47fd9f34, 0x324399e0,
			0x72713885, 0xe5ed289d, 0xdf5a4c2a, 0x34b5eccd, 0x730d6ed4,
			0xc06298b2, 0x464aa3ac, 0xab97b92f, 0xf3561b0c, 0x26d1befa,
			0x9b544063, 0x74a2a891, 0x3718a88c, 0x3362334d, 0x7897391f,
			0xe113b4a8, 0x721a812b, 0x13de3112, 0xd5c9d07c, 0x825d00fd,
			0xc551ffcb, 0xe3872dad, 0x0ea2ddda, 0x30e38a98, 0xeee886f2,
			0x851272ee, 0x26ed493e, 0x761a0a42, 0x0977f9ae, 0x15e99d35,
			0x3a58c7f1, 0xbb853700, 0x92981d45, 0xfcf005fa, 0xc903f974,
			0xd6fe5d06, 0x7797ef09, 0x39dfe6dc, 0xca778773, 0x23cd8208,
			0x3794432b, 0xe9b52bd1, 0x669dcc76, 0x7d9ff81b, 0x4edf9564,
			0x461bb932, 0x385c3cf1, 0x6d3aa7f6, 0x68d5ed7f, 0xf5c27db4,
			0xe462abe6, 0x084882a1, 0x9af14607, 0x3e2dd725, 0xc4d64037,
			0x4f94b5d1, 0x240cca02, 0x4b3d4712, 0x8542f595, 0xf6986ece,
			0xf8128c0c, 0xc27dfe0f, 0xf50304fd, 0x6fe1d3a2, 0x5c15ed8e,
			0x56064f73, 0x12bdd761, 0x4ef0c5a3, 0xb8b824cf, 0x5457bf8e,
			0xf2fab63c, 0x8745942a, 0x530d5e8e, 0xfd2d1021, 0xd50cd0ee,
			0x45e20599, 0xd956c899, 0x71a645c8, 0x24e74ebc, 0x00d5f9d6,
			0x4b47d99b, 0x819dc9ac, 0x436d92b9, 0x275d6a87, 0x3759de7e,
			0x51f82a9f, 0x5fb77a15, 0x6827054f, 0xfec842d5, 0x0773368c,
			0x6b810eff, 0xac47d454, 0x1a3f95b2, 0x3ee49234, 0x4470a046,
			0x422e7e36, 0x7199d74b, 0x62d86cc5, 0x17fb0854, 0x8bc0fcb3,
			0x98f67476, 0xa07f8ed0, 0xdd806115, 0xa4452b91, 0x3547baba,
			0xd3bc5863, 0x6566a635, 0xcb23a642, 0xd68a4a15, 0x785e4c3d,
			0x9dc9213b, 0x61a305ec, 0x5538dcf2, 0x8050cd48, 0xe51a0e50,
			0xf0944155, 0x7245b749, 0x789cca13, 0xb3eef27d, 0x876c4376,
			0x2d00d6cf, 0x23236bcf, 0x36459a1a, 0x2f18e804, 0x0a7e718f,
			0xd28ac0c5, 0xb2117e58, 0x7fd9fa32, 0xa2d7c121, 0x403bcc30,
			0x82687fb3, 0x9a83289f, 0xf7e81754, 0x182256c7, 0x212e1645,
			0x7d288176, 0x94b8f048, 0xb406bec1, 0x6685ee15, 0x05d56a42,
			0x14123af9, 0x8476b256, 0xd72ffb48, 0x5086084b, 0x32c15f36,
			0x805bcf3f, 0xa225ac8a, 0xb825bb8e, 0x47f51176, 0x3083266e,
			0xb900bdc7, 0x7fc8517a, 0x7d0533b7, 0xd1c68c2c, 0xaee40865,
			0xcb17d36e, 0xe485ac11, 0x133658cd, 0xb07cb8f0, 0xbc27214b,
			0xeb97236f, 0x46a681aa, 0x5ca3229c, 0xfebc4116, 0x344f278a,
			0x89c29539, 0x1bf5c5fe, 0x37401509, 0x6dba5477, 0x8d46f438,
			0x7ae51ee4, 0x537fd502, 0x0f69fa4e, 0xa2f58c00, 0x1a6fbf0a,
			0x54bfbcb8, 0x03c63af0, 0x3ce5dee1, 0x1d74764c, 0x75643806,
			0x6918820d, 0xaed8caf6, 0x09e78f1f, 0x487758c9, 0x92af5ec8,
			0x8eaf83c9, 0x924dc0eb };
	uint32_t X[] = { 0x00000000, 0x91ee2fce, 0xd990babd, 0x48cfce09, 0x46f6fb40,
			0xbdbcf732, 0xdfd66017, 0x32e73806, 0x21b5d9a7, 0x61c34841,
			0xc1607abe, 0x877f92ea, 0x25c46ad9, 0x0a6a918e, 0xd15682c1,
			0x0eb401d4, 0x6b00237a, 0x99342f43, 0x8853777f, 0x3cab60c0,
			0x6f111c44, 0x0f98d177, 0x7beb1f66, 0x666f952f, 0x630dee77,
			0xb1076441, 0x66ba385a, 0xa3e40dc8, 0x7e6f25fd, 0xc065f395,
			0x2e02ec62, 0x3bb628b1, 0x6dfa8cf3, 0x9ee01b61, 0x436ca2ab,
			0x2d7da420, 0x32f0f7c7, 0xb9c413c9, 0x43b47153, 0xc5ce2646,
			0x34ff1b00, 0xbdf50ac9, 0xa3ff3e59, 0xcf2c2fa7, 0xbf303804,
			0xf1b3c5d8, 0x4526f8b3, 0xa18de2d2, 0xdbfc9b2a, 0xf090b196,
			0xc7ccb848, 0x3131b895, 0xaf7f9400, 0xd2292396, 0x76eab15e,
			0x2fae6be1, 0xef3aa040, 0xc13d0c7e, 0xacbf226a, 0x8622f50d,
			0x38accb62, 0x3ea13ce5, 0xac9de28a, 0x9ab2a5d9, 0x5c40d716,
			0x73461a32, 0x5d5e4852, 0x2ce7f47c, 0x0e161969, 0x90482534,
			0x05b1a961, 0xce432fbd, 0x8bcbee70, 0x72d73000, 0x5eaae743,
			0x730c1a8e, 0x82c5fbcf, 0x35a458b8, 0x020f63b7, 0xe1c7fceb,
			0xafd9b6b8, 0xea8fad68, 0x2f33a7d4, 0x72314497, 0x3122fe7f,
			0xd681ba61, 0x9a1b71e3, 0x416d7d76, 0x378667a8, 0x13614b76,
			0x56202e44, 0x71081eab, 0x9e98b4e3, 0xa6071d0f, 0xec5846c5,
			0x26a7629d, 0xe5d6f112, 0x82050ead, 0x244f1090, 0xfd999935,
			0x3efd707b, 0x02bb1884, 0x22ae83c8, 0xf09fc654, 0x2108c3c5,
			0x61f0cd4d, 0x8fdc63fb, 0x37ad0cdb, 0x86ce43be, 0x9a140b69,
			0x2cbaf2ae, 0xf68e4a24, 0xbb393d58, 0x7419573b, 0x8ed9a742,
			0xf348cd0a, 0x299e5cc9, 0x73f3faa0, 0x91cf4de4, 0x0dd08963,
			0x1f18d2fb, 0xe986b56e, 0x29bf4808, 0xd73aedba, 0xf0e6366c,
			0x7bfa2897, 0xa5e3aee4, 0x95205dc9, 0x5531af73, 0x9ea40090,
			0xa881f170, 0xcced6400, 0x9b1cbd26, 0x02f94690, 0x5ec17402,
			0x723723e5, 0x4d7d6139, 0xb479e40c, 0xc374d2cd, 0x2637c121,
			0x2899b8cd, 0xc06b4488, 0x3895356a, 0x10a0d95d, 0x9d3dcfda,
			0x5421efb3, 0x62c3c59f, 0xbbcafbb1, 0x7a67c318, 0xc041493e,
			0x337e8494, 0x71291002, 0x55f4d850, 0x42698ec0, 0x6d3bcea1,
			0xf4009450, 0x2e1aecde, 0x37040b4a, 0x4f2799e3, 0xa5d71832,
			0x5eb96577, 0x6a2be15f, 0x2c4ec022, 0x8011cf7a, 0x4a18bdfc,
			0xec514338, 0x3e85cc1c, 0xc8d4251d, 0xcec76286, 0x821c623e,
			0xfddc00ca, 0xbd458f30, 0x69c28d23, 0x92c11af2, 0x39912502,
			0x0c2fb9c8, 0xea08eda5, 0x8761b052, 0x27520ddc, 0x54b2b6bd,
			0x8a6124b2, 0x5787201c, 0x4c0f9fa9, 0x2552dd33, 0xbaf883f6,
			0x2fe81d52, 0x4700ea40, 0x3f3631b5, 0x8152a853, 0xcd225651,
			0x3f533857, 0xdc8f2504, 0x5683b52b, 0x91fea340, 0xd09ab0f3,
			0x7f742d60, 0x9a70b4a4, 0x61e2b8e3, 0x73b6979c, 0x110a27b2,
			0x4ec92644, 0x74750fce, 0xafb9906b, 0x4a810a62, 0x9f543b2e,
			0x197d416c, 0xfebdbec4, 0x4673396a, 0x8a5c9b31, 0xae3b8072,
			0x0b6fe9ae, 0x15300640, 0xb83853ae, 0x2ff3c196, 0x6a245e27,
			0xd09fc66a, 0x9d07b333, 0x912f3b83, 0x1010fd25, 0x58e4e390,
			0xeeb97c27, 0x5655996c, 0xa34e6f13, 0xbe46862f, 0x14fc1d3b,
			0x85c293f7, 0xe2ff5268, 0x4121d6c1, 0x37fddab9, 0x9be68812,
			0x722c387a, 0xaaa9e1f4, 0x7de63d9f, 0x45958401, 0x2abab962,
			0xcad34223, 0x48cdb68d, 0x4a16786f, 0xa8934ada, 0x0cb28a9c,
			0x7e8ba2fd, 0xa092a911, 0x57507522, 0x2654c0ae, 0x10101e50,
			0x6e4d473c, 0xb6cd39b1, 0x7f7fe6db, 0x3c2fad07, 0x5d2a8940,
			0x876a91ba, 0xc5583486, 0xca4745ee, 0x4b3bdfc6, 0x4a50f9b7,
			0x4819d4ed, 0xc0e60bf9 };
	uint32_t E[] = { 0x00000000, 0xa7952e85, 0x43c27889, 0x8fdffd02, 0x9207c590,
			0xbd06bdca, 0x463f68f1, 0xb859afef, 0xa3cceecf, 0x6bf1fb58,
			0xf9e78062, 0xbf48e3b5, 0xb9f10f8d, 0xe13902aa, 0x34cbeb7c,
			0xb8459d53, 0xfef2293d, 0x6666c887, 0xab619bab, 0x1e7eafc6,
			0xe46b53de, 0x6b8e501f, 0x36367216, 0xf0dc4d4e, 0x69385748,
			0xf8e74efd, 0x13df7c40, 0x7ecb872b, 0x1a20bafa, 0x7679b6c3,
			0x7dac3a84, 0xc35a7f0f, 0x722e76ca, 0x9aaeb9ce, 0x6546a7ab,
			0x63cad8bf, 0x7ca1c7b3, 0xf6d8727a, 0x5e2642a2, 0xca207fba,
			0x9bca1605, 0xf7ec3c34, 0x356a6c47, 0xac31f740, 0x70e1e5fb,
			0xe79bc86e, 0xe8c765b3, 0x9933636c, 0x6fae593e, 0x8af6cfb9,
			0x395d6336, 0x4c86e395, 0x55d0315c, 0xa12beea8, 0x42db1aa6,
			0xe0f1beff, 0x567a053d, 0x7dfd4a9a, 0xe9c010ea, 0x170c0167,
			0x986b39a8, 0x45e4fbc8, 0xf6f2109b, 0xed9fbde5, 0xb5fe9ce8,
			0xa818db8b, 0xa34a9d87, 0x0fcd04b5, 0xecb82b19, 0x77f3d48d,
			0xedd53581, 0x698396e1, 0xb9e6c9bd, 0x9dbf5756, 0x9e5dedaa,
			0x2c3551ab, 0x8c53085c, 0x9ac48172, 0x7ff697a5, 0x313d1809,
			0x05812483, 0x41c46ea7, 0xb29a0b52, 0x9b88f14c, 0x9c04b395,
			0x2b2e1fe7, 0xd420405b, 0xdf2c3dcb, 0xf40f026a, 0x2a58acd9,
			0xceb903aa, 0xc1eca78f, 0x595a2356, 0xd2d86958, 0x8bc0117b,
			0xde2b5361, 0xe6599506, 0xa88fb08c, 0x3e8fd04d, 0x8e0c1777,
			0x2eb31d8d, 0x60c52d77, 0xa5e34552, 0xd0fbae80, 0xed03a1ed,
			0x9a34b40c, 0x790198cc, 0x792bb5f2, 0x64507faf, 0x452ab8b1,
			0x8cd4ae9a, 0x1c101f92, 0x52198813, 0xd27e288f, 0xae970221,
			0x3c09f4ad, 0x17a4fde5, 0xa12f2169, 0x6772ab4e, 0x9cac3e2e,
			0x84b31d5b, 0x127dc3eb, 0x942a2e09, 0xc8b27e25, 0x2850a5f7,
			0xce6fe8c0, 0xe7f349cd, 0xd554b87c, 0x887edb54, 0x505b06b6,
			0xdecd98cf, 0x9382672a, 0xcc6717ed, 0x149939b5, 0xe6e70e3e,
			0xf2d2b37a, 0x883734b5, 0x5c257cd2, 0x6bde4f5d, 0x87779582,
			0xfeff0b41, 0x20c33069, 0x1fee7b40, 0x65ab5fd0, 0xe8bc307e,
			0x4563baee, 0xf037a381, 0x82540003, 0x2380e427, 0x826bee8f,
			0xe8ac8ff6, 0x78af1805, 0x05feba21, 0x1e784522, 0x748bd9c0,
			0x40939ab3, 0xf647174c, 0x7202781e, 0x0797b10c, 0xa3315073,
			0xbe3e438d, 0x01ab5dc5, 0x8de96d1e, 0x3a2ed228, 0x7e0476d9,
			0xa77cb758, 0x6e738b80, 0x36c93924, 0x67cb7b44, 0x23d67f3b,
			0xe8403a2f, 0x8ac8673a, 0x9fcb4250, 0xcdcb6a72, 0x49bee847,
			0x90125f27, 0xb0ee1e58, 0x844690bc, 0xf6b509d2, 0x6b6154fb,
			0x4be41421, 0x3f2bd464, 0xddafe08e, 0x3fd8806f, 0x9a2098b6,
			0x9a6f0687, 0x265f2496, 0xffcd3cf6, 0x10bac8d1, 0x76d7b1c9,
			0x86192aff, 0xce30e7bd, 0xb123ab70, 0x639fbfbd, 0xdfe038dc,
			0xfb61dfec, 0xd21110e3, 0xc308463d, 0xa782120c, 0x7b9c183c,
			0x79d4621f, 0x8f5d3493, 0x1d492f97, 0x3821e047, 0x7c8771e1,
			0xc41690c1, 0x27854103, 0x06db0bd8, 0xb965fb59, 0x6a43f58f,
			0x369f1f39, 0x94c2a165, 0x89be3652, 0x183319db, 0x96873032,
			0xbff01c2e, 0x5926ddeb, 0x44a74881, 0xe7634087, 0x6ea90b49,
			0x7683ec18, 0x07657a35, 0x3e972c36, 0xc2983387, 0xf68aacd9,
			0x133a091b, 0xfbeefd13, 0xac7b6749, 0xc7041ae4, 0xe23a75fd,
			0x63190ba6, 0x6639d9c9, 0xb3b4e809, 0xb1ee6dca, 0x62499ce6,
			0x40412ee2, 0x854fc87c, 0x4baab3ae, 0x89c90aec, 0xea66edd3,
			0xb6f3d7d0, 0xd6440bad, 0x0d5a47ad, 0x91c74c6b, 0xadac55a4,
			0x59c15d9a, 0x89569141, 0xcd68c6fe, 0x2e3bcdd0, 0x75ec297d,
			0x5acb788b, 0x1dfc95a6, 0x6e45e3fa, 0x7f70be28, 0x30aaba09,
			0x560dab05, 0x0296f481 };
	uint32_t expected[] = { 0, 0x07fa84f1, 0xf881cf0c, 0xc7018f6f, 0x690e8edd,
			0xc3f56d42, 0x19b9b8cc, 0xc5e34956, 0x63213190, 0x369dbc29,
			0x5d7f41e0, 0x094e1297, 0x4f1a99ce, 0x31e2303b, 0x217b40b0,
			0x39a06209, 0x7ba560cf, 0x88ca8bfe, 0xb6642828, 0x107b1f6b,
			0xa31234c0, 0x5768ac5d, 0xccf70351, 0x53fe2ac3, 0x942beb11,
			0xe46a3cbe, 0xca77e33f, 0x5d942c08, 0xab953d85, 0x88501b15,
			0x558b9439, 0xa13f9f21, 0xfa740701, 0x5fcbc2cd, 0x81e6dbe1,
			0x4a115abc, 0x7e96bb21, 0x2c932ec4, 0xd32d4af9, 0x60aaef2f,
			0xd8ef568e, 0xcfeb2f35, 0x0568c228, 0x436cdc37, 0xac7b0ffb,
			0x4e517b91, 0x37a31fdd, 0xba397498, 0x13f3d5db, 0x08a4f1be,
			0x1ee258f0, 0x8e8d8fa7, 0x77a01aef, 0x96af8a67, 0xf2581061,
			0x689d8542, 0x6c6413ff, 0x09faa0be, 0x6b761805, 0x5ad03797,
			0x47ca18d2, 0x82a4365c, 0x43217ee4, 0xa2e779e4, 0x2b0973fe,
			0x3e6cc83d, 0xde7c1220, 0x929c13de, 0x25139b18, 0x6cdf03ec,
			0xca6a46dd, 0xeb6f0bce, 0x6da79445, 0xfa50d6b4, 0xbe971cd2,
			0xe63ef642, 0xbd7137cf, 0x2eae23b9, 0x056a8d02, 0x33349ad3,
			0xe726aebe, 0xecd6a029, 0x68b99843, 0xba259392, 0x01f2ed75,
			0xd70399ae, 0xd7bee4b1, 0x434dd0d3, 0x32e2a7a6, 0x324e1b7a,
			0xecad8d52, 0xb59d22c8, 0x40d19fc1, 0x7fca09c3, 0x491d3c61,
			0x0ba88028, 0x87f9611d, 0x9b839d54, 0x4225e3ed, 0x200180c6,
			0xb58ae6d3, 0xf1191ea7, 0x0a53b0dd, 0xe3e82bc5, 0xe614bcc7,
			0xd9538203, 0x4ce8ffd2, 0xe5d7284d, 0x0407d013, 0xaf5a6400,
			0x27d36e7d, 0x49c5e041, 0xd9333062, 0xe081189d, 0x5f5004fc,
			0xe09f503d, 0xa0b7471c, 0x08f12a3e, 0x2182927c, 0x2ee0f1ef,
			0x9c9d950d, 0x3030d6a8, 0xc06a9efe, 0x6deb1414, 0x48c4a93c,
			0xb87b3a89, 0x4fef01e8, 0xc855e40d, 0xd80e90d1, 0x2f6c343d,
			0x3dbea90c, 0xdee4d84b, 0xba503f3b, 0x8093472c, 0x93d37c66,
			0xed0e4659, 0xd2128503, 0x1d2b15bc, 0x48739dff, 0x5878e164,
			0x15924708, 0x9dabdbc2, 0x89504225, 0x72f47a0e, 0x56904a99,
			0x397bc9a2, 0x8021f532, 0x7b884465, 0xe9819218, 0xff372b35,
			0xb6b1e620, 0x3bf856c6, 0x71276ff8, 0xa7507908, 0xe91bc621,
			0x96b90fad, 0x7b1e2c1b, 0x1aa26f51, 0x0334abe7, 0xeb70b441,
			0xe0bb5fc2, 0xca88ea9a, 0x43ae0ef0, 0x26e1b4ef, 0xa7d9ea8c,
			0x265577af, 0x473e13e9, 0x38f013ad, 0x749c94e7, 0x70489a33,
			0xa93382c0, 0xba623a10, 0x9902054d, 0x55029834, 0xc2bab249,
			0x0f70bb25, 0x7918915b, 0x69277f4f, 0x9bd9766e, 0xb5103b86,
			0xc687927d, 0xb164c3de, 0x3f8b096c, 0xe69737cb, 0xf465582c,
			0xe11a33aa, 0xc854d343, 0x35feec27, 0x94d36b4c, 0x47b5a6b1,
			0xbdcf624a, 0x51edcc6c, 0x00a4fe60, 0xd7ad05b4, 0xba278f28,
			0xde97f809, 0xf53dfbe0, 0xf313f37b, 0xc6ff2769, 0x36c32341,
			0xc5b9810b, 0xb4b745c0, 0x444239e8, 0xfbaa71fc, 0x42c795e2,
			0xa7769079, 0x3a20ddfa, 0x8d0680f1, 0xcc0c3abc, 0x44f36126,
			0x4de23984, 0x5ace4020, 0x210d39e0, 0x72a27816, 0x5c99f78f,
			0xf2f6984a, 0x625c2caa, 0x7773bfaa, 0xd824c3b9, 0xc5b89577,
			0xa5719784, 0xee44506d, 0x4fa62cd3, 0x165295e1, 0xc21ba918,
			0x17fdf3a3, 0x796de61e, 0xe6cb5f1c, 0x0922e5fd, 0xf639d1c2,
			0xe4ec8a64, 0x3f08d5e2, 0x73468a85, 0x056daf11, 0x8cc2153e,
			0xd57b543e, 0x0f9bc965, 0xe5e48e13, 0x96c17541, 0x2c65a0cb,
			0x6740ce26, 0xcb5abfde, 0x41877fdb, 0x1235d491, 0x42c63eeb,
			0x0e91271f, 0xa2fdc9cd, 0xd924a96e, 0x3a008d8a, 0xad56e22f,
			0x7172863d, 0xf84de00f, 0xd8135175, 0x282055b0, 0x3c4447a8,
			0x030f6021, 0xc649c49f };

	size_t length = 1 + ((8192 / 8) / sizeof(uint32_t));

	//output
	uint32_t *Z = calloc(length, sizeof(uint32_t));

	mod_exp_array(257, X, E, M, Z);
	assertArrayEquals(257, expected, Z);
}

void montgomery_array_tests(int bigtests) {
  // Sub function tests.
  testShiftRight();
  testAdd();
  testSub();
  test_montgomery_one_item_array();
  test_montgomery_modulus();

  // modexp tests.
  test_montgomery_modexp();

  // Fairly big.
  test_modExp_4096bit_e65537();
  test_modExp_8192_e65537();

  // Bigtests.
  if (bigtests) {
    test_modExp_8192bit();
  }
}
