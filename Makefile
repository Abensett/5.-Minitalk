all :
	make -C libft
	gcc -Wall -Wextra -Werror -I libft src/ft_client.c libft/libft.a -o client
	gcc -Wall -Wextra -Werror -I libft src/ft_server.c libft/libft.a -o server

bonus :
	make -C libft
	gcc -Wall -Wextra -Werror -I libft src/ft_client_bonus.c libft/libft.a -o client_bonus
	gcc -Wall -Wextra -Werror -I libft src/ft_server_bonus.c libft/libft.a -o server_bonus

clean :
	make clean -C libft 
	rm -rf src/client.o src/server.o src/ft_client_bonus.o  src/ft_server_bonus.o

fclean : clean
	make fclean -C libft
	rm -rf client server client_bonus server_bonus

re : fclean all

.PHONY: all libft clean fclean re
