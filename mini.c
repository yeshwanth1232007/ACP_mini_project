#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 25
#define COLS 80

char screen[ROWS][COLS];

/* Initialize Screen */
void initialize()
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

/* Display Screen */
void display()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", screen[i][j]);
        }
        printf("\n");
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

/* Draw Diagonal Line */
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps, i;

    float xIncrement, yIncrement;
    float x = x1;
    float y = y1;

    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    for(i = 0; i <= steps; i++)
    {
        drawPoint((int)(x + 0.5), (int)(y + 0.5));

        x += xIncrement;
        y += yIncrement;
    }
}

/* Draw Rectangle */
void drawRectangle(int x, int y, int width, int height)
{
    int i;

    for(i = x; i < x + width; i++)
    {
        drawPoint(i, y);
        drawPoint(i, y + height - 1);
    }

    for(i = y; i < y + height; i++)
    {
        drawPoint(x, i);
        drawPoint(x + width - 1, i);
    }
}

/* Draw Triangle */
void drawTriangle(int x, int y, int size)
{
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = x - i; j <= x + i; j++)
        {
            drawPoint(j, y + i);
        }
    }
}

/* Draw Circle */
void drawCircle(int xc, int yc, int r)
{
    int x, y;

    for(y = -r; y <= r; y++)
    {
        for(x = -r; x <= r; x++)
        {
            if(x*x + y*y <= r*r)
            {
                drawPoint(xc + x, yc + y);
            }
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
                screen[i][j] = '_';
            }
        }
    }
}

/* Main Function */
int main()
{
    int choice;

    initialize();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Area\n");
        printf("6. Display Screen\n");
        printf("7. Clear Screen\n");
        printf("8. Exit\n");

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

            printf("Enter x y size: ");
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
            display();
        }

        else if(choice == 7)
        {
            initialize();
            printf("Screen Cleared!\n");
        }

        else if(choice == 8)
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
