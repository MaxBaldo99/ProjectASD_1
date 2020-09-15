CXX = g++
CXXFLAGS = -std=c++17 -O3

main: 
	$(CXX)  $(CXXFLAGS) utility.h time.h tree.h tree.cpp main.cpp -o main.o

.PHONY: clean
clean:
	rm  *.o 