.PHONY:clean
all: client.cc server.cc
 g++ client.cc -o client -I/usr/local/include -L/usr/local/lib -lpthread -std=c++11
 g++ server.cc -o server -I/usr/local/include -L/usr/local/lib -lpthread -std=c++11
clean:
 rm -f client server