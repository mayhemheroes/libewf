/*
 * libewf chunk cache
 *
 * Copyright (c) 2006, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the creator, related organisations, nor the names of
 *   its contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * - All advertising materials mentioning features or use of this software
 *   must acknowledge the contribution by people stated in the acknowledgements.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER, COMPANY AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LIBEWF_CHUNK_CACHE_H
#define _LIBEWF_CHUNK_CACHE_H

#include <inttypes.h>

#include "ewf_sectors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIBEWF_CHUNK_CACHE libewf_chunk_cache_t
#define LIBEWF_CHUNK_CACHE_SIZE sizeof( LIBEWF_CHUNK_CACHE )

typedef struct libewf_chunk_cache libewf_chunk_cache_t;

struct libewf_chunk_cache
{
	/* The amount of data in the chunk
	 */
	uint32_t amount;

	/* The read buffer
	 */
	EWF_SECTORS_CHUNK *read;

	/* The data buffer
	 */
	EWF_SECTORS_CHUNK *data;

	/* The identifier of the cached chunk
	 */
	uint32_t identifier;

	/* The allocated size of the cached chunk
	 */
	uint64_t allocated_size;
};

LIBEWF_CHUNK_CACHE *libewf_chunk_cache_alloc( uint32_t size );
LIBEWF_CHUNK_CACHE *libewf_chunk_cache_realloc( LIBEWF_CHUNK_CACHE *chunk_cache, uint32_t size );
void libewf_chunk_cache_free( LIBEWF_CHUNK_CACHE *chunk_cache );
LIBEWF_CHUNK_CACHE *libewf_chunk_cache_wipe( LIBEWF_CHUNK_CACHE *chunk_cache );

#ifdef __cplusplus
}
#endif

#endif

