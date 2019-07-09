CPP = gcc
CFLAGS = -Wall
LFLAGS =

OBJS = example.o tinystr.o

ALL: $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o example $(LFLAGS)

%.o: %.c %.h
	$(CPP) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
