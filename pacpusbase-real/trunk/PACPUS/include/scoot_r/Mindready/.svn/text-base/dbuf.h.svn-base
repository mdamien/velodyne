/* dbuf.h - Dynamic Buffer Module */

/* Copyright(c) 2001, Mindready Solutions Inc. All rights reserved. */

/*
 * Modification History
 * ----------------------------------------------------------------------------
 * $Log: /Common/Design/Src/dbuf/Dev/VxWorks/main/src/dbuf.h $
 * 
 * 17    8/14/01 15:46 Blc
 * Renamed both watermark functions.
 *
 * 16    8/13/01 11:29 Blc
 * Commented dbufPoolCb_t.
 *
 * 15    8/10/01 10:04 Blc
 * Added provision for watermarks: two functions to set and get
 * watermarks, a typedef for the callback, a struct to hold the data, and
 * new data members in the dbufPool_s. No functional change is in effect
 * since no code is testing for watermarks yet.
 *
 * 14    8/01/01 11:18 Blc
 * Added missing comments to describe various services. Fixed a few typos.
 *
 * 13    6/28/01 11:05a Jfha
 * Add new functions : dbufQueryPoolSize, dbufInitPool
 *
 * 12    6/12/01 16:25 Blc
 * Replaced uint16_t and uin32_t with size_t. Changed dbufConcat to return
 * the new dbuf.
 *
 * 11    5/08/01 13:45 Blc
 * Renamed dbufValidatePool to dbufIsPoolValid
 *
 * 10    5/07/01 13:58 Blc
 * Added a function to validate a pool.
 *
 * 9     5/04/01 9:38 Blc
 * Updated file header. Spell checked comments. Fixed typos.
 * ----------------------------------------------------------------------------
 * $NoKeywords: $
 */

#ifndef __INCdbufh__
#define __INCdbufh__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* includes */
#include <stdbool.h>    /* bool */
#include <stddef.h>     /* size_t */


/* pool options */
#define DBUF_PHYSICAL_MEMORY    (2)
#define DBUF_CACHE_SAFE_MEMORY  (4)

#define DBUF_QUADLET_ALIGN      (8)
#define DBUF_16BYTE_ALIGN       (16)
#define DBUF_1K_ALIGN           (32)
#define DBUF_2K_ALIGN           (64)
#define DBUF_4K_ALIGN           (128)

/* supported offset value */
#define DBUF_OFFSET_BEGIN   (1)
#define DBUF_OFFSET_END     (2)


/* error code */
#define ERR_INVALID_PARAM           (1)
#define ERR_ALLOC_FAILED            (2)
#define ERR_INVALID_OFFSET          (3)
#define ERR_INSUFFICIENT_BUFFER     (4)
#define ERR_INVALID_SEGNO           (5)
#define ERR_POOL_EMPTY              (6)


/* typedefs */
typedef struct dbufPool_s dbufPool_t;
typedef struct dbuf_s dbuf_t;

/* Prototype of the function called when a pool low/high watermark is reached. */
typedef void dbufPoolCb_t
(
	dbufPool_t *pPool,					/* Pool whose matermark is reached. */
	void *pContext						/* User context supplied to dbufSetPoolWaterMarks() */
);

/* prototype declarations */

/* dbufCreatePool - Create a dynamic buffer pool */
dbufPool_t *dbufCreatePool
(
    size_t bufSize,                     /* max size of each buf in the pool */
    size_t nbBuf,                       /* number of buffer to alloc */
    int flags                           /* dma, cache safe */
);

/* dbufSetPoolWatermarks - Activate and set the low/high watermarks mechanism. */
int dbufSetPoolWatermarks
(
	dbufPool_t *pPool,					/* Pool whose whatermarks are being set */
	dbufPoolCb_t *pLCallback,			/* Function to call when the low watermark is reached. */
	void *pLContext,					/* For use with the low wartermark callback. */
	int lowWaterMark,					/* Value of the low wartermark. */
	dbufPoolCb_t *pHCallback,			/* Function to call when the high watermark is reached. */
	void *pHContext,					/* For use with the high wartermark callback. */
	int highWaterMark					/* Value of the high wartermark. */
);

