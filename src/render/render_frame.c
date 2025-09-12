/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 15:46:01 by eazard           ###   ########.fr       */
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

void	render_frame(t_data *data)
{
	//effacer
	draw_clear(data, SKY_BLUE, DARK_GRAY);
	//peindre le fond
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