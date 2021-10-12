#include <stdio.h>
union CharInt_converter
{
    unsigned char tChar[4]; ///< four chars
    unsigned int  tInt;     ///< 4-byte integer number
} Conv; ///< union to convert 

unsigned int read_2_bytes(FILE * fdata)
{
    Conv.tInt = 0;
    fscanf(fdata, "%c%c", &Conv.tChar[0], &Conv.tChar[1]);
    //printf("%u %u\n",  Conv.tInt, Conv.tInt & 0xffff);
    return Conv.tInt & 0xFFFF;
}

unsigned int read_4_bytes(FILE * fdata)
{
    fscanf(fdata, "%c%c%c%c", &Conv.tChar[0], &Conv.tChar[1], &Conv.tChar[2], &Conv.tChar[3]);
    return Conv.tInt;
}

char* read_8_bytes(FILE * fdata)
{
    char buf[8] = {0};
    int i;
    char * xx;

    Conv.tInt = read_4_bytes(fdata);
    for(i = 0; i < 4; i++)
        buf[i] = Conv.tChar[i];
    Conv.tInt = read_4_bytes(fdata);
    for(i = 0; i < 4; i++)
        buf[i + 4] = Conv.tChar[i];
    for(i = 0; i < 8; i++)
        printf("0x%x ", buf[i]);
    return xx;
}

int main()
{
    FILE *fdata;
    char name[200] = "SIPMZynq_v1_192.168.1.200.bin";
    //unsigned char inb1, inb2;
    unsigned int  inw;

    if((fdata = fopen(name, "rb")) == NULL)
    {
        printf("Error in file %s opening!\n\n", name);
        return 1;
    }

    // read identificator == 3032
    inw = read_2_bytes(fdata);
    printf("id = %u = 0x%x\n", inw, inw);
    // read size
    inw = read_2_bytes(fdata);
    printf("size = %u = 0x%x\n", inw, inw);
    // read counter REQUEST
    inw = read_4_bytes(fdata);
    printf("requests = %u = 0x%x\n", inw, inw);
    // read counter TRIGGER
    inw = read_4_bytes(fdata);
    printf("trigger = %u = 0x%x\n", inw, inw);
    // read time
    //read_time(fdata);
    read_8_bytes(fdata);
    // read reserve
    inw = read_4_bytes(fdata);
    printf("reserve = %u = 0x%x\n", inw, inw);

    fclose(fdata);
}
