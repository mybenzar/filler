/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/27 17:17:09 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_first_line(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (get_next_line(FD, &line) <= 0)
	{
		ft_strdel(&line);
		return (0);
	}
	while (line[i] == ' ')
		i++;
	if (i != 4)
		return (0);
	while (line[i] != '\0')
	{
		if ((i - 4) % 10 + 48 != line[i] || i - 4 > board->width)
		{
			ft_strdel(&line);
			return (0);
		}
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
		return (0);
	if (ft_strncmp(line, "Plateau", 7) != 0)
		return (0);
	if (!(split = ft_strsplit(line + 8, ' '))
		|| !(board->height = ft_atoi(split[0]))
		|| !(board->width = ft_atoi(split[1])))
		return (0);
	if (board->height == 0 || board->width == 0 || ft_isdigit(board->height)
		|| ft_isdigit(board->width))
		return (0);
	return (1);
}

static int	clean_board(t_board *board)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < board->height)
	{
		if (!(tmp = ft_strdup(board->tab[i])))
			return (0);
		ft_strdel(&board->tab[i]);
		if (!(board->tab[i] = ft_strdup(tmp + 4)))
			return (0);
		ft_strdel(&tmp);
	}
	return (1);
}

/*
static int	analyze(t_board *board)
{
	int i;
	int j;

	i = 0;
	while (board->tab[i] != NULL)
	{
		j = 0;
		while (board->tab[i][j] != '\0')
		{
			if (board->tab[i][j] == g->player)
				board->tab[i][j] = E_PLAYER;
			if (board->tab[i][j] == ft_tolower(g->ennemy))
				board->tab[i][j] = E_ENNEMY;
			if (board->tab[i][j] == '.')
				board->tab[i][j] = E_EMPTY;
			j++;
		}
		i++;
	}
	return (1);
}
*/

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
