#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void exact(float *o1, float *o2, float *od, float *os, float *oe, float nn, int key);

//==========================================================
void exact(float *o1, float *o2, float *od, float *os, float *oe, float nn, int key)
{
  *o1 /= nn;
  *o2 /= (nn-1);
  *od = (*o2) - (*o1)*(*o1)*nn/(nn-1);
  *os = sqrt(*od);
  *oe = (*os)/sqrt(nn);
  if (key) printf("middle=%f;   sgm=%f;   exact=%f  nn=%.f\n",*o1,*os,*oe,nn);
}
//=========================================================
