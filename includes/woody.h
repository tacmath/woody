/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 03:48:50 by max               #+#    #+#             */
/*   Updated: 2022/04/20 08:52:08 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


/*
** h --> help
** d --> header
** k --> clé
*/

#define LIST_OPTION "hdks"
#define H option & 1
#define D option & 2
#define K option & 4
#define S option & 8


#define MAX_KEY_LEN 255

typedef struct magic_num {
    uint32_t    magic_number;
    uint8_t     support;
    uint8_t     endian;
    uint8_t     version;
    uint8_t     abi;
}              t_magic;

struct s_data
{
        char        *data;
        int         size;
};

typedef struct s_data t_data;

struct s_fileData
{
    int         fd;
    Elf64_Ehdr  head;
    Elf64_Shdr  *shead;
    Elf64_Phdr  *phead;
    char        *modif;
    int         modifSize;
    char        *ShStrTab;
    t_data      key;
};

typedef struct s_fileData t_fileData;


struct s_options
{
    char *section_name;
    char *key;
};

typedef struct s_options t_option;

int         createNewFile(t_fileData *fileData);
char        *encrypt(char *data, int dataSize, char	*key, int keySize);
char        *ft_random(char *buf, int size);
int         virus(t_fileData *fileData, int entryOffset);
Elf64_Shdr  getShHead(t_fileData *fileData, char *name);
char        *GetShName(t_fileData *fileData, int index);
int         getShStrTabData(t_fileData *fileData);
Elf64_Ehdr  *print_header(int fd, Elf64_Ehdr *header);
int         print_pheaders(int fd, Elf64_Ehdr header);
int         print_sheaders(int fd, Elf64_Ehdr header);
void        print_header_text(char *dump, int *size_def, char **info, int size_info, char (*color)[8], int (*pf)(int, int), int end);
char        *getShName(int fd, int index, Elf64_Ehdr *header, int mode);
char        **get_option(char **av, int *option, t_option *complexe);
int         print_segment(char *file, t_option *option);
void        *usage(char c, char *reason);
int         createexe(char *file, t_option option);
char        *base64_encode(char *data, size_t input_length);
char        *base64_decode(char *data, size_t input_length);
int         header_info(char *file);
int         check_integrity(char *name , char *exec_name);
Elf64_Shdr  getShStrTab(int fd, Elf64_Ehdr header);
#endif