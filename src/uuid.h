#ifndef RFC4122_UUID_H__
#define RFC4122_UUID_H__
#include "copyrt.h"

#include <stdint.h>

// Include "sysdep.h" before "uuid.h" for unsigned32, etc.
typedef struct rfc4122_uuid_tag{
  // pass all words as host endianness, will be converted to BE internally.
  unsigned32  time_low;
  unsigned16  time_mid;
  unsigned16  time_hi_and_version;
  unsigned8   clock_seq_hi_and_reserved;
  unsigned8   clock_seq_low;
  byte        node[6];
} rfc4122_uuid_t;

#undef uuid_t
#define uuid_t rfc4122_uuid_t

#ifdef __cplusplus
extern "C" {
#endif

/* uuid_create -- generate a UUID */
int uuid_create(uuid_t * uuid);

/* uuid_create_md5_from_name -- create a version 3 (MD5) UUID using a
 "name" from a "name space" */
void uuid_create_md5_from_name(
                               uuid_t *uuid,         /* resulting UUID */
                               uuid_t nsid,          /* UUID of the namespace */
                               void *name,           /* the name from which to generate a UUID */
                               int namelen           /* the length of the name */
);

/* uuid_create_sha1_from_name -- create a version 5 (SHA-1) UUID
 using a "name" from a "name space" */
void uuid_create_sha1_from_name(
                                
                                uuid_t *uuid,         /* resulting UUID */
                                uuid_t nsid,          /* UUID of the namespace */
                                void *name,           /* the name from which to generate a UUID */
                                int namelen           /* the length of the name */
);

/* uuid_compare --  Compare two UUID's "lexically" and return
 -1   u1 is lexically before u2
 0   u1 is equal to u2
 1   u1 is lexically after u2
 Note that lexical ordering is not temporal ordering!
 */
int uuid_compare(uuid_t *u1, uuid_t *u2);

#ifdef __cplusplus
}
#endif


#endif // #ifndef RFC4122_UUID_H__
