/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/05 14:11:25 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	play(t_board *board, t_game *game)
{
	strategy(board, game);
	display_board(board);
	ft_printf("%d %d\n", game->place.y, game->place.x);
	dprintf(2, "to be placed %d %d\n", game->place.y, game->place.x);
}

static int	assign_players(t_game *game)
{
	if (!(game->player = get_player()))
		return (0);
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 'O') ? 'X' : 'O';
	return (1);
}

int		main(void)
{
	t_board	*board;
	t_game	*game;
	int		end;

	end = 0;
	if (!(board = (t_board*)ft_memalloc(sizeof(t_board)))
		|| !(game = (t_game*)ft_memalloc(sizeof(t_game)))
		|| assign_players(game) == 0)
		return (0);
	while (end == 0)
	{
		if (get_board(board) != 0)
		{
			if (!(board->piece = get_piece()))
				return (free_board(board) + free_game(game));
			play(board, game);
		}
		else
			end = 1;
	}
	free_board(board);
	free_game(game);
	return (1);
}
