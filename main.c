#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"
#include "transformations.h"

int main() {
    FILE* f = fopen("./assets/adventurer.bmp", "rb");
    if (f == NULL){
        printf("Error in opening\n");
        return 1;
    }

    struct bmp_image* image = read_bmp(f);
    if (image == NULL) {
        printf("Failed to read BMP image\n");
        return 1;
    }

    struct bmp_image* flipped = flip_horizontally(image);
    if (flipped == NULL) {
        printf("Failed to flip the image\n");
        free_bmp_image(image);
        return 1;
    }

    FILE* o = fopen("Copyed_adventurere.bmp", "wb");
    if(o ==NULL) {
        free_bmp_image(image);
        free_bmp_image(flipped);
        printf("Error opening\n");
        return 1;
    }

    bool result = write_bmp(o, image);
    if(result)
    fclose(o);

    if (!result) {
        printf("Failed to write flipped image\n");
        free_bmp_image(image);
        free_bmp_image(flipped);
        return 1;
    }

    free_bmp_image(image);
    free_bmp_image(flipped);

    fclose(f);



    return 0;
}