////////////////////////////////////////////////////////////////////////////
//                                                                        
// VectorRing.h, 09/11/00, Ilja Friedel                              
//
////////////////////////////////////////////////////////////////////////////
//
// Status: ok
//
////////////////////////////////////////////////////////////////////////////

#ifndef VECTORRING_USED
#define VECTORRING_USED

////////////////////////////////////////////////////////////////////////////
// standard include files
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
// own include files
////////////////////////////////////////////////////////////////////////////

#include "own_types.h"
#include "options.h"
#include "Ring.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class VectorRing
{
protected:
          Ring * R;
          UL_int memory;

          R_Elem * _add;
          R_Elem * _mult;
          R_Elem * _a_inverse;

public:
          UL_int base;
          UL_int times;
          UL_int base_pow_times;
          char   name    [256];
          char   filename[256];

   inline RVector add          (RVector, RVector);
   inline RVector mult         (R_Elem, RVector); 
   inline RVector minus        (RVector);
   inline RVector array2vector (R_Elem *);
   inline void    vector2array (RVector, R_Elem *);

   inline UL_int memory_used(void){return(memory);}

                 VectorRing(Ring *, UL_int);
   virtual      ~VectorRing();
};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

inline RVector VectorRing::array2vector (R_Elem * a)
{
  int i;
  RVector result;

  result=0;
  for(i=0;i<times;i++) result=result*base+a[i];

  return(result);
}
  
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

inline void   VectorRing::vector2array (RVector v, R_Elem * a)
{
  int i;
  for(i=0;i<times;i++)
    {
      a[times-i-1]=v%base;
      v=v/base;
    }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

inline RVector VectorRing::add(RVector a, RVector b)
{  
#ifdef DEBUG
   if((a>base_pow_times)||(b>base_pow_times))
     {
       cerr << "Error: Arguments out of range! (VectorRing::add())" << endl;
       cerr <<  "(a=" << a << 
               ", b=" << b << 
               ", base_pow_times="<< base_pow_times <<")"<< endl;
       exit(1);
     }
#endif
   return(_add[a+b*base_pow_times]);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

inline RVector VectorRing::mult(R_Elem a, RVector b) 
{
#ifdef DEBUG
   if((a>base)||(b>base_pow_times))
     {
       cerr << "Error: Arguments out of range! (VectorRing::mult())" << endl;
       cerr <<  "(a=" << a << 
               ", b=" << b << 
               ", base_pow_times="<< base_pow_times <<")"<< endl;
       exit(1);
     }
#endif
   return(_mult[a+b*base]);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

inline RVector VectorRing::minus(RVector a) 
{
#ifdef DEBUG
   if((a>base_pow_times))
     {
       cerr << "Error: Argument out of range! (VectorRing::minus())" << endl;
       cerr << "(a=" << a << 
               ", base_pow_times="<< base_pow_times <<")"<< endl;
       exit(1);
     }
#endif
   return(_a_inverse[a]);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#endif
