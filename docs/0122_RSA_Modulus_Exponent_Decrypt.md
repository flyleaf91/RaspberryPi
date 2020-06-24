# RSA Modulus Exponent Decrypt

论证芯片签名、验签基本流程示例

## 验证代码

https://github.com/ZengjfOS/RaspberryPi/tree/RSAModExpDecrypt

## 说明

* privateEncrypt.c: 对一段文字进行加密，并导出私钥和公钥，指数采用的是0x010001
* extractHeader.c: 将der文件中的公钥的模（Modulus）
* modexpDecrypt.c: 合并模和指数成公钥，并用公钥进行解密，比较加密前和解密后的文本内容
* modexp2pubkey.c: 模和指数转公钥的一个示例