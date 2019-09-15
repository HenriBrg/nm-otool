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

#endif
