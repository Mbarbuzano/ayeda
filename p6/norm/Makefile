CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET   = arbol
SRCS     = main.cc
HDRS     = nodo_b.h ab.h abe.h abb.h nif.h

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean