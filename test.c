#include "filler.h"

/*
 * ** Parcourir ma map, retenir la potentielle position de ma pièce.
 * ** Reparcourir ma map pour trouver le x/y ennemi et enregistrer sa position.
 * ** Parcourir ma pièce et trouver tous ses points x/y.
 * ** Pour chaque point dans ma pièce, calculer la distance de ce dernier par
 * ** rapport au x/y ennemi.
 * ** Additionner le tout et comparer le total avec la distance d'une autre
 * ** potentielle position de la pièce puis bah... tu poses hein.
 * */

static int		get_distance(t_game *game, int y, int x)
{
	int		distance;

	distance = ft_abs(game->enemy_y - y) + ft_abs(game->enemy_x - x);
	return (distance);
}

static int		check_sup(t_game *game, int yboard, int xboard)
{
	int		ypiece;
	int		xpiece;
	int		count;

	ypiece = 0;
	count = 0;
	while (ypiece < game->y_piece)
	{
		xpiece = 0;
		while (game->piece[ypiece][xpiece] != '\0')
		{
			if (game->piece[ypiece][xpiece] == '*' &&
					game->board[yboard + ypiece][xboard + xpiece] == game->me)
				count++;
			if (game->piece[ypiece][xpiece] == '*' &&
					game->board[yboard + ypiece][xboard + xpiece] == game->enemy)
				return (0);
			xpiece++;
		}
		ypiece++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int				who_is_my_enemy(t_game *game, int yboard, int xboard)
{
	int		ok;

	if (game->player == '1')
	{
		game->me = 'O';
		game->enemy = 'X';
	}
	if (game->player == '2')
	{
		game->me = 'X';
		game->enemy = 'O';
	}
	ok = check_sup(game, yboard, xboard);
	return (ok);
}

static void		strategy(t_game *game)
{
	int		count;
	int		ypiece;
	int		xpiece;

	ypiece = 0;
	count = 0;
	while (ypiece < game->y_piece)
	{
		xpiece = 0;
		while (game->piece[ypiece][xpiece] != '\0')
		{
			if (game->piece[ypiece][xpiece] == '*')
				count = count + get_distance(game, game->ybefore +
						ypiece, game->xbefore + xpiece);
			xpiece++;
		}
		ypiece++;
	}
	if (count < game->distance || game->distance == -1)
		game->distance = count;
}

void			find_the_enemy(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->distance = -1;
	while (i < game->y_board)
	{
		j = 0;
		while (game->board[i][j] != '\0')
		{
			if (game->board[i][j] == game->enemy)
			{
				game->enemy_y = i;
				game->enemy_x = j;
				strategy(game);
			}
			j++;
		}
		i++;
	}
}
