CXX      = gcc
CXXFLAGS = -Wall -g -Iinclude

SRC_DIR = src
TEXT_DIR = text
INC_DIR = include

List.o: $(SRC_DIR)/List.cpp $(INC_DIR)/List.h $(INC_DIR)/Def.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/List.cpp -o $@

text1: text/text1.cpp List.o
	$(CXX) $(CXXFLAGS) text/text1.cpp List.o -o $@

clean:
	rm -f *.o text1

.PHONY: clean
