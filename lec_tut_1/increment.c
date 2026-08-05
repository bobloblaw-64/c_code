#include <stdio.h>

int main()
{
    int x, y;

// Post-increment

    x = 5;

    y = x++;

    printf("Post-increment (x++):\n");

    printf("x = %d, y = %d\n\n", x, y);

// Pre-increment

    x = 5;

    y = ++x;

    printf("Pre-increment (++x):\n");

    printf("x = %d, y = %d\n\n", x, y);

// Post-decrement

    x = 5;

    y = x--;

    printf("Post-decrement (x--):\n");

    printf("x = %d, y = %d\n\n", x, y);

// Pre-decrement

    x = 5;

    y = --x;

    printf("Pre-decrement (--x):\n");

    printf("x = %d, y = %d\n", x, y);

    return 0;


}  