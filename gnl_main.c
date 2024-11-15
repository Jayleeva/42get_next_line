#include <unistd.h>

void    putchar_(char c)
{
    write(1, &c, 1);
}

void    putstr_(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        putchar_(str[i]);
        i ++;
    }
}

int main(int argc, char *argv)
{
    //tester de rediriger stdin 
    int file_descriptor;

    if (argc > 1)
        file_descriptor = argv[1];

    while ()
    {
        putstr_(get_next_line(file_descriptor));
    }
    return (0);
}
