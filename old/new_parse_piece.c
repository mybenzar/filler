/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_piece.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:42:16 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/27 15:41:23 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_size(t_game *g)
{
	char *line;
	char **split;
	char *tmp;

	line = NULL;
	split = NULL;
	if (!(tmp = ft_strdup("Piece")))
		return (0);
	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' ')))
		return (0);
	if (ft_strcmp(split[0], "Piece") != 0
		|| !(g->piece->height = ft_atoi(split[1]))
		|| !(g->piece->width = ft_atoi(split[2])))
		return (0);
	if (g->piece->height == 0 || g->piece->width == 0 || ft_isdigit(g->piece->height)
		|| ft_isdigit(g->piece->width))
		return (0);
	ft_strdel(&tmp);
	ft_strdel(&line);
	ft_strdel(&split[0]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_strdel(split);
	g->parse = E_GET_TAB;
	return (1);
}

static int	get_tab(t_game *game)
{
	int		i;
	char	**tab;

	i = 0;
	if (get_dim_piece(piece) == 0)
		return (0);
	if (!(piece->tab = (char **)malloc(sizeof(char *) * (size_t)(piece->height + 1))))
		return (0);
	while (i < piece->height)
	{
		piece->tab[i] = NULL;
		if (get_next_line(FD, &piece->tab[i]) < 0
			|| (int)ft_strlen(piece->tab[i]) != piece->width)
		{
			ft_strdel(&piece->tab[i]);
			ft_strdel(piece->tab);
			ft_printf("error in get tab piece\n");
			return (0);
		}
		i++;
	}
	piece->tab[i] = NULL;
	g->parse = E_ANALYZE;
	return (1);
}

static int		analyze(t_game *g)
{
	int i;
	int j;

	i = 0;
	while (g->piece->tab[i] != NULL)
	{
		j = 0;
		while (g->piece->tab[i][j] != '\0')
		{
			if (g->piece->tab[i][j] == '*')
				g->piece->tab[i][j] = E_FULL;
			g->piece->tab[i][j] = E_EMPTY;
			j++;
		}
		i++;
	}
	g->parse = E_CHECK;
	return (1);
}

static int		nb_adj_piece(char **tab, int x, int y)
{
	int count;
	
	if (x >= 0 && y >= 0 && tab[y] != NULL && tab[y][x] != '\0'
		&& tab[y][x] != 'N' && tab[y][x] == '*')
	{
		count = 1;
		tab[y][x] = 'N';
		count += nb_adj_piece(tab, x, y + 1);
		count += nb_adj_piece(tab, x + 1, y);
		count += nb_adj_piece(tab, x + 1, y + 1);
		count += nb_adj_piece(tab, x, y - 1);
		count += nb_adj_piece(tab, x - 1, y);
		count += nb_adj_piece(tab, x - 1, y - 1);
		count += nb_adj_piece(tab, x - 1, y + 1);
		count += nb_adj_piece(tab, x + 1, y - 1);
		return (count);
	}
	return (0);
}

static int		check(t_game *g)
{
	int count;
	int count_adj;

	count = count_char(piece, E_FULL);
	while (piece->tab[i] != NULL)
	{
		j = 0;
		while (g->piece->tab[i][j] != '\0')
		{
			if (g->piece->tab[i][j] == E_FULL)
			{
				count_adj = nb_adj_piece(g->piece->tab, j, i);
				break ;
			}
			j++;
		}
		i++;
	}
	if (count != count_adj)
		return (0);
	return (E_END);
}

int	get_piece(t_board *piece)
{
	static t_parse	trigger_parsing[] = {get_size, get_tab, analyze, check};

	while (i != E_END)
	{
		i = trigger_parsing[g->parse](piece);
		if (i == 0)
			return (0);
	}
	return (1);
}
