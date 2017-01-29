#include "leaderboard.h"

#define inf         (1 << 30 - 1)
#define pii         pair<double,double>
#define mp          make_pair
#define fi          first
#define se          second
#define xx          fi
#define yy          se

#define PRE_TP		600
#define PRE_BT		680
#define dim1		1000
#define dim2		750

#define KEY_UP		72
#define KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_DOWN	80
#define KEY_ESCAPE	27

typedef long long int LL;
typedef double db;

using namespace std;

pii TOPL,BOTL,TOPR,BOTR,tempL,tempR;

//faka rasta
int Y1,Y2,y2,y3,tw1,tw2,bw2,tw3,tw4,hh;
double m1,c1,m2,c2;
pii lt1,lt2,rb1,rb2,rt2,lt3,rb3;

//this is the road!
int roadbottom[8]= {150,710,150,740,850,740,850,710};
int Road[8]= {450,200,150,710,850,710,550,200};

int road[8]= {450,200,113,750,875,750,550,200};


//this is the spacecraft!
int plbody[8]= {500,600,450,650,500,680,550,650};
int pllft[8]= {450,650,430,670,450,670,470,650};
int plrgt[8]= {530,650,550,670,570,670,550,650};

// variables
int h,i,j,k,nwh,nwx,nwb,nwbh,hb,rb,A[8],q,cnt=0,lb,ht,I;
int O2,h2;
char cmnd;
int moved=0,SECONDS;
int level=0;

//these variables are for "Game_over" function:
int obslftx,obsrgtx,obstpy,obsbty,planetpy,planebty,rdlftx,rdrgtx,rdtpy,planergtx,planelftx;
int lightxl=440;
int lightxr=560;
int lightyl=670;
int lightyr=670;
bool FINISH=0;

// VARIABLES FOR URADHURA OBS
int O1X,O1Y,L1;
int height;
int O2X,O2Y,L2;
int H2;
int O3X,O3Y,L3;
int H3;
int O4X,O4Y,L4;
int H4;
int O5X,O5Y,L5;
int H5;

struct quadrilateral
{
    pii top;
    pii lft;
    pii bot;
    pii rght;
} spcB,spcL,spcR;


void jump();
void jump_2();

struct SL
{
    db m;
    db c;
} lft,rght;

SL solve(pii a,pii b)
{
    SL ret;
    ret.m=(a.yy-b.yy)/(a.xx-b.xx);
    ret.c=a.yy-ret.m*a.xx;
    return ret;
}

void drawroad()
{
    setcolor(7);
    setfillstyle(SOLID_FILL,7);
    fillpoly(4,road);
}

void Drawroad()
{
    setcolor(7);
    setfillstyle(SOLID_FILL,7);
    fillpoly(4,Road);
    setfillstyle(SOLID_FILL,8);
    fillpoly(4,roadbottom);
}

void draw_new_road(pii ltop ,pii rbtm,int twidth,int bwidth,int color)
{
    pii lbtm, rtop;
    rtop.xx=ltop.xx+twidth;
    rtop.yy=ltop.yy;
    lbtm.xx=rbtm.xx-bwidth;
    lbtm.yy=rbtm.yy;

    int newroad[8]= {ltop.xx,ltop.yy,lbtm.xx,lbtm.yy,rbtm.xx,rbtm.yy,rtop.xx,rtop.yy};
    int newroadbtm[8]= {lbtm.xx,lbtm.yy,lbtm.xx,lbtm.yy+25,rbtm.xx,rbtm.yy+25,rbtm.xx,rbtm.yy};
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,newroad);
    int btclr;
    if(color==7)
        btclr=8;
    else if(color==10)
        btclr=2;
    else if(color==9)
        btclr=1;
    setcolor(btclr);
    setfillstyle(SOLID_FILL,btclr);
    fillpoly(4,newroadbtm);



}

