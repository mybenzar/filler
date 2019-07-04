/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 16:16:32 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	play(t_board *board, t_game *game)
{
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 'O') ? 'X' : 'O';
	strategy(board, game);
	display_board(board);
	ft_printf("%d %d\n", game->place.y, game->place.x);
}

int		main(void)
{
	t_board	*board;
	t_game	*game;
	int		end;

	end = 0;
	if (!(board = (t_board*)ft_memalloc(sizeof(t_board)))
		|| !(game = (t_game*)ft_memalloc(sizeof(t_game)))
		|| !(game->player = get_player()))
		return (0);
	while (end == 0)
	{
		if (get_board(board) != 0)
		{
			if (!(board->piece = get_piece()))
				return (free_board(board) + free_game(game));
			play(board, game);
		}
		end = 1;
	}
	free_board(board);
	free_game(game);
	return (1);
}
