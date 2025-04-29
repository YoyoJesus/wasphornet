ATC_EXEC = atc 
REGISTRY_EXEC = registry

. PHONY: atc registry clean

atc:
	g++ -o $(ATC_EXEC) atc.cpp
	./$(ATC_EXEC)

registry:
	g++ -o $(REGISTRY_EXEC) Registry.cpp
	./$(REGISTRY_EXEC)

clean:
	rm -f $(ATC_EXEC)
	clear