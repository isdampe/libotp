#ifndef LIBONETIMEPAD_H
#define LIBONETIMEPAD_H
#include <stddef.h>
#include <stdint.h>

#define EOTP_SIZE 0x1
#define EOTP_KEY_DEST_NULL 0x2
#define EOTP_GRAND 0x3

int otp_xor(uint8_t *src, const size_t src_size, const uint8_t *key,
	const size_t key_size);
int otp_auto_xor(uint8_t *src, const size_t src_size, uint8_t *key_dest);

#endif
