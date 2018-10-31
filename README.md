# libotp
A very small set of operations for implementing [one-time pad encryption](https://en.wikipedia.org/wiki/One-time_pad).

## Basic static usage 
Static usage with a provided key.

```c
#include <stdio.h>
#include <stdint.h>
#include "otp.h"

int main(int argc, char **argv)
{
	uint8_t message[] = "Hello world.";
	uint8_t key[sizeof(message)] = {
		0x01, 0xFA, 0xC9, 0xDE, 0x01, 0x09, 0x3A, 0xEF, 0xCB, 0xFF, 0x5C, 0x88
	};

	printf("Message before one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	otp_crypt(message, sizeof(message), key, sizeof(key));
	printf("\nMessage after one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	otp_crypt(message, sizeof(message), key, sizeof(key));
	printf("\nMessage after second one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	return 0;
}
```

## Auto-keying data sets
Auto key generation is possible using `otp_auto_crypt`. Note that the security
of `otp_auto_crypt` is wholly dependent on the security of `getrandom`.

Calling `otp_auto_crypt` dynamically generates a random key and then executes
a one-time pad on the provided source data with this key.

Using `otp_auto_crypt` returns `struct otp_handle` (see below). You must call
`otp_close` to clean up after you're done.

```c
struct otp_handle {
	uint8_t *key;
	size_t key_size;
	int result;
};
```

### Example

```c
uint8_t message[14] = {
	0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A,
	0x00, 0x01
};

struct otp_handle h = otp_auto_crypt(message, sizeof(message));
if (h.result == 0) {
	printf("Generated dynamic key:\n");
	for (int i=0; i<h.key_size; ++i)
		printf("%02x ", h.key[i]);

	printf("\nMessage after auto one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	otp_close(&h);
}
```

## Error codes

* `EOTP_SIZE` - Key size is less than size of source data.
* `EOTP_GRAND` - Error generating random key data.
* `EOTP_ALLOC` - Error allocating memory chunk for dynamic key.
