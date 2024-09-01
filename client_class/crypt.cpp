#include <openssl/aes.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <sstream>
std::string hmac_md5(const std::string& data) {
    const std::string& key = "TerminalChat";
    unsigned char* digest;
    unsigned int len = MD5_DIGEST_LENGTH;

    digest = HMAC(EVP_md5(), key.c_str(), key.length(), (unsigned char*)data.c_str(), data.length(), nullptr, nullptr);

    std::ostringstream oss;
    for (unsigned int i = 0; i < len; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    return oss.str();
}

std::string aes_encrypt(const std::string& plaintext, std::string& iv) {
    const std::string key = "TerminalChat" ;
    AES_KEY encryptKey;
    AES_set_encrypt_key((unsigned char*)key.c_str(), 128, &encryptKey);

    iv.resize(AES_BLOCK_SIZE);
    RAND_bytes((unsigned char*)iv.data(), AES_BLOCK_SIZE);

    std::string ciphertext(plaintext.size() + AES_BLOCK_SIZE, '\0');

    int num = 0;
    AES_cfb128_encrypt((unsigned char*)plaintext.c_str(), (unsigned char*)ciphertext.data(), plaintext.size(), &encryptKey, (unsigned char*)iv.data(), &num, AES_ENCRYPT);

    return ciphertext;
}


std::string aes_decrypt(const std::string& ciphertext, const std::string& iv) {
     const std::string& key = "TerminalChat";
    AES_KEY decryptKey;
    AES_set_decrypt_key((unsigned char*)key.c_str(), 128, &decryptKey);

    std::string plaintext(ciphertext.size(), '\0');
    int num = 0;
    AES_cfb128_encrypt((unsigned char*)ciphertext.c_str(), (unsigned char*)plaintext.data(), ciphertext.size(), &decryptKey, (unsigned char*)iv.data(), &num, AES_DECRYPT);

    return plaintext;
}


