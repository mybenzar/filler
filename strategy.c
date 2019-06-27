/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/27 12:29:48 by mybenzar         ###   ########.fr       */
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
static int find_possible_place(t_board *b, t_game *g)
{
	int i;
	int j;

	i = 0;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->player)
			{
				g->place.x = j;
				g->place.y = i;
				dprintf(2, "\n--> in find posible place, places found are:\n g->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
*/

/*
**	--> Place Check : checks if there is enough space to place the piece
**	starting from the target coordinates
*/

static void		mark(t_board *b, int x, int y)
{
	b->tab[y][x] = '/';
}

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

static int		scan(t_board *b, t_game *g, t_piece *p_rel, left)
{
	int		x;
	int 	y;	
	int 	i;

	i = 1;
	while (i < b->piece->size)
	{
		if (left == 1)
			place_left(g, &x, &y, p_rel->pos[i]);
		else
			place_right(g, &x, &y, p_rel->pos[i]);
		if (x >= b->width || y >= b->height || x < 0 || y < 0
			|| (b->tab[y][x] != '\0' && b->tab[y][x] != '.'))
			 return (0);
		if (b->tab[y][x] == '.')
			i++;
		if (i == b->piece->size)
			return (1);
}
//while scan = 0, start++
static int		place_check(t_board *b, t_game *g, int left, int *start)
{
	t_piece	*p_rel;

	p_rel = piece_cpy(b->piece);
	if (p_rel->width > b->width || p_rel->height > b->height)
		return (0);
	while (*start < b->piece->size)
	{
		ft_left(p_rel, start);
		if (scan(b, g, p_rel, left) == 1)
			return (1);
		*start += 1;
	}
	free_piece(p_rel);
	return (0);
}

static int	surrender(t_board *b, t_game *g)
{
	reset_board(b, g);
	g->place.x = 0;
	g->place.y = 0;
	return (1);
}

static int	attack(t_board *b, t_game *g)
{
	int left;
	int start;

	dprintf(2, "\n\n--------------->>>ATTACK TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	left = 0;
	get_closest_op(b, g);
	while (place_check(b, g, left, &start) == 0)
	{
		mark(b, g->place.x, g->place.y);
		get_closest_op(b, g);
		dprintf(2, "coordinates to be tried :\ng->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
		display_board(b);
		if (count_char(b, g->player) == 0)
		{
			if (left == 1)
				return (0);
			left = 1;
			reset_board(b, g);
			dprintf(2, "board reseted\n");
			display_board(b);
		}
	}
	g->place.x += (left == 0) ? - b->piece->pos[start].x : b->piece->pos[start].x;
	g->place.y += (left == 0) ? - b->piece->pos[start].y : b->piece->pos[start].y;
	return (1);
}

void strategy(t_board *b, t_game *g)
{
	if (attack(b, g) == 0)
		surrender(b, g);
}

/*
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
*/
/*
**	--> Settle : Covers most of the field in diagonal in order to block oponent
**	when reaches the top right corner and then the bottom left corner, starts 
**	attacking again
*/

/*
static int	settle(t_board *b, t_game *g)
{
	dprintf(2, "\n\n--------------->>>SETTLE TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	g->target.y = b->height - 1;
	g->target.x = b->width - 1;
	compute_dist(b, g);
	dprintf(2, "g->place.x = %d\n g->place.y = %d\n", g->place.x, g->place.y);
	if (place_check(b, g) == 0 || g->place.y == b->height - 1 || g->place.x == b->width - 1)
	{
		if (g->place.y == b->height || g->place.x == b->width)
		{
			g->target.y = 0;
			g->target.x = 0;
			dprintf(2, "\n\n ---> hello i've reached a corner\n");
			compute_dist(b, g);
			dprintf(2, "g->place.x = %d\n g->place.y = %d\n", g->place.x, g->place.y);
			if (place_check(b, g) == 0)
			{
				g->play = E_FILL;
				return (0);
			}
		reset_board(b, g);
		dprintf(2, "\n\n-->board has been reseted, new board:\n");
		display_board(b);
		g->play = E_FILL;
		return (0);
		}
	}
	return (1);
}
*/
/*
static int	fill(t_board *b, t_game *g)
{
	dprintf(2, "\n\n--------------->>>FILL TRIGGERED<<<<<<<<<<<<<<---------------\n\n");
	if (find_possible_place(b, g) == 1 && place_check(b, g) == 1)
		return (1);
	else
	{
		g->play = E_SURRENDER;
		return (0);
	}
}
*/
/*
** --> Strategy : if oponent is close then attack, if they're far, defend
*/
