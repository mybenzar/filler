/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:02 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/24 20:08:24 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "libft/includes/libft.h"

#define DUMP char *line = NULL; int ret = 0; while ((ret = get_next_line(FD, &line) != -1000)) { DD(line); if (ret < 0) exit(0); }
#define DD(x) ft_putendl_fd(x, 2)
#define DN(x) ft_putendl_fd(ft_itoa(x), 2)

#define FD 0
#define DEBUG 0

enum				e_state
{
	E_EMPTY,
	E_FULL
};

enum				e_play
{
	E_ATTACK,	E_MIRROR,
	E_SETTLE,
};

typedef struct		s_posi
{
	int				x;
	int				y;
}					t_posi;

typedef struct		s_piece
{
	t_posi			*pos;
	int				width;
	int				height;
	int				size;
	char			pad[4];
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
	t_posi			ennemy_pos;
	int				end;
	enum e_state	state;
	enum e_play		play;
	t_posi			target;
}					t_game;

typedef t_posi	(*t_strategy)(t_board *, t_game *);

/*
**	Parsing Functions
*/

int						get_board(t_board *board);
void					get_dim(t_board *board);
int						get_player(void);
t_piece					*get_piece(void);
void					get_dim_piece(t_piece *piece);
char					**get_tab_piece(t_piece *piece);
int						get_piece_size(t_piece *piece, char **tab);
int						nb_adj_piece(char **tab, int x, int y);
int					ft_left(t_piece *piece);
/*
**	Memory Handlers
*/

//t_board	*allocate_board(t_board *board);
void					free_board(t_board *board);
void					free_piece(t_piece *piece);
void					free_game(t_game *game);
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
