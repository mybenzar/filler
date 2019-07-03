/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/03 15:20:22 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_piece(t_piece *piece)
{
	int i;

	i = 0;
	if (piece != NULL)
	{
		ft_bzero(piece, sizeof(t_piece));
		free(piece->pos);
		piece->pos = NULL;
		if (piece->tab != NULL)
		{
			while (i < piece->height)
			{
				ft_strdel(&piece->tab[i]);
				i++;
			}
		}
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
		ft_bzero(game, sizeof(t_game));
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
