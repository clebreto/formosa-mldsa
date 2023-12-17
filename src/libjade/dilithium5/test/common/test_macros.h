#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define check32to32(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t arg;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg), sizeof(int32_t));			\
      int32_t res_c = FUNCTION_C(arg);					\
      int32_t res_jazz = FUNCTION_JASMIN(arg);				\
      if (res_c != res_jazz) {						\
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
      printf("FAIL: %s\n", function_name);				\
      exit(1);								\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

// int32 x int32 -> int32
#define check3232to32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {									\
    int32_t arg1, arg2;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg1), sizeof(int32_t));			\
      randombytes((uint8_t*)(&arg2), sizeof(int32_t));			\
      int32_t res_c = FUNCTION_C(arg1, arg2);				\
      int32_t res_jazz = FUNCTION_JASMIN(arg1, arg2);			\
      if (res_c != res_jazz) {						\
	printf("%" PRId32 ", %" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg1, arg2, res_c, res_jazz); \
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

  
#define check64to32(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int64_t arg;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg), sizeof(int64_t));			\
      int32_t res_c = FUNCTION_C(arg);					\
      int32_t res_jazz = FUNCTION_JASMIN(arg);				\
      if (res_c != res_jazz) {						\
	printf("%" PRId64 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  } 

#endif

#define fillarr(ty, k, a)				\
  {							\
    ty arg;						\
    for (int i = 0; i < k; i++) {			\
      randombytes((uint8_t*)(&arg), sizeof(ty));	\
      a[i] = arg;					\
    }							\
  }

#define fillarrN(a, a_jazz)			\
  {						\
    fillarr(int32_t, N, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * N);	\
  }

#define eqarr(size, PRI, a, a_jazz, function_name)		\
  {								\
    for (int i = 0; i < size; i++) {				\
      if (a[i] != a_jazz[i]) {					\
	printf("at %i : ", i);					\
	printf("%" PRI " != %" PRI "\n", a[i], a_jazz[i]);	\
	printf("FAIL: %s\n", function_name);			\
	exit(1);						\
      }								\
    }								\
  }

#define eqarrN(a, a_jazz, function_name) eqarr(N, PRIx32, a, a_jazz, function_name)

#define checkarrN(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {								\
    int32_t a[N];						\
    int32_t a_jazz[N];						\
    for(int t=0; t<TESTS; t++)					\
      {								\
	fillarrN(a, a_jazz);					\
	FUNCTION_C(a);						\
	FUNCTION_JASMIN(a_jazz);				\
	eqarrN(a, a_jazz, function_name);			\
      }								\
    printf("PASS: %s\n", function_name);			\
  }

#define checkpoly(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {							      \
    int32_t a[N];					      \
    int32_t a_jazz[N];					      \
    for(int t=0; t<TESTS; t++) {			      \
      fillarrN(a, a_jazz);				      \
      FUNCTION_C((poly *) a);				      \
      FUNCTION_JASMIN((poly *) a_jazz);			      \
      eqarrN(a, a_jazz, function_name);			      \
    }							      \
    printf("PASS: %s\n", function_name);		      \
  }

