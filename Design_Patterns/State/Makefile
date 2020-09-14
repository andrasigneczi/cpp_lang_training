CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=State.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin State

State: $(OBJS)
	$(CXX) $(LDFLAGS) -o State $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) State

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) State