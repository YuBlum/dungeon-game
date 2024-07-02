#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INFO(MSG, ...) printf("INFO: " MSG "\n", ## __VA_ARGS__)
#define WARN(MSG, ...) printf("WARN: " MSG "\n", ## __VA_ARGS__)
#define ERROR(MSG, ...) do { printf("ERROR: " MSG "\n", ## __VA_ARGS__); exit(1); } while(0)

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;
typedef size_t   usize;

i32
main(void) {
  INFO("hello, world");
  return 0;
}
