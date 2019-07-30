CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Facade

Facade: $(OBJS)
	$(CXX) $(LDFLAGS) -o Facade $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Facade

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Facade