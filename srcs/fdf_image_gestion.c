/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:39:45 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 17:12:14 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			*fdf_create_image(void *mlx_ptr, t_map *imap)
{
	void		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*data;
	t_pixel		*pixel;

	if ((pixel = (t_pixel *)malloc(sizeof(t_pixel))) == NULL)
		fdf_other_errors();
	pixel->ix = -1;
	pixel->iy = -1;
	if ((img = mlx_new_image(mlx_ptr, 1000, 500)) == NULL)
		fdf_other_errors();
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	while (pixel->iy++ < (imap->y - 1))
	{
		while (pixel->ix++ < (imap->x - 1))
		{
			pixel = fdf_set_color(pixel, 1);
			fdf_depths_colors(pixel, imap->map[pixel->iy][pixel->ix]);
			data = fdf_image_pixel(pixel, data, size_line, \
					imap);
		}
		pixel->ix = -1;
	}
	return (img);
}
