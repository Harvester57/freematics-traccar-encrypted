#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ChaChaPoly.h>
#include <HardwareSerial.h>
#include "Crypto.h"

static inline uint8_t hex_char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

static void parse_key(unsigned char *key) {
    for (int i = 0; i < 32; ++i) {
        key[i] = (hex_char_to_val(CHACHA20_KEY[2*i]) << 4) | hex_char_to_val(CHACHA20_KEY[2*i + 1]);
    }
}

void print_hex(const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        Serial.printf("%02x", data[i]);
    }
    Serial.println();
}

bool encrypt_string(const unsigned char *input, size_t length, unsigned char *output, size_t max_output_length) {
    ChaChaPoly chachaPoly;

    // Check if the output buffer is large enough for nonce + encrypted data + tag
    if (12 + length + chachaPoly.tagSize() > max_output_length) {
        Serial.println("[CHACHA] Output buffer too small for encryption");
        chachaPoly.clear();
        return false;
    }

    // Initialize the encryption key
    unsigned char key[32];
    parse_key(key);
    chachaPoly.setKey(key, sizeof(key));
    clean(key); // Scrub key from stack immediately after use

    // Generate a random nonce (IV)
    unsigned char nonce[12];
    esp_fill_random(nonce, sizeof(nonce)); // Use the ESP-IDF random number generator
    chachaPoly.setIV(nonce, sizeof(nonce));

    // Encrypt the input data
    chachaPoly.encrypt(output + sizeof(nonce), input, length);

    // Compute the authentication tag
    chachaPoly.computeTag(output + sizeof(nonce) + length, chachaPoly.tagSize());

    // Prepend the nonce to the output
    memcpy(output, nonce, sizeof(nonce));

    chachaPoly.clear();
    return true;
}

bool decrypt_string(const unsigned char *input, size_t length, unsigned char *output, size_t max_output_length) {
    ChaChaPoly chachaPoly;

    // Check that length is long enough to contain a nonce and a tag.
    if (length < 12 + chachaPoly.tagSize()) {
        Serial.print("[CHACHA] Input too short to contain nonce and tag: ");
        print_hex(input, length);
        if (max_output_length > 0) output[0] = '\0';
        chachaPoly.clear();
        return false;
    }

    // Initialize the decryption key
    unsigned char key[32];
    parse_key(key);
    chachaPoly.setKey(key, sizeof(key));
    clean(key); // Scrub key from stack immediately after use

    // Extract the nonce (IV) from the input
    unsigned char nonce[12];
    memcpy(nonce, input, sizeof(nonce));
    chachaPoly.setIV(nonce, sizeof(nonce));

    // Decrypt into a temporary buffer first — authenticate before exposing plaintext.
    size_t decryptedLength = length - sizeof(nonce) - chachaPoly.tagSize();
    unsigned char *tempBuf = (unsigned char *)malloc(decryptedLength);
    if (tempBuf == NULL) {
        Serial.println("[CHACHA] Memory allocation failed for decryption buffer");
        if (max_output_length > 0) output[0] = '\0';
        chachaPoly.clear();
        return false;
    }
    chachaPoly.decrypt(tempBuf, input + sizeof(nonce), decryptedLength);

    // Verify authentication tag before exposing plaintext.
    const unsigned char *tagPtr = input + sizeof(nonce) + decryptedLength;
    if (!chachaPoly.checkTag(tagPtr, chachaPoly.tagSize())) {
        Serial.println("[CHACHA] Authentication failed!");
        clean(tempBuf, decryptedLength); // Scrub unauthenticated plaintext
        free(tempBuf);
        if (max_output_length > 0) output[0] = '\0';
        chachaPoly.clear();
        return false;
    }

    // Check if output buffer is large enough for decrypted length + null terminator
    if (decryptedLength >= max_output_length) {
        Serial.println("[CHACHA] Output buffer too small for decrypted data");
        clean(tempBuf, decryptedLength);
        free(tempBuf);
        if (max_output_length > 0) output[0] = '\0';
        chachaPoly.clear();
        return false;
    }

    // Authentication succeeded — copy verified plaintext to output
    memcpy(output, tempBuf, decryptedLength);
    clean(tempBuf, decryptedLength); // Scrub temp buffer
    free(tempBuf);
    output[decryptedLength] = '\0';
    chachaPoly.clear();
    return true;
}