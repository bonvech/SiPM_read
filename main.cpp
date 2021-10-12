#include <stdio.h>
#include <string.h>
#define DEBUG

const int Debug = 1;

union CharInt_converter
{
    unsigned char tChar[4]; ///< four chars
    unsigned int  tInt;     ///< 4-byte integer number
} Conv; ///< union to convert 

#include "CData.cpp"



int main()
{
    FILE *fdata;
    FILE *fout;
    //char name[200] = "./data/SIPMZynq_v1_192.168.1.200.bin";
    //char name[200] = "02061001.001";
    char dirname[200] = "./Data/";
    char name[200] = "05101001.001";
    char namein[200] = "";
    char nameout[200] = "";


    // make filename to read
    strcpy(namein, dirname);
    strcat(namein, name);
    // make name for output file from the input file name
    strcpy(nameout, name);
    strcat(nameout, ".txt");

    // open input and output files
    if((fdata = fopen(namein, "rb")) == NULL)
    {
        printf("Error in file %s opening!\n\n", name);
        return 1;
    }
    if((fout = fopen(nameout, "wt")) == NULL)
    {
        printf("Error in file %s opening!\n\n", nameout);
        return 2;
    }

    // create new CData class object
    CData data(fdata);  

    // read one event
    data.read_header();
    data.print_header(stdout);
    data.print_header(fout);
    data.read_event();
    data.print_event(fout);

    fclose(fdata);
    fclose(fout);
}
