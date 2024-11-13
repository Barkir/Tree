#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "ascii.h"

int bgra2char(char * x)
{
    unsigned int b = x[0] / 3, g = x[1] / 2, r = x[2] / 4;
    if (b + g + r < 20) return ' ';
    if (b + g + r < 50) return '.';
    if (b + g + r < 100) return '/';
    if (b + g + r < 150) return ';';
    if (b + g + r < 200) return 'g';
    if (b + g + r < 250) return 'H';
    if (b + g + r < 300) return '$';
    if (b + g + r < 350) return 'O';
    if (b + g + r < 400) return 'X';
    return '#';
}

int ShowAscii(char * filename)
{
    char command[300] = "";

    unsigned char * pic = (unsigned char *) calloc(PIC_SIZE * 2, sizeof(char));
    unsigned char * raw = (unsigned char *) calloc(PIC_SIZE * 2, sizeof(char));

    sprintf(command, "ffmpeg -i %s -s 200x200 -vf format=gray -filter:v format=pix_fmts=bgra -vcodec rawvideo -f rawvideo - > output.raw", filename);
    system(command);

    FILE * picf = fopen("output.raw", "rb");

    char * raww = (char *) raw;
    fread(raw, sizeof(char), PIC_SIZE, picf);

    for (int i = 0; i < PIC_SIZE - 4; i+=4)
    {
        pic[(i / 4) % (PIC_SIZE * 2)] = bgra2char(raww + i);

        if ((i / 4) % 200 == 0)
        {
            // pic[(i / 4) % (PIC_SIZE * 2)] = '\n';
            printf("\n");
        }
        if ((i / 4) % (PIC_SIZE * 2) == 0)
        {
            // system("clear");
            // printf("\033[999;999H\033[6n\n");
            printf("\n");
            usleep(60000);
            // system("clear");
        }

        printf("%c", pic[(i / 4) % (PIC_SIZE * 2)]);
    }

    printf("\n");
    free(pic);
    free(raw);
    fclose(picf);

    return 0;
}
