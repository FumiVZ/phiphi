NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP
CC = cc
SRC = main.c \
	  init.c \
	  error.c \
	  free.c \
	  thread.c \
	  message.c \
	  utils.c \
	  monitoring.c \
	  lib_utils.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEPS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re