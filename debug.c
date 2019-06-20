/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:07:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/20 07:42:28 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_board(t_board *board)
{
	int i;

	i = 0;
	ft_printf("board->height = %d, board->width = %d\n", board->height, board->width);
	while (i < board->height)
		ft_printf("%s\n", board->tab[i++]);
}

void	display_piece(t_piece *piece)
{
	int i;

	i = 0;
	ft_printf("board->piece->size = %d\n", piece->size);
	while (i < piece->size)
	{
		ft_printf("piece->pos[%d].x = %d // piece->pos[%d].y = %d\n", i, piece->pos[i].x, i, piece->pos[i].y);
		i++;
	}
	ft_printf("board->piece->height = %d\n", piece->height);
	ft_printf("board->piece->width = %d\n", piece->width);
}
