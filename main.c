#include <stdio.h>
#include <stdint.h>
int32_t is_ascii(char str[]){
    for (int i = 0; i < str[i] != '\0'; i++){
        if(str[i] < 0 || str[i] > 127){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int32_t capitalize_ascii(char str[]){
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 97 && str[i] <= 122){
            str[i] = str[i] - 32;
            count += 1;
        }
    }
    return count;
}