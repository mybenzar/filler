/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 12:08:03 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_first_line(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0 || line == NULL)
		return (free_line(&line));
	while (line[i] == ' ' && i < 5)
		i++;
	if (i != 4)
		return (free_line(&line));
	while (line[i] != '\0')
	{
		if ((i - 4) % 10 + '0' != line[i] || i - 4 > board->width)
			return (free_line(&line));
		i++;
	}
	ft_strdel(&line);
	return (1);
}

static int	get_dim_board(t_board *board)
{
	char				*line;
	char				**split;
	static const char 	*tmp = "Plateau";

	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0 || line == NULL)
		return (free_line(&line));
	if (ft_strnequ(line, tmp, 7) == FALSE)
		return (free_line(&line));
	split = ft_strsplit(line + 8, ' ');
	if (split == NULL || split[0] == NULL || split[1] == NULL)
		return (free_line(&line));
	board->height = ft_atoi(split[0]);
	board->width = ft_atoi(split[1]);
	if (board->height == 0 || board->width == 0)
		return (free_line(&line));
	ft_free_tab(split, 2);
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
		tmp = board->tab[i];
		board->tab[i] = ft_strdup(tmp + 4);
		if (board->tab[i] == NULL)
			return (0);
		ft_strdel(&tmp);
		i++;
	}
	return (1);
}

int			get_board(t_board *board)
{
	int i;

	i = 0;
	if (get_dim_board(board) == 0)
		return (0);
	board->tab = (char **)malloc(sizeof(char *) * (size_t)(board->height + 1));
	if (board->tab == NULL || check_first_line(board) == 0)
		return (0);
	while (i < board->height)
	{
		board->tab[i] = NULL;
		if (get_next_line(STDIN_FILENO, &board->tab[i]) <= 0
			|| board->tab[i] == NULL || ft_atoi(board->tab[i]) != i)
		{
			ft_free_tab(board->tab, board->height);
			return (0);
		}
		i++;
	}
	board->tab[i] = NULL;
	return (clean_board(board));
}

int			get_player(void)
{
	char	*line;
	int		id;

	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0 || line == NULL)
		return (free_line(&line));
	if (ft_strnequ(line, "$$$ exec p", 10) == FALSE)
		return (free_line(&line));
	id = ft_atoi(line + 10);
	if (id != 1 && id != 2)
		return (free_line(&line));
	if (ft_strnequ(line + 11, " : [./mybenzar.filler]", 22) == FALSE)
		return (free_line(&line));
	return (id + free_line(&line));
}
