# Makefile for ATM Management System
# This Makefile compiles the ATM Management System source files into an executable

# Object files needed for the build
objects = src/main.o src/system.o src/auth.o

# Main target: builds the 'atm' executable from object files
atm : $(objects)
	cc -o atm $(objects)

# Dependencies for each object file
main.o : src/header.h
kbd.o : src/header.h
command.o : src/header.h
display.o : src/header.h
insert.o : src/header.h
search.o : src/header.h
files.o : src/header.h
utils.o : src/header.h

# Clean target: removes all object files
clean :
	rm -f $(objects)