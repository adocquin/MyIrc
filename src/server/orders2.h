/*
** orders2.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu May 26 23:12:38 2016 Avel Docquin
** Last update Sun Jun  5 12:48:24 2016 Avel Docquin
*/

#ifndef _ORDERS2_H_
# define _ORDERS2_H_

#include "misc.h"
#include "client.h"
#include "socket.h"
#include "reply2.h"

#define ERR_RECIP "411 No recipent given (PRIVMSG)\r\n"
#define ERR_TEXT "412 No text to send\r\n"
#define ADMIN " #admin :channel admin\r\n"
#define GENERAL1 " #general1 :channel general\r\n"
#define GENERAL2 " #general2 :channel general\r\n"

int	list(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write);
int	privmsg(const char** const cmd, const unsigned int fd,
		t_env* const e, const fd_set* const fd_write);
int	pong(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write);
int	quit(const char** const cmd, const unsigned int fd, t_env* const e);

#endif /* _ORDERS2_H_ */
