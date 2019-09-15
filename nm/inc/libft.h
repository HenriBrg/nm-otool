/*

	Fonctions autorisées : malloc, free, write
	Constante autorisées : NULL, size_t (via string.h)
	Casts conseillés (surtout sur des (void*))
	Fonctions Static autorisées
	Variables globales interdites
	Une chaine de caractères se termine toujours par un '/0'
	Toute mémoire alloué sur le tas (?) doit être libérée proprement

	Pour tester une fonction à part et utiliser les autres fonction de la LIBFT :
	Exemple : gcc ft_strnstr.c -L. libft.a && ./a.out BONJOUR JOUR

	RECAPITULATIF BUG LIBFT : Selon les units test :
	- Strsplit segfault dans un cas qui reste à déterminer
	- putchar et puchar_fd ne gère pas l'unicode
	- atoi ne gère pas les très long string

*/

#ifndef LIBFT_H
#	define LIBFT_H

#	include <unistd.h>
#	include <stdlib.h>
#	include <string.h>
#	include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

# define BUFF_SIZE 8

// # define malloc(x) NULL

typedef struct		s_list
{
	void			      *content;
	size_t			    content_size;
	struct s_list	  *next;
}                 t_list;

t_list 	*ft_lstmap(t_list *lst, t_list * (*f)(t_list *elem));
t_list 	*ft_lstnew(void const *content, size_t content_size);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int   ft_toupper(int c);
int   ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int 	ft_strequ(char const *s1, char const *s2);
int 	ft_strnequ(char const *s1, char const *s2, size_t n);
int		ft_get_next_line(const int fd, char **line);
int  	ft_printf(const char *format, ...);

size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

char 	*ft_itoa(int n);
char 	*ft_itoa_base(char *base, int n);
char  *ft_intmaxt_toa_base(char *base, intmax_t n);
char  *ft_Uintmaxt_toa_base(char *base, uintmax_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, char *src, size_t nb);
char	*ft_strcpy(char *dest, const char *src);
char  *ft_strncpy(char * dst, const char * src, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *str, const char *to_find);
char  *ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strnew(size_t size);
char 	*ft_strmap(char const *s, char (*f)(char));
char 	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char 	*ft_strsub(char const *s, unsigned int start, size_t len);
char 	*ft_strtrim(char const *s);
char 	*ft_strjoin(char const *s1, char const *s2);
char 	**ft_strsplit(char const *s, char c);
char 	**ft_split_by_size(char *str, int size);

void	ft_putchar(char c);
void	ft_putstr(const char *str);
void 	ft_putendl(char const *s);
void	ft_putnbr(int nb);
void 	ft_putchar_fd(char c, int fd);
void  ft_putstr_fd(char const *s, int fd);
void  ft_putendl_fd(char const *s, int fd);
void 	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_strdel(char **as);
void	ft_memdel(void **ap);
void	ft_strclr(char *s);
void 	ft_striter(char *s, void (*f)(char *));
void 	ft_striteri(char *s, void (*f)(unsigned int, char *));

void 	ft_lstadd(t_list **alst, t_list *new);
void 	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void 	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void 	ft_lstiter(t_list *lst, void (*f)(t_list *elem));

void	*ft_memset(void *b, int c, size_t len);
void  *ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void 	*ft_memalloc(size_t size);

#endif
