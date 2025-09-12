/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 16:48:39 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// static void	test_draw_vline(t_data *data)
// {
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 - 50,            0,                WINDOW_HEIGHT}, RED); // rouge, pleine hauteur
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2,50,               WINDOW_HEIGHT-50}, RED); // vert, centré, marges haut/bas
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 + 20,100,              300},            RED); // bleu, à droite, segment court
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 - 20,          0,                WINDOW_HEIGHT},              RED); // blanc, hauteur nulle (rien visible)
// }

static	t_vec2d get_rayDir(t_data *data, double x)
{
	double	cameraX;

	cameraX = 2.0 * x / (WINDOW_WIDTH - 1) - 1.0;
	return (sum_vec_2d(data->camera.dir,
			multiply_vec_by_scalar_2d(data->camera.plane, cameraX)));
}

static void	dda_algorithm(t_data *data, t_vec2d rayDir)
{
	t_vec2d	map;
	t_vec2d	deltaDist;
	t_vec2d	step;
	t_vec2d	sideDist;

	map.x = floor(data->camera.pos.x);
	map.y = floor(data->camera.pos.y);
}

void	render_frame(t_data *data)
{
	t_vec2d	rayDir;
	double	x;
	
	draw_clear(data, SKY_BLUE, DARK_GRAY);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		
		rayDir = get_rayDir(data, x);
		//DDA
	}	
	// boucle raycasting par colonne, Pour x = 0..WIN_W-1:
		//Construire le rayon
		//Initialiser DDA
		//Avancer DDA jusqu’au mur
		//Calculer perpWallDist + lineHeight
		//Dessiner la bande unicolore
		//(option) zbuf[x] = perpWallDist;
	// Présenter
		// mlx_put_image_to_window(display, win, img, 0, 0);
}