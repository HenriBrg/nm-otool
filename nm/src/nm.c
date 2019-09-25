#include "../inc/nm.h"

/*
** 1) Check des 4 premiers octets pour savoir quelle architecture on doit traiter

** NB :
** So, (int*)ptr is "the original pointer, converted to an int* so that I can read
** an int from it", and *(int*)ptr is the int value that it points to.
*/

static void nm(void *ptr)
{
  unsigned int magic;

  magic = *(unsigned int*)ptr;
  if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
    x64(ptr);
  // else if (magic == MH_MAGIC || magic == MH_CIGAM)
  //   arch32(ptr);
}

/*
**
**
** Si la size du fichier == 0 --> return
*/

static void   process(char *file)
{
  int           fd;
  void          *ptr;
  struct stat   info;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (ft_putendl_fd(strerror(errno), 2));
  if ((fstat(fd, &info)) == -1)
    return (ft_putendl_fd(strerror(errno), 2));
  if (info.st_size == 0)
    return ;
  if ((ptr = mmap(0, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    return (ft_putendl_fd(strerror(errno), 2));
  nm(ptr);
  if ((munmap(ptr, info.st_size) == -1))
    return (ft_putendl_fd(strerror(errno), 2));
  if ((close(fd)) == -1)
    return (ft_putendl_fd(strerror(errno), 2));
}

int   main(int ac, char **av)
{
  int i;

  if (ac == 1)
    process("a.out");
  else
  {
    i = 0;
    while (av[++i] != 0)
      process(av[i]);
  }
  return (0);
}
