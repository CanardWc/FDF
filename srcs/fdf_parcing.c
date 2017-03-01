/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 13:53:01 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 15:05:51 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_map	*fdf_count_create(int fd, ssize_t j, t_map *imap)
{
	char		**tmp;
	char		*line;

	imap->x = 0;
	imap->y = 0;
	while (get_next_line(fd, &line) > 0 && ++imap->y)
	{
		tmp = ft_strsplit(line,32);
		while (tmp[j])
			j++;
		if (j > imap->x)
			imap->x = j;
		j = 0;
	}
	if ((imap->map = (int **)ft_memalloc(sizeof(int *) * imap->y)) == NULL)
		return (NULL);
	while (j < imap->y)
		if ((imap->map[j++] = (int *)ft_memalloc(imap->x)) == NULL)
			return (NULL);
	return (imap);
}

static int		**fdf_transform(int fd, int **array)
{
	char		*line;
	char		**tmp;
	ssize_t		j;
	ssize_t		i;

	j = 0;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strsplit(line, 32);
		while (tmp[j])
		{
			array[i][j] = ft_atoi(tmp[j]);
			j++;
		}
		j = 0;
		i++;
		free(tmp);
	}
	return (array);
}

t_map			*fdf_parcing(char *argv)
{
	t_map		*imap;
	int			fd;
	ssize_t		j;
	ssize_t		i;
	ssize_t		y;

	j = 0;
	i = 0;
	y = 0;
	if ((imap = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (NULL);
	if ((fd = open(argv, O_RDONLY)) == -1)
		fdf_other_errors();
	printf("fd = %d:", fd);
	imap = fdf_count_create(fd, j, imap);
	close(fd);
	if ((fd = open(argv, O_RDONLY)) == -1)
		fdf_other_errors();
	imap->map = fdf_transform(fd, imap->map);
	close(fd);
	return (imap);
}
