#ifndef __TOOLS_H__
#define __TOOLS_H__
//==========================================================
typedef unsigned char    	byte;
typedef short unsigned int	word; 
typedef unsigned int     	lngi;

#define Print 1
#define NoPrint 0
#define PrintErr -1
//==========================================================
void qq(int i);
void press_any_key(void);
void NB( char text[] );
//==========================================================
void qq(int i) 
{
    printf("QQQQQQQQQQQQQ  --  step #%i\n",i);
}
//==========================================================
void press_any_key(void) 
{
int key=0;
    printf("Press 1 and ENTER\n");
    scanf("%i",&key);
}
//==========================================================
void NB(char text[]) 
{
    printf("%s\n",text );
}
//==========================================================
#endif
