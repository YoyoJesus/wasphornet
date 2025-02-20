MAP_EXEC = rosterObjectMap
SET_EXEC = rosterObjectSet
INPUT_FILES = cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

map:
	g++ -o $(MAP_EXEC) rosterObjectMap.cpp
	./$(MAP_EXEC) $(INPUT_FILES)

set:
	g++ -o $(SET_EXEC) rosterObjectSet.cpp
	./$(SET_EXEC) $(INPUT_FILES)

clean:
	rm -f $(MAP_EXEC) $(SET_EXEC)