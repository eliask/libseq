////////////////////////////////////////////////////////////////////////////
//
// SequenceTest.cpp, 03/26/01, Ilja Friedel
//
////////////////////////////////////////////////////////////////////////////
//
// Test the different methods for creating DigitalSeqences
//
////////////////////////////////////////////////////////////////////////////

#include "DigitalSequence.h"

#define TEST_EPSILON 0.0000000001

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv)
{
  UL_int pb;
  UL_int base;
  UL_int base_array[30];
  UL_int dimension;
  UL_int length;
  UL_int i,j;
  Rng rng;

  cout << "Checking types ... ";
  check_own_types();
  cout << "done!"<<endl;

  base_array[ 0]=3;
  base_array[ 1]=5;
  base_array[ 2]=7;
  base_array[ 3]=11;
  base_array[ 4]=13;
  base_array[ 5]=17;
  base_array[ 6]=19;
  base_array[ 7]=23;
  base_array[ 8]=29;
  base_array[ 9]=31;

  base_array[10]=37;
  base_array[11]=41;
  base_array[12]=43;
  base_array[13]=47;
  base_array[14]=53;
  base_array[15]=59;
  base_array[16]=61;
  base_array[17]=67;
  base_array[18]=71;
  base_array[19]=73;

  base_array[20]=79;
  base_array[21]=83;
  base_array[22]=89;
  base_array[23]=97;
  base_array[24]=101;
  base_array[25]=103;
  base_array[26]=127;
  base_array[27]=157;
  base_array[28]=997;
  base_array[29]=1997;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  dimension=16;
  length=50000;

    {
      base=2;
      Ring     R(base);
      C_matrix C(&R,"Niederreiter",dimension);

      DigitalSequence_base_2      DSb(&C, &rng);
      DigitalSequence_classic     DSc(&C, &rng);
      DigitalSequence_medium_base DSm(&C, &rng);
      DigitalSequence_advanced    DSa(&C, &rng);

      cout << "Testing base=" << base << " ... ";

      for(i=0;i<length;i++)
	{
	  for(j=0;j<dimension;j++)
	    {
	      if(DSc[j]!=DSb[j])
		{
		  cerr << DSc[j] << "  " << DSb[j] << endl;
		  cerr << "Error: At vector "<<i<<" DSc["<<j<<"]!=DSb["
		       <<j<<"]. (base="<<base<<")"<< endl;
		  exit(1);
		}

	      if(DSc[j]!=DSm[j])
		{
		  cerr << DSc[j] << "  " << DSb[j] << endl;
		  cerr << "Error: At vector "<<i<<" DSc["<<j<<"]!=DSm["
		       <<j<<"]. (base="<<base<<")"<< endl;
		  exit(1);
		}
	      
	      if(DSc[j]!=DSa[j])
		{
		  cerr << DSc[j] << "  " << DSb[j] << endl;
		  cerr << "Error: At vector "<<i<<" DSc["<<j<<"]!=DSa["
		       <<j<<"]. (base="<<base<<")"<< endl;
		  exit(1);
		}	      
	    }
	  ++DSc;
	  ++DSm;
	  ++DSa;
	  ++DSb;
	}
      cout << "done!" << endl;
    }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  for(pb=0;pb<30;pb++)
    {
      base=base_array[pb];
      cout << "Testing base=" << base << " ... ";

      Ring     R(base);
      C_matrix C(&R,"Niederreiter",dimension);

      DigitalSequence_classic     DSc(&C, &rng);
      DigitalSequence_medium_base DSm(&C, &rng);
      DigitalSequence_advanced    DSa(&C, &rng);

      for(i=0;i<length;i++)
	{
	  for(j=0;j<dimension;j++)
	    {
	      if(fabs(DSc[j]-DSm[j])>TEST_EPSILON)
		{
		  cerr << DSc[j] << "  " << DSm[j] << endl;
		  cerr << "Error: At vector "<<i<<" DSc["<<j<<"]!=DSm["
		       <<j<<"]. (base="<<base<<")"<< endl;
		  exit(1);
		}
	      
	      if(fabs(DSc[j]-DSa[j])>TEST_EPSILON)
		{
		  cerr << DSc[j] << "  " << DSa[j] << endl;
		  cerr << "Error: At vector "<<i<<" DSc["<<j<<"]!=DSa["
		       << j <<"]. (base=" << base << ")" << endl;
		  exit(1);
		}	      
	    }
	  ++DSc;
	  ++DSm;
	  ++DSa;
	}
       cout << "done!" << endl;
    }

  cout << "Testing of unrandomized DigitalSequences finished. " 
       << "No problems found." << endl;
  return(0);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
