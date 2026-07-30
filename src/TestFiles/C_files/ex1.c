void fun(int a, int b,int c,int d, int * r)
{
    int y, z, x, t, p, q,e;
    y = a & b;
    z = y & b;
    x = y & c;
    t = y & d;
    p = z & x;
    q = t & d;
    e = p & q;
    * r = e ^ q;
}