CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic -I${RW_HOME}/include/SourcePro2016 -D_RWCONFIG=m
LDFLAGS=-g
LDLIBS=-L${CRTI_RW_LIBPATH} ${CRTI_RW_LIBS}

SRCS=main.cpp OrderedUnordered.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin OrderedUnordered

OrderedUnordered: $(OBJS)
	$(CXX) $(LDFLAGS) -o OrderedUnordered $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) OrderedUnordered

DelBin:
	$(RM) OrderedUnordered