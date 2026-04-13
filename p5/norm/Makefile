CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET   = p5_ordenacion
SRCS     = main.cc
HEADERS  = Sequence.h staticSequence.h nif.h SortAlgorithms.h SortMethod.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean
