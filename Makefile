CXX = g++ -std=c++14 -Wall -O2
DIR = /usr/local
LIBS = -lgecodedriver -lgecodesearch -lgecodeminimodel -lgecodeint -lgecodekernel -lgecodesupport

ex1: src/example1.cpp
	$(CXX) -o main $^ -I$(DIR)/include/gecode -L$(DIR)/lib $(LIBS)

ex2: src/example2.cpp
	$(CXX) -o main $^ -I$(DIR)/include/gecode -L$(DIR)/lib $(LIBS)

ex3: src/example3.cpp
	$(CXX) -o main $^ -I$(DIR)/include/gecode -L$(DIR)/lib $(LIBS)