void drawplane(int moved,int height)
{
    int m;
    for(m = 0; m <= 7; m +=2)
    {
        plbody[m]+=moved;
        pllft[m]+=moved;
        plrgt[m]+=moved;
    }

    int h;
    for(h = 1; h <= 7; h+=2)
    {
        plbody[h]-=height;
        pllft[h]-=height;
        plrgt[h]-=height;
    }
    setcolor(3);
    setfillstyle(SOLID_FILL,3);
    fillpoly(4,plbody);
    setfillstyle(SOLID_FILL,3);
    fillpoly(4,pllft);
    setfillstyle(SOLID_FILL,3);
    fillpoly(4,plrgt);
    setfillstyle(SOLID_FILL,3);
    setcolor(14);
    setfillstyle(SOLID_FILL,14);
    lightxl+=moved;
    lightxr+=moved;
    lightyl-=height;
    lightyr-=height;
    fillellipse(lightxl,lightyl,10,10);
    fillellipse(lightxr,lightyr,10,10);
}

void obstacle(int pos,int height)
{

    TOPL.xx=450;
    TOPL.yy=200;
    BOTL.xx=150;
    BOTL.yy=710;
    TOPR.xx=550;
    TOPR.yy=200;
    BOTR.xx=850;
    BOTR.yy=710;
    lft=solve(TOPL,BOTL);
    rght=solve(TOPR,BOTR);

    h=1;
    setcolor(RED);
    tempL.yy=pos;
    tempL.xx=(tempL.yy-lft.c)/lft.m;
    tempR.yy=pos;
    tempR.xx=(tempR.yy-rght.c)/rght.m;

    nwh=h+height/2;
    int A[8]= {tempL.xx,tempL.yy,tempL.xx,tempL.yy+nwh,tempR.xx,tempR.yy+nwh,tempR.xx,tempR.yy};
    setfillstyle(SOLID_FILL,RED);
    fillpoly(4,A);
    obslftx=0;
    obsrgtx=inf;
}

void obstacleV2(int lbtmx,int lbtmy,int lgth,int height,int color)
{
    int rbtmx=lbtmx+lgth;
    int rbtmy=lbtmy;
    int nwh=h+height/2;
    int C[8]= {lbtmx,lbtmy-nwh,lbtmx,lbtmy,rbtmx,rbtmy,rbtmx,rbtmy-nwh};
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,C);
    obstpy=lbtmy-nwh;
    obslftx=lbtmx;
    obsrgtx=rbtmx;
}

void SECONDS_count()
{
    int q=0;
    while(!kbhit())
    {
        q++;
        if(q==5500000)
        {
            SECONDS++;
            q=0;
        }
    }
    return;
}

int Game_over()
{
    //return 0;
    if(level==1)
    {
        rdrgtx=836;
        rdlftx=155;
        rdtpy=0;
    }
    planetpy=plbody[1];
    planebty=planetpy+80;

    if(rdtpy-30>planetpy && rdtpy>=600 && planebty>=680)
    {
        return 1;
    }


    if(lightxr>=rdrgtx)
        return 1;
    if(lightxl<=rdlftx)
        return 1;

    if(obstpy<510)
        return 0;
    if(obslftx>lightxr || obsrgtx<lightxl)
        return 0;
    if(obstpy+100>=planetpy && obstpy+80<=planebty)
    {
        return 1;
    }

    return 0;
}

void OVER()
{
    int c;
    FINISH=1;
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(500,375,10000,10000);
    delay(300);
    readimagefile("game_over.jpg",0,0,1000,750);

    delay(500);
    while(1)
    {
        c=getch();
        if(c==13)
            return;
    }
}

void TAKE_COMMAND()
{
take_command2:
    ;

    SECONDS_count();
    cmnd=getch();

    if(cmnd==0)
    {
        cmnd=getch();
        if(cmnd==KEY_RIGHT)
            drawplane(12,0);

        else if (cmnd==KEY_LEFT)
            drawplane(-12,0);

        else if(cmnd!=KEY_UP)
        {
            obstacle(lb,ht);
            drawplane(0,0);
            cmnd=-1;
            goto take_command2;
        }
    }

    else if(cmnd==' ')
    {
        if(level==1 || level==2)
            jump();
        else if(level==3)
            jump_2();
    }

    else
    {
        obstacle(lb,ht);
        drawplane(0,0);
        cmnd=-1;
        goto take_command2;
    }
	if(FINISH==1)
		return;
    drawplane(0,0);
    cmnd=-1;
}




