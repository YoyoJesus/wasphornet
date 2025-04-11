ADAPTER_EXEC = adapter
STATE_EXEC = state

.PHONY: adapter state clean

adapter:
	g++ -o $(ADAPTER_EXEC) AdapterClass.cpp
	./$(ADAPTER_EXEC)

state:
	g++ -o $(STATE_EXEC) process.cpp
	./$(STATE_EXEC)

clean:
	rm -f $(ADAPTER_EXEC)
	rm -f $(STATE_EXEC)
	clear