#define checkpoly2(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int32_t a[N]; \
  int32_t b[N]; \
  int32_t c[N];	\
  int32_t a_jazz[N]; \
  int32_t b_jazz[N]; \
  int32_t c_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    fillarrN(b, b_jazz); \
    FUNCTION_C((poly *) c, (poly *) a, (poly *) b); \
    FUNCTION_JASMIN((poly *) c_jazz, (poly *) a_jazz, (poly *) b_jazz); \
    eqarrN(c, c_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpolyint(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int r; \
  int r_jazz; \
  int32_t a[N]; \
  int32_t a_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    FUNCTION_C((poly *) a, 3); \
    FUNCTION_JASMIN((poly *) a_jazz, 3); \
    eqarrN(a, a_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpolyetapack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								     \
    int32_t a[N];						     \
    uint8_t r[POLYETA_PACKEDBYTES];				     \
    int32_t a_jazz[N];						     \
    uint8_t r_jazz[POLYETA_PACKEDBYTES];			     \
    for(int t=0; t<TESTS; t++) {				     \
      fillarrN(a, a_jazz);					     \
      fillarr(uint8_t, POLYETA_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYETA_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);				     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);			     \
      eqarrN(a, a_jazz, function_name);			     \
      eqarr(POLYETA_PACKEDBYTES, PRIx8, r, r_jazz, function_name);   \
    }								     \
    printf("PASS: %s\n", function_name);			     \
  }

#define checkpolyetaunpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYETA_PACKEDBYTES];                                  \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYETA_PACKEDBYTES];                             \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYETA_PACKEDBYTES, r);                      \
      memcpy(r_jazz, r, POLYETA_PACKEDBYTES);                        \
      FUNCTION_C((poly *) a, r);				     \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);			     \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYETA_PACKEDBYTES, PRIx8, r, r_jazz, function_name);   \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt0pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYT0_PACKEDBYTES];				     \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYT0_PACKEDBYTES];				     \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYT0_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYT0_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYT0_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt0unpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								      \
    int32_t a[N];						      \
    uint8_t r[POLYT0_PACKEDBYTES];				      \
    int32_t a_jazz[N];						      \
    uint8_t r_jazz[POLYT0_PACKEDBYTES];				      \
    for(int t=0; t<TESTS; t++) {				      \
      fillarrN(a, a_jazz);					      \
      fillarr(uint8_t, POLYT0_PACKEDBYTES, r);			      \
      memcpy(r_jazz, r, POLYT0_PACKEDBYTES);			      \
      FUNCTION_C((poly *) a, r);				      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);			      \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYT0_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }								      \
    printf("PASS: %s\n", function_name);			      \
  }

#define checkpolyt1pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYT1_PACKEDBYTES];                                   \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYT1_PACKEDBYTES];                              \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYT1_PACKEDBYTES, r);                       \
      memcpy(r_jazz, r, POLYT1_PACKEDBYTES);                         \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYT1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt1unpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                                   \
    int32_t a[N];                                                     \
    uint8_t r[POLYT1_PACKEDBYTES];                                    \
    int32_t a_jazz[N];                                                \
    uint8_t r_jazz[POLYT1_PACKEDBYTES];                               \
    for(int t=0; t<TESTS; t++) {                                      \
      fillarrN(a, a_jazz);                                            \
      fillarr(uint8_t, POLYT1_PACKEDBYTES, r);                        \
      memcpy(r_jazz, r, POLYT1_PACKEDBYTES);                          \
      FUNCTION_C((poly *) a, r);                                      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);                       \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYT1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }                                                                 \
    printf("PASS: %s\n", function_name);                              \
  }

#define checkpolyzpack(FUNCTION_C, FUNCTION_JASMIN, function_name)   \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYZ_PACKEDBYTES];				     \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYZ_PACKEDBYTES];				     \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYZ_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYZ_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYZ_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyzunpack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                   \
    int32_t a[N];                                                     \
    uint8_t r[POLYZ_PACKEDBYTES];				      \
    int32_t a_jazz[N];                                                \
    uint8_t r_jazz[POLYZ_PACKEDBYTES];				      \
    for(int t=0; t<TESTS; t++) {                                      \
      fillarrN(a, a_jazz);                                            \
      fillarr(uint8_t, POLYZ_PACKEDBYTES, r);			      \
      memcpy(r_jazz, r, POLYZ_PACKEDBYTES);			      \
      FUNCTION_C((poly *) a, r);                                      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);                       \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYZ_PACKEDBYTES, PRIx8, r, r_jazz, function_name);      \
    }                                                                 \
    printf("PASS: %s\n", function_name);                              \
  }

#define checkpolyw1pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYW1_PACKEDBYTES];                                   \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYW1_PACKEDBYTES];                              \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYW1_PACKEDBYTES, r);                       \
      memcpy(r_jazz, r, POLYW1_PACKEDBYTES);                         \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYW1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }
