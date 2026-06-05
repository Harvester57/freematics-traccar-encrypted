#include "config.h"
#include <string.h>
#include <stdio.h>
#include <ChaChaPoly.h>
#include <HardwareSerial.h>

bool encrypt_string(const unsigned char *input, size_t length, unsigned char *output, size_t max_output_length);
bool decrypt_string(const unsigned char *input, size_t length, unsigned char *output, size_t max_output_length);
void print_hex(const unsigned char *data, size_t length);