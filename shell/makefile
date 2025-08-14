# make all

all: gabba_guul dump

gabba_guul: shell.o builtins.o
	gcc shell.o builtins.o -o gabba_guul
	echo "gabba_guul can now be used. Use ./gabba_guul to run the shell."

shell.o: shell.c builtins.o
	gcc -c shell.c

builtins.o: builtins.c
	gcc -c builtins.c

dump: dump.c
	gcc dump.c -o dump

# make clean
clean:
	echo "Removing executables."
	rm builtins.o shell.o dump gabba_guul