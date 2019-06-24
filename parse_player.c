/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/24 19:46:37 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	check_first_line(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (get_next_line(FD, &line) <= 0)
	{
		ft_strdel(&line);
		return ;
	}
	while (line[i] == ' ')
		i++;
	if (i != 4)
		return ;
	while (line[i] != '\0')
	{
		if ((i - 4) % 10 + 48 != line[i] || i - 4 > board->width)
		{
			ft_strdel(&line);
			return ;
		}
		i++;
	}
	ft_strdel(&line);
}

void	get_dim(t_board *board)
{
	char *line;
	char **split;
	char *tmp;

	line = NULL;

	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' '))
		|| !(tmp = ft_strdup("Plateau")))
		return ;
	if (ft_strcmp(split[0], tmp) != 0
		|| !(board->height = ft_atoi(split[1]))
		|| !(board->width = ft_atoi(split[2])))
		return ;
	ft_strdel(&tmp);
	ft_strdel(split);
	ft_strdel(&split[0]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
}

static void	clean_board(t_board *board)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < board->height)
	{
		if (!(tmp = ft_strdup(board->tab[i])))
			return ;
		ft_strdel(&board->tab[i]);
		if (!(board->tab[i] = ft_strdup(tmp + 4)))
			return ;
		ft_strdel(&tmp);
	}
}

int		get_board(t_board *board)
{
	int i;
	int j;

	i = 0;
	j = 0;
	get_dim(board);
	if (!(board->tab = (char**)malloc(sizeof(char*) * (size_t)(board->height + 1))))
		return (0);
	check_first_line(board);
	while (i < board->height)
	{
		if (get_next_line(FD, &board->tab[i]) < 0
			|| ft_atoi(board->tab[i]) != i)
		{
			while (j <= i)
				ft_strdel(&board->tab[j++]);
			ft_strdel(board->tab);
			return (0);
		}
		i++;
	}
	board->tab[i] = NULL;
	clean_board(board);
	return (1);
}

int		get_player(void)
{
	char	*line;
	int		id;

	line = NULL;
	if (get_next_line(FD, &line) < 0)
		return (-1);
	if (ft_strncmp(line, "$$$ exec p", 10) != 0
		|| (!(id = ft_atoi(line + 10))))
		return (-1);
	if (id != 1 && id != 2)
		return (-1);
	if (ft_strncmp(line + 11, " : [./mybenzar.filler]", 22) != 0)
		return (-1);
	ft_strdel(&line);
	return (id);
}
