/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/24 19:36:41 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_board(t_board *board)
{
	int i;

	i = 0;
	get_dim(board);
	ft_printf("board->height = %d, board->width = %d\n", board->height, board->width);
	while (i < board->height)
	{
		if (get_next_line(FD, &board->tab[i]) < 0)
			return ;
		i++;
	}
}

void	get_dim(t_board *board)
{
	char *line;
	char **split;

	line = NULL;
	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' ')))
		return ;
	if (ft_strcmp(split[0], "Plateau") != 0
		|| !(board->height = ft_atoi(split[1]))
		|| !(board->width = ft_atoi(split[2])))
		return ;
}

int		get_player(void)
{
	char	*line;
	int		id;

	if (get_next_line(FD, &line) < 0)
		return (-1);
	if (ft_strncmp(line, "$$$ exec p", 10) != 0
		|| (!(id = ft_atoi(line + 10)) && id != 1 && id != 2))
		return (-1);
	if (ft_strncmp(line + 15, "[mybenzar]", 10) != 0)
		return (-1);
	ft_strdel(&line);
	return (id);
}
