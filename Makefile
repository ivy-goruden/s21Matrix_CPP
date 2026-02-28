CXX := g++
FLAGS = -Werror -Wall -Wextra -std=c++17
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
BUILD := ../build/

all:
	make cf
	make test

s21_matrix_oop.a: s21_matrix.cpp s21_matrix.h
	$(CXX) $(FLAGS) -c s21_matrix.cpp
	ar rcs s21_matrix_oop.a s21_matrix.o

tests/%.o: tests/%.cpp
	$(CXX) $(FLAGS) -I/opt/homebrew/include -c $< -o $@

test: s21_matrix_oop.a $(TEST_OBJS)
# MAC
	$(CXX) $(FLAGS) $(TEST_OBJS) -L. s21_matrix_oop.a -I/opt/homebrew/include -L/opt/homebrew/lib -lcheck -lm -lpthread -o main_test.out
# LINUX	
#	$(CXX) $(FLAGS) $(TEST_OBJS) -L. s21_matrix_oop.a -I/opt/homebrew/include -L/opt/homebrew/lib -lcheck -lm -lpthread -lsubunit -o main_test.out
	./main_test.out

clean:
	rm -f *.o *.out *.a *.gcno
	rm -f tests/*.o
	rm -r $(BUILD)

gcov_report:
	mkdir -p $(BUILD)
	$(CXX) -fprofile-arcs -ftest-coverage $(TEST_SRCS) s21_matrix.cpp -o $(BUILD)/gcov_report -I/opt/homebrew/include -L/opt/homebrew/lib -lcheck -lm -lpthread
	$(BUILD)/gcov_report
	lcov -c -d $(BUILD) --base-directory $(CURDIR) -o $(BUILD)/coverage.info
	lcov --extract $(BUILD)/coverage.info "$(CURDIR)/*" -o $(BUILD)/coverage.src.info
	genhtml -o $(BUILD)/report $(BUILD)/coverage.src.info
	open $(BUILD)/report/index.html

# gcov_report:
# 	mkdir -p $(BUILD)
# 	$(CXX) -fprofile-arcs -ftest-coverage $(TEST_SRCS) s21_matrix.cpp -o $(BUILD)/gcov_report -lcheck -lm -lpthread -lsubunit
# 	$(BUILD)/gcov_report
# 	lcov -c -d $(BUILD) --base-directory $(CURDIR) -o $(BUILD)/coverage.info
# 	genhtml -o $(BUILD)/report $(BUILD)/coverage.info
# 	xdg-open $(BUILD)/report/index.html 2>/dev/null || sensible-browser $(BUILD)/report/index.html 2>/dev/null || echo "Open $(BUILD)/report/index.html"

cf:
	clang-format -i *.cpp
	clang-format -i tests/*.cpp