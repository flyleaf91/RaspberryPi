from Crypto.PublicKey import RSA
# rsa_public_key.pem
f = open("rsa_public_key.pem", "r")
key = RSA.importKey(f.read())
print(key.n)
print(key.e)
