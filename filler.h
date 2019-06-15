/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/15 15:02:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "libft/includes/libft.h"

#define FD 1

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_board
{
	char		**tab;
	int			width;
	int			height;
}				t_board;

typedef struct s_piece
{
	t_pos		*pos;
	int			width;
	int			height;
	int			size;
}				t_piece;

typedef struct 		s_game
{
	int				player;
	int				ennemy;
	s_pos			ennemy_pos;
	int				end;
	t_piece			*piece;
	enum e_state	state;
	enum e_play		play;
	int				distance;
}					t_game;

enum			e_state
{
	E_EMPTY;
	E_FULL;
}

enum			e_play
{
	E_ATTACK;
	E_MIRROR;
	E_DEFENSE;
}

typedef unsigned char	(*t_strategy)(t_game *);

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
