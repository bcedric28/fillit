/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:21:12 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/04 16:53:48 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "Libft/includes/libft.h"

typedef struct	s_block
{
	int			x;
	int			y;
	int			x_offset;
	int			x_relative;
	int			y_relative;
	int			x_in_sq;
	int			y_in_sq;
	char		letter;
}				t_block;

int				read_line(int fd, char *line, char **tab);
int				solver(char **tab);
int				create_struct(char **tab, t_block *t_tab, int n);
int				algo(char **sq_tab, t_block *t_tab, int n, int size_array);
int				free_tab(char **sq_tab);
void   				display_tetra(char **sq_tab);

#endif
