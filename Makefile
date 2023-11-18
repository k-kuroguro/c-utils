CC := gcc
CFLAGS := -W -Wall

TEST_CFLAGS := $(CFLAGS)
TEST_INC := -Icutils
TEST_LIBDIR := -L/usr/lib
TEST_LIB := -lcunit

all: test

test: test_vector

test_vector: tests/test_vector.c cutils/vector.c
	$(CC) $^ $(TEST_CFLAGS) $(TEST_INC) $(TEST_LIBDIR) $(TEST_LIB) -o $@ && ./$@


.PHONY: clean
clean:
	-rm *.o
	-rm test_vector

.DEFAULT_GOAL=all
