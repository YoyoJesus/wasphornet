PART1_EXEC = part1
PART2_EXEC = part2
PART3_EXEC = part3

.PHONY: part1 part2 part3 clean part1_user_input part2_user_input

part1:
	g++ -o $(PART1_EXEC) ./parts/part1.cpp
	./$(PART1_EXEC) < ./inputs/input.txt > output.txt

part2:
	g++ -o $(PART2_EXEC) ./parts/part2.cpp
	./$(PART2_EXEC) < ./inputs/input2.txt > output.txt


part3:
	g++ -o $(PART3_EXEC) ./parts/part3.cpp
	./$(PART3_EXEC) < ./inputs/input3.txt > output.txt


clean:
	rm -f $(PART1_EXEC) $(PART2_EXEC) $(PART3_EXEC)
	rm -f output.txt

#versions without inputs - not happening for part3
part1_user_input:
	g++ -o $(PART1_EXEC) ./parts/part1.cpp
	./$(PART1_EXEC) > output.txt
	
part2_user_input:
	g++ -o $(PART2_EXEC) ./parts/part2.cpp
	./$(PART2_EXEC) > output.txt