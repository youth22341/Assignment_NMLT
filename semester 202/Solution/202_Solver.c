#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define PI 3.14159

void exitInvalid() {
    printf("-1");
    exit(0);
}

double sin(double x) {
    double sinx = x,s = 0,k;
    int i;
    for(i = 1; i < 6; i++) {
        if(i%2 == 0) {
            k = -sinx;
            sinx = (k*x*x)/(2*i*(2*i+1));
        }
        else {
            k = sinx;
            sinx = -(k*x*x)/(2*i*(2*i+1));
        }
        s += sinx;
    }
    return s + x;
}

double cos(double x) {
    double cosx = 1,s = 0,k;
    int i;
    for(i = 1; i < 6; i++) {
        if(i%2 == 0) {
            k = -cosx;
            cosx = (1.0*k*x*x)/((2*i-1)*2*i);
        }
        else {
            k = cosx;
            cosx = (-1.0*k*x*x)/((2*i-1)*2*i);
        }
        s += cosx;
    }
    return s + 1;
}

double tan(double x) {
    return sin(x)/cos(x);
}

double deg_to_rad(double x) {
    return x*PI/180;
}

void divisor(int x2) {
    int j;
    printf("1");
    for(j = 2; j <= x2; j++)
        if(x2 % j == 0)
            printf(" %d",j) ;
}

void prime_factor(int x2) {
    int exponent,count = 0;
    int j;
    for(j = 2; j <= x2; j++) {
        exponent = 0;
        if(x2 % j == 0) {
            while(x2 % j == 0) {
                exponent++;
                x2 /= j;
            }
            count++;
            if(count == 1)
                printf("%d^%d",j,exponent);
            else
                printf("*%d^%d",j,exponent);
        }
        else continue ;
    }
}

int main() {
    int menu_code,n,m,p;
    int x2;
    double x, result;
    scanf("%d", &menu_code);
    if(menu_code == 1) {
        scanf("%d %d %d",&n,&m,&p);
        if((n != 1 && n != 2 && n != 3) || (m != 0 && m != 1) || (p != 2 && p != 4 && p != 7))
            exitInvalid();
        else {
            scanf("%lf",&x);
            switch(n) {
            case 1:
                switch(m) {
                case 0:
                    if(x < 0 || x > 180)
                        exitInvalid();
                    else
                        result = sin(deg_to_rad(x));
                    break;
                case 1:
                    if(x < 0 || x > PI)
                        exitInvalid();
                    else
                        result = sin(x);
                    break;
                }
                break;
            case 2:
                switch(m) {
                case 0:
                    if(x < 0 || x > 180)
                        exitInvalid();
                    else
                        result = cos(deg_to_rad(x));
                    break;
                case 1:
                    if(x < 0 || x > PI)
                        exitInvalid();
                    else
                        result = cos(x);
                    break;
                }
                break;
            case 3:
                switch(m) {
                case 0:
                    if(x == 90 || x < 0 || x > 180)
                        exitInvalid();
                    else
                        result = tan(deg_to_rad(x));
                    break;
                case 1:
                    if(x == PI/2 || x < 0 || x > PI)
                        exitInvalid();
                    else
                        result = tan(x);
                    break;
                }
                break;
            default :
                exitInvalid();
            }
            switch(p) {
            case 2:
                printf("%.2lf",result);
                break;
            case 4:
                printf("%.4lf",result);
                break;
            case 7:
                printf("%.7lf",result);
                break;
            }
        }
    } else if (menu_code == 2) {
        scanf("%d",&m);
        if(m != 1 && m != 2)
            exitInvalid();
        else {
            scanf("%d",&x2);
            if(x2 <= 1)
                exitInvalid();
            else {
                switch(m) {
                case 1:
                    divisor(x2) ;
                    break;
                case 2:
                    prime_factor(x2) ;
                    break;
                default :
                    exitInvalid();
                }
            }
        }
    } else
        exitInvalid();
    return 0;
}
