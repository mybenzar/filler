/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/05 12:23:53 by mybenzar         ###   ########.fr       */
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

static void	possible_place(t_game *g, int *dist)
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
	if (b->piece->min.x != 0 || b->piece->min.y != 0)
		ft_left(b->piece);
	get_min(b->piece);
	attack(b, g);
}
