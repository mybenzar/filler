/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:33:19 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/15 15:02:45 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void quarters(t_board *board, t_game *game)
{
	game->thresh.x = board->width / 4;
	game->thresh.y = board->height / 4;
	
}
