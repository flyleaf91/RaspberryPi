#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "root_oemkey_new.h"

/**
 * 参考文档
 *   1. openssl编译arm移植及RSA_generate_key_ex的使用实例
 *     https://blog.csdn.net/dreamInTheWorld/article/details/72899309
 */
unsigned char n_array[OEM_PUBK_SZ] = {OEM_PUBK};
unsigned char e_array[] = "\x01\x00\x01";

int main()
{


    unsigned char plain[512]    ="Hello world!";
    unsigned char cipper[512]   ={0};
    unsigned char newplain[512] ={0};
    size_t outl                 =256;
    size_t outl2;
    int ret = 0;
    printf("\n------n_array------\n");
    for(int i = 0; i < OEM_PUBK_SZ; i++){
        printf("%02x ", n_array[i]);
        if((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n------plain---------\n");

    printf("\n------data.sig------\n");
	FILE *fp = fopen("data.sig", "r+");
	if(NULL == fp)
		return -1;
	fread(cipper, 256, 1, fp);
	fclose(fp);

    for(int i = 0; i < 256; i++){
        printf("%02x ", cipper[i]);
        if((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n------plain---------\n");

    printf("%s\n", plain);
    for(int i = 0; i < strlen((char*)plain); i++){
        printf("%02x ", plain[i]);
    }
    printf("\n---------------\n");

    RSA* rsa= RSA_new();
    RSA_set0_key(rsa, BN_bin2bn(n_array, 256, NULL), BN_bin2bn(e_array, 3, NULL), NULL);

    EVP_PKEY* pRsaKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pRsaKey, rsa);
    FILE* file = fopen("rsa_public_key_n+e.pem", "w");
    PEM_write_PUBKEY(file, pRsaKey);
    fflush(file);
    fclose(file);

    file = fopen("rsa_public_key_n+e_rsa.pem", "w");
    PEM_write_RSA_PUBKEY(file, rsa);
    fflush(file);
    fclose(file);


    // int RSA_private_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);
    // outl2 = RSA_private_decrypt(outl, cipper, newplain, rsa, RSA_PKCS1_OAEP_PADDING);
    // outl2 = RSA_public_decrypt(outl, cipper, newplain, rsa, RSA_PKCS1_PADDING);
    outl2 = RSA_public_decrypt(outl, cipper, newplain, rsa, RSA_PKCS1_PADDING);

    
    printf("-------outl2 = %d----------\n%s\n", outl2, newplain);
    for(int i = 0;i < outl2; i++) {
        printf("%02x ", newplain[i]);

        if (outl2 > 256) 
            break;
    }
    printf("\n");

    if (strncmp(newplain, plain, outl2) == 0) 
        printf("RSA check SUCCESS\n");
    else
        printf("RSA check FAILED\n");

    return 0;
}
