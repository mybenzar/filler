/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 15:42:10 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_game *game)
{
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 'O') ? 'X' : 'O';
	strategy(board, game);
	display_board(board);
	ft_printf("%d %d\n", game->place.y, game->place.x);
}

int	main(void)
{
	t_board	*board;
	t_game	*game;
	int		end;
	int		player_id;

	end = 0;
	player_id = get_player();
	if (player_id == 0)
		return (0);
	if (!(board = (t_board*)ft_memalloc(sizeof(t_board)))
		|| !(game = (t_game*)ft_memalloc(sizeof(t_game))))
		return (0);
	while (end == 0)
	{
		game->player = player_id;
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
