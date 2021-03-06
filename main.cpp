//=========================================================
//
//   ANALYSIS OF TUNKA-IACT DATA :  NOV.2016
//
//=========================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define TEST
//#define HEADER_ONLY
#define NCLAST 25

#include "tools.h"

unsigned long lll, nnn, mmm, mmm_add;
int day, mon, year,md,year_min, ndays=0;

//long long maxi_time=0;

int MODA_TREAT=-1;	//  =0  -  standart treat
		//  =1  -  full treat
		//  =2  -  only HDR
		//  =3  -  resave outs to outs.cut



#define TIME_SYNC 10000
#define MAX_AMPL 1
#define COIN_KEY 1	//  1 - by Times of Events
			//  2 - by Numbers of Events
int FileMax=0;	//  0 - all data in one *.out file
		//  1 - in many *.out files

#define DELAY_KEY 0  //  0  only time of events
		    //  1  time + delay

int coin_Global=1;

int coin=0;

unsigned int dtime_hist[TIME_SYNC/100+1];
int MODE=0;  // 0 - only coin
             // 1 - coin+maxAmpl

//long long dtime_start=0L,dtime_fin=0L;


//#include "/home/krs/include/t133.h"

FILE *fftag,*ff111,*ffped, *ffout, *fftim, *fferr, *ffstat,*ffrate, *ffbsm, *ffcut, *fftim_cut,*fftimarray,*fftimarray_cut;

char tagname[]="00_target.lst";

char pathfile[200];
char pathout[200];
char pathout_cut[200];
char pathout_tmp[200]="./OUTs/";
//char pathout_tmp[200]="/k1/taiga_pool/IACT/";
char pathped[200];
char pathcal[200];
char dirname[200];
char pathtimarray[200]="./tim-array/";




char pathfile_tmp[200];
//char pathfile_ped[200];
//char pathfile_hist[200];
char fname[200];
char statname[200]="sipm.report";
char errname[200];
char outname[200];
char outname_cut[200];
char timarrayname[200];
char timarrayname_cut[200];
char timname[200];
char pedname[200];
char ratename[200];
char bsmname[200];
char coiname[200]="111";

char fname_xy[200];
char fname_pe[200];

//int Nsize[10001];
int multi[NCLAST];
int multi_cut[NCLAST];
int multi4;

int IACT_NN=1;


//float maxAmpl=0;
//float lmaxAmpl=0;

//int NumRateKK=0;
//int clast_maxi=0;

long long TimeRate=0;
long long TimeOut=30.E+6;  //  20 mks
long long LocalTime=0L;
int NumRate=0;

int Test_GEO=0;
int key_timarray=0;

int NtimeMLS[1001];
int NtimeMKS[1001];


//int hdip,mdip,sdip,mlsdip,mksdip,dnsdip;
//long long DTimeDip=0;
//long long TimeDip=0L;
//int keyDip=0;

int h_st,m_st,s_st,mls_st,mks_st,dns_st;
int h_fn,m_fn,s_fn,mls_fn,mks_fn,dns_fn;

int data_accept=0;
int ped_accept=0;
unsigned long test_duo=0L,test_trio=0L,test_duo_trio=0L,test_err=0;


//int portion=0;

#include "exact.h"
//#include "get_hist.c"

#include "data.c"

Data DATA[NCLAST];

//#include "read_data.c"
//#include "get_ped.c"

/*
typedef struct {
	int Ampl[8];
	float Fwhm[8];
	float bbb[8];
	int bb[8],bm[8],be[8];
	float smin[8];
} Ssecond;
Ssecond SD[NCLAST];


typedef struct {
	FILE *fff;
	char name[80];
	int end;
} SF;
SF file[NCLAST];
*/


//int status[NCLAST];
//long long dtime[NCLAST];
//long long dtime_cpy[NCLAST];


//int stat=0;


/*
typedef struct {
	long Nown;
	int hour,min,sec;
	int mlsec;
	int h,m,s,mls,mks,dns;
	int stat[NCLAST];
	double dtime[NCLAST];
	int run[NCLAST];
	char pathfile[80];
	char filename[80];
	char fileout[80];
	char filetime[80];

} Sdata;
Sdata DATA[NCLAST];
*/

//int invalid[NCLAST];
//long times=0;
//int ntim=0;



//long Nev[NCLAST];
//long Nev_cpy[NCLAST];




//int coin[NCLAST];

//#include "graphics.h"
//#include "drawdata.h"
//#include"getfname.h"
//#include "read_133.h"
//#include "analysis.h"
//#include "filesave.h"

//int clast, key=0;
//int kk=0;
//int add=0;

//#include "main-lib.cpp"
//=========================================================
int ZeroData(void);
//int DipTime(void);
int Read_Target_List (FILE *fff, int moda);
//int OpenNewFile(char *path, unsigned long nnn, int por, int flag );

//double DELAY_TIME (int claster);
//int ReadFileTimes (FILE *stream, int claster);
//int SaveData (int claster);
long long ReadData (int claster);
int mini_times(void);
int SaveTim(int clast);
int SaveAmpl(int clast,FILE *fff);
int SavePaw(int clast);
int SaveTime(int clast,FILE *fff);
int SaveTimArray(int clast,FILE *fff);
//int Get_Pedestal(int kk);
//int Get_Coeffs(char* fname);

int mini_times_and_Num(long long Num);
int Synchro_by_Number(long long Num);

int SelectAmpl (void);

//int mini_times(double *dtimes, int *stat);
//int mini_times(double *dtimes, int *stat);
//int ReSave_AddFiles(void);
//int GetCoRatesAndDip(long long maxi_time,int kk);

//int ActivePixels(void);

//int SigmaPeds(void);
//int GetPedestal(char *pathout);
//int TEST();
FILE *OpenOutFile(char *path, int por, int flag);
//int ReadOUTs (FILE *fff);
int OnlyHEADER (void);
int GetFullData(int Dpor);
int Read_XY(char *fname);
int Read_PE(char *fname);
int CUT_and_GetSpectre (FILE *fff);
int Read_GEOMETRY(char *fname,int iact,int topology);
//====================================================================
#include "read_data.c"

//=========================================================

long long ddtime=0;
long long GlobalNum=0L;
long long LocalNum=0L;
long long RejectNum=0L;
long long NeventCut=0;
long long AllEvents=0;
double time_start=0,time_fin=0,time_full=0, time_start_Global=0L;
int restart_count=0;


int main (int argc, char *argv[])
//int main ()
{
int rt=10;
//char fname[200];
//FILE *fff;
//char st[200];
FILE *fff;
//int kk=0,kkk=0;
int full=0;
//int full_bsm=0;
//int full_bsm_restart=0;
int stop=0;
int por=0;






    if ( (fftag = fopen(tagname,"r"))==NULL ) {
	printf("\n!!!   Not TARGET file ::  %s   !!!\n\n",tagname);
	return -1;
    }



    do {
	ffstat = fopen(statname,"at");

	rt = Read_Target_List (fftag, 0);  //here
	if (rt==-10) continue;  //  end target

	ZeroData();

	GlobalNum=0;
	LocalNum=0;
	AllEvents=0;
	time_fin = 0;
	time_start = 0;



//	fftim = fopen(timname,"wt");
//	fftimarray = fopen(timarrayname,"wt");
	fferr = fopen(errname,"at");
//	ff111 = fopen(coiname,"wt");
//	ffrate = fopen(ratename,"wt");

/*
	for (int clast=1;clast<NCLAST;clast++) {
	    if ( DATA[clast].run_dir==0 ) continue;
	    DATA[clast].fhdr = fopen(DATA[clast].filehdr,"wt");
	}
*/

full=0;
	for (int clast=1;clast<NCLAST;clast++) {
	    if ( DATA[clast].run_dir==0 ) continue;
		DATA[clast].run=1;
		DATA[clast].stop=0;
		DATA[clast].por=1;
		full++;
	}
	DATA[0].por=1;

qq(200);

    for (int clast=1;clast<NCLAST;clast++) {

	if ( DATA[clast].run_dir==0 ) continue;

	for( int ifl=1;ifl<1001;ifl++) {

	    por = ifl;

	    DATA[clast].fdat = DATA[clast].OpenFile(DATA[clast].pathfile,&por,0,&stop,1);

	    if ( (DATA[clast].run<0) || (DATA[clast].stop<0) ) goto END;



printf("ifl=%i   stop=%i   run=%i   por=%i\n",ifl,DATA[clast].stop,DATA[clast].run,por);
//press_any_key();


	    if (DATA[clast].run>0) ffout = OpenOutFile(pathout,por,2);
	    if (DATA[clast].stop>0) fclose(ffout);


	    if (DATA[clast].stop>0) continue;


	    do {

		ddtime = ReadData(1);  // read_data.c

		if (ddtime>0) {

		    if (DATA[1].sidi==16640) {

			GlobalNum=DATA[1].NumEvent;
			LocalNum=DATA[1].NumEvent;
			AllEvents++;
		    }
		    time_fin = DATA[1].tim_fin;
		    time_start = DATA[1].tim_start;
		    if (DATA[1].sidi==16641) SaveAmpl(1,ffout);
		}


	    } while (ddtime>0);

	    fclose(DATA[clast].fdat);
	    fclose(ffout);
	}
    }


END:

//	GlobalNum+=LocalNum;
//	time_full += (time_fin-time_start);
	time_full += (time_fin-time_start);
	time_full *= 1.E-9;

	NeventCut=AllEvents;



printf("\n   RUN=%06ld.%02d   GlobalNum=%Ld   RejectNum=%Ld   portions=%i\n   All Events=%Ld   Nev(cut)s=%Ld    dtime=%.2fs (%.2fh)   CoRate(cut)=%.3f\n",
mmm,md,GlobalNum,RejectNum,DATA[0].por,AllEvents,NeventCut,(float)time_full,(float)time_full/3600., (float)NeventCut/(float)time_full);
//fprintf(ffstat,"   RUN=%06ld.%02d   GlobalNum=%ld   RejectNum=%ld\n   All Events=%ld   Nev(cut)s=%ld    dtime=%.2fs (%.2fh)   CoRate(cut)=%.3f\n",
//mmm,md,GlobalNum,RejectNum,AllEvents,Nevent,(float)time_fin,(float)time_fin/3600., (float)Nevent/(float)time_fin);
fprintf(ffstat,"   RUN=%06ld.%02d   GlobalNum=%Ld   RejectNum=%Ld   portions=%i\n   All Events=%Ld   Nev(cut)s=%Ld    dtime=%.2fs (%.2fh)   CoRate(cut)=%.3f\n",
mmm,md,GlobalNum,RejectNum,DATA[0].por,AllEvents,NeventCut,(float)time_full,(float)time_full/3600., (float)NeventCut/(float)time_full);


//	fclose(fftim);
//	fclose(fftimarray);
	fclose(fferr);
//	fclose(ffout);
//	fclose(ff111);
//	fclose(ffrate);


/*
	kk=0;
	for(int clast=1;clast<NCLAST;clast++) {
	    if (DATA[clast].RejectEvent) kk++;
	}
	if (kk) {
	    strcpy(fname,pathout);
	    strcat(fname,"EventsReject.dat");
	    fff = fopen(fname,"w");
	    for(int clast=1;clast<NCLAST;clast++) {
		if (DATA[clast].RejectEvent) fprintf(fff,"BSM#%02d%11ld\n",clast,DATA[clast].RejectEvent);
	    }
	    fclose(fff);
	}
*/


 
//  OUT files::
//--------------------------------------

	strcpy(fname,pathout);
	strcat(fname,"multi.dat");
	fff = fopen(fname,"w");
	for(int ii=1;ii<NCLAST;ii++) {
	    fprintf(fff,"%3i%11i\n",ii,multi[ii]);
	}
//	fprintf(ffout,"\n{%ld}   All Events=%ld   Nev(cut)s=%ld    dtime=%.2fs(%.2fh)   CoRate(cut)=%.3f\n",mmm,AllEvents+Nevent,Nevent,(float)time_fin,(float)time_fin/3600., (float)Nevent/(float)time_fin);
	    DATA[0].GetClock(time_start,&h_st,&m_st,&s_st,&mls_st,&mks_st,&dns_st);
	    DATA[0].GetClock(time_fin,&h_fn,&m_fn,&s_fn,&mls_fn,&mks_fn,&dns_fn);
	fprintf(fff,"\{%06ld.%02d}   GlobalNum=%Ld   RejectNum=%Ld   portions=%i\n   All Events=%Ld   Nev(cut)s=%Ld    dtime=%.2fs (%.2fh)   CoRate(cut)=%.3f\n",
		mmm,md,GlobalNum,RejectNum,DATA[0].por,AllEvents,NeventCut,(float)time_full,(float)time_full/3600., (float)NeventCut/(float)time_full);
	fprintf(fff,"%02d:%02d:%02d,%03d.%03d.%03d   --   %02d:%02d:%02d,%03d.%03d.%03d\n",
		h_st,m_st,s_st,mls_st,mks_st,dns_st,
		h_fn,m_fn,s_fn,mls_fn,mks_fn,dns_fn);

//	if(Test_GEO==1) fprintf(fff,"test_duo=%ld   test_trio=%ld   test_duo_trio=%ld   test_err=%ld\n",
//		test_duo,test_trio,test_duo_trio,test_err);

	fclose(fff);

//--------------------------------------



	fclose(ffstat);

    } while(rt!=-10);

    fclose(fftag);
//    fclose(ffstat);
printf("Qu-Qu::   FINISH\n");
return 0;
}
//====================================================================
//=========================================================
//====================================================================
//=========================================================
//=====================================================================

