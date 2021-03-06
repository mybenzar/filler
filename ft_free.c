/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 10:16:04 by mybenzar         ###   ########.fr       */
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
	ft_free_tab(piece->tab, piece->height);
	free(piece->pos);
	piece->pos = NULL;
	free(piece);
	piece = NULL;
	return (0);
}

int			free_board(t_board *board)
{
	int i;

	i = 0;
	ft_free_tab(board->tab, board->height);
	free_piece(board->piece);
	board->width = 0;
	board->height = 0;
	return (0);
}

int			free_game(t_game *game)
{
	game->player = 0;
	game->ennemy = 0;
	game->distance = -2;
	game->overlap = 0;
	init_pos(game->target);
	init_pos(game->pos_tmp);
	init_pos(game->place);
	return (0);
}

int			free_line(char **line)
{
	ft_strdel(line);
	return (0);
}
