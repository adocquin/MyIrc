/*
** client.h for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Tue May 17 02:47:30 2016 Avel Docquin
** Last update	Tue May 24 04:28:49 2016 Avel Docquin
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "misc.h"
#include "socket.h"

#define CANAL0 "#admin"
#define CANAL1 "#general1"
#define CANAL2 "#general2"
#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 1023
#define	BUFFER 510
#define USERNAME 9
#define CHANNELL 200

typedef int(*fct)();

typedef struct		s_env
{
  char			username[USERNAME + 1];
  char			fd_type;
  fct			fct_read;
  fct			fct_write;
  struct sockaddr_in	sin;
  unsigned int		fd;
  unsigned int 		port;
  int			ch[4];
}			t_env;

char*	username_cp(char* const username, const char* const cmd);
int	client_write(const t_env* const e, char *buf,
		     const fd_set* const fd_write, const unsigned int fd);
int	client_read(t_env* const e, const unsigned int fd,
		    char* buf, const fd_set* const fd_write);
int	add_client(t_env* e, int s);

#endif /* !_CLIENT_H_ */
