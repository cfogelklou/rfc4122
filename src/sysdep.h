#ifndef RFC4122_SYSDEP_H__
#define RFC4122_SYSDEP_H__
#include "copyrt.h"
#include <stdint.h>

#ifdef WIN32
/* remove the following define if you aren't running WIN32 */
#define WININC 1
#endif

#if (WININC > 0)
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/time.h>
//#include <sys/sysinfo.h>
#endif


//#include "global.h"
/* change to point to where MD5 .h's live; RFC 1321 has sample
 implementation */
#include "md5.h"
#include "sha1.h"

/* set the following to the number of 100ns ticks of the actual
 resolution of your system's clock */
#define UUIDS_PER_TICK 1024

/* Set the following to a calls to get and release a global lock */
#define LOCK
#define UNLOCK


typedef uint64_t unsigned64;
typedef uint64_t unsigned64_t;
typedef uint32_t unsigned32;
typedef uint16_t unsigned16;
typedef uint8_t unsigned8;
typedef uint8_t byte;

typedef unsigned64_t uuid_time_t;
typedef struct {
  char nodeID[6];
} uuid_node_t;

typedef mbedtls_md5_context MD5_CTX;
typedef mbedtls_sha1_context SHA_CTX;

#ifdef __cplusplus
extern "C" {
#endif

void get_ieee_node_identifier(uuid_node_t *node);
void get_system_time(uuid_time_t *uuid_time);
void get_random_info(char seed[16]);

void MD5Init(MD5_CTX *pCtx);
void MD5Update(MD5_CTX *pCtx, void * const buf, const size_t bufSize);
void MD5Final(uint8_t seed[16], MD5_CTX *pCtx);

void SHA1_Init(SHA_CTX *pCtx);
void SHA1_Update(SHA_CTX *pCtx, void * const buf, const size_t bufSize);
void SHA1_Final(uint8_t seed[16], SHA_CTX *pCtx);

#ifdef __cplusplus
}
#endif

  
#endif // #ifndef RFC4122_SYSDEP_H__
