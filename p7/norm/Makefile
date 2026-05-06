CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET   = avl_tree

SRCS = main.cc
HDRS = nodo_b.h nodo_avl.h ab.h abb.h abe.h avl.h nif.h

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
