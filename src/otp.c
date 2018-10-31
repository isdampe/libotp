#include "otp.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef __linux__
#include <sys/random.h>
#endif

int otp_crypt(uint8_t *src, const size_t src_size, const uint8_t *key,
	const size_t key_size)
{
	if (key_size < src_size)
		return EOTP_SIZE;

	for (size_t i=0; i < src_size; ++i)
		src[i] ^= key[i];

	return 0;
}

struct otp_handle otp_auto_crypt(uint8_t *src, const size_t src_size)
{
	struct otp_handle otp_result;
	otp_result.key = malloc(src_size * sizeof(uint8_t));
	if (otp_result.key == NULL) {
		otp_result.result = EOTP_ALLOC;
		return otp_result;
	}

	int bytes_generated = 0;

#ifdef __linux__
	int result = 0;
	int read_size = 256;

	while (bytes_generated < src_size) {
		read_size = ((src_size - bytes_generated) < 256 ? 
			(src_size - bytes_generated) : 256);
		result = getrandom(&otp_result.key[bytes_generated], read_size, GRND_RANDOM);
		if (result < 0) {
			otp_result.result = EOTP_GRAND;
			return otp_result;
		}

		bytes_generated += result;
	}
#endif

	otp_result.key_size = bytes_generated;
	otp_result.result = otp_crypt(src, src_size, otp_result.key, otp_result.key_size);

	return otp_result;
}

void otp_close(struct otp_handle *handle)
{
	free(handle->key);
}
