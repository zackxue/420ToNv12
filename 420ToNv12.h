//
//  420ToNv12.h
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___20ToNv12___20ToNv12__
#define ___20ToNv12___20ToNv12__

#include <stdio.h>

int planar_to_interleave
(
  const uint8_t *u,
  const uint8_t *v,
        uint8_t *out,
        uint32_t frame_sz
 );


#endif /* defined(___20ToNv12___20ToNv12__) */
