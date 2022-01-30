# Name of the program built
NAME				:=		so_long

# Name directory
PATH_SRC			:=		src
PATH_INC			:=		inc
PATH_BUILD			:=		build
PATH_LIBFT			:=		libft
PATH_MLX			:=		minilibx-linux

# List of sources
SRCS				:=		$(shell find $(PATH_SRC) -name *.c)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
INC_DIRS			:=		$(shell find $(PATH_INC) -type d)

# Compiler
CC					:=		gcc

# Flags - compilation
# FLAG_WARNING		:=		-Wall -Wextra -Werror
# FLAG_MAKEFILE		:=		-MMD -MP
FLAG_DEBUG			:=		-g
FLAG_OPTIMIZATION	:=		-O3
FLAGS_COMP			:=		$(FLAG_WARNING) -Ilibft -Iinc $(FLAG_MAKEFILE) $(FLAG_DEBUG) $(FLAG_OPTIMIZATION)

# Flags - memory leak check
FLAG_MEM_LEAK		:=		-fsanitize=address

# Flags - linking
FLAG_LIBFT			:=		-L$(PATH_LIBFT) -lft
FLAG_MLX			:=		-L$(PATH_MLX) -lmlx -lm -lXext -lX11

# Others commands
RM					:=		rm -rf

# Color Code and template code
_YELLOW				:=		\e[38;5;184m
_GREEN				:=		\e[38;5;46m
_RESET				:=		\e[0m
_INFO				:=		[$(_YELLOW)INFO$(_RESET)]
_SUCCESS			:=		[$(_GREEN)SUCCESS$(_RESET)]

# General functions
all:						init $(NAME)
							@ printf "$(_SUCCESS) Compilation done\n"

init:
							@ printf "$(_INFO) Initialize $(NAME)\n"
							@ make -C $(PATH_LIBFT)

$(NAME):			$(OBJS)
							$(CC) $(FLAGS_COMP) -o $@ $(OBJS) $(FLAG_LIBFT) $(FLAG_MLX)
$(PATH_BUILD)/%.o:	%.c
							@ mkdir -p $(dir $@)
							@ $(CC) $(FLAGS_COMP) -c $< -o $@

bonus:						all

clean:
							@ $(RM) $(PATH_BUILD)
							@ printf "$(_INFO) Deleted files and directory\n"
#@ make -C $(PATH_LIBFT) clean

fclean:						clean
							@ $(RM) $(NAME)
#@ make -C $(PATH_LIBFT) fclean

re:							fclean all

# Debugging functions

debug:						FLAGS_COMP += $(FLAG_MEM_LEAK)
debug:						re

# Format functions

.PHONY:						all clean fclean re
