/*
** parser.c for MyFTP in /media/sf_work/c/MyFTP
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May  4 00:29:13 2016 Avel Docquin
** Last update Sun Jun  5 19:55:13 2016 masson mathieu
*/

#include "parser.h"

void		free_2d_tab(char **tab)
{
  unsigned int	i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	{
	  free(tab[i]);
	  ++i;
	}
      free(tab);
    }
}

static unsigned int	count_word(const char cmd[])
{
  unsigned int		i;
  unsigned int		word;
  int			c;

  i = word = 0;
  while (cmd[i])
    {
      if (cmd[i] == 32)
	{
	  c = i + 1;
	  if (cmd[c] != 32)
	    ++word;
	}
      ++i;
    }
  ++word;
  return (word);
}

static char*	command_word(const char cmd[], unsigned int pos)
{
  unsigned int	c;
  unsigned int	i;
  char*		word;

  c = 0;
  i = pos;
  while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\r' && cmd[i] != '\n')
    {
      ++c;
      ++i;
    }
  if (!(word = (char*)malloc(sizeof(char) * (c + 1))))
    {
      perror("malloc");
      return (NULL);
    }
  word[c] = '\0';
  i = 0;
  while (cmd[pos] && cmd[pos] != ' ' && cmd[pos] != '\r' && cmd[pos] != '\n')
    {
      word[i] = cmd[pos];
      ++i;
      ++pos;
    }
  return (word);
}

char**		command_to_tab(const char cmd[], char** tab)
{
  unsigned int	i;
  unsigned int	pos;
  unsigned int	tmp;

  if (my_strlen(cmd) == 0)
    return (NULL);
  i = count_word(cmd);
  if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
    {
      perror("malloc");
      return (NULL);
    }
  tab[i] = NULL;
  tmp = pos = 0;
  while (tmp < i)
    {
      while (cmd[pos] == ' ')
	++pos;
      if (!(tab[tmp] = command_word(cmd, pos)))
	return (NULL);
      pos += my_strlen(tab[tmp]) + 1;
      ++tmp;
    }
  tab[tmp] = NULL;
  return (tab);
}
