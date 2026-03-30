#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define m 15
#define n 15
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define EDA '@'
#define HEAD 'O'
#define BODY 'o'
#define TAIL '*'
#define BOR '%'

char z[n+2][m+2];
char dz[n+2][m+2];
char hx,hy,nd;

/* dz - number: 1,3,4,5,7
   dx = (dz%3)-1
   dy = ((dz/3)%3)-1
   dz dx dy
    1  0 -1 UP
    3 -1  0 LEFT
    4  0  0
    5  1  0 RIGHT
    7  0  1 DOWN     */

void feed() {
    char x0=1,y0=1,x,y;
    x0+=rand()%(m+1);
    y0+=rand()%(n+1);
    x=x0;
    y=y0;
    if (z[y][x]!=' ') {
        do {
            do {
                x++;
            } while ((z[y][x]!=' ') && (z[y][x]!=BOR));
            if (z[y][x]==BOR) {
                x=1;
                y++;
            }
        } while ((z[y][x]!=' ') && (y!=n+2));
        if (y==n+2) {
            y=1;
            x=0;
            do {
                do {
                    x++;
                    if ((y==y0) && (x==x0)) {
                        break;
                    }
                } while ((z[y][x]!=' ') && (z[y][x]!=BOR));
                if (z[y][x]==BOR) {
                    x=1;
                    y++;
                }
            } while ((z[y][x]!=' ') && ((y!=y0) || (x!=x0)));
        }
        if ((y==y0) && (x==x0)) {
            draw();
            printf("\nVICTORY\n");
            Sleep(1000);
            exit(2);
        }
    }
    z[y][x]=EDA;
}

void move() {
    int dx,dy,x,y;
    dx=(nd%3)-1;
    dy=((nd/3)%3)-1;
    if (z[hy+dy][hx+dx]==' ') {
        x=hx;
        y=hy;
        hy+=dy;
        hx+=dx;
        z[hy][hx]=HEAD;
        if (dz[y][x]!=4)
            dz[hy][hx]=8-nd;
        while (dz[y][x]!=4) {
            dx=(dz[y][x]%3)-1;
            dy=((dz[y][x]/3)%3)-1;
            z[y][x]=z[y+dy][x+dx];
            if (dz[y+dy][x+dx]==4 )
                dz[y][x]=4;
            y+=dy;
            x+=dx;
        }
        z[y][x]=' ';
    }
    else if (z[hy+dy][hx+dx]==EDA) {
        z[hy+dy][hx+dx]=HEAD;
        if (dz[hy][hx]==4) {
            z[hy][hx]=TAIL;
        } else {
            z[hy][hx]=BODY;
        }
        hy+=dy;
        hx+=dx;
        dz[hy][hx]=8-nd;
        feed();
    } else {
        printf("\nLOSER\n");
        Sleep(1000);
        exit(0);
    }
}

void draw() {
    char i,j;
    system("cls");
    for (i=0; i<n+2; i++) {
        for (j=0; j<m+2; j++)
            printf("%c",z[i][j]);
        printf("\n");
    }
    Sleep(500);
}

int main() {
    char i,j,x,y,c;
    for (i=0; i<n+2; i++)
        for (j=0; j<m+2; j++) {
            z[i][j]=' ';
            dz[i][j]=4;
        }
    for (i=0; i<n+2; i++)
        z[i][0]=z[i][m+1]=BOR;
    for (j=0; j<m+2; j++)
        z[0][j]=z[n+1][j]=BOR;
    hx=m/2+1;
    hy=n/2+1;
    z[hy][hx]=HEAD;
    draw();
    nd=3;
    feed();
    while (1) {
        move();
        draw();
        if (kbhit()) {
            c=getch();
            if (c==UP)
                nd=1;
            if (c==DOWN)
                nd=7;
            if (c==RIGHT)
                nd=5;
            if (c==LEFT)
                nd=3;
        }
    }
    return 0;
}
