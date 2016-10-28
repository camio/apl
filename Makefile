.PHONY: all

all: echo_client echo_server

echo_client : echo_client.cpp client.h channel.h
	g++ -DASIO_STANDALONE -fconcepts -I. -I../promise -I../asio/asio/include -std=c++1y -o $@ $< -lpthread

echo_server : echo_server.cpp server.h channel.h
	g++ -DASIO_STANDALONE -fconcepts -I. -I../promise -I../asio/asio/include -std=c++1y -o $@ $< -lpthread

main : main.cpp
	g++ -DASIO_STANDALONE -I../asio/asio/include -std=c++1y -o $@ $< -lpthread


.PHONY: clean

clean :
	$(RM) main echo_server echo_client
