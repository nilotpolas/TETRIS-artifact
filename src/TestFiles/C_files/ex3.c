void fun(int a , int b, int d, int c,  int * w)
{
    int x;
    int y;
    int z;
    int p;
    int q;
    int r;
    int s;
    int t;
    int u;
    int v;
    int e;
    int f;
    int g;
    y = x & b;
    z = x & c;
    p = x & d;
    q = y & a;
    r = y & c;
    s = z & p;
    // e = 5 ^ r;
    f1(d,x, &g);
    u = s & d;
    v = s & g;
    t = r ^ v;
    f = u ^ v;
    *w = t & f;
}
void f1(int a, int b, int * c){
    c = a & b;
}