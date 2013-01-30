/////////////////////////////////////////////////////////////////////////////
//                                                                         
// Counter.cpp, 2.8.99, Ilja Friedel                       
//
/////////////////////////////////////////////////////////////////////////////
//
// Status:
//
/////////////////////////////////////////////////////////////////////////////

#include "Counter.h"

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

Counter::Counter(Ring * R,UL_int ND)
{
   init(R,ND,(RandomPermutation **)NULL);
}

/////////////////////////////////////////////////////////////////////////////

Counter::Counter(Ring * R,UL_int ND, RandomPermutation ** psi)
{
   init(R,ND,psi);
}

/////////////////////////////////////////////////////////////////////////////

Counter::~Counter()
{
   if(x)    delete [] x;
   if(diff) delete [] diff;
   x   =NULL;
   diff=NULL;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void Counter::set(UL_int n)
{
   L_int i;
   UL_int tmp;

   for(i=0;i<NumDigits;i++)
     {
       tmp = x[i];
       x[i]= n%base;
       n=n/base;
       if(psi) diff[i]=R->add((*(psi[i]))[x[i]],R->minus((*(psi[i]))[tmp]));
       else    diff[i]=R->add(x[i],R->minus(tmp));
     }

   if(n!=0)
     {
       cerr << "Error: Counter overflow! (Counter::set())" << endl;
       exit(1);
     }
   LastChangingDigit=NumDigits-1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void Counter::reset(void)
{
   L_int i,j;

/////////////////////////////////////////////////////////////////////////////
// sets Counter and diff to zero
// (very important function for DigitalSequence::restart(), n0!=0)
/////////////////////////////////////////////////////////////////////////////
   for(i=0;i<NumDigits;i++)
     {
       if(psi==NULL) x[i]=0;
       else for(j=0;j<base;j++) if((*(psi[i]))[j]==0) x[i]=j;
       diff[i]=0;
     }
   LastChangingDigit=NumDigits-1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void Counter::init(Ring * T,UL_int ND, RandomPermutation ** ps)
{
   R=T;
   base=R->base;

   x    = new UL_int[ND];
   diff = new R_Elem[ND];
   if (!(x&&diff)) 
     {
       cerr << "Error: Out of memory! (Counter(" << ND << "))" << endl;  
       exit(1);
     }

   NumDigits         = ND;
   LastChangingDigit = ND-1;
   psi               = ps;
   memory=2*ND*sizeof(R_Elem)+sizeof(Counter);

   reset();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void Counter::increment_digit(UL_int start)
{
    L_int i;
   UL_int tmp;

   for(i=0;i<start;i++) diff[i]=0;

   i=(L_int)start;
   do
     {
       tmp    = x[i];
       x   [i]=(x[i]+1)%base;

       if(psi) diff[i]=R->add((*(psi[i]))[x[i]],R->minus((*(psi[i]))[tmp]));
       else    diff[i]=R->add(x[i],R->minus(tmp));
       i++;
     }
   while((i<NumDigits)&&(x[i-1]==0));

   if((i==NumDigits)&&(x[i-1]==0))
     {
       cerr << "Counter overflow! (Counter::operator++())" << endl;
       exit(1);
     }
   LastChangingDigit=i-1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void Counter::decrement_digit(UL_int start)
{
    L_int i;
   UL_int tmp;

   for(i=0;i<start;i++) diff[i]=0;

   i=(L_int)start;
   do
     {
       tmp     =  x[i];
       x   [i] = (x[i]+base-1)%base;

       if(psi) diff[i]=R->add((*(psi[i]))[x[i]],R->minus((*(psi[i]))[tmp]));
       else    diff[i]=R->add(x[i],R->minus(tmp));
       i++;
     }
   while((i<NumDigits)&&(x[i-1]==base-1));

   if((i==NumDigits)&&(x[i-1]==base-1))
     {
       cerr << "Counter underflow! (Counter::operator--())" << endl;
       exit(1);
     }
   LastChangingDigit=i-1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////