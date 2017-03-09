/*
** orders.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May 25 00:52:27 2016 Avel Docquin
** Last update Sun Jun  5 08:29:01 2016 Avel Docquin
*/

#ifndef _ORDERS_H_
# define _ORDERS_H_

#include "parser.h"
#include "client.h"
#include "orders2.h"
#include "orders3.h"
#include "misc.h"
#include "socket.h"

#define ERR_NICK "432 :Erroneous Nickname\r\n"
#define ERR_ARGS "461 :Not enough parameters\r\n"

typedef int(*optr)();

int	canals_cmp(const char* const s);
int	orders_cmd(t_env* const e, char* const buf,
		   const unsigned int fd, const fd_set* const fd_write);

#endif /* !_ORDERS_H_ */
