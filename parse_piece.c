/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:14:10 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 18:02:22 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_dim_piece(t_piece *piece)
{
	char *line;
	char **split;

	line = NULL;
	if (get_next_line(FD, &line) < 0
		|| !(split = ft_strsplit(line, ' ')))
		return ;
	if (ft_strcmp(split[0], "Piece") != 0
		|| !(piece->height = ft_atoi(split[1]))
		|| !(piece->width = ft_atoi(split[2])))
		return ;
}

char	**get_tab_piece(t_piece *piece)
{
	int		i;
	char	**tab;

	i = 0;
	get_dim_piece(piece);
	if (!(tab = (char **)malloc(sizeof(char *) * piece->height + 1)))
		return (NULL);
	while (i < piece->height)
	{
	//	ft_printf("piece->height = %d", piece->height);
		if (get_next_line(FD, &tab[i]) <= 0
			|| (int)ft_strlen(tab[i]) != piece->width)
		{
		//	ft_printf("i should not be here\n");
			ft_strdel(&tab[i]);
			return (NULL);
		}
		i++;
	}
//	ft_printf("hello\n");
	tab[i] = NULL;
	return (tab);
}

static int check_piece_elem(char c)
{
	if (c != 'X' && c != 'O' && c != 'x'
		&& c != 'o' && c != '.')
		return (0);
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
			else if (check_piece_elem(tab[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


void	ft_left(t_piece *piece)
{
	int p;
	int flag;

	p = 0;
	flag = 0;
//	ft_printf("im in ft_left\n");
	while (piece->pos[p].x > 0 && p < piece->width)
	{
		flag = 1;
		if (piece->pos[p].x == 0)
		{
			flag = 0;
			break ;
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
	while (piece->pos[p].y > 0 && p < piece->height)
	{
		flag = 1;
		if (piece->pos[p].y == 0)
		{
			flag = 0;
			break ;
		}
		p++;
	}
	if (flag == 1)
	{
		p = -1;
		while (++p < piece->size)
			piece->pos[p].y -= 1;
	}
//		ft_printf("new piece->pos[%d].x = %d, new piece->pos[%d].y = %d\n", p, piece->pos[p].x, p, piece->pos[p].y);
}

int		get_pos(t_piece *piece, char **tab)
{
	int i;
	int j;
	int p;

	i = 0;
	p = 0;
	if (!(piece->pos = (t_pos*)malloc(sizeof(t_pos) * piece->size + 1)))
		return (0);
//	ft_printf("here\n");
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

int		check_piece(t_piece *piece, char **tab)
{
	int x;
	int y;
	int nb;

	x = piece->pos[0].x;
	y = piece->pos[1].x;
	nb = nb_adj_piece(tab, x, y);
	y = 0;
	while (tab[y] != NULL)
		ft_strdel(&tab[y++]);
	ft_strdel(tab);
	if (nb != piece->size)
		return (0);
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

	if (!(piece = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	init_piece(piece);
	if ((tab = get_tab_piece(piece)) == NULL
		|| get_piece_size(piece, tab) == 0
		|| (get_pos(piece, tab) == 1 && check_piece(piece, tab) == 0))
	{
		free_piece(piece);
		return (NULL);
	}
	//ft_left(piece);
	display_piece(piece);
	return (piece);
}
