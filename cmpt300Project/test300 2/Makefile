CC := gcc
CFLAGS := -Wall -Werror -std=c99 -D _GNU_SOURCE -static

all: test_array test_process

test_array_stats: test_array.o
	$(CC) $(CFLAGS) -o $@ $^

test_process_ancestors: test_process.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $^

transfer: test_array test_process
	scp -P 2222 test_array root@localhost:~/
	scp -P 2222 test_process root@localhost:~/

clean:
	rm -rf *.o
	rm -rf test_array test_process