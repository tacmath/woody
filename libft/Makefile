# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: max <max@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 11:06:26 by yalabidi          #+#    #+#              #
#    Updated: 2022/04/19 06:57:57 by max              ###   ########.fr        #
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
NAME = libft.a

#sources path
SRC_PATH= srcs

#objects path
OBJ_PATH= objs

#includes
INC_PATH= includes

NAME=libft.a

HEADER=$(INC_PATH)/libft.h

NAME_SRC=ft_memcpy.c ft_strncat.c ft_memmove.c ft_memset.c ft_strcpy.c\
			ft_strncpy.c ft_bzero.c ft_memccpy.c ft_strdup.c ft_memchr.c ft_strlcat.c\
			ft_memcmp.c ft_strcat.c ft_strlen.c ft_strchr.c ft_strrchr.c ft_strstr.c\
			ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isalnum.c\
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_toupper.c ft_tolower.c\
			ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c\
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memalloc.c ft_memdel.c\
			ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c\
			ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c\
			ft_strsplit.c ft_itoa.c ft_power.c ft_putmem.c ft_utoa_base.c ft_strnjoin.c\
			ft_putnbrbase.c ft_swapbit.c ft_strjoinfree.c ft_hexdump.c ft_putnstr.c ft_putnchar.c\
			ft_hexdump_color.c ft_linear_hexdump.c ft_advanced_hexdump_color.c \

NAME_SRC_LEN	= $(shell echo -n $(NAME_SRC) | wc -w)
I				= 0


OBJ_NAME	= $(NAME_SRC:.c=.o)

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
	@ranlib $(NAME)
	@echo "	\033[2K\r$(DARK_BLUE)libft:\t\t\t\t$(GREEN)loaded\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(INC_PATH) $(CFLAGS) -c $< -o $@
	@ar rc $(NAME) $@
	@$(eval I=$(shell echo $$(($(I)+1))))
	@printf "\033[2K\r${G}$(DARK_BLUE)>>\t\t\t\t$(I)/$(shell echo $(NAME_SRC_LEN)) ${N}$(BLUE)$<\033[36m \033[0m"

clean :
ifeq ("$(wildcard $(OBJ_PATH))", "")
else
	@rm -f $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[2K\r$(DARK_BLUE)$(NAME) objects:\t\t$(LIGHT_PINK)removing\033[36m \033[0m\n"
endif

fclean : clean
ifeq ("$(wildcard $(NAME))", "")
else
	@rm -f $(NAME)
	@printf "\033[2K\r$(DARK_BLUE)$(NAME):\t\t\t$(PINK)removing\033[36m \033[0m\n"
endif


re : fclean all


.PHONY: all re clean fclean