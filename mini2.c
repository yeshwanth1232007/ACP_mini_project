#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 100

char screen[ROWS][COLS];

/* Initialize Screen */
void initialize()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            screen[i][j] = ' ';
        }
    }
}

/* Draw Point */
void drawPoint(int x, int y)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
    {
        screen[y][x] = '*';
    }
}

/* Display Screen */
void display()
{
    int i, j;

    system("cls || clear");

    printf("\n");

    for(i = 0; i < COLS + 2; i++)
        printf("-");

    printf("\n");

    for(i = 0; i < ROWS; i++)
    {
        printf("|");

        for(j = 0; j < COLS; j++)
        {
            printf("%c", screen[i][j]);
        }

        printf("|\n");
    }

    for(i = 0; i < COLS + 2; i++)
        printf("-");

    printf("\n");
}

/* Draw Line using DDA */
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;
    float xInc, yInc;
    float x = x1;
    float y = y1;

    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xInc = dx / (float)steps;
    yInc = dy / (float)steps;

    for(int i = 0; i <= steps; i++)
    {
        drawPoint(round(x), round(y));

        x += xInc;
        y += yInc;
    }
}

/* Draw Rectangle */
void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);

    drawLine(x, y, x, y + height);

    drawLine(x + width, y, x + width, y + height);

    drawLine(x, y + height, x + width, y + height);
}

/* Draw Triangle */
void drawTriangle(int x, int y, int size)
{
    drawLine(x, y, x - size, y + size);

    drawLine(x, y, x + size, y + size);

    drawLine(x - size, y + size, x + size, y + size);
}

/* Draw Circle */
void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int p = 1 - r;

    while(x <= y)
    {
        drawPoint(xc + x, yc + y);
        drawPoint(xc - x, yc + y);
        drawPoint(xc + x, yc - y);
        drawPoint(xc - x, yc - y);

        drawPoint(xc + y, yc + x);
        drawPoint(xc - y, yc + x);
        drawPoint(xc + y, yc - x);
        drawPoint(xc - y, yc - x);

        x++;

        if(p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

/* Delete Area */
void deleteArea(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height; i++)
    {
        for(j = x; j < x + width; j++)
        {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
            {
                screen[i][j] = ' ';
            }
        }
    }
}

/* Modify Object */
void modifyObject()
{
    int type;

    printf("\nModify Which Object?\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");

    printf("Enter choice: ");
    scanf("%d", &type);

    if(type == 1)
    {
        int ox1, oy1, ox2, oy2;
        int nx1, ny1, nx2, ny2;

        printf("Enter OLD x1 y1 x2 y2: ");
        scanf("%d%d%d%d", &ox1, &oy1, &ox2, &oy2);

        deleteArea(
            (ox1 < ox2 ? ox1 : ox2),
            (oy1 < oy2 ? oy1 : oy2),
            abs(ox2 - ox1) + 2,
            abs(oy2 - oy1) + 2
        );

        printf("Enter NEW x1 y1 x2 y2: ");
        scanf("%d%d%d%d", &nx1, &ny1, &nx2, &ny2);

        drawLine(nx1, ny1, nx2, ny2);
    }

    else if(type == 2)
    {
        int ox, oy, ow, oh;
        int nx, ny, nw, nh;

        printf("Enter OLD x y width height: ");
        scanf("%d%d%d%d", &ox, &oy, &ow, &oh);

        deleteArea(ox, oy, ow + 1, oh + 1);

        printf("Enter NEW x y width height: ");
        scanf("%d%d%d%d", &nx, &ny, &nw, &nh);

        drawRectangle(nx, ny, nw, nh);
    }

    else if(type == 3)
    {
        int ox, oy, osize;
        int nx, ny, nsize;

        printf("Enter OLD x y size: ");
        scanf("%d%d%d", &ox, &oy, &osize);

        deleteArea(ox - osize, oy, osize * 2 + 2, osize + 2);

        printf("Enter NEW x y size: ");
        scanf("%d%d%d", &nx, &ny, &nsize);

        drawTriangle(nx, ny, nsize);
    }

    else if(type == 4)
    {
        int oxc, oyc, or;
        int nxc, nyc, nr;

        printf("Enter OLD center x y radius: ");
        scanf("%d%d%d", &oxc, &oyc, &or);

        deleteArea(
            oxc - or - 1,
            oyc - or - 1,
            or * 2 + 3,
            or * 2 + 3
        );

        printf("Enter NEW center x y radius: ");
        scanf("%d%d%d", &nxc, &nyc, &nr);

        drawCircle(nxc, nyc, nr);
    }

    else
    {
        printf("Invalid choice!\n");
    }
}

/* Main Function */
int main()
{
    int choice;

    initialize();

    while(1)
    {
        printf("\n========= 2D GRAPHICS EDITOR =========\n");

        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Area\n");
        printf("6. Modify Object\n");
        printf("7. Display Screen\n");
        printf("8. Clear Screen\n");
        printf("9. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
        }

        else if(choice == 2)
        {
            int x, y, w, h;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &w, &h);

            drawRectangle(x, y, w, h);
        }

        else if(choice == 3)
        {
            int x, y, size;

            printf("Enter top x y size: ");
            scanf("%d%d%d", &x, &y, &size);

            drawTriangle(x, y, size);
        }

        else if(choice == 4)
        {
            int xc, yc, r;

            printf("Enter center x y radius: ");
            scanf("%d%d%d", &xc, &yc, &r);

            drawCircle(xc, yc, r);
        }

        else if(choice == 5)
        {
            int x, y, w, h;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &w, &h);

            deleteArea(x, y, w, h);
        }

        else if(choice == 6)
        {
            modifyObject();
        }

        else if(choice == 7)
        {
            display();
        }

        else if(choice == 8)
        {
            initialize();

            printf("Screen Cleared!\n");
        }

        else if(choice == 9)
        {
            printf("Program Ended.\n");
            break;
        }

        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}