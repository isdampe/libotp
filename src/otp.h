#ifndef LIBOTP_H
#define LIBOTP_H
#include <stddef.h>
#include <stdint.h>

#define EOTP_SIZE -1
#define EOTP_GRAND -2
#define EOTP_ALLOC -3

struct otp_handle {
	uint8_t *key;
	size_t key_size;
	int result;
};

int otp_crypt(uint8_t *src, const size_t src_size, const uint8_t *key,
	const size_t key_size);
struct otp_handle otp_auto_crypt(uint8_t *src, const size_t src_size);
void otp_close(struct otp_handle *handle);

#endif
