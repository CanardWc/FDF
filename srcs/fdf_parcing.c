/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 13:53:01 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/13 17:30:50 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		*fdf_set_line(t_map *imap, int j)
{
	int			i;

	i = 0;
	if ((imap->map[j] = (int *)ft_memalloc(imap->x)) == NULL)
		return (NULL);
	while (i < imap->x)
	{
		imap->map[j][i] = 0;
		i++;
	}
	return (imap->map[j]);
}

static t_map	*fdf_count_create(int fd, ssize_t j, t_map *imap, int ret)
{
	char		**tmp;
	char		*line;

	imap->x = 0;
	imap->y = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && ++imap->y)
	{
		tmp = ft_strsplit(line, 32);
		while (tmp[j])
			j++;
		if (j > imap->x)
			imap->x = j;
		j = 0;
		free(tmp);
	}
	if (ret == -1)
		fdf_map_error();
	if ((imap->map = (int **)ft_memalloc(sizeof(int *) * imap->y)) == NULL)
		return (NULL);
	while (j < imap->y)
	{
		imap->map[j] = fdf_set_line(imap, j);
		j++;
	}
	return (imap);
}

static int		**fdf_transform(int fd, int **array, int ret)
{
	char		*line;
	char		**tmp;
	ssize_t		j;
	ssize_t		i;

	j = 0;
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
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
	if (ret == -1)
		fdf_map_error();
	return (array);
}

t_map			*fdf_parcing(char *argv)
{
	t_map		*imap;
	int			fd;
	int			ret;
	ssize_t		j;

	j = 0;
	ret = 0;
	if ((imap = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (NULL);
	if ((fd = open(argv, O_RDONLY)) == -1)
		fdf_other_errors();
	imap = fdf_count_create(fd, j, imap, ret);
	close(fd);
	if ((fd = open(argv, O_RDONLY)) == -1)
		fdf_other_errors();
	imap->map = fdf_transform(fd, imap->map, ret);
	close(fd);
	return (imap);
}
