CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = hash_table
HEADERS = nif.h dispersion_function.h sequence.h \
          static_sequence.h dynamic_sequence.h \
          exploration_function.h hash_table.h

$(TARGET): main.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cc

clean:
	rm -f $(TARGET)