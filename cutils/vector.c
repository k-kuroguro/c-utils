#include <assert.h>
#include <stdlib.h>

#include "vector.h"

void *_vector_new_with_size(size_t size, size_t element_size) {
   if (size == 0) {
      return NULL;
   }

   vector_metadata_t *ptr = (vector_metadata_t *)malloc(sizeof(vector_metadata_t) + size * element_size);
   assert(ptr != NULL);
   ptr->valid_size = size;
   ptr->allocated_size = size;

   // 型関係なく0で初期化.
   int *vector = (int *)_metadata_to_vector(ptr);
   for (int i = 0; i < (int)size; i++) {
      vector[i] = 0;
   }

   return (void *)vector;
}

void *_vector_realloc(void *vector, size_t size, size_t element_size) {
   vector_metadata_t *metadata = _vector_to_metadata(vector);
   metadata = (vector_metadata_t *)realloc(metadata, sizeof(vector_metadata_t) + size * element_size);
   assert(metadata != NULL);
   metadata->allocated_size = size;
   return _metadata_to_vector(metadata);
}

void *vector_free(void *vector) {
   if (vector == NULL) {
      return NULL;
   }
   free(_vector_to_metadata(vector));
   return NULL;
}
