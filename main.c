/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/15 15:02:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_piece *piece, t_game *game)
{
	t_pos next_move;

	game->player_nb = (game->player_nb == 1) ? 'O' : 'X';
	game->ennemy_nb = (game->player_nb == 0) ? 'O' : 'X';
	next_move = strategy(board, piece);
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
	game->player_nb = get_player();
//	ft_printf("player id = %d\n", game->player_nb);
	while (game->end == 0)
	{
		if (get_board(board) != 0)
		{
			game->piece = get_piece();
			return (0);
	//		play(board, game);
		}
		else
			game->end = 1;
	}
	display_board(board);
	free_board(board);
	free_game(game);
	return (0);
}
