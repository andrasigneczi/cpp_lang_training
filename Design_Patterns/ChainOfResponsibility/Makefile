CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin ChainOfResponsibility

ChainOfResponsibility: $(OBJS)
	$(CXX) $(LDFLAGS) -o ChainOfResponsibility $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) ChainOfResponsibility

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) ChainOfResponsibility