# file to build
sources = lab1.cpp

# file to output
target = diff

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build:
	$(compiler) $(flags) $(sources) -o $(target)

# run both tests saving their results to files
run: build
	./$(target) file1.txt file2.txt > test1Result.txt
	./$(target) file11.txt file12.txt > test2Result.txt

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
# I added deletion for the result files just to be on the safe side
clean:
	rm -f $(target)
	rm ./a.out
	rm test1Result.txt
	rm test2Result.txt

# check if the programs output matches the desired output
test: run
	diff -C 3 test1Result.txt test1Solution.txt
	diff -C 3 test2Result.txt test2Solution.txt
	@echo tests passed great job