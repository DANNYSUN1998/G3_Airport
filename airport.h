#pragma once
#ifndef _AIRPORT_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
//#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdbool.h>
#include"graph.h"

//常量定义
#define MaxCheckPtLine 6				//单个安检口外队伍长度最大值
#define TransPerSec 3					//每秒从排队缓冲区进入安检口排队区的人数
#define	MaxCheckPts 8					//安检口开放数最大值
#define E 2.71828						//自然对数
//#define PI 3.1415926				//圆周率
#define Min_Efficiency 80 
#define Max_Efficiency 120 

//状态定义

//排队缓冲区
#define Buf_Empty 0						//缓冲区为空
#define Buf_Full 1						//缓冲区已满
#define Buf_NotFull 2					//缓冲区未满
#define Buf_Closed 3					//缓冲区关闭（下班请求发出后会关闭缓冲区）
#define Buf_Straight 0					//缓冲区为直线型
#define Buf_Snake 1						//缓冲区为蛇形

//安检口	
#define Closed 0						//关闭			
#define Working 1						//工作中
#define RestRequest 2					//休息指令得到批准
#define RestDenied 3					//休息指令未批准
#define Resting 4						//休息中
#define OffApproved 5					//请求下班
#define Off 6							//下班

//安检口排队区
#define CheckPt_Empty 0					//安检口排队区为空
#define CheckPt_Full 1					//安检口排队区已满
#define CheckPt_NotFull 2				//安检口排队区未满

//命令定义
#define Cmd_G 1							//乘客进入安检口
#define Cmd_R 2							//安检口发出暂停请求
#define Cmd_C 3							//安检口发出恢复请求
#define Cmd_Q 4							//安检口发出下班请求


//可在配置文件中修改的配置
typedef struct settings
{
	int MaxCustSingleLine;				//单队列最大等待乘客数
	int MaxLines;						//蛇形缓冲区的最大列数
	int MaxSeqLen;						//最大允许等待长度(乘客数量除以开放的安检口数量与此变量比较，判断安检口是否能休息）
	int MinTimeLen;						//最小单次安检时长
	int MaxTimeLen;						//最大单次安检时长
	int MinRestSec;						//最短休息时长
	int MaxRestSec;						//最长休息时长
}Settings;
extern Settings * set;

//指令，结构体定义
typedef struct Command
{
	int checkpt_num[30];					//指令指向的安检口编号（若无指向安检口，则为0）。
	int command[30];						//指令类别。
	int t;								//指令对应的时间。
}Cmd;
extern Cmd * CommandTxt;
extern Cmd * CommandCmd;
extern Cmd * CommandNIS;
extern Cmd * CommandBtn;
//顾客_定义
typedef struct guest
{
	PIMAGE face;						//长相 
	int num;							//编号
	int bufin_t;						//进缓冲区的时间点	
	int bufout_t;						//出缓冲区的时间点
	int cptnum;							//所前往的安检口序号
	int frd_count;						//所在安检口前方人数
	struct guest * next;
}Guest;
extern Guest * GlistH; 
extern Guest * CurG;
extern Guest * OutGListH;
extern Guest * CurOutG;
extern Guest * unfacedG;
extern Guest * PreOutGMark;
extern Guest * PreOutG; 
//排队缓冲区_定义
typedef struct bufferarea
{
	int shape;								//缓冲区形状
	int state;								//缓冲区状态
	int Cur_Num;							//当前的缓冲区总人数
	int en;									//当前sec进入的人数 
	int out;								//当前sec离开的人数 
}BufArea;
extern BufArea * bfa;

//安检口_定义
extern int RestList[MaxCheckPts];					//等待休息列表（有序）
typedef struct checkpoint
{
	int state;								//当前状态
	int Sum_RestSec;						//总休息时间
	int Cur_RestSec;						//当前休息时间
	int Cur_CheckLen;						//当前乘客安检已花费时间
	int Sum_CheckLen;						//当前乘客安检所需花费总时间
	int req_rest;							//0为无申请，1为申请成功，2为申请被拒绝。 
	int req_con;							//0为无申请，1为申请恢复 
	int torest;
	int efficieny;          				//安检口效率 
}CheckPt;
extern CheckPt * cpt[MaxCheckPts];

//安检口排队区_定义
typedef struct checkpt_que
{
	int Id;									//通向安检口的编号
	int	state;								//当前状态
	int PAmount;							//对应安检口排队区的人数
	Guest * Queue[MaxCheckPtLine];			//在安检口排队区的乘客列表
	int Change;								//安检口变化量
	int en;									//当前sec进入的人数 
	int out;								//当前sec离开的人数 
}CheckPt_Que;
extern CheckPt_Que * cptq[MaxCheckPts];


