#include "otp.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef __linux__
#include <sys/random.h>
#endif

int otp_xor(uint8_t *src, const size_t src_size, const uint8_t *key,
	const size_t key_size)
{
	if (key_size < src_size)
		return EOTP_SIZE;

	for (size_t i=0; i < src_size; ++i)
		src[i] ^= key[i];

	return 0;
}

int otp_auto_xor(uint8_t *src, const size_t src_size, uint8_t *key_dest)
{
	if (key_dest == NULL)
		return EOTP_KEY_DEST_NULL;

#ifdef __linux__
	int result = 0;
	int bytes_generated = 0;
	if (src_size > 256) {
		int loop_iterations = src_size / 256;
		size_t i=0;

		for (i=0; i<loop_iterations; ++i) {
			result = getrandom(key_dest, 256, GRND_RANDOM);
			if (result != 256)
				return EOTP_GRAND;
			bytes_generated += 256;
			*key_dest += bytes_generated;
		}

		int final_step_n = (src_size % 256);
		result = getrandom(key_dest, final_step_n, GRND_RANDOM);
		bytes_generated += final_step_n;
		*key_dest -= bytes_generated;
	} else {
		result = getrandom(key_dest, src_size, GRND_RANDOM);
		bytes_generated += src_size;
	}

	if (result < 0)
		return EOTP_GRAND;

#endif

	return otp_xor(src, src_size, key_dest, bytes_generated);
}
