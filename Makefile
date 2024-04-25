NAME = minishell

MINISHELL = minishell.a

FILES = src/minishell.c\
src/builtins/builtins.c\
src/builtins/builtins2.c\
src/builtins/builtins3.c\
src/builtins/builtins_utils/builtins_utils.c\
src/builtins/builtins_utils/cd_utils.c\
src/builtins/builtins_utils/export_utils.c\
src/builtins/env_utils/get_env.c\
src/exec_cmd/exec.c\
src/exec_cmd/exec_utils.c\
src/exec_cmd/exec_utils2.c\
src/minishell_utils/expand.c\
src/minishell_utils/init_struct.c\
src/minishell_utils/parser/heredoc.c\
src/minishell_utils/parser/parser.c\
src/minishell_utils/parser/parser_utils.c\
src/minishell_utils/parser/parser_utils2.c\
src/minishell_utils/prompt.c\
src/minishell_utils/signals.c\
src/minishell_utils/split.c\
src/minishell_utils/split_token.c\
src/minishell_utils/token_error.c\
src/free/free.c\
src/free/free2.c\

OBJECTS = $(FILES:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

LIBFT = ./Libft/libft.a

INC_SYS = -I ./include -I /Users/etornay-/.brew/opt/readline/include

LIB_SYS = -L /Users/etornay-/.brew/opt/readline/lib -lreadline

$(NAME):			$(LIBFT) $(OBJECTS)
						@ ar rcs $(MINISHELL) $(OBJECTS)
						@ gcc $(INC_SYS) $(LIB_SYS) $(FLAGS) $(LIBFT) $(MINISHELL) -o $(NAME)

$(OBJECTS):			src/%.o : src/%.c
						@ gcc $(INC_SYS) $(FLAGS) -c $< -o $@

$(LIBFT):
					@ make -s -C ./Libft

all:				$(NAME)

clean:
					@ rm -f $(OBJECTS)
					@ make clean -s -C ./Libft

fclean:
					@ rm -f $(NAME) $(OBJECTS) $(MINISHELL) $(LIBFT)
					@ make fclean -s -C ./Libft

re:					fclean all

.PHONY: all re clean fclean
