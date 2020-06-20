#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

/**
 * 参考文档
 *   1. openssl编译arm移植及RSA_generate_key_ex的使用实例
 *     https://blog.csdn.net/dreamInTheWorld/article/details/72899309
 */

int main()
{
    printf("\nRSA_generate_key_ex TESTING...\n\n");
    RSA *rsa = RSA_new();
    int ret = 0;
    BIGNUM *bne = BN_new();
    ret = BN_set_word(bne, RSA_F4);                     // exponent is RSA_F4(65537)
    // int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *e, BN_GENCB *cb);
    ret = RSA_generate_key_ex(rsa, 2048, bne, NULL); 

	RSA_print_fp(stdout, rsa, 0);

    BIO *out;
    out = BIO_new_file("rsa_private_key.pem","w+");
    ret = PEM_write_bio_RSAPrivateKey(out, rsa, NULL, NULL, 0, NULL, NULL);
    BIO_flush(out);
    BIO_free(out);
    
    out = BIO_new_file("rsa_public_key.pem","w+");
    ret = PEM_write_bio_RSAPublicKey(out, rsa);
    BIO_flush(out);
    BIO_free(out);

    unsigned char plain[512]    ="Hello world!";
    unsigned char cipper[512]   ={0};
    unsigned char newplain[512] ={0};
    size_t outl                 =512;
    size_t outl2;

    printf("%s\n", plain);
    for(int i = 0; i < strlen((char*)plain); i++){
        printf("%02x ", plain[i]);
    }
    printf("\n---------------\n");

    // int RSA_public_encrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);
    // outl = RSA_public_encrypt(strlen((char*)plain), plain, cipper, rsa, RSA_PKCS1_OAEP_PADDING);
    outl = RSA_private_encrypt(strlen((char*)plain), plain, cipper, rsa, RSA_PKCS1_PADDING);
    for(int i = 0; i < outl; i++){
        printf("%02x ", cipper[i]);
        if((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");

	FILE *fp = fopen("data.sig", "w");
	if(NULL == fp)
		return -1;
	fwrite(cipper, 256, 1, fp);
	fclose(fp);

    // int RSA_private_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);
    // outl2 = RSA_private_decrypt(outl, cipper, newplain, rsa, RSA_PKCS1_OAEP_PADDING);
    outl2 = RSA_public_decrypt(outl, cipper, newplain, rsa, RSA_PKCS1_PADDING);

    printf("-----------------\n%s\n", newplain);
    for(int i = 0;i < outl2; i++) {
        printf("%02x ", newplain[i]);
    }
    printf("\n");
    return 0;
}
