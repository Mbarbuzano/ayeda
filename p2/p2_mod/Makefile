CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = ant.cc tape.cc simulator.cc ruleant.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = langton

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)