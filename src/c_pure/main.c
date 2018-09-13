
#include "koch_snow_flake.h"
#include "heart_curve.h"
#include "line.h"
#include "svpng.inc"

#define W 512
#define H 512

static char *image;

int main(void){
    // showKoch();
//    showHeartCharacter();
//    showHeartPattern();
    // show3DHeart();

    // FILE *fp = fopen("heart_3d_test.png", "wb");
    // image = save3DHeart();
    // svpng(fp, W, H, image, 1);

//    FILE *fp = fopen("line_bresenham.png", "wb");
//    image = drawLineWithSimpleBresenham();
//    svpng(fp, W, H, image, 0);

    // FILE *fp = fopen("line_sample_bresenham.png", "wb");
    // image = drawLineWithSampleBresenham();
    // svpng(fp, W, H, image, 0);

    FILE *fp = fopen("line_anti_aliasing_bresenham.png", "wb");
    image = drawLineWithAntiAliasing();
    svpng(fp, W, H, image, 0);

    fclose(fp);
    return 0;
}