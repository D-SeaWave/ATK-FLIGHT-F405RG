#include <string.h>
#include <main.h>

int main(void)
{
    unsigned int count;

    count = 0;
    while (1) {
        printf("count = %u\r\n", ++count);
    }

    return 0;
}
