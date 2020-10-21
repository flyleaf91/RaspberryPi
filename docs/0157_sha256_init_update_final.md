# sha256 init update final

sha256是可以分批处理输入的，满足数据不是一次性处理完的场合

## 参考文档

* [SHA256_Init, SHA256_Update, SHA256_Final](https://www.openssl.org/docs/man1.1.0/man3/SHA256_Init.html)

## 使用说明

* SHA256_Init(): initializes a SHA_CTX structure.
* SHA256_Update(): can be called repeatedly with chunks of the message to be hashed (len bytes at data).
* SHA256_Final(): places the message digest in md, which must have space for SHA_DIGEST_LENGTH == 20 bytes of output, and erases the SHA_CTX.

`SHA256_Update()`可以被多次调用，最后通过`SHA256_Final()`算出最终值；
