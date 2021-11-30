//=========================================================
long long ReadData (int clast)
{
int res=0;
long long tim1=0;
//long long tim2=0;
//long long dtim=0;
//int numpack=0;


if (clast==25) {
	tim1 = DATA[clast].Read_tim4();
//	tim1 = DATA[clast].Read_tim_c4();
//	tim1 = DATA[clast].Read_HiSC();
}
else {

qq(1);
	tim1 = DATA[clast].Read_SIPM(0,1);  // read_hisc.c
qq(2);
	tim1 = DATA[clast].Read_SIPM(0,1);  // read_hisc.c

}

if(DATA[clast].err_data==3) printf("clast=%i   tim1=%Ld   NumEv=%Ld\n",clast,tim1,DATA[clast].NumEvent);



//press_any_key();
/*
	if ( tim1<-2 ) { 
	    fclose(DATA[clast].fdat);

//		DATA[clast].CloseFile();
		DATA[clast].por=por++;
		kk = DATA[clast].OpenNewFile(pathfile,DATA[clast].por,1);
//qq(kk);
		tim1 = DATA[clast].Read_HiSC(2,DATA[clast].EVENT_H.NumBytes,-1*(int)tim1);  // read_grande.c
printf("tim1=%Ld\n",tim1);
	}
*/
//qq(ip);
	if ( tim1==2 ) {

CYC:

if (clast==25) 
	tim1 = DATA[clast].Read_tim4();
//	tim1 = DATA[clast].Read_tim_c4();
//	tim1 = DATA[clast].Read_HiSC();
else
	tim1 = DATA[clast].Read_SIPM(0,1);

//printf("qq2,  clast=%i   tim1=%Ld   NumEv=%ld\n",clast,tim1,DATA[clast].NumEvent);
//press_any_key();

	if ( tim1==2 ) goto CYC;


	}

	if ( tim1<0 ) { 

qq(333);
	    fclose(DATA[clast].fdat);
	    fclose(ffout);

if (clast==25) {
	    DATA[clast].run=0;
	    DATA[clast].stat=0;
	    DATA[clast].stop=1;
	return -1;
}


//		DATA[clast].CloseFile();
//		DATA[clast].por++;
//		kk = DATA[clast].OpenNewFile(pathfile,DATA[clast].por,1);
//qq(kk);
//		tim1 = DATA[clast].Read_HiSC(2,DATA[xlast].NumBytes,-1*(int)tim1);  // read_grande.c
		DATA[clast].por++;

		DATA[0].por++;


		DATA[clast].fdat = DATA[clast].OpenFile(DATA[clast].pathfile,&DATA[clast].por,0,&res);
		ffout = OpenOutFile(pathout,DATA[0].por,2);
//if (clast==16) 		
//printf("open clast=%i, kk=%i\n",clast,res);

qq(543217);


		
		if (res==-1000) {
	    DATA[clast].run=0;
	    DATA[clast].stat=0;
	    DATA[clast].stop=1;
		return -1;
		}
//		if (res>0) DATA[clast].por = kk;

//		kk = DATA[clast].OpenNewFile(pathout,DATA[clast].por,10);

//		DATA[clast].por = kk;



//	tim1 = DATA[clast].Read_tim4();
//	tim1 = DATA[clast].Read_HiSC();


	if (tim1==-2) tim1 = DATA[clast].Read_SIPM(2,1);
	if (tim1==-1) tim1 = DATA[clast].Read_SIPM(0,1);

/*
	if ( tim1<-4 ) { 
if (clast==25) 
//	tim1 = DATA[clast].Read_tim4();
	tim1 = DATA[clast].Read_HiSC();
else
		tim1 = DATA[clast].Read_IACT(2,DATA[clast].EVENT_I.NumBytes,-1*(int)tim1);  // read_grande.c
//printf("clast=%i   tim1=%Ld   NumEv=%ld\n",clast,tim1,DATA[clast].NumEvent);
	}
	else {
if (clast==25) 
//	tim1 = DATA[clast].Read_tim4();
	tim1 = DATA[clast].Read_HiSC();
else
	    tim1 = DATA[clast].Read_IACT(0,0,0);  // read_hisc.c
//printf("clast=%i   tim1=%Ld   NumEv=%ld\n",clast,tim1,DATA[clast].NumEvent);
	}
*/

	}

	if (tim1>=0) {

//\	DATA[clast].SaveData_HiSCORE();


	    return tim1;
	}

//	if (tim1<0) {
//qq(kk);

//	    DATA[clast].run=0;
//	    DATA[clast].stat=0;
//	    DATA[clast].stop=1;
//	    return -1;
//	}

//press_any_key();

return tim1;
}
//====================================================================
//=========================================================
