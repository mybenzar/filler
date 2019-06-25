/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:14:10 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/25 12:08:18 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_dim_piece(t_piece *piece)
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

static char	**get_tab_piece(t_piece *piece)
{
	int		i;
	char	**tab;

	i = 0;
	if (get_dim_piece(piece) == 0)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (size_t)(piece->height + 1))))
		return (NULL);
	while (i < piece->height)
	{
		tab[i] = NULL;
		if (get_next_line(FD, &tab[i]) < 0
			|| (int)ft_strlen(tab[i]) != piece->width)
		{
			ft_strdel(&tab[i]);
			ft_strdel(tab);
			ft_printf("error in get tab piece\n");
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	display_piece(piece);
	return (tab);
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

int	get_piece_size(t_piece *piece, char **tab)
{
	int	i;
	int j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == '*')
				piece->size++;
			else if (tab[i][j] != '\0' && check_piece_elem(tab[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (piece->size == 0)
		return (0);
	return (1);
}


int	ft_left(t_piece *piece)
{
	int p;
	int flag;

	p = 0;
	flag = 0;
	while (p < piece->size && piece->pos[p].x > 0)
	{
		flag = 1;
		if (piece->pos[p].x == 0)
		{
			flag = 0;
			return (0);
		}
		p++;
	}
	if (flag == 1)
	{
		p = -1;
		while (++p < piece->size)
			piece->pos[p].x -= 1;
	}
	p = 0;
	flag = 0;
	while (p < piece->size && piece->pos[p].y > 0)
	{
		flag = 1;
		if (piece->pos[p].y == 0)
		{
			flag = 0;
			return (0);
		}
		p++;
	}
	if (flag == 1)
	{
		p = -1;
		while (++p < piece->size)
			piece->pos[p].y -= 1;
	}
	return (1);
}

int		nb_adj_piece(char **tab, int x, int y)
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

static int		get_pos(t_piece *piece, char **tab)
{
	int i;
	int j;
	int p;

	i = 0;
	p = 0;
	if (!(piece->pos = (t_posi*)malloc(sizeof(t_posi) * (size_t)piece->size)))
		return (0);
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == '*')
			{
				piece->pos[p].x = j;
				piece->pos[p].y = i;
				p++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int		check_piece(t_piece *piece, char **tab)
{
	int x;
	int y;
	int nb;

	x = piece->pos[0].x;
	y = piece->pos[0].y;
	nb = nb_adj_piece(tab, x, y);
	y = 0;
	while (tab[y] != NULL)
		ft_strdel(&tab[y++]);
	ft_strdel(tab);
	if (nb != piece->size)
	{
		ft_printf("error in check piece\n");
		return (0);
	}
	return (1);
}

void	init_piece(t_piece *piece)
{
	piece->width = 0;
	piece->height = 0;
	piece->size = 0;
}

t_piece	*get_piece(void)
{
	t_piece *piece;
	char 	**tab;

	if (!(piece = (t_piece*)ft_memalloc(sizeof(t_piece))))
	{
		DD("malloc");
		return (NULL);
	}
	if ((tab = get_tab_piece(piece)) == NULL)
	{
		DD("get_tab_piece");
		free_piece(piece);
		return (NULL);
	}
	if (get_piece_size(piece, tab) == 0)
	{
		DD("get_piece_size");
		free_piece(piece);
		return (NULL);
	}
	if (piece->size == 0 || get_pos(piece, tab) == 0)
	{
		DD("get_pos");
		free_piece(piece);
		return (NULL);
	}
	if (check_piece(piece, tab) == 0)
	{
		DD("check_piece");
		free_piece(piece);
		return (NULL);
	}
	return (piece);
}
