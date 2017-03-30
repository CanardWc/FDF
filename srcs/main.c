/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:07:34 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/14 19:34:19 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			fdf_create_hud(t_pxl *pxl)
{
	int			i;

	i = 0x00FF00;
	mlx_string_put(pxl->mlx, pxl->win, 10, 0, i, "rgth/lft/up/dwn : Moove");
	mlx_string_put(pxl->mlx, pxl->win, 10, 20, i, "H/L : disco club");
	mlx_string_put(pxl->mlx, pxl->win, 10, 40, i, "echap : quit");
	mlx_string_put(pxl->mlx, pxl->win, 10, 60, i, "R : Refresh");
	mlx_string_put(pxl->mlx, pxl->win, 10, 80, i, "+/- : Zoom");
	mlx_string_put(pxl->mlx, pxl->win, 10, 960, i, "Autorepeat is on, enjoy");
}

int				main(int argc, char **argv)
{
	t_map		*imap;
	t_pxl		*pxl;

	fdf_usage(argc);
	imap = fdf_parcing(argv[1]);
	if ((pxl = (t_pxl *)malloc(sizeof(t_pxl))) == NULL)
		fdf_other_errors();
	if ((pxl->mlx = mlx_init()) == NULL)
		fdf_other_errors();
	if ((pxl->win = mlx_new_window(pxl->mlx, 2000, 1000, "FDF")) == NULL)
		fdf_other_errors();
	mlx_do_key_autorepeaton(pxl->mlx);
	if ((pxl->img = fdf_create_image(imap, pxl)) == NULL)
		fdf_other_errors();
	mlx_hook(pxl->win, 2, 1L << 0, fdf_key_capture, pxl);
	mlx_loop(pxl->mlx);
	return (0);
}