void jump( )
{
    int cnt=0;

    // this for loop takes the plane upwards

    for(q=-1; q>=-410; q-=45,lb+=9,ht+=6,cnt++)
    {
        if(cnt==15)
        {
            SECONDS++;
            cnt=0;
        }
        if(lb>400)
        {
            lb+=1;
            if(I%2==0)
            {
                obstacle(O2,h2);
                if(lb>650)
                    O2+=2;
                O2+=6;
                h2+=4;
                obstpy=O2;
            }

        }

        if(lb<=750)
        {
            obstacle(lb,ht);
            obstpy=lb;
        }

        if(FINISH==1)
            return;
        if(Game_over())
        {
            OVER();
			cout << "hello" << endl;
            return;
        }
		cout << "asd" << endl;
        if(FINISH==1)
            return;

        drawplane(0,30);

        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);
        drawroad();
    }
    //this for loop is for taking the plane downwards.
    // comments above are also applicable here
    for(q=-410; q<=0; q+=45,ht+=6,lb+=9,cnt++)
    {
        if(cnt==15)
        {
            SECONDS++;
            cnt=0;
        }

        if(lb>400)
        {
            lb+=1;
            if(I%2==0)
            {
                obstacle(O2,h2);
                if(lb>650)
                    O2+=2;
                O2+=6;
                h2+=4;
                obstpy=O2;
            }
        }

        if(lb<=750)
        {
            obstacle(lb,ht);
            obstpy=lb;
        }

        if(FINISH==1)
            return;
        if(Game_over())
        {
            OVER();
            return;
        }
        if(FINISH==1)
            return;


        drawplane(0,-30);
        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);
        drawroad();
    }
}

void one_obs()
{
    int cnt=0;
    for(lb=200,ht=1; lb<=750; lb+=6,ht+=4,cnt++)
    {
        drawplane(0,0);
        if(cnt==25)
        {
            cout << SECONDS << endl;
            SECONDS++;
            cnt=0;
        }

        if(lb>350)
            lb+=1;
        obstacle(lb,ht);
        obstpy=lb;
        q=0;
        TAKE_COMMAND();
		if(FINISH==1)
            return;
        if(Game_over())
        {
            OVER();
            return;
        }
        if(FINISH==1)
            return;
        drawroad();
    }
}

void two_obs()
{
    int cnt=0;
    for(lb=200,ht=1,O2=200,i=1,h2=1; lb<=1000; lb+=6,ht+=4,i++,cnt++)
    {
        drawplane(0,0);
        if(cnt==25)
        {
            SECONDS++;
            cnt=0;
        }
        if(lb>=400)
        {
            lb+=1;
            obstacle(O2,h2);
            if(lb>650)
                O2+=1;
            O2+=6;
            h2+=4;
            obstpy=O2;
        }

        if(lb<=750)
        {
            obstacle(lb,ht);
            obstpy=lb;
        }

        TAKE_COMMAND();
		if(FINISH==1)
            return;

        if(Game_over())
        {
            OVER();
            return;
        }

        if(FINISH==1)
            return;
        drawroad();
    }
}

void getscore(int lev)
{
    readimagefile("leaders.jpg",0,0,dim1,dim2);
    int i,ycor;
    setbkcolor(WHITE);
    setcolor(BLUE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    outtextxy(270,100,"LEADER BOARD");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(80,200,"NAME");
    outtextxy(740,200,"TIME");
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    FILE *fp;
	if(lev==1)
		fp=fopen("in.txt","r");
	else 
		fp=fopen("in2.txt","r");
    char name[20],a[5],score[10],c='.';
    for(i=1,ycor=250; i<=10; i++,ycor+=50)
    {
        if(1!=fscanf(fp,"%s",name))
            break;
        fscanf(fp,"%s",score);
        sprintf(a,"%2d",i);
        outtextxy(80,ycor,a);
        sprintf(a,"%c",c);
        outtextxy(120,ycor,a);
        outtextxy(140,ycor,name);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);
        outtextxy(740,ycor,score);
    }
    fclose(fp);
    return;
}


