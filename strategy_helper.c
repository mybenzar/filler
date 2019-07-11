/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:32:37 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 18:25:20 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	bottom_corner(t_board *b, t_game *g, int c_x, int c_y)
{
	int i;
	int j;
	int dist;

	i = b->height - 1;
	dist = -2;
	while (i >= 0)
	{
		j = b->width - 1;
		while (j >= 0)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				g->target.x = c_x - 1;
				g->target.y = c_y - 1;
				get_min_distance(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j--;
		}
		i--;
	}
}

void	upper_corner(t_board *b, t_game *g, int c_x, int c_y)
{
	int i;
	int j;
	int dist;

	i = 0;
	dist = -2;
	while (i < b->height)
	{
		j = b->width / 2;
		while (j >= 0)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				g->target.x = c_x - 1;
				g->target.y = c_y;
				get_min_distance(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j--;
		}
		i++;
	}
}

void	fill(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;

	j = b->width - 1;
	dist = -2;
	while (j >= 0)
	{
		i = 0;
		while (i < b->height)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->place.x = j - b->piece->min.x;
				g->place.y = i - b->piece->min.y;
				return ;
			}
			i++;
		}
		j--;
	}
}

int		count_char(t_board *b)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (b->tab[i][j] != '.')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
