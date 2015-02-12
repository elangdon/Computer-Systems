#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;

	//Made local variables outside of function calls to decrease frequency of allocations
	int width = (input->width)-1;
	int height = (input->height)-1;
	int fdivisor = filter->getDivisor();
	int acc0,acc1,acc2;

	//Made local array for filter->get so we wouldn’t have to access memory to retrieve value as often
	int i, j;
	int filterx[3][3];
	for (i=0;i<3;i++){
		for(j=0;j<3;j++){
			filterx[i][j]=filter->get(i,j);
		}
	}
	
	// reordered loops for closer memory references
  for(int plane = 0; plane < 3; plane++) {
	for(int row = 1; row < height; row++) {
		for(int col = 1; col < width; col++) {
			
		//unrolled two loops that iterate over the filter array
		 acc0 = (input->color[plane][row-1][col-1]*filterx[0][0]);
		 acc1 = (input->color[plane][row-1][col]*filterx[0][1]);
		 acc2 = (input->color[plane][row-1][col+1]*filterx[0][2]);
		 acc0 += (input->color[plane][row][col-1]*filterx[1][0]);
		 acc1 += (input->color[plane][row][col]*filterx[1][1]);
		 acc2 += (input->color[plane][row][col+1]*filterx[1][2]);
		 acc0 += (input->color[plane][row+1][col-1]*filterx[2][0]);
		 acc1 += (input->color[plane][row+1][col]*filterx[2][1]);
		 acc2 += (input->color[plane][row+1][col+1]*filterx[2][2]);
	
	//Used our three accumulators to combine so they could be done in parallel with less dependancy		
	output -> color[plane][row][col] = acc0+acc1+acc2;
	
	//attempt to reduce frequency of division 
	if (fdivisor > 1){
		output -> color[plane][row][col] = output -> color[plane][row][col]/fdivisor;
	}
	
	//reordered  saturation so branch prediction would be accurate more frequently 
	//and reduce the necessity for some of these checks since they are dependant
	if ( output -> color[plane][row][col]  > 0 && output -> color[plane][row][col]  < 255 ) 
	/*empty*/;
	else if ( output -> color[plane][row][col]  > 255 )  
	  output -> color[plane][row][col] = 255;  
	else if ( output -> color[plane][row][col]  < 0)  
	  output -> color[plane][row][col] = 0;
	
	  
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