/* dbufGetPoolWatermarks - Returns the current setting of all watermarks related values. */
int dbufGetPoolWatermarks
(
	const dbufPool_t *pPool,			/* Pool whose whatermarks are being query. */
	dbufPoolCb_t **ppLCallback,			/* Returns the function called when the low watermark is reached. */
	void **ppLContext,					/* Returns the user context matching the low wartermark callback. */
	int *pLowWaterMark,					/* Returns the current value of the low wartermark. */
	dbufPoolCb_t **ppHCallback,			/* Returns the function called when the high watermark is reached. */
	void **ppHContext,					/* Returns the user context matching the high wartermark callback. */
	int *pHighWaterMark					/* Returns the current value of the high wartermark. */
);

/* dbufDestroyPool - Destroy a buffer pool */
void dbufDestroyPool
(
    dbufPool_t *pPool                   /* The pool Identifier */
);

/* dbufGetAvailableCount - return number of dynbuf available */
int dbufGetAvailableCount
(
    dbufPool_t *pPool                   /* The pool Identifier */
);

/* dbufAlloc - allocate a dynamic buffer */
dbuf_t *dbufAlloc
(
    dbufPool_t *pPool,                  /* The pool Identifier */
    size_t bufSize,                     /* size of the dynbuf to create */
    size_t headerOffset                 /* size of the header to add at start */
                                        /* of the dynamic buffer */
);

/* dbufMultiAlloc - Allocate a chain of dynamic buffers */
dbuf_t *dbufMultiAlloc
(
    dbufPool_t *pPool,                  /* The pool Identifier */
    size_t nbBbuf                       /* number of dynbuf to alloc */
);

/* dbufFree - Return the dynamic buffer to its pool */
void dbufFree
(
    dbuf_t *pDynBuf                     /* Dynamic buffer to return to the pool */
);

/* dbufAddSpace - adds space for a number of bytes in a dynamic buffer */
int dbufAddSpace
(
    dbuf_t *pDynBuf,                    /* dynamic buffer to add data to */
    size_t offset,                      /* offset in the dynamic buffer data */
    size_t nbBytesToAdd                 /* number of bytes to add */
);

/* dbufDelSpace - deletes a number of bytes from a dynamic buffer */
int dbufDelSpace
(
    dbuf_t *pDynBuf,                    /* dynamic buffer to del data from */
    size_t offset,                      /* offset in the dynamic buffer data */
    size_t nbBytesToDel                 /* number of bytes to del */
);

/* dbufGetDataPtr - gets a pointer to the data part of a dynamic buffer */
void *dbufGetDataPtr
(
    dbuf_t *pDynBuf,                    /* dynamic buffer to get data from */
    size_t offset,                      /* offset in the dynamic buffer data */
    size_t nbBytesToGet                 /* number of bytes to get from dynamic buffer */
);

/* dbufCopyDataToBuf - Copy data from user buffer to dynamic buffer */
int dbufCopyDataToBuf
(
    const void *pSrc,                   /* src user buffer */
    dbuf_t *pDynBuf,                    /* dest dynamic buffer */
    size_t offset,                      /* dest offset in dynamic buffer */
    size_t nbBytesToCopy                /* number of bytes to copy */
);

/* dbufCopyDataFromBuf - Copy data from dynamic buffer to user buffer */
int dbufCopyDataFromBuf
(
    const dbuf_t *pDynBuf,              /* src dynamic buffer */
    size_t offset,                      /* src offset in the dynamic buffer */
    void *pDest,                        /* dest user buffer */
    size_t nbBytesToCopy                /* number of bytes to copy */
);

/* dbufSpawn - Alloc a dynamic buffer that point on another dynbuf data */
dbuf_t *dbufSpawn
(
    dbufPool_t *pPool,                  /* Pool to be use for this operation */
    dbuf_t *pDynBuf,                    /* Source dynamic buffer */
    size_t offset,                      /* Offset in the dynamic buffer */
    size_t size                         /* Number of bytes to get */
);

/* dbufDuplicate -  Create a copy of a spawned dynbuf */
dbuf_t *dbufDuplicate
(
    dbufPool_t *pPool,                  /* Pool to be use for this operation */
    dbuf_t *pDynBuf                     /* Source spawned dynamic buffer */
);

/* dbufConcat - concatenate 2 dynamic buffers */
dbuf_t *dbufConcat
(
    dbuf_t *pBegin,                     /* First DynBuf */
    dbuf_t *pEnd                        /* DynBuf appended */
);

