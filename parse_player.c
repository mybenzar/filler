/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 15:42:12 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	free_line(char *line)
{
	ft_strdel(&line);
	return (0);
}

static int	check_first_line(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (get_next_line(FD, &line) <= 0)
		return (free_line(line));
	while (line[i] == ' ')
		i++;
	if (i != 4)
		return (free_line(line));
	while (line[i] != '\0')
	{
		if ((i - 4) % 10 + 48 != line[i] || i - 4 > board->width)
			return (free_line(line));
		i++;
	}
	ft_strdel(&line);
	return (1);
}

static int	get_dim(t_board *board)
{
	char	*line;
	char	**split;

	line = NULL;
	if (get_next_line(FD, &line) < 0)
		return (free_line(line));
	if (ft_strncmp(line, "Plateau", 7) != 0)
		return (free_line(line));
	if (!(split = ft_strsplit(line + 8, ' '))
		|| !(board->height = ft_atoi(split[0]))
		|| !(board->width = ft_atoi(split[1])))
		return (free_line(line));
	ft_free_tab(split, 2);
	if (board->height == 0 || board->width == 0 || ft_isdigit(board->height)
		|| ft_isdigit(board->width))
		return (free_line(line));
	ft_strdel(&line);
	return (1);
}

static int	clean_board(t_board *board)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < board->height)
	{
		if (!(tmp = ft_strdup(board->tab[i])))
			return (0);
		ft_strdel(&board->tab[i]);
		if (!(board->tab[i] = ft_strdup(tmp + 4)))
			return (0);
		ft_strdel(&tmp);
		i++;
	}
	return (1);
}

int		get_board(t_board *board)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (get_dim(board) == 0)
		return (0);
	if (!(board->tab = (char**)malloc(sizeof(char*) * (size_t)(board->height + 1))))
		return (0);
	if (check_first_line(board) == 0)
		return (0);
	while (i < board->height)
	{
		board->tab[i] = NULL;
		if (get_next_line(FD, &board->tab[i]) < 0
			|| ft_atoi(board->tab[i]) != i)
			return (0);
		i++;
	}
	board->tab[i] = NULL;
	if (clean_board(board) == 0)
		return (0);
	return (1);
}

int		get_player(void)
{
	char	*line;
	int		id;

	line = NULL;
	if (get_next_line(FD, &line) < 0)
		return (free_line(line));
	if (ft_strncmp(line, "$$$ exec p", 10) != 0
		|| (!(id = ft_atoi(line + 10))))
		return (free_line(line));
	if (id != 1 && id != 2)
		return (free_line(line));
	if (ft_strncmp(line + 11, " : [./mybenzar.filler]", 22) != 0)
		return (free_line(line));
	ft_strdel(&line);
	return (id);
}
