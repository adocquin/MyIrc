/*
** infos.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed Jun  1 00:42:14 2016 Avel Docquin
** Last update Sun Jun  5 20:09:15 2016 Avel Docquin
*/

#ifndef _INFOS_H_
# define _INFOS_H_

#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "parser.h"
#include "misc.h"
#include "socket.h"

#define BUFFER 512
#define USERNAME 9

typedef struct		s_infos
{
  char			username[USERNAME + 1];
  unsigned int		mode;
  int			fd;
  int			port;
  char			*ip;
  struct sockaddr_in	s_in;
  struct protoent	*pe;
}			t_infos;

typedef int(*optr)(const char** const cmd, t_infos* infos,
		   const fd_set* const fd_write, const unsigned int i);

int		priv_msg_send(const char* const cmd, const char** const args,
			      const t_infos* const infos,
			      const fd_set* const fd_write);
int		cmd_send(const char* const cmd, const char* const arg,
			 const t_infos* const infos,
			 const fd_set* const fd_write);
t_infos*	init_infos(t_infos* const infos, char** const cmd);

#endif /* !_INFOS_H_ */
