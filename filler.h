/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 09:38:01 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft/includes/libft.h"
# define FALSE 0
# define TRUE 1

enum				e_parse
{
	E_GET_TAB,
	E_ANALYZE,
	E_GET_MIN,
	E_FINISH
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
	t_posi			max;
	t_posi			*pos;
	enum e_parse	parse;
}					t_piece;

typedef struct		s_board
{
	char			**tab;
	int				width;
	int				height;
	int				area;
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

typedef int (*t_parse_piece)(t_piece *);

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
int						trim(t_piece *piece);

/*
**	Memory Handlers
*/

int						free_board(t_board *board);
int						free_piece(t_piece *piece);
int						free_game(t_game *game);
void					init_piece(t_piece *piece);
int						free_line(char **line);

/*
**	Play Functions
*/

int						check_piece(t_board *b, int x, int y);
int						start_piece(t_board *b, t_game *g, int x, int y);
int						get_distance(int x, int y, int j, int i);
void					get_min_distance(t_board *b, t_game *g);
void					strategy(t_board *b, t_game *g);
void					bottom_corner(t_board *b, t_game *g, int c_x, int c_y);
void					upper_corner(t_board *b, t_game *g, int c_x, int c_y);
void					fill(t_board *b, t_game *g);
int						count_char(t_board *b);
void					play(t_board *board, t_game *game);
void					possible_place(t_game *g, int *dist);

/*
**	Debug Functions
*/

void					display_board(t_board *board);
void					display_piece(t_piece *piece);

#endif
