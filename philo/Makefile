NAME 		= philo
CC 			= gcc
CFLAGS 		= -I. -g3 -g -fsanitize=address -Wall -Wextra -Werror

RED			= \033[1;31m
BLUE		= \033[1;34m
RESET		= \033[0m

SRC			= philo.c

OBJ = $(SRC:.c=.o)

all: cute ${NAME}

${NAME}: $(OBJ)
		@echo "$(BLUE)███████████████████████ Making Philo ███████████████████████$(RESET)"
		@$(CC) $(CFLAGS) -lm $(SRC) -o $(NAME)
		@echo "$(BLUE)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
		@rm -rf $(OBJ)
		@echo "$(RED)OBJECT FILES DELETED$(RESET)"

fclean: clean
		@rm -rf $(NAME) $(OBJ)
		@echo "$(RED)PHILO DELETED$(RESET)"

re: fclean all

.PHONY: all clean fclean re

cute:
	@echo "███╗   ███╗██╗███╗   ██╗██╗   ██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║   ██║  ██║██╔════╝██║     ██║     " 
	@echo "██╔████╔██║██║██╔██╗ ██║██║   ███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║   ██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║   ██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "         Made by : \033[1;91mabolor-e\033[m"
