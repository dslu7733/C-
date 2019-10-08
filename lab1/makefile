sources := main.cpp stack.cpp
objs    := $(sources:.cpp=.o)
exec    := main

CC:=g++
CFLAGS:='-std=c99'

start : $(objs)
	echo $(sources)
	echo $(objs)
	$(CC) -o $(exec) $(objs)

.c.o:
	$(CC) -g -o $@ -c $<

clean:
	rm -rf $(exec) $(objs)

