#include"airport.h"

//初始化排队缓冲区
void InitBuf(BufArea * bfa)			
{
	bfa->shape = Buf_Straight;
	bfa->state = Buf_Empty;
	bfa->Cur_Num = 0;
}

//缓冲区进人
void Buf_Entry(BufArea * bfa)			
{

	sumguest++;
	New_Guest();
	CurG->num = sumguest;
	CurG->bufin_t = TimeClock;
	bfa->Cur_Num++;
	fprintf(Outputdetail, "T=%3ds,%d号旅客进入安检接纳区\n", TimeClock, CurG->num);
	bfa->en++;
}

//判断排队缓冲区状态
int Buff_Check(BufArea * bfa, Settings * set)				
{
	int max = set->MaxCustSingleLine*set->MaxLines;
	int n = bfa->Cur_Num;
	if (bfa->state == Buf_Closed)
		return 0;
	if (n < max&& n  >0)
	{
		bfa->state = Buf_NotFull;
		return Buf_NotFull;
	}
	else if (n == 0)
	{
		bfa->state = Buf_Empty;
		return Buf_Empty;
	}
	else if (n == max)
	{
		bfa->state = Buf_Full;
		//fprintf(Outputdetail, "t=  %ds,当前接纳区已满，可能会拒绝乘客进入。\n");
		return Buf_Full;
	}
	else return -1;
}

//判断排队缓冲区形状
int ShapeJudge(BufArea * bfa)		
{
	
	if (bfa->Cur_Num <= set->MaxCustSingleLine)
	{
		bfa->shape = Buf_Straight;
		return Buf_Straight;
	}
	if (bfa->Cur_Num > set->MaxCustSingleLine && bfa->Cur_Num <= set->MaxCustSingleLine*set->MaxLines)
	{
		bfa->shape = Buf_Snake;
		return Buf_Snake;
	}
	else return -1;
}

//判断乘客应该进入哪个安检口
int ToWhich(CheckPt_Que * cptq[], CheckPt * cpt[])
{
	int i = 0;
	int choice = 0;
	int tmpPAmount;
	while (i < MaxCheckPts)								//读取第一个开启的安检口编号以及人数
	{
		if (cpt[i]->state == Working ||cpt[i]->state == RestDenied ||cpt[i]->state == OffApproved && cptq[i]->state != CheckPt_Full)
		{
			tmpPAmount = cptq[i]->PAmount;
			choice = i;
			break;
		}
		i++;
	}
	while (i < MaxCheckPts)							//将各安检口外人数与临时变量比较，以找到人数最少的安检口。
	{
		if (cpt[i]->state != Working && cpt[i]->state != RestDenied && cpt[i]->state != OffApproved)
		{
			i++;
			continue;
		}
		if (cptq[i]->PAmount < tmpPAmount)
			choice = i;
		tmpPAmount = cptq[i]->PAmount;				//将当前安检口外队伍长度存入临时变量。
		i++;
	}
	//printf("%d is open\n", choice + 1);
	return choice;
}



int ToWhicheff(CheckPt_Que * cptq[], CheckPt * cpt[])//从效率角度判断乘客去哪个安检口 
{
	int i=0;
	int choice=0;
	int tmpeff,tmppA;
	while(i<MaxCheckPts)
	{
		if (cpt[i]->state == Working ||cpt[i]->state == RestDenied ||cpt[i]->state == OffApproved && cptq[i]->state != CheckPt_Full)
		{
			tmpeff = cpt[i]->efficieny;
			tmppA = cptq[i]->PAmount;
			choice = i;
			break;
		}
		i++;
	}
	while(i < MaxCheckPts)	
	{
		if (cpt[i]->state != Working && cpt[i]->state != RestDenied && cpt[i]->state != OffApproved)
		{
			i++;
			continue;
		}
		if (cptq[i]->PAmount < tmppA&&cptq[i]->PAmount!=6)
			choice = i;
		else if(cptq[i]->PAmount==tmppA&&cptq[i]->PAmount!=6)
		{
			if(cpt[i]->efficieny > tmpeff)
			{
				choice=i;
				tmpeff=cpt[i]->efficieny;
				tmppA=cptq[i]->PAmount;
			}
		}
		i++;
	}
	return choice;
}



//乘客从缓冲区进入安检口排队区
void Transfer(BufArea * bfa, CheckPt_Que * cptq[], CheckPt * cpt[])
{
	int counttrm;
	int nextisnull = 0;
	while (bfa->Cur_Num != 0 && !Que_AllFull(cptq, cpt))
	{
		counttr++;
		counttrm = counttr;
		bfa->Cur_Num--;
		ShapeJudge(bfa);
		int temp = ToWhicheff(cptq, cpt);
		cptq[temp]->PAmount++;
		cptq[temp]->Change++;
		
		if(!bfa->out)
			PreOutGMark = CurOutG;
		CurOutG = CurOutG->next;
		CurOutG->bufout_t = TimeClock;
		CurOutG->cptnum = temp;
		CurOutG->frd_count = cptq[temp]->PAmount - 1;
		cptq[temp]->Queue[cptq[temp]->PAmount - 1] = CurOutG;


		SumWaitLen += (CurOutG->bufout_t - CurOutG->bufin_t);

		fprintf(Outputdetail, "T=%3ds,%d号旅客进入安检口%d\n", TimeClock, CurOutG->num, temp + 1);
		bfa->out++;
		//fprintf(OutputChange, "t = %d, A passenge goes into checkpoint.\n", TimeClock);
	}
}