void show(int pres)
{
    if(pres==0)
        readimagefile("play.jpg",0,0,dim1,dim2);
    if(pres==1)
        readimagefile("Instructions.jpg",0,0,dim1,dim2);
    if(pres==2)
        readimagefile("Leaderboard.jpg",0,0,dim1,dim2);
    if(pres==3)
        readimagefile("Exit.jpg",0,0,dim1,dim2);
    if(pres==5)
        readimagefile("ins.jpg",0,0,dim1,dim2);

   
    if(pres==7)
        readimagefile("level1.jpg",0,0,dim1,dim2);
    if(pres==8)
        readimagefile("level2.jpg",0,0,dim1,dim2);
	if(pres==9)
		readimagefile("lev1.jpg",0,0,dim1,dim2);
	if(pres==10)
		readimagefile("lev2.jpg",0,0,dim1,dim2);
	if(pres==11)
	{
		readimagefile("leaders.jpg",0,0,dim1,dim2);
        getscore(1);
		while(1)
		{
			int command=getch();
			if(command==KEY_ESCAPE)
				return;
		}
	}
	if(pres==12)
	{
		readimagefile("leaders.jpg",0,0,dim1,dim2);
        getscore(2);
		while(1)
		{
			int command=getch();
			if(command==KEY_ESCAPE)
				return;
		}
	}
    return;
}



int DOO(int pres) /// -1 means exit,  -2 means go to main menu
{
    int command;
    if(pres==3)
        return -1;
    if(pres==2)
    {
		int present=9;
        show(9);
        while(1)
        {
            command=getch();
            if(command==KEY_ESCAPE)
                return -2;
			if(command==13)
			{
				show(present+2);
				show(present);
			}
			if(command==0)
			{
				command=getch();
				if(command==KEY_UP)
				{
					present=max(9,present-1);
					show(present);
				}
				else if(command==KEY_DOWN)
				{
					present=min(10,present+1);
					show(present);
				}
			}

        }
    }

    if(pres==1)
    {
        show(5);
        while(1)
        {
            command=getch();
            if(command==27)
                return -2;
        }
    }

    if(pres==0)
    {
        int present=7;

        while(1)
        {
            show(present);
            command=getch();
            if(command==13)
                return present;
            else if(command==27)
                return -2;
            else if(command==0)
            {
                command=getch();
                if(command==KEY_UP)
                    present=max(7,present-1);
                else if(command==KEY_DOWN)
                    present=min(8,present+1);
            }
        }
    }
}

char str[30];

void kickstart()
{
    int cnt=0;
    while(1)
    {
        SECONDS_count();
        cmnd=getch();
        if(cmnd==0)
        {
            cmnd=getch();
            if(cmnd==KEY_UP)
            {
                delay(500);
                return;
            }
        }
    }
}


