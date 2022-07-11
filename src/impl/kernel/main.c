#include "terminal.h"
#include "drivers/keyboard.h"
#include "str.h"
#include "drivers/port.h"
#include "user_files/pcmem.h"
#include "contol/power.h"

void kstart(){
    tset_color(LIGHT_CYAN,BLACK);
    print("Welcome to Sourim OS\n\n");
    tset_color(WHITE,BLACK);
}

void print_log(enum color log_color, char *log, char *message, char *joiner){
    tset_color(log_color, BLACK);
    print(log);
    tset_color(WHITE, BLACK);
    print(joiner);
    print(message);
}

void krun(){
    char enter_input[512];
    print("@");
    tset_color(CYAN, BLACK);
    print(username);
    tset_color(WHITE, BLACK);
    print(" $ ");
    keyboard_input(enter_input);
    char command[32];
    memset(command, 0, 32);
    for(int i = 0; i < 32; i++){
        if(enter_input[i] == ' ' || enter_input[i] == 0){
            break;
        }
        charadd(command, enter_input[i]);
    }
    
    if(strcheck(command, "echo", 32)){
        if(strlen(enter_input) > 5){
            for(int i = strlen(command)+1; i < strlen(enter_input); i++){            
                tputchar(enter_input[i]);
            }
            tputchar('\n');
        } else {
            print_log(RED, "ERROR", "Arguments is empty\n", " > ");
        }
    } else if(strcheck(command, "help", 32)){
        print_log(LIGHT_GREEN, "echo <text*>","        Print the text in terminal\n","");
        print_log(LIGHT_GREEN, "clear","               Clear screen\n",              "");
        print_log(LIGHT_GREEN, "setusername <name*>"," Set username\n",              "");
        print_log(LIGHT_GREEN, "russia","              Show Russian flag\n",         "");
        print_log(LIGHT_GREEN, "shutdown","            Power off\n",                 "");
        print_log(LIGHT_GREEN, "reboot","              Restart machine\n",           "");
    } else if(strcheck(command, "clear", 32)){
        clear();
    } else if(strcheck(command, "setusername", 32)){
        if(strlen(enter_input) > strlen(command)+1){
            int ii = 0;
            for(int i = strlen(command)+1; i < strlen(command)+33; i++){
                username[ii] = enter_input[i];
                ii++;
            }
            print_log(GREEN, "OK", "Username is changed\n", " > ");
        } else {
            print_log(RED, "ERROR", "Arguments is empty\n", " > ");
        }
    } else if(strcheck(command, "russia", 32)){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 10; x++){
                if(y == 0){
                    tset_color(WHITE, WHITE);
                } else if(y == 1){
                    tset_color(WHITE, BLUE);
                } else if(y == 2){
                    tset_color(WHITE, RED);
                }
                tputchar(' ');
            }
            tputchar('\n');
        }
    } else if(strcheck(command, "reboot", 32)){
        reboot();
    } else if(strcheck(command, "shutdown", 32)){
        shutdown();
    } else {
        print_log(CYAN, "WARN", "Unknown command, please type 'help'\n", " > ");
    }
}
