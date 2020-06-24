# OpenSSL C Example

学习OpenSSL的使用

## 参考文档

* [How to install OpenSSL 1.0.2 on Raspberry Pi3](https://raspberrypi.stackexchange.com/questions/66782/how-to-install-openssl-1-0-2-on-raspberry-pi3)

## Compile

* https://github.com/openssl/openssl/tree/OpenSSL_1_1_1-stable
* ./config
* make
* make test
* sudo make install

## 参考源代码

https://github.com/ZengjfOS/RaspberryPi/tree/RSAModExpDecrypt

## 无填充公钥解密

```C
#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "root_oemkey_new.h"

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

    printf("\n------pack_content.sig------\n");
        FILE *fp = fopen("pack_content.sig", "r+");
        if(NULL == fp)
                return -1;
        fread(cipper, 256, 1, fp);
        fclose(fp);

    for(int i = 0; i < 256; i++){
        printf("%02x ", cipper[i]);
        if((i + 1) % 16 == 0) printf("\n");
    }


    RSA* rsa= RSA_new();
    RSA_set0_key(rsa, BN_bin2bn(n_array, 256, NULL), BN_bin2bn(e_array, 3, NULL), NULL);

    outl2 = RSA_public_decrypt(outl, cipper, newplain, rsa, RSA_NO_PADDING);

    printf("\n------plain---------\n");
    for(int i = 0; i < outl2; i++) {
        printf("%02x ", newplain[i]);

        if((i + 1) % 16 == 0)
            printf("\n");

        if (outl2 > 256)
            break;
    }
    printf("\n");

    return 0;
}
```