#ifndef JADE_SIGN_dilithium_dilithium3_amd64_ref_API_H
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_API_H

#define JADE_SIGN_dilithium_dilithium3_amd64_ref_PUBLICKEYBYTES   1952
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_SECRETKEYBYTES   4000
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_BYTES            3293
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_KEYPAIRCOINBYTES 32
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_DETERMINISTIC    1

#define JADE_SIGN_dilithium_dilithium3_amd64_ref_ALGNAME         "Dilithium3"
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_ARCH            "amd64"
#define JADE_SIGN_dilithium_dilithium3_amd64_ref_IMPL            "ref"

#include <stdint.h>

int jade_sign_dilithium_dilithium3_amd64_ref_keypair_derand(
  uint8_t *public_key,
  uint8_t *secret_key,
  const uint8_t *coins
);

int jade_sign_dilithium_dilithium3_amd64_ref_keypair(
  uint8_t *public_key,
  uint8_t *secret_key
);

int jade_sign_dilithium_dilithium3_amd64_ref(
  uint8_t *signed_message,
  uint64_t *signed_message_length,
  const uint8_t *message,
  uint64_t message_length,
  const uint8_t *secret_key
);

int jade_sign_dilithium_dilithium3_amd64_ref_open(
  uint8_t *message,
  uint64_t *message_length,
  const uint8_t *signed_message,
  uint64_t signed_message_length,
  const uint8_t *public_key
);

#endif

