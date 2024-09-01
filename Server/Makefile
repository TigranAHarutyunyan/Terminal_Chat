CXX = g++
CXX_FLAGS = -Wall -Wextra -std=c++17
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

all : server

server : $(OBJS)
	$(CXX) $(OBJS) -o server

%.o : %.cpp	
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf *.o 

.PHONY : all clean