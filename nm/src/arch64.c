#include "../inc/nm.h"

// void		print_unsigned(size_t addr, size_t base, size_t len)
// {
// 	char	value;
//
// 	if (len <= 0)
// 		return ;
// 	print_unsigned(addr / base, base, len - 1);
// 	value = HEX_STRING[(addr % base)];
// 	write(1, &value, 1);
// }

void hexa(uintmax_t address, int undefined)
{
  char *strptr;

  if (undefined == 1)
    return (ft_putstr("                "));
  strptr = ft_Uintmaxt_toa_base("0123456789abcdef", address);
  if (strptr != 0)
    ft_putstr("0000000");
  ft_putstr(strptr);
  free(strptr);
}

void sort_symbols(t_symbol *syms)
{
  (void)syms;
}

/*
** Un symbol de type N_UNDF, l'adresse est vide et le type de symbol est U pour undefined
**
** name = string du symbol
*/

void print(struct nlist_64 sym, char *name)
{
  uint8_t     type;
  uint8_t     ext;
  uint8_t     sect;
  uint64_t    value;

  type = sym.n_type & N_TYPE;
  ext  = sym.n_type & N_EXT;
  sect = sym.n_sect;
  value = sym.n_value;

  /* ADRESSE du symbole */
  hexa((uintmax_t)value, (type == N_UNDF));
  /* TYPE du symbole */
  if (name == 0)
    return ;
  else if (type == N_UNDF)
    write(1, " U ", 3);
  /* NOM du symbole */
  write(1, " ", 1);
  ft_putstr(name);
  write(1, "\n", 1);
}

/*
**
** Les paramètres sont des offsets et non des pointeurs,
** donc doit faire des "sauts" en mémoire
**
** strtab = Pointeur, on se positionne sur le début du tableau de string avec le nom des commandes
**
** array  = Pointeur, on se positionne sur la structure nlist_64 qui
** suit (en mémoire) la structure symtab_command
** (cette derniere nous fourni l'offet pour jump sur la nlist_64)
** Exemple : Bitwise & : 1110 & 0111 = 0110
*/

static void output64(void *ptr, int nsyms, int symoff, int stroff)
{
  int             i;
  char            *strtab;
  t_symbol        *syms;
  struct nlist_64 *array;

  i = -1;
  strtab = ptr + stroff;
  array = ptr + symoff;
  // TODO : Trier les symboles car ils doivent être affichés dans l'ordre
  syms = (t_symbol*)malloc(sizeof(t_symbol) * nsyms);
  if (syms == 0)
    return ;
  while (++i < nsyms)
  {
    // syms[i].name = malloc(sizeof(char) * ft_strlen((char*)array[i].n_un.n_strx));
    // syms[i].name = ft_strcpy(syms[i].name, array[i].n_un.n_strx);
    syms[i].type = array[i].n_type;
    syms[i].ext  = array[i].n_desc;
    syms[i].sect = array[i].n_sect;
    syms[i].value = array[i].n_value;
    print(array[i], strtab + array[i].n_un.n_strx);
  }
}


/*
** lc = (void *)lc + lc->cmdsize
** Fonctionnement similaire aux listes chainées -
** Le sym change à chaque tour de boucle (sym = (struct symtab_command *)lc) puisque
** lc est incrémenté de la taille de lc->cmdsize, c.a.d la commande sur laquelle
** on est positionné en mémoire
*/

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
