/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:33:24 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 16:00:18 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_distance(int x, int y, int j, int i)
{
	return (ft_abs(x - j) + ft_abs(y - i));
}

void	get_min_distance(t_board *b, t_game *g)
{
	int		dist;
	int		y;
	int		x;

	y = 0;
	x = 0;
	dist = 0;
	while (y < b->piece->height)
	{
		x = 0;
		while (b->piece->tab[y][x] != '\0')
		{
			if (b->piece->tab[y][x] == '*')
				dist += get_distance(g->target.x, g->target.y,
					g->pos_tmp.x + x, g->pos_tmp.y + y);
			x++;
		}
		y++;
	}
	if (dist < g->distance || g->distance == -1)
		g->distance = dist;
}
