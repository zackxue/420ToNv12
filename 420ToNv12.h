//
//  420ToNv12.h
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___420ToNv12___
#define ___420ToNv12___

#ifdef SSE
int planar_to_interleave
(
        uint32_t    wxh,
        uint64_t   *u_et_v,
  const uint64_t   *u,
  const uint64_t   *v
);
#else
int planar_to_interleave
(
        uint32_t    wxh,
        uint8_t    *u_et_v,
  const uint8_t    *u,
  const uint8_t    *v
);
#endif


#endif
