/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 10:17:50 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	find_target(t_board *b, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	g->distance = -1;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->ennemy || b->tab[i][j] == g->ennemy - 32)
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

void		possible_place(t_game *g, int *dist)
{
	*dist = g->distance;
	g->place.x = g->pos_tmp.x;
	g->place.y = g->pos_tmp.y;
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
	b->area = b->height * b->width;
	if (b->piece->min.x != 0 || b->piece->min.y != 0)
	{
		ft_left(b->piece);
		trim(b->piece);
	}
	if (b->height > 30 && b->width > 30)
	{
		if (count_char(b) < b->area / 8)
			bottom_corner(b, g, b->width, b->height);
		else if (count_char(b) < b->area / 6)
			attack(b, g);
		else
		{
			if (count_char(b) < b->area / 4)
				bottom_corner(b, g, 0, b->height);
			else if (count_char(b) < b->area / 2)
				upper_corner(b, g, b->width, 0);
			else
				fill(b, g);
		}
	}
	else
		attack(b, g);
}
