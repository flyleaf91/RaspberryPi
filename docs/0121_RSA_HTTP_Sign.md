# RSA HTTP Sign

利用HTTP请求来对HASH数进行签名

## 参考文档

* [0115_Openssl_RSA_Hash_Sign.md](0115_Openssl_RSA_Hash_Sign.md)
* https://github.com/ZengjfOS/RaspberryPi/tree/RSAModExpDecrypt
* [0122_RSA_Modulus_Exponent_Decrypt.md](0122_RSA_Modulus_Exponent_Decrypt.md)

## 源代码

https://github.com/ZengjfOS/RaspberryPi/tree/RSAHTTPSign

## 简要说明

* 代码用Python3运行
* server：服务端私钥签名流程
* client：客户端产生hash，通过http post发送hash到server端进行sign的流程
* check_signed.sh：shell脚本进行验签的流程
