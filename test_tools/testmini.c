/* testmini.c -- very simple test program for the miniLZO library

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2015 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
   http://www.oberhumer.com/opensource/lzo/
 */


#include <stdio.h>
#include <stdlib.h>


/*************************************************************************
// This program shows the basic usage of the LZO library.
// We will compress a block of data and decompress again.
//
// For more information, documentation, example programs and other support
// files (like Makefiles and build scripts) please download the full LZO
// package from
//    http://www.oberhumer.com/opensource/lzo/
**************************************************************************/

/* First let's include "minizo.h". */

#include "minilzo.h"


/* We want to compress the data block at 'in' with length 'IN_LEN' to
 * the block at 'out'. Because the input block may be incompressible,
 * we must provide a little more output space in case that compression
 * is not possible.
 */

#define IN_LEN      (128*1024ul)
#define OUT_LEN     (IN_LEN + IN_LEN / 16 + 64 + 3)
static unsigned char __LZO_MMODEL in  [ IN_LEN ];
static unsigned char __LZO_MMODEL out [ OUT_LEN ];


/* Work-memory needed for compression. Allocate memory in units
 * of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);


/*************************************************************************
//
**************************************************************************/

int main(int argc, char *argv[])
{
    int r;
    lzo_uint in_len;
    lzo_uint out_len;
    lzo_uint new_len;

    if (argc < 0 && argv == NULL)   /* avoid warning about unused args */
        return 0;
	FILE * fp_in , * fp_out;
    

/*
 * Step 1: initialize the LZO library
 */
    if (lzo_init() != LZO_E_OK)
    {
        printf("internal error - lzo_init() failed !!!\n");
        printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
        return 3;
    }


	fp_in=fopen(argv[2],"rb");
	fp_out=fopen(argv[3],"wb");
	r=-1;
	switch(argv[1][0]){
	case 'c':
		while(!feof(fp_in)){
			in_len = IN_LEN;
			lzo_memset(in,0,in_len);
			in_len=fread(in,1,in_len,fp_in);
			r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);
			if (r != LZO_E_OK)
			{
				/* this should NEVER happen */
				printf("internal error - compression failed: %d\n", r);
				goto error;
			}
			printf("compressed %lu bytes into %lu bytes\n",
				(unsigned long) in_len, (unsigned long) out_len);
			fwrite(out,1,out_len,fp_out);
		}
		break;
	case 'd':
		while(!feof(fp_in)){
			in_len = IN_LEN;
			lzo_memset(in,0,in_len);
			in_len=fread(in,1,in_len,fp_in);
			r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);
			if (r != LZO_E_OK)
			{
				/* this should NEVER happen */
				printf("internal error - compression failed: %d\n", r);
				goto error;
			}
			printf("compressed %lu bytes into %lu bytes\n",
				(unsigned long) in_len, (unsigned long) out_len);
			fwrite(out,1,out_len,fp_out);
		}
		break;
	default:break;
	}
	
error:
    fclose(fp_in);
    fclose(fp_out);
    return r;
    ///* check for an incompressible block */
    //if (out_len >= in_len)
    //{
        //printf("This block contains incompressible data.\n");
        //return 0;
    //}

///*
 //* Step 4: decompress again, now going from 'out' to 'in'
 //*/
    //new_len = in_len;
    //r = lzo1x_decompress(out,out_len,in,&new_len,NULL);
    //if (r == LZO_E_OK && new_len == in_len)
        //printf("decompressed %lu bytes back into %lu bytes\n",
            //(unsigned long) out_len, (unsigned long) in_len);
    //else
    //{
        ///* this should NEVER happen */
        //printf("internal error - decompression failed: %d\n", r);
        //return 1;
    //}

    //printf("\nminiLZO simple compression test passed.\n");
    //return 0;
}


/* vim:set ts=4 sw=4 et: */
