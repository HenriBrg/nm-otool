#include "../inc/nm.h"

/*
**
** Les paramètres sont des offsets et non des pointeurs,
** donc doit faire des "sauts" en mémoire
**
** strtab = Pointeur, on se positionne sur le début du tableau de string avec le nom des commandes
** array  = Pointeur, on se positionne sur la structure nlist_64 qui suit (en mémoire)
** la structure symtab_command (cette derniere nous fourni l'offet pour jump sur la nlist_64)
*/

static void output64(void *ptr, int nsyms, int symoff, int stroff)
{
  int             i;
  char            *strtab;
  struct nlist_64 *array;

  strtab = ptr + stroff;
  array = ptr + symoff;
  i = -1;
  while (++i < nsyms)
    ft_printf("%s\n", strtab + array[i].n_un.n_strx);
}

void arch64(void *ptr)
{
  int i;
  int ncmds;
  struct mach_header_64 *header;
  struct load_command   *lc;
  struct symtab_command *sym;

  i = -1;
  header = (struct mach_header_64 *)ptr;
  ncmds = header->ncmds;
  lc = (void *)ptr + sizeof(*header);
  while (++i < ncmds)
  {
    if (lc->cmd == LC_SYMTAB)
    {
      sym = (struct symtab_command *)lc;
      output64(ptr, sym->nsyms, sym->symoff, sym->stroff);
      break ;
    }
    lc = (void *)lc + lc->cmdsize;
  }
}
