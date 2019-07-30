CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Bridge

Bridge: $(OBJS)
	$(CXX) $(LDFLAGS) -o Bridge $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Bridge

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Bridge