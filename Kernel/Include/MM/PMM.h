#pragma once
#include <stdint.h>

// 4 Kb block size.
#define BLOCK_SIZE 4096
#define BLOCKS_PER_BYTE 8
#define BLOCK_ALIGN BLOCK_SIZE

// Memory bit array.
static uint64_t *PMM_Bitmap = 0;
// How many blocks are currently in use.
static uint64_t PMM_UsedBlocks = 0;
// The maximum number of blocks.
static uint64_t PMM_MaxBlocks = 0;
// Size of the physical memory.
static uint64_t PMM_MemorySize = 0;

void PMM_Init();
