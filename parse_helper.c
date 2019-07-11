/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:36:41 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 17:56:20 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		check_piece_elem(char c)
{
	if (c != 'X' && c != 'O' && c != 'x'
			&& c != 'o' && c != '.')
	{
		ft_printf("error in check piece\n");
		return (0);
	}
	return (1);
}

int		get_dim(t_piece *piece)
{
	char				*line;
	char				**split;
	static const char	*piece_str = "Piece";

	line = NULL;
	split = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0 || line == NULL)
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
	return (1);
}
