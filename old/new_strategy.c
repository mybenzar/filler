/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_strategy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:38:53 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/27 15:56:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		get_distance(int x, int y, int j, int i)
{
	return (ft_abs(x - j) + ft_abs(y - i));
}

static int		compute_dist(t_game *g)
{
	int	dist;
	int i;
	int j;

	i = 0;
	dist = g->board->height + g->board->width;
	while (g->board->tab[i] != NULL)
	{
		j = 0;
		while (g->board->tab[i][j] != '\0')
		{
			if (g->board->tab[i][j] == E_PLAYER)
			{
				if (dist > get_distance(g->target.x, g->target.y, j, i))
				{
					dist = get_distance(g->target.x, g->target.y, j, i);
					g->place.x = j;
					g->place.y = i;
				}
			}
			j++;
		}
		i++;
	}
	return (dist);
}

static void	get_closest_op(t_game *g)
{
	int 	i;
	int 	j;
	int		dist;
	t_posi	place;
	int		tmp;

	i = 0;
	dist = b->height + b->width;
	place.x = 0;
	place.y = 0;
	while (g->board->tab[i] != NULL)
	{
		j = 0;
		while (g->board->tab[i][j] != '\0')
		{
			if (g->board->tab[i][j] == E_ENNEMY)
			{
				g->target.x = j;
				g->target.y = i;
				if ((tmp = compute_dist(b, g)) && dist > tmp && dist != 0) 
				{
					dist = tmp;
					place = g->place;
				}
			}
			j++;
		}
		i++;
	}
	g->place = place;
}

static int scan(t_game *g)
{
	int i;
	int j;

	i = 0;
	while (
}
