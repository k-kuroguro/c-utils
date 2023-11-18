#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector_metadata_t {
   size_t valid_size;
   size_t allocated_size;
} vector_metadata_t;

#define vector(type) type *
#define vector_iterator(type) vector(type)
#define vector_new(type) (vector_new_with_size(type, 0))
#define vector_new_with_size(type, size) ((vector(type))_vector_new_with_size(size, sizeof(type)))
#define vector_size(vector) ((vector) ? _vector_to_metadata(vector)->valid_size : 0)
#define vector_begin(vector) (vector)
#define vector_end(vector) ((vector) ? (vector) + vector_size(vector) : NULL)
#define vector_fill(vector, value)                       \
   do {                                                  \
      for (size_t i = 0; i < vector_size(vector); ++i) { \
         (vector)[i] = (value);                          \
      }                                                  \
   } while (0)
#define vector_recursively_free(vector, free_func)       \
   do {                                                  \
      for (size_t i = 0; i < vector_size(vector); ++i) { \
         (free_func)((vector)[i]);                       \
      }                                                  \
      vector_free(vector);                               \
   } while (0)
#define vector_push_back(vector, value)                                        \
   do {                                                                        \
      if ((vector) == NULL) {                                                  \
         (vector) = _vector_new_with_size(1, sizeof(vector));                  \
         (vector)[0] = (value);                                                \
      } else {                                                                 \
         size_t new_size = vector_size(vector) + 1;                            \
         if (new_size > _vector_to_metadata(vector)->allocated_size) {         \
            (vector) = _vector_realloc((vector), new_size, sizeof(*(vector))); \
         }                                                                     \
         _vector_to_metadata(vector)->valid_size = new_size;                   \
         (vector)[vector_size(vector) - 1] = (value);                          \
      }                                                                        \
   } while (0)
#define _vector_allocated_size(vector) ((vector) ? _vector_to_metadata(vector)->allocated_size : 0)
#define _vector_to_metadata(vector) (&((vector_metadata_t *)(vector))[-1])
#define _metadata_to_vector(metadata) ((void *)(&((vector_metadata_t *)(metadata))[1]))

void *_vector_new_with_size(size_t size, size_t element_size);
void *_vector_realloc(void *vector, size_t size, size_t element_size);
void *vector_free(void *vector);

#endif /* VECTOR_H_ */
