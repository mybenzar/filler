/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/15 15:02:42 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

t_pos	attack(t_board *board, t_game *game)
{
	if (game->state == E_EMPTY)

}

t_pos mirror(t_board *board, t_game *game)
{
	
}

/*
**	--> Defense : Covers most of the field in diagonal in order to block oponent
*/

t_pos	defense(t_board *board, t_game *game)
{

}

/*
**	--> Find Closest Opponent's Piece : look for coordinates of closest 
**	oponent's piece in order to attack
*/

int		get_closest_op(t_board *b, t_game *game)
{
	int	count;
	int	x;
	int y;
	int i;

	i = 0;
	while (i < game->piece.size)
}

t_pos	op_pieces_comp(t_board *b, t_game *game)
{
	int i;
	int j;
	t_pos ;

	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == game->ennemy)
			{
				game->ennemy_pos.x = j;
				game->ennemy_pos.y = i;
				get_closest_op(b, game);
			}
			j++;
		}
		i++;
	}
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

