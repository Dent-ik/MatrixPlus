CFLAGS = -Wall -Werror -Wextra

all: matrix.a

build: matrix.cc
	gcc -c $(CFLAGS) -lstdc++ -std=c++17 matrix.cc -o matrix.o

matrix.a: build
	ar rcs matrix.a matrix.o
	ranlib matrix.a

clean:
	rm -rf *.o *.out matrix.a unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: test
	leaks -atExit -- ./unit_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.cc *.h ./unit_tests/*.cc --verbose
	clang-format -i *.cc *.h ./unit_tests/*.cc --verbose
	clang-format -n *.cc *.h --verbose
	clang-format -i *.cc *.h --verbose
	rm .clang-format

test: matrix.a ./unit_tests/unit_tests.cc
	gcc -lgtest -lstdc++ -std=c++17 --coverage matrix.a ./unit_tests/unit_tests.cc -o unit_test
	./unit_test

gcov_report: test
	gcc  --coverage ./unit_tests/unit_tests.cc matrix.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info --ignore-errors mismatch --no-external -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

