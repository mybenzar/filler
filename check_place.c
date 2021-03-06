/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:25:51 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 10:15:18 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	check_piece(t_board *b, int x, int y)
{
	if (x + b->piece->width <= b->width
		&& y + b->piece->height <= b->height)
		return (TRUE);
	return (FALSE);
}

int	start_piece(t_board *b, t_game *g, int x, int y)
{
	int		i;
	int		j;
	int		overlap;

	i = 0;
	overlap = 0;
	while (i < b->piece->height)
	{
		j = 0;
		while (b->piece->tab[i][j] != '\0')
		{
			if (b->piece->tab[i][j] == '*'
				&& b->tab[y + i][x + j] == g->player)
				overlap++;
			if (b->piece->tab[i][j] == '*'
				&& (b->tab[y + i][x + j] == g->ennemy
				|| b->tab[y + i][x + j] == g->ennemy - 32))
				return (0);
			j++;
		}
		i++;
	}
	return (overlap == 1 ? 1 : 0);
}

int	ft_left(t_piece *piece)
{
	int		y;
	int		x;

	y = 0;
	while (y < piece->height)
	{
		x = 0;
		while (piece->tab[y][x] != '\0')
		{
			if (piece->tab[y][x] == '*')
			{
				piece->tab[y - piece->min.y][x - piece->min.x] = '*';
				piece->tab[y][x] = '.';
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}
