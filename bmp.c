#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream)
{
    if (stream == NULL) {
        return NULL;
    }

    struct bmp_header* header = malloc(sizeof(struct bmp_header));
    if (header == NULL) return NULL;

    size_t result = fread(header, sizeof(struct bmp_header), 1, stream);
    if (result == 0) {
        free(header);
        return NULL;
    } 
    if (header -> type != 0x4D42) { // error: comparison between pointer and integer
        free(header);
        printf("Error: not a Bmp file\n");
        return NULL;
    }

    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header)
{
    if ((stream == NULL) || (header == NULL)) return NULL;

    size_t size = header -> width * header -> height;
    struct pixel* data = malloc(size * sizeof(struct pixel));
    if (data == NULL) return NULL;

    fread(data, sizeof(struct pixel), size, stream);

    return data;
}

struct bmp_image* read_bmp(FILE* stream)
{
    struct bmp_header* header = read_bmp_header(stream);
    if (header == NULL){
        printf("dont got header\n");
        return NULL;
    }

    struct pixel* data = read_data(stream, header);
    if (data == NULL) {
        printf("dont got data\n");
        return NULL;
    }

    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    if (image == NULL) {
        printf("problem during openning image\n");
        free(header);
        free(data);
        return NULL;
    }

    image -> header = header;
    image -> data = data;

    return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image ) {
    if ((stream == NULL) || (image == NULL))return NULL;

    size_t size = image->header->width * image->header-> height;

    fwrite(image->header, sizeof(struct bmp_header), 1, stream);
    fwrite(image->data, sizeof(struct pixel), size, stream);

    return true;
}

void free_bmp_image(struct bmp_image* image) {
    if (image == NULL) return;
    free(image->data);
    free(image->header);
    free(image);
}
