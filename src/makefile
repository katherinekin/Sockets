CXX := g++
CXXFLAGS += -std=c++11

.PHONY = all send encode

all: send encode

send: sender.o WalshCode.o
	$(CXX) -o send sender.o WalshCode.o

encode: encoder.o WalshCode.o
	$(CXX) -o encode encoder.o WalshCode.o

WalshCode.o: WalshCode.cpp
	g++ -c WalshCode.cpp 

sender.o:
	g++ -c sender.cpp

encoder.o:
	g++ -c encoder.cpp

clean: rm -f send encode sender.o encoder.o WalshCode.o