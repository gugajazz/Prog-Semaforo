#include <stdio.h>

typedef struct
{
    int    a;
    double b;
} TestStruct;

int main(void)
{
    /*FILE *file = fopen("test", "wb");

    TestStruct ts;
    ts.a = 105;
    ts.b = 194.543;

    fwrite(&ts, sizeof(TestStruct), 1, file);
    fclose(file); */

    FILE *file = fopen("test", "rb");

    TestStruct ts;

    fread(&ts, sizeof(TestStruct), 1, file);
    fclose(file);

    printf("ts.a = %d\nts.b = %f\n", ts.a, ts.b);
}