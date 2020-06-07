#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define INPUT_FILE		"rsa_public_key.der"
#define OUTPUT_FILE		"root_oemkey_new.h"
#define READ_SIZE		1024
#define OEM_KEY_SIZE	256

#define FILE_HEADER		"#ifndef __OEMKEY__\n\
#define __OEMKEY__\n\
#define OEM_PUBK_SZ 256\n\
#define OEM_PUBK   "

#define FILE_FOOTER		"\n#endif /*__OEM_KEY__ */"

unsigned char inArray[READ_SIZE] = {0};
unsigned char outArray[OEM_KEY_SIZE] = {0};
unsigned char temp[8] = {0};
int readSize = 0;
int flag = 0;

void read_parse_der(unsigned char array[]) {
	int i = 0;
	int length = 0;
	unsigned char *pointer = array;

	while((pointer - inArray) < readSize ) {
		printf("*pointer: %02x, flag = %d\n", *pointer, flag);
		if (*pointer == 0x2a) 
			break;
		switch(*pointer) {
			// sequence
			case 0x30:
				pointer += 1;
				break;
			// interger
			case 0x02:
				pointer += 1;
				break;
			// mutiple length
			case 0x82:
				if (flag == 1) {
					length = *(pointer + 1) << 8 | *(pointer + 2);
					printf("rsa key n e length: %04x:%d\n", length, length);


					pointer += (3 + 1);						// 1 byte padding
					flag = 2;
					read_parse_der(pointer);
					return;
				} if (flag == 2) {
					length = *(pointer + 1) << 8 | *(pointer + 2);
					printf("rsa key n item length: %04x:%d\n", length, length);
					pointer += 3;
					flag = 3;
					read_parse_der(pointer);
					return;
				} if (flag == 3) {
					length = *(pointer + 1) << 8 | *(pointer + 2);
					pointer += (3 + 1);						// 1 byte padding
					memcpy(outArray, pointer, length - 1);

					printf("rsa key n length: %04x:%d, outArray[0]: %02x\n", length, length,  outArray[0]);
					return;
				} else {
					printf("multiple byte: %02x ", *pointer);

					length = *(pointer + 1) << 8 | *(pointer + 2);
					printf("%04x:%d\n", length, length);

					pointer += 3;
					read_parse_der(pointer);

					pointer += length;
				}
				break;
			// object id
			case 0x06:
				printf("Object identifier item\n");
				return;
			// bit string
			case 0x03:
				printf("bit String item\n");
				pointer += 1;
				flag = 1;									// bit string
				break;
			// 1 byte length
			default:
				printf("1 byte %02x ", *pointer);
				length = *(pointer);
				printf("%04x:%d\n", length, length);

				pointer += 1;
				read_parse_der(pointer);

				pointer += length;
				break;
		}
		sleep(1);
	}
}

int main(void) {

	int i = 0;
	int o_fd = -1;
	int i_fd = -1;


	// open der input file
	i_fd = open(INPUT_FILE, O_RDONLY);
	if (i_fd == -1) {
		printf("open " INPUT_FILE " file error\n");
		return -1;
	} else
		printf("open " INPUT_FILE " file success\n");
	
	// read der file
	readSize = read(i_fd, inArray, READ_SIZE);
	close(i_fd);

	// deal with der data
	read_parse_der(inArray);

	// open output file
	o_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT);
	if (o_fd == -1) {
		printf("open " OUTPUT_FILE " file error\n");
		return -2;
	} else 
		printf("open " OUTPUT_FILE " file success\n");

	// write header
	write(o_fd, FILE_HEADER, sizeof(FILE_HEADER) - 1);

	// write content
	for (i = 1; i < OEM_KEY_SIZE + 1; i++) {
		memset(temp, 0, 8);
		// last char
		if (i == OEM_KEY_SIZE) 
			sprintf(temp, "0x%02X", outArray[i - 1]);
		else {
			// line end
			if ((i > 0x0F) && (i % 16) == 0) {
				sprintf(temp, "0x%02X, \\\n                   ", outArray[i - 1]);
			} else {
				sprintf(temp, "0x%02X, ", outArray[i - 1]);
			}
		}

		write(o_fd, temp, strlen(temp));
	}
	// write footer
	write(o_fd, FILE_FOOTER, sizeof(FILE_FOOTER) - 1);

	close(o_fd);
	printf("data write to " OUTPUT_FILE " success\n");
}
