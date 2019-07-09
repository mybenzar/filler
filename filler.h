/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/09 16:00:17 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "libft/includes/libft.h"
#define FD 0
#define DEBUG 0
#include <stdio.h>

enum				e_parse
{
	E_GET_TAB,
	E_ANALYZE,
//	E_GET_POS,
	E_GET_MIN,
//	E_CHECK
};

enum				e_aim
{
	E_TOP_RIGHT,
	E_BOTTOM_LEFT,
	E_RUSH
};

typedef struct		s_posi
{
	int				x;
	int				y;
}					t_posi;

typedef struct		s_piece
{
	char			**tab;
	int				width;
	int				height;
	int				size;
	t_posi			min;
	t_posi			*pos;
	enum e_parse	parse;
}					t_piece;

typedef struct		s_board
{
	char			**tab;
	int				width;
	int				height;
	t_piece			*piece;
}					t_board;

typedef struct 		s_game
{
	int				player;
	int				ennemy;
	int				end;
	int				distance;
	int				overlap;
	t_posi			target;
	t_posi			pos_tmp;
	t_posi			place;
	enum e_aim		aim;
}					t_game;

typedef int (*t_parse_piece)(t_piece *);
typedef void (*t_aim)(t_board *b, t_game *g);

/*
 **	Parsing Functions
 */

int						get_board(t_board *board);
int						get_player(void);
t_piece					*get_piece(void);
int						ft_left(t_piece *piece);
int						get_min(t_piece *piece);
int						nb_adj_piece(char **tab, int x, int y);
int						check_piece_elem(char c);
int						get_dim(t_piece *piece);

/*
**	Memory Handlers
*/

int						free_board(t_board *board);
int						free_piece(t_piece *piece);
int						free_game(t_game *game);
void					init_piece(t_piece *piece);
int						free_line(char *line);

/*
**	Play Functions
*/

int						check_piece(t_board *b, int x, int y);
int						start_piece(t_board *b, t_game *g, int x, int y);
int						get_distance(int x, int y, int j, int i);
void					get_min_distance(t_board *b, t_game *g);
void					strategy(t_board *b, t_game *g);
void					play(t_board *board, t_game *game);

/*
**	Debug Functions
*/

void					display_board(t_board *board);
void					display_piece(t_piece *piece);

#endif
