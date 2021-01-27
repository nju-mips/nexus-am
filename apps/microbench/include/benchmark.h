#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <am.h>
#include <klib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MB * 1024 * 1024
#define KB * 1024

#define REF_CPU    "i7-7700K @ 4.20GHz"
#define REF_SCORE  100000

#ifdef SETTING_TEST
  #define SETTING 0
#elif defined SETTING_TRAIN
  #define SETTING 1
#elif defined SETTING_REF
  #define SETTING 2
#elif defined SETTING_HUGE
  #define SETTING 3
#else
  #error "Must define SETTING_TEST/SETTING_TRAIN/SETTING_REF"
#endif

#define REPEAT  1

//                  size |  heap | time |  checksum
#define QSORT_S {      100,   1 KB,      0, 0x08467105}
#define QSORT_M {    30000, 128 KB,      0, 0xa3e99fe4}
#define QSORT_L {   400000,1640 KB,  20546, 0x216f5851}
#define QSORT_H { 12800000,  64 MB,1034000, 0x17f28691}
#define QUEEN_S {        8,   0 KB,      0, 0x0000005c}
#define QUEEN_M {       11,   0 KB,      0, 0x00000a78}
#define QUEEN_L {       12,   0 KB,   4707, 0x00003778}
#define QUEEN_H {       15,   1 MB,1024000, 0x0022c710}
#define    BF_S {        2,  32 KB,      0, 0xa6f0079e}
#define    BF_M {       25,  32 KB,      0, 0xa88f8a65}
#define    BF_L {      180,  32 KB,  23673, 0x9221e2b3}
#define    BF_H {     1360, 512 KB, 910000, 0xdb49fbde}
#define   FIB_S {        2,   1 KB,      0, 0x7cfeddf0}
#define   FIB_M {       23,  16 KB,      0, 0x94ad8800}
#define   FIB_L {       91, 256 KB,  28318, 0xebdc5f80}
#define   FIB_H {      305,  64 MB,1086000, 0x00000000}
#define SIEVE_S {      100,   1 KB,      0, 0x00000019}
#define SIEVE_M {   200000,  32 KB,      0, 0x00004640}
#define SIEVE_L { 10000000,   2 MB,  39361, 0x000a2403}
#define SIEVE_H {140000000,  32 MB,1010000, 0x0078bb07}
#define  PZ15_S {        0,   1 KB,      0, 0x00000006}
#define  PZ15_M {        1, 256 KB,      0, 0x0000b0df}
#define  PZ15_L {        2,   2 MB,   4486, 0x00068b8c}
#define  PZ15_H {        2, 110 MB,   4486, 0x00068b8c}
#define DINIC_S {       10,   8 KB,      0, 0x0000019c}
#define DINIC_M {       80, 512 KB,      0, 0x00004f99}
#define DINIC_L {      128,   1 MB,  10882, 0x0000c248}
#define DINIC_H {      628, 100 MB, 980000, 0x0004ba05}
#define  LZIP_S {      128, 128 KB,      0, 0xe05fc832}
#define  LZIP_M {    50000,   1 MB,      0, 0xdc93e90c}
#define  LZIP_L {  1048576,   4 MB,   7593, 0x8d62c81f}
#define  LZIP_H { 54218215, 110 MB, 505000, 0x9547d2f0}
#define SSORT_S {      100,   4 KB,      0, 0x4c555e09}
#define SSORT_M {    10000, 512 KB,      0, 0x0db7909b}
#define SSORT_L {   100000,   4 MB,   4504, 0x4f0ab431}
#define SSORT_H {  4000000, 110 MB,1060000, 0x37cf6f7a}
#define   MD5_S {      100,   1 KB,      0, 0xf902f28f}
#define   MD5_M {   200000, 256 KB,      0, 0xd4f9bc6d}
#define   MD5_L { 10000000,  16 MB,  17239, 0x27286a42}
#define   MD5_H {109999999, 110 MB, 219000, 0xbc1a5b43}

#define BENCHMARK_LIST(def) \
  def(qsort, "qsort", QSORT_S, QSORT_M, QSORT_L, QSORT_H, "Quick sort") \
  def(queen, "queen", QUEEN_S, QUEEN_M, QUEEN_L, QUEEN_H, "Queen placement") \
  def(   bf,    "bf",    BF_S,    BF_M,    BF_L,    BF_H, "Brainf**k interpreter") \
  def(  fib,   "fib",   FIB_S,   FIB_M,   FIB_L,   FIB_H, "Fibonacci number") \
  def(sieve, "sieve", SIEVE_S, SIEVE_M, SIEVE_L, SIEVE_H, "Eratosthenes sieve") \
  def( 15pz,  "15pz",  PZ15_S,  PZ15_M,  PZ15_L,  PZ15_H, "A* 15-puzzle search") \
  def(dinic, "dinic", DINIC_S, DINIC_M, DINIC_L, DINIC_H, "Dinic's maxflow algorithm") \
  def( lzip,  "lzip",  LZIP_S,  LZIP_M,  LZIP_L,  LZIP_H, "Lzip compression") \
  def(ssort, "ssort", SSORT_S, SSORT_M, SSORT_L, SSORT_H, "Suffix sort") \
  def(  md5,   "md5",   MD5_S,   MD5_M,   MD5_L,   MD5_H, "MD5 digest") \

// Each benchmark will run REPEAT times

#define DECL(_name, _sname, _s, _m, _l, _h, _desc) \
  void bench_##_name##_prepare(); \
  void bench_##_name##_run(); \
  int bench_##_name##_validate();

BENCHMARK_LIST(DECL)

typedef struct Setting {
  int size;
  unsigned long mlim, ref;
  uint32_t checksum;
} Setting;

typedef struct Benchmark {
  void (*prepare)();
  void (*run)();
  int (*validate)();
  const char *name, *desc;
  Setting settings[4];
} Benchmark;

extern Benchmark *current;
extern Setting *setting;

typedef struct Result {
  int pass;
  unsigned long tsc, msec;
} Result;

void prepare(Result *res);
void done(Result *res);

// memory allocation
void* bench_alloc(size_t size);
void bench_free(void *ptr);

// random number generator
void bench_srand(uint32_t seed);
uint32_t bench_rand(); // return a random number between 0..32767

// checksum
uint32_t checksum(void *start, void *end);

#ifdef __cplusplus
}
#endif

#endif
