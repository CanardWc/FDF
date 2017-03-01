/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 21:15:03 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/01 17:11:27 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include <mlx.h>

typedef struct		s_map
{
	int				**map;
	ssize_t			x;
	ssize_t			y;
}					t_map;

typedef struct		s_pixel
{
	int				R;
	int				G;
	int				B;

	int				ix;
	int				iy;
	int				iso;
	int				Bx1;
	int				Bx2;
	int				By1;
	int				By2;
	int				Be;
	int				Bdx;
	int				Bdy;
}					t_pixel;

t_map		*fdf_parcing(char *argv);
void		*fdf_create_image(void *mlx_ptr, t_map *smap);
t_pixel		*fdf_depths_colors(t_pixel *pixel, int depths);
t_pixel		*fdf_set_color(t_pixel *pixel, int set_base);
char		*fdf_image_pixel(t_pixel *pixel, char *data, int size, t_map *imap);
void		fdf_usage(int argc);
void		fdf_other_errors();

#endif
