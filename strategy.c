/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 12:21:20 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	--> Find Closest Opponent's Piece : look for coordinates of closest 
**	oponent's piece in order to attack
*/

int		compute_dist(t_board *b, t_game *g)
{
	int	dist;
	int	x;
	int y;
	int i;

	i = 0;
	dist = b->height + b->width;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->player)
			{
				x = j;
				y = i;
				if (dist > ft_abs(g->ennemy_pos.x - x) + ft_abs(g->ennemy_pos.y - y))
				{
					dist = ft_abs(g->ennemy_pos.x - x) + ft_abs(g->ennemy_pos.y - y);
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

void	get_closest_op(t_board *b, t_game *g)
{
	int 	i;
	int 	j;
	int		dist;
	t_pos	target;

	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->ennemy)
			{
				g->ennemy_pos.x = j;
				g->ennemy_pos.y = i;
				if ((tmp = compute_dist(b, game)) && dist > tmp) 
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

int		place_check(t_board *b, t_game *g)
{
	int x;
	int y;
	int i;

	i = 1;
	if (p->width > b->width || p->height > b->height)
		return (0);
	while (i < p.size)
	{
		x = g->p.pos[i].x + g->target.x;
		y = g->p.pos[i].y + g->target.y;
		if (b->tab[y][x] != '.')
			return (0);
		i++;
	}
	return (1);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

t_pos	attack(t_board *board, t_game *game)
{
	get_closest_op(board, game);
	if (place_check(board, game->piece) != 0)
		game->play = E_MIRROR;
	return (g->target);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

t_pos mirror(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;
	int tmp;

	while (b->tab[i] != NULL)
	{
		j = 0;
		while (g->tab[i][j] != '\0')
		{
			if (g->tab[i][j] == ft_tolower(g->ennemy))
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
**	--> Defense : Covers most of the field in diagonal in order to block oponent
**	when reaches the corner, starts attacking again
*/
/*
t_pos	defense(t_board *b, t_game *g)
{
	
}
*/

/*
** --> Strategy : if oponent is close then attack, if they're far, defend
*/

t_pos strategy(t_board *b, t_game *g)
{
	static t_strategy	trigger_strategy[] = {attack, mirror, defense};

	find_closest_op(b, g);
	if (compute_distance(b, g) < ft_min(b->width / 4, b->height / 4))
		g->play = E_ATTACK;
//	else
//		g->play = DEFENSE;
	trigger_strategy[game.play](b, g);
}

