/*
** server.h for my_irc in /home/docqui_a/PSU_2015_myirc/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Mon May 16 23:47:19 2016 Avel Docquin
** Last update Fri May 20 06:09:09 2016 Avel Docquin
*/

#ifndef _SERVER_H_
# define _SERVER_H_

#include <signal.h>
#include <errno.h>
#include "client.h"
#include "handle.h"

int	add_server(t_env* const e);
int	manage_server(t_env* const e);

#endif /* !_SERVER_H_ */
