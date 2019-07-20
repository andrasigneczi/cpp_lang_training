CXX=g++
CPPFLAGS=-g -std=c++11 -g -Wall -pedantic -Wno-literal-suffix -fPIC
LDFLAGS=-g -pthread
LDLIBS=

SRCS=main.cpp CppMemento.cpp stringutil.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
TARGET=cppmemento

all: DelBin $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)


%.o: %.cpp
		$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
		$(RM) $(OBJS)
		$(RM) $(TARGET)

full:
		make -C .. clean
		make -C ..

DelBin:
		$(RM) $(TARGET)
