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
    
    char *cp;
    char output_file_name[256];

    
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
    cp          = NULL;
    memset(output_file_name, 0, sizeof(output_file_name));
    
    // get input file name from comand line
    fd_in   = open(argv[1], O_RDONLY);
    
    // specify output file name
    cp = strchr(argv[1], '.');
    strncpy(output_file_name, argv[1], cp - argv[1]);
    strcat(output_file_name, "_nv12");
    strcat(output_file_name, cp);
    
    fd_out  = open(output_file_name, O_WRONLY | O_CREAT, S_IRUSR);
    
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
                frame_sz,
                buffer,
                u,
                v
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
    
    printf("Done\n");
    printf("Output file: %s\n", output_file_name);
    
    return 0;
}
