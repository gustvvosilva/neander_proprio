#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv){

    FILE *file = fopen(argv[1], "rb");

    if(!file) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    
    __uint8_t bytes[256];
    __uint8_t byte[1];
    int getByte = 0;
    __uint32_t memID[1];

    __uint8_t ac = 0, pc = 0;
    bool neg, zer;

    fread(memID, 1, 4, file);
    if(*memID != 0x52444e03) {
        printf("O arquivo fornecido não corresponde á um formato conhecido do neander.%08x\n", *memID);
        fclose(file);
        return 1;
    }

    for(int i = 0; i < 512; i++) {

        if(i % 2 == 1)
            fread(byte, 1, 1, file);
        else {
            fread(byte, 1, 1, file);
            bytes[getByte] = *byte;
            getByte++;
        }
    }
    fclose(file);

    // Mude esse valores para trocar os caracteres da operação.
    // bytes[0x80] = 0xF7;
    // bytes[0x81] = 0xFB;

    while(bytes[pc] != 0xf0) {

        if(ac >= 0x80)
            neg = true;
        else
            neg = false;

        if(ac == 0)
            zer = true;
        else
            zer = false;

        // printf("AC:%02x PC:%02x %s %s", ac, pc, neg?"neg":"pos", zer?"zer":"nze");
        // for(int i = 0; i < 256; i++){
        //     if(i % 16 == 0)
        //         printf("\n");
        //     printf("%02x ", bytes[i]);
        // }
        // printf("\n===================================================\n");
            
        switch(bytes[pc]) {

            case 0x10:
            pc++;
            bytes[bytes[pc]] = ac;
            break;

            case 0x20:
            pc++;
            ac = bytes[bytes[pc]];
            break;

            case 0x30:
            pc++;
            ac += bytes[bytes[pc]];
            break;

            case 0x60:
            ac = ~ac;
            break;

            case 0x80:
            pc++;
            pc = bytes[pc] - 0x01;
            break;

            case 0x90:
            pc++;
            if(neg) {
                pc = bytes[pc] - 0x01;
            }
            break;

            case 0xa0:
            pc++;
            if(zer) {
                pc = bytes[pc] - 0x01;
            }
            break;
        }

        pc++;
    }

    printf("\nAC: %02x - PC: %02x\n"
        "flags: N(%c) - Z(%c)\n", ac, pc, neg?'*':' ', zer?'*':' ');
    printf("\nMemória final =========================================");
    for(int i = 0; i < 256; i++){
        if(i % 16 == 0)
            printf("\n%07x ", i);
        printf("%02x ", bytes[i]);
    }
    printf("\n=======================================================\n");
    printf("Finalizou com sucesso!\n\n");
    return 0;
}
