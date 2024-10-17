# Nazwa pliku wykonywalnego
NAME = philo

# Kompilator
CC = gcc

# Flagi kompilatora
CFLAGS = -Wall -Wextra -Werror -pthread

# Pliki źródłowe
SRCS = main.c data_init.c dinner.c error_handling.c parsing_input.c mutex_handle.c set_get.c threads_handle.c utils.c write.c monitor.c

# Pliki nagłówkowe
HEADERS = philo.h

# Pliki obiektowe (z plików .c tworzymy pliki .o)
OBJS = $(SRCS:.c=.o)

# Reguła domyślna, która uruchomi się po wpisaniu 'make'
all: $(NAME)

# Tworzenie pliku wykonywalnego z plików obiektowych
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Kompilacja plików .c do .o, z uwzględnieniem nagłówków jako zależności
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Reguła czyszczenia plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(OBJS)

# Reguła czyszczenia całego projektu (pliki obiektowe i plik wykonywalny)
fclean: clean
	rm -f $(NAME)

# Reguła do przebudowania całego projektu
re: fclean all

# Ignorujemy plik Makefile i inne istotne pliki w regułach 'make'
.PHONY: all clean fclean re
