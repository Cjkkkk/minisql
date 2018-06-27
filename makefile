CC    ?= clang
CXX   ?= clang++

EXE = mini

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++11

CFLAGS = -Wno-deprecated-register -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -Wno-deprecated-register -O0  $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main mc_driver catalogManager API Buffer IndexManager RecordManager Record
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))#加后缀

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 mc_parser.tab.cc mc_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh mc_parser.output parser.o \
				 lexer.o mc_lexer.yy.cc $(EXE)\
				 API.o catalogManager.o\
				  Buffer.o IndexManager.o RecordManager.o Record.o\

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: mc_parser.yy
	bison -d -v mc_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o mc_parser.tab.cc

lexer: mc_lexer.l
	flex --outfile=mc_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c mc_lexer.yy.cc -o lexer.o

# API.o: API.h API.cpp
# 	$(CXX)  $(CXXFLAGS) -c API.cpp 

# catalogManager.o:catalogManager.h catalogManager.cpp
# 	$(CXX)  $(CXXFLAGS) -c catalogManager.cpp 

.PHONY: test
test:
	cd test && ./test0.pl

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)