/*
 * libewf offset table
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

#include <stdlib.h>

#include "libewf_common.h"
#include "libewf_notify.h"
#include "libewf_offset_table.h"

/* Allocates memory for a new offset table struct
 * Returns a pointer to the new instance, NULL on error
 */
LIBEWF_OFFSET_TABLE *libewf_offset_table_alloc( uint32_t size )
{
	LIBEWF_OFFSET_TABLE *offset_table = NULL;

	offset_table = (LIBEWF_OFFSET_TABLE *) libewf_alloc( LIBEWF_OFFSET_TABLE_SIZE );

	if( offset_table == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_alloc: unable to allocate offset table.\n" );

		return( NULL );
	}
	offset_table->file_descriptor = (int *) libewf_alloc_cleared( ( size * LIBEWF_OFFSET_TABLE_FILE_DESCRIPTOR_SIZE ), -1 );

	if( offset_table->file_descriptor == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_alloc: unable to allocate file descriptor.\n" );

		libewf_free( offset_table );

		return( NULL );
	}
	offset_table->compressed = (uint8_t *) libewf_alloc_cleared( ( size * LIBEWF_OFFSET_TABLE_COMPRESSED_SIZE ), -1 );

	if( offset_table->compressed == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_alloc: unable to allocate compressed.\n" );

		libewf_free( offset_table->file_descriptor );
		libewf_free( offset_table );

		return( NULL );
	}
	offset_table->offset = (uint64_t *) libewf_alloc_cleared( ( size * LIBEWF_OFFSET_TABLE_OFFSET_SIZE ), 0 );

	if( offset_table->offset == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_alloc: unable to allocate offset.\n" );

		libewf_free( offset_table->file_descriptor );
		libewf_free( offset_table->compressed );
		libewf_free( offset_table );

		return( NULL );
	}
	offset_table->size = (uint64_t *) libewf_alloc_cleared( ( size * LIBEWF_OFFSET_TABLE_SIZE_SIZE ), 0 );

	if( offset_table->size == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_alloc: unable to allocate size.\n" );

		libewf_free( offset_table->file_descriptor );
		libewf_free( offset_table->compressed );
		libewf_free( offset_table->offset );
		libewf_free( offset_table );

		return( NULL );
	}
	offset_table->amount = size;
        offset_table->last   = 0;

	return( offset_table );
}

/* Reallocates memory for the dynamic file descriptor, offset and size array
 * Returns a pointer to the instance, NULL on error
 */
LIBEWF_OFFSET_TABLE *libewf_offset_table_realloc( LIBEWF_OFFSET_TABLE *offset_table, uint32_t size )
{
	if( offset_table == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_realloc: invalid offset_table.\n" );

		return( NULL );
	}
	offset_table->file_descriptor = (int *) libewf_realloc_new_cleared( offset_table->file_descriptor, offset_table->amount, ( size * LIBEWF_OFFSET_TABLE_FILE_DESCRIPTOR_SIZE ), -1 );

	if( offset_table->file_descriptor == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_realloc: unable to allocate file_descriptor.\n" );

		return( NULL );
	}
	offset_table->compressed = (uint8_t *) libewf_realloc_new_cleared( offset_table->compressed, offset_table->amount, ( size * LIBEWF_OFFSET_TABLE_COMPRESSED_SIZE ), -1 );

	if( offset_table->compressed == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_realloc: unable to allocate compressed.\n" );

		return( NULL );
	}
	offset_table->offset = (uint64_t *) libewf_realloc_new_cleared( offset_table->offset, offset_table->amount, ( size * LIBEWF_OFFSET_TABLE_OFFSET_SIZE ), 0 );

	if( offset_table->offset == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_realloc: unable to allocate offset.\n" );

		return( NULL );
	}
	offset_table->size = (uint64_t *) libewf_realloc_new_cleared( offset_table->size, offset_table->amount, ( size * LIBEWF_OFFSET_TABLE_SIZE_SIZE ), 0 );

	if( offset_table->size == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_realloc: unable to allocate size.\n" );

		return( NULL );
	}
	offset_table->amount = size;

	return( offset_table );
}

/* Frees memory of a offset table struct including elements
 */
void libewf_offset_table_free( LIBEWF_OFFSET_TABLE *offset_table )
{
	if( offset_table == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_free: invalid offset table.\n" );

		return;
	}
	if( offset_table->file_descriptor != NULL )
	{
		libewf_free( offset_table->file_descriptor );
	}
	if( offset_table->compressed != NULL )
	{
		libewf_free( offset_table->compressed );
	}
	if( offset_table->offset != NULL )
	{
		libewf_free( offset_table->offset );
	}
	if( offset_table->size != NULL )
	{
		libewf_free( offset_table->size );
	}
	libewf_free( offset_table );
}

/* Sets the values for a specific offset
 * Returns a pointer to the instance, NULL on error
 */
LIBEWF_OFFSET_TABLE *libewf_offset_table_set_values( LIBEWF_OFFSET_TABLE *offset_table, uint32_t chunk, int file_descriptor, uint8_t compressed, uint64_t offset, uint64_t size )
{
	if( offset_table == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_offset_table_set_values: invalid offset table.\n" );

		return( NULL );
	}
	if( chunk > offset_table->amount )
	{
		LIBEWF_VERBOSE_PRINT( "libewf_offset_table_set_values: allocating additional offset table entries.\n" );

		offset_table = libewf_offset_table_realloc( offset_table, chunk );

		if( offset_table == NULL )
		{
			LIBEWF_WARNING_PRINT( "libewf_offset_table_set_values: unable to enlarge offset table.\n" );

			return( NULL );
		}
	}
	offset_table->file_descriptor[ chunk ] = file_descriptor;
	offset_table->compressed[ chunk ]      = compressed;
	offset_table->offset[ chunk ]          = offset;
	offset_table->size[ chunk ]            = size;

	return( offset_table );
}

