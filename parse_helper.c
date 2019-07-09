/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:36:41 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/09 15:54:33 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
/*
int		nb_adj_piece(char **tab, int x, int y)
{
	int count;

	if (x >= 0 && y >= 0 && tab[y] != NULL && tab[y][x] != '\0'
			&& tab[y][x] != 'N' && tab[y][x] == '*')
	{
		count = 1;
		tab[y][x] = 'N';
		count += nb_adj_piece(tab, x, y + 1);
		count += nb_adj_piece(tab, x + 1, y);
		count += nb_adj_piece(tab, x + 1, y + 1);
		count += nb_adj_piece(tab, x, y - 1);
		count += nb_adj_piece(tab, x - 1, y);
		count += nb_adj_piece(tab, x - 1, y - 1);
		count += nb_adj_piece(tab, x - 1, y + 1);
		count += nb_adj_piece(tab, x + 1, y - 1);
		return (count);
	}
	return (0);
}
*/
int		check_piece_elem(char c)
{
	if (c != 'X' && c != 'O' && c != 'x'
			&& c != 'o' && c != '.')
	{
		ft_printf("error in check piece\n");
		return (0);
	}
	return (1);
}

int		get_dim(t_piece *piece)
{
	char *line;
	char **split;
	char *tmp;

	line = NULL;
	split = NULL;
	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' ')))
		return (0);
	if (!(tmp = ft_strdup("Piece")))
		return (0);
	if (ft_strcmp(split[0], tmp) != 0
		|| !(piece->height = ft_atoi(split[1]))
		|| !(piece->width = ft_atoi(split[2])))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_free_tab(split, 3);
	if (piece->height == 0 || piece->width == 0)
		return (0);
	ft_strdel(&tmp);
	ft_strdel(&line);
	return (1);
}
int		get_min(t_piece *piece)
{
	int x;
	int y;

	y = 0;
	piece->min.x = -1;
	piece->min.y = -1;
	while (piece->tab[y] != NULL)
	{
		x = 0;
		while (piece->tab[y][x] != '\0')
		{
			if (piece->tab[y][x] == '*')
			{
				if (x < piece->min.x || piece->min.x == -1)
					piece->min.x = x;
				if (y < piece->min.y || piece->min.y == -1)
					piece->min.y = y;
			}
			x++;
		}
		y++;
	}
	//piece->parse = E_CHECK;
	return (2);
	//return (1);
}
/*
int		get_min(t_piece *piece)
{
	int p;

	p = 0;
	piece->min.x = -1;
	piece->min.y = -1;
	while (p < piece->size)
	{
		if (piece->tab[x] < piece->min.x || piece->min.x == -1)
			piece->min.x = piece->tab[x];
		if (piece->tab[y] < piece->min.y || piece->min.y == -1)
			piece->min.y = piece->tab[y];
		p++;
	}
	//piece->parse = E_CHECK;
	return (2);
	//return (1);
}
*/
