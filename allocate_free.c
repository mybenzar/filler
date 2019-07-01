/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/01 16:31:07 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_piece(t_piece *piece)
{
	if (piece != NULL)
	{
		free(piece->pos);
		piece->pos = NULL;
		free(piece);
		piece = NULL;
	}
}

void		free_board(t_board *board)
{
	int i;

	i = 0;
	if (board != NULL)
	{
		while (i < board->height)
			ft_strdel(&board->tab[i++]);
		ft_strdel(board->tab);
		free_piece(board->piece);
		ft_bzero(board, sizeof(t_board));
		free(board);
		board = NULL;
	}
}

void		free_game(t_game *game)
{
	if (game != NULL)
	{
		game->player = 0;
		game->end = 0;
		game->to_mark.x = 0;
		game->to_mark.y = 0;
		game->target.x = 0;
		game->target.y = 0;
		free(game);
		game = NULL;
	}
}
/*
void		free_board(t_board *board)
{
	int i;

	i = 0;
	if (board != NULL)
	{
		while (i < board->height)
			ft_strdel(&board->tab[i++]);
		ft_strdel(board->tab);
		free_piece(board->piece);
		ft_bzero(board, sizeof(t_board));
		free(board);
		board = NULL;
	}
}

void		free_game(t_game *game)
{
	if (game != NULL)
	{
		free_board(game->board);
		free_board(game->piece);
		ft_bzero(game, sizeof(t_game));
		free(game);
		game = NULL;
	}
}
*/
