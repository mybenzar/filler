/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/02 10:49:01 by mybenzar         ###   ########.fr       */
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

static int		scan_board(t_board *b, t_game *g)
{
	int i;
	int j;

	while (i > b->height)
	{
		j = 0;
		while (j -> b->width)
		{
			if ((b->tab[i][j] == g->player || b->tab[i][j] == '.'))
			{
				g->place.x = j - b->piece->min.x;
				g->place.y = i - b->piece->min.y;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	get_distance(t_board *b, t_game *g)
{
	int		dist;
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < b->piece->height)
	{
		x = 0;
		while (b->piece[y][x] != '\0')
		{
			if (b->piece[y][x] == '*')
				dist += get_distance(g->target.x, g->target.y, g->place.x + x, g->place.y + y);
			x++;
		}
		y++;
	}
	if (dist < game->distance || game->distance == -1)
		game->distance = dist;
}

static void find_target(t_board *b, t_game *g)
{
	int 	i;
	int 	j;

	i = 0;
	game->distance = -1;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (ft_toupper(b->tab[i][j]) == ft_toupper(g->ennemy))
			{
				g->target.x = j;
				g->target.y = i;
				get_distance(b, g);
			}
			j++;
		}
		i++;
	}
}

static int	attack(t_board *b, t_game *g)
{
	scan_board(b, g);
	find_target(b, g);
	if (g->distance < dist || dist == -2)
	{
		dist = g->distance;
		g->x = 
	}

}

static int	surrender(t_board *b, t_game *g)
{
	g->place.x = 0;
	g->place.y = 0;
	return (1);
}

void strategy(t_board *b, t_game *g)
{
	if (attack(b, g) == 0)
		surrender(b, g);
}

