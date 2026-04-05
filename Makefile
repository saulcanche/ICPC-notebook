CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lgtest -lgtest_main -pthread

# Find all source and test files
SRCS = $(wildcard src/math/*.cpp)
TEST_SRCS = $(wildcard tests/*.cpp)

# Convert .cpp filenames to .o (object) filenames
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# The final executable depends on all object files
run_tests: $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# Rule to compile any .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the compiled files
clean:
	rm -f src/math/*.o tests/*.o run_tests
