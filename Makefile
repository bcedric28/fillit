# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 13:10:48 by vjovanov          #+#    #+#              #
#    Updated: 2018/11/03 14:12:17 by vjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

LIBFT_DIR = Libft/

SRCS = main.c checker.c solver.c solver_algo.c init_struct.c
OBJ = $(subst .c,.o,$(SRCS))

INC_DIR = .

WFLAGS = -Wall -Werror -Wextra

GCCRESET=\033[0m
GCCMAG=\033[1;35m

all: $(NAME)

$(NAME):
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@gcc $(WFLAGS) -c $(SRCS) -I $(INC_DIR)
	@echo "Compilation des fichiers sources $(GCCMAG)<fillit>$(GCCRESET)..."
	@gcc $(WFLAGS) $(OBJ) -I $(INC_DIR) -L $(LIBFT_DIR) -lft -o $(NAME)
	@echo "Creation du binaire $(GCCMAG)<fillit>$(GCCRESET)..."

clean:
	@rm -Rf $(OBJ)
	@echo "Suppression des fichiers objet $(GCCMAG)<fillit>$(GCCRESET)..."

fclean: clean
	@rm -Rf $(NAME)
	@echo "Suppression de l'executable $(GCCMAG)<fillit>$(GCCRESET)..."
	@make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
