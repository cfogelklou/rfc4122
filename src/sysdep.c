#include "copyrt.h"
#include <stdio.h>
#include "sysdep.h"
#include <string.h>
#include <stdlib.h>

/* system dependent call to get IEEE node ID.
 This sample implementation generates a random node ID. */
void get_ieee_node_identifier(uuid_node_t *node)
{
  static int inited = 0;
  static uuid_node_t saved_node;
  char seed[16];
  FILE *fp;
  
  if (!inited) {
    fp = fopen("nodeid", "rb");
    if (fp) {
      fread(&saved_node, sizeof saved_node, 1, fp);
      fclose(fp);
    }
    else {
      get_random_info(seed);
      seed[0] |= 0x01;
      memcpy(&saved_node, seed, sizeof saved_node);
      fp = fopen("nodeid", "wb");
      if (fp) {
        fwrite(&saved_node, sizeof saved_node, 1, fp);
        fclose(fp);
      }
    }
    inited = 1;
  }
  
  *node = saved_node;
}

/* system dependent call to get the current system time. Returned as
 100ns ticks since UUID epoch, but resolution may be less than
 100ns. */
#if (WININC > 0)

void get_system_time(uuid_time_t *uuid_time)
{
  ULARGE_INTEGER time;
  
  /* NT keeps time in FILETIME format which is 100ns ticks since
   Jan 1, 1601. UUIDs use time in 100ns ticks since Oct 15, 1582.
   The difference is 17 Days in Oct + 30 (Nov) + 31 (Dec)
   + 18 years and 5 leap days. */
  GetSystemTimeAsFileTime((FILETIME *)&time);
  time.QuadPart +=
  
  (unsigned __int64) (1000*1000*10)       // seconds
  * (unsigned __int64) (60 * 60 * 24)       // days
  * (unsigned __int64) (17+30+31+365*18+5); // # of days
  *uuid_time = time.QuadPart;
}

#else

#define I64(x) (int64_t)(x)

void get_system_time(uuid_time_t *uuid_time)
{
  struct timeval tp;
  
  gettimeofday(&tp, (struct timezone *)0);
  
  /* Offset between UUID formatted times and Unix formatted times.
   UUID UTC base time is October 15, 1582.
   Unix base time is January 1, 1970.*/
  *uuid_time = ((unsigned64)tp.tv_sec * 10000000)
  + ((unsigned64)tp.tv_usec * 10)
  + I64(0x01B21DD213814000);
}

#endif

/* Sample code, not for use in production; see RFC 1750 */
void get_random_info(char seed[16])
{
  SHA_CTX ctx;
  SHA1_Init(&ctx);
  uuid_time_t t;
  get_system_time(&t);
  srand(t);
  SHA1_Update(&ctx, &t, sizeof(t));
  uint16_t r[32];
  for (int i = 0; i < 32; i++) {
    r[i] = rand() & 0xffff;
  }
  SHA1_Update(&ctx, r, sizeof(r));
  uint8_t tmp[20];
  SHA1_Final(tmp, &ctx);
  memcpy(seed, tmp, 16);
}


void MD5Init(MD5_CTX *pCtx) {
  mbedtls_md5_init(pCtx);
  mbedtls_md5_starts(pCtx);
}

void MD5Update(MD5_CTX *pCtx, void * const buf, const size_t bufSize){
  mbedtls_md5_update_ret(pCtx, buf, bufSize);
}

void MD5Final(uint8_t seed[16], MD5_CTX *pCtx){
  mbedtls_md5_finish_ret(pCtx, seed);
  mbedtls_md5_free(pCtx);
}

void SHA1_Init(SHA_CTX *pCtx){
  mbedtls_sha1_init(pCtx);
  mbedtls_sha1_starts(pCtx);
}

void SHA1_Update(SHA_CTX *pCtx, void * const buf, const size_t bufSize){
  mbedtls_sha1_update_ret(pCtx, buf, bufSize);
}

void SHA1_Final(uint8_t seed[20], SHA_CTX *pCtx){
  mbedtls_sha1_finish_ret(pCtx, seed);
  mbedtls_sha1_free(pCtx);
}
