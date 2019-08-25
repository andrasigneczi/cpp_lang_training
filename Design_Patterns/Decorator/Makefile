CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=BackgroundDecorator.cpp Decorator.cpp TitleDecorator.cpp Widget.cpp Window.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: DelBin Decorator

Decorator: $(OBJS)
	$(CXX) $(LDFLAGS) -o Decorator $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
	$(RM) Decorator

full:
	make -C .. clean
	make -C ..

DelBin:
	$(RM) Decorator