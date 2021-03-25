panserverloc = ./panserver/panServer
boostloc = /home/reined/boost_1_75_0/stage/lib
debugflag = -ggdb -Wall -Wextra
localib = ./libraries/lib
localinc = ./libraries/include
all: testserver testclient appMovement clean

server: panServer.o main.o testserver.o
	g++ -I ~/boost_1_75_0 panServer.o main.o  -lpthread -lboost_thread -o server

appComms: appComms.o
	g++ appComms.o -Wl,-rpath=${localib} -L ${localib} -I ${localinc} -lIrrKlang -lpthread -o appComms

appMovement: appMovement.o
	g++  appMovement.o -o appMovement -lncurses

testserver: testserver.o
	g++ -I ~/boost_1_75_0 testserver.o -lpthread -lboost_thread -o testserver

testclient: testclient.o
	g++ -I ~/boost_1_75_0 testclient.o -lpthread -lboost_thread -o testclient

appComms.o:
	g++ -ggdb -Wall -Wextra -L ${localib} -I ${localinc} -lpthread -lIrrKlang -c ./appComms.cpp

appMovement.o:
	g++  -ggdb -Wall -Wextra -c ./panserver/appMovement.cpp

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
