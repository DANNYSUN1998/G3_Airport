#include"airport.h"


//�жϵ�ǰ������Ƿ�������Ϣ����
int RestJudge(int checkpt_num, CheckPt_Que ** cptq, CheckPt ** cpt, BufArea * bfa)
{	
	if (checkpt_num == -1)
		return 0;
	extern Settings* set;
	if (Amt_OpenCpt(cpt) != 0 &&  (bfa->Cur_Num / Amt_OpenCpt(cpt)) < set->MaxSeqLen && cptq[checkpt_num]->state == CheckPt_Empty )
		return 1;                           //������Ϣ��������1

	else
	{
		fprintf(Outputdetail,"T=  %d,����%d���ڵȴ���Ϣ\n",TimeClock, checkpt_num + 1);
		return 0;                           //��������Ϣ��������0
	}
}


//�����жϵ�ǰ��������󰲼����Ϣ��
int RestAvailable_Amount(CheckPt * cpt[], BufArea * bfa)
{
	int Rest_Amount = 0;             //�����Ϣ��
	int AmountOfWorkingCheckPt = 0;  //���ڼ����������еİ���ڵ�����
	int i = 0;
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (cpt[i]->state == (Working || RestRequest || RestDenied || OffApproved))
			AmountOfWorkingCheckPt++;
	}
	Rest_Amount = AmountOfWorkingCheckPt - (int)(bfa->Cur_Num / set->MaxSeqLen);
	return Rest_Amount;
}

//�����ж�������Ϣ�İ�����Ƿ�õ���׼
int RestAvailable(CheckPt ** cpt, BufArea * bfa, Settings * set, int cpt_num)
{
	//printf("bfa->Cur_Num / Amt_OpenCpt(cpt) = %d, set->MaxSeqLen = %d\n", bfa->Cur_Num / Amt_OpenCpt(cpt), set->MaxSeqLen);

	if (bfa->Cur_Num / Amt_OpenCpt(cpt) < set->MaxSeqLen)
		return 1;
	return 0;
}

//������Ϣ���ڴӵȴ���Ϣ�б���ȥ��
int RemoveFrList(int RestAvailable_Amount)
{
	int i = 0;
	int CheckPt_ToRest = 0;//�����еȴ���Ϣ�İ���ڵ�����
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (RestList[i] != -1)
			CheckPt_ToRest++;
	}

	if (CheckPt_ToRest <= RestAvailable_Amount)//�ȴ���Ϣ�İ��������С�ڵ�ǰ״̬�������Ϣ��
	{

		for (i = 0; i < MaxCheckPts; i++)
			RestList[i] = -1;
	}

	else if (CheckPt_ToRest > RestAvailable_Amount)//�ȴ���Ϣ�İ�����������ڵ�ǰ״̬�������Ϣ��
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

	return 1;            //ȥ���ɹ�������1   
}

//ͳ�Ƶ�ǰ������������Ϣ��δ����׼�İ��������
int AmtOfCheckPt_ReqForRest(CheckPt ** CheckPts)
{
	int i = 0;
	int AmtOfCheckPt = 0;        //����ͳ�Ƶ�ǰ������������Ϣ��δ����׼�İ��������
	for (i = 0; i < MaxCheckPts; i++)
	{
		if (CheckPts[i]->state == RestRequest)
			AmtOfCheckPt++;

	}
	return AmtOfCheckPt;          //����ͳ�ƽ��
}

//ͬʱ������Ϣ���ŶӺ����������ŶӶ���
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

//����ھܾ���Ϣ״̬ת��Ϊ��Ϣ����״̬
int Rest_D2A(CheckPt ** cpt,BufArea * bfa,Settings * set)
{
	for (int i = 0; i < MaxCheckPts; i++)
		if (cpt[i]->state == RestDenied)	if (RestAvailable(cpt, bfa, set, i))	cpt[i]->state = RestRequest;
	return 0;
}
//��������ڽ�����Ϣ״̬
int Rest(CheckPt ** cpt, int cpt_Id)
{
	cpt[cpt_Id]->state = Resting;
	cpt[cpt_Id]->Sum_RestSec = AreaRand(set->MinRestSec, set->MaxRestSec);
	fprintf(Outputdetail, "T=%3ds,�����%d��ʼ��Ϣ\n", TimeClock, cpt_Id + 1);
	cpt[cpt_Id]->torest = 1;

}

//����Ϣ�����ϲ���
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
	while (ra_counter > 0)								//��Ϣ�������ͬһ���ӣ��������������Ϣ����������Ϊ0��ֱ����Ϣ��
	{
		if ((RestList[i] != -1)  && cptq[RestList[i]]->PAmount == 0)
		{
			Rest(cpt, RestList[i]);
		}
		i++;
		ra_counter--;
	}
	for (i = 0; i < MaxCheckPts; i++)				//��Ϣ�������(��ͬһ�룩���������������Ϣ����������Ϊ0�� �������Ϣ״̬��
	{
		if (cpt[i]->state == RestRequest && cptq[i]->PAmount == 0)
		{
			Rest(cpt, i);
		}
	}
	for (i = 0; i < MaxCheckPts; i++)				//��������Ϣ�İ���ڽ��д���
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

//�ص�����״̬
int BTWork(CheckPt ** cpt, int checkpt_num)
{
	cpt[checkpt_num]->Cur_RestSec = cpt[checkpt_num]->Sum_RestSec = 0;
	cpt[checkpt_num]->state = Working;
	cpt[checkpt_num]->req_con = 1;
	fprintf(Outputdetail, "T=%3ds,�����%d�ָ�����\n", TimeClock, checkpt_num + 1);

}
