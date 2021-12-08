#ifndef __DATA_H__
#define __DATA_H__

#define BASE 1
#define MUON 2



class Data {

public:


//char filename[200];
char filedata[200];
char fileout[200];
char fileped[200];
char filedel[200];
char filehdr[200];
char fileampl[200];

char pathfile[200];
char pathfile_new[200];
char pathfile_hist[200];
char dirname[200];

char filehistA[200];
char filehistQ[200];

char fileA1A2[200];
char fileA3A4[200];
char fileA2A6[200];
char fileA4A8[200];

char fileA1A3[200];
char fileA2A4[200];
char fileA6A8[200];

FILE *fdat;
FILE *fout;
FILE *fhdr;
FILE *fped;
//FILE *fdel;
FILE *fcal;





int por;
int run;
int run_dir;
int ready;
int stop;
int restart;
long long dtime;
int stat;
int cut;
int Number;
int NumHiSC;
long long NumEvent;
long long NumEvent_prim;
long long TimeEvent;
long long TimeEvent_prim;
int h,m,s,mls,mks,dns,Delay;
int hour_plus,min_plus,key_plus;
int hour,min,sec,mlsec;
int Bank;
int NumPacks;
int err;
int kadd,hadd;

int IACT_num;

float ped[64],dped[64],sped[64];
float ped_minus[64],sped_minus[64];
int nped[64],nped_minus[64];
int gped[64][4101];
int hped[64][4101];
int hped_max[64][4101];





int active[64];
int valid[64];
float del;
int ndel;
int ped_present;
unsigned long  para[64][64];

float GAIN[64];
float K_ADC[64];
float PE_CODE[64];
float SENS[64];

float XXpmt[64];
float YYpmt[64];

unsigned long Trigg[64];
int Stat[64];
byte add_byte[4];
int err_data;
unsigned long RejectEvent;


int gall[64][4101];
int gampl[64][4101];
int hampl[64][4101];
//int gped[64][401];

float Ampl[32][1024];
float Ampl_pe[64];
float Ampl_pe_clean[64];
int spe[5001];
int spe_clean[5001];
int spe_det[64][5001];


float A12[64][2][2000];
int nA12[64];


float XX,YY,Tet,Fi,lgE;
int NumSt;
float Alfa,Delta,Angle;

int nerr[10];

int Nrate;
int IACT_NN;

typedef struct {
	int num1,nn1,ncl1,nch1;
	int num2,nn2,ncl2,nch2;
	int num3,nn3,ncl3,nch3;
	float xx,yy;
} Spmt;
Spmt SORT[3000];



unsigned char buf[70000];

int s_add,mls_add,mks_add,dns_add;
int sidi;
int NumBytes;


unsigned char hd[30];
unsigned char data[70000];



//====================================================================

long long tim3,tim_start,tim_fin;
//int Ampl[16];
//long Qpls[16];
//int Hist_A[16][2101];
//int Hist_Q[16][41001];
//int Hist_T[10001];
//int Hist_allQ[16][21000];

		Data(){ 

		    IACT_num=61;
		    por=0;
		    run=0;
		    ready=0;
		    stop=1;
		    restart=0;
		    stat=0;
		    cut=0;
		    dtime=0L;
		    Number=0;
		    Bank=0;
		    NumPacks=0;
		    tim3=0L;
		    tim_start=0L;
		    tim_fin=0L;
		    err=0;
		    kadd=0;
		    hadd=0;
		    Delay = 1453;  // from IACT
		    err_data=0;
		    IACT_NN=1;

		    fdat=NULL;
		    fout=NULL;
		    fhdr=NULL;
		    for(int ii=0;ii<64;ii++) {
			GAIN[ii]=1;
			K_ADC[ii]=1;
			PE_CODE[ii]=1000;
			SENS[ii]=1000;
			Trigg[ii]=0;
			Stat[ii]=0;
		    }



		};
		~Data(){};


//		int OpenNewFile(char *path, int por, int flag );
//		int OpenNextFile(char *path, int por, int flag );
//		int CloseFile(void);

//		int GetHist(void);
//		int HistZero(void);

