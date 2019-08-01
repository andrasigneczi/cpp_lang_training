CXX=g++
CPPFLAGS=-g -std=c++17 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Factory

Factory: $(OBJS)
	$(CXX) $(LDFLAGS) -o Factory $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Factory

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Factory