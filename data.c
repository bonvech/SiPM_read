#include <sys/stat.h>
#include <unistd.h>


#include "data.h"
#include "data_add.c"
//====================================================================
//====================================================================
FILE *Data::OpenFile(char *path, int *por, int flag, int *res, int mode )
{
FILE *fff;
char st[100];
int kkk;
int portion=*por;
char fname[200];

if (flag>10) {
	strcpy(fname,path);
	fff = EmptyFile(fname,(char*)"rb",&kkk);
	*por=portion;
	*res=kkk;
return fff;
}


NEW:
if (flag<10) {
	strcpy(fname,path);
	sprintf(st,"%05ld",nnn);
	strcat(fname,st);
	sprintf(st,"%03d",Number);
	strcat(fname,st);
	sprintf(st,".%03d",portion);
	strcat(fname,st);
//	printf("<OpenFile>(Cl#%02d)::OPEN filename={%s}\n",Number,fname);
}
	fff = EmptyFile(fname,(char*)"rb",&kkk);
	*por=portion;
	*res=kkk;
	strcpy(filedata,fname);
printf("kkk=%i   portion=%i\n",kkk,portion);


if (kkk==-1000) {
	    run=0;
	    stop=1;

	    if (mode==1) {
		stop=-1000;
		run=-1000;
		return NULL;
	    }
	    return NULL;



}

if (kkk==0) {
	    run=0;
	    stop=0;

	    if (mode==1) {
		stop=1;
		run=1;
		return NULL;
	    }

	    portion++;
	    if (portion<1000) goto NEW;
	    else {
		run=0;
		stop=1;
		return NULL;
	    }
}

if (kkk==1) {
	    run=1;
	    stop=0;
	    return fff;
	}


return fff;
}
//====================================================================
FILE *Data::EmptyFile ( char fname[], char mod[], int *res )
{
FILE *fsf;
int fsize=0;
int kkk=0;

	fsf = fopen(fname,mod);
	if ( fsf == NULL ) {
//		printf("EmptyFile::   !!!     NO file %s     !!!\n",fname);
	    kkk=-1000;
	    *res=kkk;
	    return NULL;
	}
	fseek(fsf,0,SEEK_END);
	fsize = ftell(fsf);
	fclose(fsf);
//	printf("EmptyFile::   datafilename=%s   fsize=%i\n",fname, fsize);

	if ( fsize==0 ) {
		kkk=0;
		*res=kkk;
		return fsf;
	}
	else {
		fsf = fopen(fname,mod);
		kkk=1;
		*res=kkk;
	}
//	printf("EmptyFile::   datafilename=%s   fsize=%i   kkk=%i\n",fname, fsize,kkk);
return fsf;
}
//====================================================================
//====================================================================
//====================================================================
/*
void Data:: AddTime ( int clast, short unsigned int Delay )
{
	DATA[clast].dns += Delay;
	while (DATA[clast].dns>=1000) { DATA[clast].mks += 1; DATA[clast].dns -= 1000; }
	while (DATA[clast].mks>=1000) { DATA[clast].mls += 1; DATA[clast].mks -= 1000; }
	while (DATA[clast].mls>=1000) { DATA[clast].s += 1;   DATA[clast].mls -= 1000; }
	while (DATA[clast].s>=60)     { DATA[clast].m += 1;   DATA[clast].s -= 60;     }
	while (DATA[clast].m>=60)     { DATA[clast].h += 1;   DATA[clast].m -= 60;     }
}
*/
//====================================================================
long long Data::GetDtime (int type)
{
long long times=0;

    if (type==1) times = (long long)(Delay);
    if (type==2) times = (long long)(Delay*5);

	times += (long long)dns;
	times += (long long)mks*1000;
	times += (long long)mls*1000*1000;
	times += (long long)s*1000*1000*1000;
	times += (long long)m*1000*1000*1000*60;
	times += (long long)h*1000*1000*1000*60*60;

return times;
}
//====================================================================
int Data::GetClock (long long times, int *hhh, int *mmm, int *sss,  int *mlsss, int *mksss, int *dnsss)
{
long long dat;
int h,m,s,mls,mks,dns=0;


//printf(" times=%Ld\n",times);

	dat = times/1000;
	dns = (int)(times - dat*1000);
	times/=1000;
//printf(" times=%Ld  dat=%Ld  dns=%i\n",times,dat,dns);

	dat = times/1000;
	mks = (int)(times-dat*1000);
	times /= 1000;
//printf(" times=%Ld  dat=%Ld  mks=%i\n",times,dat,mks);

	dat = times/1000;
	mls = (int)(times-dat*1000);
	times /= 1000;
//printf(" times=%Ld  dat=%Ld  mls=%i\n",times,dat,mls);

	dat = times/60;
	s = (int)(times-dat*60);
	times /= 60;
//printf(" times=%Ld  dat=%Ld  s=%i\n",times,dat,s);

	dat = times/60;
	m = (int)(times-dat*60);
	times /= 60;
	h = (int) times;
//printf(" times=%Ld  dat=%Ld  m=%i  h=%i\n",times,dat,m,h);


	*hhh = h;
	*mmm = m;
	*sss = s;
	*mlsss = mls;
	*mksss = mks;
	*dnsss = dns;

//press_any_key();
return 1;
}
//====================================================================
void Data::GetTime (unsigned char buf[8],int *hh,int *mm,int *ss,int *mlss,int *mkss,int *dnss)
{
int hhhh=0,mmmm=0,ssss=0,mlssss=0,mkssss=0,dnssss=0;
int data_time[4]={0,0,0,0};

	for(int ii=0; ii<8; ii+=2) {
	    data_time[ii/2]=buf[ii+1]*256+buf[ii];
//	    printf("time:  buf[%d] = 0x%x  buf[%d] = 0x%x    data[%d] = 0x%x\n",
//		(ii+1) , buf[ii+1], ii, buf[ii], ii/2, data_time[ii/2] );
	}
	    dnssss = ( data_time[0] & 0x7f ) * 10;
	    mkssss = ( data_time[0] & 0xff80 ) >> 7;
	    mkssss |= (data_time[1] & 1) << 9;
	    mlssss = ( data_time[1] & 0x7fe ) >> 1;
	    ssss   = ( data_time[1] & 0xf800 ) >> 11;
	    ssss |= (data_time[2] & 1) << 5;
	    mmmm  = ( data_time[2] & 0x7e ) >> 1;
	    hhhh = ( data_time[2] & 0xf80 ) >> 7;
	    *hh=hhhh;
	    *mm=mmmm;
	    *ss=ssss;
	    *mlss=mlssss;
	    *mkss=mkssss;
	    *dnss=dnssss;
	if ( (hhhh>23) || (mmmm>59) || (ssss>59) || (mlssss>999) || (mkssss>999) || (dnssss>999) ) {
	    printf("GetTime::  Wrong Time:  {%06ld.%02d}  BSM#%02d  por=%i  %02d:%02d:%02d,%03d.%03d.%03d  NumEvent=%Ld\n",
		mmm,md,Number,por,hhhh,mmmm,ssss,mlssss,mkssss,dnssss,NumEvent);
	    if (fferr!=NULL) fprintf(fferr,"BSM#%02d  por=%i  Wrong Time:  %02d:%02d:%02d,%03d.%03d.%03d  NumEvent=%Ld\n",
		Number,por,hhhh,mmmm,ssss,mlssss,mkssss,dnssss,NumEvent);
//	    press_any_key();
	}
}

