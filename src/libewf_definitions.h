/*
 * Definitions for libewf
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

#ifndef _LIBEWF_DEFINIONS_H
#define _LIBEWF_DEFINIONS_H

#include <inttypes.h>

/* The minimum chunk size is 32k (32 * 1024)
 * 64 * 512 (64 sectors)
 */
#define EWF_MINIMUM_CHUNK_SIZE 32768

/* The possible EWF file formats
 */
#define EWF_FORMAT_E01	'e'
#define EWF_FORMAT_L01	'l'
#define EWF_FORMAT_S01	's'

/* Fix for systems without PRI definitions
 */
#ifndef PRIi8
	#define PRIi8 "i"
#endif

#ifndef PRIi16
	#define PRIi16 "i"
#endif

#ifndef PRIi32
	#define PRIi32 "i"
#endif

#ifndef PRIi64
#if __WORDSIZE == 64
	#define PRIi64 "li"
#else
	#define PRIi64 "lli"
#endif
#endif

#ifndef PRIu8
	#define PRIu8 "u"
#endif

#ifndef PRIu16
	#define PRIu16 "u"
#endif

#ifndef PRIu32
	#define PRIu32 "u"
#endif

#ifndef PRIu64
#if __WORDSIZE == 64
	#define PRIu64 "lu"
#else
	#define PRIu64 "llu"
#endif
#endif

#ifndef PRIx8
	#define PRIx8 "x"
#endif

#ifndef PRIx16
	#define PRIx16 "x"
#endif

#ifndef PRIx32
	#define PRIx32 "x"
#endif

#ifndef PRIx64
#if __WORDSIZE == 64
	#define PRIx64 "lx"
#else
	#define PRIx64 "llx"
#endif
#endif

#endif

