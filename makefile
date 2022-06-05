CXX=gcc


all: main1 ClientActiveObject

main1: main1.o ActiveObject.o SafeQueue.o
	$(CXX) -Wall ActiveObject.o SafeQueue.o main1.o -o main1 -lpthread
	
main1.o: SafeQueue.h ActiveObject.h main1.c 
	$(CXX) -Wall -c main1.c -lpthread -g

ActiveObject.o: SafeQueue.h ActiveObject.h ActiveObject.c
	$(CXX) -Wall -c ActiveObject.c -lpthread -g

SafeQueue.o: SafeQueue.h SafeQueue.c
	$(CXX) -Wall -c SafeQueue.c -lpthread -g

ClientActiveObject: ClientActiveObject.o
	$(CXX) -Wall ClientActiveObject.o -o client -lpthread

ClientActiveObject.o: ClientActiveObject.c
	$(CXX) -Wall -c ClientActiveObject.c -lpthread -g

clean:
	rm -f *.o *.gch main1 client