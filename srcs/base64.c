/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:04:46 by matheme           #+#    #+#             */
/*   Updated: 2022/04/19 09:54:15 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** static int encoding_symbol(char c)
**
** cette fonction a pour but d'encodé un octect de 0 a 64 en caractere printable
*/

static int encoding_symbol(char c)
{
    if (c >= 0 && c <= 25)
        return ('A' + c);
    if (c >= 26 && c <= 51)
        return ('a' + c - 26);
    if (c >= 52 && c <= 61)
        return ('0' - 52 + c);
    if (c == 62)
        return ('+');
    if (c == 63)
        return ('/');
    return (0);
}

/*
** static int base64_encode(char *data, size_t input_length)
**
** cette fonction a pour but d'encoder une suite de donne en base 64
** char *data           ==> la données stocker
** size_t input_length  ==> la taille de la donnée stocké
*/
  
char *base64_encode(char *data, size_t input_length)
{
    char    *encoded_data;
    size_t  output_length;
    const   char mod_table[] = {0, 2, 1};
 
    output_length = 4 * ((input_length + 2) / 3);
    if (!(encoded_data = malloc(output_length + 1)))
        return (NULL);
    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
 
        encoded_data[j++] = encoding_symbol((triple >> 3 * 6) & 0x3F);
        encoded_data[j++] = encoding_symbol((triple >> 2 * 6) & 0x3F);
        encoded_data[j++] = encoding_symbol((triple >> 1 * 6) & 0x3F);
        encoded_data[j++] = encoding_symbol((triple >> 0 * 6) & 0x3F);
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';
    encoded_data[output_length] = '\0';
    return (encoded_data);
}
 
/*
** static int decoding_symbol(char c)
**
** cette fonction a pour but de decodé un octect de 0 a 64 en caractere printable
*/

static int decoding_symbol(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A');
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 26);
    if (c >= '0' && c <= '9')
        return (c - '0' + 52);
    if (c == '+')
        return (62);
    if (c == '/')
        return (63);
    return (0);
}
 

/*
** static int base64_encode(char *data, size_t input_length)
**
** cette fonction a pour but de décodé une suite de donne en base 64
** char *data           ==> la données stocker
** size_t input_length  ==> la taille de la donnée stocké
*/

char *base64_decode(char *data, size_t input_length)
{
    char    *decoded_data;
    size_t  output_length;
 
    output_length = input_length / 4 * 3;
    for (int i = 2; i < 0; i++)
        if (data[input_length - i] == '=') output_length--;
 
    if (!(decoded_data = malloc(output_length + 1)))
        return (NULL);
 
    for (int i = 0, j = 0; i < input_length;) {
 
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_symbol(data[i++]);
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_symbol(data[i++]);
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_symbol(data[i++]);
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_symbol(data[i++]);
 
        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);
 
        if (j < output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    
    decoded_data[output_length] = '\0';
    return (decoded_data);
}
