/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:00:12 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/14 13:59:47 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	check_first_line(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
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

	line = NULL;
	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' ')))
		return ;
	ft_printf("for board split 1 = %s\n split 2 = %s\n", split[1], split[2]);
	if (ft_strcmp(split[0], "Plateau") != 0
		|| !(board->height = ft_atoi(split[1]))
		|| !(board->width = ft_atoi(split[2])))
		return ;
}

void	clean_board(t_board *board)
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

	i = 0;
//	if (!(board = (t_board *)malloc(sizeof(t_board))))
//		return ;
	get_dim(board);
	if (!(board->tab = (char **)malloc(sizeof(char *) * board->height + 1)))
		return (0);
	ft_printf("board->height = %d, board->width = %d\n", board->height, board->width);
	check_first_line(board);
	ft_printf("get_line v\n");
	while (i < board->height)
	{
		if (get_next_line(FD, &board->tab[i]) < 0
			|| ft_atoi(board->tab[i]) != i)
		{
	//	ft_printf("atoi of board tab[%d] = %d\n", i, ft_atoi(board->tab[i]));
	//	ft_printf("board->tab[%d] = %s\n", i, board->tab[i]);
			ft_strdel(&board->tab[i]);
			free_board(board);
			return (0);
		}
	//	ft_printf("atoi of board tab[%d] = %d\n", i, ft_atoi(board->tab[i]));
	//	ft_printf("board->tab[%d] = %s\n", i, board->tab[i]);
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

	if (get_next_line(FD, &line) < 0)
		return (-1);
	if (ft_strncmp(line, "$$$ exec p", 10) != 0
		|| (!(id = ft_atoi(line + 10))))
		return (-1);
	if (id != 1 && id != 2)
		return (-1);
	if (ft_strncmp(line + 11, " : [mybenzar]", 13) != 0)
		return (-1);
	ft_strdel(&line);
	return (id);
}
