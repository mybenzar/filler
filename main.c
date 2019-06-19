/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 18:02:24 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_game *game)
{
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 0) ? 'O' : 'X';
	strategy(board, game);
//	ft_printf("\n\nmy result :");
	ft_printf("%d %d\n", game->target.y, game->target.x);
}

int	main(void)
{
	t_board	*board;
	t_game	*game;

	if (!(board = (t_board*)malloc(sizeof(t_board)))
		|| !(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	init_gb(game, board);
	game->player = get_player();
//	ft_printf("player id = %d\n", game->player);
	while (game->end == 0)
	{
		if (get_board(board) != 0)
		{
			display_board(board);
			board->piece = get_piece();
//			ft_printf("piece parsed\n");
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
