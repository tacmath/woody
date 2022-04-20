/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:56:58 by max               #+#    #+#             */
/*   Updated: 2022/04/20 07:53:00 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static char *disas_magic_number(unsigned long long value)
{
    t_magic magic;
    char    *str;
    static char    m_abi[][20] = {"System V", "HP-UX", "NetBSD", "	Linux", "GNU Hurd", "Solaris", "AIX", "IRIX", "FreeBSD", "Tru64", "Novell Modesto", "OpenBSD", "OpenVMS", "NonStop Kernel", "AROS", "FenixOS", "Nuxi CloudABI", "OpenVOS" };


    ft_memcpy(&magic, &value, sizeof(t_magic));
    str = ft_strdup("ELF ");
    ft_strjoin_free(&str, ft_strdup(m_abi[magic.abi]));
    if (magic.support == 0x1)
        ft_strjoin_free(&str, ft_strdup(" 32 bit "));
    else
        ft_strjoin_free(&str, ft_strdup(" 64 bit "));
    
    if (magic.endian == 0x1)
        ft_strjoin_free(&str, ft_strdup("(Little)"));
    else
        ft_strjoin_free(&str, ft_strdup("(Big)"));
    return (str);
}

static char *printMachine(int nb) {
    static char    m_type[7][15] = {"undefined", "No machine", "SPARC", "Intel 80386", "Sun SPARC 32+", "SPARC V9", "AMD 64"};
    int     nb_list[7] = {-1, 0, 2, 3, 18, 43, 62};
    int n;

    n = -1;
    while (++n < 7)
        if (nb_list[n] == nb)
           return(m_type[n]);
    return (m_type[0]);
}

static char *convert_val_to_str(int idx, unsigned long long val)
{
    static char e_type[5][20] = {"No file type", "Relocatable file", "Executable file", "Shared object file", "Core file"};

    if (idx == 0)
        return (ft_strdup(disas_magic_number(val)));
    if (idx == 1)
        return (ft_strdup(e_type[val]));
    if (idx == 2)
        return (ft_strdup(printMachine(val)));
    return (ft_strdup("undefined"));
}



static int check_correspondance(int idx, int val)
{
    char *str;

    if (idx >= 0 && idx <= 2)
    {
        str = convert_val_to_str(idx, val);
        ft_putnstr(str, 30);
        free(str);
        return (0);
    }
    return (1);
}

Elf64_Ehdr *print_header(int fd, Elf64_Ehdr *header)
{
    int size_def[] = {
        EI_NIDENT, sizeof(Elf64_Half),
        sizeof(Elf64_Half),
        sizeof(Elf64_Word),
        sizeof(Elf64_Addr),
        sizeof(Elf64_Off),
        sizeof(Elf64_Off),
        sizeof(Elf64_Word),
        sizeof(Elf64_Half),
        sizeof(Elf64_Half),
        sizeof(Elf64_Half),
        sizeof(Elf64_Half),
        sizeof(Elf64_Half),
        sizeof(Elf64_Half)
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
        "Magic number                \0",
        "type file                   \0",
        "type of machine             \0",
        "Version                     \0",
        "Entry point                 \0",
        "offset of programme's header\0",
        "offset of section's header  \0",
        "Processor-specific flags    \0",
        "size of ELF header          \0",
        "size of program header      \0",
        "number of program header    \0",
        "size of section header      \0",
        "number of section header    \0",
        "index of section name entry \0",
    };

 
    if (read(fd, header, sizeof(*header)) < sizeof(Elf64_Ehdr))
        return (NULL);


    ft_putstr("\033[0;37m\0");
    ft_putstr("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    ft_putstr("┃                                             ┃           ELF HEADER          ┃                                                  ┃\n");

    print_header_text((char*)header, size_def, info, sizeof(info) / sizeof(*info), color, &check_correspondance, 1);
    return (NULL);
}