//====================================================================
//====================================================================
int Data::GetDelay (int NumHiSC)
{
int delay_hisc = 0;

    switch (NumHiSC)
    {
	case 1:   delay_hisc=    883; break;
	case 2:   delay_hisc=   1398; break;
	case 3:   delay_hisc=    801; break;
	case 4:   delay_hisc=    556; break;
	case 5:   delay_hisc=   1479; break;
	case 6:   delay_hisc=    575; break;
	case 7:   delay_hisc=   1432; break;
	case 8:   delay_hisc=   1361; break;
	case 9:   delay_hisc=   1868; break;
	case 10:   delay_hisc=    943; break;
	case 12:   delay_hisc=   1540; break;
	case 14:   delay_hisc=    906; break;
	case 16:   delay_hisc=    204; break;
	case 18:   delay_hisc=   1937; break;
	case 19:   delay_hisc=   1436; break;
	case 20:   delay_hisc=   1598; break;
	case 21:   delay_hisc=   1078; break;
	case 22:   delay_hisc=    706; break;
	case 23:   delay_hisc=   1198; break;
	case 24:   delay_hisc=    850; break;
	case 25:   delay_hisc=   1253; break;
	case 26:   delay_hisc=   2275; break;
	case 27:   delay_hisc=   1648; break;
	case 28:   delay_hisc=   1951; break;
	case 29:   delay_hisc=   1586; break;
	case 30:   delay_hisc=   1238; break;
	case 31:   delay_hisc=   1233; break;
	case 32:   delay_hisc=   1714; break;
	case 34:   delay_hisc=   2783; break;
	case 35:   delay_hisc=   2164; break;

	case 101:   delay_hisc=    722; break;
	case 102:   delay_hisc=   1473; break;
	case 103:   delay_hisc=   2904; break;
	case 104:   delay_hisc=      0; break;
	case 105:   delay_hisc=    221; break;
	case 106:   delay_hisc=    868; break;
	case 107:   delay_hisc=   2067; break;
	case 108:   delay_hisc=   2590; break;
	case 109:   delay_hisc=   3430; break;
	case 110:   delay_hisc=    572; break;
	case 111:   delay_hisc=   1327; break;
	case 112:   delay_hisc=   2187; break;
	case 113:   delay_hisc=   2779; break;
	case 114:   delay_hisc=      0; break;
	case 115:   delay_hisc=   1180; break;
	default :   delay_hisc=      0; break;
    }
return delay_hisc;
}
//====================================================================
//====================================================================
//int Data::ReRead (unsigned char ch1, unsigned char ch0, FILE *fdat)
int Data::ReRead (unsigned char ch0, unsigned char ch1)
{
int ii=0,kk=0;
//int size=0;
unsigned char ch2,ch3;
unsigned long Fin=0;

//printf("111:  %02X %02X %02x %02x\n",ch0,ch1,ch2,ch3);
//	printf("%i   0x%X  0x%X  0x%X  0x%X\n",ii,ch0,ch1,ch2,ch3);
//	kk = fread(&ch2,sizeof(ch2),1,fdat );
	kk = fread(&ch2,1,1,fdat );
	if (!kk) {
//	    printf("ReadBIN:: end of file\n");
	    return -1;
	}
CYC:
//	kk = fread(&ch3,sizeof(ch3),1,fdat );
	kk = fread(&ch3,1,1,fdat );

	if (!kk) {
//	    printf("ReadBIN:: end of file\n");
	    return -1;
	}

//printf("222:  %02X %02X %02X %02X\n",ch0,ch1,ch2,ch3);

	Fin = (unsigned long)ch0*256L*256L*256L
	    + (unsigned long)ch1*256L*256L
	    + (unsigned long)ch2*256L
	    + (unsigned long)ch3;
//	printf("%i   0x%X  0x%X  0x%X  0x%X\n",ii,ch0,ch1,ch2,ch3);
//	printf("fin=0x%X\n",DATA.fin);

	if ( Fin != 0xFFFFFFFF ) {
//	    printf("ii=%i   Fin=0x%lX\n",ii,Fin);
	    ch0 = ch1;
	    ch1 = ch2;
	    ch2 = ch3;
	    ii++;
//	if (!(ii%10)) press_any_key();
	    goto CYC;
	}
//	printf("ERROR::  uncorrect finich of package  ii=%i bytes\n",ii);
//	press_any_key();
return 1;
}
//====================================================================
//====================================================================
//====================================================================
//====================================================================
long long Data::Read_tim2 (void)
{
char ch[10];
int res=0;

	res=fscanf(fdat,"%02d%11Ld%d%1s%d%1s%d%1s%d%1s%d%1s%d",
	    &NumHiSC,&NumEvent,
	    &h,&ch[0],&m,&ch[0],&s,&ch[0],
	    &mls,&ch[0],&mks,&ch[0],&dns);   //  tim2

	    Delay = GetDelay(NumHiSC);
//	    EVENT_I.tim = GetDtime(0);
	    TimeEvent = GetDtime(0);

//	    Delay=1453;

	if (res<0) return -1000;
//	printf("%02d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d   %Ld\n",
//	    NumClast,NumEvent,
//	    h,m,s,mls,mks,dns,
//	    TimeEvent);
//	    EVENT_I.tim);

//press_any_key();
//return EVENT_I.tim;
return TimeEvent;
}
//====================================================================
long long Data::Read_tim4 (void)
{
char ch[10];
int res=0;

	res=fscanf(fdat,"%d%11Ld%d%1s%d%1s%d%1s%d%1s%d%1s%d%d",
	    &NumHiSC,&NumEvent,
	    &h,&ch[0],&m,&ch[0],&s,&ch[0],
	    &mls,&ch[0],&mks,&ch[0],&dns,&Delay);   //  tim4

	    Delay = GetDelay(NumHiSC);
//	    EVENT_I.tim = GetDtime(0);
	    TimeEvent = GetDtime(0);
//	    Delay = 1453;

	if (res<0) return -1000;
//	printf("%02d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d   %Ld\n",
//	    NumClast,NumEvent,
//	    h,m,s,mls,mks,dns,
//	    TimeEvent);
//	    EVENT_I.tim);

//press_any_key();
//return EVENT_I.tim;
return TimeEvent;
}
//====================================================================
long long Data::Read_tim_c4 (void)
{
char ch[10];
int res=0;
long long Nsh=0;
int icl=0, ncl=0;
//int clast[35];
int Nnn=0,Nst;
float dtim,lgE,Zzz;

	res=fscanf(fdat,"%11Ld",&Nsh);
	if (res<0) return -1000;

	for(int ii=0;ii<35;ii++) {
	    res=fscanf(fdat,"%d",&icl);
//	    clast[ii]=icl;
	    if (icl>0) ncl++;
	    if (res<0) return -1000;
	}

	for(int ii=0;ii<ncl;ii++) {
	    res=fscanf(fdat,"%d%Ld%d%d%1s%d%1s%d%1s%d%1s%d%1s%d%f%f%f%d",
	    &NumHiSC,&NumEvent,&Nnn,
	    &h,&ch[0],&m,&ch[0],&s,&ch[0],
	    &mls,&ch[0],&mks,&ch[0],&dns,
	    &dtim,&lgE,&Zzz,&Nst);

//	    Delay = 0;
//	    EVENT_I.tim = GetDtime(0);

	    Delay = GetDelay(NumHiSC);
//	    EVENT_I.tim = GetDtime(0);
	    TimeEvent = GetDtime(0);
//	    Delay = 1453;

	    if (res<0) return -1000;
//	printf("%02d%11Ld   %02d:%02d:%02d,%03d.%03d.%03d   %Ld\n",
//	    NumClast,NumEvent,
//	    h,m,s,mls,mks,dns,
//	    TimeEvent);
//	    EVENT_I.tim);
	}
//press_any_key();
//return EVENT_I.tim;
return TimeEvent;
}
//====================================================================
long long Data::Read_HiSC_out (void)
{
char ch[10];
int res=0;

	res=fscanf(fdat,"%7Ld%3i%4i%1s%2i%1s%2i%1s%03d%1s%03d%1s%03d%f%f%f%f%f%i%f%f%f",
	    &NumEvent,&NumHiSC,
	    &h,&ch[0],&m,&ch[0],&s,&ch[0],
	    &mls,&ch[0],&mks,&ch[0],&dns,
	    &Tet,&Fi,&XX,&YY,&lgE,
	    &NumSt,&Alfa,&Delta,&Angle);

//	    Delay = 0;
//	    EVENT_I.tim = GetDtime(0);

	    Delay = GetDelay(NumHiSC);
//	    EVENT_I.tim = GetDtime(0);
	    TimeEvent = GetDtime(0);
//	    Delay = 1453;

	if (res<0) return -1000;

//	printf("%7Ld   %02d:%02d:%02d,%03d.%03d.%03d%7.2f%7.2f%7.2f%7.2f%7.3f%4i%7.2f%7.2f%7.2f\n",
//	    NumEvent,
//	    h,m,s,mls,mks,dns,
//	    Tet,Fi,XX,YY,lgE,
//	    NumSt,Alfa,Delta,Angle);

//press_any_key();
//return EVENT_I.tim;
return TimeEvent;
}
//====================================================================