		FILE *EmptyFile(char fname[], char mod[], int *res);
		FILE *OpenFile(char *path, int *por, int flag, int *res, int mode );

//		int Errors(int flag,long long Bad, long long Realy) 

//  T133  &   HiSCORE:
		long long ReadBIN(int numpack);
		long long ReadBIN_33104(int numpack);
		int Collection2(unsigned long Addr, unsigned char *buf, int NumBytes, int add);
//		int ReadData(void);
//  IACT primary:
		int Read_ped_IACT(FILE *fff);
		int Read_ped_txt_IACT(FILE *fff);
		long long Read_IACT(int key_add, int key);
		long long Read_IACT_old(int key_add, int key);
		long long AddTime_2019_20_iact01(long long tim);
		long long AddTime_2019_20_iact02(long long tim);
//		int RejectIACT_old(int iact,long mmm,int md, long long NumEvent,int h,int m,int s,unsigned long *Reject);
		int RejectIACT(void);
		int RestartIACT(int maska_key);
		int GetAddBytes(unsigned char ctt[8],int *ss,int *mlss,int *mkss,int *dnss,int *maska_key);
		int SaveHDR(FILE *fff);
		int Errors_IACT(int *err,int *maska);


//  SIPM primary:
		long long Read_SIPM(int key_add, int key);



//  Readers:
		long long Read_tim2 (void);
		long long Read_tim4 (void);
		long long Read_tim_c4 (void);
		long long Read_HiSC_out (void);
//		long long Read_IACT(int flag, int next,int add);
//		long long Read_HiSC(int flag, int next,int add);
//		long long Read_HiSC(int flag, int next,int add);
//		long long Read_HiSC_old(void);

//  Common:
		long long GetDtime(int type);
		int GetDelay (int clast);
		int ReRead (unsigned char ch1, unsigned char ch0);
		void GetTime (unsigned char ctt[8],int *h,int *m,int *s,int *mls,int *mks,int *dns);
		void GetNewTime (unsigned char ctt[8]);
		int GetClock (long long times,int *h,int *m,int *s,int *mls,int *mks,int *dns);

//  Save  new data:
		int SaveHist_GRANDE(void);
		int SaveHist_GRANDE_01(void);
		int SaveData_GRANDE(void);
		int SaveData_T133(void);
		int SaveData_HiSCORE(void);

//		int SaveDataGist(FILE *fff,int key);
//		int SavePedestalGist(void);
//		int GetPedestalGist(void);
//		int GetPedestal(char *fileout);
	private:
};
//====================================================================
//====================================================================
//====================================================================
long long Data::Read_SIPM(int key_add, int key)
{
int kk=0;
int ddd=0;
unsigned long Finish=0;



	err_data=0;

    if (key_add==2) goto DATA_NEW;

HEADER_NEW:

	for (int j=0;j<70000;j++)  { buf[j]=0; }
	for (int j=0;j<70000;j++) { data[j]=0; }

    // ====   read header ===========

	kk = fread( &buf, 24, 1, fdat );
	if(kk!=1) return -1;

	sidi = buf[1]*256+buf[0];
	NumBytes = ((buf[3]&0xff)*256)+(buf[2]&0xff);

	NumEvent = ((unsigned long)buf[7]<<24) + ((unsigned long)buf[6]<<16) + ((unsigned long)buf[5]<<8)           + ((unsigned long)buf[4]);

    //GetAddBytes(buf+8,&s_add,&mls_add,&mks_add,&dns_add,&maska_key);
	GetTime(buf+12,&h,&m,&s,&mls,&mks,&dns);
	TimeEvent = GetDtime(0);

//    printf("sidi=%i  NumBytes=%i  Number=%lld\n",sidi,NumBytes,NumEvent);
//	SaveHDR(fhdr);
//	Errors_IACT(&err_data,&maska_key);
    // ===== end of read header  ======

    // ===== read data

	Nrate++;

DATA_NEW:

	kk = fread( &data, NumBytes, 1, fdat );
	if(kk!=1) {
		printf("Fragmentary Data:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Fragmentary Data:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    err_data=8;
//press_any_key();
	    return -2;  //  недописан кусок дочитования данных, если данные записаны в разные файлы
	}

	Finish = ((unsigned long) data[NumBytes-4] << 24) + ((unsigned long) data[NumBytes-3]<<16) 
		   + ((unsigned long) data[NumBytes-2] <<  8) +  (unsigned long) data[NumBytes-1];

	if (Finish != 0xFFFFFFFF) {
		printf("Wrong FFFFFFFF:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Wrong FFFFFFFF:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    err_data=9;
	    nerr[9]++;
	    kk=ReRead(data[130],data[131]);
//press_any_key();
	    if (kk==-1) return -1;
	    else { RejectEvent++; goto HEADER_NEW; }
	}


//	if ( RestartIACT(maska_key) == 1 ) goto HEADER_NEW;  //  for 2017-18

	NumEvent_prim  = NumEvent;
	TimeEvent_prim = TimeEvent;

//	SaveHDR(fhdr);

//	if ( RejectIACT() == 1 ) goto HEADER_NEW;
//		memcpy(&hd,buf,24);
//		memcpy(&data,data,NumBytes);

	if (tim_start==0) tim_start=TimeEvent;
	tim_fin = TimeEvent;
//    printf("tim_start=%Ld  tim_fin=%Ld\n",tim_start,tim_fin);

/*
    for (int ich = 0; ich < 32; ich ++) {
        for (int ibin = 0; ibin < 1024; ibin ++) {
            Ampl[ich][ibin] = 0;
        }
    }
    */

    int NumBytesCh = (NumBytes-4);
    /// если пакет пустой, то его не обрабатываем
    if (NumBytesCh <= 0) // goto HEADER_NEW;
        return TimeEvent;

//    printf("!!! sidi=%i  NumBytes=%i    NumBytesCh=%i\n",sidi,NumBytes,NumBytesCh);


    int ibin=0;
    int ich_prim=0,ich=0;

	for(int ii=0; ii<NumBytesCh; ii+=2) 
    {
        // calculate channel number
        ich = data[ii+1] >> 4;
        if(sidi == 16641) // if second packet
            ich += 16;

        if (ich != ich_prim) { 
            ich_prim=ich;
            ibin=0;
 //press_any_key();
        }
   
        ddd = (data[ii+1] * 256 + data[ii]);
        ddd &= 4095;
        Ampl[ich][ibin] = (float)ddd-2048.;
    
     //       if (ibin<10) printf("ich=%i  ii=%i   ibin=%i  0x%02X 0x%02X   ampl=%.2f   ddd=%d\n",ich,ii,         ibin,data[ii],data[ii+1],Ampl[ich][ibin], ddd);
            ibin++;
    }

//press_any_key();
//============================   read data

return TimeEvent;
}
//====================================================================
int Data::GetAddBytes(unsigned char ctt[8],int *ss,int *mlss,int *mkss,int *dnss,int *maska_key)
{
unsigned char bufAdd[10]={0};
int hhh=0,mmm=0,sss=0,mlsss=0,mksss=0,dnsss=0;
int maska=0;
unsigned long MaskaTRIGG=0;
unsigned long MaskaBSM=0;

if (lll<=20171010) {

	for(int ii=0; ii<8; ii++) {
	    if (ii<4)	bufAdd[ii] = ctt[ii];
	    else 	bufAdd[ii] = 0;
	}
	GetTime(bufAdd,&hhh,&mmm,&sss,&mlsss,&mksss,&dnsss);
	*ss=sss;   *mlss=mlsss;   *mkss=mksss;   *dnss=dnsss; 
/*
	for(int ii=0; ii<4; ii+=2) {
	    data_time[ii/2]=buf[ii+9]*256+buf[ii+8];
//	    printf("time:  buf[%d] = 0x%x  buf[%doo] = 0x%x    data[%d] = 0x%x\n",
//		(ii+13) , buf[ii+13], ii+12, buf[ii+12], ii/2, data_time[ii/2] );
	    add_byte[ii]=buf[ii+8];
	    add_byte[ii+1]=buf[ii+9];
	}
	    dns = ( data_time[0] & 0x7f ) * 10;
	    mks = ( data_time[0] & 0xff80 ) >> 7;
	    mks |= (data_time[1] & 1) << 9;
	    mls = ( data_time[1] & 0x7fe ) >> 1;
	    s   = (( data_time[1] & 0xf800 ) >> 11);
*/
}  //  old versia proshivki

if (lll>20171010) {
	MaskaTRIGG = (unsigned long)ctt[2]*256L*256L
		+ (unsigned long)ctt[1]*256L
		+ (unsigned long)ctt[0];
	MaskaBSM = (unsigned long)(pow(2,(Number-1)));
	if (MaskaTRIGG>MaskaBSM) maska=1;
	else  maska=0;

	*maska_key = maska;
//if (maska_key>0) {
//printf("BSM%i  MaskaBSM=0x%lX  TRIGG=0x%lX(%02X,%02X,%02X)     maska_key=%i\n",
//Number,MaskaBSM,MaskaTRIGG,buf[8],buf[9],buf[10],maska_key);
//press_any_key();
//}
}  //  new versia proshivki
return 1;
}
//====================================================================
int Data::SaveHDR(FILE *fff)
{
	if (fff!=NULL) {
	    if (lll<=20171010)
		fprintf(fff,"%4i%5i%5i%12Ld   %02d,%03d.%03d.%03d   %02d:%02d:%02d,%03d.%03d.%03d\n",
		    sidi,NumBytes,por,NumEvent,s_add,mls_add,mks_add,dns_add,h,m,s,mls,mks,dns);
	    if (lll>20171010)
		fprintf(fff,"%4i%5i%5i%12Ld   %02X,%02X,%02X,%02X   %02d:%02d:%02d,%03d.%03d.%03d\n",
		    sidi,NumBytes,por,NumEvent,buf[8],buf[9],buf[10],buf[11],h,m,s,mls,mks,dns);
	}
return 1;
}
//====================================================================
//====================================================================
//====================================================================
//====================================================================

#endif
