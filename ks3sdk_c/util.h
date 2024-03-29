
#ifndef _KS3_SDK_C_UTIL_H_
#define _KS3_SDK_C_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// acl groups
#define ACS_URL "http://acs.ksyun.com/groups/"

#define ACS_GROUP_ALL_USERS     ACS_URL "global/AllUsers"
#define ACS_GROUP_AWS_USERS     ACS_URL "global/AuthenticatedUsers"
#define ACS_GROUP_LOG_DELIVERY  ACS_URL "s3/LogDelivery"

// Derived from S3 documentation

// This is the maximum number of bytes needed in a "compacted meta header"
// buffer, which is a buffer storing all of the compacted meta headers.
#define COMPACTED_METADATA_BUFFER_SIZE \
    (S3_MAX_METADATA_COUNT * sizeof(S3_METADATA_HEADER_NAME_PREFIX "n: v"))

// Maximum url encoded key size; since every single character could require
// URL encoding, it's 3 times the size of a key (since each url encoded
// character takes 3 characters: %NN)
#define MAX_URLENCODED_KEY_SIZE (3 * S3_MAX_KEY_SIZE)

// This is the maximum size of a URI that could be passed to S3:
// https://s3.amazonaws.com/${BUCKET}/${KEY}?acl
// 255 is the maximum bucket length
#define MAX_URI_SIZE \
    ((sizeof("https:///") - 1) + S3_MAX_HOSTNAME_SIZE + 255 + 1 +       \
     MAX_URLENCODED_KEY_SIZE + (sizeof("?torrent" - 1)) + 1)

// Maximum size of a canonicalized resource
#define MAX_CANONICALIZED_RESOURCE_SIZE \
    (1 + 255 + 1 + MAX_URLENCODED_KEY_SIZE + (sizeof("?torrent") - 1) + 1)


// Utilities -----------------------------------------------------------------

// URL-encodes a string from [src] into [dest].  [dest] must have at least
// 3x the number of characters that [source] has.   At most [maxSrcSize] bytes
// from [src] are encoded; if more are present in [src], 0 is returned from
// urlEncode, else nonzero is returned.
int urlEncode(char *dest, const char *src, int maxSrcSize);

// Returns < 0 on failure >= 0 on success
int64_t parseIso8601Time(const char *str);

uint64_t parseUnsignedInt(const char *str);

// base64 encode bytes.  The output buffer must have at least
// ((4 * (inLen + 1)) / 3) bytes in it.  Returns the number of bytes written
// to [out].
int base64Encode(const unsigned char *in, int inLen, char *out);

// Compute HMAC-SHA-1 with key [key] and message [message], storing result
// in [hmac]
void HMAC_SHA1(unsigned char hmac[20], const unsigned char *key, int key_len,
               const unsigned char *message, int message_len);

// Compute a 64-bit hash values given a set of bytes
uint64_t hash(const unsigned char *k, int length);

// Because Windows seems to be missing isblank(), use our own; it's a very
// easy function to write in any case
int is_blank(char c);

#ifdef __cplusplus
}
#endif
#endif  // _KS3_SDK_C_UTIL_H_
