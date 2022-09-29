main: main.o getWord.o crc64.o newNode.o newItem.o getHash.o dumpHash.o sortFun.o
	gcc -g -o wordpairs main.o getWord.o crc64.o newNode.o newItem.o getHash.o dumpHash.o sortFun.o
main.o: main.c
	gcc -Wall -g -c main.c  
getWord.o: getWord.c
	gcc -Wall -g -c getWord.c
crc64.o: crc64.c
	gcc -Wall -g -c crc64.c
newNode.o: newNode.c
	gcc -Wall -g -c newNode.c
newItem.o: newItem.c
	gcc -Wall -g -c newItem.c
getHash.o: getHash.c
	gcc -Wall -g -c getHash.c
dumpHash.o: dumpHash.c
	gcc -Wall -g -c dumpHash.c
sortFun.o: sortFun.c
	gcc -Wall -g -c sortFun.c
clean:
	    rm wordpairs main.o getWord.o crc64.o newNode.o newItem.o getHash.o dumpHash.o sortFun.o

