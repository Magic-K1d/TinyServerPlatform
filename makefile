CG = g++

DEBUG = 1


client: Client.cpp Client.h Utils.h Utils.cpp
	$(CG) -std=c++11 -o client $^ 

server: Server.cpp Server.h Utils.h Utils.cpp Event.h Event.cpp
	$(CG) -std=c++11 -o server $^


clean:
	-rm -r client server
