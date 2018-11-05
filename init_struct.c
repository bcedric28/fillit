/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:42:52 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/04 16:55:10 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		set_pos_relative(t_block *t_tab, int n)
{
	int i;
	int j;

	i = 0;
	while (i < (n * 4))
	{
		j = i;
		while (j < (i + 4))
		{
			t_tab[j].x_relative = t_tab[j].x - t_tab[i].x;
			t_tab[j].y_relative = t_tab[j].y - t_tab[i].y;
			j++;
		}
		i += 4;
	}
}

static void		set_offset(t_block *t_tab, int n)
{
	int i;
	int j;
	int offset;

	i = 0;
	while (i < n * 4)
	{
		j = 1;
		offset = 0;
		while (j < 4)
		{
			if ((t_tab[i].x - t_tab[i + j].x) > offset)
				offset = t_tab[i].x - t_tab[i + j].x;
			j++;
		}
		t_tab[i].x_offset = offset;
		i += 4;
	}
	set_pos_relative(t_tab, n);
}

int				create_struct(char **tab, t_block *t_tab, int n)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] != '.')
			{
				t_tab[k].x = j % 4;
				t_tab[k].y = i % 4;
				t_tab[k].letter = tab[i][j];
				t_tab[k].x_in_sq = 0;
				t_tab[k].y_in_sq = 0;
				k++;
			}
		}
	}
	set_offset(t_tab, n);
	return (1);
}
