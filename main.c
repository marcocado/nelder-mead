#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double function(double x, double y){
    /*
    Himmelblau Function: f(x, y) = (x^2 + y - 11)^2 + (x + y^2 - 7)^2
    */
    return pow((pow(x, 2) + y - 11), 2) + pow((x + pow(y, 2) -7), 2);
}

struct simplex {
    /*
    Data Structure for the Simplex
    - contains all edge points of the simplex
    - contains all information about the minimum and maximum point of the simplex
    */
    double x1;
    double x2;
    double x3;
    double y1;
    double y2;
    double y3;
    double f1;
    double f2;
    double f3;
    double xMax;
    double yMax;
    double fMax;
    double xMin;
    double yMin;
    double fMin;
    unsigned int max : 3;
    unsigned int min : 3;
};

struct point {
    /*
    Data Structure for all Points
    */
    double x;
    double y;
    double f;
};

void initialize_simplex(struct simplex *s, double step_width){
    /*
    Initialsation of the Simplex with a simplex rectangular triangle. Side length as an input.
    */
    s->x2 = s->x1 + step_width;
    s->x3 = s->x1;
    s->y2 = s->y1;
    s->y3 = s->y1 + step_width;
    s->f1 = function(s->x1, s->y1);
    s->f2 = function(s->x2, s->y2);
    s->f3 = function(s->x3, s->y3);
}

void print_simplex(struct simplex *s, FILE *fp){
    /*
    Print all Points of the Simplex to a file
    */
    fprintf(fp, "%.2f, %.2f, %.2f, ", s->x1, s->y1, s->f1);
    fprintf(fp, "%.2f, %.2f, %.2f, ", s->x2, s->y2, s->f2);
    fprintf(fp, "%.2f, %.2f, %.2f\n", s->x3, s->y3, s->f3);
}

void calculate_simplex(struct simplex *s){
    s->f1 = function(s->x1, s->y1);
    s->f2 = function(s->x2, s->y2);
    s->f3 = function(s->x3, s->y3);
}

void sort_simplex(struct simplex *s){
    /*
    Calculate the Maximum and Minimum Point of the Simplex. Write the variables into the
    Data Structure of the Simplex
    */
    if(s->f1 > s->f2 && s->f1 > s->f3){
        s->max = 1;
        s->xMax = s->x1;
        s->yMax = s->y1;
        s->fMax = function(s->xMax, s->yMax);
        if(s->f2 > s->f3){
            s->min = 3;
            s->xMin = s->x3;
            s->yMin = s->y3;
            s->fMin = function(s->xMin, s->yMin);
        }
        else {
            s->min = 2;
            s->xMin = s->x2;
            s->yMin = s->y2;
            s->fMin = function(s->xMin, s->yMin);
        }
    }
    else if (s->f2 > s->f1 && s->f2 > s->f3)
    {
        s->max = 2;
        s->xMax = s->x2;
        s->yMax = s->y2;
        s->fMax = function(s->xMax, s->yMax);
        if(s->f1 > s->f3){
            s->min = 3;
            s->xMin = s->x3;
            s->yMin = s->y3;
            s->fMin = function(s->xMin, s->yMin);
        }
        else {
            s->min = 1;
            s->xMin = s->x1;
            s->yMin = s->y1;
            s->fMin = function(s->xMin, s->yMin);
        }
    }
    else {
        s->max = 3;
        s->xMax = s->x3;
        s->yMax = s->y3;
        s->fMax = function(s->xMax, s->yMax);
        if(s->f1 > s->f2){
            s->min = 2;
            s->xMin = s->x2;
            s->yMin = s->y2;
            s->fMin = function(s->xMin, s->yMin);
        }
        else {
            s->min = 1;
            s->xMin = s->x1;
            s->yMin = s->y1;
            s->fMin = function(s->xMin, s->yMin);
        }
    }
}

void replace_simplex_point(struct simplex *s, struct point p, int position){
    /*
    Replace a Simplex Point with a Point
    Inputs:
        pointer to a struct simplex
        struct point
        position: to know which point you want to change
    */
    if(position == 1){
        s->x1 = p.x;
        s->y1 = p.y;
    }
    else if(position == 2){
        s->x2 = p.x;
        s->y2 = p.y;
    }
    else if(position == 3){
        s->x3 = p.x;
        s->y3 = p.y;
    }
    else{
        printf("Warning raised. Simplex couldn't be replaced.\n");
    }
}

void compress_simplex(struct simplex *s, int position){
    /*
    Compress the simplex with a factor of 2
    */
    if(position == 1){
        s->x2 = (s->x2 + s->x1)/2.0;
        s->y2 = (s->y2 + s->y1)/2.0;
        s->x3 = (s->x3 + s->x1)/2.0;
        s->y3 = (s->y3 + s->y1)/2.0;
    }
    else if(position == 2){
        s->x1 = (s->x1 + s->x2)/2.0;
        s->y1 = (s->y1 + s->y2)/2.0;
        s->x3 = (s->x3 + s->x2)/2.0;
        s->y3 = (s->y3 + s->y2)/2.0;
    }
    else if(position == 3){
        s->x1 = (s->x1 + s->x3)/2.0;
        s->y1 = (s->y1 + s->y3)/2.0;
        s->x2 = (s->x2 + s->x3)/2.0;
        s->y2 = (s->y2 + s->y3)/2.0;
    }
    else{
        printf("Warning raised. Simplex couldn't be replaced.\n");
    }
}

struct point calculate_reflexion(struct simplex *s, double value){
    /*
    Calculate a reflected point of the Simplex.
    Inputs:
        pointer to a struct simplex
        value: reflecion value, determines the width of the reflexion
    Return:
        struct point
    */
    struct point p;
    p.x = 1.5*(((s->x1 + s->x2 + s->x3)/3.0) - s->xMax)*(1.0 + value) + s->xMax;
    p.y = 1.5*(((s->y1 + s->y2 + s->y3)/3.0) - s->yMax)*(1.0 + value) + s->yMax;
    p.f = function(p.x, p.y);
    return p;
}

double calculate_average_edge_length(struct simplex *s){
    /*
    As a termination criterion the averge edge length of the simplex needs to be calculated
    */
    double l1, l2, l3;
    l1 = sqrt(pow(s->x1 - s->x2, 2) + pow(s->y1 - s->y2, 2));
    l2 = sqrt(pow(s->x2 - s->x3, 2) + pow(s->y2 - s->y3, 2));
    l3 = sqrt(pow(s->x1 - s->x3, 2) + pow(s->y1 - s->y3, 2));
    return (l1 + l2 + l3)/3.0;
}

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
