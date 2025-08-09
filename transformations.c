#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "transformations.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
    size_t width = image->header->width;
    size_t height = image->header->height;
    size_t size = width * height;

    struct bmp_image* flipped = malloc(sizeof(struct bmp_image));
    if (flipped == NULL) {
        printf("Error\n");
        return NULL;
    }


    struct bmp_header* header = malloc(sizeof(struct bmp_header));
    if (header == NULL) {
        printf("Not BMP file\n");
        free(flipped);
        return NULL;
    }

    memcpy(header, image->header, sizeof(struct bmp_header));
    flipped->header = header;

    struct pixel* data = malloc(size * sizeof(struct pixel));
    if (data == NULL) {
        free(header);
        free(flipped);
        printf("dont got data\n");
        return NULL;
    }

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            
        }
    }
    flipped->data = data;
    return flipped;
}