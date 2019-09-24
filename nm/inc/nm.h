#ifndef NM_H
#define NM_H

# include "./libft.h"

# include <errno.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define SYM_NAME_SIZE 256

typedef struct	s_symbol
{
	char			name[SYM_NAME_SIZE];
	uint8_t		type;
	uint8_t		ext;
	uint8_t		sect;
	uint64_t	value;
}				t_symbol;

void arch64(void *ptr);
t_symbol *sort(t_symbol *syms, int size);

#endif
