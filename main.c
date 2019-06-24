/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/24 20:08:25 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_game *game)
{
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player != 1) ? 'O' : 'X';
	strategy(board, game);
	ft_printf("%d %d\n", game->target.y, game->target.x);
}

int	main(void)
{
	t_board	*board;
	t_game	*game;
	int		end;
	int		player_id;

	end = 0;
//	DD("lol");
//	DUMP
		player_id = get_player();
	while (end == 0)
	{
		if (!(board = (t_board*)ft_memalloc(sizeof(t_board)))
			|| !(game = (t_game*)ft_memalloc(sizeof(t_game))))
			return (0);
		init_gb(game, board);
		game->player = player_id;
		if (get_board(board) != 0)
		{
			if (!(board->piece = get_piece()))
			{
				DD("main");
				while (1) ;
				return (0);
			}
			play(board, game);
		}
		else
			end = 1;
		free_board(board);
		free_game(game);
	}
	return (0);
}
