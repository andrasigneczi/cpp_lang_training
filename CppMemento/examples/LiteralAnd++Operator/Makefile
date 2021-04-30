CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic -Wno-literal-suffix
LDFLAGS=-g
LDLIBS=

SRCS=OperatorPlusPlus.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin operatorplusplus literaloperator

operatorplusplus: $(OBJS)
	$(CXX) $(LDFLAGS) -o operatorplusplus $(OBJS) $(LDLIBS)

literaloperator:  LiteralOperator.o
	$(CXX) $(LDFLAGS) -o literaloperator LiteralOperator.o $(LDLIBS)
	
%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) operatorplusplus
	$(RM) LiteralOperator.o
	$(RM) literaloperator

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) operatorplusplus