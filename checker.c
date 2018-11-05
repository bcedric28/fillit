/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 10:53:24 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/04 21:45:17 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	block_checker(char *tab, char letter)
{
	int i;
	int nb_block;

	nb_block = 0;
	i = 0;
	while (i < 20)
	{
		if (tab[i] == letter)
		{
			if ((i + 1) < 20 && tab[i + 1] == letter)
				nb_block++;
			if ((i - 1) >= 0 && tab[i - 1] == letter)
				nb_block++;
			if ((i + 5) < 20 && tab[i + 5] == letter)
				nb_block++;
			if ((i - 5) >= 0 && tab[i - 5] == letter)
				nb_block++;
		}
		i++;
	}
	if (nb_block == 6 || nb_block == 8)
		return (1);
	return (0);
}

static int	form_checker(char *tab, int adr)
{
	int		i;
	int		j;
	int		nb_block;
	char	letter;

	i = -1;
	nb_block = 0;
	while (tab[++i])
		if (tab[i] == '#')
		{
			nb_block++;
			tab[i] = (adr < (21 * 20)) ?
				(adr % 20) + 65 : ((adr % 20) + 65) + 20;
			letter = tab[i];
		}
	if (nb_block != 4)
		return (0);
	j = ft_strclen(tab, letter);
	return (block_checker(&(tab[j]), letter));
}

static int	fill_in_tab(char **tab, char *line)
{
	char			*tmp;
	static int		adr = 0;

	tmp = *tab;
	*tab = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
	if (*tab == NULL)
		return (-1);
	if (ft_strlen(*tab) > 21)
		adr += 21;
	return (form_checker(&(tab[0][adr]), adr));
}

static int	line_checker(char **tab, char *line, int ret)
{
	int i;

	i = 0;
	while (i < ret)
	{
		if (i < 20 && ft_strclen(&line[i], '\n') != 4)
			return (0);
		else if (i >= 20 && ft_strclen(&line[i], '\n') != 0)
			return (0);
		i += 5;
	}
	i = 1;
	while (i <= ret)
	{
		if ((i % 5) != 0 && (line[i - 1] != '.'
			&& line[i - 1] != '#') && i < 20)
			return (0);
		if (i >= 20 && ret >= 20 && line[i - 1] != '\n')
			return (0);
		i++;
	}
	return (fill_in_tab(tab, line));
}

int			read_line(int fd, char *line, char **tab)
{
	int			ret;
	static int	old_ret = 0;

	if (!(line = ft_strnew(21)))
		return (0);
	if (!(*tab = ft_strdup("")))
		return (0);
	while ((ret = read(fd, line, 21)) >= 20)
	{
		old_ret = ret;
		if (!(line_checker(tab, line, ret)))
			return (0);
		ft_strdel(&line);
		if (!(line = ft_strnew(21)))
			return (0);
	}
	ft_strdel(&line);
	if (ret == 0 && old_ret != 20)
		return (0);
	if ((ret < 20 && ret != 0) || ret == -1)
		return (0);
	return (1);
}
