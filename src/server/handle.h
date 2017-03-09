/*
** handle.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Fri May 20 06:00:03 2016 Avel Docquin
** Last update Sun Jun  5 20:16:26 2016 Avel Docquin
*/

#ifndef _HANDLE_H_
# define _HANDLE_H_

#include "client.h"
#include "orders.h"

void	init_fd(t_env* const e, int* fd_max,
		fd_set* const fd_read, fd_set* const fd_write);
int	handle_input(t_env* const e, char* buf, const fd_set* const fd_write,
		     const unsigned int fd);
int	handle_chat(t_env* const e, char buf[BUFFER],
		    const fd_set* const fd_read,
		    const fd_set* const fd_write);

#endif /* !_HANDLE_H_ */
