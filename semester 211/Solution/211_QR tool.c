#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *split_STK(int k, char *S);
char *split_Owner(int k, char *S);
char *split_Time(int k, char *S);

int detect(char *S) { //detect what type of bank in QR information
    int n = strlen(S);
    int i;
    if(strstr(S,"BKB") != NULL) return 1;
    else if(strstr(S,"KHB") != NULL) return 2;
    else if(strstr(S,"HBB") != NULL) return 3;
    else return 0;
}

char *delete_sign(char *S) { //delete '/' sign after use function split_Time()
    int i, n = 11;
    for(i = 2; i < n; i++) {
        if(S[i] == '/') {
            strcpy(&S[i],&S[i+1]);
            n--;
        }
    }
    S[n] = '\0';
    return S;
}

char *rerange_Time(int k, int q, char *S) { // k represent for source, q represent for destination
    int i;
    char *S1 = delete_sign(split_Time(detect(S),S)); //after this command, the result has type: ddmmyyyy
    char *S2 = (char *)malloc(9);
    if(k == 1) {
        if(q == 2) {
            S2[0] = S1[2];
            S2[1] = S1[3];
            S2[2] = S1[0];
            S2[3] = S1[1];
            S2[4] = S1[4];
            S2[5] = S1[5];
            S2[6] = S1[6];
            S2[7] = S1[7];
            S2[8] = '\0';
        }
        else {
            S2[0] = S1[6];
            S2[1] = S1[7];
            S2[2] = S1[2];
            S2[3] = S1[3];
            S2[4] = S1[0];
            S2[5] = S1[1];
            S2[6] = '\0';
        }
    }
    if(k == 2) {
        if(q == 1) {
            for(i = 0; i < 9; i++)
                S2[i] = S1[i];
            S2[i] = '\0';
        }
        else {
            S2[0] = S1[6];
            S2[1] = S1[7];
            S2[2] = S1[2];
            S2[3] = S1[3];
            S2[4] = S1[0];
            S2[5] = S1[1];
            S2[6] = '\0';
        }
    }
    if(k == 3) {
        if(q == 1) {
            for(i = 0; i < 9; i++)
                S2[i] = S1[i];
            S2[i] = '\0';
        }
        else {
            S2[0] = S1[2];
            S2[1] = S1[3];
            S2[2] = S1[0];
            S2[3] = S1[1];
            S2[4] = S1[4];
            S2[5] = S1[5];
            S2[6] = S1[6];
            S2[7] = S1[7];
            S2[8] = '\0';
        }
    }
    return S2;
}

