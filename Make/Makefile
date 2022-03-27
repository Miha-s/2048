CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lfltk
FILES = Field Cell Window
HEAD_DIR = ../2048/
OBJS = $(patsubst %, %.o, $(FILES))
SRC_DIR  = ../src/

##################################################

%.o: $(SRC_DIR)%.cpp $(HEAD_DIR)%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Field.o: Cell.o

game: $(HEAD_DIR)game.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $< $(OBJS) $(LIBS) -o $@
