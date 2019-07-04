/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:14:10 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 16:47:24 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_tab(t_piece *piece)
{
	int		i;

	i = 0;
	if (get_dim(piece) == 0)
		return (0);
	if (!(piece->tab = (char **)malloc(sizeof(char *)
		* (size_t)(piece->height + 1))))
		return (0);
	while (i < piece->height)
	{
		piece->tab[i] = NULL;
		if (get_next_line(FD, &piece->tab[i]) < 0
			|| (int)ft_strlen(piece->tab[i]) != piece->width)
			return (0);
		i++;
	}
	piece->tab[i] = NULL;
	piece->parse = E_ANALYZE;
	return (1);
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
				return (0);
			j++;
		}
		i++;
	}
	if (piece->size == 0)
		return (0);
	piece->parse = E_GET_POS;
	return (1);
}

static int	get_pos(t_piece *piece)
{
	int i;
	int j;
	int p;

	i = -1;
	p = 0;
	if (!(piece->pos = (t_posi*)malloc(sizeof(t_posi)
		* (size_t)piece->size)))
		return (0);
	while (piece->tab[++i] != NULL)
	{
		j = 0;
		while (piece->tab[i][j] != '\0')
		{
			if (piece->tab[i][j] == '*')
			{
				piece->pos[p].x = j;
				piece->pos[p].y = i;
				p++;
			}
			j++;
		}
	}
	piece->parse = E_GET_MIN;
	return (1);
}

static int	check(t_piece *piece)
{
	int		x;
	int		y;
	int		nb;
	char	**tab;

	x = piece->pos[0].x;
	y = piece->pos[0].y;
	if (!(tab = ft_tabcpy(piece->tab)))
		return (0);
	nb = nb_adj_piece(tab, x, y);
	y = 0;
	ft_free_tab(tab, piece->height);
	if (nb != piece->size)
		return (0);
	return (2);
}

t_piece		*get_piece(void)
{
	int						i;
	t_piece					*piece;
	static t_parse_piece	trigger_parsing[] = {get_tab, analyze,
												get_pos, get_min, check};

	i = 0;
	if (!(piece = (t_piece*)ft_memalloc(sizeof(t_piece))))
		return (NULL);
	while (i != 2)
	{
		i = trigger_parsing[piece->parse](piece);
		if (i == 0)
			return (NULL);
	}
	return (piece);
}
