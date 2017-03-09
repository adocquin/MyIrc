/*
** orders3.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 05:15:24 2016 Avel Docquin
** Last update Sun Jun  5 09:06:46 2016 Avel Docquin
*/

#ifndef _ORDERS3_H_
# define _ORDERS3_H_

#include "misc.h"
#include "client.h"
#include "socket.h"
#include "reply.h"
#include "orders.h"

#define ARGS_JOIN " JOIN :Not enough parameters.\r\n"
#define SYNTAX_JOIN " :SYNTAX JOIN <channel>{,<channel>} {<key>{,<key>}}\r\n"
#define ARGS_PART " PART :Not enough parameters.\r\n"
#define SYNTAX_PART " :SYNTAX PART <channel>{,<channel>} [<reason>]\r\n"

int	names(const char** const cmd, const unsigned int fd,
	      t_env* const e, const fd_set* const fd_write);
int	join(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write);
int	part(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write);

#endif /* _ORDERS3_H_ */
