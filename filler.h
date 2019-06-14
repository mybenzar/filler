/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/14 10:34:46 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#define FD 1

#include "libft/includes/libft.h"

typedef struct	s_board
{
	char	**tab;
	int		width;
	int		height;
}				t_board;

/*
**	Parsing Functions
*/

void	get_board(t_board *board);
void	get_dim(t_board *board);
int		get_player(void);

/*
**	Parsing Functions
*/

t_board	*allocate_board(t_board *board);
void	free_board(t_board *board);

/*
**	Debug Functions
*/

void	display_board(t_board *board);
#endif
