siguel: main.o read.o qryinspect.o qrycustom.o geo.o figlist.o
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all main.o read.o qryinspect.o qrycustom.o geo.o figlist.o -lm -o siguel
main.o: main.c read.o geo.o qryinspect.o qrycustom.o figlist.o figures.h figlist.h geo.h qryinspect.h qrycustom.h read.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c main.c -lm -o main.o
read.o: read.c geo.o qryinspect.o qrycustom.o figlist.o figures.h geo.h figlist.h qryinspect.h qrycustom.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c read.c -lm -o read.o
qryinspect.o: qryinspect.c figlist.o figures.h figlist.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c qryinspect.c -lm -o qryinspect.o
qrycustom.o: qrycustom.c figlist.o figures.h figlist.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c qrycustom.c -o qrycustom.o
geo.o: geo.c figures.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c geo.c -o geo.o
figlist.o: figlist.c figures.h
	gcc -std=c99 -g -Wall -Wextra -fmax-errors=10 -fstack-protector-all -c figlist.c -o figlist.o
clean:
	rm -f *.o siguel
