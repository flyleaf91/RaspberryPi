#!/bin/bash

echo "check local hash"
openssl dgst -binary -sha256 -out content_hash.bin client/monitor.fex
openssl pkeyutl -verify -in content_hash.bin -sigfile client/pack_content.sig -pkeyopt rsa_padding_mode:pss -pubin -inkey client/rsa_public_key.pem -pkeyopt rsa_pss_saltlen:32 -pkeyopt digest:sha256
rm content_hash.bin

echo "check server hash"
openssl pkeyutl -verify -in server/content_hash.bin -sigfile client/pack_content.sig -pkeyopt rsa_padding_mode:pss -pubin -inkey client/rsa_public_key.pem -pkeyopt rsa_pss_saltlen:32 -pkeyopt digest:sha256