//常用全局变量
extern int TimeClock;						//系统运行时间
extern int CurCmd;							//当前的命令
extern int threadkey;						//进程锁开关
extern int sumguest;						//服务乘客的总量
extern int SumWaitLen;						//乘客在缓冲区等待的总时长
extern FILE * input;						//输入文件指针
extern FILE * Output;						//周期输出文件指针
extern FILE * Outputdetail;				//详细输出文件指针
extern int txtin;
extern int nisin;
extern int mode;
extern int counttr;
extern int frame;
/*函数声明区*/


/*通用功能*/
int AreaRand(int min, int max);		//生成随机数
void InitAll();						//初始化所有区域和外部变量
void ThreadLock();					//进程锁

//读取
void GetSet(Settings*);				//从配置文件中获取配置
void InitCmd(Cmd * input);			//初始化指令结构体
void GetCmd(Cmd* input, FILE * fp);					//获取文本指令
void GetCmd_Win(Cmd* input);					//读取命令行指令
void ProcessCmd(Cmd * Command);					//处理指令
void CreatPassenger_NorDis(Cmd * input, int T);		//产生随时间符合正态分布部的乘客
int KbIn(Cmd* input);
//输出
void OutPutWin();					//命令行输出
void FOutPut(FILE * fp);						//文件输出

//维护配置文件 
void UpdateSet(Settings *);					//更改配置文件


/*程序基本功能*/
//乘客
void CreateList();						//创建一个乘客表
void New_Guest();						//产生一个乘客
void createface();						//产生脸 
Guest * findcust_bfa(int num);			//找到缓冲区内的特定乘客 
//排队缓冲区
void InitBuf(BufArea * bfa);			//初始化排队缓冲区
void Buf_Entry(BufArea * bfa);			//缓冲区进人
int ShapeJudge(BufArea * bfa);		//判断排队缓冲区形状
int Buff_Check(BufArea * bfa, Settings * set);				//判断排队缓冲区状态

//由缓冲区进入安检口排队区s
void Transfer(BufArea * bfa, CheckPt_Que * cptq[], CheckPt * cpt[]);			//乘客由排队缓冲区进入安检口排队区
int ToWhich(CheckPt_Que * cptq[], CheckPt * cpt[]);							//判断乘客应该进入哪个安检口

//安检口排队区
int InitQue(CheckPt_Que ** cptq);				//初始化安检口排队区
int Que_AllFull(CheckPt_Que ** cptq, CheckPt** cpt);			//判断整个安检口排队是否已满
int Que_StateJudge(CheckPt_Que * cptq);			//判断单个安检口外队伍是否已满

//安检口
void Init_AllCheckPt(CheckPt ** cpt);			//初始化整个安检口区域
int Check(CheckPt * cpt[], CheckPt_Que * cptq[]);//安检过程
void OpenWin(CheckPt ** cpt, BufArea * bfa, Settings * set);			//用于开放安检口
void CloseWin(CheckPt ** cpt, BufArea * bfa, Settings * set);		//用于关闭安检口
int Amt_OpenCpt(CheckPt ** cpt);					//用于统计当前工作的安检口数量,返回个数
int OpenSingleCpt(CheckPt ** cpt);					//用于开启一个安检口的函数
int CloseSingleCpt(CheckPt ** cpt, CheckPt_Que ** cptq);					//用于关闭一个安检口
void CheckPtEffe(CheckPt ** cpt)	;
//安检口休息
int RestJudge(int checkpt_num, CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa);			//判断当前安检口是否满足休息条件
int RestAvailable_Amount(CheckPt * cpt[], BufArea * bfa);				//判断满足休息条件的安检口数量
int RemoveFrList(int RestAvailable_Amount);	//将已休息窗口从等待休息列表中去除
int AddToList(CheckPt * cpt[], int CheckPt_ID, int count);				//将申请休息的窗口加入等待休息列表（若有多个窗口同时申请休息，需在函数外将窗口休息的顺序排列完毕）
int Rest(CheckPt ** cpt, int cpt_Id);								//单个安检口进入休息状态
int RestAll(CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa, Settings * set);		//对休息的整合操作
int RestAvailable(CheckPt ** cpt, BufArea * bfa, Settings * set, int cpt_num);		//用于判断申请休息的安检口是否得到批准
int Rest_D2A(CheckPt ** cpt, BufArea * bfa, Settings * set);						//安检口拒绝休息状态转换为休息请求状态
int BTWork(CheckPt ** cpt, int checkpt_num);									//回到工作状态

//下班
int PreOver(CheckPt * cpt[], BufArea * bfa);		//下班准备（用于接受到Q指令后）
int WorkOver(CheckPt * cpt[]);						//下班





#endif

