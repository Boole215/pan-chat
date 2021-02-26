panserverloc = ./panserver/panServer
boostloc = /home/reined/boost_1_75_0/stage/lib

all: server clean

server: panServer.o main.o
	g++ -I ~/boost_1_75_0 panServer.o main.o  -lpthread -lboost_thread -o server

panServer.o: ${panserverloc}/panServer.cpp
	g++  -I ~/boost_1_75_0 -c ${panserverloc}/panServer.cpp

main.o: ./panserver/main.cpp
	g++  -I ~/boost_1_75_0 -I ${panserverloc}/ -lboost_system -c ./panserver/main.cpp

clean:
	rm *.o
