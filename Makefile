panserverloc = ./panserver/panServer
boostloc = /home/reined/boost_1_75_0/stage/lib
debugflag = -ggdb -Wall -Wextra
all: testserver testclient clean

server: panServer.o main.o testserver.o
	g++ -I ~/boost_1_75_0 panServer.o main.o  -lpthread -lboost_thread -o server

testserver: testserver.o
	g++ -I ~/boost_1_75_0 testserver.o -lpthread -lboost_thread -o testserver

testclient: testclient.o
	g++ -I ~/boost_1_75_0 testclient.o -lpthread -lboost_thread -o testclient

testclient.o: ./panserver/testclient.cpp
	g++ -I ~/boost_1_75_0 ${debugflag} -c ./panserver/testclient.cpp

testserver.o: ./panserver/testserver.cpp
	g++ -I ~/boost_1_75_0 ${debugflag} -c ./panserver/testserver.cpp

panServer.o: ${panserverloc}/panServer.cpp
	g++ -I ~/boost_1_75_0 ${debugflag} -c ${panserverloc}/panServer.cpp

main.o: ./panserver/main.cpp
	g++ -I ~/boost_1_75_0 -I ${panserverloc}/ -lboost_system $(debugflag) -c ./panserver/main.cpp



clean:
	rm *.o
