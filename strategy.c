/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/24 20:08:23 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	--> Find Closest Opponent's Piece : look for coordinates of closest 
**	oponent's piece in order to attack
*/

static int		get_distance(t_game *g, int x, int y)
{
	return (ft_abs(g->ennemy_pos.x - x) + ft_abs(g->ennemy_pos.y - y));
}

static int		compute_dist(t_board *b, t_game *g)
{
	int	dist;
	int i;
	int j;

	i = 0;
	dist = b->height + b->width;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->player)
			{
				if (dist > get_distance(g, j, i))
				{
					dist = get_distance(g, j, i);
					g->target.x = j;
					g->target.y = i;
				}
			}
			j++;
		}
		i++;
	}
	return (dist);
}

static void	get_closest_op(t_board *b, t_game *g)
{
	int 	i;
	int 	j;
	int		dist;
	t_posi	target;
	int		tmp;

	i = 0;
	dist = b->height + b->width;
	target.x = 0;
	target.y = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->ennemy || b->tab[i][j] == ft_tolower(g->ennemy))
			{
				g->ennemy_pos.x = j;
				g->ennemy_pos.y = i;
				if ((tmp = compute_dist(b, g)) && dist > tmp) 
				{
					dist = tmp;
					target = g->target;
				}
			}
			j++;
		}
		i++;
	}
	g->target = target;
}

/*
**	--> Place Check : checks if there is enough space to place the piece
**	starting from the target coordinates
*/

static void		mark(t_board *b, t_game *g)
{
	b->tab[g->target.y][g->target.x] = '/';
}
static int		place_check(t_board *b, t_game *g)
{
	int x;
	int y;
	int i;
	t_posi tmp;

	tmp.x = b->piece->pos[0].x;
	tmp.y = b->piece->pos[0].y;
	if (ft_left(b->piece) == 0)
		return (0);
	i = 1;
	if (b->piece->width > b->width || b->piece->height > b->height)
		return (0);
	while (i < b->piece->size)
	{
		x = b->piece->pos[i].x + g->target.x;
		y = b->piece->pos[i].y + g->target.y;
		i++;
		if (b->tab[y][x] != '.')
		{
			if (b->tab[y][x] != '\0' && b->tab[y][x] != '/' && b->tab[y])
			{
				mark(b, g);
				get_closest_op(b, g);
			}
			if (b->tab[y][x] == '\0' && b->tab[y] == NULL)
				return (0);
			i = 1;
		}
	}
	g->target.x -= tmp.x;
	g->target.y -= tmp.y;
	return (1);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

static t_posi	attack(t_board *board, t_game *game)
{
	get_closest_op(board, game);
	if (place_check(board, game) != 0)
		game->play = E_MIRROR;
/*	else
	{
		
		game->play = E_SETTLE;
	}*/
	return (game->target);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

static t_posi mirror(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;
	int tmp;
	t_posi target;

	i = 0;
	dist = 0;
	target.x = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == ft_tolower(g->ennemy))
			{
				g->ennemy_pos.x = j;
				g->ennemy_pos.y = i;
				if ((tmp = compute_dist(b, g)) && dist > tmp) 
				{
					dist = tmp;
					target = g->target;
				}
			}
			j++;
		}
		i++;
	}
	g->play = E_ATTACK;
	return (target);
}

/*
**	--> Settle : Covers most of the field in diagonal in order to block oponent
**	when reaches the corner, starts attacking again
*/

static t_posi	settle(t_board *b, t_game *g)
{
	int x;
	int y;

	y = 0;
	x = y;
	b->height = b->height;
	return (g->target);
}

/*
** --> Strategy : if oponent is close then attack, if they're far, defend
*/

void strategy(t_board *b, t_game *g)
{
	static t_strategy	trigger_strategy[] = {attack, mirror, settle};

	get_closest_op(b, g);
	if (compute_dist(b, g) < ft_min(b->width / 4, b->height / 4))
		g->play = E_ATTACK;
	else
		g->play = E_SETTLE;
	trigger_strategy[g->play](b, g);
}

