//
//  420ToNv12.c
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>

int planar_to_interleave
(
  const uint8_t *u,
  const uint8_t *v,
        uint8_t *u_et_v,
        uint32_t frame_sz
)
{
    int i;
    
    for (i = 0; i < frame_sz / 4; i++)
    {
        uint8_t u_data = u[i];  // fetch u data
        uint8_t v_data = v[i];  // fetch v data
        
        u_et_v[2 * i]       = u_data;   // write u data
        u_et_v[2 * i + 1]   = v_data;   // write v data
    }
    
    return 0;
}
