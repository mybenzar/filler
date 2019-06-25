/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/25 16:52:28 by mybenzar         ###   ########.fr       */
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

static int		place_check(t_board *b, t_game *g)
{
	int		x;
	int 	y;
	int 	i;
	t_posi	tmp;

	dprintf(2, "\n im in place check\n");
	tmp.x = b->piece->pos[0].x;
	tmp.y = b->piece->pos[0].y;
	if (ft_left(b->piece) == 0)
		return (0);
	i = 1;
	if (b->piece->width > b->width || b->piece->height > b->height)
		return (0);
	while (i < b->piece->size)
	{
		x = b->piece->pos[i].x + g->place.x;
		y = b->piece->pos[i].y + g->place.y;
		dprintf(2, "tab[%d][%d] = %c\n", y, x, b->tab[y][x]);
		if (b->tab[y][x] == '.')
			i++;
		else if (b->tab[y][x] == '\0' && b->tab[y] == NULL)
			return (0);
		else
			//(b->tab[y][x] == g->ennemy || b->tab[y][x] == ft_tolower(g->ennemy))
		{
			mark(b, g->place.x, g->place.y);
			get_closest_op(b, g);
			if (place_check(b, g) == 0)
				return (0);
		}
	}
	g->place.x -= tmp.x;
	g->place.y -= tmp.y;
	return (1);
}

/*
**	--> Attack : moves directly towards the closest opponent's piece
**	and then triggers the mirror attack
*/

static int	attack(t_board *board, t_game *game)
{
	dprintf(2, "\nattack has been triggered\n");
	get_closest_op(board, game);
	if (place_check(board, game) == 0)
	{
		/*dprintf(2, "place check failed and this is gonna exit\n");
		game->place.x = 0;
		game->place.y = 0;i*/
		game->play = E_MIRROR;
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

	dprintf(2, "\nmirror has been triggered\n");
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

static int	settle(t_board *b, t_game *g)
{
	dprintf(2, "settle has been triggered\n");
	g->target.y = 0;
	g->target.x = b->height;
	compute_dist(b, g);
	dprintf(2, "g->place.x = %d\n g->place.y = %d\n", g->place.x, g->place.y);
	if (place_check(b, g) == 0)
	{
		g->play = E_ATTACK;
		return (0);
	}
	if (g->place.x == 0 && g->place.y == b->width)
	{
		g->target.y = b->width;
		g->target.x = 0;
		compute_dist(b, g);
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
	static t_strategy	trigger_strategy[] = {settle, attack, mirror};
	int					i;

	i = 0;
	while (i == 0)
		i = trigger_strategy[g->play](b, g);
}

/*

static void		mark(t_board *b, t_game *g)
{
	b->tab[g->target.y][g->target.x] = '/';
}
static int		place_check(t_board *b, t_game *g)
{
	int		x;
	int 	y;
	int 	i;
	t_posi	tmp;

	tmp.x = b->piece->pos[0].x;
	tmp.y = b->piece->pos[0].y;
	if (ft_left(b->piece) == 0)
		return (0);
	i = 1;
	if (b->piece->width > b->width || b->piece->height > b->height)
		return (0);
	while (i < b->piece->size)
	{
		x = b->piece->pos[i].x + g->place.x;
		y = b->piece->pos[i].y + g->place.y;
		i++;
		if (b->tab[y][x] != '.')
		{
			if (b->tab[y][x] == g->ennemy || b->tab[y][x] == ft_tolower(g->ennemy))
			{
				
			}
			if (b->tab[y][x] != '\0' && b->tab[y][x] != '/' && b->tab[y])
			{
				mark(b, g);
				get_closest_op(b, g); 
				if (place_check(b, g) == 0)
					return (0);
			}
			if (b->tab[y][x] == '\0' && b->tab[y] == NULL)
				return (0);
			i = 1;
		}
	}
	g->place.x -= tmp.x;
	g->place.y -= tmp.y;
	return (1);
}
*/
