/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel_color_gestion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:49:28 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/13 17:54:53 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pxl			*fdf_set_color(t_pxl *pxl, int set_base)
{
	if (set_base == 1)
	{
		pxl->r = 200;
		pxl->g = 100;
		pxl->b = 100;
	}
	if (set_base == 2)
	{
		pxl->r = 100;
		pxl->g = 200;
		pxl->b = 100;
	}
	if (set_base == 3)
	{
		pxl->r = 100;
		pxl->g = 100;
		pxl->b = 200;
	}
	return (pxl);
}

t_pxl			*fdf_depths_colors(t_pxl *pxl, int depths)
{
	if (pxl->r == 200)
	{
		pxl->g += depths;
		pxl->b += depths;
	}
	if (pxl->g == 200)
	{
		pxl->r += depths;
		pxl->b += depths;
	}
	if (pxl->b == 200)
	{
		pxl->r += depths;
		pxl->g += depths;
	}
	return (pxl);
}
