/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:07:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 16:36:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_board(t_board *board)
{
	int i;

	i = 0;
	dprintf(2, "board->height = %d, board->width = %d\n", board->height, board->width);
	while (i < board->height)
		dprintf(2, "%s\n", board->tab[i++]);
}

void	display_piece(t_piece *piece)
{
	int i;

	i = 0;
	while (i < piece->height)
	{
		dprintf(2, "%d %s\n", i, piece->tab[i]);
		i++;
	}
}
