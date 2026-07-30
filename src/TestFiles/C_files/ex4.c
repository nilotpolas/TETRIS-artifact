void test(int a , int b, int c, int d,  int * w)
{
    int x;
    int y;
    x = a&b;
    y = c&d;
    *w = x ^ y;
}