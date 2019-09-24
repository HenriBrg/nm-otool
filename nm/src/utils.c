#include "../inc/nm.h"

/*
** Trie alphabétique sur le "name" de chaque élément t_symbol
**
*/

t_symbol *sort(t_symbol *syms, int size)
{
  int       i;
  int       j;
  t_symbol  tmp;

  i = 0;
  while (i < size)
  {
    j = i + 1;
    while (j < size)
    {
      if (ft_strcmp(syms[i].name, syms[j].name) > 0)
      {
        tmp = syms[i];
        syms[i] = syms[j];
        syms[j] = tmp;
      }
      j++;
    }
    i++;
  }
  return (syms);
}
