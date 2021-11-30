//====================================================================
//====================================================================
int Data:: Errors_IACT(int *err,int *maska)
{
int err_data=0;
int maska_key=0;

	if (sidi!=3032) {
		printf("Wrong SIDI:  {%06ld.%02d}  BSM#%02d  por=%i  sidi=%i(%02X %02X)  NumBytes=%i  NumEvent_pre=%Ld\n",
		mmm,md,Number,por,sidi,buf[0],buf[1],NumBytes,NumEvent_prim);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Wrong SIDI:  sidi=%i(%02X %02X)  NumBytes=%i  NumEvent_pre=%Ld\n",
		Number,por,sidi,buf[0],buf[1],NumBytes,NumEvent_prim);
	    }
	    err_data=2;
	    nerr[2]++;
//press_any_key();
	}
	if (NumBytes!=132) {
		printf("Wrong Bytes:  {%06ld.%02d}  BSM#%02d  por=%i  sidi=%i  NumBytes=%i(%02X %02X)  NumEvent_pre=%Ld\n",
		mmm,md,Number,por,sidi,NumBytes,buf[2],buf[3],NumEvent_prim);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Wrong Bytes:  sidi=%i  NumBytes=%i(%02X %02X)  NumEvent_pre=%Ld\n",
		Number,por,sidi,NumBytes,buf[2],buf[3],NumEvent_prim);
	    }
		NumBytes=132;
	    err_data=3;
	    nerr[3]++;
