/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 12:21:19 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
t_board		*allocate_board(t_board *board)
{
	int i;

	i = 0;
	if (!(board->tab = (char**)malloc(sizeof(char*) * board->height + 1)))
		return (NULL);
	while (i < board->height)
	{
		if (!(board->tab[i++] = (char*)malloc(sizeof(char) * board->width + 1)))
			return (NULL);
	}
	return (board);
}


void		free_piece(t_piece piece)
{
	free(piece.pos);
	init_piece(&piece);
	piece.pos = NULL;
//	free(&piece);
//	&piece = NULL;
}
*/

void		free_board(t_board *board)
{
	int i;

	i = 0;
	ft_strdel(board->tab);
	while (i < board->height)
		ft_strdel(&board->tab[i++]);
	board->height = 0;
	board->width = 0;
//	free_piece(board->piece);
	free(board);
	board = NULL;

}

void		free_game(t_game *game)
{
	game->player = 0;
	game->end = 0;
	game->ennemy_pos = NULL;
	game->target = NULL;
	free(game);
	game = NULL;
}
