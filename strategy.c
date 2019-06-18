/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/18 12:18:46 by mybenzar         ###   ########.fr       */
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
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

t_pos	attack(t_board *board, t_game *game)
{
	get_closest_op(board, game);
	game->play = E_MIRROR;
	return (g->target);
}

t_pos mirror(t_board *b, t_game *g)
{
	int i;
	int j;

	while (b->tab[i] != NULL)
	{
		j = 0;
		while (g->tab[i][j] != '\0')
		{
			if (g->tab[i][j] == ft_)
		}
	}
}

/*
**	--> Defense : Covers most of the field in diagonal in order to block oponent
*/

t_pos	defense(t_board *board, t_game *game)
{

}
/*
** --> Strategy : if oponent is close then attack, if they're far, defend
*/

t_pos strategy(t_board *board, t_game *game)
{
	static t_strategy	trigger_strategy[] = {attack, mirror, defense};

	find_closest_op(board, game);
	compute_distance(board, game);
	trigger_strategy[game.play](board, game);
}

