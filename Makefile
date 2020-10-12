BIN = graph.exe

LIBS = 
INCL = -I. -I./include
SRCS = driver.cpp ./src/*

CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: bin

bin: $(SRCS)
	$(CXX) -o $(BIN) $(CXXFLAGS) $(INCL) $(LIBS) $(SRCS)	

clean: 
	rm *.exe