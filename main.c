/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 10:22:13 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		play(t_board *board, t_game *game)
{
	strategy(board, game);
	ft_printf("%d %d\n", game->place.y, game->place.x);
}

static int	assign_players(t_game *game)
{
	if (!(game->player = get_player()))
		return (1);
	game->player = (game->player == 1) ? 'O' : 'X';
	game->ennemy = (game->player == 'O') ? 'X' : 'O';
	return (0);
}

int			main(void)
{
	t_board			board;
	t_game			game;

	ft_bzero(&game, sizeof(t_game));
	if (assign_players(&game) == 1)
		return (EXIT_FAILURE);
	ft_bzero(&board, sizeof(t_board));
	while (1)
	{
		if (get_board(&board) == 0)
			break ;
		board.piece = get_piece();
		if (board.piece == NULL)
			break ;
		play(&board, &game);
	}
	free_board(&board);
	free_game(&game);
	return (EXIT_SUCCESS);
}
