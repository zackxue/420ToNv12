//
//  main.c
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "420ToNv12.h"
#define TIMING  1
#if (TIMING)
struct timeval tv1, tv2;
#endif

int main(int argc, const char * argv[]) {
    int fd_rd;
    int fd_wr;
    
    uint8_t *y;
    uint8_t *u;
    uint8_t *v;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    
    uint8_t *frame;
    uint8_t *dst;
    
    char *cp;
    char output_file_name[256];

    
    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }
    
    
    rd_sz   = 0;
    width   = 0;
    height  = 0;
    wxh     = 0;
    frame   = NULL;
    dst     = NULL;
    cp      = NULL;
    memset(output_file_name, 0, sizeof(output_file_name));
    
    // get input file name from comand line
    fd_rd = open(argv[1], O_RDONLY);
    
    // specify output file name
    cp = strchr(argv[1], '.');
    strncpy(output_file_name, argv[1], cp - argv[1]);
    strcat(output_file_name, "_nv12");
    strcat(output_file_name, cp);
    
    fd_wr = open
            (
             output_file_name,
             O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR
            );
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    wxh = width * height;
    
    frame = malloc(wxh * 3 / 2);
    dst = malloc(wxh / 2);
    
    y = frame;
    u = y + wxh;
    v = u + wxh / 4;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(fd_rd, frame, wxh * 3 / 2);
        
        if (rd_sz == wxh * 3 / 2)
        {
            write(fd_wr, y, wxh);
            #if (TIMING)
            gettimeofday(&tv1, NULL);
            #endif
            planar_to_interleave
            (
                wxh,
                dst,
                u,
                v
            );
            #if (TIMING)
            gettimeofday(&tv2, NULL);
            printf ("Total time = %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));
            #endif
            write(fd_wr, dst, wxh / 2);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    
    close(fd_rd);
    close(fd_wr);
    
    printf("Done\n");
    printf("Output file: %s\n", output_file_name);
    
    return 0;
}
