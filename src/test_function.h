/*
Himmelblau Function: f(x, y) = (x^2 + y - 11)^2 + (x + y^2 - 7)^2
*/
double function(double x, double y){
    return pow((pow(x, 2) + y - 11), 2) + pow((x + pow(y, 2) -7), 2);
}