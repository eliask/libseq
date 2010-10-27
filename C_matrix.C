//////////////////////////////////////////////////////////////////////////////
//
// C_matrix.C, 11.6.99, Ilja Friedel
//
//////////////////////////////////////////////////////////////////////////////
//
// Status: load is still buggy
//  -- C_matrix on disc too big -> out of array ranges
//  -- load Ring automatically
//
//////////////////////////////////////////////////////////////////////////////

#include "C_matrix.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void C_matrix::ignore_comments(FILE * fid)
{
   char c;

   do
     {
       c=getc(fid);
       if(c=='#')
	 {
	   do c=getc(fid);
	   while (c!='\n');
	 }
     }
   while (c==' ' || c=='\n' || c=='\t');
 
   ungetc(c,fid);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void C_matrix::load(char * fname)
{
   FILE *fid;
   char buffer[256];
   int i;
   UL_int row,akdim,column,base,tmp;

   fid=fopen(fname,"rt");

   if(fscanf(fid,"C_MATRIX")>-1)
     {
       ignore_comments(fid);
       
       if(fscanf(fid,"C_MATRIX_NAME %s",name)<1)
	 {
	   cerr << "Error: No C_MATRIX_NAME specification or wrong place!";
	   cerr << endl;
	   exit(1);
	 }
       ignore_comments(fid);
       
//////////////////////////////////////////////////////////////////////////////
       
       if(fscanf(fid,"C_MATRIX_RING_NAME %s",buffer)<1)
	 {
	   cerr << "Error: No C_MATRIX_RING_NAME specification or wrong place!";
	   cerr << endl;
	   exit(1);
	 }
#ifdef WARNINGS_EXTERNAL
       if(strcmp(R->name,buffer)!=0)
	 {
	   cerr << "Warning: "
		<< "C_MATRIX_RING_NAME and Ring->name are not equal! "
		<< "Possibly using wrong ring."
		<< "(C_matrix::load())" << endl;
	 }
#endif

       ignore_comments(fid);
#if UINT32_MAX == ULONG_MAX
       if(fscanf(fid,"C_MATRIX_RING_CARD %lu",&base)<1)
#elif UINT32_MAX == UINT_MAX
       if(fscanf(fid,"C_MATRIX_RING_CARD %u",&base)<1)
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
	 {
	   cerr << "Error: No C_MATRIX_RING_CARD specification ";
	   cerr << "or wrong place!" << endl;
	   exit(1);
	 }
       
       if(base!=R->base)
	 {
	   cerr << "Error: C_MATRIX_RING_CARD is not equal to R->base";
	   cerr << endl;
	   cerr << "       Trying to use wrong ring!" << endl;
	   exit(1);
	 }
   
//////////////////////////////////////////////////////////////////////////////

      ignore_comments(fid);
#if UINT32_MAX == ULONG_MAX
      if(fscanf(fid,"DIGIT_ACCURACY %lu",&NumDigits)<1)
#elif UINT32_MAX == UINT_MAX
      if(fscanf(fid,"DIGIT_ACCURACY %u",&NumDigits)<1)
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
	{
	  cerr << "Error: No DIGIT_ACCURACY specification or wrong place!";
	  cerr << endl;
	  exit(1);
	}
#ifdef WARNINGS_EXTERNAL
      if(NumDigits>32) cerr << "Warning: "
			    << "Very large NumDigits!"
			    << "(C_matrix::load())"<<endl;
#endif
      ignore_comments(fid);
#if UINT32_MAX == ULONG_MAX
      if(fscanf(fid,"MAX_DIMENSION %lu",&dimension)<1)
#elif UINT32_MAX == UINT_MAX
      if(fscanf(fid,"MAX_DIMENSION %u",&dimension)<1)
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
	{
	  cerr << "Error: No MAX_DIMENSION specification or wrong place!";
	  cerr << endl;
	  exit(1);
	}
#ifdef WARNINGS_EXTERNAL
      if(dimension>32) cerr << "Warning: "
			    << "Very large MAX_DIMENSION. "
			    << "(C_matrix::load())" << endl;
#endif
//////////////////////////////////////////////////////////////////////////////

      for(akdim=0;akdim<dimension;akdim++)
        {
	  ignore_comments(fid);
	  fscanf(fid,"DIMENSION %d",&i);	//No #if required because i is an int
          for(row=0;row<NumDigits;row++) 
             {
	       for(column=0;column<NumDigits;column++)
		 {
#if UINT32_MAX == ULONG_MAX
		   fscanf(fid,"%lu",&tmp);
#elif UINT32_MAX == UINT_MAX
		   fscanf(fid,"%u",&tmp);
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
		   if(tmp>=base)
		     {
		       cerr << "Error: Element out of range!" << endl;
		       exit(1);
		     }
                   set(akdim,row,column,tmp);
		   ignore_comments(fid);
		 }
	       fscanf(fid,"END_LINE");
             }
	  ignore_comments(fid);
          fscanf(fid,"END_DIMENSION");
        }

      ignore_comments(fid);
      if(fscanf(fid,"END_C_MATRIX")<0)
	{
	  cerr << "Error: No END_C_MATRIX found!" << endl;
	  exit(1);
	}
     }
//////////////////////////////////////////////////////////////////////////////

   else
     { 
       cerr << "Error: '" << fname << "' is not a C_MATRIX file! ";
       cerr << "(First keyword must be 'C_MATRIX'.)";
       cerr << endl;
       exit(1);
     }
   fclose(fid);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void C_matrix::save(char * fname)
{
   int akdim,row,column;
   FILE * fid;

   fid=fopen(fname,"wt");

   fprintf(fid,"C_MATRIX\n");
   fprintf(fid,"C_MATRIX_NAME %s\n",name);
   fprintf(fid,"C_MATRIX_RING_NAME %s\n",R->name);
#if UINT32_MAX == ULONG_MAX
   fprintf(fid,"C_MATRIX_RING_CARD %lu\n",R->base);
   fprintf(fid,"DIGIT_ACCURACY %lu\n",NumDigits);
   fprintf(fid,"MAX_DIMENSION %lu\n\n",dimension);
#elif UINT32_MAX == UINT_MAX
   fprintf(fid,"C_MATRIX_RING_CARD %u\n",R->base);
   fprintf(fid,"DIGIT_ACCURACY %u\n",NumDigits);
   fprintf(fid,"MAX_DIMENSION %u\n\n",dimension);
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif

   fprintf(fid,"# The indices of the following arrays are \n");
   fprintf(fid,"# horizontal is l\n");
   fprintf(fid,"# vertical is r\n");
   fprintf(fid,"# Please compare with the documentation\n");
   fprintf(fid,"# or Niederreiter'92\n\n");


   for(akdim=0;akdim<dimension;akdim++)
     {
#if UINT32_MAX == ULONG_MAX
       fprintf(fid,"DIMENSION %lu\n",akdim);
#elif UINT32_MAX == UINT_MAX
       fprintf(fid,"DIMENSION %u\n",akdim);
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
       for(row=0;row<NumDigits;row++)
	 {
	   for(column=0;column<NumDigits;column++)
	     {
#if UINT32_MAX == ULONG_MAX
	       fprintf(fid,"%lu ",query(akdim,row,column));
#elif UINT32_MAX == UINT_MAX
	       fprintf(fid,"%u ",query(akdim,row,column));
#else
	#error "Can't determine appropriate parameters for fscanf"
#endif
	     }
	   fprintf(fid,"END_LINE\n");
	 }
       fprintf(fid,"END_DIMENSION\n\n");
     }
   fprintf(fid,"END_C_MATRIX\n");
   fclose(fid);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void C_matrix::get_Niederreiter()
{

   UL_int* v = new UL_int[NumDigits+64];

   if(!v)
   {
     cerr << "Error: Out of memory!" << endl;
	 exit(1);
   }

   L_int row, column, akdim;
   L_int q,e,u,m,k;
   L_int i;
   
   Polynomial Px, Bx;
   Polynomial * irr_poly;

   sprintf(name,"Niederreiter");

   irr_poly =first_irr_polynomials(dimension,R);

//////////////////////////////////////////////////////////////////////////////
// Beginn der Berechnung der c[i][j] aus den irreduziblen Polynomen.   
// Diese c[i] sind wichtigster Ausgangspunkt der Berechnung fuer die   
// (t,s)-Folge.                                                        
//////////////////////////////////////////////////////////////////////////////
   
   for(akdim=0;akdim<dimension;akdim++)
     {
      
       Px=irr_poly[akdim];
       e=(L_int)Px.deg;
       Bx=one(R);
      
       q=-1;
       u=e;
       for(row=0;row<NumDigits;row++)
         {
	   if(u==e)
	     {
	       q++;
	       u=0;
	       Bx=Bx*Px;
	       m=(L_int)Bx.deg;
	    
//////////////////////////////////////////////////////////////////////////////
// Beginn der Berechnung der v[i] als Zwischenergebnis fuer die c[i][j]  
//////////////////////////////////////////////////////////////////////////////
	    
	       for(i=0;i<=NumDigits+e-2;i++)
		 {
		   if(i<=m-2) {v[i]=0;}
		   else{
		     if(i==m-1){v[i]=1;}
		     else
		       {
			 UL_int tmp;
			 tmp=0;
			 for(k=1;k<=m;k++) 
			   {
			     if(k>i) 
			       {
				 cerr << "Error: Underflow in v[i-k]!";
				 cerr << endl;
				 exit(1);
			       }
			
//////////////////////////////////////////////////////////////////////////////
// Hier kommt eine ganz interessante Stelle. Zu beachten ist vor allem   
// der Ausdruck invert(Bx.digit[m-k]). Dadurch erhaelt man 
// die geforderten negativen Vorzeichen im Polynom Bx. Der               
// Leitkoeffizient geht nicht in die Berechnung ein.                     
//////////////////////////////////////////////////////////////////////////////
			
			     tmp=R->add(tmp,R->mult
					(R->minus((Bx.digit)[m-k]),
					 v[i-k]));
			   }
			 v[i]=tmp;
		       }
		   }
		 }
	   
//////////////////////////////////////////////////////////////////////////////
// Ende der Berechnung der v[i]	                                      
//////////////////////////////////////////////////////////////////////////////
	 
	     }
	   for(column=0;column<NumDigits;column++) 
	     {
               set(akdim,row,column,v[column+u]);
	     }
	   u++;
         }
     }
   if(irr_poly) delete[] irr_poly;
   irr_poly=NULL;
   
   delete[] v;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

C_matrix::~C_matrix()
{
  if(c) delete[] c;
  c=NULL;
  // don't delete the Ring!
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