FILE *OpenOutFile(char *path, int por, int flag)
{
char st[100];
FILE *ftmp;
int res=0;

printf("flag= %d\n", flag);
if (flag==1) {
	strcpy(outname,path);
	strcat(outname,"outs/");
	res=mkdir(outname,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname);
//	    press_any_key();
	}
	sprintf(st,"%06ld.out",mmm);
	strcat(outname,st);
	sprintf(st,"_%03d",por);
	strcat(outname,st);
	printf("outname={%s}\n",outname);
	if ( (ftmp = fopen(outname,"rt")) == NULL ) return NULL;
}
if (flag==2) {
	strcpy(outname,path);
	strcat(outname,"outs/");
	res=mkdir(outname,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname);
//	    press_any_key();
	}
	sprintf(st,"%06ld.out",mmm);
	strcat(outname,st);
	sprintf(st,"_%03d",por);
	strcat(outname,st);
	printf("outname={%s}\n",outname);
	ftmp = fopen(outname,"wt");
}
if (flag==3) {
	strcpy(pathout_cut,"./OUTs.cut/");
	strcpy(outname_cut,"./OUTs.cut/");
	res=mkdir(outname_cut,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname_cut);
//	    press_any_key();
	}
	sprintf(st,"%06ld.%02d/",mmm,md);
	strcat(pathout_cut,st);
	strcat(outname_cut,st);
	res=mkdir(outname_cut,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname_cut);
//	    press_any_key();
	}
	strcat(outname_cut,"outs/");
	res=mkdir(outname_cut,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname_cut);
//	    press_any_key();
	}
	sprintf(st,"%06ld.out",mmm);
	strcat(outname_cut,st);
	sprintf(st,"_%03d",por);
	strcat(outname_cut,st);
	printf("outname={%s}\n",outname_cut);
	ftmp = fopen(outname_cut,"wt");
}
if (flag==4) {
	strcpy(pathout_cut,"./OUTs.cut/");
	strcpy(outname_cut,"./OUTs.cut/");
	res=mkdir(outname_cut,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname_cut);
//	    press_any_key();
	}
	sprintf(st,"%06ld.%02d/",mmm,md);
	strcpy(pathout_cut,st);
	strcat(outname_cut,st);
	res=mkdir(outname_cut,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",outname_cut);
//	    press_any_key();
	}
	sprintf(st,"%06ld.tim-coin.%02d.cut",mmm,md);
	strcat(outname_cut,st);
	printf("timname={%s}\n",outname_cut);
	ftmp = fopen(outname_cut,"wt");
}
if (flag==5) {
//	strcpy(pathout_cut,"./OUTs.cut/");
//	strcpy(pathtimarray,"./tim-array/");
	res=mkdir(pathtimarray,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",pathtimarray);
//	    press_any_key();
	}
	strcat(timarrayname_cut,pathtimarray);
	sprintf(st,"%06ld_%03d.tim-array",mmm,IACT_NN+60);
	strcat(timarrayname_cut,st);
	printf("timarray={%s}\n",timarrayname_cut);

	if (mmm==mmm_add) ftmp = fopen(timarrayname_cut,"at");
	if (mmm!=mmm_add) ftmp = fopen(timarrayname_cut,"wt");
}

//	qq(109);

//if (ftmp!=NULL) qq(12345);
//	qq(1091);

