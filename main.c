#include <stdio.h>
#include <stdint.h>
int main(){

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
            count++;
        }
    }
    return count;
}

int32_t width_from_start_byte(char start_byte){
    unsigned char byte = (unsigned char)start_byte;{
        if (byte >> 7 == 0){ // checks the first element of the bit sequence, since a bit sequence is 8 units long it shifts to the right 7 bits and then records the 1st bit as the 8th
            return 1;
        }
        else if(byte >> 5 == 0b110){
            return 2;
        }
        else if(byte >> 4 == 0b1110){
            return 3;
        }
        else if(byte >> 3 == 0b11110){
            return 4;
        }
        else{
            return -1;
        }
    }
}

int32_t utf8_strlen(char str[]){

    int32_t length = 0;
    unsigned char byte;

    while (*str) {
        byte = (unsigned char)*str;


        if ((byte & 0x80) == 0x00) {
            str += 1;  
        }
 
        else if ((byte & 0xE0) == 0xC0) {
            if ((str[1] & 0xC0) != 0x80) {  
                return -1;  
            }
            str += 2;
        }
      
        else if ((byte & 0xF0) == 0xE0) {
            if ((str[1] & 0xC0) != 0x80 || (str[2] & 0xC0) != 0x80) {
                return -1;  
            }
            str += 3;
        }
        
        else if ((byte & 0xF8) == 0xF0) {
            if ((str[1] & 0xC0) != 0x80 || (str[2] & 0xC0) != 0x80 || (str[3] & 0xC0) != 0x80) {
                return -1;  
            }
            str += 4;
        }
   
        else {
            return -1;
        }

     
        length++;
    }

    return length;
}


int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int32_t current_cpi = 0;  
    int32_t byte_index = 0;   
    unsigned char byte;

    
    while (str[byte_index] != '\0') {
        byte = (unsigned char)str[byte_index];

       
        if ((byte & 0x80) == 0x00) {
            if (current_cpi == cpi) {
                return byte_index;  
            }
            byte_index += 1;  
        }
        
        else if ((byte & 0xE0) == 0xC0) {
            if (current_cpi == cpi) {
                return byte_index;  
            }
            
            if ((str[byte_index + 1] & 0xC0) != 0x80) {
                return -1;  
            }
            byte_index += 2;
        }
        
        else if ((byte & 0xF0) == 0xE0) {
            if (current_cpi == cpi) {
                return byte_index;  
            }
            // Validate continuation bytes
            if ((str[byte_index + 1] & 0xC0) != 0x80 || (str[byte_index + 2] & 0xC0) != 0x80) {
                return -1;  
            }
            byte_index += 3;
        }
        
        else if ((byte & 0xF8) == 0xF0) {
            if (current_cpi == cpi) {
                return byte_index;  
            }
            // Validate continuation bytes
            if ((str[byte_index + 1] & 0xC0) != 0x80 || (str[byte_index + 2] & 0xC0) != 0x80 || (str[byte_index + 3] & 0xC0) != 0x80) {
                return -1;  
            }
            byte_index += 4;
        }
        
        else {
            return -1;
        }

        current_cpi++;  
    }

   
    return -1;
}
    

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
if (cpi_start < 0 || cpi_end < 0 || cpi_start >= cpi_end) {
     
        return;
    }

    int32_t current_cpi = 0;  
    int32_t byte_index = 0;   
    int32_t result_index = 0; 
    unsigned char byte;

    
    while (str[byte_index] != '\0' && current_cpi < cpi_end) {
        byte = (unsigned char)str[byte_index];

        
        int bytes_in_codepoint = 0;
        if ((byte & 0x80) == 0x00) {
           
            bytes_in_codepoint = 1;
        } else if ((byte & 0xE0) == 0xC0) {
            
            bytes_in_codepoint = 2;
        } else if ((byte & 0xF0) == 0xE0) {
            
            bytes_in_codepoint = 3;
        } else if ((byte & 0xF8) == 0xF0) {
            
            bytes_in_codepoint = 4;
        } else {
            
            result[0] = '\0';
            return;
        }

        
        if (current_cpi >= cpi_start && current_cpi < cpi_end) {
            for (int i = 0; i < bytes_in_codepoint; i++) {
                result[result_index++] = str[byte_index + i];
            }
        }

        
        byte_index += bytes_in_codepoint;
        current_cpi++;
    }

    
    result[result_index] = '\0';
}


int32_t codepoint_at(char str[], int32_t cpi){
    if (cpi < 0) {
        return -1; 
    }

    int32_t current_cpi = 0; 
    int32_t byte_index = 0;  
    unsigned char byte;

   
    while (str[byte_index] != '\0') {
        byte = (unsigned char)str[byte_index];

        
        if (current_cpi == cpi) {
            int32_t codepoint = 0;

            
            if ((byte & 0x80) == 0x00) {
                codepoint = byte;
                return codepoint;
            }
            
            else if ((byte & 0xE0) == 0xC0) {
                codepoint = (byte & 0x1F) << 6;
                if ((str[byte_index + 1] & 0xC0) != 0x80) {
                    return -1; 
                }
                codepoint |= (str[byte_index + 1] & 0x3F);
                return codepoint;
            }
           
            else if ((byte & 0xF0) == 0xE0) {
                codepoint = (byte & 0x0F) << 12;
                if ((str[byte_index + 1] & 0xC0) != 0x80 || (str[byte_index + 2] & 0xC0) != 0x80) {
                    return -1; 
                }
                codepoint |= (str[byte_index + 1] & 0x3F) << 6;
                codepoint |= (str[byte_index + 2] & 0x3F);
                return codepoint;
            }
            
            else if ((byte & 0xF8) == 0xF0) {
                codepoint = (byte & 0x07) << 18;
                if ((str[byte_index + 1] & 0xC0) != 0x80 || (str[byte_index + 2] & 0xC0) != 0x80 || (str[byte_index + 3] & 0xC0) != 0x80) {
                    return -1; 
                }
                codepoint |= (str[byte_index + 1] & 0x3F) << 12;
                codepoint |= (str[byte_index + 2] & 0x3F) << 6;
                codepoint |= (str[byte_index + 3] & 0x3F);
                return codepoint;
            } else {
                return -1; 
            }
        }

       
        if ((byte & 0x80) == 0x00) {
            byte_index += 1; // 1-byte (ASCII)
        } else if ((byte & 0xE0) == 0xC0) {
            byte_index += 2; // 2-byte UTF-8
        } else if ((byte & 0xF0) == 0xE0) {
            byte_index += 3; // 3-byte UTF-8
        } else if ((byte & 0xF8) == 0xF0) {
            byte_index += 4; // 4-byte UTF-8
        } else {
            return -1; 
        }

        current_cpi++;
    }

    
    return -1;
}



char is_animal_emoji_at(char str[], int32_t cpi) {
    
    int32_t codepoint = codepoint_at(str, cpi);
    
    if (codepoint < 0) {
        return -1; 
    }

    
    if ((codepoint >= 0x1F400 && codepoint <= 0x1F43F) ||  
        (codepoint >= 0x1F980 && codepoint <= 0x1F993)) { 
        return 1; // It's an animal emoji
    }
    
    return 0; // It's not an animal emoji
}


}

