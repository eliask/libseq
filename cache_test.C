////////////////////////////////////////////////////////////////////////////
// 
// cache_test.C, Ilja Friedel, 03/26/01
//
// use this program to measure cache miss penalty
// e.g. "time cache_test 10^7 1" vs. "time cache_test 10^7 11"
//
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  int i,j,offset,size;
  int * mem;

  if(argc!=3)
    {
      cerr << argv[0] << " size offset" << endl;
      exit(1);
    }

  size=atoi(argv[1]);
  offset=atoi(argv[2]);

  mem=new int[size];

  if(!mem)
    {
      cerr << "Error: Not enough memory for size="<<size<<"!"<<endl;
      exit(1);
    }

  i=0;
  j=0;
  for(i=0;i<size;i++)
    {
      mem[j]=1;
      j+=offset;
      if(j>=size) j-=size;
    }

  return(0);
}

  
