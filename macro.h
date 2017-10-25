#pragma once

#include <stdint.h>
#include <string.h>

#define ROL(datas,bits) ((datas) << (bits) | (datas) >> (32-(bits)))

#define Tranverse16(x) ((((uint16_t)(x) & 0xff00) >> 8) | (((uint16_t)(x) & 0x00ff) << 8))
#define Tranverse32(x) ((((uint32_t)(x) & 0xff000000) >> 24) | (((uint32_t)(x) & 0x00ff0000) >> 8) | (((uint32_t)(x) & 0x0000ff00) << 8) | (((uint32_t)(x) & 0x000000ff) << 24))
#define Tranverse64(x) ((((uint64_t)(x) & 0xff00000000000000) >> 56) | (((uint64_t)(x) & 0x00ff000000000000) >> 40) | (((uint64_t)(x) & 0x0000ff0000000000) >> 24) | (((uint64_t)(x) & 0x000000ff00000000) >> 8) | (((uint64_t)(x) & 0x00000000ff000000) << 8) | (((uint64_t)(x) & 0x0000000000ff0000) << 24) | (((uint64_t)(x) & 0x000000000000ff00) << 40) | (((uint64_t)(x) & 0x00000000000000ff) << 56))