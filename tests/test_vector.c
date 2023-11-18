#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "vector.h"

void vector_new_test(void);
void vector_push_back_test(void);
void vector_iter_test(void);
void vector_fill_test(void);
void vector_with_multiple_types_test(void);
void vector_with_struct_test(void);
void vector_2d_test(void);

int main(void) {
   int ret;
   CU_pSuite suite;
   CU_initialize_registry();

   suite = CU_add_suite("Vector Test", NULL, NULL);
   CU_add_test(suite, "Vector New Test", vector_new_test);
   CU_add_test(suite, "Vector Push Back Test", vector_push_back_test);
   CU_add_test(suite, "Vector Iter Test", vector_iter_test);
   CU_add_test(suite, "Vector Fill Test", vector_fill_test);
   CU_add_test(suite, "Vector With Multiple Types Test", vector_with_multiple_types_test);
   CU_add_test(suite, "Vector With Struct Test", vector_with_struct_test);
   CU_add_test(suite, "Vector 2D Test", vector_2d_test);

   CU_basic_run_tests();
   ret = CU_get_number_of_failures();
   CU_cleanup_registry();
   return ret;
}

void vector_new_test(void) {
   vector(int) empty_vector1 = vector_new(int);
   vector(int) empty_vector2 = vector_new_with_size(int, 0);
   vector(int) sized_vector = vector_new_with_size(int, 3);

   CU_ASSERT_PTR_NULL(empty_vector1);
   CU_ASSERT_EQUAL(vector_size(empty_vector1), 0);
   CU_ASSERT_PTR_NULL(vector_begin(empty_vector1));
   CU_ASSERT_PTR_NULL(vector_end(empty_vector1));

   CU_ASSERT_PTR_NULL(empty_vector2);
   CU_ASSERT_EQUAL(vector_size(empty_vector2), 0);
   CU_ASSERT_PTR_NULL(vector_begin(empty_vector2));
   CU_ASSERT_PTR_NULL(vector_end(empty_vector2));

   CU_ASSERT_PTR_NOT_NULL(sized_vector);
   CU_ASSERT_EQUAL(vector_size(sized_vector), 3);
   CU_ASSERT_PTR_EQUAL(vector_begin(sized_vector), sized_vector);
   CU_ASSERT_PTR_EQUAL(vector_end(sized_vector), &sized_vector[3]);
   for (int i = 0; i < 3; i++) {
      CU_ASSERT_EQUAL(sized_vector[i], 0);
   }

   vector_free(empty_vector1);
   vector_free(empty_vector2);
   vector_free(sized_vector);
   return;
}

void vector_push_back_test(void) {
   vector(int) vector = vector_new(int);

   vector_push_back(vector, 1);
   vector_push_back(vector, 2);
   vector_push_back(vector, 3);

   CU_ASSERT_EQUAL(vector_size(vector), 3);
   CU_ASSERT_EQUAL(vector[0], 1);
   CU_ASSERT_EQUAL(vector[1], 2);
   CU_ASSERT_EQUAL(vector[2], 3);

   vector_free(vector);
   return;
}

void vector_iter_test(void) {
   vector(int) vector = vector_new(int);

   vector_push_back(vector, 1);
   vector_push_back(vector, 2);
   vector_push_back(vector, 3);
   vector_push_back(vector, 4);
   vector_push_back(vector, 5);

   int i = 0;
   for (vector_iterator(int) it = vector_begin(vector); it != vector_end(vector); ++it) {
      CU_ASSERT_EQUAL(*it, ++i);
   }

   vector_free(vector);
   return;
}

void vector_fill_test(void) {
   vector(int) vector = vector_new_with_size(int, 5);

   vector_fill(vector, 15);

   for (vector_iterator(int) it = vector_begin(vector); it != vector_end(vector); ++it) {
      CU_ASSERT_EQUAL(*it, 15);
   }

   vector_free(vector);
   return;
}

void vector_with_multiple_types_test(void) {
   vector(int) int_vector = vector_new(int);
   vector(double) double_vector = vector_new(double);
   vector(char) char_vector = vector_new(char);

   vector_push_back(int_vector, 1);
   vector_push_back(int_vector, 2);
   vector_push_back(int_vector, 3);
   vector_push_back(double_vector, 1.1);
   vector_push_back(double_vector, 2.2);
   vector_push_back(double_vector, 3.3);
   vector_push_back(char_vector, 'a');
   vector_push_back(char_vector, 'b');
   vector_push_back(char_vector, 'c');

   CU_ASSERT_EQUAL(int_vector[0], 1);
   CU_ASSERT_EQUAL(int_vector[1], 2);
   CU_ASSERT_EQUAL(int_vector[2], 3);
   CU_ASSERT_EQUAL(double_vector[0], 1.1);
   CU_ASSERT_EQUAL(double_vector[1], 2.2);
   CU_ASSERT_EQUAL(double_vector[2], 3.3);
   CU_ASSERT_EQUAL(char_vector[0], 'a');
   CU_ASSERT_EQUAL(char_vector[1], 'b');
   CU_ASSERT_EQUAL(char_vector[2], 'c');

   vector_free(int_vector);
   vector_free(double_vector);
   vector_free(char_vector);
   return;
}

void vector_with_struct_test(void) {
   struct point {
      int x;
      int y;
   };

   vector(struct point) vector = vector_new(struct point);

   struct point p1 = {1, 2};
   struct point p2 = {3, 4};
   vector_push_back(vector, p1);
   vector_push_back(vector, p2);

   CU_ASSERT_EQUAL(vector[0].x, 1);
   CU_ASSERT_EQUAL(vector[0].y, 2);
   CU_ASSERT_EQUAL(vector[1].x, 3);
   CU_ASSERT_EQUAL(vector[1].y, 4);

   vector_free(vector);
   return;
}

void vector_2d_test(void) {
   const int H = 2, W = 3;
   vector(vector(int)) vector_2d = vector_new_with_size(vector(int), H);
   vector_fill(vector_2d, vector_new_with_size(int, W));
   for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
         vector_2d[i][j] = i * W + j;
      }
   }

   CU_ASSERT_EQUAL(vector_2d[0][0], 0);
   CU_ASSERT_EQUAL(vector_2d[0][1], 1);
   CU_ASSERT_EQUAL(vector_2d[0][2], 2);
   CU_ASSERT_EQUAL(vector_2d[1][0], 3);
   CU_ASSERT_EQUAL(vector_2d[1][1], 4);
   CU_ASSERT_EQUAL(vector_2d[1][2], 5);

   vector_free_each(vector_2d, vector_free);
   return;
}
