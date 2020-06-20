CC = gcc
CFLAGS =
DEPS = 
LIBS = -lssl -lcrypto

all: 
	$(CC) -o modexp2pubkey modexp2pubkey.c $(CFLAGS) $(LIBS)
	$(CC) -o privateEncrypt privateEncrypt.c $(CFLAGS) $(LIBS)
	$(CC) -o extractHeader extractHeader.c $(CFLAGS) $(LIBS)

	./privateEncrypt
	openssl rsa -RSAPublicKey_in -in rsa_public_key.pem -pubout -out rsa_public_key.pem
	openssl rsa -pubin -inform PEM -in rsa_public_key.pem -outform DER -out rsa_public_key.der
	rm root_oemkey_new.h -f
	./extractHeader

	$(CC) -o modexpDecrypt modexpDecrypt.c $(CFLAGS) $(LIBS)
	./modexpDecrypt

.PHONY: clean
clean:
	rm -f modexp2pubkey privateEncrypt modexpDecrypt extractHeader
	rm -f *.pem
	rm -f root_oemkey_new.h
	rm -f rsa_public_key.der
	rm -f data.sig
