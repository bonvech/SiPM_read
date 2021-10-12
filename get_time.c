//====================================================================
void Data::GetTime (unsigned char buf[8],int *hh,int *mm,int *ss,int *mlss,int *mkss,int *dnss)
{
    int hhhh=0, mmmm=0, ssss=0, mlssss=0, mkssss=0, dnssss=0;
    int data_time[4] = {0,0,0,0};

    for(int ii=0; ii<8; ii+=2) {
        data_time[ii/2]=buf[ii+1]*256+buf[ii];
        //printf("time:  buf[%d] = 0x%x  buf[%d] = 0x%x    data[%d] = 0x%x\n",
        //(ii+1) , buf[ii+1], ii, buf[ii], ii/2, data_time[ii/2] );
    }
        dnssss  = (data_time[0] & 0x7f)   * 10;
        mkssss  = (data_time[0] & 0xff80) >> 7;
        mkssss |= (data_time[1] &   1)    << 9;
        mlssss  = (data_time[1] & 0x7fe)  >> 1;
        ssss    = (data_time[1] & 0xf800) >> 11;
        ssss   |= (data_time[2] &   1)    << 5;
        mmmm    = (data_time[2] & 0x7e)   >> 1;
        hhhh    = (data_time[2] & 0xf80)  >> 7;
        *hh=hhhh;
        *mm=mmmm;
        *ss=ssss;
        *mlss=mlssss;
        *mkss=mkssss;
        *dnss=dnssss;
    if ( (hhhh>23) || (mmmm>59) || (ssss>59) || (mlssss>999) || (mkssss>999) || (dnssss>999) ) {
        printf("GetTime::  Wrong Time:  {%06ld.%02d}  BSM#%02d  por=%i  %02d:%02d:%02d,%03d.%03d.%03d  NumEvent=%ld\n",
        mmm,md,Number,por,hhhh,mmmm,ssss,mlssss,mkssss,dnssss,NumEvent);
    }
}

//====================================================================
