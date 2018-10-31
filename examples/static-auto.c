#include <stdio.h>
#include <stdint.h>
#include "../src/otp.h"

int main(int argc, char **argv)
{
	uint8_t message[14] = {
		0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A,
		0x00, 0x01
	};

	uint8_t key[14] = {
		0x01, 0xFA, 0xC9, 0xDE, 0x01, 0x09, 0x3A, 0xEF, 0xCB, 0xFF, 0x5C, 0x88,
		0x31, 0x5F
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

	printf("\n\nGenerating dynamic key...\nIf program hangs, create entropy by moving" \
			" your mouse around or pressing keys.\n");
	struct otp_handle h = otp_auto_crypt(message, sizeof(message));
	printf("Generated dynamic key:\n");
	for (int i=0; i<h.key_size; ++i)
		printf("%02x ", h.key[i]);
	printf("\nMessage after auto one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	otp_crypt(message, sizeof(message), h.key, h.key_size);
	printf("\nMessage after second one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);
	printf("\n");

	otp_close(&h);

	return 0;
}
