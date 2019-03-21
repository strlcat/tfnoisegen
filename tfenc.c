#include "tfdef.h"
#include "tfcore.h"

#define PROCESS_BLOCKP(x,k1,k2,k3,k4,k5,k6)						\
	do {										\
		KE_MIX(Y, X, k1 + k2, k3, TFS_KS01);					\
		KE_MIX(T, Z, k4 + x, k5 + k6, TFS_KS02);				\
											\
		BE_MIX(X, T, TFS_BS01); BE_MIX(Z, Y, TFS_BS02);				\
		BE_MIX(X, Y, TFS_BS03); BE_MIX(Z, T, TFS_BS04);				\
		BE_MIX(X, T, TFS_BS05); BE_MIX(Z, Y, TFS_BS06);				\
	} while (0)

#define PROCESS_BLOCKN(x,k1,k2,k3,k4,k5,k6)						\
	do {										\
		KE_MIX(Y, X, k1 + k2, k3, TFS_KS03);					\
		KE_MIX(T, Z, k4 + x, k5 + k6, TFS_KS04);				\
											\
		BE_MIX(X, T, TFS_BS07); BE_MIX(Z, Y, TFS_BS08);				\
		BE_MIX(X, Y, TFS_BS09); BE_MIX(Z, T, TFS_BS10);				\
		BE_MIX(X, T, TFS_BS11); BE_MIX(Z, Y, TFS_BS12);				\
	} while (0)

void tfng_encrypt_rawblk(TFNG_UNIT_TYPE *O, const TFNG_UNIT_TYPE *I, const TFNG_UNIT_TYPE *K)
{
	TFNG_UNIT_TYPE X, Y, Z, T;
	TFNG_UNIT_TYPE K0, K1, K2, K3;
	TFNG_UNIT_TYPE K4, T0, T1, T2;

	X = I[0]; Y = I[1]; Z = I[2]; T = I[3];

	K0 = K[0]; K1 = K[1]; K2 = K[2]; K3 = K[3];
	K4 = K[4]; T0 = K[5]; T1 = K[6]; T2 = K[7];

	PROCESS_BLOCKP( 1,K1,T0,K0,K3,K2,T1);
	PROCESS_BLOCKN( 2,K2,T1,K1,K4,K3,T2);
	PROCESS_BLOCKP( 3,K3,T2,K2,K0,K4,T0);
	PROCESS_BLOCKN( 4,K4,T0,K3,K1,K0,T1);

	PROCESS_BLOCKP( 5,K0,T1,K4,K2,K1,T2);
	PROCESS_BLOCKN( 6,K1,T2,K0,K3,K2,T0);
	PROCESS_BLOCKP( 7,K2,T0,K1,K4,K3,T1);
	PROCESS_BLOCKN( 8,K3,T1,K2,K0,K4,T2);

	PROCESS_BLOCKP( 9,K4,T2,K3,K1,K0,T0);
	PROCESS_BLOCKN(10,K0,T0,K4,K2,K1,T1);
	PROCESS_BLOCKP(11,K1,T1,K0,K3,K2,T2);
	PROCESS_BLOCKN(12,K2,T2,K1,K4,K3,T0);

	O[0] = X + K3; O[1] = Y + K4 + T0; O[2] = Z + K0 + T1; O[3] = T + K1 + 18;
}
