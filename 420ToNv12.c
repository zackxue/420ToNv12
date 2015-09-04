//
//  420ToNv12.c
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>

#define SSE

typedef char __attribute__((vector_size(8)))    v8qi;

#ifdef SSE
int planar_to_interleave
(
        uint32_t    wxh,
        uint64_t   *u_et_v,
  const uint64_t   *u,
  const uint64_t   *v
)
{
    int i;
    v8qi *res;
        
    res = (v8qi *) u_et_v;
        
    for (i = 0; i < wxh / 32; i++)
    {        
        res[0] = __builtin_ia32_punpcklbw( (v8qi) u[i], (v8qi) v[i]);
        res[1] = __builtin_ia32_punpckhbw( (v8qi) u[i], (v8qi) v[i]);
        
        res += 2;
    }
    
    return 0;
}
#else
int planar_to_interleave
(
        uint32_t    wxh,
        uint8_t    *u_et_v,
  const uint8_t    *u,
  const uint8_t    *v
)
{
    int i;

    for (i = 0; i < wxh / 4; i++)
    {
        uint8_t u_data = u[i];  // fetch u data
        uint8_t v_data = v[i];  // fetch v data
        
        u_et_v[2 * i]       = u_data;   // write u data
        u_et_v[2 * i + 1]   = v_data;   // write v data
    }

    return 0;
}
#endif
