/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 23:00:08 by abensett          #+#    #+#             */
/*   Updated: 2021/12/19 13:30:12 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

static void	ft_receive(int signum, siginfo_t *siginfo, void *context)
{
	static pid_t	c_pid = 0;
	static char		char_toprint = 0;
	static int		i = 0;	

	if (!c_pid)
		c_pid = siginfo->si_pid;
	if (signum == SIGUSR2)
		char_toprint |= 1;
	if (++i == 8)
	{
		i = 0;
		if (!char_toprint)
		{
			kill(c_pid, SIGUSR2);
			c_pid = 0;
			return ;
		}
		write(1, &char_toprint, 1);
		char_toprint = 0;
		kill(c_pid, SIGUSR1);
	}
	else
		char_toprint <<= 1;
	(void)context;
}
/*sigaction change action of signum 
sa_flags as SA_SIGINFO to get the client (bonus)*/

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("SERVER PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	s_sigaction.sa_sigaction = ft_receive;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
