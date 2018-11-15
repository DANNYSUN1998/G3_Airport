#include"airport.h"

//为安检口附效率值 
void CheckPtEffe(CheckPt ** cpt)
{
	int i;
	for(i=0;i<MaxCheckPts;i++)
	{
		cpt[i]->efficieny=AreaRand(Min_Efficiency, Max_Efficiency);
	}
}


//初始化整个安检口区域
void Init_AllCheckPt(CheckPt ** cpt)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		if (i < 4)
			cpt[i]->state = Working;
		else
			cpt[i]->state = Closed;
		cpt[i]->efficieny = 0;
		cpt[i]->Sum_CheckLen = 0;
		cpt[i]->Cur_CheckLen = 0;
		cpt[i]->Cur_RestSec = 0;
		cpt[i]->Sum_RestSec = 0;
		
	}
	CheckPtEffe(cpt);
}

//初始化安检口排队区
int InitQue(CheckPt_Que ** cptq)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < MaxCheckPts; i++)
	{
		cptq[i]->Id = i + 1;
		cptq[i]->PAmount = 0;
		cptq[i]->state = CheckPt_Empty;
		cptq[i]->Change = 0;
		for (j = 0; j < MaxCheckPtLine; j++)
			cptq[i]->Queue[j] = NULL;
	}
	return  1;//返回1表示初始化成功
}

//判断整个安检口是否已满
int Que_AllFull(CheckPt_Que ** cptq, CheckPt ** cpt)
{
	
	for (int i = 0; i < MaxCheckPts; i++)
	{
		if (Que_StateJudge(cptq[i]) != CheckPt_Full && ((cpt[i]->state == (Working || RestRequest)) || cpt[i]->state == OffApproved))
			return 0;
	}
	return 1;
}

//判断整个安检口是否为空
int Que_AllEmpty(CheckPt_Que ** cptq, CheckPt ** cpt)
{
	for (int i = 0; i < MaxCheckPts; i++)
		if (Que_StateJudge(cptq[i]) != CheckPt_Empty)
			return 0;
	return 1;
}

//判断单个安检口外队伍是否已满
int Que_StateJudge(CheckPt_Que * cptq)
{
		if (cptq->PAmount == MaxCheckPtLine)
		{
			cptq->state = CheckPt_Full;
			return CheckPt_Full;
		}

		else if (cptq->PAmount == 0)
		{
			cptq->state = CheckPt_Empty;
			return CheckPt_Empty;
		}
		else
		{
			cptq->state = CheckPt_NotFull;
			return CheckPt_NotFull;
		}
}

//安检过程
int Check(CheckPt * cpt[], CheckPt_Que * cptq[])
{
	int counter = 0;
	int i;


	for (counter = 0; counter < MaxCheckPts; counter++)
	{
		if (cpt[counter]->state ==  Working || cpt[counter]->state == OffApproved || cpt[counter]->state == RestRequest || cpt[counter]->state == RestDenied)
		{
			if (cpt[counter]->Sum_CheckLen == cpt[counter]->Cur_CheckLen && cpt[counter]->Sum_CheckLen != 0)
			{
				cpt[counter]->Sum_CheckLen = 0;
				cpt[counter]->Cur_CheckLen = 0;
				if (Que_StateJudge(cptq[counter]) != CheckPt_Empty)
				{
					cptq[counter]->PAmount--;
					cptq[counter]->Change--;
					fprintf(Outputdetail, "T=%3ds,%d号乘客完成安检，从安检口%d离开\n", TimeClock,cptq[counter]->Queue[0]->num, counter + 1);
					cptq[counter]->out++;
					for (i = 0; i < MaxCheckPtLine - 1; i++)
						cptq[counter]->Queue[i] = cptq[counter]->Queue[i + 1];
					cptq[counter]->Queue[MaxCheckPtLine - 1] = NULL;
				}
			}
			if (Que_StateJudge(cptq[counter]) != CheckPt_Empty && cpt[counter]->Sum_CheckLen == 0)
				cpt[counter]->Sum_CheckLen = AreaRand(set->MinTimeLen, set->MaxTimeLen);
			else if(Que_StateJudge(cptq[counter]) != CheckPt_Empty && cpt[counter]->Sum_CheckLen != 0)
				cpt[counter]->Cur_CheckLen++;
			if (cpt[counter]->Sum_CheckLen != 0 && cpt[counter]->Cur_CheckLen == 0 && Que_StateJudge(cptq[counter]) != CheckPt_Empty)
				cpt[counter]->Cur_CheckLen++;
		}
	}
	if (bfa->state == Buf_Closed && Que_AllEmpty(cptq, cpt))
		WorkOver(cpt);
	return 0;
}

