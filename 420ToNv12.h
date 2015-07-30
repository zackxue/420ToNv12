//
//  420ToNv12.h
//  420ToNv12
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef __420ToNv12__
#define __420ToNv12__


int planar_to_interleave
(
  const uint8_t *u,
  const uint8_t *v,
        uint8_t *u_et_v,
        uint32_t frame_sz
 );


#endif
