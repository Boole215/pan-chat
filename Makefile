panserverloc = ./panserver/panServer
boostloc = /home/reined/boost_1_75_0/stage/lib

all: server testserver clean

server: panServer.o main.o testserver.o
	g++ -I ~/boost_1_75_0 panServer.o main.o  -lpthread -lboost_thread -o server

testserver: testserver.o
	g++ -I ~/boost_1_75_0 testserver.o -lpthread -lboost_thread -o testserver

testclient: testclient.o
	g++ -I ~/boost_1_75_0 testclient.o -lpthread -lboost_thread -o testclient

testclient.o: ./panserver/testclient.cpp
	g++ -I ~/boost_1_75_0 -c ./panserver/testclient.cpp

testserver.o: ./panserver/testserver.cpp
	g++ -I ~/boost_1_75_0 -c ./panserver/testserver.cpp

panServer.o: ${panserverloc}/panServer.cpp
	g++  -I ~/boost_1_75_0 -c ${panserverloc}/panServer.cpp

main.o: ./panserver/main.cpp
	g++  -I ~/boost_1_75_0 -I ${panserverloc}/ -lboost_system -c ./panserver/main.cpp



clean:
	rm *.o
