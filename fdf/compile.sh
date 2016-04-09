#!/bin/sh

# osx
# gcc -Wall -Werror -Wextra -I./libft main.c draw.c draw_3dgrid.c -L./lib -lmlx -L./libft -lft -framework OpenGL -framework AppKit
# linux
# gcc -Wall -Werror -Wextra -o fdf -D LINUX -D BONUS -I./libft src/main.c src/draw.c src/draw_3dgrid.c -L./lib -lmlx_linux_x86 -lXext -lX11 -lm -lbsd -L./libft -lft
gcc -Wall -Werror -Wextra -o fdf -D LINUX -D BONUS -I./libft src/main.c src/draw.c src/draw_3dgrid.c -L./lib -lmlx_linux_x64 -lXext -lX11 -lm -lbsd -L./libft -lft
