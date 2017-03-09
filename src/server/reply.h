/*
** reply.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 05:58:37 2016 Avel Docquin
** Last update Sun Jun  5 12:53:35 2016 Avel Docquin
*/

#ifndef _REPLY_H_
# define _REPLY_H_

#include "socket.h"
#include "client.h"

#define BAD_JOIN " :No such channel\r\n"
#define NOT_IN_CHANNEL " :You're not on that channel\r\n"
#define END_NAMES " :End of /NAMES list\r\n"

int	rpl_end_of_names(char* canal, const unsigned int fd,
			 const fd_set* const fd_write);
int	rpl_namreply(const unsigned int canal, const unsigned int fd,
		     const fd_set* const fd_write, t_env* const e);
int	rpl_not_in_channel(char* canal, const unsigned int fd,
			   const fd_set* const fd_write);
int	rpl_no_such_channel(char* canal, const unsigned int fd,
			    const fd_set* const fd_write);
int	rpl_topic(char* canal, const char* const sujet,
		  const unsigned int fd, const fd_set* const fd_write);

#endif /* !_REPLY_H_ */
