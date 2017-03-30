# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrea <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 16:19:36 by fgrea             #+#    #+#              #
#    Updated: 2017/03/30 14:49:29 by fgrea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

ifneq ($(shell make -q -C libft; echo $$?), 0)
	.PHONY: libft/libft.a
endif

NAME = fdf

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -g -Wall -Wextra -Werror
# FRAM = -lmlx -framework OpenGL -framework AppKit
FRAM = -framework OpenGL -framework AppKit minilibx_macos/libmlx.a

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = fdf.h
SRC_NAME = main.c fdf_errors.c fdf_parcing.c fdf_pixel_gestion.c \
		   fdf_image_gestion.c fdf_pixel_color_gestion.c fdf_put_pxl_to_img.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
			@make -C $(LFT_PATH)
			@$(CC) -o $(NAME) $(FRAM) -L $(LFT_PATH) -lft $^ -o $@
			@echo "$(OKC)FDF:\tCOMPILED$(NOC)"
			@echo "***************************************"
			@echo "----------------__---------------------"
			@echo "--------------<(o )___.----------------"
			@echo "---------------( ._> /-----------------"
			@echo "----------------\`---'-------C.WC------"
			@echo "***************************************"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			@mkdir -p $(OBJ_PATH) 2> /dev/null || true
			@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
			@make -C $(LFT_PATH) clean
			@rm -rf $(OBJ_PATH)
			@echo "$(WAC)FDF:\tCLEANING OBJS$(NOC)"
			@echo "***************************************"


fclean: clean
			@make -C $(LFT_PATH) fclean
			@rm -f $(NAME)
			@echo "$(WAC)FDF:\tCOMPILATION TRACES REMOVED$(NOC)"
			@echo "***************************************"


re: fclean
			@$(MAKE) all
