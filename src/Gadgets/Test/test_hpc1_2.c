# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void HPC1(int a0, int a1, int b0, int b1, int *c0, int *c1, int r0, int p01){
  int b0_;
  int b1_;

  int r1;
  r1 = r0;
  
  b0_ = b0 ^ r0;
  b1_ = b1 ^ r1;

  int v00, v01, v10, v11;

  v00 = a0 & b0_;
  int t0, t1;
  
  t0 = a0 & b1_;
  v01 = p01 ^ t0;

  t1 = a1 & b0_;
  v10 = p01 ^ t1;

  *c0 = v00 ^ v01;
  
  v11 = a1 & b1_;
  *c1 = v10 ^ v11;

}
int main(){
    srand(time(NULL)); // Seed random number generator

    int a = 0; // Example input
    int b = 0; // Example input

    int a0, a1, b0, b1;
    a0 = rand();
    a1 = a ^ a0;

    b0 = rand();
    b1 = b ^ b0;
    int r0;

    r0 = rand();
    int p01;
    p01 = rand();

    int c0, c1;

    HPC1(a0, a1, b0, b1, &c0, &c1, r0, p01);
    
    printf("c = %d", c0 ^ c1);

}