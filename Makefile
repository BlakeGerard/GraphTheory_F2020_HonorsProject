BIN = graph.exe
TEST = tests.exe

LIBS = 
INCL = -I. -I./include
SRCS = driver.cpp ./src/*
TEST_SRCS = tests.cpp ./src/*

CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: bin

bin: $(SRCS)
	$(CXX) -o $(BIN) $(CXXFLAGS) $(INCL) $(LIBS) $(SRCS)

test: $(TEST_SRCS)
	$(CXX) -o $(TEST) $(CXXFLAGS) $(INCL) $(LIBS) $(TEST_SRCS)

clean: 
	rm *.exe