//安检口下班准备
int PreOver(CheckPt * cpt[], BufArea * bfa)
{
	int i;
	bfa->state = Buf_Closed;				//先关闭排队缓冲区
	printf("%d\n", bfa->state);

	fprintf(Outputdetail, "T=%3ds,接纳区关闭\n", TimeClock);
	for (i = 0; i < MaxCheckPts; i++)
	{	
		if (cpt[i]->state != Resting)
			cpt[i]->state = OffApproved;
	}
	return 0;
}

//安检口下班
int WorkOver(CheckPt * cpt[])
{
	for (int i = 0; i < MaxCheckPts; i++)
	{
		cpt[i]->state = Off;

		fprintf(Outputdetail, "T=%3ds,从安检口%d关闭\n", TimeClock, i + 1);
	}
	fprintf(Outputdetail, "T=%3ds,安检区域关闭\n", TimeClock);
	return 0;
}

//用于及时增添工作状态安检口数量
void OpenWin(CheckPt** cpt, BufArea * bfa, Settings * set)
{
	int amount = 0;                                            //用于记录已通过此函数而被打开的安检口的数量
	if (bfa->Cur_Num >= 3 * Amt_OpenCpt(cpt))
	{
		while (bfa->Cur_Num >= 3 * Amt_OpenCpt(cpt) && Amt_OpenCpt(cpt) < 8)//排队缓冲区人数大于安检口开放量的3倍
		{
			if (OpenSingleCpt(cpt)) amount++;                                     //开放安检口
			else break;														//未打开安检口，直接弹出;                                                  
		}
	}
}

//用于减少工作状态安检口数量
void CloseWin(CheckPt ** cpt, BufArea * bfa, Settings * set)
{
	int amount = 0;                                            //用于记录已通过此函数而被关闭的安检口的数量
	if (bfa->Cur_Num <= 2 * Amt_OpenCpt(cpt))
	{
		while (bfa->Cur_Num <= 2 * Amt_OpenCpt(cpt) && Amt_OpenCpt(cpt) > 4)//排队缓冲区人数小于安检口开放量的2倍
		{
			if (CloseSingleCpt(cpt, cptq)) amount++;                                     //关闭安检口
			else break;														//未关闭安检口，直接弹出;                                                  
		}
	}
}
//用于统计当前工作的安检口数量,返回个数
int Amt_OpenCpt(CheckPt** cpt)
{
	int counter = 0, amount = 0;
	for (counter = 0; counter < MaxCheckPts; counter++)
	{
		if (cpt[counter]->state == (Working || RestRequest || RestDenied))
			amount++;
	}
	return amount;
}

//用于开启一个安检口的函数
int OpenSingleCpt(CheckPt** cpt)//返回值申明：如果成功打开一个安检口返回1，否则返回0
{
	int counter = 0;
	for (counter = 0; counter < MaxCheckPts; counter++)
		if (cpt[counter]->state == Closed)//遇到关闭状态的安检口
		{
			cpt[counter]->state = Working;
			fprintf(Outputdetail, "T=%3ds,从安检口%d开放\n", TimeClock, counter + 1);
			return 1;
		}
	return 0;
}

//用于关闭一个安检口
int CloseSingleCpt(CheckPt** cpt, CheckPt_Que ** cptq)//返回值申明：如果成功关闭一个安检口返回1，否则返回0
{
	int counter = 0;
	for (counter = 0; counter < MaxCheckPts; counter++)
		if (cpt[counter]->state == Working && cptq[counter]->PAmount == 0)//遇到开启状态的安检口
		{
			cpt[counter]->state = Closed;
			fprintf(Outputdetail, "T=%3ds,安检口%d关闭\n", TimeClock, counter + 1);
			return 1;
		}
	return 0;
}

