CXX=g++
CPPFLAGS=-g -std=c++17 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin AbstractFactory

AbstractFactory: $(OBJS)
	$(CXX) $(LDFLAGS) -o AbstractFactory $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) AbstractFactory

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) AbstractFactory