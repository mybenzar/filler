/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:14:10 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/03 15:49:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_dim(t_piece *piece)
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
			|| !(piece->height = ft_atoi(split[1]))
			|| !(piece->width = ft_atoi(split[2])))
		return (0);
	if (piece->height == 0 || piece->width == 0 || ft_isdigit(piece->height)
			|| ft_isdigit(piece->width))
		return (0);
	ft_strdel(&tmp);
	ft_strdel(&line);
	ft_strdel(&split[0]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_strdel(split);
	return (1);
}

static int get_tab(t_piece *piece)
{
	int		i;

	i = 0;
	if (get_dim(piece) == 0)
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
			return (0);
		}
		i++;
	}
	piece->tab[i] = NULL;
	piece->parse = E_ANALYZE;
	return (1);
}

static int check_piece_elem(char c)
{
	if (c != 'X' && c != 'O' && c != 'x'
			&& c != 'o' && c != '.')
	{
		ft_printf("error in check piece\n");
		return (0);
	}
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
			else if (piece->tab[i][j] != '\0' && check_piece_elem(piece->tab[i][j]) == 0)
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

int	ft_left(t_piece *piece)
{
	int		y;
	int		x;

	y = 0;
	while (y < piece->height)
	{
		x = 0;
		while (piece->tab[y][x] != '\0')
		{
			if (piece->tab[y][x] == '*')
			{
				piece->tab[y - piece->min.y][x - piece->min.x] = '*';
				piece->tab[y][x] = '.';
			}
			x++;
		}
		y++;
	}
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

static int		get_pos(t_piece *piece)
{
	int i;
	int j;
	int p;

	i = 0;
	p = 0;
	if (!(piece->pos = (t_posi*)malloc(sizeof(t_posi) * (size_t)piece->size)))
		return (0);
	while (piece->tab[i] != NULL)
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
		i++;
	}
	piece->parse = E_GET_MIN;
	return (1);
}

int		get_min(t_piece *piece)
{
	int p;

	p = 0;
	piece->min.x = -1;
	piece->min.y = -1;
	while (p < piece->size)
	{
		if (piece->pos[p].x < piece->min.x || piece->min.x == -1)
			piece->min.x = piece->pos[p].x;
		if (piece->pos[p].y < piece->min.y || piece->min.y == -1)
			piece->min.y = piece->pos[p].y;
		p++;
	}
	piece->parse = E_CHECK;
	return (1);
}

static char		**tabcpy(char **tab)
{
	int		i;
	char	**ret;

	i = 0;
	while (tab[i] != NULL)
		i++;
	if (!(ret = (char **)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (tab[++i] != NULL)
	{
		if (!(ret[i] = ft_strdup(tab[i])))
			return (NULL);
	}
	ret[i] = NULL;
	return (ret);
}

static int		check(t_piece *piece)
{
	int x;
	int y;
	int nb;
	char **tab;

	x = piece->pos[0].x;
	y = piece->pos[0].y;
	if (!(tab = tabcpy(piece->tab)))
		return (0);
	nb = nb_adj_piece(tab, x, y);
	y = 0;
	while (tab[y] != NULL)
		ft_strdel(&tab[y++]);
	ft_strdel(tab);
	if (nb != piece->size)
		return (0);
	return (2);
}

void	init_piece(t_piece *piece)
{
	piece->width = 0;
	piece->height = 0;
	piece->size = 0;
}

t_piece	*get_piece()
{
	t_piece *piece;
	static t_parse_piece	trigger_parsing[] = {get_tab, analyze, get_pos, get_min, check};
	int		i;

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
