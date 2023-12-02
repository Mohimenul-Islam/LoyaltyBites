#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

double checkLoyalty(double total) {
    if (total <= 5000) return 1.0;
    else if (total <= 10000) return .95;
    else if (total <= 25000) return .90;
    else return .88;
}