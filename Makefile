CXX+= -std=c++11
CXXFLAGS= -g -O0 -Wall -static

LIBS+= -pthread

INCLUDE_DIR=include
SRC_DIR=src
INCLUDES+= -I$(INCLUDE_DIR)
OUTPUT_DIR=build
PROGRAM=netproj
CXXFLAGS+= $(INCLUDES)

SRCS_C= $(wildcard $(SRC_DIR)/*.c)
SRCS_CPP= $(wildcard $(SRC_DIR)/*.cpp) 
SRCS_CC= $(wildcard $(SRC_DIR)/*.cc)
SRCS_CXX= $(wildcard $(SRC_DIR)/*.cxx)
SRCS= $(SRCS_C) $(SRCS_CC) $(SRCS_CPP) $(SRCS_CXX)
OBJS= $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o) $(SRCS_CC:.cc=.o) $(SRCS_CXX:.cxx=.o)
HEADERS= $(wildcard *.h) $(wildcard *.hh) $(wildcard *.hpp) $(wildcard $(INCLUDE_DIR)/*.hpp) $(wildcard $(INCLUDE_DIR)/*/*.hpp) $(wildcard $(INCLUDE_DIR)/*/*/*.hpp)
DEPS= .make.dep

all: $(OUTPUT_DIR)/$(PROGRAM)

$(OUTPUT_DIR)/$(PROGRAM): $(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm -f $(OUTPUT_DIR)/$(PROGRAM) *.o $(OBJS)

$(DEPS): $(SRCS) $(HEADERS)
	@$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPS);

.PHONY: all clean