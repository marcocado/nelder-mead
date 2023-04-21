/*
Data Structure for the Simplex
- contains all edge points of the simplex
- contains all information about the minimum and maximum point of the simplex
*/
struct simplex {
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

/*
Data Structure for all Points
*/
struct point {
    double x;
    double y;
    double f;
};