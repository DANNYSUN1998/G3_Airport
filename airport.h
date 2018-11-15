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

//��������
#define MaxCheckPtLine 6				//�������������鳤�����ֵ
#define TransPerSec 3					//ÿ����Ŷӻ��������밲����Ŷ���������
#define	MaxCheckPts 8					//����ڿ��������ֵ
#define E 2.71828						//��Ȼ����
//#define PI 3.1415926				//Բ����
#define Min_Efficiency 80 
#define Max_Efficiency 120 

//״̬����

//�Ŷӻ�����
#define Buf_Empty 0						//������Ϊ��
#define Buf_Full 1						//����������
#define Buf_NotFull 2					//������δ��
#define Buf_Closed 3					//�������رգ��°����󷢳����رջ�������
#define Buf_Straight 0					//������Ϊֱ����
#define Buf_Snake 1						//������Ϊ����

//�����	
#define Closed 0						//�ر�			
#define Working 1						//������
#define RestRequest 2					//��Ϣָ��õ���׼
#define RestDenied 3					//��Ϣָ��δ��׼
#define Resting 4						//��Ϣ��
#define OffApproved 5					//�����°�
#define Off 6							//�°�

//������Ŷ���
#define CheckPt_Empty 0					//������Ŷ���Ϊ��
#define CheckPt_Full 1					//������Ŷ�������
#define CheckPt_NotFull 2				//������Ŷ���δ��

//�����
#define Cmd_G 1							//�˿ͽ��밲���
#define Cmd_R 2							//����ڷ�����ͣ����
#define Cmd_C 3							//����ڷ����ָ�����
#define Cmd_Q 4							//����ڷ����°�����


//���������ļ����޸ĵ�����
typedef struct settings
{
	int MaxCustSingleLine;				//���������ȴ��˿���
	int MaxLines;						//���λ��������������
	int MaxSeqLen;						//�������ȴ�����(�˿��������Կ��ŵİ����������˱����Ƚϣ��жϰ�����Ƿ�����Ϣ��
	int MinTimeLen;						//��С���ΰ���ʱ��
	int MaxTimeLen;						//��󵥴ΰ���ʱ��
	int MinRestSec;						//�����Ϣʱ��
	int MaxRestSec;						//���Ϣʱ��
}Settings;
extern Settings * set;

//ָ��ṹ�嶨��
typedef struct Command
{
	int checkpt_num[30];					//ָ��ָ��İ���ڱ�ţ�����ָ�򰲼�ڣ���Ϊ0����
	int command[30];						//ָ�����
	int t;								//ָ���Ӧ��ʱ�䡣
}Cmd;
extern Cmd * CommandTxt;
extern Cmd * CommandCmd;
extern Cmd * CommandNIS;
extern Cmd * CommandBtn;
//�˿�_����
typedef struct guest
{
	PIMAGE face;						//���� 
	int num;							//���
	int bufin_t;						//����������ʱ���	
	int bufout_t;						//����������ʱ���
	int cptnum;							//��ǰ���İ�������
	int frd_count;						//���ڰ����ǰ������
	struct guest * next;
}Guest;
extern Guest * GlistH; 
extern Guest * CurG;
extern Guest * OutGListH;
extern Guest * CurOutG;
extern Guest * unfacedG;
extern Guest * PreOutGMark;
extern Guest * PreOutG; 
//�Ŷӻ�����_����
typedef struct bufferarea
{
	int shape;								//��������״
	int state;								//������״̬
	int Cur_Num;							//��ǰ�Ļ�����������
	int en;									//��ǰsec��������� 
	int out;								//��ǰsec�뿪������ 
}BufArea;
extern BufArea * bfa;

//�����_����
extern int RestList[MaxCheckPts];					//�ȴ���Ϣ�б�����
typedef struct checkpoint
{
	int state;								//��ǰ״̬
	int Sum_RestSec;						//����Ϣʱ��
	int Cur_RestSec;						//��ǰ��Ϣʱ��
	int Cur_CheckLen;						//��ǰ�˿Ͱ����ѻ���ʱ��
	int Sum_CheckLen;						//��ǰ�˿Ͱ������軨����ʱ��
	int req_rest;							//0Ϊ�����룬1Ϊ����ɹ���2Ϊ���뱻�ܾ��� 
	int req_con;							//0Ϊ�����룬1Ϊ����ָ� 
	int torest;
	int efficieny;          				//�����Ч�� 
}CheckPt;
extern CheckPt * cpt[MaxCheckPts];

//������Ŷ���_����
typedef struct checkpt_que
{
	int Id;									//ͨ�򰲼�ڵı��
	int	state;								//��ǰ״̬
	int PAmount;							//��Ӧ������Ŷ���������
	Guest * Queue[MaxCheckPtLine];			//�ڰ�����Ŷ����ĳ˿��б�
	int Change;								//����ڱ仯��
	int en;									//��ǰsec��������� 
	int out;								//��ǰsec�뿪������ 
}CheckPt_Que;
extern CheckPt_Que * cptq[MaxCheckPts];


