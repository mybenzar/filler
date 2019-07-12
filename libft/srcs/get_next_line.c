/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:15:48 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/12 12:23:48 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strncat_and_free(char *s1, char *s2, int nb)
{
	char *str;
	char *tmp;

	tmp = s1;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + nb)))
		return (NULL);
	ft_strcat(str, s1);
	ft_strncat(str, s2, nb);
	ft_strdel(&tmp);
	return (str);
}

static char		*ft_strdup_and_free(char *str, int nb)
{
	char *tmp;

	tmp = str;
	if (!(str = ft_strdup(str + nb)))
		return (NULL);
	ft_strdel(&tmp);
	return (str);
}

static int		free_error(char **line, char **tmp)
{
	if (line != NULL)
		ft_strdel(line);
	if (tmp != NULL)
		ft_strdel(tmp);
	return (-1);
}

int				get_next_line(char **line)
{
	char			*buf;
	char			*tmp;
	int				nb;

	if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	if (!line || read(STDIN_FILENO, buf, 0) < 0 || BUFF_SIZE < 0)
		return (free_error(&buf, &tmp));
	if (!(tmp = ft_strdup("\0")))
		return (free_error(&buf, &tmp));
	while (!(ft_strchr(tmp, '\n')) && (nb = read(STDIN_FILENO, buf, BUFF_SIZE)))
		tmp = ft_strncat_and_free(tmp, buf, nb);
	if (tmp == NULL)
		return (free_error(&buf, &tmp));
	nb = 0;
	while (tmp[nb] && tmp[nb] != '\n')
		nb++;
	if (!(*line = ft_strnew(nb)))
		return (free_error(&buf, &tmp));
	ft_strncat(*line, tmp, nb);
	if (tmp[nb] == '\n')
		nb++;
	tmp = ft_strdup_and_free(tmp, nb);
	if (!nb)
		return (free_line(&buf));
	ft_strdel(&buf);
	return (1);
}
