#include <stdint.h>
#include "drivers/port.h"
#include "drivers/ports.h"
#include "terminal.h"
#include "str.h"
#define input_max_size 512

int capslock = 0;
char *keyboard_char_keys_down[] ={"ENTER","q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "1", "2", "3", "4", "5",
"6", "7", "8", "9", "0", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "\\","z", "x", "c", "v", "b", "n", "m",
",", ".", "/", " ", "\1"};
uint16_t keyboard_byte_keys[] =  {0x1c,   0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x02,0x03,0x04,0x05,0x06,
0x07,0x08,0x09,0x0a,0x0b,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,
0x33,0x34,0x35,0x39,0x0e};
int block_capslock = 0;
int nullkey = 0;
int enterpressed = 0;
char input[input_max_size];

int len(uint16_t arr[]){
    int len;
	while (arr[len])
		len++;
	return len;
}

uint16_t keyboard_byte_key(){
    return port_byte_in(KEYBOARD_PS2_PORT);
}
char *keyboard_key(){
    int i;
    while(keyboard_byte_keys[i] != 0){
        if(keyboard_byte_key() == keyboard_byte_keys[i]){
            nullkey = 0;
            return keyboard_char_keys_down[i];
        }
        i++;
    }
    nullkey = 1;
    return (char*)"null";
}
void tkeyboard_input(){
    int timer = 0;
    int len = 0;
    memset(input, '\0', 32);
    while(1){
        char *key = keyboard_key();
        if(timer == 0){
            if(key == (char*)"ENTER" && enterpressed == 0){
                print("\n");
                enterpressed = 1;
                break;
            } else if(key != (char*)"ENTER"){
                enterpressed = 0;
            }
            if(key == (char*)"\1" && len > 0){
                input[strlen(input)-1] = 0;
                len--;
                print(key);
            } else if(strlen(key) == 1 && key != (char*)"\1" && len < input_max_size){
                charadd(input, key[0]);
                len++;
                print(key);
            }
            timer = 1;
        }
        if(key[0] == 'n' && key[strlen(key)-1] == 'l'){
            timer = 0;
        }
    }
}
void keyboard_input(char tinput[]){
    memset(tinput, '\0', 32);
    tkeyboard_input();
    for(int i; i < input_max_size; i++){
        tinput[i] = input[i];
    }
}
