/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 14:39:00 by matheme           #+#    #+#             */
/*   Updated: 2022/04/13 09:48:37 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/// function on char
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_putchar(char c);
void                ft_putnchar(int c, int n);
void				ft_putchar_fd(char c, int fd);

/// function on memory
void				*ft_memalloc(size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t len);
void				ft_memdel(void **ap);
void				ft_putmem(const void *addr);
void 				ft_hexdump(char *dump, int dump_size);
void                ft_hexdump_color(char *dump, int dump_size, int *color_size);
void                ft_linear_hexdump(char *dump, int dump_size);
void                ft_advanced_hexdump_color(char *dump, int dump_size, int *color_size);

/// function on str
char				*ft_strnew(size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putstr(const char *str);
void                ft_putnstr(const char *str, int n);
void				ft_putendl(const char *str);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putendl_fd(const char *str, int fd);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_strdel(char **as);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, int s1_len, int s2_len);
void				ft_strjoin_free(char **s1, char *s2);

/// function convert
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_utoa_base(unsigned long long nb, int bx, int champ);
char				**ft_strsplit(char const *s, char c);
uint8_t				swap_uint8t(uint8_t nb);
uint16_t			swap_uint16t(uint16_t nb);
uint32_t			swap_uint32t(uint32_t nb);
uint64_t			swap_uint64t(uint64_t nb);
uint64_t            swap_byte(uint64_t k, size_t size);
char                *ft_strrev_swap(char *str);

/// function math
int					ft_power(int nb, int power);


/// function number
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbrbase(long long nb, int base);

#endif
