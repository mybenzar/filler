/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/03 10:50:35 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_piece(t_piece *piece)
{
	int i;

	i = 0;
	if (piece != NULL)
	{
		free(piece->pos);
		piece->pos = NULL;
		while (piece->tab[i] != NULL)
			ft_strdel(&piece->tab[i++]);
		ft_strdel(piece->tab);
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
		game->pos_tmp.x = 0;
		game->pos_tmp.y = 0;
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
