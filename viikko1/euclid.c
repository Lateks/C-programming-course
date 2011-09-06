long int gcd_rec(long int a, long int b)
{
    if (b == 0)
        return a;
    else
        return gcd_rec(b, a % b);
}

long int gcd_iter(long int a, long int b)
{
    while (b)
    {
        long int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
