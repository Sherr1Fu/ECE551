program: test-power.o power.o
	gcc -o program -pedantic -std=gnu99 -Wall -Werror test-power.o power.o
power.o: power.c
	gcc -c -pedantic -std=gnu99 -Wall -Werror power.c
test-power.o: test-power.c 
	gcc -c -pedantic -std=gnu99 -Wall -Werror test-power.c
