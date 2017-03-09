/*
** client.h for MyFTP in /home/docqui_a/work/c/MyFTP/src/client/
**
** Made by avel docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed Apr 27 03:55:45 2016 avel docquin
** Last update	Tue May 24 04:28:17 2016 Avel Docquin
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#include <signal.h>
#include "socket.h"
#include "control.h"
#include "connection.h"
#include "infos.h"

int	handle_online(t_infos* const infos);

#endif /* !_CLIENT_H_ */
