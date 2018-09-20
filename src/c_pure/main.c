
#include "koch_snow_flake.h"
#include "heart_curve.h"
#include "line.h"
#include "svpng.inc"
#include "light.h"

#define W 512
#define H 512

static char *image;

void savePic(char* picName, unsigned char* (* save)(),int alpha){
     FILE *fp = fopen(picName, "wb");
     image = save();
     svpng(fp, W, H, image, alpha);
    fclose(fp);
}
int main(void){
    // showKoch();
//    showHeartCharacter();
//    showHeartPattern();
    // show3DHeart();

//    savePic("heart_3d_test.png", save3DHeart, 1);

//    savePic("line_bresenham.png", drawLineWithSimpleBresenham, 0);

//    savePic("line_sample.png", drawLineWithSample, 0);

//    savePic("line_anti_aliasing.png", drawLineWithAntiAliasing, 0);

//    savePic("line_sdf.png", drawLineWithSDF, 0);

//    savePic("line_sdf_aabb.png", drawLineWithAABBSDF, 0);

//    savePic("line_stitch_heart.png", drawStitchHeart, 0);

//    savePic("light_basic.png", drawBasicLight, 0);

//    savePic("light_geomitry_basic.png", drawCSGLight, 0);

//    savePic("light_geometry_shape.png", drawShapes, 0);

//    savePic("light_m.png", drawM, 0);

//    savePic("light_gradient.png", drawGradient, 0);

//    savePic("light_reflect.png", drawReflect, 0);

    savePic("light_refract.png", drawRefract, 0);

    return 0;
}