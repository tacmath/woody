/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sheaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:20:34 by max               #+#    #+#             */
/*   Updated: 2022/04/20 04:21:48 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static char *get_section_type(unsigned long long val)
{
    static char *p_type[] = {"PT_NULL (section header entry)", "SHT_PROGBITS (Program data)", "SHT_SYMTAB (Symbol table)", "SHT_STRTAB (String table)", "SHT_RELA (Reloc addends)", "SHT_HASH (Symbol hash table)", "SHT_DYNAMIC (linking info)", "SHT_NOTE (Notes)", "SHT_NOBITS (bss)", "SHT_REL (Reloc no addends)", "SHT_SHLIB (Reserved)", "SHT_DYNSYM (link symbol table)", "SHT_INIT_ARRAY (constructors)", "SHT_FINI_ARRAY (destructors)", "SHT_PREINIT_ARRAY (pre-construct)", "SHT_GROUP (Section group)", "SHT_SYMTAB_SHNDX (section index ++)", "SHT_NUM (Number defined types)", "SHT_LOOS (Start OS-speci)", "SHT_GNU_ATTRIBUTES (attributes)", "SHT_GNU_HASH (hash table)", "SHT_GNU_LIBLIST (Prelink libraries)", "SHT_CHECKSUM (Checksum)", "SHT_LOSUNW (Sun-speci)", "SHT_SUNW_COMDAT", "SHT_SUNW_syminfo", "SHT_GNU_verdef (Version)", "SHT_GNU_verneed (Version)", "SHT_GNU_versym (Version)", "SHT_HIOS (End OS-spec)", "SHT_LOPROC (Start proc-spec)", "SHT_HIPROC (End proc-spec)", "SHT_LOUSER (Start app spec)", "SHT_HIUSER (End app spec)"};
    static int value [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 16, 17, 18, 19, 0x60000000, 0x6ffffff5, 0x6ffffff6, 0x6ffffff7, 0x6ffffff8, 0x6ffffffa, 0x6ffffffb, 0x6ffffffc, 0x6ffffffd, 0x6ffffffe, 0x6fffffff, 0x70000000, 0x7fffffff, 0x80000000, 0x8fffffff};
    int n;

    n = -1;
    while (++n <= sizeof(value)) {
        if (value[n] == val) {
            return (ft_strdup(p_type[n]));
        }
    }
    return (ft_strdup("undefined"));
}

static char *get_section_flags(unsigned long long val)
{
    static char *p_type[] = {
        "Writable",
        "Occupies memory",
        "Executable",
        "Might be merged",
        "Contains strings",
        "sh_info",
        "Preserve",
        "Non-standard OS spec",
        "member of a group",
        "thread-local data",
        "compressed data",
        "OS-specific",
        "Processor-specific",
        "Special Solaris",
        "excluded unless Solaris"
        };
    static unsigned long long value [] = {SHF_WRITE, SHF_ALLOC,SHF_EXECINSTR, SHF_MERGE,SHF_STRINGS,  SHF_INFO_LINK,  SHF_LINK_ORDER,  SHF_OS_NONCONFORMING, SHF_GROUP, SHF_TLS, SHF_COMPRESSED, SHF_MASKOS, SHF_MASKPROC, SHF_ORDERED , SHF_EXCLUDE};
    int n;
    int ite;
    char *str;

    n = -1;
    ite = 0;
    str = ft_strdup("");
    while (++n < 15) {
        if (value[n] & val) {
            ite++;
            if (ite > 1)
                ft_strjoin_free(&str, ft_strdup(" && "));
            ft_strjoin_free(&str, ft_strdup(p_type[n]));
        }
    }
    return (str);
}

static char *get_aligment(unsigned long long val)
{
    char *align;
    char *str;

    align = ft_utoa_base(val, 10, 4);
    if (val == 0 || val == 1)
        return (ft_strdup("No Aligment"));
    str = ft_strdup("Aligment (");
    ft_strjoin_free(&str, align);
    ft_strjoin_free(&str, ft_strdup(")"));
    return (str);
}

static char *convert_sheader_to_str(int idx, unsigned long long val)
{
    if (idx == 1)
        return (get_section_type(val));
    if (idx == 8)
        return (get_aligment(val));
    if (idx == 0)
        return (ft_strdup(getShName(0, val, NULL, 0)));
    if (idx == 2)
        return (ft_strdup("    ⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓    "));
    return (ft_strdup("undefined"));
}


static int check_sheader_correspondance(int idx, int val)
{
    char *str;

    if (idx == 0 || idx == 1 || idx == 8 || idx == 2)
    {
        str = convert_sheader_to_str(idx, val);
        ft_putnstr(str, 30);
        free(str);
        return (0);
    }
    return (1);
}

void print_sheader_flag(Elf64_Xword *flag, int end)
{
    char *str_flag;

    ft_putstr("┃\033[0;33m ");
    str_flag = get_section_flags((unsigned long long)*flag);
    ft_putnstr(str_flag, 127);
    free(str_flag);
    ft_putstr("\033[0;37m\0");
    if (end == 0)
        ft_putstr("┃\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    else
         ft_putstr("┃\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

int print_sheader(int fd, int end)
{
    Elf64_Shdr header;
    int size_def[] = {
        sizeof(Elf64_Word),
        sizeof(Elf64_Word),
        sizeof(Elf64_Xword),
        sizeof(Elf64_Addr),
        sizeof(Elf64_Off),
        sizeof(Elf64_Xword),
        sizeof(Elf64_Word), 
        sizeof(Elf64_Word),
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
        "Section name                \0",
        "Section type                \0",
        "Section flags               \0",
        "Section addr at execution   \0",
        "Section file offset         \0",
        "Section size in bytes       \0",
        "Link to another section     \0",
        "Additional information      \0",
        "Section alignment           \0",
        "Entry size section table    \0"
    };

    if (read(fd, &header, sizeof(Elf64_Shdr)) < sizeof(Elf64_Shdr))
        return (1);

    print_header_text((char*)&header, size_def, info, sizeof(info) / sizeof(*info), color, &check_sheader_correspondance, 0);
    print_sheader_flag((Elf64_Xword*)((char*)&header + sizeof(uint64_t)), end);
    ft_putstr("\n\n");
}

int print_sheaders(int fd, Elf64_Ehdr header) {
    int n = -1;
    char *p;

    getShName(fd, 0, &header, 1);
    lseek(fd, header.e_shoff, SEEK_SET);
    while (++n < header.e_shnum)
    {
        ft_putstr("\033[0;37m\n\n");
        ft_putstr("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        ft_putstr("┃                                             ┃        SECTIONS HEADER N°");
        p = ft_utoa_base(n, 10, 2);
        ft_putstr(p);
        free(p);
        ft_putstr("   ┃                                                  ┃\n");
        print_sheader(fd, 1);
        lseek(fd, header.e_shoff + (n + 1) * header.e_shentsize , SEEK_SET);
    }
}