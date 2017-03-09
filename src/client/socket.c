/*
** socket.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Mon May 23 05:17:53 2016 Avel Docquin
** Last update Sun Jun  5 20:12:50 2016 Avel Docquin
*/

#include "socket.h"

static int	sigpipe = 0;

static void	sig_handler(int sig)
{
  if (sig == SIGPIPE)
    sigpipe = 1;
}

int		read_socket(unsigned int fd, char* buf,
			    const struct sockaddr_in* const s_in)
{
  ssize_t	r;
  socklen_t	s_length;

  if (fd != 1)
    {
      s_length = (socklen_t)sizeof(struct sockaddr_in);;
      r = recvfrom(fd, buf, BUFFER, 0, (struct sockaddr*)&s_in, &s_length);
    }
  else
    r = read(1, buf, BUFFER);
  if ((r == -1 && fd != 1 && errno == ENOMEM) || (r == -1 && fd == 1))
    {
      perror("read");
      return (-1);
    }
  else if (r == -1 && fd != 1)
    r = 0;
  if (r == 0 && fd != 1 && my_write(1, CO_CLOSED) == -1)
    return (-1);
  if (r != 0)
    buf[r] = '\0';
  return (r);
}

int	write_socket(unsigned int fd, char* buf, const fd_set* const fd_write)
{
  int	len;
  int	tmp;
  int	r;

  signal(SIGPIPE, sig_handler);
  if (FD_ISSET(fd, fd_write))
    {
      tmp = r = my_strlen(buf);
      len = 0;
      r = tmp;
      while (len != r && sigpipe == 0)
	{
	  r -= len;
	  if ((len = write(fd, buf + len, r)) == -1 && sigpipe != 1)
	    {
	      perror("write socket");
	      return (-1);
	    }
	}
    }
  return (0);
}
