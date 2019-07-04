/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 16:20:16 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	init_pos(t_posi pos)
{
	pos.x = 0;
	pos.y = 0;
	return (0);
}

int			free_piece(t_piece *piece)
{
	int i;

	i = 0;
	if (piece != NULL)
	{
		if (piece->tab != NULL)
			ft_free_tab(piece->tab, piece->height);
		if (piece->pos != NULL)
		{
			free(piece->pos);
			piece->pos = NULL;
		}
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
		ft_free_tab(board->tab, board->height);
		if (board->piece != NULL)
			free_piece(board->piece);
		board->width = 0;
		board->height = 0;
		free(board);
		board = NULL;
	}
	return (0);
}

int			free_game(t_game *game)
{
	if (game != NULL)
	{
		game->player = 0;
		game->ennemy = 0;
		game->distance = -2;
		game->overlap = 0;
		init_pos(game->target);
		init_pos(game->pos_tmp);
		init_pos(game->place);
		free(game);
		game = NULL;
	}
	return (0);
}

int			free_line(char *line)
{
	ft_strdel(&line);
	return (0);
}
