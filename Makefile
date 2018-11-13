CFLAGS=-Wall -g

LDFLAGS=-lm

Project_1_bkhuu_207:
	gcc -o Project_1_bkhuu_207 Project_1_bkhuu_207.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f Project_1_bkhuu_207
