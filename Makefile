NAME        = pipex
BONUS       = pipexb
SRCDIR      = src
INCDIR      = includes

SRC         = cmds.c files.c main.c utils.c
OBJ         = $(addprefix $(SRCDIR)/, $(SRC:%.c=%.o))

BONUS_SRC   = bonus.c cmds.c files.c utils.c
BONUS_OBJ   = $(addprefix $(SRCDIR)/, $(BONUS_SRC:%.c=%.o))

CC          = cc -Wall -Werror -Wextra
INC         = -I $(INCDIR) -Ilibft
RM          = rm -rf

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

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(INC) -c $< -o $@

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
