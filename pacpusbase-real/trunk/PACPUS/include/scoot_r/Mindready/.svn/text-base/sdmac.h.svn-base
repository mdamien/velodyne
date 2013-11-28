/* sdmac.h - General macro */

/* Copyright(c) 2000, Solution Mindready Inc. All rights reserved. */

/*
Basic data types and defines used by programmers.
*/

#ifndef __sdmach
#define __sdmach

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#if defined(WIN32)

	/* Macro definition for embed SdeNet2 IOCTL control codes to the Windows NT own	*/
	/* IOCTL control codes. 														*/
	#define SDNET2_CTL_CODE(_CTL_CODE) \
		( \
			((FILE_DEVICE_UNKNOWN) << 16) | \
			((FILE_READ_ACCESS | FILE_WRITE_ACCESS) << 14) | \
			((_CTL_CODE-1000) << 2) | (METHOD_NEITHER) \
		)


#endif /* WIN32 */

#if defined(_KRNL32_)

	/* Macro definition for extract SdeNet2 IOCTL control codes from		*/
	/* the Windows NT own IOCTL control codes.								*/
	#define SDNET2_XCTL_CODE(_CTL_CODE) \
			( ((_CTL_CODE << 18) >> 20) +1000 )


#endif /* _KRNL32_ */


#if defined(__LYNX__)
	
	#define SDNET2_XCTL_CODE(_CTL_CODE) \
			_CTL_CODE

#endif	/* defined(__LYNX__) */


#if defined(__QNXNTO__)
	
	#define SDNET2_XCTL_CODE(_CTL_CODE) \
		( ( ((UINT32) _CTL_CODE) & ((UINT32) 0x0000FFFF) ) - ((UINT32) 0x00001000) )

#endif	/* defined(__QNXNTO__) */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsdtypesh */
