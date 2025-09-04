/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 15:04:03 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdint.h>
# include "mlx.h"

int main(void)
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp, line_length, endian;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Gradient");

    img = mlx_new_image(mlx, 800, 600);
    addr = mlx_get_data_addr(img, &bpp, &line_length, &endian);

    // Dégradé vertical du noir en haut au blanc en bas
    for (int x = 0; x < 800; x++)
    {
        int color = (255 - x * 255 / 800) << 16   // rouge
                  | (255 - x * 255 / 800) << 8    // vert
                  | (255 - x * 255 / 800);        // bleu
        for (int y = 0; y < 600; y++)
        {
            char *dst = addr + (y * line_length + x * (bpp / 8));
            *(unsigned int*)dst = color;
        }
    }

    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
}