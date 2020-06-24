# Openssl RSA Hash Sign

RAS Hash签名、验签

## 参考

* [openssl常用命令，签名、非对称加解密](http://abcdxyzk.github.io/blog/2018/02/09/tools-openssl/)
* [RSA加密：利用模数和指数生成公钥加密](https://www.cnblogs.com/tml839720759/p/3926006.html)
* [How to find modulus from a RSA public key?](https://crypto.stackexchange.com/questions/18031/how-to-find-modulus-from-a-rsa-public-key)
  * [ASN.1](https://zh.wikipedia.org/wiki/ASN.1)
  * [ASN.1 BER编码](https://blog.csdn.net/wzj_whut/article/details/86241935)
  * [DER的编码范例](https://zh.wikipedia.org/wiki/ASN.1#DER%E7%9A%84%E7%B7%A8%E7%A2%BC%E7%AF%84%E4%BE%8B)
  * DER uses a pattern of type-length-value triplets
* [ASN.1格式的RSA私钥PEM包含额外字节](https://xbuba.com/questions/48404917)
* [为什么RSA 公钥指数(e=65537)](https://blog.csdn.net/hherima/article/details/52461759)
* [RSA密钥长度、明文长度和密文长度](https://blog.csdn.net/dengcanjun6/article/details/83141764)
* [RSA签名的PSS模式](https://www.cnblogs.com/qcloud1001/p/10373760.html)

## RAS基本概念

RSA模数和指数，对应到结构中分别是其中的`n`和`e`，模反数对应`d`，最开始的质数因子对应`p`和`q`，`n`和`e`决定了公钥，`n`和`d`决定了私钥。

## DER长度

如果长度的第一个字节为:
* 如果是0x80, 表示content的长度不确定, 需要根据content的定义来解码content, 此时content之后需要跟随结束码
* 若不是0x80, 则又分为单字节编码和多字节编码.
  * 如果content的长度小于或等于127个字节, 则使用1个字节表示长度.
  * 如果content的长度大于127个字节, 则长度的第1个字节的低7位表示长度占用的字节数(不包含第1个字节), 第1个字节的最高位bit8置为1. 随后的N个字节(包含所有的8bit)共同表示一个整数假设长度为`201`, 它的二进制为`110010012`, 最后编码为 `10000001 110010012`

## 签名验签步骤

* https://github.com/ZengjfOS/RaspberryPi/tree/RSA_Hash_Sign
* openssl genrsa -out rsa_private_key.pem 2048
* openssl rsa -in rsa_private_key.pem -pubout -out rsa_public_key.pem
* 生成hash：
 * 从头文件获取：
   * make -C ../der && cd ../der && ./header2bin && cd -
   * cp ../der/out.bin .
   * sha256sum out.bin
     ```
     9af8a28bf1096b58751ab5ef5f696c5df3050124bb9fec51bd9bf190d04c618f  out.bin
     ```
  * 从der直接提取
    * ../der/extractHeader
      * 目前没有直接保存成bin文件，而是提取成头文件，可以修改为保存为bin的形式
  * python版本的查看信息：hash/extractKey.py 
* sha256sum out.bin | cut -d " " -f 1 > hash.txt
* openssl rsautl -sign -in hash.txt -out hash.sig -inkey rsa_private_key.pem
* openssl rsautl -verify -in hash.sig -out hash.verify -inkey rsa_public_key.pem -pubin
* cmp hash.txt hash.verify
* 以上签名是直接对Hash签名，还有一种是对Hash进行PASS签名

## der解析

* openssl rsa -pubin -inform PEM -in rsa_public_key.pem -outform DER -out rsa_public_key.der
* hexdump -v -e '1/1 "%02x"' rsa_public_key.der
  * 30820122300d06092a864886f70d01010105000382010f003082010a0282010100c190252b9d822cda0780bfcd7edf472788de118fefb6d4eab025bc647ca6b4bc801245a24a8da792a4b1c02271c1039f9cc2e6390d0d0a93b762f009a86398217397e5441064827f23329efe9d87353d58eb5bdfdc116eb4437291db83df0c80ec1ed6f7695ea33f252700eba4c53f4cb266ff834b0ce272301f86d3f736a78ceef647d42466120affd35917f28a8b911591b26054fccc2e956f73571f62528c2043f3416e18b4dfbd09e19c69586f6aca1c939c9004569afe308f93ba110f7fdb2bd0cdd3f85f1bb538926d4c8a91d0f14b495354bf613133fef1682bd01e1f3fe8d2cfc0588164a3ebde2cf306ef49911579ffc1133c833e35fdd478a7241b0203010001
  * 输出的hex文本可以在这里面进行解码：https://lapo.it/asn1js/#
  * 30: sequence (type)
  * 82: length property(最高位1(0x80)表示可变长，2(0x02)表示长度为两字节)
  * 01 22: 290 byte (length value)
    * 30: sequence (type) 
      * 0d: 13 byte (length value)
        * 06: Object identifier
        * 09: 长度为9个字节
          * 2a 86 48 86 f7 0d 01 01 01
        * 05 00
          * NULL
          * tag = 5
          * 固定值: 0x05 0x00
    * 03: 表示bitstring
      * 82: length property(最高位1(0x80)表示可变长，2(0x02)表示长度为两字节)
      * 01 0f: 271 byte (length value)
        * 00: padding的比特数为0.
        * 30: sequence (type)
        * 82: length property(最高位1(0x80)表示可变长，2(0x02)表示长度为两字节)
        * 01 0a: 266 byte (length value)
          * 02: tag = 2，整数
          * 82 01 01: --长度为257,  以下是一个超级大的整数, 为密钥中的n
            * 00c190252b9d822cda0780bfcd7edf472788de118fefb6d4eab025bc647ca6b4bc801245a24a8da792a4b1c02271c1039f9cc2e6390d0d0a93b762f009a86398217397e5441064827f23329efe9d87353d58eb5bdfdc116eb4437291db83df0c80ec1ed6f7695ea33f252700eba4c53f4cb266ff834b0ce272301f86d3f736a78ceef647d42466120affd35917f28a8b911591b26054fccc2e956f73571f62528c2043f3416e18b4dfbd09e19c69586f6aca1c939c9004569afe308f93ba110f7fdb2bd0cdd3f85f1bb538926d4c8a91d0f14b495354bf613133fef1682bd01e1f3fe8d2cfc0588164a3ebde2cf306ef49911579ffc1133c833e35fdd478a7241b
            * 第一个字节为00的解释：RSA模数是正数，ASN.1整数都是有符号的。因此，如果前导0x00不存在，则此字节编码将表示负数，因为第一个字节将设置高位（0xB7> = 0x80）。结果，0x00被插入到DER数据流中。
          * 02: tag = 2，整数
          * 03: 3个字节
          * 010001: 数字 65537, , 为RSA密钥中e
* 我们只需要模数和指数，所以不用解析第一部分、

## PSS签名验签

如下是stackoverflow上的示例

[How to verify signature with pss padding?](https://stackoverflow.com/questions/44428095/how-to-verify-signature-with-pss-padding)
```bash
$ openssl dgst -sha256 -binary payload.bin > cp1.bin
$ openssl pkeyutl -sign \
  -in cp1.bin -inkey pvt_dbg.pem \
  -out sig1.bin \
  -pkeyopt digest:sha256 \
  -pkeyopt rsa_padding_mode:pss \
  -pkeyopt rsa_pss_saltlen:-1
$ openssl pkeyutl -verify \
  -in cp1.bin -sigfile sig1.bin \
  -pkeyopt rsa_padding_mode:pss \
  -pubin -inkey pub_dbg.pem \
  -pkeyopt rsa_pss_saltlen:-1 \
  -pkeyopt digest:sha256
```

`rsa_pss_saltlen`可以尝试改成`32`，当然效果不会有什么特殊的，测试一下自己的命令：

* openssl dgst -sha256 -binary hash.txt > hash.bin
* openssl pkeyutl -sign -in hash.bin -inkey rsa_private_key.pem -out hash.sig -pkeyopt digest:sha256 -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:32
* openssl pkeyutl -verify -in hash.bin -sigfile hash.sig -pkeyopt rsa_padding_mode:pss -pubin -inkey rsa_public_key.pem -pkeyopt rsa_pss_saltlen:32 -pkeyopt digest:sha256
* 执行流程
  ```bash
  pi@raspberrypi:hash $ openssl dgst -sha256 -binary hash.txt > hash.bin
  pi@raspberrypi:hash $ openssl pkeyutl -sign -in hash.bin -inkey rsa_private_key.pem -out hash.sig -pkeyopt digest:sha256 -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:32
  pi@raspberrypi:hash $ openssl pkeyutl -verify -in hash.bin -sigfile hash.sig -pkeyopt rsa_padding_mode:pss -pubin -inkey rsa_public_key.pem -pkeyopt rsa_pss_saltlen:32 -pkeyopt digest:sha256
  Signature Verified Successfully
  pi@raspberrypi:hash $
  ```

## ASN1 Decode

* https://python-asn1.readthedocs.io/en/latest/introduction_to_asn1.html
* DER is a binary format for data structures described by ASN.1.
* <tag> <length+> <value>
  * http://luca.ntop.org/Teaching/Appunti/asn1.html
  * tag:
    * tag[8:7]: type
    * tag[6]: class
    * tag[5:0]: number
  * length: 
    * lenth[8]: 短/长编码
    * length: 短编码：长度立即数；长编码：长度字节数；
    * length+: 长编码长度
  * value: 实际数据
* https://github.com/andrivet/python-asn1/blob/master/examples/dump.py
  ```diff
  diff --git a/examples/dump.py b/examples/dump.py
  index a0cf0be..a9e1a73 100755
  --- a/examples/dump.py
  +++ b/examples/dump.py
  @@ -154,10 +154,10 @@ parser.set_default('mode', 'pem')
   (opts, args) = parser.parse_args()
  
   if opts.mode == 'pem':
  -    input_file = open(sys.argv[1], 'r')
  +    input_file = open(args[0], 'r')
       input_data = read_pem(input_file)
   else:
  -    input_file = open(sys.argv[1], 'rb')
  +    input_file = open(args[0], 'rb')
       input_data = input_file.read()
  
   if opts.output:
  ```