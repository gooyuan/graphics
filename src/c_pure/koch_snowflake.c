//
// Created by Administrator on 2018/9/1.
//
#include "koch_snow_flake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 竟然看不明白算法, 没心思去想, 那就就先抄吧
 */
static char *image;
static int x, y, w, h;

/**
 * 这种赋值方式, 能过指针来赋值
 * @param i 画布的坐标x
 * @param j 画布的坐标y
 * @param c 需要画的字符
 */
static void Put(int i, int j, char c) {
    // 这里就相当于公式咯? image + w * j + i
    char *p = image + j * w + i;
    if (*p == ' ' || *p == '_') {
        *p = c;
    }
}

static void KochCurve(int n, int dir) {
    if (n == 0) {
        switch (dir % 6) {
            case 0:
                Put(x++, y, '_');
                Put(x++, y, '_');
                break;
            case 1:
                Put(x++, y--, '/');
                break;
            case 2:
                Put(--x, y--, '\\');
                break;
            case 3:
                Put(--x, y, '_');
                Put(--x, y, '_');
                break;
            case 4:
                Put(--x, ++y, '/');
                break;
            case 5:
                Put(x++, ++y, '\\');
                break;
        }
    } else {
        KochCurve(n - 1, dir);
        KochCurve(n - 1, dir + 1);
        KochCurve(n - 1, dir + 5);
        KochCurve(n - 1, dir);
    }
}

void showKoch(){
    w = 2;
    h = 2;
    for (int n = 0; n < 5; n++) {
        image = (char *) malloc(w * h);
        memset(image, ' ', w * h);
        x = 0;
        y = h/4 - 1;
        KochCurve(n, 0);
        KochCurve(n, 4);
        KochCurve(n, 2);
        printf("\nn=%d\n\n", n);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                putchar(image[j * w + i]);
            }
            putchar('\n');
        }
        w *= 3;
        h = n == 0 ? 4 : h * 3;
        free(image);
    }
}