//printf("path={%s}   outfile={%s}\n",path,outname);
return ftmp;
}
//=====================================================================
//====================================================================
//====================================================================
/*
int CUT_and_GetSpectre (FILE *fff)
{
char ch[100];
int clast=0;
int coin_dat=0;
int kk=0;
int ddd,stat;
//int peds=0;
//float maxAmpl=0;
//int maxPMT=-1;
//int maxPMT_2=-1;
//int maxPMT_3=-1;
float Ampl_pe=0;
float Ampl_pe_clean=0;
float dist=0;
int iclast=0,kcoin=0;
//unsigned long Nev;
//int hh,mm,ss,mlss,mkss,dnss;



    for(int clast=1;clast<24;clast++) {
	DATA[clast].stat=0;
	DATA[clast].Number=0;
	for(int ii=0;ii<64;ii++) {
	    DATA[clast].valid[ii]=0;
	    DATA[clast].Ampl_pe[ii]=-1000.;
	}
    }


//qq(555);

	kk = fscanf(fff,"%d",&coin_dat);

//printf("kk=%i  coin_dat=%i\n",kk,coin_dat);

	if (kk<0) return kk;

	Ampl_pe=0;
	Ampl_pe_clean=0;

    kcoin=0;

    for(int ico=0;ico<coin_dat;ico++) {
//printf("kk=%i  coin_dat=%i\n",kk,coin_dat);

	fscanf(fff,"%d%Ld%d%1s%d%1s%d%1s%d%1s%d%1s%d",
		&iclast,&DATA[0].NumEvent,
		&DATA[0].h,&ch[0],&DATA[0].m,&ch[0],&DATA[0].s,&ch[0],
		&DATA[0].mls,&ch[0],&DATA[0].mks,&ch[0],&DATA[0].dns);
//	printf("%d  %ld %d:%d:%d,%d.%d.%d   coin_dat=%i   ico=%i\n",iclast,DATA[0].NumEvent,
//		DATA[0].h,DATA[0].m,DATA[0].s,DATA[0].mls,DATA[0].mks,DATA[0].dns,coin_dat,ico);
		clast = iclast;

		DATA[clast].Number=clast;
		DATA[clast].stat=1;
		DATA[clast].NumEvent = DATA[0].NumEvent;
		DATA[clast].h = DATA[0].h;
		DATA[clast].m = DATA[0].m;
		DATA[clast].s = DATA[0].s;
		DATA[clast].mls = DATA[0].mls;
		DATA[clast].mks = DATA[0].mks;
		DATA[clast].dns = DATA[0].dns;
		DATA[clast].ready=1;

		DATA[0].TimeEvent = DATA[0].GetDtime(0);
		DATA[clast].TimeEvent = DATA[clast].GetDtime(0);
		DATA[clast].Nrate++;

//	maxAmpl=0;
//	maxPMT=-1;
	
	for(int ii=0;ii<64;ii++) {
	    fscanf(fff,"%i%i",&ddd,&stat);

	    DATA[clast].Ampl[ii]=ddd;
	    DATA[clast].Stat[ii]=stat;

//printf("666:   clast=%i   id=%i   pe=%.f  sens=%.f\n",clast,ii,DATA[clast].PE_CODE[ii],DATA[clast].SENS[ii]);
	    if (DATA[clast].PE_CODE[ii]==0.) continue;
	    if (DATA[clast].SENS[ii]==0.) continue;
	    if (DATA[clast].PE_CODE[ii]==-1000.) continue;
	    if (DATA[clast].SENS[ii]==-1000.) continue;

	    DATA[clast].Ampl_pe[ii]=ddd;
//	    if (DATA[clast].Ampl_pe[ii]>3000) DATA[clast].Ampl_pe[ii]=DATA[clast].Ampl_pe[ii]
	    DATA[clast].Ampl_pe[ii] -= DATA[clast].ped[ii];
	    DATA[clast].Ampl_pe[ii] /= DATA[clast].PE_CODE[ii];
	    DATA[clast].Ampl_pe[ii] /= DATA[clast].SENS[ii];
//printf("clast=%i  Nev=%ld  id=%i  ddd=%i   ampl=%.f  ped=%.f  pe=%.2f   sens=%.2f\n",
//	clast,DATA[clast].NumEvent,ii,ddd,DATA[clast].Ampl_pe[ii],DATA[clast].ped[ii],DATA[clast].PE_CODE[ii],DATA[clast].SENS[ii]);
	    if (DATA[clast].Ampl_pe[ii]<0) continue;

		if ( (int)DATA[clast].Ampl_pe[ii]<5000) DATA[clast].spe_det[ii][(int)DATA[clast].Ampl_pe[ii]]++;
		else DATA[clast].spe_det[ii][5000]++;
	} //  ich
//press_any_key();
	for(int ii=0;ii<64;ii+=2) {
	    if (DATA[clast].Ampl_pe[ii]<0) continue;
	    Ampl_pe += DATA[clast].Ampl_pe[ii];
//	    if (DATA[clast].Ampl_pe[ii]>=4) DATA[clast].valid[ii]=2;
//	    if (DATA[clast].Ampl_pe[ii]>=6) DATA[clast].valid[ii]=2;
//	    if (DATA[clast].Ampl_pe[ii]>=8) DATA[clast].valid[ii]=2;
	    if (DATA[clast].Ampl_pe[ii]>=10) DATA[clast].valid[ii]=2;
	}
    } // clast


    for(int clast=1;clast<24;clast++) {

	if ( DATA[clast].stat==0 ) continue;

	for(int ii=0;ii<64;ii+=2) {

	    if (DATA[clast].valid[ii]!=2) continue;
	    if (DATA[clast].Ampl_pe[ii]<0) continue;
	    if (DATA[clast].XXpmt[ii]==-1000.) continue;
	    if (DATA[clast].YYpmt[ii]==-1000.) continue;


	    for (int jclast=1;jclast<24;jclast++) {
		if (DATA[jclast].stat==0) continue;

		for(int jj=0;jj<64;jj+=2) {
		    if (DATA[jclast].valid[jj]==2) continue;
		    if (DATA[jclast].Ampl_pe[jj]<0) continue;
		    if (DATA[jclast].XXpmt[jj]==-1000.) continue;
		    if (DATA[jclast].YYpmt[jj]==-1000.) continue;

		    dist=sqrt( (DATA[clast].XXpmt[ii]-DATA[jclast].XXpmt[jj])*(DATA[clast].XXpmt[ii]-DATA[jclast].XXpmt[jj]) + 
			(DATA[clast].YYpmt[ii]-DATA[jclast].YYpmt[jj])*(DATA[clast].YYpmt[ii]-DATA[jclast].YYpmt[jj]) );
		    if (dist>4) continue;

//		    if (DATA[jclast].Ampl_pe[jj]>=2) DATA[jclast].valid[jj]=1;
//		    if (DATA[jclast].Ampl_pe[jj]>=3) DATA[jclast].valid[jj]=1;
//		    if (DATA[jclast].Ampl_pe[jj]>=4) DATA[jclast].valid[jj]=1;
		    if (DATA[jclast].Ampl_pe[jj]>=5) DATA[jclast].valid[jj]=1;
		}
	    }
	}

    }  //  clast

    for(int clast=1;clast<24;clast++) {
	if ( DATA[clast].stat==0 ) continue;
	for(int ii=0;ii<64;ii+=2) {
	    if (DATA[clast].valid[ii]==0) continue;
	    Ampl_pe_clean += DATA[clast].Ampl_pe[ii];
	}
//printf("cl=%i   Num=%ld   AmaxPMT(%i)=%.f  AmaxPMT2(%i)=%.f  AmaxPMT3(%i)=%.f  Ampl_pe=%.f  Ampl_clean_pe=%.f\n",
//	clast,DATA[clast].NumEvent,maxPMT,DATA[clast].Ampl_pe[maxPMT],
//	maxPMT_2,DATA[clast].Ampl_pe[maxPMT_2],maxPMT_3,DATA[clast].Ampl_pe[maxPMT_3],Ampl_pe,Ampl_pe_clean);

    }  // coin


    kcoin=0;

    for(int clast=1;clast<24;clast++) {
	if ( DATA[clast].stat==0 ) continue;
	DATA[clast].stat=0;
	for(int ii=0;ii<64;ii+=2) {
	    if (DATA[clast].valid[ii]==0) continue;
	    DATA[clast].stat=1;
	}
	if (DATA[clast].stat==1) kcoin++;
//printf("cl=%i   Num=%ld   AmaxPMT(%i)=%.f  AmaxPMT2(%i)=%.f  AmaxPMT3(%i)=%.f  Ampl_pe=%.f  Ampl_clean_pe=%.f\n",
//	clast,DATA[clast].NumEvent,maxPMT,DATA[clast].Ampl_pe[maxPMT],
//	maxPMT_2,DATA[clast].Ampl_pe[maxPMT_2],maxPMT_3,DATA[clast].Ampl_pe[maxPMT_3],Ampl_pe,Ampl_pe_clean);

    }  // clast

    if (kcoin>0) {
	multi_cut[kcoin]++;
	fprintf(ffcut,"%3i\n",kcoin);
	fprintf(fftim_cut,"%3i\n",kcoin);

	key_timarray=0;
	for(int clast=1;clast<24;clast++) {
	    if ( DATA[clast].stat==0 ) continue;
	
		SaveAmpl(clast,ffcut);
		SaveTime(clast,fftim_cut);
		if (key_timarray==0) {
		    SaveTimArray(clast,fftimarray_cut);
		    key_timarray=1;
		}
	}
    }

		if ((Ampl_pe)<5000)  DATA[0].spe[(int)Ampl_pe]++;
		else DATA[0].spe[5000]++;
		if ((Ampl_pe_clean)<5000)  DATA[0].spe_clean[(int)Ampl_pe_clean]++;
		else DATA[0].spe_clean[5000]++;

//press_any_key();
return 1;
}
*/
//====================================================================
/*
int ReadOUTs (FILE *fff)
{
char ch[100];
int clast=0;
int coin=0;
int kk=0;
int ddd,stat;
int peds=0;

	kk = fscanf(fff,"%i",&coin);
	if (kk<0) return kk;

    for(int ico=0;ico<coin;ico++) {
	fscanf(fff,"%d%Ld%d%1s%d%1s%d%1s%d%1s%d%1s%d",
		&clast,&DATA[0].NumEvent,
		&DATA[0].h,&ch[0],&DATA[0].m,&ch[0],&DATA[0].s,&ch[0],
		&DATA[0].mls,&ch[0],&DATA[0].mks,&ch[0],&DATA[0].dns);

		DATA[clast].Number=clast;
		DATA[clast].NumEvent = DATA[0].NumEvent;
		DATA[clast].h = DATA[0].h;
		DATA[clast].m = DATA[0].m;
		DATA[clast].s = DATA[0].s;
		DATA[clast].mls = DATA[0].mls;
		DATA[clast].mks = DATA[0].mks;
		DATA[clast].dns = DATA[0].dns;
		DATA[clast].ready=1;

		DATA[0].TimeEvent = DATA[0].GetDtime(0);
		DATA[clast].TimeEvent = DATA[clast].GetDtime(0);
		DATA[clast].Nrate++;

	for(int ii=0;ii<64;ii++) {
	    fscanf(fff,"%i%i",&ddd,&stat);
	    DATA[clast].Ampl[ii]=ddd;
	    DATA[clast].Stat[ii]=stat;
	    if ((ii&0x1)==0) {
		if(DATA[clast].Stat[ii]==0) peds=1;
		else peds=0;
	    }
	    if (peds==1) {
		if (ddd<=4100)  DATA[clast].hped[ii][ddd]++;
		else DATA[clast].hped[ii][4100]++;
		if (ddd<=4100)  DATA[clast].hped_max[ii][ddd]++;
		else DATA[clast].hped_max[ii][4100]++;
	    }
	    if (peds==0) {
		if (ddd<=4100)  DATA[clast].hampl[ii][ddd]++;
		else DATA[clast].hampl[ii][4100]++;
	    }
	}

    }  // coin
//press_any_key();
return 1;
}
*/
//====================================================================
//int mini_times(double *dtimes, int *stat)
int mini_times(void)
{
//int clast_mini=0;
//long long mini_time=1E+14;
long long mini_time=1;
int multi_time=0;
int dh=0;
//float maxAmpl=0;
//float lmaxAmpl=0;

printf("MINI  TIME\n");
//qq(11111);
//press_any_key();
    for (int clast=1;clast<NCLAST;clast++) {
	if ( DATA[clast].run==0 ) continue;
	DATA[clast].stat=0;
    }

    for (int clast=1;clast<NCLAST;clast++) {

	if ( DATA[clast].run==0 ) continue;

	if ( (DATA[clast].dtime>0) && (mini_time==1) ) mini_time=DATA[clast].dtime;

        if ( (DATA[clast].dtime>0) && (DATA[clast].dtime<mini_time) ) {
	    mini_time=DATA[clast].dtime;
//	    clast_mini=clast;
//printf("clast_mini=%i   mini_time=%e   stat=%i\n",clast_mini,mini_time,DATA[clast].stat);
	}
//	if (dtime_fin<DATA[clast].dtime) dtime_fin=DATA[clast].dtime;


//printf("clast=%i   dtime=%Ld   mini=%Ld\n",clast,DATA[clast].dtime,mini_time);
    }

//	if (dtime_start==0) dtime_start=mini_time;


//qq(100);

//    maxAmpl=0;
//    lmaxAmpl=0;
    multi_time=0;
    for (int clast=1;clast<NCLAST;clast++) {

	if ( DATA[clast].run==0 ) continue;

        if ( (DATA[clast].dtime-mini_time)<TIME_SYNC ) {
	    DATA[clast].stat=1;

	    dh = (int) ((DATA[clast].dtime-mini_time)/100);
	    if (dh>(TIME_SYNC/100)-1) dh = (TIME_SYNC/100)-1;
	    dtime_hist[dh]++;

//	    printf("dh=%i    hist=%i\n",dh,dtime_hist[dh]);

//	    maxAmpl+=DATA[clast].maxAmpl;

//	    if (clast<30) DATA[clast].stat=0;
//	    if (clast>30) multi_time++;

//	    if (clast>30) DATA[clast].stat=0;
//	    if (clast<30) multi_time++;

//   if ((fabs)(clast_mini-clast)!=30) multi_time++;
//	    if (((fabs)(clast_mini-clast)!=30) && (clast>30) ) multi_time++;
//	    if ( clast>30 ) 
	    multi_time++;

	}
//printf("clast_mini=%i   dtime(%i)=%Ld   stat=%i\n",clast_mini,clast,DATA[clast].dtime,DATA[clast].stat);
//printf("clast_mini=%i   dtime(%i)=%Ld   stat=%i\n",clast_mini,clast,DATA[clast].dtime,DATA[clast].stat);
    }

//qq(200);

//    if (multi_time>10) {
//printf("multi=%i   maxAmpl=%.0f\n",multi_time,maxAmpl);

//	maxAmpl/=15.;

//	if ( maxAmpl > MAX_AMPL) {
//	if (( maxAmpl > MAX_AMPL) && ( maxAmpl < 40)) {

//	    multi_time+=100;

//	    lmaxAmpl = log10((float)maxAmpl)*100.;
//	    if (lmaxAmpl<10000) Nsize[(int)lmaxAmpl]++;
//	    else Nsize[10000]++;

//	}

//maxAmpl=2;
/*
if (DATA[25].run_dir==1) {
    if (DATA[25].stat==1) multi_time+=100;
}
else {
    if (maxAmpl > MAX_AMPL) multi_time+=100;
}
*/

//multi_time+=100;
//press_any_key();
//}
return multi_time+100;
}
//=========================================================
int Synchro_by_Number(long long Num)
{
int clast_maxi=0;
long long maxi_time=0;
int multi_time=0;
long long ddtime[NCLAST];


	for (int clast=1;clast<NCLAST;clast++) {
	    ddtime[clast] = 0;
	    if ( DATA[clast].run==0 ) continue;
	    DATA[clast].stat=0;
	    ddtime[clast] = DATA[clast].dtime;
	}

	for (int clast=1;clast<24;clast++) {
	    if ( DATA[clast].run==0 ) continue;
	    if ( DATA[clast].stop==1 ) continue;
	    if (DATA[clast].NumEvent==Num) {
		DATA[clast].stat=1;
		DATA[clast].Nrate++;
		multi_time++;
	    }
	}
	if (multi_time==0) return 0;

	for (int clast=1;clast<NCLAST;clast++) {
	    if ( DATA[clast].run==0 ) continue;
	    if ( DATA[clast].stat==0 ) continue;

	    if ( (ddtime[clast]>0) && (maxi_time==0) ) maxi_time=ddtime[clast];
    	    if ( (ddtime[clast]>0) && (ddtime[clast]>=maxi_time) ) {
		maxi_time=ddtime[clast];
		clast_maxi=clast;
//printf("clast_maxi=%i   maxi_time=%Ld  stat=%i\n",clast_maxi,maxi_time,DATA[clast].stat);
	    }
	}



//printf("LocalTime=%Ld   Time=%Ld   dtime=%Ld\n",LocalTime,ddtime[clast_maxi],(ddtime[clast_maxi]-LocalTime)/1000);
	if (LocalTime>0) {
	    ddtime[0] = (ddtime[clast_maxi]-LocalTime)/1000;
	    if ( (ddtime[0]>=0) && (ddtime[0]<1001) )  {
		    NtimeMKS[(int)ddtime[0]]++;
	    }
	    if (ddtime[0]>1000) {
		ddtime[0]-=1000;
		if ( (ddtime[0]>=0) && (ddtime[0]<1001) )  {
		    NtimeMLS[(int)ddtime[0]]++;
		}
	    }
	}
	LocalTime = ddtime[clast_maxi];
//press_any_key();


	if (TimeRate==0) TimeRate=maxi_time;
	if ( (TimeRate>0) && ( (maxi_time-TimeRate)>=TimeOut ) ) {

//printf("111:timeRate=%Ld    maxi_time=%Ld   dt=%Ld \n",TimeRate, maxi_time,(maxi_time-TimeRate));
//	    if ( (maxi_time-TimeRate)<TimeOut*2 ) TimeRate+=TimeOut;
//	    else 
	    TimeRate=maxi_time;
//printf("    timeRate=%Ld    maxi_time=%Ld   dt=%Ld \n",TimeRate, maxi_time,(maxi_time-TimeRate));
	    DATA[0].GetClock(TimeRate,&DATA[0].h,&DATA[0].m,&DATA[0].s,&DATA[0].mls,&DATA[0].mks,&DATA[0].dns);
//	    fprintf(ffrate,"%02d:%02d:%02d,%03d.%03d.%03d     %i   %i\n",
	    fprintf(ffrate,"%02d:%02d:%02d,%03d.%03d.%03d    %i    %i\n",
		DATA[0].h,DATA[0].m,DATA[0].s,
		DATA[0].mls,DATA[0].mks,DATA[0].dns,DATA[0].por,
		DATA[0].Nrate);
//		NumRate);
		DATA[0].Nrate=0;
//		NumRate=0;
//press_any_key();

	}
	DATA[0].Nrate+=multi_time;
//	NumRate ++;

/*
int multi_stat=0;
	for (int clast=1;clast<2;clast++) {
	    if ( DATA[clast].run==0 ) continue;
	    if ( DATA[clast].stat==0 ) continue;
	    if (multi_stat==3) continue;
	    for(int ii=0;ii<64;ii+=2) {
		if (DATA[clast].Stat[ii]==1) multi_stat++;
	    }
	}

	if (multi_stat==3) multi_time+=100;
*/   //  top3



multi_time+=100;
//press_any_key();

    if (Test_GEO==1) {

int test_geo_duo=0,test_geo_trio=0;
unsigned long NumEv_err=0L;

	for(int clast=1;clast<23;clast++) {
	    if ( DATA[clast].run==0 ) continue;
	    if ( DATA[clast].stat==0 ) continue;

		for (int ii=0;ii<64;ii+=2) {
		    if (DATA[clast].Stat[ii]==0) continue;
//printf("clast=%i  Num=%ld   ich=%i   stat=%i\n",
//clast,DATA[clast].NumEvent,ii,DATA[clast].Stat[ii]);

		}
 

	    for(int n_sort=0;n_sort<3000;n_sort++) {

		if (DATA[clast].SORT[n_sort].num1==-1) continue;

		for (int ii=0;ii<64;ii+=2) {
		    if (DATA[clast].Stat[ii]==0) continue;

		    for(int jj=0;jj<64;jj+=2) {
			if (DATA[clast].Stat[jj]==0) continue;

			for(int kk=0;kk<64;kk+=2) {

///			    if (DATA[clast].Stat[kk]==0) continue;

		    if ( (ii==jj) || (jj==kk) || (ii==kk) ) continue;



//		    geo=0;

		    if (DATA[clast].SORT[n_sort].num3==-1) {
//			if ( ((DATA[clast].SORT[n_sort].nch1) == DATA[clast].Stat[ii]) &&
//			    ((DATA[clast].SORT[n_sort].nch2) == DATA[clast].Stat[jj]) ) test_geo++;
			if ( ((DATA[clast].SORT[n_sort].nch1) == ii) &&
			    ((DATA[clast].SORT[n_sort].nch2) == jj) ) {
				test_geo_duo++;
//				geo=1;
			}

/*
if (geo==1) {
fprintf(fferr,"clast=%i  Num=%ld   (%i,%i,%i)   i=%i(%i)  j=%i(%i)  k=%i(%i)   test_duo=%i\n",
    clast,DATA[clast].NumEvent,
    DATA[clast].SORT[n_sort].nch1,DATA[clast].SORT[n_sort].nch2,DATA[clast].SORT[n_sort].nch3,
    ii,DATA[clast].Stat[ii],jj,DATA[clast].Stat[jj],kk,DATA[clast].Stat[kk],test_geo_duo);
}
*/
//printf("clast=%i  Num=%ld   (%i,%i,%i)   i=%i(%i)  j=%i(%i)  k=%i(%i)   test=%i\n",
//clast,DATA[clast].NumEvent,
//DATA[clast].SORT[n_sort].nch1,DATA[clast].SORT[n_sort].nch2,DATA[clast].SORT[n_sort].nch3,
//ii,DATA[clast].Stat[ii],jj,DATA[clast].Stat[jj],kk,DATA[clast].Stat[kk],test_geo);
		    }
		    else {
//			if ( ((DATA[clast].SORT[n_sort].nch1) == DATA[clast].Stat[ii]) &&
//			    ((DATA[clast].SORT[n_sort].nch2) == DATA[clast].Stat[jj]) &&
//			    ((DATA[clast].SORT[n_sort].nch3) == DATA[clast].Stat[kk]) ) test_geo++;
			if ( ((DATA[clast].SORT[n_sort].nch1) == ii) &&
			    ((DATA[clast].SORT[n_sort].nch2) == jj) &&
			    ((DATA[clast].SORT[n_sort].nch3) == kk) ) {
				test_geo_trio++;
//				geo=1;
			}
/*
if (geo==1) {
fprintf(fferr,"clast=%i  Num=%ld   (%i,%i,%i)    i=%i(%i)  j=%i(%i)  k=%i(%i)   test_trio=%i\n",
    clast,DATA[clast].NumEvent,
    DATA[clast].SORT[n_sort].nch1,DATA[clast].SORT[n_sort].nch2,DATA[clast].SORT[n_sort].nch3,
    ii,DATA[clast].Stat[ii],jj,DATA[clast].Stat[jj],kk,DATA[clast].Stat[kk],test_geo_trio);
}
*/
//printf("clast=%i  Num=%ld  i=%i  j=%i  k=%i    ii=%i  jj=%i  kk=%i   iii=%i   jjj=%i   kkk=%i   test=%i\n",
//clast,DATA[clast].NumEvent,ii,jj,kk,
//DATA[clast].SORT[n_sort].nch1,DATA[clast].SORT[n_sort].nch2,DATA[clast].SORT[n_sort].nch3,
//DATA[clast].Stat[ii],DATA[clast].Stat[jj],DATA[clast].Stat[kk],test_geo);
		    }

//printf("clast=%i  i=%i  j=%i  k=%i    ii=%i  jj=%i  kk=%i   iii=%i   jjj=%i   kkk=%i\n",
//clast,ii,jj,kk,DATA[clast].SORT[n_sort].nch1,DATA[clast].SORT[n_sort].nch2,DATA[clast].SORT[n_sort].nch3,
//DATA[clast].Stat[ii/2],DATA[clast].Stat[jj/2],DATA[clast].Stat[kk/2]);

//press_any_key();



			}  //  kk
		    }  //  jj
		}  //  ii
	    }  // sort 

	    if ( (test_geo_duo==0) && (test_geo_trio==0) ) {
//		printf("  geo err\n");
//		press_any_key();

		NumEv_err = DATA[clast].NumEvent;

	    }
	    else {
//printf("clast=%i    Num=%ld   geo_duo=%i   geo_trio=%i\n",clast,DATA[clast].NumEvent,test_geo_duo,test_geo_trio);
	    }


	}  //clast



	    if ( (test_geo_duo!=0) && (test_geo_trio==0) ) test_duo++;
	    if ( (test_geo_duo==0) && (test_geo_trio!=0) ) test_trio++;
	    if ( (test_geo_duo!=0) && (test_geo_trio!=0) ) test_duo_trio++;
	    if ( (test_geo_duo==0) && (test_geo_trio==0) ) test_err++;

//printf("test_duo=%ld   test_trio=%ld   test_duo_trio=%ld\n",test_duo,test_trio,test_duo_trio);
//printf("test_duo=%ld   test_trio=%ld   test_duo_trio=%ld   test_err=%ld\n",
//		test_duo,test_trio,test_duo_trio,test_err);


	    if ( (test_geo_duo==0) && (test_geo_trio==0) ) {
//	    if (test_geo_duo==0) {
//		printf("  geo err\n");
//		test_err++;
//		press_any_key();
fprintf(fferr,"error=%ld   Num Event=%ld\n",test_err,NumEv_err);

	    }


    }   // test_geo


return multi_time;
}
//====================================================================
/*
//int mini_times_and_Num(unsigned long Num)
int Synchro_by_Number(unsigned long Num)
{
int clast_maxi=0;
//long long mini_time=1E+14;
//long long mini_time=0;
long long maxi_time=0;
int multi_time=0;
//int dh=0;
int hh=0,mm=0,ss=0,mlss=0,mkss=0,dnss=0;

long TimeOut=50.E+6;

long long ddtime=0L;

//float maxAmpl=0;
//float lmaxAmpl=0;

//printf("Global  Num=%ld\n",Num);


    for (int clast=1;clast<NCLAST;clast++) {
	if ( DATA[clast].run==0 ) continue;
	DATA[clast].stat=0;
    }
    multi_time=0;
    maxAmpl=0;
    lmaxAmpl=0;

    for (int clast=1;clast<24;clast++) {
	if ( DATA[clast].run==0 ) continue;
	if ( DATA[clast].stop==1 ) continue;
	if (DATA[clast].NumEvent==Num) {
	    DATA[clast].stat=1;
	    DATA[clast].Nrate++;
	    multi_time++;

//if (clast==8) {
//printf("Global=%ld   clast=%d   Num=%ld   multi=%i\n",Num,clast,DATA[clast].NumEvent,multi_time);
//press_any_key();

//}

	}
//press_any_key();
    }

    if (multi_time==0) return 0;

//press_any_key();

    for (int clast=1;clast<25;clast++) {

	if ( DATA[clast].run==0 ) continue;
	if ( DATA[clast].stat==0 ) continue;

if (DELAY_KEY==0) ddtime = DATA[clast].dtime;
if (DELAY_KEY==1) ddtime = DATA[clast].dtime+DATA[clast].Delay;



	if ( (DATA[clast].dtime>0) && (maxi_time==0) ) maxi_time=DATA[clast].dtime;

        if ( (DATA[clast].dtime>0) && (DATA[clast].dtime>=maxi_time) ) {
	    maxi_time=DATA[clast].dtime;
	    clast_maxi=clast;
//printf("clast_maxi=%i   maxi_time=%Ld  stat=%i\n",clast_maxi,maxi_time,DATA[clast].stat);
	}
//	if (dtime_fin<DATA[clast].dtime) dtime_fin=DATA[clast].dtime;
//printf("clast=%i   dtime=%Ld   maxi=%Ld\n",clast,DATA[clast].dtime,maxi_time);
    }

//	if (dtime_start==0) dtime_start=mini_time;
//printf("clast_maxi=%i                        maxi=%Ld\n",clast_maxi,maxi_time);




//qq(100);
//press_any_key();


	if ( DATA[25].run==1 ) {

//printf("clast=25   dtime=%Ld   maxi=%Ld\n",DATA[25].dtime,maxi_time-TIME_SYNC);

    if ( DATA[25].dtime<(maxi_time-TIME_SYNC) ) {
	for (int clast=1;clast<NCLAST-1;clast++) {
	    DATA[clast].stat=0;
	}


	    DATA[25].stat=1;
	    multi_time=1;
	    return 1;
    }
	}
//press_any_key();



	if (TimeRate==0) {
	    TimeRate=maxi_time;
	}

//printf("qqq1::  clast_maxi=%i   maxi_time=%Ld   time_rate=%Ld   dtime=%Ld\n",clast_maxi,maxi_time,TimeRate,(maxi_time-TimeRate));


	if ( (TimeRate>0) && ( (maxi_time-TimeRate)>=TimeOut ) ) {

	    TimeRate+=TimeOut;


//printf("clast_maxi=%i   maxi_time=%Ld   time_rate=%Ld   dtime=%Ld\n",clast_maxi,maxi_time,TimeRate,(maxi_time-TimeRate));



//	    DATA[clast_maxi].GetClock(maxi_time,&hh,&mm,&ss,&mlss,&mkss,&dnss);
	    DATA[clast_maxi].GetClock(TimeRate,&hh,&mm,&ss,&mlss,&mkss,&dnss);

	    fprintf(ffrate,"%02d:%02d:%02d,%03d.%03d.%03d     %i\n",
		hh,mm,ss,mlss,mkss,dnss,NumRate);

//	    printf("%02d:%02d:%02d,%03d.%03d.%03d     %i\n",
//		hh,mm,ss,mlss,mkss,dnss,NumRate);


//press_any_key();
//	    fprintf(ffrate,"%02d:%02d:%02d,%03d.%03d.%03d     %i\n",
//		DATA[clast_maxi].h,DATA[clast_maxi].m,DATA[clast_maxi].s,
//		DATA[clast_maxi].mls,DATA[clast_maxi].mks,DATA[clast_maxi].dns,
//		NumRate);


//		1.E+9*(float)NumRate/(float)TimeOut);

//	    printf("%02d:%02d:%02d,%03d.%03d.%03d   %i\n",
//		DATA[clast_maxi].h,
//		DATA[clast_maxi].m,
//		DATA[clast_maxi].s,
//		DATA[clast_maxi].mls,
//		DATA[clast_maxi].mks,
//		DATA[clast_maxi].dns,NumRate);

//	    printf("%02d:%02d:%02d,%03d.%03d.%03d   %i   %02d:%02d:%02d,%03d.%03d.%03d\n",
//		DATA[clast_maxi].h,
//		DATA[clast_maxi].m,
//		DATA[clast_maxi].s,
//		DATA[clast_maxi].mls,
//		DATA[clast_maxi].mks,
//		DATA[clast_maxi].dns,NumRate,
//		hh,mm,ss,mlss,mkss,dnss);

//press_any_key();
		NumRate=0;


//	    for (int clast=1;clast<NCLAST-1;clast++) {
//		if ( DATA[clast].run==0 ) continue;
//		fprintf(ffrate,"   %i",DATA[clast].Nrate);
//		printf("   %i",DATA[clast].Nrate);
//		DATA[clast].Nrate=0;
//	    }
//	    fprintf(ffrate,"\n");
//	    printf("\n");


	}





    for (int clast=25;clast<NCLAST;clast++) {

	if ( DATA[clast].run==0 ) continue;

        if ( (fabs)(DATA[clast].dtime-maxi_time)<TIME_SYNC ) {
	    DATA[clast].stat=1;

//	    dh = (int) ((DATA[clast].dtime-mini_time)/100);
//	    if (dh>(TIME_SYNC/100)-1) dh = (TIME_SYNC/100)-1;
//	    dtime_hist[dh]++;
	    multi_time++;

//press_any_key();
	}


    }





    for (int clast=1;clast<25;clast++) {

	if ( DATA[clast].stat==0 ) continue;

//	    printf("dh=%i    hist=%i\n",dh,dtime_hist[dh]);

	    maxAmpl+=DATA[clast].maxAmpl;

//	    if (clast<30) DATA[clast].stat=0;
//	    if (clast>30) multi_time++;

//	    if (clast>30) DATA[clast].stat=0;
//	    if (clast<30) multi_time++;

//   if ((fabs)(clast_mini-clast)!=30) multi_time++;
//	    if (((fabs)(clast_mini-clast)!=30) && (clast>30) ) multi_time++;
//	    if ( clast>30 ) 

//	}
//printf("clast_mini=%i   dtime(%i)=%Ld   stat=%i\n",clast_mini,clast,DATA[clast].dtime,DATA[clast].stat);
//printf("clast_mini=%i   dtime(%i)=%Ld   stat=%i\n",clast_mini,clast,DATA[clast].dtime,DATA[clast].stat);
    }

//printf("MAX Ampl=%f   Num=%ld\n",(float)maxAmpl,Num);

//qq(200);

//    if (multi_time>10) {
//printf("multi=%i   maxAmpl=%.0f\n",multi_time,maxAmpl);

//	maxAmpl/=15.;

//	if ( maxAmpl > MAX_AMPL) {
//	if (( maxAmpl > MAX_AMPL) && ( maxAmpl < 40)) {

//	    multi_time+=100;

//	    lmaxAmpl = log10((float)maxAmpl)*100.;
//	    if (lmaxAmpl<10000) Nsize[(int)lmaxAmpl]++;
//	    else Nsize[10000]++;

//	}



if (DATA[25].run_dir==1) {
    if (DATA[25].stat==1) multi_time+=100;

//if (multi_time>101) press_any_key();

}
else {
    if (maxAmpl > MAX_AMPL) multi_time+=100;
}
//multi_time+=100;
//press_any_key();
//}
return multi_time;
}
*/
//====================================================================
/*
int SavePaw(int clast)
{
//	ff111 = fopen(coiname,"at");
    if (clast!=25) {
	fprintf(ff111,"%2d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d\n",
	    DATA[clast].Number,DATA[clast].NumEvent,
	    DATA[clast].h,DATA[clast].m,DATA[clast].s,
	    DATA[clast].mls,DATA[clast].mks,DATA[clast].dns);
//	    DATA[clast].maxAmpl);

	for(int ii=0;ii<64;ii++) {
//	    fprintf(ff111,"%9.2f%3i",DATA[clast].Ampl[ii]+DATA[clast].ped[ii],DATA[clast].Stat[ii]);
//	    fprintf(ff111,"%9.2f%3i",DATA[clast].Ampl[ii],DATA[clast].Stat[ii]);
	    fprintf(ff111,"%6.0f%3i",DATA[clast].Ampl[ii],DATA[clast].Stat[ii]);
	    if ((ii+1)%8 == 0) fprintf(ff111,"\n");
	}
//	for(int ii=0;ii<64;ii++) {
//	    fprintf(ff111,"%9.2f",DATA[clast].Ampl[ii]);
//	    if ((ii+1)%8 == 0) fprintf(ff111,"\n");
//	}
    }
//	fclose(ff111);
    if (clast==25) {
//	fprintf(ff111,"%8i  %02d:%02d:%02d,%03d.%03d.%03d%7.2f%7.2f%5.0f.%5.0f.%7.3f%3i%7.2f%7.2f%7.2f\n",
//	    DATA[clast].NumEvent,
	fprintf(ff111,"%2d%11Ld  %02d:%02d:%02d,%03d.%03d.%03d%7.2f%7.2f%6.0f.%6.0f.%7.3f%3i%7.2f%7.2f%7.2f\n",
	    DATA[clast].Number,DATA[clast].NumEvent,
	    DATA[clast].h,DATA[clast].m,DATA[clast].s,DATA[clast].mls,DATA[clast].mks,DATA[clast].dns,
	    DATA[clast].Tet,DATA[clast].Fi,DATA[clast].XX,DATA[clast].YY,DATA[clast].lgE,
	    DATA[clast].NumSt,DATA[clast].Alfa,DATA[clast].Delta,DATA[clast].Angle);   //  tim4
    }
return 1;
}
*/
//====================================================================
/*
int SaveAmpl_IACT(int clast, FILE *fff)
{
//	ffout = fopen(outname,"at");
    if (clast!=25) {
	fprintf(fff,"%2d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d\n",
		DATA[clast].Number,DATA[clast].NumEvent,
		DATA[clast].h,DATA[clast].m,DATA[clast].s,
		DATA[clast].mls,DATA[clast].mks,DATA[clast].dns);
//		DATA[clast].maxAmpl);

//	for(int ii=0;ii<64;ii++) {
//		fprintf(ffout,"%9.2f",DATA[clast].Ampl[ii]);
//		if ((ii+1)%8 == 0) fprintf(ffout,"\n");
//	}

	for(int ii=0;ii<64;ii++) {
//	    fprintf(ffout,"%9.2f%3i",DATA[clast].Ampl[ii],DATA[clast].Stat[ii]);
	    fprintf(fff,"%6.0f%3i",DATA[clast].Ampl[ii],DATA[clast].Stat[ii]);
	    if ((ii+1)%8 == 0) fprintf(fff,"\n");
	}

    }
//	fclose(ffout);

    if (clast==25) {
//	fprintf(ffout,"%8i  %02d:%02d:%02d,%03d.%03d.%03d%7.2f%7.2f%5.0f.%5.0f.%7.3f%3i%7.2f%7.2f%7.2f\n",
//	    DATA[clast].NumEvent,
	fprintf(fff,"%2d%11Ld  %02d:%02d:%02d,%03d.%03d.%03d%7.2f%7.2f%5.0f.%5.0f.%7.3f%3i%7.2f%7.2f%7.2f\n",
	    DATA[clast].Number,DATA[clast].NumEvent,
	    DATA[clast].h,DATA[clast].m,DATA[clast].s,DATA[clast].mls,DATA[clast].mks,DATA[clast].dns,
	    DATA[clast].Tet,DATA[clast].Fi,DATA[clast].XX,DATA[clast].YY,DATA[clast].lgE,
	    DATA[clast].NumSt,DATA[clast].Alfa,DATA[clast].Delta,DATA[clast].Angle);   //  tim4
    }

return 1;
}
*/

