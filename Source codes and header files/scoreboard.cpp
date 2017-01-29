#include <iostream>
#include <vector>
#include "graphics.h"
#include <cstdio>
#include <string.h>
using namespace std;

int calc(string str)
{
    int ret = 0, into = 1, len = str.size(), i;

    for(i = len-1; i >= 0; i--)
    {
        ret = ret + (str[i]-'0')*into;
        into = into*10;
    }

    return ret;
}

void getln(char *str)
{
	int i=1;
    char ch,  s[2] = "";


    strcpy(str, "");
    while(i<=10)
    {
        i++;
        ch = getch();
		while(!ch)
		{
            ch = getch();
			ch = getch();
        }
        if(ch == 13 || ch== ' ')
        {
            break;
        }
		if(ch==8)
        {
            str[strlen(str)-1]=0;
			setbkcolor(BLUE);
			setcolor(WHITE);
			settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
            outtextxy(300, 300, str);
            i-=2;
            continue;
        }

        s[0] = ch;
        strcat(str, s);
		setbkcolor(BLUE);
		setcolor(WHITE);
		settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
        outtextxy(500, 300, str);
    }
    return;
}

int leader(int seconds,bool lev)
{
	int k;
	FILE *fp;
	if(lev==0)
		fp = fopen("in.txt", "r");
	else
		fp = fopen("in2.txt", "r");

    vector <string> names[15];
    string  scr,ST;
    char str[100];
    char np[100], sp[100]; // np -> name of the player, sp -> score of the player
    int nw = 1, val, pos = -1, i, j, int_scr;
    sprintf(sp,"%d",seconds);
    scr=sp;
    int_scr = calc(scr);

    sprintf(sp,"Your timing is %d seconds",seconds);

	setbkcolor(BLUE);
	setcolor(WHITE);
	settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
    outtextxy(300, 200, sp);


	
	i=0;
    while(EOF!= fscanf(fp, "%s", str) && nw <= 10 )
    {
		i++;
        names[nw].push_back(str);
        if(i%2==0)
        {
			val = calc(str);
            if(val > int_scr && pos == -1)
            {
                pos = nw;
                names[nw+1] = names[nw];
                names[nw].clear();
                nw++;
            }
            nw++;
        }
    }
    fclose(fp);
	
    if(nw <= 10 && pos == -1) pos = nw;
	cout <<"pos=" <<  pos << endl;
    if(pos == -1)
    {
        delay(500);
        getch();
        getch();

        return 0;
    }
    delay(500);
    outtextxy(100, 300, "Enter Your Name: ");
    getln(np);
    ST = np;

    names[pos].push_back(ST);
    names[pos].push_back(scr);

	if(lev==0)
		fp=fopen("in.txt", "w");
	else
		fp = fopen("in2.txt", "w");

	for(i = 1; i <= min(nw,10); i++)
    {
        for(j = 0; j <= 1; j++)
        {
			for(k=0;k<(int)names[i][j].size();k++)
			{
				fprintf(fp,"%c",names[i][j][k]);
			}
            fprintf(fp," ");
        }
        fprintf(fp,"\n");
    }
   fclose(fp);
   return 0;
}
