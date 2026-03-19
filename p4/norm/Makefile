CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = main.cc nif.h dispersion_function.h
OBJ = $(SRC:.cc=.o)

EXEC = langton

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)