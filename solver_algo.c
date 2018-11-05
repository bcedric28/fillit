/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:43:11 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/04 16:43:21 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	rm_tetra(char **sq_tab, t_block *t_tab)
{
	int i;
	int j;

	i = 0;
	while (sq_tab[i])
	{
		j = 0;
		while (sq_tab[i][j])
		{
			if (sq_tab[i][j] == t_tab->letter)
				sq_tab[i][j] = '.';
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_outside(char **sq_tab, t_block *t_tab, int pos, int s_array)
{
	int i;
	int j;
	int k;

	i = pos / s_array;
	j = pos % s_array;
	k = 0;
	while (k < 4)
	{
		if (sq_tab[i + t_tab[k].y_relative] == 0)
			return (-1);
		if (sq_tab[i + t_tab[k].y_relative]
			[j + t_tab[0].x_offset + t_tab[k].x_relative] == '\0')
			return (-2);
		k++;
	}
	return (1);
}

static int	write_tetra(char **sq_tab, t_block *t_tab, int pos, int size_array)
{
	int i;
	int j;
	int k;

	i = pos / size_array;
	j = pos % size_array;
	k = 0;
	while (k < 4)
	{
		sq_tab[i + t_tab[k].y_relative]
			[j + t_tab[0].x_offset + t_tab[k].x_relative] = t_tab[k].letter;
		t_tab[k].y_in_sq = i;
		t_tab[k].x_in_sq = j;
		k++;
	}
	system("clear");
	display_tetra(sq_tab);
	return (1);
}

static int	put_tetra(char **sq_tab, t_block *t_tab, int pos, int s_array)
{
	int i;
	int j;
	int k;

	i = pos / s_array;
	j = pos % s_array;
	if ((k = check_outside(sq_tab, t_tab, (i * s_array) + j, s_array)) == 1)
	{
		k = -1;
		while (++k < 4)
			if (sq_tab[i + t_tab[k].y_relative]
				[j + t_tab[0].x_offset + t_tab[k].x_relative] != '.')
				break ;
	}
	if (k == 4)
		return (write_tetra(sq_tab, t_tab, pos, s_array));
	if (k == -1 && t_tab->letter == 'A')
		return (-1);
	if (k == -1)
		return (0);
	if (sq_tab[i + 1] == 0 && sq_tab[i][j + 1] == '\0')
		return (0);
	if (k == -2)
		return (put_tetra(sq_tab, t_tab, ((i + 1) * s_array) + 0, s_array));
	return (put_tetra(sq_tab, t_tab, (i * s_array) + (j + 1), s_array));
}

int			algo(char **sq_tab, t_block *t_tab, int n, int size_array)
{
	int k;
	int i;
	int pos;
	int l;

	k = 0;
	i = 0;
	pos = 0;
	while (i < n)
		if ((l = put_tetra(sq_tab, &t_tab[k], pos, size_array)) == 0)
		{
			rm_tetra(sq_tab, &t_tab[k - 4]);
			i--;
			k -= 4;
			pos = (t_tab[k].y_in_sq * size_array) + (t_tab[k].x_in_sq + 1);
		}
		else if (l == -1)
			return (free_tab(sq_tab));
		else
		{
			pos = 0;
			i++;
			k += 4;
		}
	return (1);
}