//====================================================================
//====================================================================
/// ???????????????? ??????????????
int SaveAmpl_0(int clast, FILE *fff)
{
	fprintf(fff,"%2d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d\n",
		DATA[clast].Number,DATA[clast].NumEvent,
		DATA[clast].h,DATA[clast].m,DATA[clast].s,
		DATA[clast].mls,DATA[clast].mks,DATA[clast].dns);
    for(int ib=0;ib<1024;ib++) {
	fprintf(fff,"%4i  ",ib);
	for(int ii=0;ii<32;ii++) {
//	    fprintf(ffout,"%9.2f%3i",DATA[clast].Ampl[ii],DATA[clast].Stat[ii]);
	    fprintf(fff,"%6.0f",DATA[clast].Ampl[ii][ib]);
	}
	fprintf(fff,"\n");
    }
return 1;
}
//====================================================================
//====================================================================
/// ???????????? ?????? ???????????????????? ???? ????????????
int SaveAmpl(int clast, FILE *fff)
{
	for(int ii = 0; ii < 8; ii++) 
    {
        fprintf(fff,"%Ld  %02d:%02d:%02d,%03d.%03d.%03d  %d  ",
            DATA[clast].NumEvent,
            DATA[clast].h,DATA[clast].m,DATA[clast].s,
            DATA[clast].mls,DATA[clast].mks,DATA[clast].dns,
            ii);
        //for(int ib=0; ib<1024; ib++) {
        for(int ib=300; ib<500; ib++) {
   	        fprintf(fff,"%6.0f",DATA[clast].Ampl[ii][ib]);
	    }
	    fprintf(fff,"\n");
    }
    return 1;
}
//====================================================================
int SaveTimArray(int clast,FILE *fff)
{
	fprintf(fff,"%3d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d%7i   %s\n",
//	    DATA[clast].Number,DATA[clast].NumEvent,
	    (IACT_NN+60),DATA[clast].NumEvent,
	    DATA[clast].h,DATA[clast].m,DATA[clast].s,
	    DATA[clast].mls,DATA[clast].mks,DATA[clast].dns,
	    DATA[clast].Delay,DATA[clast].dirname);
return 1;
}
//====================================================================
//====================================================================
int SaveTime(int clast, FILE *fff)
{
//	fftim = fopen(timname,"at");
	if (fff!=NULL) {
//	    fprintf(fftim,"%2d%11ld   %02d:%02d:%02d,%03d.%03d.%03d\n",
//		DATA[clast].Number,DATA[clast].NumEvent,
//		DATA[clast].h,DATA[clast].m,DATA[clast].s,
//		DATA[clast].mls,DATA[clast].mks,DATA[clast].dns);

	    fprintf(fff,"%2d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d   %02X,%02X,%02X,%02X\n",
		DATA[clast].Number,DATA[clast].NumEvent,
		DATA[clast].h,DATA[clast].m,DATA[clast].s,
		DATA[clast].mls,DATA[clast].mks,DATA[clast].dns,
		DATA[clast].add_byte[0],DATA[clast].add_byte[1],DATA[clast].add_byte[2],DATA[clast].add_byte[3]);
//	    	DATA[clast].Delay);
	}
//	fclose(fftim);
return 1;
}
//====================================================================
//====================================================================
/*
int SaveTim(int clast)
{
	fftim = fopen(timname,"at");

	fprintf(fftim,"%02d%11ld   %02d:%02d:%02d,%03d.%03d.%03d\n",
	    DATA[clast].Number,DATA[clast].NumEvent,
	    DATA[clast].h,DATA[clast].m,DATA[clast].s,
	    DATA[clast].mls,DATA[clast].mks,DATA[clast].dns);
//	    DATA[clast].Delay);

	fclose(fftim);
return 1;
}
*/
//====================================================================
int Read_Target_List (FILE *fff, int moda)
{
int add_day;
int kkk=0;
int res=0;
char sst[1];
char stt[200];
char st[200];
//char fname[200];
//FILE *fsub;

	mmm_add = mmm;

	fscanf(fff,"%1s",&sst[0]);
	if ( feof(fff) ) return -10;

	if ( (sst[0]=='/') || (sst[0]=='.') || (sst[0]=='~') )  {
	    strcpy(pathfile,sst);
	    fscanf(fff,"%s",pathfile_tmp);
	    strcat(pathfile,pathfile_tmp);
	    strcpy(pathfile_tmp,pathfile);
	}
	else {
	    strcpy(pathfile,pathfile_tmp);
	}
	printf("\n\npathdata={%s}   pathout={%s}\n",pathfile,pathout_tmp);

	fscanf(fff,"%d%4d%4d%4d",&day,&mon,&year,&md);

	if ( (sst[0]!='/') && (sst[0]!='.') && (sst[0]!='~') ) add_day = (int)sst[0]-48;
	else add_day = 0;
	day += add_day*10;

	year_min = (int) fmod(year,10);

	lll = ((long)year*10000L + (long)mon*100L + (long)day) + 20000000L;
	mmm = (long)day*10000L + (long)mon*100L + (long)year;
	nnn = (long)day*1000L + (long)mon*10L + (long)(year_min);
	ndays++;

	printf("	day=%02d  mon=%02d  year=%02d   md=%02d\n",day,mon,year,md);
	printf("	lll=%ld    mmm=%06ld   nnn=%05ld\n\n",lll,mmm,nnn);

	fprintf(ffstat,"\n%2d)   %02d/%02d/%02d.%02d\n",ndays,day,mon,year,md);


//press_any_key();

	sprintf(stt,"%06ld",mmm);
	strcat(pathfile,stt);
	strcpy(dirname,stt);

	    sprintf(stt,".%02d",md);

	if (md>0) {
	    strcat(pathfile,stt);
//	    strcat(dirname,stt);
	}
	    strcat(dirname,stt);


	for (int clast=1;clast<NCLAST;clast++) {
		strcpy(DATA[clast].dirname,dirname);
	}


	strcat(pathfile,"/");
//	strcat(dirname,"/");

	strcpy(pathped,pathfile);
	strcat(pathped,"PED/");
 
	strcpy(pathout,pathout_tmp);
	res = mkdir(pathout,0x41FF);
	if (res==0) {
	    printf("NOT THIS OUTDIR  {%s}   res=%i\n",pathout,res);
//	    press_any_key();
	}

//	    press_any_key();

	strcat(pathout,dirname);
	strcat(pathout,"/");
	res = mkdir(pathout,0x41FF);
	if (res==0) {
	    printf("NOT THIS OUTDIR  {%s}   res=%i\n",pathout,res);
//	    press_any_key();
	}

printf("MODA=%i   res=%i    pathout={%s}\n",MODA_TREAT,res,pathout);
//	    press_any_key();




	strcpy(errname,pathout);
	sprintf(st,"%06ld.err",mmm);
	strcat(errname,st);
	fferr = fopen(errname,"wt");
//	fclose(fferr);

	printf("   pathfile={%s}\n    pathped={%s}\n    pathout={%s}\n    dirname={%s}\n    errname={%s}\n",
	    pathfile,pathped,pathout,dirname,errname);


	data_accept=0;
	for (int clast=1;clast<NCLAST;clast++) {
	    strcpy(DATA[clast].pathfile,pathfile);
//	    strcat(DATA[clast].pathfile,"BSM");
	    strcat(DATA[clast].pathfile,"SIPM/");
	    DATA[clast].Number=clast;
	    DATA[clast].por=1;
	    DATA[clast].fdat = DATA[clast].OpenFile(DATA[clast].pathfile,&DATA[clast].por,0,&res,0);
	    if (res<=0) {
		DATA[clast].run=0;
		DATA[clast].run_dir=0;
//		DATA[clast].Number=0;
	    }
	    if (res>0) {
		DATA[clast].run=1;
		DATA[clast].run_dir=1;
//		DATA[clast].Number=clast;
		data_accept++;
		fclose (DATA[clast].fdat);
	    }
	    printf("   filedata[%02d]={%s}   res=%i   stop=%i\n",
		clast,DATA[clast].filedata,res,DATA[clast].stop);
	}

	if (data_accept==0) {
	    fprintf(fferr,"Not data in {%s}\n",pathfile);
	    fprintf(ffstat,"Not data in {%s}\n",pathfile);
	    printf("Not data in {%s}\n",pathfile);
	}
	else {
	    kkk+=1;
	}
	fclose(fferr);

printf("kkk=%i\n",kkk);
	if (data_accept==0) return kkk;

	strcpy(timname,pathout);
	sprintf(st,"%06ld.tim-coin",mmm);
	strcat(timname,st);
	sprintf(st,".%02d",md);
	strcat(timname,st);
	printf("timname={%s}\n",timname);
//	fftim = fopen(timname,"wt");
//	fclose(fftim);

//	strcpy(pathtimarray,"./tim-array/");
	res=mkdir(pathtimarray,0x41FF);
	if (res<=0) {
	    printf("Not dir {%s}\n",pathtimarray);
//	    press_any_key();
	}

	strcpy(timarrayname,pathtimarray);
	sprintf(st,"%06ld_%03d.tim-array",mmm,IACT_NN+60);
	strcat(timarrayname,st);
	sprintf(st,".%02d",md);
	strcat(timarrayname,st);
	printf("timarrayname={%s}\n",timarrayname);
//	if (mmm!=mmm_add) {
//	    fftimarray = fopen(timarrayname,"wt");  //  ???????????? ?????????? ?????? ???????????? ??????????
//	    fclose(fftimarray);
//	}

	strcpy(ratename,pathout);
	sprintf(st,"%06ld.rate",mmm);
	strcat(ratename,st);
	printf("ratename={%s}\n",ratename);
//	ffrate = fopen(ratename,"wt");
//	fclose(ffrate);

	for (int clast=1;clast<NCLAST;clast++) {
	    if (DATA[clast].run_dir==0) continue;

	    strcpy(DATA[clast].filehdr,pathout);
	    strcat(DATA[clast].filehdr,"headers/");
	    res = mkdir(DATA[clast].filehdr,0x41FF);
	    sprintf(st,"%05ld",nnn);
	    strcat(DATA[clast].filehdr,st);
	    sprintf(st,"%03d.hdr",clast);
	    strcat(DATA[clast].filehdr,st);
	    printf("bsm%02d   filetim={%s}\n",clast,DATA[clast].filehdr);
	}

printf("kkk=%i\n",kkk);
//press_any_key();
return kkk;
}
//====================================================================
//====================================================================
int OnlyHEADER (void) 
{
int stop=0;
//int por=0;

	for (int clast=1;clast<NCLAST;clast++) {
	    if ( DATA[clast].run_dir==0 ) continue;
	    DATA[clast].fhdr = fopen(DATA[clast].filehdr,"wt");
	    DATA[clast].NumEvent=0L;
	    DATA[clast].NumEvent_prim=0L;
	    DATA[clast].TimeEvent=0L;
	    DATA[clast].TimeEvent_prim=0L;
	    DATA[clast].por=1;
	    DATA[clast].fdat = DATA[clast].OpenFile(DATA[clast].pathfile, &DATA[clast].por, 0, &stop,0 );
	    printf("clast=%i   por=%i   stop=%i\n",clast,DATA[clast].por,stop);
	    if (stop<=0) continue;
	    printf("clast=%i   por=%i   stop=%i\n",clast,DATA[clast].por,stop);
	    do {
		    DATA[clast].dtime = ReadData(clast);  // read_data.c
	    } while (DATA[clast].stop!=1);
//		fclose(DATA[clast].fdat);  //  ?????? ?????????????? ?? ???????????? ????????????????
//press_any_key();
	    fclose(DATA[clast].fhdr);
qq(1100);
	} // clast

return 1;
}
//====================================================================
int GetFullData(int Dpor) 
{
FILE *fff;
int fullpor[NCLAST];
int por=0,stop=0,max=0;

	for (int clast=1;clast<NCLAST;clast++) {
	    fullpor[clast]=0;
	    if ( DATA[clast].run_dir==0 ) continue;
	    por=1;
	    stop=0;
	    do {
		fff = DATA[clast].OpenFile(DATA[clast].pathfile,&por,0,&stop,0);
//	printf("clast=%i   {%s}   por=%i   stop=%i\n",clast,DATA[clast].pathfile,por,stop);
		por++;
		if (stop<=0) continue;
		fullpor[clast]=por;
		fclose(fff);
	    } while (stop>=0);
//press_any_key();
	}

	for (int clast=1;clast<NCLAST;clast++) {
	    if(max<fullpor[clast]) max=fullpor[clast];
	}
	max-=1;

	if (max!=Dpor) {
	    fff = fopen("iact_full.por","at");
	    fprintf(fff,"\n!!!   all_portions=%i  !=  treat_portions=%i   !!!\n",max,Dpor);
	    fclose(fff);
	    printf("\n!!!   all_portions=%i  !=  treat_portions=%i   !!!\n",max,Dpor);
	    press_any_key();
	}
return max;
}
//====================================================================
int Read_XY(char *fname)
{
int kk=0;
FILE *fff;
int cl,ch,nn;
float xx,yy;
int n_cur,n_an,n_din;

	fff = fopen(fname,"rt");
	if (fff==NULL) {
	    printf("Not file {%s}\n",fname);
	    abort();
	}

	for (int icl=0;icl<24;icl++) {
	    for(int ich=0;ich<64;ich++) {
		DATA[icl].XXpmt[ich]=-1000.;
		DATA[icl].YYpmt[ich]=-1000.;
	    }
	}

	do {
		kk = fscanf(fff,"%i%i%i%f%f%i%i%i",&cl,&ch,&nn,&xx,&yy,&n_an,&n_din,&n_cur);
		if (kk<0) continue;
		DATA[cl].XXpmt[n_an]=xx;
		DATA[cl].YYpmt[n_an]=yy;
		DATA[cl].XXpmt[n_din]=xx;
		DATA[cl].YYpmt[n_din]=yy;
		printf("cl=%i  an=%i  din=%i  xx=%f  yy=%f\n",cl,n_an,n_din,DATA[cl].XXpmt[n_an],DATA[cl].YYpmt[n_an]);
	} while (kk>0);
    fclose(fff);

//press_any_key();
return 1;
}
//====================================================================
int Read_PE(char *fname)
{
int kk=0;
FILE *fff;
int cl,ch;
float pe,sens;
char st[20];

	fff = fopen(fname,"rt");
	if (fff==NULL) {
	    printf("Not file {%s}\n",fname);
	    abort();
	}

	for (int icl=0;icl<24;icl++) {
	    for(int ich=0;ich<64;ich++) {
		DATA[icl].PE_CODE[ich]=-1000.;
		DATA[icl].SENS[ich]=-1000.;
	    }
	}

	kk = fscanf(fff,"%s%s%s%s",st,st,st,st);
	do {
		kk = fscanf(fff,"%i%i%f%f",&cl,&ch,&pe,&sens);
		if (kk<0) continue;
		DATA[cl].PE_CODE[ch]=pe;
		DATA[cl].SENS[ch]=sens;
		printf("cl=%i  ch=%i  pe=%f  sens=%f\n",cl,ch,DATA[cl].PE_CODE[ch],DATA[cl].SENS[ch]);
	} while (kk>0);

    fclose(fff);
//press_any_key();
return 1;
}
//====================================================================
int Read_GEOMETRY(char *fname,int iact,int topology)
{
int kk=0;
FILE *fff;
//char st[20];
int n_para=0,n_trio=0;
int num1,nn1,ncl1,nch1,n_sort;
int num2,nn2,ncl2,nch2;
int num3,nn3,ncl3,nch3;


	fff = fopen(fname,"rt");
	if (fff==NULL) {
	    printf("Not file {%s}\n",fname);
	    abort();
	}

	if (iact==1) {
	    if (topology==2)  { n_para=798; n_trio=0;    }
	    if (topology==3)  { n_para=0;   n_trio=2045; }
	    if (topology==23) { n_para=619; n_trio=317;  }
	}
//	if (iact==1) {
////	    if (topology==2)  { n_para=795; n_trio=0;    }
//	    if (topology==3)  { n_para=0;   n_trio=2026; }
//	    if (topology==23) { n_para=610; n_trio=320;  }
//	}
	if (iact==2) {
	    if (topology==2)  { n_para=795; n_trio=0;    }
	    if (topology==3)  { n_para=0;   n_trio=2026; }
	    if (topology==23) { n_para=610; n_trio=320;  }
	}


	for(int icl=1;icl<25;icl++) {
	    for (int n_sort=0;n_sort<3000;n_sort++) {
		DATA[icl].SORT[n_sort].num1=-1;
		DATA[icl].SORT[n_sort].nn1=-1;
		DATA[icl].SORT[n_sort].ncl1=-1;
		DATA[icl].SORT[n_sort].nch1=-1;

		DATA[icl].SORT[n_sort].num2=-1;
		DATA[icl].SORT[n_sort].nn2=-1;
		DATA[icl].SORT[n_sort].ncl2=-1;
		DATA[icl].SORT[n_sort].nch2=-1;

		DATA[icl].SORT[n_sort].num3=-1;
		DATA[icl].SORT[n_sort].nn3=-1;
		DATA[icl].SORT[n_sort].ncl3=-1;
		DATA[icl].SORT[n_sort].nch3=-1;
	    }
	}


	for(int ii=0;ii<n_para;ii++) {

	    kk = fscanf(fff,"%i%i%i%i%i%i%i%i%i",&n_sort,
		&num1,&nn1,&ncl1,&nch1,
		&num2,&nn2,&ncl2,&nch2);

		DATA[ncl1].SORT[n_sort].num1=num1;
		DATA[ncl1].SORT[n_sort].nn1=nn1;
		DATA[ncl1].SORT[n_sort].ncl1=ncl1;
		DATA[ncl1].SORT[n_sort].nch1=nch1*2;

		DATA[ncl2].SORT[n_sort].num2=num2;
		DATA[ncl2].SORT[n_sort].nn2=nn2;
		DATA[ncl2].SORT[n_sort].ncl2=ncl2;
		DATA[ncl2].SORT[n_sort].nch2=nch2*2;
	}
	for(int ii=n_para;ii<n_para+n_trio;ii++) {

	    kk = fscanf(fff,"%i%i%i%i%i%i%i%i%i%i%i%i%i",&n_sort,
		&num1,&nn1,&ncl1,&nch1,
		&num2,&nn2,&ncl2,&nch2,
		&num3,&nn3,&ncl3,&nch3);

		DATA[ncl1].SORT[n_sort+ii].num1=num1;
		DATA[ncl1].SORT[n_sort+ii].nn1=nn1;
		DATA[ncl1].SORT[n_sort+ii].ncl1=ncl1;
		DATA[ncl1].SORT[n_sort+ii].nch1=nch1*2;

		DATA[ncl2].SORT[n_sort+ii].num2=num2;
		DATA[ncl2].SORT[n_sort+ii].nn2=nn2;
		DATA[ncl2].SORT[n_sort+ii].ncl2=ncl2;
		DATA[ncl2].SORT[n_sort+ii].nch2=nch2*2;

		DATA[ncl3].SORT[n_sort+ii].num3=num3;
		DATA[ncl3].SORT[n_sort+ii].nn3=nn3;
		DATA[ncl3].SORT[n_sort+ii].ncl3=ncl3;
		DATA[ncl3].SORT[n_sort+ii].nch3=nch3*2;
	}
    fclose(fff);

	for(int icl=1;icl<25;icl++) {
	    for(int n_sort=0;n_sort<3000;n_sort++) {

		if (DATA[icl].SORT[n_sort].num1==-1) continue;

		printf("%5i%5i%5i%4i%4i%5i%5i%4i%4i%5i%5i%4i%4i\n",
		    n_sort,
		DATA[icl].SORT[n_sort].num1,
		DATA[icl].SORT[n_sort].nn1,
		DATA[icl].SORT[n_sort].ncl1,
		DATA[icl].SORT[n_sort].nch1,

		DATA[icl].SORT[n_sort].num2,
		DATA[icl].SORT[n_sort].nn2,
		DATA[icl].SORT[n_sort].ncl2,
		DATA[icl].SORT[n_sort].nch2,

		DATA[icl].SORT[n_sort].num3,
		DATA[icl].SORT[n_sort].nn3,
		DATA[icl].SORT[n_sort].ncl3,
		DATA[icl].SORT[n_sort].nch3);
	    }
	}

press_any_key();
return kk;
}
//====================================================================
int ZeroData(void)
{
	for (int clast=0;clast<NCLAST;clast++) {
	    DATA[clast].IACT_NN=IACT_NN;
	    if (IACT_NN==1) DATA[clast].Delay=1411;
	    if (IACT_NN==2) DATA[clast].Delay=2036;
	    DATA[clast].ready=0;
	    DATA[clast].stop=1;
	    DATA[clast].stat=0;
	    DATA[clast].restart=0;
	    DATA[clast].dtime=0L;
	    DATA[clast].tim3=0L;
	    DATA[clast].tim_start=0L;
	    DATA[clast].tim_fin=0L;
	    DATA[clast].hour_plus=0L;
	    DATA[clast].key_plus=0L;
	    DATA[clast].min_plus=0L;
	    DATA[clast].NumEvent=0L;
	    DATA[clast].NumEvent_prim=0L;
	    DATA[clast].TimeEvent=0L;
	    DATA[clast].TimeEvent_prim=0L;
	    DATA[clast].Nrate=0L;
	    DATA[clast].h=0;
	    DATA[clast].m=0;
	    DATA[clast].s=0;
	    DATA[clast].mls=0;
	    DATA[clast].mks=0;
	    DATA[clast].dns=0;
	    multi[clast]=0;
	    multi_cut[clast]=0;
	    DATA[clast].RejectEvent=0;
		for(int ii=0;ii<10;ii++) {
		    DATA[clast].nerr[ii]=0;
		}
	    for(int ich=0;ich<64;ich+=2) {
		for(int jch=0;jch<64;jch++) {
		    DATA[clast].para[ich][jch]=0;
		}
	    }
	    for(int ich=0;ich<64;ich++) {
		DATA[clast].Ampl_pe[ich]=0;
		DATA[clast].Ampl_pe_clean[ich]=0;
		for(int ig=0;ig<5001;ig++) {
		    DATA[clast].spe_det[ich][ig]=0;
		}
	    }
	    for(int ich=0;ich<64;ich++) {
		for(int ig=0;ig<4101;ig++) {
		    DATA[clast].gall[ich][ig]=0;
		    DATA[clast].gampl[ich][ig]=0;
		    DATA[clast].gped[ich][ig]=0;
		}
		for(int ig=0;ig<2000;ig++) {
		    DATA[clast].A12[ich][0][ig]=0;
		    DATA[clast].A12[ich][1][ig]=0;
		}
		DATA[clast].nA12[ich]=0;
		DATA[clast].Trigg[ich]=0;
		DATA[clast].Stat[ich]=0;
	    }
	}  // clast
	NumRate=0;
	TimeRate=0;
	LocalTime=0L;
	NeventCut=0;
	AllEvents=0;
	multi4=0;
	time_start=0;
	time_start_Global=0;
	time_fin=0;
	time_full=0L;
	GlobalNum=0L;
	LocalNum=0L;
	RejectNum=0L;
	restart_count=0;
	test_duo=0L;
	test_trio=0L;
	test_duo_trio=0L;
	test_err=0L;



		for(int ii=0;ii<1001;ii++) {
		    NtimeMKS[ii]=0;
		    NtimeMLS[ii]=0;
		}




		    h_st=0;
		    m_st=0;
		    s_st=0;
		    mls_st=0;
		    mks_st=0;
		    dns_st=0;
		    h_fn=0;
		    m_fn=0;
		    s_fn=0;
		    mls_fn=0;
		    mks_fn=0;
		    dns_fn=0;
return 1;
}
//====================================================================
