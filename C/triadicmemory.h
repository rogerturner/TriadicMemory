/*
triadicmemory.h

C-language reference implementation of Triadic Memory and related algorithms published in
   https://github.com/PeterOvermann/Writings/blob/main/TriadicMemory.pdf

Copyright (c) 2022 Peter Overmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



// ---------- SDR data type and utility functions ----------

	
typedef struct
	{
	int 	*a,	// indices of non-zero positions, stored in array of size n
		n,	// SDR dimension
		p; 	// number of non-zero positions
	} SDR;
	

SDR *sdr_new (int n);				// SDR constructor
void sdr_delete(SDR *);				// destructor

SDR *sdr_random (SDR*, int p);			// random generator
SDR *sdr_noise (SDR*, int bits);		// add/remove random bits


SDR *sdr_set( SDR *x, SDR *y); 			// copy y to x
SDR *sdr_rotateright( SDR *x ); 		// shift x right by one bit
SDR *sdr_rotateleft( SDR *x ); 			// shift x left by one bit
SDR *sdr_or (SDR*res, SDR *x, SDR *y);		// store bit-wise OR of x and y and res

int  sdr_equal( SDR*x, SDR*y); 			// whether x and y are identical
int  sdr_distance( SDR*x, SDR*y); 		// Hamming distance
int  sdr_overlap( SDR*x, SDR*y); 		// number of common bits

void sdr_print(SDR *);				// print SDR followed by newline (values 1 to N)
void sdr_print0(SDR *);				// print SDR followed by newline (values 0 to N-1)


#define TMEMTYPE unsigned char


// ---------- Dyadic Memory (stores hetero-associations x-> y) ----------



typedef struct
	{
		
	TMEMTYPE* m;
	int 	nx,	// dimension of x
		ny,	// dimension of y
		p; 	// target sparsity of y in query
	
	} DyadicMemory;


DyadicMemory *dyadicmemory_new(int nx, int ny, int p);

void dyadicmemory_write 	(DyadicMemory *, SDR *, SDR *);
void dyadicmemory_delete 	(DyadicMemory *, SDR *, SDR *);
SDR* dyadicmemory_read 		(DyadicMemory *, SDR *, SDR *);


// AsymmetricDyadicMemory has been deprecated to avoid code duplication
// DyadicMemory now includes the asymmetric case




// ---------- Monadic Memory (stores autoassociations) ----------


typedef struct
	{
	DyadicMemory *D1, *D2;
	SDR *h, *r;
	int items;
	} MonadicMemory;


MonadicMemory* monadicmemory_new (int n, int p);	// constructor
SDR* monadicmemory (MonadicMemory *, SDR *);		// store and recall




// ---------- Triadic Memory (stores triple associations (x,y,z} ) ----------


typedef struct
	{
	TMEMTYPE* m;
	int n, p;
	} TriadicMemory;

TriadicMemory *triadicmemory_new(int n, int p);

void triadicmemory_write   (TriadicMemory *, SDR *, SDR *, SDR *);
void triadicmemory_delete  (TriadicMemory *, SDR *, SDR *, SDR *);

SDR* triadicmemory_read_x  (TriadicMemory *, SDR *, SDR *, SDR *);
SDR* triadicmemory_read_y  (TriadicMemory *, SDR *, SDR *, SDR *);
SDR* triadicmemory_read_z  (TriadicMemory *, SDR *, SDR *, SDR *);




// ---------- Command Line Functions ----------

char* sdr_parse (char *buf, SDR *s);

