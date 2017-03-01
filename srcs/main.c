/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:07:34 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 16:13:12 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*imap;

	fdf_usage(argc);
	imap = fdf_parcing(argv[1]);
	if ((mlx = mlx_init()) == NULL)
		fdf_other_errors();
	if ((win = mlx_new_window(mlx, 2000, 1000, "FDF")) == NULL)
		fdf_other_errors();
	img = fdf_create_image(mlx, imap);
	mlx_put_image_to_window(mlx, win, img, 500, 250);
	mlx_loop(mlx);
	return (0);
}
