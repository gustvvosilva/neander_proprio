#include <stdio.h>
#include <stdbool.h>

int main(){

    FILE *file = fopen("soma.mem", "rb");
    
    __uint8_t bytes[256];
    __uint8_t byte[1];
    int i2 = 0;

    __uint8_t ac = 0, pc = 0;
    bool neg = false, zer = false;

    for(int i = 0; i < 516; i++) {

        if(i < 4)
            fread(byte, 1, 1, file);
        else if(i % 2 == 1)
            fread(byte, 1, 1, file);
        else {
            fread(byte, 1, 1, file);
            bytes[i2] = byte[0];
            i2++;
        }
    }
    fclose(file);

    // bytes[0x80] = 0x04;
    // bytes[0x81] = 0xFE;

    while(bytes[pc] != 0xf0) {

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
        }

        printf("AC:%02x PC:%02x", ac, pc);
        for(int i = 0; i < 256; i++){
            if(i % 16 == 0)
                printf("\n");
            printf("%02x ", bytes[i]);
        }
        printf("\n===================================================\n");

        pc++;
    }
    printf("cabo\n");

    return 0;
}