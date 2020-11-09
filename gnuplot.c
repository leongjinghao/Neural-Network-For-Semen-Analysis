#include <stdlib.h>
#include <stdio.h>
#define NUM_POINTS 5

void main()
{
    double xvals[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double yvals[NUM_POINTS] = {5.0 ,3.0, 1.0, 3.0, 5.0};

    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */

    FILE * gnuplotPipe = _popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot '-' \n");
    int i;

    for (int i = 0; i < NUM_POINTS; i++)
    {
        fprintf(gnuplotPipe, "%g %g\n", xvals[i], yvals[i]);
    }

    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    getch();
    fclose(gnuplotPipe);

} 