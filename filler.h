/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 15:42:10 by mybenzar         ###   ########.fr       */
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
	E_GET_POS,
	E_GET_MIN,
	E_CHECK
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
}					t_game;

typedef int	(*t_strategy)(t_board *, t_game *);
typedef int (*t_parse_piece)(t_piece *);

/*
 **	Parsing Functions
 */

int						get_board(t_board *board);
int						get_player(void);
t_piece					*get_piece(void);
int						ft_left(t_piece *piece);
int						count_char(t_board *b, char c);
int						get_min(t_piece *piece);

/*
 **	Memory Handlers
 */

int						free_board(t_board *board);
int						free_piece(t_piece *piece);
int						free_game(t_game *game);
void					init_piece(t_piece *piece);
void					init_gb(t_game *game, t_board *board);

/*
 **	Play Functions
 */

void					strategy(t_board *b, t_game *g);
void					play(t_board *board, t_game *game);

/*
 **	Debug Functions
 */

void					display_board(t_board *board);
void					display_piece(t_piece *piece);
#endif
