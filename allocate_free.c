/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/27 15:38:11 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

void	init_gb(t_game *game, t_board *board)
V{
//	ft_bzero(game, sizeof(t_game));
//	ft_bzero(board, sizeof(t_board));
	game->ennemy_pos.x = 0;
	game->ennemy_pos.y = 0;
	game->target.x = 0;
	game->target.y = 0;
	board->width = 0;
	board->height = 0;
}
