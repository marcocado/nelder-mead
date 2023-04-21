/*
Initialsation of the Simplex with a simplex rectangular triangle. Side length as an input.
*/
void initialize_simplex(struct simplex *s, double step_width){
    s->x2 = s->x1 + step_width;
    s->x3 = s->x1;
    s->y2 = s->y1;
    s->y3 = s->y1 + step_width;
    s->f1 = function(s->x1, s->y1);
    s->f2 = function(s->x2, s->y2);
    s->f3 = function(s->x3, s->y3);
}

/*
Print all Points of the Simplex to a file
*/
void print_simplex(struct simplex *s, FILE *fp){
    fprintf(fp, "%.2f, %.2f, %.2f, ", s->x1, s->y1, s->f1);
    fprintf(fp, "%.2f, %.2f, %.2f, ", s->x2, s->y2, s->f2);
    fprintf(fp, "%.2f, %.2f, %.2f\n", s->x3, s->y3, s->f3);
}

void calculate_simplex(struct simplex *s){
    s->f1 = function(s->x1, s->y1);
    s->f2 = function(s->x2, s->y2);
    s->f3 = function(s->x3, s->y3);
}

/*
Calculate the Maximum and Minimum Point of the Simplex. Write the variables into the
Data Structure of the Simplex
*/
void sort_simplex(struct simplex *s){
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

/*
Replace a Simplex Point with a Point
Inputs:
    pointer to a struct simplex
    struct point
    position: to know which point you want to change
*/
void replace_simplex_point(struct simplex *s, struct point p, int position){
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

/*
Compress the simplex with a factor of 2
*/
void compress_simplex(struct simplex *s, int position){
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

/*
As a termination criterion the averge edge length of the simplex needs to be calculated
*/
double calculate_average_edge_length(struct simplex *s){
    double l1, l2, l3;
    l1 = sqrt(pow(s->x1 - s->x2, 2) + pow(s->y1 - s->y2, 2));
    l2 = sqrt(pow(s->x2 - s->x3, 2) + pow(s->y2 - s->y3, 2));
    l3 = sqrt(pow(s->x1 - s->x3, 2) + pow(s->y1 - s->y3, 2));
    return (l1 + l2 + l3)/3.0;
}

/*
Calculate a reflected point of the Simplex.
Inputs:
    pointer to a struct simplex
    value: reflecion value, determines the width of the reflexion
Return:
    struct point
*/
struct point calculate_reflexion(struct simplex *s, double value){
    struct point p;
    p.x = 1.5*(((s->x1 + s->x2 + s->x3)/3.0) - s->xMax)*(1.0 + value) + s->xMax;
    p.y = 1.5*(((s->y1 + s->y2 + s->y3)/3.0) - s->yMax)*(1.0 + value) + s->yMax;
    p.f = function(p.x, p.y);
    return p;
}