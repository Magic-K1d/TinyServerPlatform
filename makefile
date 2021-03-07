CG = g++

DEBUG = 1


client: Client.cpp Client.h Utils.h Utils.cpp
	$(CG) -std=c++11 -o client $^ 

server: Server.cpp Server.h Utils.h Utils.cpp Event.h Event.cpp Epoller.h Epoller.cpp Connection.h Connection.cpp Threadpool.h Threadpool.cpp Config.h main.cpp
	$(CG) -std=c++11 -o server $^ -lpthread


clean:
	-rm -r client server
