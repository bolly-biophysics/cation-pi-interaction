#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define r 3.5

float x[60000], y[60000], z[60000];
float pi_center_x[1000], pi_center_y[1000], pi_center_z[1000];
float na_x[1000], na_y[1000], na_z[1000];
char atom[60000][30];

int main()
{
    int i,j,k,m,t,frame;
    float tmp_x,tmp_y,tmp_z;

    FILE *fp,*output;
    fp=fopen("xxx","r+");
    output=fopen("cation_pi.dat","w+");
    i=1; j=1; k=1; m=0; frame=0; tmp_x=0; tmp_y=0; tmp_z=0;

    while (!feof(fp))
    {
        if (fscanf(fp, "%s %f %f %f\n", atom[i], &x[i], &y[i], &z[i]) == 4);
        i++;
    }
    t=i;

    for (i = 1; i <= t; i++)
    {
        if (strcmp(atom[i], "N1") == 0)
        {
            tmp_x = x[i];
            tmp_y = y[i];
            tmp_z = z[i];
            continue;
        }
        if (strcmp(atom[i], "C4") == 0)
        {
            pi_center_x[j] = (x[i] + tmp_x) / 2;
            pi_center_y[j] = (y[i] + tmp_y) / 2;
            pi_center_z[j] = (z[i] + tmp_z) / 2;
            j++;
            continue;
        }
        if (strcmp(atom[i], "MG") == 0)
        {
            na_x[k] = x[i];
            na_y[k] = y[i];
            na_z[k] = z[i];
            k++;
        }
    }

    for (i = 1; i <= k - 1; i++)
    {
        for (m = 1; m <= j - 1; m++)
        {
            if (sqrt((na_x[i] - pi_center_x[m]) * (na_x[i] - pi_center_x[m]) + (na_y[i] - pi_center_y[m]) * (na_y[i] - pi_center_y[m]) + (na_z[i] - pi_center_z[m]) * (na_z[i] - pi_center_z[m])) <= r)
            {
                frame++;
                goto here;
            }
        }
        here:continue;
    }

    fprintf(output, "%4d%4d%4d", j - 1, k - 1, frame);

    if (frame >= 1)
        fprintf(output, "  xxx\n");
    else
        fprintf(output,"\n");

    fclose(fp);
    fclose(output);

    return 0;
}
