#include <cstdio>

bool compare(int l, int w, int r1, int r2)
{
    int lowest = l < w ? l : w;
    
    if (r1 * 2 > lowest || r2 * 2 > lowest)
        return false;
    
    int x = l - r1 - r2, y = w - r1 - r2, r = r1 + r2;
    
    if (x * x + y * y >= r * r)
    {
        return true;
    }
    
    return false;
}

int main()
{
    int l, w, r1, r2;
    
    while (scanf("%d %d %d %d", &l, &w, &r1, &r2), l)
    {
        if (compare(l, w, r1, r2))
            printf("S\n");
        else
            printf("N\n");
    }
}