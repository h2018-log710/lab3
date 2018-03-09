CC=gcc
CFLAGS=-Wall -g 
LDFLAGS=
LDLIBS=
TARGET=Log710H18_lab03
EXTRA_TARGET=
VPATH=src
ODIR=obj
BINDIR=bin

objects=main.o memory_manager.o first_fit.o best_fit.o worst_fit.o next_fit.o list.o
extra_objects=

$(TARGET): $(objects) $(EXTRA_TARGET)
    @mkdir -p $(BINDIR)
    $(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(objects)

$(EXTRA_TARGET): $(extra_objects)
    @mkdir -p $(BINDIR)
    $(CC) -o $(BINDIR)/$(EXTRA_TARGET) $(LDFLAGS) $(extra_objects)

main.o: memory_manager.h
memory_manager.o: memory_manager.h first_fit.h best_fit.h worst_fit.h next_fit.h
first_fit.o: first_fit.h
best_fit.o: best_fit.h
worst_fit.o: worst_fit.h
next_fit.o: next_fit.h
list.o: list.h

clean:
    rm $(objects) $(BINDIR)/$(TARGET)

run: $(TARGET)
    ./$(BINDIR)/$(TARGET)
