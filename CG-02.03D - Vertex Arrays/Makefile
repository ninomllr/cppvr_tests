PROG=varrays
OBJS=varrays.cppo zpr.co

CC=gcc
CFLAGS=-Wall -pedantic
LD=gcc
LFLAGS=-lGL -lGLU -lglut -I. -L.
RM=rm -f

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

%.cppo: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.co: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(PROG) $(OBJS)

nowin:
	$(RM) $(PROG).cpp.bak $(PROG).exe $(PROG).ncb $(PROG).sln $(PROG).suo $(PROG).vcproj 

run: all
	./$(PROG)
