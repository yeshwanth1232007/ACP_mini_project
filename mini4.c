#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 25
#define COLS 80

char picture[ROWS][COLS];

/* Initialize Picture */

void initializePicture()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            picture[i][j] = '_';
        }
    }
}

/* Display Picture */

void displayPicture()
{
    int i, j;

    printf("\n");

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", picture[i][j]);
        }

        printf("\n");
    }
}

/* Draw Point */

void drawPoint(int x, int y)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
    {
        picture[y][x] = '*';
    }
}

/* Draw Line */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps, i;

    float xIncrement, yIncrement;

    float x = x1;
    float y = y1;

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
            p = p + 2 * x + 1;
        }
        else
        {
            y--;

            p = p + 2 * (x - y) + 1;
        }
    }
}

/* Delete Object */

void deleteObject(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height; i++)
    {
        for(j = x; j < x + width; j++)
        {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
            {
                picture[i][j] = '_';
            }
        }
    }
}

/* Modify Object */

void modifyObject()
{
    int choice;

    printf("\n1. Line");
    printf("\n2. Rectangle");
    printf("\n3. Triangle");
    printf("\n4. Circle");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    initializePicture();

    if(choice == 1)
    {
        int x1, y1, x2, y2;

        printf("Enter new x1 y1 x2 y2: ");
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

        drawLine(x1, y1, x2, y2);
    }

    else if(choice == 2)
    {
        int x, y, width, height;

        printf("Enter new x y width height: ");
        scanf("%d%d%d%d", &x, &y, &width, &height);

        drawRectangle(x, y, width, height);
    }

    else if(choice == 3)
    {
        int x, y, size;

        printf("Enter new x y size: ");
        scanf("%d%d%d", &x, &y, &size);

        drawTriangle(x, y, size);
    }

    else if(choice == 4)
    {
        int xc, yc, r;

        printf("Enter new center x y radius: ");
        scanf("%d%d%d", &xc, &yc, &r);

        drawCircle(xc, yc, r);
    }
}

/* Main Function */

int main()
{
    int choice;

    initializePicture();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");

        printf("1. Add Line\n");
        printf("2. Add Rectangle\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Object\n");
        printf("6. Modify Object\n");
        printf("7. Display Picture\n");
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
            int x, y, width, height;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &width, &height);

            drawRectangle(x, y, width, height);
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
            int x, y, width, height;

            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &width, &height);

            deleteObject(x, y, width, height);
        }

        else if(choice == 6)
        {
            modifyObject();
        }

        else if(choice == 7)
        {
            displayPicture();
        }

        else if(choice == 8)
        {
            break;
        }

        else
        {
            printf("Invalid choice\n");
        }
    }

    return 0;
}

