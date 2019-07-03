/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/03 15:49:44 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	--> Find Closest Opponent's Piece : look for coordinates of closest 
**	oponent's piece in order to attack
*/

static int		get_distance(int x, int y, int j, int i)
{
	return (ft_abs(x - j) + ft_abs(y - i));
}

static void	get_min_distance(t_board *b, t_game *g)
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
				dist += get_distance(g->target.x, g->target.y, g->pos_tmp.x + x, g->pos_tmp.y + y);
			x++;
		}
		y++;
	}
	if (dist < g->distance || g->distance == -1)
		g->distance = dist;
}

static void find_target(t_board *b, t_game *g)
{
	int 	i;
	int 	j;

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
//	dprintf(2, "\n___________________>>>>>>>> in find target <<<<<<<<______________\n");
//	dprintf(2, "g->target.x = %d and g->target.y = %d\n", g->target.x, g->target.y);
}

static int check_piece(t_board *b, int x, int y)
{
	if (x + b->piece->width <= b->width
		&& y + b->piece->height <= b->height)
		return (1);
	return (0);
}

static int		start_piece(t_board *b, t_game *g, int x, int y)
{
	int		i;
	int		j;
	int		overlap;

	i = 0;
	overlap = 0;
//	dprintf(2, "\n------->>>>>>start piece<<<<<<<<--------\n for x = %d and y = %d\n", x, y);
	while (i < b->piece->height)
	{
		j = 0;
		while (b->piece->tab[i][j] != '\0')
		{
			if (b->piece->tab[i][j] == '*' &&
				b->tab[y + i][x + j] == g->player)
				overlap++;
			if (b->piece->tab[i][j] == '*' &&
				ft_toupper(b->tab[y + i][x + j]) == g->ennemy)
				return (0);
			j++;
		}
		i++;
	}
	if (overlap == 1)
		return (1);
	return (0);
}

static void		attack(t_board *b, t_game *g)
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
				dprintf(2, "==========>>>> check piece and start piece OK VV\n");
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				dprintf(2, "g->pos_tmp.x = %d and g->pos_tmp.y = %d\n", g->pos_tmp.x, g->pos_tmp.y);
				find_target(b, g);
				if (g->distance < dist || dist == -2)
				{
					dist = g->distance;
					dprintf(2, "-------->>> coordinates sent: \ng->pos_tmp.x = %d and g->pos_tmp.y = %d\n", g->pos_tmp.x, g->pos_tmp.y);
					g->place.x = g->pos_tmp.x;
					g->place.y = g->pos_tmp.y;
				}
			}
			j++;
		}
		i++;
	}
}

void strategy(t_board *b, t_game *g)
{
	if (b->piece->min.x != 0 || b->piece->min.y != 0)
		ft_left(b->piece);
	get_min(b->piece);
	attack(b, g);
}