//press_any_key();
	}

	if ( (Nrate>0) && (NumEvent==NumEvent_prim) ) {
		printf("Double Number:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Double Number:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    err_data=4;
	    nerr[4]++;
//	    press_any_key();
	}
	if ( (Nrate>0) && (NumEvent<NumEvent_prim) ) {
		printf("Less Number:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Less Number:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    err_data=5;
	    nerr[5]++;
//	    press_any_key();
	}

	if ( (TimeEvent>0) && (TimeEvent==TimeEvent_prim) ) {
		printf("Double Time:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
if ( (lll>20171010) && (lll<20180530) ) {
	    if (maska_key==1) {
		fprintf(fferr,"BSM#%02d  por=%i  Double Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    if (maska_key==0) {
		fprintf(fferr,"BSM#%02d  por=%i  Double Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d  <-  Reject Event\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
}
else {  //!!!!!!!!!!
		fprintf(fferr,"BSM#%02d  por=%i  Double Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
}
	    }
	    err_data=6;
	    nerr[6]++;
//	    press_any_key();
	}

	if ( (TimeEvent>0) && (TimeEvent<TimeEvent_prim) ) {
		printf("Less Time:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
if ( (lll>20171010) && (lll<20180530) ) {
	    if (maska_key==1) {
		fprintf(fferr,"BSM#%02d  por=%i  Less Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    if (maska_key==0) {
		fprintf(fferr,"BSM#%02d  por=%i  Less Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d  <-  Reject Event\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
}
else {  //!!!!!!!!!!!!!!
		fprintf(fferr,"BSM#%02d  por=%i  Less Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		Number,por,NumEvent,h,m,s,mls,mks,dns);
}
	    }
	    err_data=7;
	    nerr[7]++;
//	    press_any_key();
	}

	if (TimeEvent>TimeEvent_prim) { nerr[6]=0; nerr[7]=0; }  //  ???

	*err= err_data;
	*maska = maska_key;

return 1;
}
//====================================================================
int Data::RejectIACT(void)
{
int key=0;

	if (TimeEvent==0) {
	    printf("Wrong Time:  {%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
	    if (fferr!=NULL) {
		fprintf(fferr,"BSM#%02d  por=%i  Wrong Time:  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		    Number,por,NumEvent,h,m,s,mls,mks,dns);
	    }
	    press_any_key();
	}
	if (TimeEvent==0) { RejectEvent++; key=1; }


//	if ( (lll>20200310) && ( (err_data==4) || (err_data==5) ) ) key=1;
//	if ( (lll>20200310) && ( (err_data==6) || (err_data==7) ) ) key=1;



if ( (mmm==31019)  && (md==2)  && (NumEvent==20270) && (s==35) )  { RejectEvent++; key=1; }
if ( (mmm==31019)  && (md==3)  && (NumEvent==19503) && (s==11) )  { RejectEvent++; key=1; }
if ( (mmm==31019)  && (md==8)  && (NumEvent==18918) && (s==28) )  { RejectEvent++; key=1; }
if ( (mmm==31019)  && (md==11) && (NumEvent==18471) && (s==13) )  { RejectEvent++; key=1;; }
if ( (mmm==31019)  && (md==16) && (NumEvent==8786)  && (s==37) )  { RejectEvent++; key=1;; }
if ( (mmm==31019)  && (md==22) && (NumEvent==17940) && (s==25) )  { RejectEvent++; key=1;; }
if ( (mmm==31019)  && (md==23) && (NumEvent==18160) && (s==6)  )  { RejectEvent++; key=1;; }
if ( (mmm==41019)  && (md==2)  && (NumEvent==20475) && (s==27) )  { RejectEvent++; key=1;; }
if ( (mmm==41019)  && (md==5)  && (NumEvent==13803) && (s==29) )  { RejectEvent++; key=1;; }
if ( (mmm==71019)  && (md==1)  && (NumEvent==410)   && (s==30) )  { RejectEvent++; key=1;; }
if ( (mmm==261019) && (md==2)  && (NumEvent==16066) && (s==6)  )  { RejectEvent++; key=1;; }

if ( (IACT_NN==2) && (mmm==121120) && (md==0) && (NumEvent==7346)  && (s==20) )  { RejectEvent++; key=1; }  //  iact02 ?
if ( (IACT_NN==2) && (mmm==231220) && (md==1) && (NumEvent==74337) && (s==1)  )  { RejectEvent++; key=1; }  //  iact02 ?
if ( (IACT_NN==2) && (mmm==151220) && (md==1) && (NumEvent==39429) && (s==6)  )  { RejectEvent++; key=1; }  //  iact02 ?
if ( (IACT_NN==1) && (mmm==150421) && (md==2) && (NumEvent==7000)  && (s==16) )  { RejectEvent++; key=1; }  //  iact01 ?

//  проверить номера телескопов !!!


if (RejectEvent>1) {
printf("{%06ld.%02d}  BSM#%02d  por=%i  NumEvent=%Ld  %02d:%02d:%02d,%03d.%03d.%03d\n",
		mmm,md,Number,por,NumEvent,h,m,s,mls,mks,dns);
printf("   RejectEvent=%ld\n",RejectEvent);
//press_any_key();
}




return key;
}
//====================================================================
//int Data::RestartIACT(int iact,long mmm,int md, int Number,int por, int *Restart, unsigned long *Reject)
int Data::RestartIACT(int maska_key)
{
//int restart = *Restart;
//unsigned long RejectEvent = *Reject;
int key=0;


if ( (lll>20171010) && (lll<20180915) ) {

	if (NumEvent<NumEvent_prim) {
	    restart++;
printf("clast=%i   por=%i   restart=%i\n",Number,por,restart);
//press_any_key();
//	    stop=1;
	}
	if ( (nerr[6]>0) && (maska_key==0) ) {
	    RejectEvent++;
	    key=1;
	}
	if ( (nerr[7]>0) && (maska_key==0) ) {
	    RejectEvent++;
	    key=1;
	}

if ( (mmm==120318) && (md==1) && (Number==18) && (restart==0) ) restart=1;

//if ( (mmm==140318) && (md==3) && (Number==17) && (por==3) && (restart==0) ) restart=2;
//if ( (mmm==140318) && (md==3) && (Number!=20) && (por==4) && (restart==0) ) restart=1;
//if ( (mmm==140318) && (md==3) && ( (Number!=17) || (Number!=20) ) && (por==4) && (restart==0) ) restart=1;
//if ( (mmm==140318) && (md==3) && (Number==17) && (por==3) && (restart==0) ) restart=1;

if ( (mmm==140318) && (md==4) && (Number==18) && (restart==0) ) restart=1;
if ( (mmm==200318) && (md==0) && (Number!=20) && (restart==0) ) restart=1;
if ( (mmm==200318) && (md==0) && (Number==20) && (restart==0) && (por==2) ) restart=1;

}
return key;
}
//====================================================================
//====================================================================
long long Data::AddTime_2019_20_iact01(long long tim) 
{
long long TimeEv=tim;


//-------------   sep19   ----------------------
    if ( (mmm==200919) && (md==1) ) {
	{ h+=14;  m+=29;  s+=31;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==250919) && (md==2) ) {
	{ h+=14;  m+=33;  s+=33;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   sep19   ----------------------
//-------------   oct19   ----------------------
    if ( (mmm==81019) && (md==0) ) {
	if (m==7) { h+=18;  m+=15;  s+=20;  mls-=0; }
	else { h+=18;  m+=22;  s+=22;  mls+=200; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==81019) && (md==1) ) {
	if (h==0) { h+=18;  m+=22;  s+=22;  mls-=389; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==241019) && (md==0) ) {
	{ h+=12;  m+=15;  s+=41;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==271019) && (md==0) ) {
	{ h+=11;  m+=50;  s+=36;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   oct19   ----------------------
//-------------   nov19   ----------------------
    if ( (mmm==261119) && (md==1) ) {
	{ h+=11;  m+=53;  s+=30;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   nov19   ----------------------
//-------------   dec19   ----------------------
    if ( (mmm==211219) && (md==0) ) {
	{ h+=11;  m+=5;  s+=28;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==301219) && (md==0) ) {
	{ h+=14;  m+=4;  s+=43;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   dec19   ----------------------
//-------------   jan20   ----------------------
    if ( (mmm==240120) && (md==1) ) {
	{ h+=3;  m-=13;  s-=15;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==260120) && (md==1) ) {
	{ h+=6;  m-=32;  s+=12;  mls-=0; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   jan20   ----------------------
//-------------   feb20   ----------------------
    if ( (mmm==20220) && (md==0) ) {
	if (h>8) s+=2;
	if (h==8) { h+=10;  m+=17;  s-=9;  mls-=334; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==30220) && (md==0) ) {
	if (h==8) { h+=12;  m-=54;  s-=8;  mls-=690; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==130220) && (md==0) ) {
	if (h>0) s+=4;
	if (h==0) { h+=12;  m+=5;  s-=38;  mls-=655; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   feb20   ----------------------
//-------------   mar20   ----------------------
    if ( (mmm==130320) && (md==0) ) {
	if (h>0) s+=3;
	if (h==0) { h+=13;  m+=33;  s-=26;  mls-=71; }
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==130320) && (md==1) ) {
	if (h>0) s+=3;
	if (h==0) { h+=14;  m+=6;  s-=25;  mls-=545; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==130320) && (md==2) ) {
	if (h>0) s+=4;
	if (h==0) { h+=14;  m+=41;  s+=61;  mls-=792; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==130320) && (md==3) ) {
	if (h>0) s+=4;
	if (h==0) { h+=15;  m+=22;  s-=27;  mls-=171; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==140320) && (md==0) ) {
	if (h>0) s+=7;
	if (h==0) { h+=13;  m+=23;  s+=41;  mls-=62; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==150320) && (md==0) ) {
	if (h>0) s+=4;
	if (h==0) { h+=14;  m+=6;  s+=51;  mls-=502; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==160320) && (md==0) ) {
//	if (h>0) s+=4;
//	if (h==0) { h+=13;  m+=39;  s+=19;  mls-=963; } 
	if (h>0) s+=3;
	if (h==0) { h+=13;  m+=39;  s+=18;  mls-=963; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==180320) && (md==0) ) {
	if (h>0) s+=5;
	if (h==0) { h+=13;  m+=18;  s+=27;  mls-=425; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==190320) && (md==0) ) {
//	if (h>0) s+=6;
//	if (h==0) { h+=13;  m+=39;  s+=5;  mls-=157; } 
	if (h>0) s+=5;
	if (h==0) { h+=13;  m+=39;  s+=4;  mls-=157; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==200320) && (md==0) ) {
	{ h+=13;  m+=38;  s+=5;  mls-=0; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==200320) && (md==1) ) {
	if (h>0) s+=3;
	if (h==0) { h+=19;  m+=1;  s-=40;  mls-=495; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==210320) && (md==0) ) {
	if (h>0) s+=2;
	if (h==0) { h+=14;  m+=2;  s-=24;  mls-=242; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==210320) && (md==1) ) {
	if (h>0) s+=4;
	if (h==0) { h+=19;  m+=15;  s-=15;  mls-=981; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==220320) && (md==0) ) {
	if (h>0) s+=5;
	if (h==0) { h+=13;  m+=11;  s+=17;  mls-=452; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==220320) && (md==1) ) {
	if (h>0) s+=5;
	if (h==0) { h+=19;  m+=18;  s+=18;  mls-=562; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==250320) && (md==2) ) {
//	{ h+=16;  m+=54;  s+=40;  mls-=0; } 
	{ h+=16;  m+=54;  s+=39;  mls-=0; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==250320) && (md==3) ) {
//	if (h>0) s+=5;
//	if (h==0) { h+=18;  m+=58;  s-=41;  mls-=490; } 
	if (h>0) s+=4;
	if (h==0) { h+=18;  m+=58;  s-=42;  mls-=490; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==260320) && (md==0) ) {
	if (h>0) s+=6;
	if (h==0) { h+=16;  m+=17;  s-=37;  mls-=258; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==260320) && (md==1) ) {
	if (h==0) { h+=19;  m+=16;  s-=4;  mls-=8; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==270320) && (md==0) ) {
	if (h>0) s+=3;
	if (h==0) { h+=16;  m+=6;  s+=18;  mls-=177; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==270320) && (md==1) ) {
	if (h>0) s+=5;
	if (h==0) { h+=18;  m+=50;  s-=3;  mls-=414; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==280320) && (md==0) ) {
	if (h>0) s+=3;
	if (h==0) { h+=19;  m+=57;  s-=45;  mls-=197; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   mar20   ----------------------
//-------------   apr20   ----------------------
    if ( (mmm==110420) && (md==0) ) {
	if (h>0) s+=4;
	if (h==0) { h+=14;  m+=13;  s+=9;  mls-=114; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==130420) && (md==0) ) {
	if (h>0) s+=3;
	if (h==0) { h+=14;  m+=10;  s+=22;  mls-=523; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==160420) && (md==0) ) {
	if (h>0) s+=3;
	if (h==0) { h+=14;  m-=6;  s+=24;  mls-=994; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==220420) && (md==3) ) {
	if (h==0) { h+=17;  m+=11;  s+=6;  mls-=0; } 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   apr20   ----------------------

return TimeEv;
}
//====================================================================
long long Data::AddTime_2019_20_iact02(long long tim) 
{
long long TimeEv=tim;

//-------------   mar20   ----------------------
//-------------   feb20   ----------------------
    if ( (mmm==220120) && (md==3) ) {
	{ h+=11;  m+=23;  s+=40;  mls+=511;  mks+=216;} 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   feb20   ----------------------
//-------------   mar20   ----------------------
    if ( (mmm==200320) && (md==0) ) {
	if (h==0) { h+=13;  m+=21;  s-=23;  mls-=650;} 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==260320) && (md==1) ) {
	{ h+=19;  m+=17;  s-=8;  mls-=0;} 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   mar20   ----------------------
//-------------   apr20   ----------------------
    if ( (mmm==130420) && (md==0) ) {
	{ h+=14;  m+=14;  s+=40;  mls-=0;} 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
    if ( (mmm==160420) && (md==0) ) {
	{ h+=14;  m+=34;  s+=26;  mls-=0;} 
	TimeEv = GetDtime(0);
	GetClock (TimeEv,&h,&m,&s,&mls,&mks,&dns);
    }
//-------------   apr20   ----------------------

return TimeEv;
}
//====================================================================
//====================================================================

