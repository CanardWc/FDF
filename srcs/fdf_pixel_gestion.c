/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:40:03 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 20:28:02 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"

static t_pixel		*fdf_pixel_prepare(t_pixel *pixel, t_map *imap, \
										int size, int i)
{
	if (pixel->ix == 0)
		pixel->iso = (40 * pixel->iy);
	pixel->Bx1 = pixel->ix * 40 + pixel->iso;
	pixel->By1 = pixel->iy * 40 * size - imap->map[pixel->iy][pixel->ix];
	if (i == 0)
	{
		pixel->Bx2 = (pixel->ix + 1) * 40 + pixel->iso;
		pixel->By2 = pixel->iy * 40 * size \
					 - imap->map[pixel->iy][pixel->ix + 1];
	}
	else if (i == 1)
	{
		pixel->Bx2 = pixel->ix * 40 + pixel->iso;
		pixel->By2 = (pixel->iy + 1) * 40 * size \
					 - imap->map[pixel->iy + 1][pixel->ix];
	}
	/* calc = (pixel->ix * 40 * 4) + (pixel->iy * 40 * size - \
	   imap->map[pixel->iy][pixel->ix]) + pixel->iso; */
	return (pixel);
}

static char			*fdf_bresenhamX(t_pixel *pixel, char *data)
{
	int				calc;
	int				e;
	int				dx;
	int				dy;

	e = pixel->Bx2 - pixel->Bx1;
	dx = e * 2;
	dy = (pixel->By2 - pixel->By1) * 2;
	while (pixel->Bx1 <= pixel->Bx2)
	{
		calc = pixel->Bx1 * 4 + pixel->By1;
		data[calc] = pixel->R;
		data[calc + 1] = pixel->G;
		data[calc + 2] = pixel->B;
		pixel->Bx1++;
		e -= dy;
		if (e <= 0)
		{
			pixel->By1++;
			e += dx;
		}
	}
	return (data);
}

static char			*fdf_bresenhamY(t_pixel *pixel, char *data)
{
	int				calc;
	int				e;
	int				dx;
	int				dy;

	e = pixel->By2 - pixel->By1;
	dy = e * 2;
	dx = (pixel->Bx2 - pixel->Bx1) * 2;
	while (pixel->By1 <= pixel->By2)
	{
		calc = pixel->Bx1 * 4 + pixel->By1;
		data[calc] = pixel->R;
		data[calc + 1] = pixel->G;
		data[calc + 2] = pixel->B;
		pixel->By1++;
		e -= dx;
		if (e <= 0)
		{
			pixel->Bx1++;
			e += dy;
		}
	}
	return (data);
}

char				*fdf_image_pixel(t_pixel *pixel, char *data, int size, \
		t_map *imap)
{
	int				calc;

	if (pixel->ix + 1 <= imap->x - 1)
	{
		pixel = fdf_pixel_prepare(pixel, imap, size, 0);
		if (imap->map[pixel->iy][pixel->ix] == \
				imap->map[pixel->iy][pixel->ix + 1])
			while (pixel->Bx1 <= pixel->Bx2)
			{
				calc = pixel->Bx1 * 4 + pixel->By1;
				data[calc] = pixel->R;
				data[calc + 1] = pixel->G;
				data[calc + 2] = pixel->B;
				pixel->Bx1++;
			}
		else
			data = fdf_bresenhamX(pixel, data);
	}
	if (pixel->iy + 1 <= imap->y - 1)
	{
		pixel = fdf_pixel_prepare(pixel, imap, size, 1);
		data = fdf_bresenhamY(pixel, data);
	}
	return (data);
}
