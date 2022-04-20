# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: max <max@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 11:06:26 by yalabidi          #+#    #+#              #
#    Updated: 2022/04/20 08:38:47 by max              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_RED = \033[0;38;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m

# nom de l'executable
NAME = woody_woodpacker

#sources path
SRC_PATH= srcs
SRC_ASM_PATH= ASM

#objects path
OBJ_PATH= objs
OBJ_ASM_PATH= objs

#includes
INC_PATH= includes/

HEADER=$(INC_PATH)/woody.h

NAME_SRC=main.c print_header.c print_pheaders.c  print_sheaders.c print_header_text.c\
		get_shname.c option.c createxe.c print_segment.c virus.c base64.c headers_info.c\
		check_integrity.c new_file.c \

NAME_SRC_ASM=ft_random.s encrypt.s


NAME_SRC_LEN	= $(shell echo -n $(NAME_SRC) $(NAME_SRC_ASM) | wc -w)
I				= 0


OBJ_NAME		= $(NAME_SRC:.c=.o)
OBJ_NAME_ASM	= $(NAME_SRC_ASM:.s=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) $(addprefix $(OBJ_ASM_PATH)/,$(OBJ_NAME_ASM))

CC			= gcc 
NASM		= nasm -f elf64 
CFLAGS		= -Wall -Werror -Wextra

#librairies
LIBFT			= libft
LIBFT_INC		= libft/includes/
LIBFT.A			= $(LIBFT)/libft.a


all: lib $(NAME)

$(NAME) : $(OBJS) $(LIBFT.A)
	@$(CC) $^ -o $@
	@echo "	\033[2K\r$(DARK_BLUE)$(NAME):\t\t$(GREEN)loaded\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(INC_PATH) -I $(LIBFT_INC) -c $< -o $@
	@$(eval I=$(shell echo $$(($(I)+1))))
	@printf "\033[2K\r${G}$(DARK_BLUE)>>\t\t\t\t$(I)/$(shell echo $(NAME_SRC_LEN)) ${N}$(BLUE)$<\033[36m \033[0m"


$(OBJ_ASM_PATH)/%.o: $(SRC_ASM_PATH)/%.s
	@mkdir $(OBJ_ASM_PATH) 2> /dev/null || true
	@$(NASM) $< -o $@
	@$(eval I=$(shell echo $$(($(I)+1))))
	@printf "\033[2K\r${G}$(DARK_BLUE)>>\t\t\t\t$(I)/$(shell echo $(NAME_SRC_LEN)) ${N}$(BLUE)$<\033[36m \033[0m"


$(OBJ_PATH)/%.o: $(SRC_PATH)/disas_elf_header/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(INC_PATH) -I $(LIBFT_INC) -c $< -o $@
	@$(eval I=$(shell echo $$(($(I)+1))))
	@printf "\033[2K\r${G}$(DARK_BLUE)>>\t\t\t\t$(I)/$(shell echo $(NAME_SRC_LEN)) ${N}$(BLUE)$<\033[36m \033[0m"

lib:
	@make --no-print-directory --silent -C $(LIBFT)

clean:
	@make clean --no-print-directory --silent -C $(LIBFT)
ifeq ("$(wildcard $(OBJ_PATH))", "")
else
	@rm -f $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[2K\r$(DARK_BLUE)$(NAME) objects:\t$(LIGHT_PINK)removing\033[36m \033[0m\n"
endif


fclean: clean
	@make fclean --no-print-directory --silent -C $(LIBFT)
	@rm -f woody
ifeq ("$(wildcard $(NAME))", "")
else
	@rm -f $(NAME)
	@printf "\033[2K\r$(DARK_BLUE)$(NAME):\t\t$(PINK)removing\033[36m \033[0m\n"
endif

re: fclean all

.PHONY: all re clean fclean lib silent