void LEVEL(int lev)
{
    int command;
    if(lev==1)
    {
        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);

        Drawroad();
        drawplane(0,0);

        SECONDS_count();

        kickstart();
        drawroad();
        drawplane(0,0);
        while(I<5)
        {
            if(FINISH==1)
                break;
            I++;
            if(I%2==1)
                one_obs();

            else
                two_obs();
			
        }
        readimagefile("leaders.jpg",0,0,dim1,dim2);
        if(FINISH==0)
            leader(SECONDS,0);
        getscore(1);

        while(1)
        {
            command=getch();
            if(command==KEY_ESCAPE)
                return;
        }
    }
    else
    {
        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);

        rb1.xx=875,rb1.yy=750;
        SL eq1=solve(mp(450,200),mp(113,750));
        m1=eq1.m;
        c1=eq1.c;
        SL eq2=solve(mp(550,200),mp(875,750));
        m2=eq2.m;
        c2=eq2.c;

        Drawroad();
        drawplane(0,0);

        SECONDS_count();

        kickstart();

        ///whole level 2
        {
            drawroad();
            drawplane(0,0);

            rdrgtx=836;
            rdlftx=155;
            I=2;
            two_obs();
			
            I=1;
			if(FINISH!=1)
				one_obs();
			
            level=3;
            y2=180;
            lt2.yy=y2;
            lt2.xx=(lt2.yy-c1)/m1;
            rt2.yy=y2;
            rt2.xx=(rt2.yy-c2)/m2;
            O1X=lt2.xx,O1Y=lt2.yy,L1=20;
            L2=20,O2X=rt2.xx-L2,O2Y=rt2.yy;
            O3X=lt2.xx,O3Y=lt2.yy,L3=20;
            O4X=rt2.xx-L2,O4Y=rt2.yy+15,L4=20,H4=30;
            O5X=lt2.xx,O5Y=lt2.yy+15,L5=90,H5=H4;
			int cnt=0;
            for(Y1=200,Y2=200,y2=200,tw1=100,height=10,tw2=100,tw3=100,tw4=100,hh=10; Y1<=5000 && FINISH!=1; Y1+=10,tw1+=10,cnt++)
            {
				if(cnt>=10)
				{
					cnt=0;
					SECONDS++;
				}
                lt1.yy=Y1;
                lt1.xx=(lt1.yy-c1)/m1;
                rb2.yy=lt1.yy-70;
                rb2.xx=lt1.xx+tw1;
                if(Y1>2600)
                {
                    lt2.yy=Y2;
                    lt2.xx=(lt2.yy-c1)/m1;
                    rb2.yy=rb1.yy;
                    rb2.xx=rb1.xx-100;
                    draw_new_road(lt2,rb2,tw3,650,10);
                    rdtpy=lt2.yy;
                    tw3+=10;
                    Y2+=10;

                    lt3.yy=y2;
                    lt3.xx=(lt3.yy-c1)/m1;
                    rb3.yy=lt2.yy-70;
                    rb3.xx=lt2.xx+tw3;
                    draw_new_road(lt3,rb3,tw4,tw3,9);
                    if(rb3.xx-tw3<700)
                        obstacleV2(rb3.xx-tw3,rb3.yy,tw3,hh,4);
                    hh+=3;
                    rb3.yy=lt2.yy-70;
                    rb3.xx=lt2.xx+tw3;

                    if(lt2.yy>600)
                        rdtpy=0;

                }
                else
                {
                    draw_new_road(lt2,rb2,tw2,tw1,10);
                    rdtpy=0;
                }

                draw_new_road(lt1,rb1,tw1,762,7);
                drawplane(0,0);
                if(Y1<=750)
                    rdtpy=Y1;
                if(Y1>1000 && Y1<1600)
                {
                    obstacleV2(O1X,O1Y,L1,height,5);
                    O1X-=5;
                    O1Y+=10;
                    L1+=5;
                    height+=4;
                }


                if(Y1>1700 && Y1<2550)
                {
                    obstacleV2(O3X,O3Y,L3,height-270,6);
                    O3X-=5;
                    O3Y+=10;
                    L3+=3;
                    height+=2;

                }


                if(Y1>1500 && O2Y<700)
                {
                    obstacleV2(O2X,O2Y,L2,height-200,12);
                    O2X-=1;
                    O2Y+=10;
                    L2+=4;
                    height+=2;

                }
                if(Y1>3400)
                {
                    obstacleV2(O4X,O4Y,L4,H4,4);
                    O4X-=1;
                    O4Y+=10;
                    L4+=5;
                    H4+=3;

                }

                if(Y1>3900)
                {
                    obstacleV2(O5X,O5Y,L5,H5,13);
                    O5X-=3;
                    O5Y+=10;
                    L5+=6;
                    H5+=3;

                }

				
                TAKE_COMMAND();
                if(FINISH==1)
                    break;
                if(Game_over())
                {
                    OVER();
                    break;
                }

                readimagefile("space-sunrise.jpg",0,0,dim1,dim2);
            }

        }

        readimagefile("leaders.jpg",0,0,dim1,dim2);
        if(FINISH==0)
            leader(SECONDS,1);
        getscore(2);
        while(1)
        {
            command=getch();
            if(command==KEY_ESCAPE)
                return;
        }
    }
    return;
}