/* dbufSplit - Fragment a dynamic buffer onto 2 separates ones */
dbuf_t *dbufSplit
(
    dbuf_t *pDynBuf,                    /* The dynamic buffer is split in two patrs.
                                           After the operation Dynbuf is truncated
                                           after the segment segNo */
    size_t segNo                        /* The segment number where the dynamic buffer
                                           will be separated */
);

/* dbufGetLength - returns the total length of all segments of a dynamic buffer */
int dbufGetLength
(
    dbuf_t *pDynBuf                     /* dynamic buffer to get length from (I) */
);

/* dbufGetSegCount - Return the number of segment in the dynamic buffer */
int dbufGetSegCount
(
    dbuf_t *pDynBuf                     /* The dynamic buffer being measured */
);

/* dbufGetSegLength - returns the length of the specified segment from a dynamic buffer */
int dbufGetSegLength
(
    dbuf_t *pDynBuf,                    /* The dynamic buffer being measured */
    size_t segNo                        /* The number of the segment to measure.
                                           The first segment starts with 0 */
);

/* dbufGetSegDataPtr - Returns a pointer to the data section of the specified segment. */
void *dbufGetSegDataPtr
(
    dbuf_t *pDynBuf,                    /* src dynamic buffer */
    size_t segNo                        /* segment number pDynBuf */
);

/* dbufIsContiguous - check if data in a dynamic buffer is contiguous */
bool dbufIsContiguous
(
    dbuf_t *pDynBuf                     /* The dynamic buffer use for the operation */
);



/*
 *      Mindready Internal use only.
 */

/* dbufGetNextDataPtr - Get next data pointer and size */
int dbufGetNextDataPtr
(
    dbuf_t **ppDynBuf,                  /* a pointer to a temp dynbuf pointer */
    void **ppBuf,                       /* a pointer to the buffer pointer */
    size_t *pSize                       /* a pointer to the size variable */
);

/* dbufGetPhysicalAddress - Get the physical of the supplied virtual address */
void *dbufGetPhysicalAddress
(
    dbuf_t *pDynBuf,                    /* a pointer to a temp dynbuf pointer */
    void *vaddr                         /* a virtual address */
);

/* dbufSetPoolContext - Set the user context of a pool */
int dbufSetPoolContext
(
    dbufPool_t *pPool,                  /* a pointer to a pool */
    void *pContext                      /* a user context pointer */
);

/* dbufGetPoolContext - Get the user context (only one of the 2 params can be valid) */
void *dbufGetPoolContext
(
    dbufPool_t *pPool,                  /* a pointer to a pool */
    dbuf_t *pDynBuf                     /* a pointer to a dynbuf */
);

/* dbufSetContext - Set the user context of a DynBuf */
int dbufSetContext
(
    dbuf_t *pDynBuf,                    /* a pointer to a dynbuf */
    void *pContext                      /* a user context pointer */
);

/* dbufGetContext - Get the user context of a DynBuf */
void *dbufGetContext
(
    dbuf_t *pDynBuf                     /* a pointer to a dynbuf */
);

/* dbufSetDataPtr - Sets the data pointer to pre-allocated buffer */
int dbufSetDataPtr
(
    dbuf_t *pDynBuf,                    /* dynamic buffer to get data from */
    void *bufAddr,                      /* address of the pre-allocated data */
    size_t bufSize                      /* size of buf pointed by bufAddr */
);


/* dbufFindLast - Get the last dynbuf of a chained list of dynbuf */
dbuf_t *dbufFindLast
(
    dbuf_t *pDynBuf                     /* a pointer to a dynbuf */
);


/* dbufIsPoolValid - Verifies the integrity of the specified pool. */
bool dbufIsPoolValid
(
    const dbufPool_t *pPool             /* Points to the pool to validate */
);

/* dbufQueryPoolSize - Computes the required pool size to fit the specified number of dynamic buffers. */
size_t dbufQueryPoolSize
(
    size_t bufSize,                     /* max size of each buf in the pool */
    size_t nbBuf,                       /* number of buffers to alloc */
    int flags                           /* dma, cache safe */
);

/* dbufInitPool - Initializes a dynamic buffer pool using a specified memory buffer. */
dbufPool_t *dbufInitPool
(
    size_t bufSize,                     /* max size of each buf in the pool */
    size_t nbBuf,                       /* number of buffer to alloc */
    void   *pPoolPtr,                   /* address of the memory buffer used to initialize the pool */
    size_t poolSize,                    /* size of the memory buffer */
    int flags                           /* dma, cache safe */
);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCdbufh__ */
