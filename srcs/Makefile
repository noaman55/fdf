
SRCS = main.c fdf_utils.c fdf_utils2.c parsing.c parsing2.c bresenham.c rotation.c events.c transformations.c colors.c colors2.c

OBJ =  $(SRCS:.c=.o)

B_SRCS = 

B_OBJ = $(B_SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ../libft/Inc

NAME = ../fdf

LIBFT = ../libft/libft.a

all : $(NAME)

bonus : $(B_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I/usr/include -I ../mlx_linux -c $< -o $@
#$(CC) $(CFLAGS) -Imlx_linux -c $< -o $@ 

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT)  -L ../mlx_linux -lmlx_Linux -L/usr/lib -I ../mlx_linux -lXext -lX11 -lm -lz -o $(NAME)
#$(CC) $(LIBFT) $(OBJ) -L../minilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)  -g -fsanitize=address
#$(CC) $(CFLAGS) $^ -o $(NAME)

$(B_NAME) : $(B_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(B_NAME)

clean :
	rm -f $(OBJ)
	rm -f $(B_OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f $(B_NAME)

re : fclean all

.PHONY:  all clean fclean re





