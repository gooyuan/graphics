
#include "heart_curve.h"
#include "pub.h"

/**
 * 心型曲线方程:
 * 三维: (x^2 + (9/4) * y^2 + z^2 - 1)^3 - x^2 * z^3 - (9/80) * y^2 * z^3 = 0
 * 二维: 令 y = 0 (为何不是z=0?) 这是算出来的, 按方程的参数来命名, 可以知道三维上的y表示的是深度
 *     (x^2 + z^2 - 1)^3 - x^2 * z^3 = 0
 */
void showHeartCharacter() {
    for (float y = 1.5f; y > -1.5f; y -= .1f) {
        for (float x = -1.5f; x < 1.5f; x += .05f) {
            float a = x * x + y * y - 1;
            float r = a * a * a - x * x * y * y * y;
            putchar(r <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
}

void showHeartPattern() {
    for (float y = 1.5f; y > -1.5f; y -= .1f) {
        for (float x = -1.5f; x < 1.5f; x += .05f) {
            float a = x * x + y * y - 1;
            float r = a * a * a - x * x * y * y * y;
//            printf("result %f", r);
            putchar(r <= 0.0f ? ".:-=+*#%@"[(int) (r * -8.0f)] : ' ');
        }
        putchar('\n');
    }

}

float heart3DFunction(float x, float y, float z) {
    float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
    return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

float heightRange(float x, float z) {
    for (float y = 1.0f; y >= 0.0f; y -= 0.001f) {
        if (heart3DFunction(x, y, z) <= 0.0f)
            return y;
    }
    return 0.0f;
}

void show3DHeart() {
    for (float z = 1.5f; z > -1.5f; z -= 0.05f) {
        for (float x = -1.5f; x < 1.5f; x += 0.025f) {
            float v = heart3DFunction(x, 0.0f, z);
            if (v <= 0.0f) {
                float y0 = heightRange(x, z);
                float ny = 0.01f;
                float nx = heightRange(x + ny, z) - y0;
                float nz = heightRange(x, z + ny) - y0;
                float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                putchar(".:-=+*#%@"[(int) (d * 5.0f)]);
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }

    // 保存图像
    save3DHeart();
}


char* save3DHeart() {
    // FILE *fp = fopen("heart_3d.png", "wb");
    int sw = 512, sh = 512;
    unsigned char rgba[sw * sh * 4], *p = rgba;
    for (int sy = 0; sy < sh; sy++) {
        float z = 1.5f - sy * 3.0f / sh;
        for (int sx=0; sx < sw; sx++) {
            float x = sx * 3.0f / sw - 1.5f;
            float v = heart3DFunction(x, 0.0f, z);
            int r = 0;
            if (v <= 0.0f) {
                float y0 = heightRange(x, z);
                float ny = 0.01f;
                float nx = heightRange(x + ny, z) - y0;
                float nz = heightRange(x, z + ny) - y0;
                float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
//                float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                float d = (float) ((nx + ny - nz) / sqrt(3) * nd * 0.5f + 0.5f);
                r = (int) (d * 255.0f);
            }
            *p++ = (unsigned char) r;                /* R */
            *p++ = (unsigned char) 0;                /* G */
            *p++ = 0;                             /* B */
            *p++ = (unsigned char) (255);    /* A */
        }
    }
    p = rgba;
    // svpng(fp, sw, sh, rgba, 1);
    // fclose(fp);
    return p;
}
