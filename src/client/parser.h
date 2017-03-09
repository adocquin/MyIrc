/*
** parser.h for MyFTP in /media/sf_work/c/MyFTP
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May  4 00:29:28 2016 Avel Docquin
** Last update Tue May 31 22:59:24 2016 Avel Docquin
*/

#ifndef _PARSER_H_
# define _PARSER_H_

#include <stdlib.h>
#include "misc.h"

void	free_2d_tab(char **tab);
char**	command_to_tab(const char cmd[], char** tab, const char c);

#endif /* !_PARSER_H_ */
