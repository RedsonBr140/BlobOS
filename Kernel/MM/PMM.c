#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <MM/PMM.h>
#include <limine.h>
#include <stddef.h>

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST, .revision = 0};

// Set a bit in the bitmap.
void PMM_Set(int bit) { PMM_Bitmap[bit / 64] |= (1 << (bit % 64)); }

// Unset a bit in the bitmap.
void PMM_Unset(int bit) { PMM_Bitmap[bit / 64] &= ~(1 << (bit % 64)); }

// Test if bit is set.
// Return: 1 or 0.
uint8_t PMM_Test(int bit) { return PMM_Bitmap[bit / 64] & (1 << (bit % 64)); }

// Find the first free blocks of memory
int64_t PMM_First_Free_Blocks(int64_t num_blocks) {
    if (num_blocks == 0) // How can we return no memory?
        return -1;
    for (uint64_t i = 0; i < PMM_MaxBlocks / 64; i++) {
        if (PMM_Bitmap[i] != 0xFFFFFFFFFFFFFFFF) {
            for (int64_t j = 0; j < 64; j++) {
                int32_t bit = 1 << j;
                if (!(PMM_Bitmap[i] & j)) {
                    int64_t start_bit = i * 64 + bit;
                    uint64_t free_blocks = 0;

                    for (uint64_t count = 0; count <= num_blocks; count++) {
                        if (!PMM_Test(start_bit + count))
                            free_blocks++;
                    }
                }
            }
        }
    }
}

void PMM_Init() {
    if (memmap_request.response == NULL ||
        memmap_request.response->entry_count < 1) {
        panic("Memory map unavailable!");
    }

    kprintf("[OK] Initialize Physical Memory Manager\n");

    for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        kprintf("Region %p: Base: %p | Lenght: %p | Type: %d\n", i, entry->base,
                entry->length, entry->type);

        PMM_MemorySize += entry->length;
    }
    kprintf("[PMM] Total Physical Memory in megabytes: %d MiB\n",
            (PMM_MemorySize / 1024) / 1024 - 1);
}
