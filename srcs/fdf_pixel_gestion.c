/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:40:03 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/13 17:58:48 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_pxl		*fdf_pxl_prepare_n(t_pxl *pxl, t_map *imap, int i)
{
	if (i == 0)
	{
		pxl->bx2 = (pxl->c1 * ((pxl->ix + 1) - pxl->iy)) * \
				pxl->czoom + pxl->cxcenter;
		pxl->by2 = -((pxl->c2 * (imap->map[pxl->iy][pxl->ix + 1] / 16.0)) \
				- (pxl->c3 * ((pxl->ix + 1) + pxl->iy))) * \
				pxl->czoom + pxl->cycenter;
	}
	else if (i == 1)
	{
		pxl->bx2 = (pxl->c1 * (pxl->ix - (pxl->iy + 1))) * \
				pxl->czoom + pxl->cxcenter;
		pxl->by2 = -((pxl->c2 * (imap->map[pxl->iy + 1][pxl->ix] / 16.0)) - \
				(pxl->c3 * (pxl->ix + (pxl->iy + 1)))) * \
				pxl->czoom + pxl->cycenter;
	}
	return (pxl);
}

static t_pxl		*fdf_pxl_prepare(t_pxl *pxl, t_map *imap, int i)
{
	pxl->czoom = ((pxl->iwidth / imap->x + pxl->iheight / imap->y) / 2.5) + \
			pxl->zoom;
	pxl->cxcenter = ((pxl->iwidth / 2) - ((sqrt(2) / 2) * \
			(imap->x - imap->y)) / 2 * pxl->czoom) + pxl->xdcl;
	pxl->cycenter = ((pxl->iheight / 2) - ((1 / sqrt(6)) * \
			(imap->x + imap->y)) / 2 * pxl->czoom) + pxl->ydcl;
	pxl->c1 = sqrt(2) / 2;
	pxl->c2 = sqrt(2.0 / 3);
	pxl->c3 = 1 / sqrt(6);
	pxl->bx1 = (pxl->c1 * (pxl->ix - pxl->iy)) * pxl->czoom + pxl->cxcenter;
	pxl->by1 = -((pxl->c2 * (imap->map[pxl->iy][pxl->ix] / 16.0)) - \
			(pxl->c3 * (pxl->ix + pxl->iy))) * pxl->czoom + pxl->cycenter;
	pxl = fdf_pxl_prepare_n(pxl, imap, i);
	return (pxl);
}

static t_pxl		*fdf_immersive_3d_n(t_map *imap, t_pxl *pxl, int i)
{
	if (i == 1)
	{
		pxl->bx1 = (pxl->c1 * ((pxl->ix + 1) - pxl->iy)) * \
				pxl->czoom + pxl->cxcenter;
		pxl->by1 = -((pxl->c2 * (imap->map[pxl->iy][pxl->ix + 1] / 16.0)) - \
				(pxl->c3 * ((pxl->ix + 1) + pxl->iy))) * \
				pxl->czoom + pxl->cycenter;
		pxl->bx2 = (pxl->c1 * (pxl->ix - (pxl->iy + 1))) * \
				pxl->czoom + pxl->cxcenter;
		pxl->by2 = -((pxl->c2 * (imap->map[pxl->iy + 1][pxl->ix] / 16.0)) - \
				(pxl->c3 * (pxl->ix + (pxl->iy + 1)))) * \
				pxl->czoom + pxl->cycenter;
	}
	if (i == 2)
	{
		pxl->bx1 = (pxl->c1 * (pxl->ix - pxl->iy)) * pxl->czoom + pxl->cxcenter;
		pxl->by1 = -((pxl->c2 * (imap->map[pxl->iy][pxl->ix] / 16.0)) - \
				(pxl->c3 * (pxl->ix + pxl->iy))) * pxl->czoom + pxl->cycenter;
		pxl->bx2 = (pxl->c1 * ((pxl->ix + 1) - (pxl->iy + 1))) * \
				pxl->czoom + pxl->cxcenter;
		pxl->by2 = -((pxl->c2 * (imap->map[pxl->iy + 1][pxl->ix + 1] / 16.0)) -\
				(pxl->c3 * ((pxl->ix + 1) + (pxl->iy + 1)))) * \
				pxl->czoom + pxl->cycenter;
	}
	return (pxl);
}

static char			*fdf_immersive_3d(t_map *imap, t_pxl *pxl)
{
	if ((imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy][pxl->ix + 1] && \
		imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy + 1][pxl->ix] && \
		imap->map[pxl->iy + 1][pxl->ix + 1] != imap->map[pxl->iy][pxl->ix]) || \
		(imap->map[pxl->iy][pxl->ix + 1] == imap->map[pxl->iy + 1][pxl->ix + 1]\
		&& imap->map[pxl->iy][pxl->ix + 1] == imap->map[pxl->iy + 1][pxl->ix] \
		&& imap->map[pxl->iy][pxl->ix + 1] != imap->map[pxl->iy][pxl->ix]))
		pxl = fdf_immersive_3d_n(imap, pxl, 1);
	if ((imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy + 1][pxl->ix] && \
		imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy + 1][pxl->ix + 1] && \
		imap->map[pxl->iy][pxl->ix + 1] != imap->map[pxl->iy][pxl->ix]) || \
		(imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy][pxl->ix + 1] && \
		imap->map[pxl->iy][pxl->ix] == imap->map[pxl->iy + 1][pxl->ix + 1] && \
		imap->map[pxl->iy + 1][pxl->ix] != imap->map[pxl->iy][pxl->ix]))
		pxl = fdf_immersive_3d_n(imap, pxl, 2);
	pxl->data = fdf_bress(pxl, imap);
	return (pxl->data);
}

char				*fdf_image_pxl(t_pxl *pxl, t_map *imap)
{
	if (pxl->ix + 1 <= imap->x - 1)
	{
		pxl = fdf_pxl_prepare(pxl, imap, 0);
		pxl->data = fdf_bress(pxl, imap);
	}
	if (pxl->iy + 1 <= imap->y - 1)
	{
		pxl = fdf_pxl_prepare(pxl, imap, 1);
		pxl->data = fdf_bress(pxl, imap);
	}
	if (pxl->iy + 1 <= imap->y - 1 && pxl->ix + 1 <= imap->x - 1)
		pxl->data = fdf_immersive_3d(imap, pxl);
	return (pxl->data);
}