//����ȫ�ֱ���
extern int TimeClock;						//ϵͳ����ʱ��
extern int CurCmd;							//��ǰ������
extern int threadkey;						//����������
extern int sumguest;						//����˿͵�����
extern int SumWaitLen;						//�˿��ڻ������ȴ�����ʱ��
extern FILE * input;						//�����ļ�ָ��
extern FILE * Output;						//��������ļ�ָ��
extern FILE * Outputdetail;				//��ϸ����ļ�ָ��
extern int txtin;
extern int nisin;
extern int mode;
extern int counttr;
extern int frame;
/*����������*/


/*ͨ�ù���*/
int AreaRand(int min, int max);		//���������
void InitAll();						//��ʼ������������ⲿ����
void ThreadLock();					//������

//��ȡ
void GetSet(Settings*);				//�������ļ��л�ȡ����
void InitCmd(Cmd * input);			//��ʼ��ָ��ṹ��
void GetCmd(Cmd* input, FILE * fp);					//��ȡ�ı�ָ��
void GetCmd_Win(Cmd* input);					//��ȡ������ָ��
void ProcessCmd(Cmd * Command);					//����ָ��
void CreatPassenger_NorDis(Cmd * input, int T);		//������ʱ�������̬�ֲ����ĳ˿�
int KbIn(Cmd* input);
//���
void OutPutWin();					//���������
void FOutPut(FILE * fp);						//�ļ����

//ά�������ļ� 
void UpdateSet(Settings *);					//���������ļ�


/*�����������*/
//�˿�
void CreateList();						//����һ���˿ͱ�
void New_Guest();						//����һ���˿�
void createface();						//������ 
Guest * findcust_bfa(int num);			//�ҵ��������ڵ��ض��˿� 
//�Ŷӻ�����
void InitBuf(BufArea * bfa);			//��ʼ���Ŷӻ�����
void Buf_Entry(BufArea * bfa);			//����������
int ShapeJudge(BufArea * bfa);		//�ж��Ŷӻ�������״
int Buff_Check(BufArea * bfa, Settings * set);				//�ж��Ŷӻ�����״̬

//�ɻ��������밲����Ŷ���s
void Transfer(BufArea * bfa, CheckPt_Que * cptq[], CheckPt * cpt[]);			//�˿����Ŷӻ��������밲����Ŷ���
int ToWhich(CheckPt_Que * cptq[], CheckPt * cpt[]);							//�жϳ˿�Ӧ�ý����ĸ������

//������Ŷ���
int InitQue(CheckPt_Que ** cptq);				//��ʼ��������Ŷ���
int Que_AllFull(CheckPt_Que ** cptq, CheckPt** cpt);			//�ж�����������Ŷ��Ƿ�����
int Que_StateJudge(CheckPt_Que * cptq);			//�жϵ��������������Ƿ�����

//�����
void Init_AllCheckPt(CheckPt ** cpt);			//��ʼ���������������
int Check(CheckPt * cpt[], CheckPt_Que * cptq[]);//�������
void OpenWin(CheckPt ** cpt, BufArea * bfa, Settings * set);			//���ڿ��Ű����
void CloseWin(CheckPt ** cpt, BufArea * bfa, Settings * set);		//���ڹرհ����
int Amt_OpenCpt(CheckPt ** cpt);					//����ͳ�Ƶ�ǰ�����İ��������,���ظ���
int OpenSingleCpt(CheckPt ** cpt);					//���ڿ���һ������ڵĺ���
int CloseSingleCpt(CheckPt ** cpt, CheckPt_Que ** cptq);					//���ڹر�һ�������
void CheckPtEffe(CheckPt ** cpt)	;
//�������Ϣ
int RestJudge(int checkpt_num, CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa);			//�жϵ�ǰ������Ƿ�������Ϣ����
int RestAvailable_Amount(CheckPt * cpt[], BufArea * bfa);				//�ж�������Ϣ�����İ��������
int RemoveFrList(int RestAvailable_Amount);	//������Ϣ���ڴӵȴ���Ϣ�б���ȥ��
int AddToList(CheckPt * cpt[], int CheckPt_ID, int count);				//��������Ϣ�Ĵ��ڼ���ȴ���Ϣ�б����ж������ͬʱ������Ϣ�����ں����⽫������Ϣ��˳��������ϣ�
int Rest(CheckPt ** cpt, int cpt_Id);								//��������ڽ�����Ϣ״̬
int RestAll(CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa, Settings * set);		//����Ϣ�����ϲ���
int RestAvailable(CheckPt ** cpt, BufArea * bfa, Settings * set, int cpt_num);		//�����ж�������Ϣ�İ�����Ƿ�õ���׼
int Rest_D2A(CheckPt ** cpt, BufArea * bfa, Settings * set);						//����ھܾ���Ϣ״̬ת��Ϊ��Ϣ����״̬
int BTWork(CheckPt ** cpt, int checkpt_num);									//�ص�����״̬

//�°�
int PreOver(CheckPt * cpt[], BufArea * bfa);		//�°�׼�������ڽ��ܵ�Qָ���
int WorkOver(CheckPt * cpt[]);						//�°�





#endif

