COURSE = cs373
SEMESTER = fall2023

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 1

# Change the following to your own information
LASTNAME = Cataneo
GITUSERID = Vendiblebee8

# The name of the executable
EXE = cataneo_p1

FLAGS = -Wall -w -Wextra -g
# FLAGS = -Wall -O3
CC = g++
OBJ = obj

# Store executables in a subdirectory
all: $(EXE)

$(EXE): cataneo_p1.o
	$(CC) $(FLAGS) cataneo_p1.o -o $@

cataneo_p1.o: cataneo_p1.cpp
	$(CC) $(FLAGS) -c cataneo_p1.cpp -o $@


tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f *.o $(EXE) *.tar.gz
