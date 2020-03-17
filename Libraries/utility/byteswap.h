#if defined(HAVE_BYTESWAP_H) && HAVE_BYTESWAP_H
#include_next <byteswap.h>
#else

#include <stm32f4xx.h>
#include <inttypes.h>

/* minimal version defining only the macros we need in our codebase */

static inline uint16_t __bswap_16(uint16_t u)
{
#if defined(__ICCARM__)
    return (uint16_t)__REV16(u);
#elif defined(__GNUC__)
    return (uint16_t) __builtin_bswap16(u);
#endif
}

static inline uint32_t __bswap_32(uint32_t u)
{
#if defined(__ICCARM__)
    return (uint16_t)__REV(u);
#elif defined(__GNUC__)
    return (uint32_t) __builtin_bswap32(u);
#endif
}

static inline uint64_t __bswap_64(uint64_t u)
{
#if defined(__ICCARM__)
    return (uint16_t)__REV(u);
#elif defined(__GNUC__)
    return (uint64_t) __builtin_bswap64(u);
#endif
}

#endif
