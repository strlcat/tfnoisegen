#ifndef _THREEFISH_CIPHER_CORE_HEADER
#define _THREEFISH_CIPHER_CORE_HEADER

#ifndef _THREEFISH_CIPHER_DEFINITIONS_HEADER
#error Threefish definitions header is required! Include tfdef.h first.
#endif

#define ROL(x, s, max) ((x << s) | (x >> (-s & (max-1))))
#define ROR(x, s, max) ((x >> s) | (x << (-s & (max-1))))

#define KE_MIX(x, y, k1, k2, sl)				\
	do {							\
		x += k1;					\
		y += x;						\
		y += k2;					\
		x = ROL(x, sl, TF_UNIT_BITS);			\
		x ^= y;						\
	} while (0)

#define BE_MIX(x, y, sl)					\
	do {							\
		x += y;						\
		y = ROL(y, sl, TF_UNIT_BITS);			\
		y ^= x;						\
	} while (0)

#define KD_MIX(x, y, k1, k2, sr)				\
	do {							\
		x ^= y;						\
		x = ROR(x, sr, TF_UNIT_BITS);			\
		y -= x;						\
		y -= k2;					\
		x -= k1;					\
	} while (0)

#define BD_MIX(x, y, sr)					\
	do {							\
		y ^= x;						\
		y = ROR(y, sr, TF_UNIT_BITS);			\
		x -= y;						\
	} while (0)

enum tf_rotations {
	TFS_KS01 =  7, TFS_KS02 = 25, TFS_KS03 = 19, TFS_KS04 =  7,
	TFS_BS01 =  5, TFS_BS02 = 27, TFS_BS03 = 26, TFS_BS04 =  6,
	TFS_BS05 = 14, TFS_BS06 = 11, TFS_BS07 = 24, TFS_BS08 = 18,
	TFS_BS09 =  9, TFS_BS10 = 24, TFS_BS11 =  6, TFS_BS12 =  7,
};

#endif
