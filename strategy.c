/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:13:56 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 12:08:03 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	find_target(t_board *b, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	g->distance = -1;
	while (b->tab[i] != NULL)
	{
		j = 0;
		while (b->tab[i][j] != '\0')
		{
			if (b->tab[i][j] == g->ennemy || b->tab[i][j] == g->ennemy - 32)
			{
				g->target.x = j;
				g->target.y = i;
				get_min_distance(b, g);
			}
			j++;
		}
		i++;
	}
}

static void	possible_place(t_game *g, int *dist)
{
	*dist = g->distance;
	g->place.x = g->pos_tmp.x;
	g->place.y = g->pos_tmp.y;
}

static void bottom_corner(t_board *b, t_game *g, int c_x, int c_y)
{
	int i;
	int j;
	int dist;

	i = b->height - 1;
	dist = -2;
	while (i >= 0)
	{
		j = b->width - 1;
		while (j >= 0)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
					dprintf(2, "g->pos_tmp.x = %d, g->pos_tmp.y = %d\n", g->pos_tmp.x, g->pos_tmp.y);
				g->target.x = c_x - 1;
				g->target.y = c_y - 1;
				get_min_distance(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j--;
		}
		i--;
	}
}

static void	upper_corner(t_board *b, t_game *g, int c_x, int c_y)
{
	int i;
	int j;
	int dist;

	i = 0;
	dist = -2;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				g->target.x = c_x - 1;
				g->target.y = c_y - 1;
				get_min_distance(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j++;
		}
		i++;
	}
}
static void	attack(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;

	i = 0;
	dist = -2;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->pos_tmp.x = j - b->piece->min.x;
				g->pos_tmp.y = i - b->piece->min.y;
				find_target(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j++;
		}
		i++;
	}
}

static int	corner_full(t_board *b, int c_x, int c_y)
{
	int i;
	int j;
	int	area;
	int	full;

	full = 0;
	area = b->height * b->width;
	i = b->height / 4;
	while (i < c_y)
	{
		j = b->width / 4;
		while (j < c_x)
		{
			if (b->tab[i][j] != '.')
				full++;
			j++;
		}
		i++;
	}
	dprintf(2, "full = %d, area / 32 = %d\n", full, area / 32);
	return (full > (area / 32) ? 1 : 0);
}

/*
static int	count_char(t_board *b, int c)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (b->tab[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count > 0 ? 1 : 0);
}

static void fill(t_board *b, t_game *g)
{
	int i;
	int j;
	int dist;

	i = 0;
	dist = -2;
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			if (check_piece(b, j, i) == 1 && start_piece(b, g, j, i) == 1)
			{
				g->target.x = j - b->piece->min.x;
				g->target.y = i - b->piece->min.y;
				get_min_distance(b, g);
				if (g->distance < dist || dist == -2)
					possible_place(g, &dist);
			}
			j++;
		}
		i++;
	}
}

*/
void		strategy(t_board *b, t_game *g)
{
	if (b->piece->min.x != 0 || b->piece->min.y != 0)
		ft_left(b->piece);
	if (b->height > 20 && b->width > 20)
	{
		if (corner_full(b, b->width, b->height) == FALSE)
		{
			dprintf(2, " bottom corner launched\n");
			bottom_corner(b, g, b->width, b->height);
			dprintf(2, "\n\n g->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
		}
		if (corner_full(b, b->width, 0) == FALSE)
		{
			dprintf(2, " upper corner launched\n");
			upper_corner(b, g, b->width, 0);
			dprintf(2, "\n\n g->place.x = %d and g->place.y = %d\n", g->place.x, g->place.y);
		}
		else
			attack(b, g);
	}
/*
	if (count_char(b, g->ennemy - 32) == 0 && count_char(b, g->ennemy) != 0)
		fill(b, g);
*/
	else
		attack(b, g);
}
