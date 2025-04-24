GENES_EXEC = genes
DOC_EXEC = doc


.PHONY: genes doc clean

genes:
	g++ -o $(GENES_EXEC) genealogy.cpp
	./$(GENES_EXEC)

doc:
	g++ -o $(DOC_EXEC) history.cpp
	./$(DOC_EXEC)

clean:
	rm -f $(GENES_EXEC)
	rm -f $(DOC_EXEC)
	clear
