#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ChaChaPoly.h>
#include <HardwareSerial.h>
#include "Crypto.h"

void print_hex(const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        Serial.printf("%02x", data[i]);
    }
    Serial.println();
}

void encrypt_string(const unsigned char *input, size_t length, unsigned char *output) {
    ChaChaPoly chachaPoly;

    // Initialize the encryption key
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        sscanf(CHACHA20_KEY + 2*i, "%02x", &key[i]);
    }
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
}

void decrypt_string(const unsigned char *input, size_t length, unsigned char *output) {
    ChaChaPoly chachaPoly;

    // Initialize the decryption key
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        sscanf(CHACHA20_KEY + 2*i, "%02x", &key[i]);
    }
    chachaPoly.setKey(key, sizeof(key));
    clean(key); // Scrub key from stack immediately after use

    // Extract the nonce (IV) from the input
    unsigned char nonce[12];
    memcpy(nonce, input, sizeof(nonce));
    chachaPoly.setIV(nonce, sizeof(nonce));

    // Check that length is long enough to contain a nonce and a tag.
    if (length < sizeof(nonce) + chachaPoly.tagSize()) {
        Serial.print("[CHACHA] Input too short to contain nonce and tag: ");
        print_hex(input, length);
        output[0] = '\0';
        chachaPoly.clear();
        return;
    }

    // Decrypt into a temporary buffer first — authenticate before exposing plaintext.
    size_t decryptedLength = length - sizeof(nonce) - chachaPoly.tagSize();
    unsigned char *tempBuf = (unsigned char *)malloc(decryptedLength);
    if (tempBuf == NULL) {
        Serial.println("[CHACHA] Memory allocation failed for decryption buffer");
        output[0] = '\0';
        chachaPoly.clear();
        return;
    }
    chachaPoly.decrypt(tempBuf, input + sizeof(nonce), decryptedLength);

    // Verify authentication tag before exposing plaintext.
    const unsigned char *tagPtr = input + sizeof(nonce) + decryptedLength;
    if (!chachaPoly.checkTag(tagPtr, chachaPoly.tagSize())) {
        Serial.println("[CHACHA] Authentication failed!");
        clean(tempBuf, decryptedLength); // Scrub unauthenticated plaintext
        free(tempBuf);
        output[0] = '\0';
        chachaPoly.clear();
        return;
    }

    // Authentication succeeded — copy verified plaintext to output
    memcpy(output, tempBuf, decryptedLength);
    clean(tempBuf, decryptedLength); // Scrub temp buffer
    free(tempBuf);
    output[decryptedLength] = '\0';
    chachaPoly.clear();
}