PROG = graphcolor

INCLUDE_DIR = includes
SRC_DIR = src

HDR_FILES = readgraph.h graph.h graphcolor.h
SRC_FILES = main.cpp readgraph.cpp graph.cpp graphcolor.cpp

HDRS = $(patsubst %.h, $(INCLUDE_DIR)/%.h, $(HDR_FILES))
SRCS = $(patsubst %.cpp, $(SRC_DIR)/%.cpp, $(SRC_FILES))

OBJDIR = object
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))
CC = g++
CFLAGS = -Wall -I$(INCLUDE_DIR)
LIBS = -std=c++11


all : $(OBJDIR) $(PROG)

$(PROG) : $(OBJS)
	$(CC) $(CFLAGS) $(patsubst %.o, $(OBJDIR)/%.o, $(notdir $^)) -o $(PROG) $(LIBS)

object/%.o : %.cpp $(HDRS)
	$(CC) -c $(CFLAGS) $< -o $(OBJDIR)/$(notdir $@) $(LIBS)

$(OBJDIR) :
	mkdir -p $@/

run:
	./$(PROG)

clean:
	rm -rf object/
	rm -f $(PROG)