//////////////////////////////////////////////////////////////////////////////
//
// RandomizedTSSequence_base_2.C, 8.8.99, Ilja Friedel
//
//////////////////////////////////////////////////////////////////////////////
//
// Status: tested
//
//////////////////////////////////////////////////////////////////////////////


#include "RandomizedTSSequence.h"
#include <limits>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

RandomizedTSSequence_base_2::RandomizedTSSequence_base_2(C_matrix * C, 
							 UL_int len, Rng * rng_ptr):RandomizedTSSequence(C->dimension,rng_ptr)
{
   init(C,C->dimension,len,0);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

RandomizedTSSequence_base_2::RandomizedTSSequence_base_2(C_matrix * C,UL_int dim,UL_int len,Rng * rng_ptr):RandomizedTSSequence(dim,rng_ptr)
{
   init(C,dim,len,0);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

RandomizedTSSequence_base_2::RandomizedTSSequence_base_2(C_matrix * C,
							 UL_int dim,
							 UL_int len, 
							 UL_int LSS_flag,
							 Rng * rng_ptr):RandomizedTSSequence(dim,rng_ptr)
{
   init(C,dim,len,LSS_flag);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RandomizedTSSequence_base_2::init(C_matrix * C, 
				       UL_int dim, 
				       UL_int len, 
				       UL_int LSS_flag)
{
   UL_int akdim,k;
   DigitalSequence_base_2 * GEN;

   n        =  0;
   n0       =  0;
   base     =  C->R->base;
   if(base!=2) 
     {
       cerr << "Error: Ring->base not equal to 2! ";
       cerr << "(RandomizedTSSequence_base_2::RandomizedTSSequence_base_2())";
       cerr << endl;
       exit(1);
     }

   length                      = len;
   NumDigits                   = 32;
   inv_Max_int                 = 1.0/4294967296.0;
   //dimension                   = dim; // is set in Sequence(dim);
   Component_of_LatinSupercube = LSS_flag;

//////////////////////////////////////////////////////////////////////////////

   GEN=new DigitalSequence_base_2(C, rng);
   if(!(GEN))
     {
       cerr << "Error: Out of memory! (RandomizedTSSequence_base_2";
       cerr << "::RandomizedTSSequence_base_2():1)" << endl;
       exit(1);
     }

   get_memory(dimension,length);

   for(k=0;k<length;k++)
     {
       for(akdim=0;akdim<dim;akdim++)
	 {
	   (Seq[akdim])[k]=GEN->query_bitmap(akdim);
	   (P  [akdim])[k]=k;
	 }
       ++(*GEN);
     }
   delete GEN;
   GEN=NULL;

//////////////////////////////////////////////////////////////////////////////

   sort_sequence_and_generate_permutation();
   calc_changing_digits();
   randomize_sequence();

//////////////////////////////////////////////////////////////////////////////

   n=0;
   n--;
   operator++();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RandomizedTSSequence_base_2::randomize_sequence()
{
   UL_int akdim,k;
   UL_int CD;
   UL_int digits;
   static boost::uniform_int<UL_int> distUint32(std::numeric_limits<UL_int>::min(), std::numeric_limits<UL_int>::max());

   for(akdim=0;akdim<dimension;akdim++)
     {
       //digits=get_32_random_bits();
	   digits=distUint32(*rng);

       for(k=0;k<length;k++)
	 {
	   CD    =(ChangingDigit[akdim])[k];
	   if(CD!=0)
	     { 
	       CD--;
	       //digits=digits ^ ((2147483648UL | get_31_random_bits())>>CD);
	       //Doesn't matter that we use the full distUint32
	       //Because the first bit is going to be 1 anyway
	       digits=digits ^ ((2147483648UL | distUint32(*rng))>>CD);

//////////////////////////////////////////////////////////////////////////////
// the following two statements are semantically equal
// the second is better for testing and understanding
//
//	       digits=digits ^ ((2147483648UL | get_31_random_bits())>>CD);
//	       digits=(digits & ((4294967295UL)<<(31-CD))) 
//		       ^ ((2147483648UL | get_31_random_bits())>>CD);
//
// toggle ChangingDigit and make digits right of CD random
//////////////////////////////////////////////////////////////////////////////

	     }
	   (Seq[akdim])[(P[akdim])[k]]=digits;
	 }
     }
   apply_permutation_for_latin_supercube();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RandomizedTSSequence_base_2::calc_changing_digits(void)
{
   UL_int k,akdim,i;
   UL_int last_digits, now_digits,diff_digits;

   for(akdim=0;akdim<dimension;akdim++)
     {
       last_digits=0;

       for(k=0;k<length;k++)
	 {
	   now_digits=(Seq[akdim])[k];
	   diff_digits=now_digits ^ last_digits;
	   i=33;
	   while(diff_digits)
	     {
	       diff_digits=diff_digits>>1;
	       i--;
	     }
	   if(i==33) ChangingDigit[akdim][k]=0;
	   else      ChangingDigit[akdim][k]=(unsigned char)i;
	   last_digits=now_digits;
	 }
     }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RandomizedTSSequence_base_2::random_restart()
{
   randomize_sequence();
   n=0;
   n--;
   operator++();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
