CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = main.cc svexception.cc tape.cc tape_periodic.cc tape_reflective.cc tape_sliding.cc
OBJ = $(SRC:.cc=.o)

EXEC = langton

$(EXEC): $(OBJ)
  $(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
  $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
  rm -f $(OBJ) $(EXEC)