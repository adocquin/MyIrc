/*
** init_func_tab.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sat Jun  4 20:36:37 2016 Avel Docquin
** Last update Sat Jun  4 20:44:56 2016 Avel Docquin
*/

#include "init_func_tab.h"

int	func_tab(optr** tab)
{
  if (!(*tab = malloc(sizeof(optr) * 9)))
    {
      perror("malloc");
      return (-1);
    }
  (*tab)[0] = ping;
  (*tab)[1] = server;
  (*tab)[2] = nick;
  (*tab)[3] = list;
  (*tab)[4] = msg;
  (*tab)[5] = join;
  (*tab)[6] = users;
  (*tab)[7] = part;
  (*tab)[8] = NULL;
  return (0);
}
