/*
** main.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed Apr 27 03:21:56 2016 Avel Docquin
** Last update Sun Jun  5 19:50:37 2016 masson mathieu
*/

#include "client.h"

static int	end(t_infos* infos)
{
  if (infos->fd != 0 && close(infos->fd) == -1)
    {
      perror("close");
      free(infos);
      return (-1);
    }
  free(infos);
  return (0);
}

int		main(void)
{
  t_infos*	infos;
  int		quit;

  quit = 0;
  while (quit == 0)
    {
      if (!(infos = malloc(sizeof(t_infos)))
	  || !(infos = init_infos(infos, NULL)))
	return (1);
      if (quit != 1)
	{
	  quit = handle_online(infos);
	  if (quit == -1)
	    {
	      end(infos);
	      return (-1);
	    }
	}
      if (end(infos) == -1)
	return (1);
    }
  return (0);
}
