/*
** commands.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sat Jun  4 07:40:08 2016 Avel Docquin
** Last update Sat Jun  4 08:36:05 2016 Avel Docquin
*/

#ifndef _COMMANDS_H_
# define _COMMANDS_H_

#include "infos.h"

int	list(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i);
int	msg(const char** const cmd, t_infos* infos,
	    const fd_set* const fd_write, const unsigned int i);
int	join(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i);
int	users(const char** const cmd, t_infos* infos,
	      const fd_set* const fd_write, const unsigned int i);
int	part(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i);

#endif /* !_COMMANDS_H_ */
