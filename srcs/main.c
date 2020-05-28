#include <stdio.h>
#include "ui.h"
#include "libft.h"

int	main(void)
{
	t_winui	*win;

	ft_putchar('a');
	win = ui_new_win("title", (t_rect){0, 0, 10, 10}, SDL_WINDOW_SHOWN, SDL_RENDERER_SOFTWARE);

	printf("win = %p\n", win);
	printf("SCOP\n");
	return (0);
}
