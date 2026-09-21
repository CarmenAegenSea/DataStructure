CXX      = gcc
CXXFLAGS = -Wall -g -Iinclude
CFLAGS   = -x c

SRC_DIR = src
TEXT_DIR = text
INC_DIR = include

List.o: $(SRC_DIR)/List.cpp $(INC_DIR)/List.h $(INC_DIR)/Def.h
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $(SRC_DIR)/List.cpp -o $@

Stack.o: $(SRC_DIR)/Stack.cpp $(INC_DIR)/Stack.h $(INC_DIR)/Def.h
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $(SRC_DIR)/Stack.cpp -o $@

text1: text/text1.cpp List.o
	$(CXX) $(CXXFLAGS) $(CFLAGS) text/text1.cpp List.o -o $@ -lm

clean:
	rm -f *.o text1

.PHONY: clean
