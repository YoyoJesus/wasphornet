LEMON_EXEC = lemon
ORANGE_EXEC = orange
APPLE_EXEC = apple
PEACH_EXEC = peach

.PHONY: lemon orange apple peach clean

lemon:
	g++ -o $(LEMON_EXEC) lemons.cpp
	./$(LEMON_EXEC)

orange:
	g++ -o $(ORANGE_EXEC) oranges.cpp
	./$(ORANGE_EXEC)

apple:
	g++ -o $(APPLE_EXEC) apples.cpp
	./$(APPLE_EXEC)

peach:
	g++ -o $(PEACH_EXEC) peaches.cpp
	./$(PEACH_EXEC)

clean:
	rm -f $(LEMON_EXEC) $(ORANGE_EXEC) $(APPLE_EXEC) $(PEACH_EXEC)
