#include <stdio.h>

double trnSet[25][3];                                 // Training Set Simuating f(x, y) = 3x + 4y + 1
int trnSetSize = (int)(sizeof(trnSet)/sizeof(double[3]));

double theta_0, theta_1, theta_2;
double derivatives[3];

double alpha;

void fill_trnSet(){                                   // Fills the training set with random input values
    for(int i = 0; i < trnSetSize; i++){
        trnSet[i][0] = (i*93654 + 873324) % 50;
        trnSet[i][1] = (i*28524 + 335249) % 50;
        trnSet[i][2] = 3*(trnSet[i][0]) + 4*(trnSet[i][1]) + 1;
    }
}

double f(double x_0, double x_1){return (theta_0*x_0 + theta_1*x_1 + theta_2);}

double absVal(double num){return (num < 0 ? -num : num);}

void findDerivatives(){
    derivatives[0] = derivatives[1] = derivatives[2] = 0;
    double term;
    for(int i = 0; i < trnSetSize; i++){
        term = f(trnSet[i][0], trnSet[i][1]) - trnSet[i][2];
        derivatives[0] += term*trnSet[i][0];
        derivatives[1] += term*trnSet[i][1];
        derivatives[2] += term;
    }
    derivatives[0] /= trnSetSize;
    derivatives[1] /= trnSetSize;
    derivatives[2] /= trnSetSize;
}

void gradDescent(double min_error, int max_iters){
    double curr_error = min_error+1;
    int counter = 0;
    while(curr_error > min_error && counter < max_iters){
        counter++;
        findDerivatives();
        theta_0 -= alpha*derivatives[0];
        theta_1 -= alpha*derivatives[1];
        theta_2 -= alpha*derivatives[2];
        curr_error = absVal(alpha*(derivatives[0] + derivatives[1] + derivatives[2]) / 3 );
        printf("%d: f(x_0,x_1) = %.5fx_0 + %.5fx_1 + %.5f\n", counter, theta_0, theta_1, theta_2);
    }
}

int exponent(int base, int exp){
    int result = 1;
    for(int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

int charpToInt(char* c){
    int size = 0;
    int power = 0;
    int num = 0;
    while(*c != 0){
        size++;
        c++;
    }
    for(int i = size-1; i >= 0; i--){
        c--;
        num += ((int)*c - 48) * exponent(10, power);
        power++;
    }
    return num;
}

int main(int argv, char** argc){

    fill_trnSet();
    theta_0 = -8;
    theta_1 = -93;
    theta_2 = 20;
    alpha = 1e-3;
    gradDescent(1e-7, 100000);
    return 0;
}
