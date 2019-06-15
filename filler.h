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

#include "libft/includes/libft.h"

#define FD 1
# define PLAYER_ONE "$$$ exec p1 : ["
# define PLAYER_TWO "$$$ exec p2 : ["


typedef struct	s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct	s_board
{
	char	**tab;
	int		width;
	int		height;
}				t_board;

typedef struct s_piece
{
	t_pos	*pos;
	int		width;
	int		height;
	int		size;
}				t_piece;

typedef struct s_game
{
	int		player_nb;
	int		ennemy_nb;
	int		end;
	t_piece	*piece;		
}				t_game;

/*
**	Parsing Functions
*/

int		get_board(t_board *board);
void	get_dim(t_board *board);
int		get_player(void);
t_piece	*get_piece(void);
void	get_dim_piece(t_piece *piece);
char	**get_tab_piece(t_piece *piece);
int		get_piece_size(t_piece *piece, char **tab);
int		nb_adj_piece(char **tab, int x, int y);
/*
**	Memory Handlers
*/
//t_board	*allocate_board(t_board *board);
void	free_board(t_board *board);
void	free_piece(t_piece *piece);
void	free_game(t_game *game);
void	init_piece(t_piece *piece);
/*
**	Play Functions
*/

/*
**	Debug Functions
*/

void	display_board(t_board *board);
#endif
