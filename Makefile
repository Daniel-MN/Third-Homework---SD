build: 
	gcc -o tema3 -Wall main.c Functions.c FUtils.c FTrie.c
clean:
	rm -rf tema3 *.o