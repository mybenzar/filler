/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:15:48 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/11 10:26:18 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*find_fd(t_list **list, int fd)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = (t_list*)ft_memalloc(sizeof(t_list)))
		|| !(tmp->content = ft_strdup("\0")))
		return (NULL);
	ft_lstadd(list, tmp);
	return (tmp);
}

static char		*ft_strncat_and_free(char *s1, char s2[BUFF_SIZE + 1], int nb)
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

int				get_next_line(char **line)
{
	static t_list	*statictmp;
	char			*buf;
	t_list			*tmp;
	int				nb;

	if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	if (!line || read(STDIN_FILENO, buf, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	tmp = ft_strnew(1);
	if (tmp == NULL)
		return (-1);
	while (!(ft_strchr(tmp, '\n')) && (nb = read(fd, buf, BUFF_SIZE)))
	{
		tmp = ft_strncat_and_free(tmp->content, buf, nb);
	}
	nb = 0;
	while (((char*)tmp->content)[nb] && ((char*)tmp->content)[nb] != '\n')
		nb++;
	if (!(*line = ft_strnew(nb)))
		return (-1);
	ft_strncat(*line, tmp->content, nb);
	if (((char*)tmp->content)[nb] == '\n')
		nb++;
	tmp->content = ft_strdup_and_free(tmp->content, nb);
	if (!nb)
		return (0);
	ft_strdel(&buf);
	return (1);
}
