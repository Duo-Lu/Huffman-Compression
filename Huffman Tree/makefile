all: huff

huff: main.o PriorityQueue.h HTNode.h BitStream.h HuffmanTree.h FrequencyCounter.o Character.o EmptyDataCollectionException.o HTNode.o HuffmanTree.o BitStream.o
	g++ -Wall -std=c++11 -o huff main.o FrequencyCounter.o Character.o EmptyDataCollectionException.o HTNode.o HuffmanTree.o BitStream.o

main.o: main.cpp HuffmanTree.h PriorityQueue.h HTNode.h BitStream.h EmptyDataCollectionException.h FrequencyCounter.h Character.h
	g++ -c main.cpp

BitStream.o: BitStream.cpp BitStream.h PriorityQueue.h FrequencyCounter.h Character.h HTNode.h HuffmanTree.h 
	g++ -c BitStream.cpp

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h PriorityQueue.h FrequencyCounter.h Character.h HTNode.h
	g++ -c HuffmanTree.cpp

FrequencyCounter.o: FrequencyCounter.cpp  FrequencyCounter.h
	g++ -c FrequencyCounter.cpp

Character.o: Character.cpp Character.h
	g++ -c Character.cpp

HTNode.o: HTNode.cpp HTNode.h 
	g++ -c HTNode.cpp

EmptyDataCollectionException.o:	EmptyDataCollectionException.cpp EmptyDataCollectionException.h
	g++ -c EmptyDataCollectionException.cpp

clean:	
	rm -f sim *.o

