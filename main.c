/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/24 19:29:56 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void play(t_board *board, t_game *game)
{
game->player = (game->player == 1) ? 'O' : 'X';
game->ennemy = (game->player != 1) ? 'O' : 'X';
/* if (DEBUG)
{
	ft_printf("\n-->in play\n");
	ft_printf("game->player = %c\n", game->player);
	ft_printf("game->ennemy = %c\n", game->ennemy);
} */
strategy(board, game);
//	ft_printf("\n\nmy result :");
ft_printf("%d %d\n", game->target.y, game->target.x);
//	game->target.y = 0;
//	game->target.x = 0;
}

int	main(void)
{
t_board	*board;
t_game	*game;
int		end;
int		player_id;
//	int 	fd;

//	fd = open("test", O_WRONLY, O_CREATE, 0644);
end = 0;
DD("lol");
DUMP
player_id = get_player();
while (end == 0)
{

		if (!(board = (t_board*)malloc(sizeof(t_board)))
			|| !(game = (t_game*)malloc(sizeof(t_game))))
		{
			return (0);
		}
		init_gb(game, board);
		game->player = player_id;
//		if (get_board(board, fd) != 0)
		if (get_board(board) != 0)
		{
//			dprintf(fd, "valeur de end : %d\n", end);
			if (!(board->piece = get_piece()))
			{
				DD("main");
				while (1) ;
				return (0);
			}
			/* if (DEBUG)
				ft_printf("piece parsed\n"); */
			play(board, game);
		}
		else
			end = 1;
		free_board(board);
		free_game(game);
	}
	return (0);
}
