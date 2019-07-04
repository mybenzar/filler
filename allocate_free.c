/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 12:25:46 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		free_piece(t_piece *piece)
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
	return (0);
}

int			free_board(t_board *board)
{
	int i;

	i = 0;
	if (board != NULL)
	{
		ft_bzero(board, sizeof(t_board));
		if (board->tab != NULL)
		{
			while (i < board->height)
				ft_strdel(&board->tab[i++]);
			ft_strdel(board->tab);
		}
		if (board->piece != NULL)
			free_piece(board->piece);
		free(board);
		board = NULL;
	}
	return (0);
}

int			free_game(t_game *game)
{
	if (game != NULL)
	{
		ft_bzero(game, sizeof(t_game));
		free(game);
		game = NULL;
	}
	return (0);
}
