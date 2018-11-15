#include"airport.h"

//Ϊ����ڸ�Ч��ֵ 
void CheckPtEffe(CheckPt ** cpt)
{
	int i;
	for(i=0;i<MaxCheckPts;i++)
	{
		cpt[i]->efficieny=AreaRand(Min_Efficiency, Max_Efficiency);
	}
}


//��ʼ���������������
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

//��ʼ��������Ŷ���
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
	return  1;//����1��ʾ��ʼ���ɹ�
}

//�ж�����������Ƿ�����
int Que_AllFull(CheckPt_Que ** cptq, CheckPt ** cpt)
{
	
	for (int i = 0; i < MaxCheckPts; i++)
	{
		if (Que_StateJudge(cptq[i]) != CheckPt_Full && ((cpt[i]->state == (Working || RestRequest)) || cpt[i]->state == OffApproved))
			return 0;
	}
	return 1;
}

//�ж�����������Ƿ�Ϊ��
int Que_AllEmpty(CheckPt_Que ** cptq, CheckPt ** cpt)
{
	for (int i = 0; i < MaxCheckPts; i++)
		if (Que_StateJudge(cptq[i]) != CheckPt_Empty)
			return 0;
	return 1;
}

//�жϵ��������������Ƿ�����
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

//�������
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
					fprintf(Outputdetail, "T=%3ds,%d�ų˿���ɰ��죬�Ӱ����%d�뿪\n", TimeClock,cptq[counter]->Queue[0]->num, counter + 1);
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

//������°�׼��
int PreOver(CheckPt * cpt[], BufArea * bfa)
{
	int i;
	bfa->state = Buf_Closed;				//�ȹر��Ŷӻ�����
	printf("%d\n", bfa->state);

	fprintf(Outputdetail, "T=%3ds,�������ر�\n", TimeClock);
	for (i = 0; i < MaxCheckPts; i++)
	{	
		if (cpt[i]->state != Resting)
			cpt[i]->state = OffApproved;
	}
	return 0;
}

//������°�
int WorkOver(CheckPt * cpt[])
{
	for (int i = 0; i < MaxCheckPts; i++)
	{
		cpt[i]->state = Off;

		fprintf(Outputdetail, "T=%3ds,�Ӱ����%d�ر�\n", TimeClock, i + 1);
	}
	fprintf(Outputdetail, "T=%3ds,��������ر�\n", TimeClock);
	return 0;
}

//���ڼ�ʱ������״̬���������
void OpenWin(CheckPt** cpt, BufArea * bfa, Settings * set)
{
	int amount = 0;                                            //���ڼ�¼��ͨ���˺��������򿪵İ���ڵ�����
	if (bfa->Cur_Num >= 3 * Amt_OpenCpt(cpt))
	{
		while (bfa->Cur_Num >= 3 * Amt_OpenCpt(cpt) && Amt_OpenCpt(cpt) < 8)//�Ŷӻ������������ڰ���ڿ�������3��
		{
			if (OpenSingleCpt(cpt)) amount++;                                     //���Ű����
			else break;														//δ�򿪰���ڣ�ֱ�ӵ���;                                                  
		}
	}
}

//���ڼ��ٹ���״̬���������
void CloseWin(CheckPt ** cpt, BufArea * bfa, Settings * set)
{
	int amount = 0;                                            //���ڼ�¼��ͨ���˺��������رյİ���ڵ�����
	if (bfa->Cur_Num <= 2 * Amt_OpenCpt(cpt))
	{
		while (bfa->Cur_Num <= 2 * Amt_OpenCpt(cpt) && Amt_OpenCpt(cpt) > 4)//�Ŷӻ���������С�ڰ���ڿ�������2��
		{
			if (CloseSingleCpt(cpt, cptq)) amount++;                                     //�رհ����
			else break;														//δ�رհ���ڣ�ֱ�ӵ���;                                                  
		}
	}
}
//����ͳ�Ƶ�ǰ�����İ��������,���ظ���
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

//���ڿ���һ������ڵĺ���
int OpenSingleCpt(CheckPt** cpt)//����ֵ����������ɹ���һ������ڷ���1�����򷵻�0
{
	int counter = 0;
	for (counter = 0; counter < MaxCheckPts; counter++)
		if (cpt[counter]->state == Closed)//�����ر�״̬�İ����
		{
			cpt[counter]->state = Working;
			fprintf(Outputdetail, "T=%3ds,�Ӱ����%d����\n", TimeClock, counter + 1);
			return 1;
		}
	return 0;
}

//���ڹر�һ�������
int CloseSingleCpt(CheckPt** cpt, CheckPt_Que ** cptq)//����ֵ����������ɹ��ر�һ������ڷ���1�����򷵻�0
{
	int counter = 0;
	for (counter = 0; counter < MaxCheckPts; counter++)
		if (cpt[counter]->state == Working && cptq[counter]->PAmount == 0)//��������״̬�İ����
		{
			cpt[counter]->state = Closed;
			fprintf(Outputdetail, "T=%3ds,�����%d�ر�\n", TimeClock, counter + 1);
			return 1;
		}
	return 0;
}

