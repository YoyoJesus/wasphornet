LOGGER_EXEC = logger
GAME_EXEC = game

.PHONY: logger game clean cleanlogger

logger:
	g++ -o $(LOGGER_EXEC) singletonLogger.cpp
	./$(LOGGER_EXEC)

cleanlogger:
	rm -f log.txt

game:
	g++ -o $(GAME_EXEC) templateMethodGames.cpp
	./$(GAME_EXEC)

clean:
	rm -f $(LOGGER_EXEC) $(GAME_EXEC)

