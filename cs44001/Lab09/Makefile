CARBUYER_EXEC = carbuyer
FIGURE_EXEC = figure

.PHONY: carbuyer figure clean

carbuyer:
	g++ -o $(CARBUYER_EXEC) ./part1/CarBuyer.cpp ./part1/CarFactory.cpp
	./$(CARBUYER_EXEC)

figure:
	g++ -o $(FIGURE_EXEC) ./part2/bridgeFigures.cpp
	./$(FIGURE_EXEC)

clean:
	rm -f $(CARBUYER_EXEC) $(FIGURE_EXEC)
	clear
