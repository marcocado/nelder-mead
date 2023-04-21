#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#include "test_function.h"
#include "simplex/simplex.h"
#include "simplex/simplex_methods.h"
#include "nelder_mead.h"

int main(void){
    // Initialization of all variables
    double alpha = 1;
    double beta = 2.0;
    double gamma = 0.5;
    double omega = -0.5;
    double step_width = 0.6;
    double tolerance = 0.1;
    int maximum_iterations = 30;
    int i = 0;

    // Declaration of all points and the simplex structure and assignment of the starting conditions
    struct point P_reflexion, P_expansion, P_outer_contraction, P_inner_contraction;
    struct simplex S, *ptrS;
    ptrS = &S;
    ptrS->x1 = -4.0;
    ptrS->y1 = -6.0;
    initialize_simplex(ptrS, step_width);
    double average_edge_length = calculate_average_edge_length(ptrS);

    // Start the writing process of the txt-file
    FILE *filePtr;
    filePtr = fopen("downhill_simplex.txt","w");
    fprintf(filePtr, "x1, y1, f1, x2, y2, f2, x3, y3, f3\n");

    // Numerical solving process until a solution is found of maximum itertations are reached
    while(average_edge_length > tolerance && i <= maximum_iterations){
        print_simplex(ptrS, filePtr);
        calculate_simplex(ptrS);
        sort_simplex(ptrS);
        P_reflexion = calculate_reflexion(ptrS, alpha);
        if(P_reflexion.f < ptrS->fMin){
            P_expansion = calculate_reflexion(ptrS, beta);
            if(P_expansion.f < ptrS->fMin){
                replace_simplex_point(ptrS, P_expansion, ptrS->max);
            }
            else {
                replace_simplex_point(ptrS, P_reflexion, ptrS->max);
            }
        }
        else if(P_reflexion.f < ptrS->fMax){
            P_outer_contraction = calculate_reflexion(ptrS, gamma);
            if(P_outer_contraction.f < P_reflexion.f){
                replace_simplex_point(ptrS, P_outer_contraction, ptrS->max);
            }
            else{
                compress_simplex(ptrS, ptrS->min);
            }
        }
        else if(P_reflexion.f >= ptrS->fMax){
            P_inner_contraction = calculate_reflexion(ptrS, omega);
            if (P_inner_contraction.f < ptrS->fMax)
            {
                replace_simplex_point(ptrS, P_inner_contraction, ptrS->max);
            }
            else{
                compress_simplex(ptrS, ptrS->min);
            }
        }
        else{
            replace_simplex_point(ptrS, P_reflexion, ptrS->max);
        }
        average_edge_length = calculate_average_edge_length(ptrS);
        i++;
    }

    // Show if the numerical process have reached a valueable solution
    if(average_edge_length > tolerance){
        printf("Numerical process haven't converged with the %d iteration\n", i-1);
    }
    else{
        printf("The solution is x = %.2f and y = %.2f\n", ptrS->xMin, ptrS->yMin);
    }
    
    // Close the printet .txt-file
    fclose(filePtr);
    
    return 0;
}
