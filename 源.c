#include "airport.h"
#include "graph.h"
#include<graphics.h>


Settings * set;
Cmd * CommandTxt;
Cmd * CommandCmd;
Cmd * CommandNIS;
Cmd * CommandBtn;
Guest * GlistH; 
Guest * CurG;
Guest * OutGListH;
Guest * CurOutG;
Guest * unfacedG;
Guest * CurCptG[MaxCheckPts];
Guest * CptGListH[MaxCheckPts];
Guest * PreOutGMark;
Guest * PreOutG; 
BufArea * bfa;
int RestList[MaxCheckPts];
CheckPt * cpt[MaxCheckPts];
CheckPt_Que * cptq[MaxCheckPts];
int TimeClock;
int CurCmd;						
int threadkey;						
int sumguest;						
int SumWaitLen;	
int txtin;
int nisin;
int mode;
int frame;					
FILE * input;						
FILE * Output;						
FILE * Outputdetail;	
int counttr;
PIMAGE BFAbkg;
PIMAGE bkg1;
PIMAGE FaceList[MaxFaceNum];
PIMAGE CMD_R;
PIMAGE CMD_G;
PIMAGE CMD_Q;
PIMAGE CMD_Rf;
PIMAGE CMD_Qf;
mouse_msg msg;
int cmdnum;
int MsgBoxNum;
//文本命令
DWORD WINAPI TxtCmd(LPVOID lpParameter)
{

	int R_Count = 0;
	int i = 0;
		
	if (CommandTxt->t == TimeClock)
	{
		ProcessCmd(CommandTxt);

		InitCmd(CommandTxt);
		GetCmd(CommandTxt, input);
	}
	return 0;
}

//窗口操作
DWORD WINAPI OP_WIN(LPVOID lpParameter)
{
	for(int i = 0; i < MaxCheckPts; i++)
		Que_StateJudge(cptq[i]);
	OpenWin(cpt, bfa, set);
	CloseWin(cpt, bfa, set);
	RestAll(cptq, cpt, bfa, set);
	Transfer(bfa, cptq, cpt);
	ShapeJudge(bfa);
	Check(cpt, cptq);
	return 0;
}



//输入命令行指令
DWORD WINAPI InputCmd(LPVOID lpParameter)
{
	
	ProcessCmd(CommandCmd);
	return 0;
}

//正态分布生成乘客
DWORD WINAPI Cmd_NorDis(LPVOID IpParameter)
{

	InitCmd(CommandNIS);
	CommandCmd->t = TimeClock;
	CreatPassenger_NorDis(CommandNIS, TimeClock);

	ProcessCmd(CommandNIS);

	return 0;
}

//输出
DWORD WINAPI OUTPUT(LPVOID IpParameter)
{
	//OutPutWin();
	FOutPut(Output);
	return 0;
}

