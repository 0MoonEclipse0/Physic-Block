/* Util.c defining Functions of util.h */

/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Function to read a shader-file */
const char* readShader(const char* shaderfile,char buf[] , int bufsize) 
{      

    FILE* f = fopen(shaderfile, "r");
    if (NULL == f) {
        fprintf(stderr, "Couldn't open Shader file: %s\n", shaderfile);
        return NULL;
    }

    size_t bytesRead = fread(buf, 1, bufsize - 1, f);
    buf[bytesRead] = '\0';

    fclose(f);
    return buf;
}