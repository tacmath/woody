#include "woody.h"

void autoCompletionDuCode(t_fileData *fileData, char *decode, int startSize, int keyoff, char decryptoff) {
    Elf64_Shdr shead;
    int offset;

    shead = getShHead(fileData, ".text");
    offset = shead.sh_offset - fileData->head.e_entry - startSize - 7;
    ft_memcpy(&decode[3], &offset, 4);
    ft_memcpy(&decode[8], &shead.sh_size, 4);
    ft_memcpy(&decode[15], &keyoff, 4);
    ft_memcpy(&decode[20], &fileData->key.size, 4);
    decode[25] = decryptoff;
}

int virus(t_fileData *fileData, int entryOffset) {
    char start[] = {    0x50, 0x53, 0x51, 0x52, 0x56, 0x57, 0x41, 0x54, 0x41, 0x55, 0xeb, 0x1a};//push rax rbx rcx rdx rsi rdi r12 r13 | jmp print_woody

    char decode[] = {   0x48, 0x8d, 0x3d, 0x00, 0x00, 0x00, 0x00,   //lea rdi (a changer)
                        0xbe, 0x00, 0x00, 0x00, 0x00,               //mov rsi (a changer)
                        0x48, 0x8d, 0x15, 0x77, 0x00, 0x00, 0x00,   //lea rdx key
                        0xb9, 0x00, 0x00, 0x00, 0x00,               //mov rcx (a changer)
                        0xeb, 0x28};                                //jmp decrypt

    char p_woody[] = {  0xbf, 0x01, 0x00, 0x00, 0x00,
                        0x48, 0x8d, 0x35, 0x0e, 0x00, 0x00, 0x00,
                        0xba, 0x0e, 0x00, 0x00, 0x00,
                        0xb8, 0x01, 0x00, 0x00, 0x00,
                        0x0f, 0x05,
                        0xeb, 0xcc,                                 // jmp decode
                        0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a};
    
    char decrypt[] = {  0x48, 0x89, 0xf0, 0x49, 0x89, 0xd4, 0x48, 0x31, 0xd2, 0x49, 0x89, 0xcd, 0x49, 0xf7, 0xf5, 0x49, 0x89, 0xd5, 0x4c, 0x89, 0xe2,
                        0x49, 0x83, 0xfd, 0x00, 0x75, 0x03, 0x49, 0x89, 0xcd,
                        0x49, 0xff, 0xcd, 0x48, 0xff, 0xce, 0x8a, 0x5c, 0x37, 0xff, 0x42, 0x02, 0x1c, 0x2a, 0x28, 0x1c, 0x37, 0x48, 0x83, 0xfe, 0x01, 0x75, 0xe0, 0x8a, 0x1a, 0x28, 0x1f};
    
    char fin[] = {      0x41, 0x5d, 0x41, 0x5c, 0x5f, 0x5e, 0x5a, 0x59, 0x5b, 0x58, // pop all registers
                        0xe9, 0x00, 0x00, 0x00, 0x00};                              // jmp to old entry (a changer)


    char *tmp;

    start[sizeof(start) - 1] = sizeof(decode);
    autoCompletionDuCode(fileData, decode, sizeof(start), sizeof(p_woody) + sizeof(decrypt) + sizeof(fin) + 7, sizeof(p_woody));
    p_woody[sizeof(p_woody) - 15] = -((char)sizeof(p_woody) - 14 + (char)sizeof(decode));
    fileData->modifSize = sizeof(start) + sizeof(decode) + sizeof(p_woody) + sizeof(decrypt) + sizeof(fin);
    entryOffset -= fileData->modifSize;
    ft_memcpy(&fin[sizeof(fin) - 4], &entryOffset, 4);
    fileData->modifSize += fileData->key.size;
    if (!(fileData->modif = malloc(fileData->modifSize)))
        return (0);
    tmp = fileData->modif;
    ft_memcpy(tmp, start, sizeof(start));
    tmp += sizeof(start);
    ft_memcpy(tmp, decode, sizeof(decode));
    tmp += sizeof(decode);
    ft_memcpy(tmp, p_woody, sizeof(p_woody));
    tmp += sizeof(p_woody);
    ft_memcpy(tmp, decrypt, sizeof(decrypt));
    tmp += sizeof(decrypt);
    ft_memcpy(tmp, fin, sizeof(fin));
    tmp += sizeof(fin);
    ft_memcpy(tmp, fileData->key.data, fileData->key.size);
 //   ft_hexdump(fileData->modif, fileData->modifSize);
    return (1);
}
