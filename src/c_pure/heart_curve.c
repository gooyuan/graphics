
#include "heart_curve.h"
#include <stdio.h>
/**
 * 心型曲线方程:
 * 三维: (x^2 + (9/4) * y^2 + z^2 - 1)^3 - x^2 * z^3 - (9/80) * y^2 * z^3 = 0
 * 二维: 令 y = 0 (为何不是z=0?) 这是算出来的, 按方程的参数来命名, 可以知道三维上的y表示的是深度
 *     (x^2 + z^2 - 1)^3 - x^2 * z^3 = 0
 */
void showHeartCharacter()
{
    for (float y = 1.5f; y > -1.5f; y -= .1f)
    {
        for (float x = -1.5f; x < 1.5f; x += .05f)
        {
            float a = x * x + y * y - 1;
            float r = a * a * a - x * x * y * y * y;
            putchar( r <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
}

void showHeartPattern()
{
    for (float y = 1.5f; y > -1.5f; y -= .1f)
    {
        for (float x = -1.5f; x < 1.5f; x += .05f)
        {
            float a = x * x + y * y - 1;
            float r = a * a * a - x * x * y * y * y;
            putchar( r <= 0.0f ? ".:-=+*#%@"[(int)(r * -8.0f)] : ' ');
        }
        putchar('\n');
    }

}