void sbox(int a , int b, int c, int * w)
{
    int x;
    x=a&b;
    *w=x&c;
}