/*
** parser.h for MyFTP in /media/sf_work/c/MyFTP
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May  4 00:29:28 2016 Avel Docquin
** Last update Thu May 26 17:56:16 2016 Avel Docquin
*/

#ifndef _PARSER_H_
# define _PARSER_H_

#include <stdlib.h>
#include "misc.h"

void	free_2d_tab(char **tab);
char**	command_to_tab(const char cmd[], char** tab);

#endif /* !_PARSER_H_ */
