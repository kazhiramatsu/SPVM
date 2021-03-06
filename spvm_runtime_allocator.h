#ifndef SPVM_RUNTIME_ALLOCATOR_H
#define SPVM_RUNTIME_ALLOCATOR_H
#include <stddef.h>
#include "spvm_base.h"
#include "spvm_api.h"

// Parser information
struct SPVM_runtime_allocator {
  // Memory_pool
  SPVM_MEMORY_POOL* memory_pool;
  
  // Free lists
  SPVM_ARRAY** freelists;

  // use memory pool max reference byte size
  int64_t data_max_byte_size_use_memory_pool;
};

SPVM_RUNTIME_ALLOCATOR* SPVM_RUNTIME_ALLOCATOR_new(SPVM_RUNTIME* runtime);
void* SPVM_RUNTIME_ALLOCATOR_malloc(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ALLOCATOR* allocator, int64_t size);
void SPVM_RUNTIME_ALLOCATOR_free_data(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ALLOCATOR* allocator, SPVM_DATA* data);
int32_t SPVM_RUNTIME_ALLOCATOR_get_freelist_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ALLOCATOR* allocator, int64_t size);
void SPVM_RUNTIME_ALLOCATOR_free(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ALLOCATOR* allocator);

#endif
