/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:08:04 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/24 19:36:42 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
t_board		*allocate_board(t_board *board)
{
	int i;

	i = 0;
	if (!(board->tab = (char**)malloc(sizeof(char*) * board->height + 1)))
		return (NULL);
	while (i < board->height)
	{
		if (!(board->tab[i++] = (char*)malloc(sizeof(char) * board->width + 1)))
			return (NULL);
	}
	return (board);
}
*/

void		free_board(t_board *board)
{
	int i;

	i = 0;
	ft_strdel(board->tab);
	while (i < board->height)
		ft_strdel(&board->tab[i++]);
	board->height = 0;
	board->width = 0;
	free(board);
	board = NULL;

}
