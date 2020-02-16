#include<stdio.h>
#include<math.h>

float f(float x) {
   return x*log10(x) - 1.2;
}

float df(float x) {
   return log10(x) + 0.43429;
}

int main() {
   int itr, maxmitr;
   float h, x0, x1, allerr;
   printf("\nForneça x0, erro permitido e número máximo de iterações\n");
   scanf("%f %f %d", &x0, &allerr, &maxmitr);
   for (itr=1; itr<=maxmitr; itr++){
      h=f(x0)/df(x0);
      x1=x0-h;
      printf(" Na iteração %3d, x = %9.6f\n", itr, x1);
      if (fabs(h) < allerr) {
         printf("Após %3d iterações, raiz = %8.6f\n", itr, x1);
         return 0;
      }
      x0 = x1;
   }
   printf(" A solução esperada não converge ou as iterações não são suficientes\n");
   return 1;
}
