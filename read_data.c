//=========================================================
long long ReadData (int clast)
{
int res=0;
long long tim1=0;
//long long tim2=0;
//long long dtim=0;
//int numpack=0;


	tim1 = DATA[clast].Read_SIPM(0,1);  // data.h

//if(DATA[clast].err_data==3) 
//printf("clast=%i   tim1=%Ld   NumEv=%Ld\n",clast,tim1,DATA[clast].NumEvent);

/*
	if ( tim1==2 ) {
CYC:
	    tim1 = DATA[clast].Read_SIPM(0,1);
	    if ( tim1==2 ) goto CYC;
	}
*/

	if ( tim1<0 ) { 
//qq(333);
	    fclose(DATA[clast].fdat);
	    fclose(ffout);

		DATA[clast].por++;
		DATA[clast].fdat = DATA[clast].OpenFile(DATA[clast].pathfile,&DATA[clast].por,0,&res);
//qq(543217);

		if (res==-1000) {
	    DATA[clast].run=0;
	    DATA[clast].stat=0;
	    DATA[clast].stop=1;
		return -1;
		}

		DATA[0].por++;
		ffout = OpenOutFile(pathout,DATA[0].por,2);


	    if (tim1==-2) tim1 = DATA[clast].Read_SIPM(2,1);
	    if (tim1==-1) tim1 = DATA[clast].Read_SIPM(0,1);
	}

	if (tim1>=0) {

	    return tim1;
	}


//press_any_key();

return tim1;
}
//====================================================================
//=========================================================
