/*
** connection.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Jun  2 01:52:32 2016 Avel Docquin
** Last update Sun Jun  5 14:37:24 2016 Avel Docquin
*/

#ifndef _CONNECTION_H_
# define _CONNECTION_H_

#include "infos.h"
#include "socket.h"
#include "control.h"

#define USER "USER nobody unknown unknown :noname\r\n"

int	online(t_infos* const infos, char* const buf,
	       const fd_set* const fd_read, const fd_set* const fd_write);
int	connection(t_infos* const infos,
		   const fd_set* const fd_write);

#endif /* !_CONNECTION_H_ */
