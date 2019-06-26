/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/26 12:01:59 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	--> Find Closest Opponent's Piece : look for coordinates of closest 
**	oponent's piece in order to attack
**		>> get_distance computes the sum of the distance between coordinates
**		>> compute_dist compares distances between the target and the player
**		>> get_closest_op for each ennemy, finds the closest player coordinates
*/

static int		get_distance(int x, int y, int j, int i)
{
	return (ft_abs(x - j) + ft_abs(y - i));
}

static int		compute_dist(t_board *b, t_game *g)
{
	int	dist;
	int i;
	int j;

	i = 0;
	dist = b->height + b->width;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->player)
			{
				if (dist > get_distance(g->target.x, g->target.y, j, i))
				{
					dist = get_distance(g->target.x, g->target.y, j, i);
					g->place.x = j;
					g->place.y = i;
				}
			}
			j++;
		}
		i++;
	}
	return (dist);
}

static void	get_closest_op(t_board *b, t_game *g)
{
	int 	i;
	int 	j;
	int		dist;
	t_posi	place;
	int		tmp;

	i = 0;
	dist = b->height + b->width;
	place.x = 0;
	place.y = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->ennemy || b->tab[i][j] == ft_tolower(g->ennemy))
			{
				g->target.x = j;
				g->target.y = i;
				if ((tmp = compute_dist(b, g)) && dist > tmp && dist != 0) 
				{
					dist = tmp;
					place = g->place;
				}
			}
			j++;
		}
		i++;
	}
	g->place = place;
}

/*
**	--> Place Check : checks if there is enough space to place the piece
**	starting from the target coordinates
*/

static void		mark(t_board *b, int x, int y)
{
	b->tab[y][x] = '/';
}
/*
static int		place_left(t_game *g, int *x, int *y, t_posi pos)
{
	if (pos.x - g->place.x >= 0 && pos.y - g->place.y >= 0)
	{
		*x = pos.x - g->place.x;
		*y = pos.y - g->place.y;
		return (1);
	}
	return (0);
}
*/
static int		place_right(t_game *g, int *x, int *y, t_posi pos)
{
	*x = pos.x + g->place.x;
	*y = pos.y + g->place.y;
	return (1);
}

