/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:36:41 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 12:17:30 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			check_piece_elem(char c)
{
	if (c != 'X' && c != 'O' && c != 'x'
			&& c != 'o' && c != '.')
		return (FALSE);
	return (TRUE);
}

int			get_dim(t_piece *piece)
{
	char				*line;
	char				**split;
	static const char	*piece_str = "Piece";

	line = NULL;
	split = NULL;
	if (get_next_line(&line) <= 0 || line == NULL)
		return (free_line(&line));
	split = ft_strsplit(line, ' ');
	if (split == NULL || split[0] == NULL || split[1] == NULL)
		return (free_line(&line));
	if (ft_strequ(split[0], piece_str) == FALSE)
		return (free_line(&line));
	piece->height = ft_atoi(split[1]);
	piece->width = ft_atoi(split[2]);
	if (piece->height == 0 || piece->width == 0)
		return (free_line(&line));
	ft_free_tab(split, 3);
	ft_strdel(&line);
	return (TRUE);
}

static int	get_max(t_piece *piece)
{
	int x;
	int y;

	y = 0;
	piece->max.x = -1;
	piece->max.y = -1;
	while (y < piece->height)
	{
		x = 0;
		while (x < piece->width)
		{
			if (piece->tab[y][x] == '*')
			{
				if (x > piece->max.x || piece->max.x == -1)
					piece->max.x = x;
				if (y > piece->max.y || piece->max.y == -1)
					piece->max.y = y;
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

int			trim(t_piece *piece)
{
	int i;
	int j;

	get_max(piece);
	i = piece->max.y + 2;
	while (i < piece->height)
		ft_strdel(&piece->tab[i++]);
	piece->height = piece->max.y + 1;
	i = 0;
	while (i < piece->height)
	{
		j = piece->max.x + 1;
		while (j < piece->width)
			piece->tab[i][j++] = '\0';
		i++;
	}
	piece->width = piece->max.x + 1;
	return (TRUE);
}
