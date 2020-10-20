BIN = graph.exe
TEST = tests.exe
SCANNER = graph_scanner
PARSER = graph_parser

LIBS = 
INCL = -I. -I./include
SRCS = driver.cpp ./src/*
TEST_SRCS = tests.cpp ./src/*

FLEX = flex
BISON = bison
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: scanner parser bin

scanner: $(SCANNER).yy
	$(FLEX) -o $(SCANNER).c $(SCANNER).yy

parser: $(PARSER).y
	$(BISON) -o $(PARSER).c $(PARSER).y

bin: $(SRCS)
	$(CXX) -o $(BIN) $(CXXFLAGS) $(INCL) $(LIBS) $(SRCS)

test: $(TEST_SRCS)
	$(CXX) -o $(TEST) $(CXXFLAGS) $(INCL) $(LIBS) $(TEST_SRCS)

clean: 
	rm *.exe