static int	count_char(t_board *b, char c)
{
	int		i;
	int 	j;
	int		count;

	i = 0;
	count = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static t_piece	*piece_cpy(t_piece *src)
{
	int		i;
	t_piece *dest;

	i = -1;
	if (!(dest = (t_piece*)ft_memalloc(sizeof(t_piece)))
		|| !(dest->pos = (t_posi*)malloc(sizeof(t_posi) * (size_t)src->size)))
		return (NULL);
	dest->size = src->size;
	while (++i < src->size)
	{
		dest->pos[i].x = src->pos[i].x;
		dest->pos[i].y = src->pos[i].y;
	}
	dest->width = src->width;
	dest->height = src->height;
	return (dest);
}

static int		place_check(t_board *b, t_game *g)
{
	int		x;
	int 	y;
	int 	i;
	t_piece	*p_rel;

	i = 1;
	p_rel = piece_cpy(b->piece);
	dprintf(2, "\n im in place check\n");
	dprintf(2, "\nbefore b->piece->pos[0].x = %d\n", b->piece->pos[0].x); 
	dprintf(2, "before b->piece->pos[0].y = %d\n", b->piece->pos[0].y); 
	if (ft_left(p_rel) == 0
		|| p_rel->width > b->width || p_rel->height > b->height)
		return (0);
	while (i < b->piece->size)
	{
		place_right(g, &x, &y, p_rel->pos[i]);
		if (x >= b->width || y >= b->height || count_char(b, g->player) == 0)
			return (0);
		else if (b->tab[y][x] == '.')
		{
			dprintf(2, "b->piece->pos[%d].x = %d + g->place.x = %d\n", i, p_rel->pos[i].x, g->place.x); 
			dprintf(2, "b->piece->pos[%d].y = %d + g->place.y = %d\n", i, p_rel->pos[i].y, g->place.y); 
			dprintf(2, "tab[%d][%d] = %c\n", y, x, b->tab[y][x]);
			i++;
		}
		else
		{
			dprintf(2, "-->entered the recursive loop\n");
			mark(b, g->place.x, g->place.y);
			get_closest_op(b, g);
			dprintf(2, "new g->place.x = %d, new g->place.y = %d\n", g->place.x, g->place.y);
			if (place_check(b, g) == 0)
				return (0);
		}
	}
	free_piece(p_rel);
	g->place.x -= b->piece->pos[0].x;
	g->place.y -= b->piece->pos[0].y;
	dprintf(2, "when quitting check place: \n g->place.x = %d, g->place.y = %d\n", g->place.x, g->place.y);
	dprintf(2, "\nafter ->piece->pos[0].x = %d\n", b->piece->pos[0].x); 
	dprintf(2, "after->piece->pos[0].y = %d\n", b->piece->pos[0].y); 
	return (1);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

static int	attack(t_board *board, t_game *game)
{
	dprintf(2, "\n\n--------------->>>ATTACK TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	get_closest_op(board, game);
	if (place_check(board, game) == 0)
	{
		/*dprintf(2, "place check failed and this is gonna exit\n");
		game->place.x = 0;
		game->place.y = 0;i*/
		game->play = E_SETTLE;
		return (0);
	}
	return (1);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

static int  mirror(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;
	int tmp;
	t_posi place;

	dprintf(2, "\n\n--------------->>>MIRROR TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	i = 0;
	dist = 0;
	place.x = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == ft_tolower(g->ennemy))
			{
				g->ennemy_pos.x = j;
				g->ennemy_pos.y = i;
				if ((tmp = compute_dist(b, g)) && dist > tmp) 
				{
					dist = tmp;
					place = g->place;
				}
			}
			j++;
		}
		i++;
	}
	//g->play = E_ATTACK;
	if (place_check(b, g) == 0)
	{
		g->place.x = 0;
		g->place.y = 0;
		return (1);
	}
	return (1);
}

/*
**	--> Settle : Covers most of the field in diagonal in order to block oponent
**	when reaches the top right corner and then the bottom left corner, starts 
**	attacking again
*/

static void	reset_board(t_board *b, t_game *g)
{
	int i;
	int j;

	i = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == '/')
				b->tab[i][j] = g->player;
			j++;
		}
		i++;
	}
}

static int	settle(t_board *b, t_game *g)
{
	dprintf(2, "\n\n--------------->>>SETTLE TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	g->target.y = b->height;
	g->target.x = b->width;
	compute_dist(b, g);
	dprintf(2, "g->place.x = %d\n g->place.y = %d\n", g->place.x, g->place.y);
	if (place_check(b, g) == 0)
	{
		reset_board(b, g);
		dprintf(2, "\n\n-->board has been reseted, new board:\n");
		display_board(b);
		g->play = E_ATTACK;
		return (0);
	}
	if (g->place.y == b->height || g->place.x == b->width)
	{
		g->target.y = 0;
		g->target.x = 0;
		dprintf(2, "\n\n ---> hello i've reached a corner\n");
		reset_board(b, g);
		compute_dist(b, g);
		dprintf(2, "g->place.x = %d\n g->place.y = %d\n", g->place.x, g->place.y);
		if (place_check(b, g) == 0)
		{
			g->play = E_ATTACK;
			return (0);
		}
	}
	return (1);
}

/*
** --> Strategy : if oponent is close then attack, if they're far, defend
*/

void strategy(t_board *b, t_game *g)
{
	static t_strategy	trigger_strategy[] = {attack, settle, mirror};
	int					i;

	i = 0;
	while (i == 0)
	{
		i = trigger_strategy[g->play](b, g);
		reset_board(b, g);
	}
}
