/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:39:45 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/27 08:47:27 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_pxl	*fdf_pxl_setup(t_pxl *pxl)
{
	pxl->ix = 0;
	pxl->iy = 0;
	pxl->iwidth = 2000;
	pxl->iheight = 1000;
	pxl->zoom = 0;
	pxl->xdcl = 0;
	pxl->ydcl = 0;
	pxl->dpth = 1;
	return (pxl);
}

int				fdf_key_capture(int kcd, t_pxl *pxl)
{
	if (kcd == 126)
		pxl->ydcl += 8;
	if (kcd == 125)
		pxl->ydcl -= 8;
	if (kcd == 123)
		pxl->xdcl -= 8;
	if (kcd == 124)
		pxl->xdcl += 8;
	if (kcd == 69)
		pxl->zoom += 1;
	if (kcd == 78)
		pxl->zoom -= 1;
	if (kcd == 4)
		pxl->dpth += 1;
	if (kcd == 37)
		pxl->dpth -= 1;
	if (kcd == 15)
		pxl = fdf_pxl_setup(pxl);
	if (kcd == 123 || kcd == 125 || kcd == 126 || kcd == 124 || kcd == 69 || \
		kcd == 78 || kcd == 4 || kcd == 37 || kcd == 15)
		fdf_kcd_for_img(pxl, pxl->imap);
	if (kcd == 53)
		exit(0);
	return (0);
}

static char		*fdf_piece_setup(t_pxl *pxl, t_map *imap)
{
	while (pxl->iy < imap->y)
	{
		while (pxl->ix < imap->x)
		{
			pxl = fdf_set_color(pxl, pxl->dpth);
			pxl->data = fdf_image_pxl(pxl, imap);
			pxl->ix++;
		}
		pxl->ix = 0;
		pxl->iy++;
	}
	pxl->iy = 0;
	return (pxl->data);
}

void			*fdf_kcd_for_img(t_pxl *pxl, t_map *imap)
{
	int			bits_per_pixel;
	int			endian;

	mlx_destroy_image(pxl->mlx, pxl->img);
	if ((pxl->img = mlx_new_image(pxl->mlx, pxl->iwidth, pxl->iheight)) == NULL)
		fdf_other_errors();
	pxl->data = mlx_get_data_addr(pxl->img, &bits_per_pixel, \
			&pxl->size, &endian);
	pxl->data = fdf_piece_setup(pxl, imap);
	mlx_put_image_to_window(pxl->mlx, pxl->win, pxl->img, 0, 0);
	fdf_create_hud(pxl);
	return (pxl->img);
}

void			*fdf_create_image(t_map *imap, t_pxl *pxl)
{
	int			bits_per_pixel;
	int			endian;

	pxl->imap = imap;
	pxl = fdf_pxl_setup(pxl);
	if ((pxl->img = mlx_new_image(pxl->mlx, pxl->iwidth, pxl->iheight)) == NULL)
		fdf_other_errors();
	pxl->data = mlx_get_data_addr(pxl->img, &bits_per_pixel, &pxl->size, \
			&endian);
	pxl->data = fdf_piece_setup(pxl, imap);
	mlx_put_image_to_window(pxl->mlx, pxl->win, pxl->img, 0, 0);
	fdf_create_hud(pxl);
	return (pxl->img);
}
