/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel_color_gestion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:49:28 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 17:50:10 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pixel				*fdf_set_color(t_pixel *pixel, int set_base)
{
	if (set_base == 1)
	{
		pixel->R = 200;
		pixel->G = 100;
		pixel->B = 100;
	}
	if (set_base == 2)
	{
		pixel->R = 100;
		pixel->G = 200;
		pixel->B = 100;
	}
	if (set_base == 3)
	{
		pixel->R = 100;
		pixel->G = 100;
		pixel->B = 200;
	}
	return (pixel);
}

t_pixel			*fdf_depths_colors(t_pixel *pixel, int depths)
{
	if (pixel->R == 200)
	{
		pixel->G += depths;
		pixel->B += depths;
	}
	if (pixel->G == 200)
	{
		pixel->R += depths;
		pixel->B += depths;
	}
	if (pixel->B == 200)
	{
		pixel->R += depths;
		pixel->G += depths;
	}
	return (pixel);
}
