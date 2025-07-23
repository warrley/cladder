#include <stdio.h>
#include "awtils.h"

int awlen(char *s1) {
    int i;
    for(i = 0; s1[i] != '\0'; i++);
    return i; 
};

int awcmp(char *s1, char *s2) {
    int diff = 0;
    for(int i = 0; (i < awlen(s1) || i < awlen(s2)) && diff == 0; i++) {
        if(s1[i] != s2[i]) {
            diff = s1[i] - s2[i];
        };
    };
    return diff;
};