void RESET()
{
    //Resetting plbody
    plbody[0]=500;
    plbody[1]=600;
    plbody[2]=450;
    plbody[3]=650;
    plbody[4]=500;
    plbody[5]=680;
    plbody[6]=550;
    plbody[7]=650;

    //Resetting pllft

    pllft[0]= 450;
    pllft[1]= 650;
    pllft[2]= 430;
    pllft[3]= 670;
    pllft[4]= 450;
    pllft[5]= 670;
    pllft[6]= 470;
    pllft[7]= 650;

    //Resetting plrgt
    plrgt[0]= 530;
    plrgt[1]= 650;
    plrgt[2]= 550;
    plrgt[3]= 670;
    plrgt[4]= 570;
    plrgt[5]= 670;
    plrgt[6]= 550;
    plrgt[7]= 650;


    h=0,j=0,k=0,nwh=0,hb=0,rb=0,q=0,cnt=0,lb=0,ht=0,I=0;
    O2=0,h2=0;
    cmnd=-1;
    moved=0,SECONDS=0;
    level=0;

    //these variables are for "Game_over" function:
    obslftx=0,obsrgtx=0,obstpy=0,obsbty=0,planetpy=0,planebty=0,rdlftx=0,rdrgtx=0,rdtpy=0;
    lightxl=440;
    lightxr=560;
    lightyl=670;
    lightyr=670;
    FINISH=0;
}

