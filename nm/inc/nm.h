#ifndef NM_H
#define NM_H

# include "./libft.h"

# include <errno.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

void arch64(void *ptr);
void arch32(void *ptr);

# define SYM_NAME_SIZE 256

typedef struct	s_symbol
{
	char			*name; //[SYM_NAME_SIZE];
	uint8_t		type;
	uint8_t		ext;
	uint8_t		sect;
	uint64_t	value;
}				t_symbol;

#endif
