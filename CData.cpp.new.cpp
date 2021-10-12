extern const int Debug;
const int Chans = 12;
const int Times = 1024;

struct STime
{
    unsigned int hh, mm, ss, mls, mks, dns;
    char stime[50] = "";
};


class CData
{
    FILE *fdata;
    unsigned int id, size, requests, trigger, reserve;
    unsigned char buf[8] = {0};
    STime etime;
    int chans = Chans;
    int times = Times;
    unsigned int event[Chans][Times];
    unsigned int baseline = 2048;
    unsigned int counter = 0;


public:
    CData(FILE *fin)
    {
        fdata = fin;
        for(int chan = 0; chan < chans; chan++)
            for(int t = 0; t < times; t++)
                event[chan][t] = 0;
    }
    int  read_header();
    int  read_event();
    void print_header(FILE *fout);
    void print_event(FILE *fout);
    void check_event();

private:
    unsigned int read_2_bytes();
    unsigned int read_4_bytes();
    void read_8_bytes_to_buf();
    void buf_to_time();
    void time_to_str();
    void read_time();
};


//====================================================================
/// read datafile header - 24 bytes
int CData::read_header()
{
    // read identificator == 3032
    id = read_2_bytes();
    // read size
    size = read_2_bytes();
    times = (size - 4) / 2 / chans;
    // read counter REQUEST
    requests = read_4_bytes();
    // read counter TRIGGER
    trigger = read_4_bytes();
    // read time
    //read_time(fdata);
    read_time();
    // read reserve
    reserve = read_4_bytes();
    counter += 1;
    return 0;
}

void CData::print_header(FILE *fout)
{
    fprintf(fout, "Counter = %u\n", counter);
    fprintf(fout, "id = %u = 0x%x\n", id, id);
    fprintf(fout, "size = %u = 0x%x\n", size, size);
    // print counter REQUEST
    fprintf(fout, "requests = %u = 0x%x\n", requests, requests);
    // print counter TRIGGER
    fprintf(fout, "trigger = %u = 0x%x\n", trigger, trigger);
    // print time
    fprintf(fout, "time: %s\n", etime.stime);
    // print reserve
    fprintf(fout, "reserve = %u = 0x%x\n", reserve, reserve);
    fprintf(fout, "\n");
}


/// count event length
void CData::check_event()
{
    int counter = 0;
    unsigned int readbyte = 0;

    while(readbyte != 0xffffffff)
    {
        readbyte = read_4_bytes();
        counter += 4;
    }
    printf("\nOne event is %d bytes long.\n", counter);
}


int CData::read_event()
{
    for(int chan = 0; chan < chans; chan++)
        for(int t = 0; t < times; t++)
        {
            event[chan][t] = (read_2_bytes() & 0xfff) - baseline;
        }

    if(read_4_bytes() == 0xffffffff)
    {
        if(Debug) printf("Event read OK!\n");
        return 0; // OK
    }
    if(Debug) printf("read_event(): Event read ERROR!\n");
    return 1; // error
}


void CData::print_event(FILE *fout)
{
    for(int ichan = 0; ichan < chans; ichan++)
    {
        for(int t = 0; t < times; t++)
        {
            fprintf(fout, "%d ", event[ichan][t]);
        }
        fprintf(fout, "\n");
    }
}


unsigned int CData::read_2_bytes()
{
    Conv.tInt = 0;
    fscanf(fdata, "%c%c", &Conv.tChar[0], &Conv.tChar[1]);
    //printf("%u %u\n",  Conv.tInt, Conv.tInt & 0xffff);
    return Conv.tInt & 0xFFFF;
}


unsigned int CData::read_4_bytes()
{
    fscanf(fdata, "%c%c%c%c", &Conv.tChar[0], &Conv.tChar[1], 
                              &Conv.tChar[2], &Conv.tChar[3]);
    return Conv.tInt;
}


void CData::read_8_bytes_to_buf()
{
    Conv.tInt = read_4_bytes();
    if(Debug) printf("int1: %x ", Conv.tInt);
    for(int i = 0; i < 4; i++)
        buf[i] = Conv.tChar[i];
    Conv.tInt = read_4_bytes();
    if(Debug) printf("int2: %x = ", Conv.tInt);
    for(int i = 0; i < 4; i++)
        buf[i + 4] = Conv.tChar[i];

    if(Debug)
    {
        // printf buffer:
        printf("buffer:  ");
        for(int i = 0; i < 8; i++)
            printf("0x%x ", buf[i]);
        printf("\n");
    }
}


void CData::buf_to_time()
{
    int data_time[4] = {0,0,0,0};

    for(int i = 0; i < 8; i += 2) 
    {
        data_time[i/2] = buf[i+1] * 256 + buf[i];
        //printf("time:  buf[%d] = 0x%x  buf[%d] = 0x%x    data[%d] = 0x%x\n",
        //(ii+1) , buf[ii+1], ii, buf[ii], ii/2, data_time[ii/2] );
    }
    etime.dns  = (data_time[0] & 0x7f)   * 10;
    etime.mks  = (data_time[0] & 0xff80) >> 7;
    etime.mks |= (data_time[1] &   1)    << 9;
    etime.mls  = (data_time[1] & 0x7fe)  >> 1;
    etime.ss   = (data_time[1] & 0xf800) >> 11;
    etime.ss  |= (data_time[2] &   1)    << 5;
    etime.mm   = (data_time[2] & 0x7e)   >> 1;
    etime.hh   = (data_time[2] & 0xf80)  >> 7;

    if ( (etime.hh  >  23) || (etime.mm  >  59) || (etime.ss  >  59) ||
         (etime.mls > 999) || (etime.mks > 999) || (etime.dns > 999))
    {
        time_to_str();
        printf("buf_to_time error:  Wrong Time:  %s  \n", etime.stime);
        printf("buf_to_time error:  Wrong Time:  %02d:%02d:%02d,%03d.%03d.%03d  \n",
               etime.hh, etime.mm, etime.ss, etime.mls, etime.mks, etime.dns);
    }
}


void CData::read_time()
{
    read_8_bytes_to_buf();
    buf_to_time();
    time_to_str();
}


void CData::time_to_str()
{
    sprintf(etime.stime, "%02d:%02d:%02d,%03d.%03d.%03d",
            etime.hh, etime.mm, etime.ss, etime.mls, etime.mks, etime.dns);
}
