/*
** reply2.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 11:13:25 2016 Avel Docquin
** Last update Sun Jun  5 12:07:37 2016 Avel Docquin
*/

#ifndef _REPLY2_H_
# define _REPLY2_H_

#include "socket.h"
#include "client.h"

#define UNKNOWN " :Unknown command\r\n"
#define NO_NICK " :No such nick\r\n"

int	rpl_unknown_cmd(char* cmd, const unsigned int fd,
			const fd_set* const fd_write, const t_env* const e);
int	rpl_no_such_nick(char* cmd, const unsigned int fd,
			 const fd_set* const fd_write, t_env* const e);

#endif /* !_REPLY2_H_ */
