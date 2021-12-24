CFLAGS = -c -g -Wall $(shell pkg-config --cflags check)
TST_LIBS = $(shell pkg-config --libs check)

TESTS_NAME=tests
AOC_FILES=../src/*/*.o

.PHONY: tests
tests: days tests.o
	$(CC) -g tests.o $(TST_LIBS) $(AOC_FILES) -o $(TESTS_NAME)

days:
	$(MAKE) -C ../src/ $(MAKECMDGOALS)

tests.o: tests.c tests.h
	gcc $(CFLAGS) tests.c



.PHONY: clean
clean: days
	rm tests.o
	rm $(TESTS_NAME)
