int x = 0;

union t
{
    int m, n;
} temp;

int add(int a, int b)
{
    int c = a + b;
    return c;
}

int main()
{
    int i, j;
    union t t1, t2;
    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            int m = add(i, j);
        }
    }

    float t0;

    add(t1.m, t2.n);
}