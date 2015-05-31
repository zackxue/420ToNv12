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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "420ToNv12.h"

int main(int argc, const char * argv[]) {
    int fd_in;
    int fd_out;
    
    uint8_t *y;
    uint8_t *u;
    uint8_t *v;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t frame_sz;
    
    uint8_t *frame;
    uint8_t *buffer;
    
    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }
    
    
    rd_sz       = 0;
    width       = 0;
    height      = 0;
    frame_sz    = 0;
    frame       = NULL;
    buffer      = NULL;
    
    
    // get input file name from comand line
    fd_in   = open(argv[1], O_RDONLY);
    
    // specify output file name
    fd_out  = open("nv12.yuv", O_WRONLY | O_CREAT);
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    frame_sz = width * height;
    
    frame = malloc(frame_sz * 3 / 2);
    buffer = malloc(frame_sz / 2);
    
    y = frame;
    u = y + frame_sz;
    v = u + frame_sz / 4;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(fd_in, frame, frame_sz * 3 / 2);
        
        if (rd_sz == frame_sz * 3 / 2)
        {
            write(fd_out, y, frame_sz);
            
            planar_to_interleave
            (
                u,
                v,
                buffer,
                frame_sz
            );
            
            write(fd_out, buffer, frame_sz / 2);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    close(fd_in);
    close(fd_out);
    
    printf("\n");
    
    return 0;
}
