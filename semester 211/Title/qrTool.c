#include<stdio.h>
#include<string.h>

void checkInfoQR() {
    /*
    Hint:
    - Look up for strstr() 
    - Look up for printf() using precision field
    */
}

void convertQR() {
    /*
    Hint: 
    - Look up for strcmp(), strlen(), strcpy(), strncpy()
    */ 
}

void encryptQR() {
    /*
    Hint: 
    - Look up for sprintf(), strcat(), strncat()
    */ 
}

int main(){
    int menu_code;
    scanf("%d", &menu_code);
    if(menu_code == 1) {
        checkInfoQR();
    } else if (menu_code == 2) {
        convertQR();
    } else {
        encryptQR();
    }
    return 0;
}