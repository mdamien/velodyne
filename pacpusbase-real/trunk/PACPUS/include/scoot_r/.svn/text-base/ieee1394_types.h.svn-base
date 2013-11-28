
#ifndef _IEEE1394_TYPES_H
#define _IEEE1394_TYPES_H

// #include <linux/string.h>
// #include <linux/types.h>
// #include <linux/version.h>
// #include <linux/list.h>
// #include <asm/byteorder.h>

/*
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,3,0)
#include "linux22compat.h"
#else
#define V22_COMPAT_MOD_INC_USE_COUNT do {} while (0)
#define V22_COMPAT_MOD_DEC_USE_COUNT do {} while (0)
#define OWNER_THIS_MODULE owner: THIS_MODULE,

#define INIT_TQ_LINK(tq) INIT_LIST_HEAD(&(tq).list)
#define INIT_TQ_HEAD(tq) INIT_LIST_HEAD(&(tq))
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,3,18)
#include <asm/spinlock.h>
#else
#include <linux/spinlock.h>
#endif
*/

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

typedef u32 quadlet_t;
typedef u64 octlet_t;
typedef u16 nodeid_t;

#define BUS_MASK  0xffc0
#define NODE_MASK 0x003f
#define LOCAL_BUS 0xffc0
#define ALL_NODES 0x003f

#ifdef __BIG_ENDIAN

static __inline__ void *memcpy_le32(u32 *dest, const u32 *src, size_t count)
{
        void *tmp = dest;

        count /= 4;

        while (count--) {
                *dest++ = swab32p(src++);
        }

        return tmp;
}

#else

static __inline__ void *memcpy_le32(u32 *dest, const u32 *src, size_t count)
{
        return memcpy(dest, src, count);
}

#endif /* __BIG_ENDIAN */

#endif /* _IEEE1394_TYPES_H */
