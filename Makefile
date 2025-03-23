NAME = flag_parser.a

SRCS = flag_parser.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I inc

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
