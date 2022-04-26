picalc: main.c picalc.c
	gcc -o picalc main.c picalc.c -lm -pthread

install: picalc
	mv picalc /usr/bin/picalc