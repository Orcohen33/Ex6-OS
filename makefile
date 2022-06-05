CXX=gcc

GXX=g++

all: main1 ClientActiveObject poll_client poll_server guard singleton

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

poll_server: poll_server.o
	$(GXX) -Wall poll_server.cpp -o poll_server -lpthread

poll_server.o: poll_server.cpp
	$(GXX) -Wall -c poll_server.cpp -lpthread -g

poll_client: poll_client.o
	$(GXX) -Wall poll_client.cpp -o poll_client -lpthread

poll_server.o: poll_client.cpp
	$(GXX) -Wall -c poll_client.cpp -lpthread -g

guard : guard.o
	$(GXX) -Wall guard.o -o guard -lpthread

guard.o : guard.cpp
	$(GXX) -Wall -c guard.cpp -lpthread -g

singleton : singleton.o
	$(GXX) -Wall singleton.o -o singleton -lpthread

singleton.o : singleton.cpp
	$(GXX) -Wall -c singleton.cpp -lpthread -g

clean:
	rm -f *.o *.gch main1 client guard singleton poll_client poll_server