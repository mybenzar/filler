/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:14:10 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/10 14:49:31 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_tab(t_piece *piece)
{
	int		i;

	i = 0;
	if (get_dim(piece) == 0)
		return (FALSE);
	piece->tab = (char **)malloc(sizeof(char *) * (size_t)(piece->height + 1));
	if (piece->tab == NULL)
		return (FALSE);
	while (i < piece->height)
	{
		piece->tab[i] = NULL;
		if (get_next_line(STDIN_FILENO, &piece->tab[i]) <= 0
			|| (int)ft_strlen(piece->tab[i]) != piece->width)
		{
			ft_free_tab(piece->tab, piece->height);
			return (FALSE);
		}
		i++;
	}
	piece->tab[i] = NULL;
	piece->parse = E_ANALYZE;
	return (TRUE);
}

static int	analyze(t_piece *piece)
{
	int	i;
	int j;

	i = 0;
	while (piece->tab[i] != NULL)
	{
		j = 0;
		while (piece->tab[i][j] != '\0')
		{
			if (piece->tab[i][j] == '*')
				piece->size++;
			else if (piece->tab[i][j] != '\0'
				&& check_piece_elem(piece->tab[i][j]) == 0)
				return (FALSE);
			j++;
		}
		i++;
	}
	piece->parse = E_GET_MIN;
	return (piece->size == 0 ? FALSE : TRUE);
}

int		get_min(t_piece *piece)
{
	int x;
	int y;

	y = 0;
	piece->min.x = -1;
	piece->min.y = -1;
	while (piece->tab[y] != NULL)
	{
		x = 0;
		while (piece->tab[y][x] != '\0')
		{
			if (piece->tab[y][x] == '*')
			{
				if (x < piece->min.x || piece->min.x == -1)
					piece->min.x = x;
				if (y < piece->min.y || piece->min.y == -1)
					piece->min.y = y;
			}
			x++;
		}
		y++;
	}
	piece->parse = E_FINISH;
	return (1);
}

t_piece		*get_piece(void)
{
	t_piece					*piece;
	static t_parse_piece	trigger_parsing[] = {get_tab, analyze, get_min};

	piece = (t_piece*)ft_memalloc(sizeof(t_piece));
	if (piece == NULL)
		return (NULL);
	piece->parse = E_GET_TAB;
	while (piece->parse != E_FINISH)
	{
		if (trigger_parsing[piece->parse](piece) == 0)
			return (NULL);
	}
	return (piece);
}
