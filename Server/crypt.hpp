#ifndef __CRYPT__
#define __CRYPT__
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <sstream>
std::string hmac_md5(const std::string& data);
std::string aes_decrypt(const std::string& ciphertext, const std::string& iv);
std::string aes_decrypt(const std::string& ciphertext, const std::string& iv);
#endif
