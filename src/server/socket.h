/*
** socket.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Mon May 23 05:18:42 2016 Avel Docquin
** Last update Sun Jun  5 15:16:01 2016 Avel Docquin
*/

#ifndef _SOCKET_H_
# define _SOCKET_H_

#include <arpa/inet.h>
#include <signal.h>
#include "misc.h"

int	msg_send(const char* const cmd, const char* const arg,
		 const unsigned int fd, const fd_set* const fd_write);
int	write_socket(unsigned int fd, char* buf, const fd_set* const fd_write);

#endif /* !_SOCKET_H_ */
