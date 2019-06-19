/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 12:13:36 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_game *game)
{
	t_pos next_move;

	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 0) ? 'O' : 'X';
	next_move = strategy(board, game);
	ft_printf("%d %d\n", next_move.y, next_move.x);
}

int	main(void)
{
	t_board	*board;
	t_game	*game;
	char	*line;

	if (!(board = (t_board*)malloc(sizeof(t_board)))
		|| !(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	line = NULL;
	game->player = get_player();
//	ft_printf("player id = %d\n", game->player_nb);
	while (game->end == 0)
	{
		if (get_board(board) != 0)
		{
			board->piece = get_piece();
			return (0);
			play(board, game);
		}
		else
			game->end = 1;
	}
	display_board(board);
	free_board(board);
	free_game(game);
	return (0);
}
