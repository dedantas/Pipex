NAME = pipex
BONUS = pipexb

SRC = cmds.c files.c main.c utils.c
OBJ = $(SRC:%.c=%.o)

BONUS_SRC = bonus.c cmds.c files.c utils.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

CC = cc -Wall -Werror -Wextra
INC = -I ./
RM = rm -rf

all: $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $^ -Llibft -lft -o $(NAME)
	@echo "Pipex compiled"

$(BONUS): $(BONUS_OBJ)
	@make -C libft
	$(CC) $^ -Llibft -lft -o $(BONUS)
	@echo "Bonus compiled"

%.o: %.c
	$(CC) $(INC) -Ilibft -c $< -o $@

bonus: $(BONUS)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "Object files cleaned"

fclean: clean
	$(RM) $(NAME) $(BONUS)
	@make fclean -C libft/
	@echo "Executables cleaned"

re: fclean all

.PHONY: all clean fclean re bonus libft