void jump_2()
{
    int cnt=0;

    // this for loop takes the plane upwards

    for(q=-1; q>=-410; q-=45,cnt++,Y1+=20,tw1+=20)
    {
        drawplane(0,30);
        lt1.yy=Y1;
        lt1.xx=(lt1.yy-c1)/m1;

        rb2.yy=lt1.yy-70;
        rb2.xx=lt1.xx+tw1;
        if(Y1>2600)
        {
            lt2.yy=Y2;
            lt2.xx=(lt2.yy-c1)/m1;
            rb2.yy=rb1.yy;
            rb2.xx=rb1.xx-100;
            draw_new_road(lt2,rb2,tw3,650,10);
            rdtpy=lt2.yy;
            tw3+=10;
            Y2+=10;

            lt3.yy=y2;
            lt3.xx=(lt3.yy-c1)/m1;
            rb3.yy=lt2.yy-70;
            rb3.xx=lt2.xx+tw3;
            draw_new_road(lt3,rb3,tw4,tw3,9);
            obstacleV2(rb3.xx-tw3,rb3.yy,tw3,hh,4);

        }
        else
            draw_new_road(lt2,rb2,tw2,tw1,10);
        drawplane(0,0);
        draw_new_road(lt1,rb1,tw1,762,7);
        drawplane(0,0);
        obstpy=-inf;
        if(Y1<=750)
            rdtpy=Y1;
        obstpy=-inf;
        if(Y1>1000 && Y1<1600)
        {
            obstacleV2(O1X,O1Y,L1,height,5);
            O1X-=5;
            O1Y+=10;
            L1+=5;
            height+=4;
        }


        if(Y1>1700)
        {
            obstacleV2(O3X,O3Y,L3,height-270,6);
            O3X-=5;
            O3Y+=10;
            L3+=3;
            height+=2;

        }


        if(Y1>1500 && O2Y<700)
        {
            obstacleV2(O2X,O2Y,L2,height-200,12);
            O2X-=1;
            O2Y+=10;
            L2+=4;
            height+=2;

        }

        if(Y1>3400)
        {
            obstacleV2(O4X,O4Y,L4,H4,4);
            O4X-=1;
            O4Y+=10;
            L4+=5;
            H4+=3;

        }

        if(Y1>3900)
        {
            obstacleV2(O5X,O5Y,L5,H5,13);
            O5X-=3;
            O5Y+=10;
            L5+=6;
            H5+=3;

        }

        drawplane(0,0);

        if(Game_over())
        {
            OVER();
            return;
        }

        if(cnt==15)
        {
            SECONDS++;
            cnt=0;
        }

        if(FINISH==1)
            return;
        if(Game_over())
        {
            OVER();
            return;
        }
        if(FINISH==1)
            return;



        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);
        drawplane(0,0);
    }
    //this for loop is for taking the plane downwards.
    // comments above are also applicable here
    for(q=-410; q<=0; q+=45,cnt++,Y1+=10,tw1+=10)
    {
        drawplane(0,-30);
        lt1.yy=Y1;
        lt1.xx=(lt1.yy-c1)/m1;

        rb2.yy=lt1.yy-70;
        rb2.xx=lt1.xx+tw1;
        if(Y1>2600)
        {
            lt2.yy=Y2;
            lt2.xx=(lt2.yy-c1)/m1;
            rb2.yy=rb1.yy;
            rb2.xx=rb1.xx-100;
            draw_new_road(lt2,rb2,tw3,650,10);
            tw3+=10;
            Y2+=10;

            lt3.yy=y2;
            lt3.xx=(lt3.yy-c1)/m1;
            rb3.yy=lt2.yy-70;
            rb3.xx=lt2.xx+tw3;
            draw_new_road(lt3,rb3,tw4,tw3,9);
            obstacleV2(rb3.xx-tw3,rb3.yy,tw3,hh,4);

        }
        else
        {
            draw_new_road(lt2,rb2,tw2,tw1,10);
            rdtpy=0;
        }

        drawplane(0,0);
        draw_new_road(lt1,rb1,tw1,762,7);
        drawplane(0,0);
        if(Y1<=750)
            rdtpy=Y1;
        else
            rdtpy=0;
        obstpy=-inf;
        if(Y1>1000 && Y1<1600)
        {
            obstacleV2(O1X,O1Y,L1,height,5);
            O1X-=5;
            O1Y+=10;
            L1+=5;
            height+=4;
        }


        if(Y1>1700)
        {
            obstacleV2(O3X,O3Y,L3,height-270,6);
            O3X-=5;
            O3Y+=10;
            L3+=3;
            height+=2;

        }


        if(Y1>1500 && O2Y<700)
        {
            obstacleV2(O2X,O2Y,L2,height-200,12);
            O2X-=1;
            O2Y+=10;
            L2+=4;
            height+=2;

        }

        if(Y1>3400)
        {
            obstacleV2(O4X,O4Y,L4,H4,4);
            O4X-=1;
            O4Y+=10;
            L4+=5;
            H4+=3;

        }

        if(Y1>3900)
        {
            obstacleV2(O5X,O5Y,L5,H5,13);
            O5X-=3;
            O5Y+=10;
            L5+=6;
            H5+=3;

        }

        drawplane(0,0);
        if(Game_over())
        {
            OVER();
            return;
        }

        if(cnt==15)
        {
            SECONDS++;
            cnt=0;
        }


        if(FINISH==1)
            return;

        readimagefile("space-sunrise.jpg",0,0,dim1,dim2);
        drawplane(0,0);
    }
}



int main()
{
    int command,present=0,temporary;
    initwindow(dim1, dim2, "First Sample");

    /// MAIN MENU

    readimagefile("play.jpg",0,0,dim1,dim2);
    while(1)
    {

        RESET();

        present=0;
        show(present);
        while(1)
        {
            command=getch();
            if(command==13)
            {
                temporary=DOO(present);
                if(temporary==-1)
                    return 0;
                else if(temporary==-2)
                {
                    present=0;
                    show(present);
                    continue;
                }
                break;
            }
            if(command!=0)
                continue;
            command=getch();
            if(command==KEY_UP)
                present=max(present-1,0);
            else if(command==KEY_DOWN)
                present=min(3,present+1);
            else
                continue;
            show(present);
        }
        if(temporary==7)
        {
            level=1;
            LEVEL(1);
        }
        else
        {
            level=2;
            LEVEL(2);
        }
    }

    return 0;
}
