CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Adapter

Adapter: $(OBJS)
	$(CXX) $(LDFLAGS) -o Adapter $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Adapter

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Adapter