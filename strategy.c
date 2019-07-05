/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/05 12:23:00 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	find_target(t_board *b, t_game *g)
{
	dprintf(2, "--------------->>>>>>>>>>RUSH LAUNCEHD<<<<<<<<<<---------\n");
	int	i;
	int	j;

	i = 0;
	g->distance = -1;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (ft_toupper(b->tab[i][j]) == ft_toupper(g->ennemy))
			{
				g->target.x = j;
				g->target.y = i;
				get_min_distance(b, g);
			}
			j++;
		}
		i++;
	}
}
/*
static void	top_right(t_board *b, t_game *g)
{
	dprintf(2, "--------------->>>>>>>>>>TOP RIGHT LAUNCHED<<<<<<<<<<---------\n");
	g->target.x = b->width;
	g->target.y = 0;
	get_min_distance(b, g);
}

static void	bottom_left(t_board *b, t_game *g)
{
	dprintf(2, "--------------->>>>>>>>>>BOTTOMLEFT LAUNCHED<<<<<<<<<<---------\n");
	g->target.x = 0;
	g->target.y = b->height;
	get_min_distance(b, g);
}

static void find_target(t_board *b, t_game *g)
{
	static t_aim	aim[] = {top_right, bottom_left, rush};
	
	aim[g->aim](b, g);
}
*/
static void	possible_place(t_game *g, int *dist)
{
	*dist = g->distance;
	g->place.x = g->pos_tmp.x;
	g->place.y = g->pos_tmp.y;
	dprintf(2, "possible places : g->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
}

static void	attack(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;

	i = 0;
	dist = -2;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				find_target(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j++;
		}
		i++;
	}
}

void		strategy(t_board *b, t_game *g)
{
	if (b->piece->min.x != 0 || b->piece->min.y != 0)
		ft_left(b->piece);
	get_min(b->piece);
	attack(b, g);
/*	dprintf(2, "\nin possible place, g->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
	if (g->place.x == b->width && g->place.y == 0)
	{
		g->aim = E_BOTTOM_LEFT;
		attack(b, g);
	}
	if (g->place.x == 0 && g->place.y == b->height)
	{
		g->aim = E_RUSH;
		attack(b, g);
	}
	*/
}
