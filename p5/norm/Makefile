CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET   = p5_ordenacion
SRCS     = main.cc
HEADERS  = sequence.h static_sequence.h nif.h sort_algorithms.h s_method.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean
