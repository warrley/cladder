#include <stdio.h>

int wacmp(char w1[], char w2[]) {
    int i;
    for(i = 0; w1[i] != '\0' && w2[i] != '\0'; i++) {
        if(w1[i] != w2[i]) {
            return w1[i] - w2[i];
        }
    }

    return 0;
}

int main()  {


    return 0;
}