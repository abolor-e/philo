NAME 		= philo
CC 			= gcc
CFLAGS 		= -I. -g3 -g -fsanitize=thread -Wall -Wextra -Werror
THREAD_FLG	= -pthread

RED			= \033[1;31m
BLUE		= \033[1;34m
RESET		= \033[0m
GREEN		= \033[0;32m

SRC			= philo.c	\
			  philo_utils.c	\
			  data_init_parse.c \
			  main_operation.c \
			  


OBJ = $(SRC:.c=.o)

all: cute ${NAME}

${NAME}: $(OBJ)
		@$(CC) $(CFLAGS) ${THREAD_FLG} -lm $(SRC) -o $(NAME)
		@echo "$(GREEN)███████████████████████ Compilation DONE ██████████████████████$(RESET)"

%.o: %.c
	@${CC} ${CFLAGS} ${THREAD_FLG} -c $< -o $@

clean:
		@rm -rf $(OBJ)
		@echo "OBJECT FILES $(RED)DELETED$(RESET)"

fclean: clean
		@rm -rf $(NAME) $(OBJ)
		@echo "PHILO $(RED)DELETED$(RESET)"

re: fclean all

.PHONY: all clean fclean re

cute:
	@echo "$(GREEN)██████████╗     ███╗     ███╗   ███╗  ███╗            █████████═╗       "
	@echo "███║      ███╗  ███║     ███║   ███║  ███║         ███╔═╝     ███╚═╗    "
	@echo "███║       ███║ ███║     ███║   ███║  ███║        ███╔╝         ███╚╗   "
	@echo "███║       ███║ ███║     ███║   ███║  ███║       ███╔╝           ███║   "
	@echo "███║      ███╔╝ ████████████║   ███║  ███║       ███║            ███║   "
	@echo "██████████╔═╝   ███╔═════███║   ███║  ███║       ███╚╗           ███║   "
	@echo "███╔══════╝     ███║     ███║   ███║  ███║        ███╚╗         ███╔╝   "
	@echo "███║            ███║     ███║   ███║  ███║         ███╚╗      ███╔═╝    "
	@echo "███║            ███║     ███║   ███║  ████████████╗   █████████╔═╝      "
	@echo "╚══╝            ╚══╝     ╚══╝   ╚══╝  ╚═══════════╝    ╚═══════╝        $(RESET)"
	@echo "$(RED)██████████████████████████████████████████████████████████████████████╗ "
	@echo "╚═════════════════════════════════════════════════════════════════════╝ $(RESET)"
	@echo "                                              Made by : \033[1;91mabolor-e\033[m"