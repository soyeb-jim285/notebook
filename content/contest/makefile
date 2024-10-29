# runs by make run file=filename, use *tab*
CC = g++
CFLAGS = -fsanitize=address -std=c++17 -Wall -Wextra -Wshadow -DONPC -O2
all:
%: %.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
run: $(file)
	./$(file)
clean:
	find . -type f -executable -delete
