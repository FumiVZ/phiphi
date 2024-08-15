NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
SRC = main.c \
	  init.c \
	  error.c \
	  free.c \
	  thread.c \
	  message.c \
	  utils.c \
	  monitoring.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEPS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): libft
	make -C $(LIBFT_DIR)	

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft