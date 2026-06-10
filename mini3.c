#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 100

char screen[ROWS][COLS];

/* ---------- INITIALIZE SCREEN ---------- */

void initializeScreen()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            screen[i][j] = '_';
        }
    }
}

/* ---------- DRAW SINGLE POINT ---------- */

void drawPoint(int x, int y)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
    {
        screen[y][x] = '*';
    }
}

/* ---------- DISPLAY SCREEN ---------- */

void displayScreen()
{
    int i, j;

    system("cls || clear");

    printf("\n");

    for(i = 0; i < COLS + 2; i++)
    {
        printf("-");
    }

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
    {
        printf("-");
    }

    printf("\n");
}

/* ---------- DRAW LINE ---------- */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;
    float xIncrement;
    float yIncrement;

    float x = x1;
    float y = y1;

    int i;

    if(abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    for(i = 0; i <= steps; i++)
    {
        drawPoint(round(x), round(y));

        x += xIncrement;
        y += yIncrement;
    }
}

/* ---------- DRAW RECTANGLE ---------- */

void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);

    drawLine(x, y, x, y + height);

    drawLine(x + width, y, x + width, y + height);

    drawLine(x, y + height, x + width, y + height);
}

/* ---------- DRAW TRIANGLE ---------- */

void drawTriangle(int x, int y, int size)
{
    drawLine(x, y, x - size, y + size);

    drawLine(x, y, x + size, y + size);

    drawLine(x - size, y + size, x + size, y + size);
}

/* ---------- DRAW CIRCLE ---------- */

void drawCircle(int xc, int yc, int radius)
{
    int x = 0;
    int y = radius;

    int p = 1 - radius;

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
            p = p + 2 * x + 1;
        }
        else
        {
            y--;

            p = p + 2 * (x - y) + 1;
        }
    }
}

/* ---------- DELETE AREA ---------- */

void deleteArea(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height; i++)
    {
        for(j = x; j < x + width; j++)
        {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
            {
                screen[i][j] = '_';
            }
        }
    }
}

/* ---------- MODIFY OBJECT ---------- */

void modifyObject()
{
    int choice;

    printf("\nMODIFY MENU\n");

    printf("1. Modify Line\n");
    printf("2. Modify Rectangle\n");
    printf("3. Modify Triangle\n");
    printf("4. Modify Circle\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    /* MODIFY LINE */

    if(choice == 1)
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

    /* MODIFY RECTANGLE */

    else if(choice == 2)
    {
        int ox, oy, ow, oh;
        int nx, ny, nw, nh;

        printf("Enter OLD x y width height: ");
        scanf("%d%d%d%d", &ox, &oy, &ow, &oh);

        deleteArea(ox, oy, ow + 2, oh + 2);

        printf("Enter NEW x y width height: ");
        scanf("%d%d%d%d", &nx, &ny, &nw, &nh);

        drawRectangle(nx, ny, nw, nh);
    }

    /* MODIFY TRIANGLE */

    else if(choice == 3)
    {
        int ox, oy, osize;
        int nx, ny, nsize;

        printf("Enter OLD x y size: ");
        scanf("%d%d%d", &ox, &oy, &osize);

        deleteArea(
            ox - osize,
            oy,
            osize * 2 + 2,
            osize + 2
        );

        printf("Enter NEW x y size: ");
        scanf("%d%d%d", &nx, &ny, &nsize);

        drawTriangle(nx, ny, nsize);
    }

    /* MODIFY CIRCLE */

    else if(choice == 4)
    {
        int oxc, oyc, oradius;
        int nxc, nyc, nradius;

        printf("Enter OLD center x y radius: ");
        scanf("%d%d%d", &oxc, &oyc, &oradius);

        deleteArea(
            oxc - oradius - 1,
            oyc - oradius - 1,
            oradius * 2 + 3,
            oradius * 2 + 3
        );

        printf("Enter NEW center x y radius: ");
        scanf("%d%d%d", &nxc, &nyc, &nradius);

        drawCircle(nxc, nyc, nradius);
    }

    else
    {
        printf("Invalid choice!\n");
    }
}

/* ---------- MAIN FUNCTION ---------- */

int main()
{
    int choice;

    initializeScreen();

    while(1)
    {
        printf("\n========== 2D GRAPHICS EDITOR ==========\n");

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

        /* DRAW LINE */

        if(choice == 1)
        {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
        }

        /* DRAW RECTANGLE */

        else if(choice == 2)
        {
            int x, y, width, height;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &width, &height);

            drawRectangle(x, y, width, height);
        }

        /* DRAW TRIANGLE */

        else if(choice == 3)
        {
            int x, y, size;

            printf("Enter top x y size: ");
            scanf("%d%d%d", &x, &y, &size);

            drawTriangle(x, y, size);
        }

        /* DRAW CIRCLE */

        else if(choice == 4)
        {
            int xc, yc, radius;

            printf("Enter center x y radius: ");
            scanf("%d%d%d", &xc, &yc, &radius);

            drawCircle(xc, yc, radius);
        }

        /* DELETE AREA */

        else if(choice == 5)
        {
            int x, y, width, height;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &width, &height);

            deleteArea(x, y, width, height);
        }

        /* MODIFY OBJECT */

        else if(choice == 6)
        {
            modifyObject();
        }

        /* DISPLAY SCREEN */

        else if(choice == 7)
        {
            displayScreen();
        }

        /* CLEAR SCREEN */

        else if(choice == 8)
        {
            initializeScreen();

            printf("Screen Cleared Successfully!\n");
        }

        /* EXIT */

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

