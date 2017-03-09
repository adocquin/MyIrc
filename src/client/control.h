/*
** control.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Tue May 24 18:48:10 2016 Avel Docquin
** Last update Sun Jun  5 12:37:15 2016 Avel Docquin
*/

#ifndef _CONTROL_H_
# define _CONTROL_H_

#include "infos.h"
#include "socket.h"
#include "commands.h"
#include "init_func_tab.h"

#define ERROR "ERROR"
#define NICK_USAGE "Usage: /nick _nickname[1-9]_\n\r"
#define SERVER_USAGE "/server _host_[:_port_]\n\r"

int	nick(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i);
int	server(const char** const cmd, t_infos* infos,
	       const fd_set* const fd_write, const unsigned int i);
int	ping(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i);
int	handle_input(t_infos* const infos, const char* const buf,
		     const fd_set* const fd_write, const unsigned int i);

#endif /* !_CONTROL_H_ */
