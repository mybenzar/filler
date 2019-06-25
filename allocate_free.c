/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/25 16:00:34 by mybenzar         ###   ########.fr       */
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
*/

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
		game->ennemy_pos.x = 0;
		game->ennemy_pos.y = 0;
		game->target.x = 0;
		game->target.y = 0;
		free(game);
		game = NULL;
	}
}

void	init_gb(t_game *game, t_board *board)
{
//	ft_bzero(game, sizeof(t_game));
//	ft_bzero(board, sizeof(t_board));
	game->ennemy_pos.x = 0;
	game->ennemy_pos.y = 0;
	game->round = 0;
	game->target.x = 0;
	game->target.y = 0;
	board->width = 0;
	board->height = 0;
}
