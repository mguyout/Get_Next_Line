/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 14:44:34 by mguyout           #+#    #+#             */
/*   Updated: 2017/01/28 14:53:58 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "get_next_line.h"

int	get_line(int fd, char **stock)
{
	char	buf[BUFF_SIZE + 1];
	char	*str;
	int		check;

	check = read(fd, buf, BUFF_SIZE);
	if (check > 0)
	{
		buf[check] = '\0';
		str = ft_strjoin(*stock, buf);
		if (!str)
			return (-1);
		free(*stock);
		*stock = str;
	}
	return (check);
}

int	get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	char		*str;
	int			check;

	if (!stock && (stock = malloc(1)) == NULL)
		return (-1);
	str = ft_strchr(stock, '\n');
	while (str == NULL)
	{
		check = get_line(fd, &stock);
		if (check == 0)
		{
			if (stock == (str = ft_strchr(stock, '\0')))
				return (0);
		}
		else if (check < 0)
			return (-1);
		else
			str = ft_strchr(stock, '\n');
	}
	*line = ft_strsub(stock, 0, str - stock);
	str = ft_strdup(str + 1);
	free(stock);
	stock = str;
	return (1);
}
