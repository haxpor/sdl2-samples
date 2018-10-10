# Makefile to build samples
#
# template.c is a testing template source code that other samples can base upon.

srcdir = .

CC = clang
EXE = .out
CFLAGS = -g
LIBS = -lsdl2
TARGETS = \
	  alloc_palette$(EXE) \
	  allocrw$(EXE) \
	  timer$(EXE)

all: $(TARGETS)

alloc_palette$(EXE): $(srcdir)/alloc_palette.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

allocrw$(EXE): $(srcdir)/allocrw.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

timer$(EXE): $(srcdir)/timer.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf $(TARGETS) *.dSYM
