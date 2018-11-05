/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:05:03 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/03 16:04:51 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	display_tetra(char **sq_tab)
{
	int i;

	i = 0;
	while (sq_tab[i])
	{
		ft_putendl(sq_tab[i]);
		i++;
	}
}

static int	check_put_tetra(char **sq_tab, t_block *t_tab, int n, int s_array)
{
	int			i;
	int			j;
	static int	tetri_ok = 0;

	i = 0;
	while (!(tetri_ok) && i < (n * 4))
	{
		j = i;
		while (j < (i + 4))
		{
			if (sq_tab[t_tab[j].y_relative] == 0)
				return (free_tab(sq_tab));
			if (sq_tab[t_tab[j].y_relative]
				[t_tab[i].x_offset + t_tab[j].x_relative] == '\0')
				return (free_tab(sq_tab));
			j++;
		}
		i += 4;
	}
	tetri_ok = 1;
	return (algo(sq_tab, t_tab, n, s_array));
}

static int	create_sq_tab(t_block *t_tab, int n, int size_array)
{
	char	**sq_tab;
	int		i;
	int		j;

	i = -1;
	if (!(sq_tab = (char**)malloc(sizeof(char*) * (size_array + 1))))
		return (0);
	sq_tab[size_array] = NULL;
	while (++i < size_array)
	{
		j = -1;
		if (!(sq_tab[i] = (char*)malloc(sizeof(char) * (size_array + 1))))
			return (free_tab(sq_tab));
		sq_tab[i][size_array] = '\0';
		while (++j < size_array)
			sq_tab[i][j] = '.';
	}
	if (!(check_put_tetra(sq_tab, t_tab, n, size_array)))
		create_sq_tab(t_tab, n, size_array + 1);
	else
		display_tetra(sq_tab);
	return (1);
}

int			solver(char **tab)
{
	int		i;
	int		nb_form;
	int		size_array;
	t_block	*t_tab;

	i = 0;
	while (tab[i])
		i++;
	nb_form = i / 4;
	if (nb_form > 26)
		return (0);
	size_array = ft_sqrt_next(i);
	if (!(t_tab = (t_block*)malloc(sizeof(t_block) * (nb_form * 4))))
		return (0);
	if (!(create_struct(tab, t_tab, nb_form)))
		return (0);
	if (!(create_sq_tab(t_tab, nb_form, size_array)))
		return (0);
	return (1);
}
