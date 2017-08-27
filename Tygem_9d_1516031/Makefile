# program name and object files
PROGRAM = tygem

OBJS = tygem.o

# define
CC = gcc
CFLAGS = -O3
LDFLAGS = -lstdc++ -lpthread -lm

# suffixes rule
.SUFFIXES: .cpp .o

# target
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^ $(LDFLAGS)

# suffixe rule
.cpp.o:
	$(CC) $(CFLAGS) -c $<

# delete target
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
	$(RM) *.gcda
	$(RM) *.gcno

