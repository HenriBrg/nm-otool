#include "../inc/nm.h"

/*
** Affiche l'adresse du symbol
** Si symbole de type U (undefined), affiche 16 espaces
*/

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

/*
** Un symbol de type N_UNDF, l'adresse est vide et le type de symbol est U pour undefined
**
** name = string du symbol
** Documentation sur les types de symbole possible : https://github.com/grumbach/nm_otool
*/

void print(t_symbol sym)
{

  hexa((uintmax_t)sym.value, (sym.type == N_UNDF));
  if (sym.type == N_UNDF)
    write(1, sym.ext ? " U " : " u ", 3);
  else if (sym.type == N_ABS)
    write(1, sym.ext ? " A " : " a ", 3);
  else if (sym.type == N_INDR)
    write(1, sym.ext ? " I " : " i ", 3);
  // else if (sym.type == N_SECT)
  ft_printf(" %s\n", sym.name);
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

static void sym64(void *ptr, struct symtab_command *sym)
{
  int             i;
  char            *tmp;
  char            *strtab;
  t_symbol        *symscpy;
  struct nlist_64 *array;

  array = ptr + sym->symoff;
  strtab = ptr + sym->stroff;
  if ((symscpy = (t_symbol*)malloc(sizeof(t_symbol) * sym->nsyms)) == 0)
    return ;
  i = -1;
  while (++i < (int)sym->nsyms)
  {
    tmp = strtab + array[i].n_un.n_strx;
    ft_strcpy(symscpy[i].name, tmp);
    symscpy[i].type = array[i].n_type & N_TYPE;
    symscpy[i].ext  = array[i].n_type & N_EXT;
    symscpy[i].sect = array[i].n_sect;
    symscpy[i].value = array[i].n_value;
  }
  i = -1;
  symscpy = sort(symscpy, sym->nsyms);
  while (++i < (int)sym->nsyms)
    print(symscpy[i]);
}

/*
** Voir img4
** Segment : __text, __data, __bss
** Un segment contient plusieurs sections dans lesquelles le contenu du programme est distribué
**
** + de détail sur segment et section : https://opensource.apple.com/source/xnu/xnu-2050.18.24/EXTERNAL_HEADERS/mach-o/loader.h
*/

static void segment(struct load_command *lc)
{
  uint32_t                  i;
  struct segment_command_64 *segment;
  struct section_64         *section;

  i = 0;
  segment = (struct segment_command_64*)lc;
  section = (struct section_64*)((void*)lc + sizeof(segment));
  while (i < segment->nsects)
  {
    printf("Section[%d] : %s\n", i, section[i].sectname);
    i++;
  }
}

/*
** lc = (void *)lc + lc->cmdsize
** Fonctionnement similaire aux listes chainées -
** Le sym change à chaque tour de boucle (sym = (struct symtab_command *)lc) puisque
** lc est incrémenté de la taille de lc->cmdsize, c.a.d la commande sur laquelle
** on est positionné en mémoire
*/

void x64(void *ptr)
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
    if (lc->cmd == LC_SEGMENT_64)
      segment(lc);
    if (lc->cmd == LC_SYMTAB)
    {
      sym = (struct symtab_command *)lc;
      sym64(ptr, sym);
      break ;
    }
    lc = (void *)lc + lc->cmdsize;
  }
}
