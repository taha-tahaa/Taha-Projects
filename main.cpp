#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"


const int MONE = -1;
const int ONE =1;
const int TWO=2;


int main(int argc, char ** argv)
{

    if(check_args(argc,argv)){
        return MONE;
        }
	String trim_array = String(argv[ONE]);
  	trim_array = trim_array.trim();
    char delimiters[TWO]={'=',','};
    String *dst_src_arr;
    size_t length =0;

    trim_array.split(delimiters,&dst_src_arr,&length);
    
   

    if(dst_src_arr[0].trim().equals("src-port"))
    {
    	port SP("src-port");
        SP.set_value(dst_src_arr[ONE]);
        parse_input(SP);
    }

    if(dst_src_arr[0].trim().equals("src-ip"))
    {
    	ip SI("src-ip");
        SI.set_value(dst_src_arr[ONE]);
        parse_input(SI);
    }


    if(dst_src_arr[0].trim().equals("dst-port"))
    {
    	port DP("dst-port");
        DP.set_value(dst_src_arr[ONE]);
        parse_input(DP);
    }


    if(dst_src_arr[0].trim().equals("dst-ip"))
    {
    	ip DI("dst-ip");
        DI.set_value(dst_src_arr[ONE]);
        parse_input(DI);
    }
    delete[] dst_src_arr;


    return 0;
}
