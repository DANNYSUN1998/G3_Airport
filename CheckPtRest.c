#include"airport.h"


//判断当前安检口是否满足休息条件
int RestJudge(int checkpt_num, CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa)
{	
	if (checkpt_num == -1)
		return 0;
	extern Settings* set;
	if (Amt_OpenCpt(cpt) != 0 &&  (bfa->Cur_Num / Amt_OpenCpt(cpt)) < set->MaxSeqLen && cptq[checkpt_num]->state == CheckPt_Empty )
		return 1;                           //满足休息条件返回1

	else
	{
		fprintf(Outputdetail,"T=  %d,窗口%d正在等待休息\n",TimeClock, checkpt_num + 1);
		return 0;                           //不满足休息条件返回0
	}
}


//用于判断当前条件下最大安检口休息量
int RestAvailable_Amount(CheckPt * cpt[], BufArea * bfa)
{
	int Rest_Amount = 0;             //最大休息量
	int AmountOfWorkingCheckPt = 0;  //用于计算正在运行的安检口的数量
	int i = 0;
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (cpt[i]->state == (Working || RestRequest || RestDenied || OffApproved))
			AmountOfWorkingCheckPt++;
	}
	Rest_Amount = AmountOfWorkingCheckPt - (int)(bfa->Cur_Num / set->MaxSeqLen);
	return Rest_Amount;
}

//用于判断申请休息的安检口是否得到批准
int RestAvailable(CheckPt ** cpt, BufArea * bfa, Settings * set, int cpt_num)
{
	//printf("bfa->Cur_Num / Amt_OpenCpt(cpt) = %d, set->MaxSeqLen = %d\n", bfa->Cur_Num / Amt_OpenCpt(cpt), set->MaxSeqLen);

	if (bfa->Cur_Num / Amt_OpenCpt(cpt) < set->MaxSeqLen)
		return 1;
	return 0;
}

//将已休息窗口从等待休息列表中去除
int RemoveFrList(int RestAvailable_Amount)
{
	int i = 0;
	int CheckPt_ToRest = 0;//队列中等待休息的安检口的数量
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (RestList[i] != -1)
			CheckPt_ToRest++;
	}

	if (CheckPt_ToRest <= RestAvailable_Amount)//等待休息的安检口数量小于当前状态下最大休息量
	{

		for (i = 0; i < MaxCheckPts; i++)
			RestList[i] = -1;
	}

	else if (CheckPt_ToRest > RestAvailable_Amount)//等待休息的安检口数量大于当前状态下最大休息量
	{
		for (i = 0; i < MaxCheckPts; i++)
		{
			if ((i+ RestAvailable_Amount >0) && (i + RestAvailable_Amount) < MaxCheckPts)
			{
				RestList[i] = RestList[i + RestAvailable_Amount];
			}
			else if (i + RestAvailable_Amount >= MaxCheckPts)
			{
				RestList[i] = -1;
			}
		}

	}

	return 1;            //去除成功，返回1   
}

//统计当前条件下申请休息但未被批准的安检口数量
int AmtOfCheckPt_ReqForRest(CheckPt ** CheckPts)
{
	int i = 0;
	int AmtOfCheckPt = 0;        //用于统计当前条件下申请休息但未被批准的安检口数量
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (CheckPts[i]->state == RestRequest)
			AmtOfCheckPt++;

	}
	return AmtOfCheckPt;          //返回统计结果
}

//同时申请休息的排队函数并加入排队队列
int AddToList(CheckPt * cpt[], int CheckPt_ID, int count)
{

	int i = 0;
	for (i = 0; RestList[i] != -1; i++)	printf("%d ", RestList[i]);
	int StartPt = i - count;

	RestList[i] = CheckPt_ID;

	if (count == 0)
		RestList[StartPt] = CheckPt_ID;
	else
		//qsort(RestList + StartPt, count, sizeof(int), AddToList);

	return 1;
}

//安检口拒绝休息状态转换为休息请求状态
int Rest_D2A(CheckPt ** cpt,BufArea * bfa,Settings * set)
{
	for (int i = 0; i < MaxCheckPts; i++)
		if (cpt[i]->state == RestDenied)	if (RestAvailable(cpt, bfa, set, i))	cpt[i]->state = RestRequest;
	return 0;
}
//单个安检口进入休息状态
int Rest(CheckPt ** cpt, int cpt_Id)
{
	cpt[cpt_Id]->state = Resting;
	cpt[cpt_Id]->Sum_RestSec = AreaRand(set->MinRestSec, set->MaxRestSec);
	fprintf(Outputdetail, "T=%3ds,安检口%d开始休息\n", TimeClock, cpt_Id + 1);
	cpt[cpt_Id]->torest = 1;

}

//对休息的整合操作
int RestAll(CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa, Settings * set)
{

	int ra_counter = RestAvailable_Amount(cpt, bfa);
	//printf("restavailable amount: %d\n", RestAvailable_Amount(cpt, bfa));
	RemoveFrList( ra_counter);
	/*for (int j = 0; j < 8; j++)
		printf("restlist[%d] : %d\n", j, RestList[j]);
	*/
	int i = 0;
	Rest_D2A(cpt, bfa, set);
	while (ra_counter > 0)								//休息命令发出的同一秒钟，若安检口满足休息条件且人数为0可直接休息。
	{
		if ((RestList[i] != -1)  && cptq[RestList[i]]->PAmount == 0)
		{
			Rest(cpt, RestList[i]);
		}
		i++;
		ra_counter--;
	}
	for (i = 0; i < MaxCheckPts; i++)				//休息命令发出后(非同一秒），若安检口满足休息条件且人数为0， 则进入休息状态。
	{
		if (cpt[i]->state == RestRequest && cptq[i]->PAmount == 0)
		{
			Rest(cpt, i);
		}
	}
	for (i = 0; i < MaxCheckPts; i++)				//对正在休息的安检口进行处理。
	{
		if (cpt[i]->state == Resting)
		{
			if (cpt[i]->Cur_RestSec < cpt[i]->Sum_RestSec)
				cpt[i]->Cur_RestSec++;
			else
				BTWork(cpt, i);
		}
	}
	return 1;
}

//回到工作状态
int BTWork(CheckPt ** cpt, int checkpt_num)
{
	cpt[checkpt_num]->Cur_RestSec = cpt[checkpt_num]->Sum_RestSec = 0;
	cpt[checkpt_num]->state = Working;
	cpt[checkpt_num]->req_con = 1;
	fprintf(Outputdetail, "T=%3ds,安检口%d恢复工作\n", TimeClock, checkpt_num + 1);

}
