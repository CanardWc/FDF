/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_pxl_to_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 01:26:55 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 11:02:54 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char	*put_pxl_to_img(t_pxl *pxl, t_map *imap, int i)
{
	int		calc;

	pxl = fdf_depths_colors(pxl, imap->map[pxl->iy][pxl->ix]);
	calc = (pxl->bx1 * 4) + (pxl->by1 * pxl->size);
	if (0 <= calc && calc < (pxl->iheight * pxl->size) && \
			pxl->bx1 < pxl->iwidth && 0 <= pxl->bx1 && 0 <= pxl->by1 && \
			pxl->by1 < pxl->iheight)
	{
		pxl->data[calc] = pxl->r;
		pxl->data[calc + 1] = pxl->g;
		pxl->data[calc + 2] = pxl->b;
	}
	if (i == 1)
		pxl->bx1 += 1;
	if (i == 2)
		pxl->bx1 -= 1;
	if (i == 3)
		pxl->by1 += 1;
	if (i == 4)
		pxl->by1 -= 1;
	return (pxl->data);
}

static char	*bres_first(t_pxl *pxl, t_map *imap, int oct)
{
	pxl->e = pxl->dx;
	pxl->dx = pxl->dx * 2;
	pxl->dy = pxl->dy * 2;
	while (pxl->bx1 != pxl->bx2)
	{
		pxl->data = put_pxl_to_img(pxl, imap, 0);
		if (oct == 1)
			if ((pxl->e -= pxl->dy) < 0)
				pxl->by1 += 1 - ((pxl->e + pxl->dx) - (pxl->e += pxl->dx));
		if (oct == 3)
			if ((pxl->e += pxl->dy) < 0)
				pxl->by1 -= 1 - ((pxl->e + pxl->dx) - (pxl->e += pxl->dx));
		if (oct == 5)
			if ((pxl->e += pxl->dy) >= 0)
				pxl->by1 += 1 - ((pxl->e + pxl->dx) - (pxl->e += pxl->dx));
		if (oct == 7)
			if ((pxl->e -= pxl->dy) >= 0)
				pxl->by1 -= 1 - ((pxl->e + pxl->dx) - (pxl->e += pxl->dx));
		if (oct == 1 || oct == 3)
			pxl->bx1 += 1;
		else
			pxl->bx1 -= 1;
	}
	return (pxl->data);
}

static char	*bres_second(t_pxl *pxl, t_map *imap, int oct)
{
	pxl->e = pxl->dy;
	pxl->dy = pxl->dy * 2;
	pxl->dx = pxl->dx * 2;
	while (pxl->by1 != pxl->by2)
	{
		pxl->data = put_pxl_to_img(pxl, imap, 0);
		if (oct == 2)
			if ((pxl->e -= pxl->dx) < 0)
				pxl->bx1 += 1 - ((pxl->e + pxl->dy) - (pxl->e += pxl->dy));
		if (oct == 4)
			if ((pxl->e += pxl->dx) > 0)
				pxl->bx1 += 1 - ((pxl->e + pxl->dy) - (pxl->e += pxl->dy));
		if (oct == 6)
			if ((pxl->e += pxl->dx) <= 0)
				pxl->bx1 -= 1 - ((pxl->e + pxl->dy) - (pxl->e += pxl->dy));
		if (oct == 8)
			if ((pxl->e -= pxl->dx) >= 0)
				pxl->bx1 -= 1 - ((pxl->e + pxl->dy) - (pxl->e += pxl->dy));
		if (oct == 2 || oct == 6)
			pxl->by1 += 1;
		else
			pxl->by1 -= 1;
	}
	return (pxl->data);
}

static char	*bres_conditions(t_pxl *pxl, t_map *imap, int i)
{
	if (i == 1)
	{
		if (pxl->dy > 0)
			pxl->dx >= pxl->dy ? (pxl->data = bres_first(pxl, imap, 1)) :\
					(pxl->data = bres_second(pxl, imap, 2));
		else
			pxl->dx >= ((-1) * pxl->dy) ? (pxl->data = bres_first(pxl, \
						imap, 3)) : (pxl->data = bres_second(pxl, imap, 4));
	}
	if (i == 2)
		while (pxl->bx1 != pxl->bx2)
			pxl->data = put_pxl_to_img(pxl, imap, 1);
	if (i == 3)
	{
		if (pxl->dy > 0)
			((-1) * pxl->dx) >= pxl->dy ? pxl->data = bres_first(pxl, imap, 5) \
					: (pxl->data = bres_second(pxl, imap, 6));
		else
			pxl->dx <= pxl->dy ? (pxl->data = bres_first(pxl, imap, 7)) : \
					(pxl->data = bres_second(pxl, imap, 8));
	}
	if (i == 4)
		while (pxl->bx1 != pxl->bx2)
			pxl->data = put_pxl_to_img(pxl, imap, 2);
	return (pxl->data);
}

char		*fdf_bress(t_pxl *pxl, t_map *imap)
{
	if ((pxl->dx = pxl->bx2 - pxl->bx1) != 0)
	{
		if (pxl->dx > 0)
			(pxl->dy = pxl->by2 - pxl->by1) != 0 ? \
					(pxl->data = bres_conditions(pxl, imap, 1)) : \
					(pxl->data = bres_conditions(pxl, imap, 2));
		else
			(pxl->dy = pxl->by2 - pxl->by1) != 0 ? \
					(pxl->data = bres_conditions(pxl, imap, 3)) : \
					(pxl->data = bres_conditions(pxl, imap, 4));
	}
	else if ((pxl->dy = pxl->by2 - pxl->by1) != 0)
	{
		if (pxl->dy > 0)
			while (pxl->by1 != pxl->by2)
				pxl->data = put_pxl_to_img(pxl, imap, 3);
		else
			while (pxl->by1 != pxl->by2)
				pxl->data = put_pxl_to_img(pxl, imap, 4);
	}
	return (pxl->data);
}
