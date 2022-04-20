/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pheaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:18:31 by max               #+#    #+#             */
/*   Updated: 2022/04/20 04:33:35 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static char *get_segment_type(unsigned long long val)
{
    static char *p_type[] = {"PT_NULL", "PT_LOAD", "PT_DYNAMIC", "PT_INTERP", "PT_NOTE", "PT_SHLIB", "PT_PHDR", "PT_TLS", "PT_NUM", "PT_LOOS", "PT_GNU_EH_FRAME", "PT_GNU_STACK", "PT_GNU_RELRO", "PT_LOSUNW", "PT_SUNWSTACK", "PT_HIOS", "PT_LOPROC", "PT_HIPROC"};
    static int value [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0x60000000, 0x6474e550, 0x6474e551, 0x6474e552, 0x6474e552, 0x6ffffffa, 0x6ffffffb, 0x6fffffff, 0x70000000, 0x7fffffff};
    int n;

    n = -1;
    while (++n <= sizeof(value)) {
        if (value[n] == val) {
            return (ft_strdup(p_type[n]));
        }
    }
}

static char *get_aligment(unsigned long long val)
{
    char *align;
    char *str;

    align = ft_utoa_base(val, 10, 4);
    str = ft_strdup(val <= 1 ? "No aligment (" : "Aligment (");
    ft_strjoin_free(&str, align);
    ft_strjoin_free(&str, ft_strdup(")"));
    return (str);
}

static char *get_right(unsigned long long val)
{
    char *right;

    right = ft_strdup("");
    if (val & 1)
        ft_strjoin_free(&right, ft_strdup("E "));
    if (val & 2)
        ft_strjoin_free(&right, ft_strdup("W "));
    if (val & 4)
        ft_strjoin_free(&right, ft_strdup("R "));
    return (right);
}

static char *convert_pheader_to_str(int idx, unsigned long long val)
{    
    if (idx == 0)
        return (get_segment_type(val));
    if (idx == 7)
        return (get_aligment(val));
    if (idx == 1)
        return (get_right(val));
    return (ft_strdup("undefined"));
}


static int check_pheader_correspondance(int idx, int val)
{
    char *str;

    if (idx == 0 || idx == 7 || idx == 1)
    {
        str = convert_pheader_to_str(idx, val);
        ft_putnstr(str, 30);
        free(str);
        return (0);
    }
    return (1);
}

int print_pheader(int fd)
{
    Elf64_Phdr header;
    int size_def[] = {
        sizeof(Elf64_Word),
        sizeof(Elf64_Word),
        sizeof(Elf64_Off),
        sizeof(Elf64_Addr),
        sizeof(Elf64_Addr),
        sizeof(Elf64_Xword),
        sizeof(Elf64_Xword),
        sizeof(Elf64_Xword)
        };
    char color[][8] = {
        "\033[0;31m\0",
        "\033[0;32m\0",
        "\033[0;33m\0",
        "\033[0;34m\0",
        "\033[0;35m\0",
        "\033[0;36m\0",
        "\e[0;91m\0",
        "\e[0;92m",
        "\e[0;93m",
        "\e[0;94m",
        "\e[0;95m",
        "\e[0;96m",
        "\e[0;97m",
        "\e[1;91m",
        "\e[1;92m",
        "\e[1;93m",
        "\e[1;94m",
        "\e[1;95m",
        "\e[1;96m",
        "\e[1;97m"
        };
    static char *info[] = {
        "Segment type                \0",
        "Segment flags               \0",
        "Segment file offset         \0",
        "Segment virtual address     \0",
        "Segment physical address    \0",
        "Segment size in file        \0",
        "Segment size in memory      \0",
        "Segment alignment           \0",
    };

    if (read(fd, &header, sizeof(Elf64_Phdr)) < sizeof(Elf64_Phdr))
        return (1);

    print_header_text((char*)&header, size_def, info, sizeof(info) / sizeof(*info), color, &check_pheader_correspondance, 1);
    ft_putstr("\n\n");
}

int print_pheaders(int fd, Elf64_Ehdr header) {
    int n = -1;
    char *p;


    lseek(fd, header.e_phoff, SEEK_SET);
    while (++n < header.e_phnum)
    {
        ft_putstr("\033[0;37m\n\n");
        ft_putstr("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        ft_putstr("┃                                             ┃       PROGRAMME HEADER N°");
        p = ft_utoa_base(n, 10, 2);
        ft_putstr(p);
        free(p);
        ft_putstr("   ┃                                                  ┃\n");
        print_pheader(fd);
        lseek(fd, header.e_ehsize + (n + 1) * header.e_phentsize, SEEK_SET);
    }
}