//主程序
int main(int argc, char *argv[])
{
	HANDLE CmdSTL;
	HANDLE WINOP;
	HANDLE GETCMD;
	HANDLE NORDIS;
	HANDLE OUTP;
	HANDLE BTN;
	Outputdetail = fopen("OutputDetail.txt", "w");
	char c;
	int choice = 0;
	InitAll();
	CWIN();
	

	setcolor(BLACK);
	GetFaceList();
	MsgBoxNum = 0;
	BFAbkg = newimage(457,418);
	getimage(BFAbkg, 50,50,457,418);
	bkg1 = newimage(1280, 720);
	PIMAGE bk = newimage(1280, 720);
	getimage(bk, "imgs\\背景_改.png");
	
	CMD_R = newimage(70,35);
	CMD_G = newimage(100,50);
	CMD_Q = newimage(100,50);
	CMD_Rf = newimage(70,35);
	CMD_Qf = newimage(100, 50);
	getimage(CMD_R,"imgs\\圆角矩形 1.png",70,35);
	getimage(CMD_G,"imgs\\圆角矩形 2.png",100, 50);
	getimage(CMD_Q,"imgs\\圆角矩形 2.png",100, 50);
	getimage(CMD_Rf,"imgs\\圆角矩形 1灰.png", 70,35);
	getimage(CMD_Qf, "imgs\\圆角矩形 2灰.png", 100, 50); 

	int i;
	for(i = 0;i < MaxCheckPts; i++)
	{
		if(cpt[i]->state == RestRequest || cpt[i]->state == RestDenied || cpt[1]->state == OffApproved)
			putimage_transparent(NULL, CMD_Rf, 1040, 87 + i * 72,BLACK);
		else
			putimage_transparent(NULL, CMD_R, 1040, 87 + i * 72,BLACK);
		if(cpt[i]->state == Resting)
			outtextxy(1065,88+72 * i , "C");
		else
			outtextxy(1065,88 + 72 * i, "R");
	}
	putimage_transparent(NULL, CMD_G, 60,650,BLACK);
	if(cpt[0]->state != OffApproved)
		putimage_transparent(NULL, CMD_Q,180,650,BLACK);
	else
		putimage_transparent(NULL, CMD_Qf, 180, 650, BLACK); 
	outtextxy(100,655,"G");
	outtextxy(220,655,"Q");

	
	



	for(;is_run();delay_fps(1))
	{	
			mouse_msg msg = {0};	
		
					
		
		
		
		setfont(40, 0, "黑体");
		cmdnum = 0;
		Outputdetail = fopen("OutputDetail.txt", "a");

		for(i = 0; i < MaxCheckPts; i++)
		{
			cpt[i]->req_rest = 0;
			cpt[i]->req_con = 0;
			cpt[i]->torest = 0;
			cptq[i]->en = cptq[i]->out = 0;
		}
		
		bfa->en = bfa->out = 0;
		
		
			GETCMD = CreateThread(NULL, 0, InputCmd, NULL, 0, NULL);
		if (txtin)
			CmdSTL = CreateThread(NULL, 0, TxtCmd, NULL, 0, NULL);
			Sleep(10);
		if(nisin)
			NORDIS = CreateThread(NULL, 0, Cmd_NorDis, NULL, 0, NULL);
			Sleep(10);

		WINOP = CreateThread(NULL, 0, OP_WIN, NULL, 0, NULL);
			Sleep(10);	
		ProcessCmd(CommandBtn);
		OUTP = CreateThread(NULL, 0, OUTPUT, NULL, 0, NULL);
		fclose(Outputdetail);
		createface();
		InitCmd(CommandBtn);
		InitCmd(CommandCmd);
		if(!(bfa->out))
			PreOutG = CurOutG;
		else
			PreOutG = PreOutGMark;
		
		
		
		
		
		
		
		if(cpt[0]->state == Off) 
			exit(0);
		
		
		
		
		
		
		//graph
		for(;is_run();delay_fps(60))
		{
			frame++;
			//cleardevice();
		
		
		putimage(0,0,bk);	
		/*
		xyprintf(0,0,"%d",bfa->Cur_Num);
		xyprintf(50,0,"%d",cptq[0]->PAmount);
		xyprintf(100,0,"%p",CurOutG);
		xyprintf(450,0,"%p",CurG);
		xyprintf(800,0,"%p",GlistH);
		xyprintf(1150,0,"%d",counttr);
		xyprintf(0,600, "%d", TimeClock);
		*/
		/*
		
		putimage(0,500,CurOutG->face); 
		for(i = 0;i < MaxCheckPts; i++)
		{
			putimage(1040, 57 + i * 72,CMD_R);
			if(cpt[i]->state == Resting)
				outtextxy(1070,58+72 * i , "C");
			else
				outtextxy(1070,58 + 72 * i, "R");
		}
		putimage(60,650,CMD_G);
		putimage(180,650,CMD_Q);
		outtextxy(90,651,"G");
		outtextxy(210,651,"Q");
		for(i = 0;i<8;i++)
			outtextxy(1070,58+72*i,"R");
		*/
		
		xyprintf(0,500, "T = %d", TimeClock);
		
		cptq_graph();
		
		bfa_image();
	
		KbIn(CommandCmd);
	
		CommandCmd->t = TimeClock;
		setcolor(BLACK);
		setfont(40, 0, "黑体");
		for(i = 0;i < MaxCheckPts; i++)
		{
			if(cpt[i]->state == RestRequest || cpt[i]->state == RestDenied || cpt[1]->state == OffApproved)
				putimage_transparent(NULL, CMD_Rf, 1040, 87 + i * 72,BLACK);
			else
				putimage_transparent(NULL, CMD_R, 1040, 87 + i * 72,BLACK);
			if(cpt[i]->state == Resting)
				outtextxy(1065,88+72 * i , "C");
			else
				outtextxy(1065,88 + 72 * i, "R");
		}
		putimage_transparent(NULL, CMD_G, 60,650,BLACK);
		if(cpt[0]->state != OffApproved)
		putimage_transparent(NULL, CMD_Q,180,650,BLACK);
		else
		putimage_transparent(NULL, CMD_Qf, 180, 650, BLACK); 
		outtextxy(100,655,"G");
		outtextxy(220,655,"Q");

		msg = {0};
		SelectCmd(); 
		
		
		
		getMsgBoxNum();
		DetailMsg();
		SelectCmd(); 
		
		
		setfont(40, 0, "黑体");
		
		
		
		
		Checkegefps();
		Bubblefps();
		
		
		if(frame == 60)
			break;
		
		
		}
		
		frame = 0;

		
		
	
		CommandBtn->t = TimeClock;
		
	
	
		
		TimeClock++;
		
		
		
		
		if(!(bfa->out))
			PreOutG = CurOutG;
		else
			PreOutG = PreOutGMark;
		
		
		
		
		
		
		
		
		
		
		//getch();
		
		/*if (cpt[0]->state == Off)
		{
			printf("Work is over, thank you for using!\n");
			printf("Press any key to close\n");
			getchar();
			break;
		}*/
	}

}

