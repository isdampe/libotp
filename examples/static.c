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

	otp_xor(message, sizeof(message), key, sizeof(key));
	printf("\nMessage after one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	otp_xor(message, sizeof(message), key, sizeof(key));
	printf("\nMessage after second one-time pad:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);
	printf("\n");

	otp_auto_xor(message, sizeof(message), key);
	printf("Random key:\n");
	for (int i=0; i<14; ++i)
		printf("%02x ", message[i]);

	return 0;
}
