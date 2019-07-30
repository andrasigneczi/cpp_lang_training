CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=ChatRoom.cpp User.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Mediator

Mediator: $(OBJS)
	$(CXX) $(LDFLAGS) -o Mediator $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Mediator

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Mediator