char *encrypt_Owner(int a, char *S) {
    int i,j,m = 0;
    int n = strlen(S);
    int A[52];
    char *S1 = (char *)malloc(91); //max_length = 30, max ASCII has 3 numbers => max_length = 30*3 = 90 => max_size = 91
    char alpha[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    if(a == 0) return S;
    else {
        if(a == 1) {
            A[0] = 65;
            for(i = 1; i < 52; i++) {
                if(i < 26) A[i] = A[0] + i;
                else A[i] = A[0] + 6 + i; // A[i] = A[0] + 32 + (i-26)
            }
            for(i = 0; i < n; i++) {
                for(j = 0; j < 52; j++) {
                    if(S[i] == alpha[j]) {
                        if(A[j] < 100) {
                            S1[m] = (A[j]/10) + '0'; // convert type int into type char
                            S1[m+1] = (A[j]%10) + '0';
                            m += 2;
                        }
                        else {
                            S1[m] = (A[j]/100) + '0';
                            S1[m+1] = ((A[j]/10)-(A[j]/100)*10) + '0';
                            S1[m+2] = (A[j]%10) + '0';
                            m += 3;
                        }

                    }
                }
            }
            S1[m] = '\0';
        }
        else {
            for(i = 0; i < n; i++) {
                for(j = 0; j < 52; j++) {
                    if(S[i] == alpha[j]) {
                        S1[m] = (j/10) + '0';
                        S1[m+1] = (j%10) + '0';
                        m += 2;
                    }
                }
            }
            S1[m] = '\0';
        }
        return S1;
    }
}

char *encrypt_STK(int b, char *S) {
    if(b == 0) return S;
    else{
        int i,j = 0,n = strlen(S);
        char *S2 = (char *)malloc(16);
        for(i = n-1; i >= 0; i--){
            S2[j] = S[i];
            j++;
        }
        S2[j] = '\0';
        return S2;
    }
}

char *split_STK(int k, char *S) {
    int i,j = 0;
    int n = strlen(S);
    char *S1 = (char *)malloc(16);
    if(k == 1) {
        for(i = 14; i <= 26; i++) {
            S1[j] = S[i];
            j++;
        }
        S1[j] = '\0';
    }
    else if(k == 2) {
        for(i = 22; i <= 36; i++) {
            S1[j] = S[i];
            j++;
        }
        S1[j] = '\0';
    }
    else {
        for(i = 11; i < n-9; i++) {
            if(S[i] >= 48 && S[i] <= 57) {
                S1[j] = S[i];
                j++;
            }
        }
        S1[j] = '\0';
    }
    return S1;
}

char *split_Owner(int k, char *S) {
    int i,j = 0;
    int n = strlen(S);
    char *S2 = (char *)malloc(31);
    if(k == 1) {
        for(i = 27; i < n-8; i++) {
            if(S[i] > 57) {
                S2[j] = S[i];
                j++;
            }
        }
        S2[j] = '\0';
    }
    else if(k == 2) {
        for(i = 37; i < n; i++) {
            S2[j] = S[i];
            j++;
        }
        S2[j] = '\0';
    }
    else {
        for(i = 11; i < n-17; i++) {
            S2[j] = S[i];
            j++;
        }
        S2[j] = '\0';
    }
    return S2;
}

char *split_Time(int k, char *S) {
    int i,j = 0;
    int n = strlen(S);
    char *S3 = (char *)malloc(11);
    if(k == 1) {
        for(i = n-8; i < n; i++) {
            S3[j] = S[i];
            j++;
            if(j == 2 || j == 5) {
                S3[j] = '/';
                j++;
            }
        }
        S3[j] = '\0';
    }
    else if(k == 2) {
        S3[0] = S[13];
        S3[1] = S[14];
        S3[2] = '/';
        S3[3] = S[11];
        S3[4] = S[12];
        S3[5] = '/';
        S3[6] = S[15];
        S3[7] = S[16];
        S3[8] = S[17];
        S3[9] = S[18];
        S3[10] = '\0';
    }
    else {
        S3[0] = S[n-5];
        S3[1] = S[n-4];
        S3[2] = '/';
        S3[3] = S[n-7];
        S3[4] = S[n-6];
        S3[5] = '/';
        S3[6] = '2';
        S3[7] = '0';
        S3[8] = S[n-9];
        S3[9] = S[n-8];
        S3[10] = '\0';
    }
    return S3;
}

char *Time_Origin(int k, char *S) { //Keep origin type of bank's Time
    int i, j = 0;
    int n = strlen(S);
    char *S0 = (char *)malloc(8);
    if(k == 2) {
        for(i = 11; i < 19; i++) {
            S0[j] = S[i];
            j++;
        }
        S0[j] = '\0';
    }
    else {
        for(i = n-9; i <= n-4; i++) {
            S0[j] = S[i];
            j++;
        }
        S0[j] = '\0';
    }
    return S0;
}

int main() {
    int menu_code;
    scanf("%d",&menu_code);
    if(menu_code == 1) {
        char S[68] = "0002010102108162021KHB012100002512112DangVu";
        //scanf("%s",S);
        int k = detect(S);
        if(k == 1) printf("Ngan hang: BKB\n");
        if(k == 2) printf("Ngan hang: KHB\n");
        if(k == 3) printf("Ngan hang: HBB\n");
        printf("So tai khoan: %s\n",split_STK(k,S));
        printf("Ten chu tai khoan: %s\n",split_Owner(k,S));
        printf("Thoi diem tao QR: %s",split_Time(k,S));
    }
    else if(menu_code == 2) {
        char S0[4] = "BKB";
        char S[68] = "0002010102108162021KHB02100002512112DangVu";
        //  scanf("%s",S0); //destination
        //scanf("%s",S); // source
        if(detect(S0) == 0) printf("Ngan hang chuyen den khong hop le");
        else {
            int k = detect(S);
            int q = detect(S0);
            char *S1;
            if(k == 1) S1 = "BKB";
            if(k == 2) S1 = "KHB";
            if(k == 3) S1 = "HBB";
            if(q == 1) {
                printf("00020101021%s%s%s%s",S1,split_STK(k,S),split_Owner(k,S),rerange_Time(k,1,S));
            }
            else if(q == 2) {
                printf("00020101021%s%s%s%s",rerange_Time(k,2,S),S1,split_STK(k,S),split_Owner(k,S));
            }
            else {
                printf("00020101021%s%s%s%s",split_Owner(k,S),split_STK(k,S),rerange_Time(k,3,S),S1);
            }
        }
    }
    else {
        char S[68] = "00020101021BKB0882003729910DangVanThanh18072020";
        int a,b,c;
        int k = detect(S);
//        scanf("%d%d%d",&a,&b,&c);
//        scanf("%s",S);
        a = 1, b = 1, c = 1;
        if((a != 0 && a != 1 && a!= 2) || (b != 0 && b != 1) | (c != 0 && c != 1)) printf("Thong so nhap vao khong hop le");
        else {
            char *S1 = encrypt_Owner(a,split_Owner(k,S));
            char *S2 = encrypt_STK(b,split_STK(k,S));
            char S3[117] = "00020101021"; //max_length = max_STK + max_Owner + max_Time + max_bank's name = 15 + 90 + 8 + 3 = 116 => max_size = 117
            char *S4 = (char *)malloc(117);
            if(k == 1) {
                strcat(S3,"BKB");
                strcat(S3,S2);
                strcat(S3,S1);
                strcat(S3,delete_sign(split_Time(1,S)));
            }
            if(k == 2) {
                strcat(S3,Time_Origin(2,S));
                strcat(S3,"KHB");
                strcat(S3,S2);
                strcat(S3,S1);
            }
            if(k == 3) {
                strcat(S3,S1);
                strcat(S3,S2);
                strcat(S3,Time_Origin(3,S));
                strcat(S3,"HBB");
            }
            if(c == 0) {
                printf("%s",S3);
            }
            else {
                char alpha_digit[63] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
                int s = strlen(S1);
                int n = strlen(S3);
                int d = (11*s)%62;
                int i,j;
                for(i = 0; i < n; i++) {
                    for(j = 0; j < 62; j++) {
                        if(S3[i] == alpha_digit[j]) S4[i] = alpha_digit[(j+d)%62];
                    }
                }
                S4[n] = '\0';
                printf("%s",S4);
                free(S4);
            }
        }
    }
    return 0;
}



    