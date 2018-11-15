#include "airport.h"


//����[min,max]��Χ�������
int AreaRand(int min, int max)
{
	int output;
	
	randomize();
	if(max == min)
		return min;
	output = randomf() * (max - min) + min;
	
	/*
	srand((unsigned)(clock()));
	if (min == max)
		return min;
	output = rand() % (max - min) + min;
	*/
	return output;
}

//�������ļ��л�ȡ��������
void GetSet(Settings * set)
{

	FILE * fp;
	char ch = 'a';
	int TmpNumber[20];
	int i = 0;														//������i�����ڽ���ȡ�����ֱ������ʱ����
	if ((fp = fopen("Settings.txt", "r")) == NULL)					//�������ļ�
		exit(1);

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != ']')
			continue;
		fscanf(fp, "%d", TmpNumber + i);							//��ȡ"]"���ź������
		i++;
	}
	set->MaxCustSingleLine = TmpNumber[0];
	set->MaxLines = TmpNumber[1];
	set->MaxSeqLen = TmpNumber[2];
	set->MinTimeLen = TmpNumber[3];
	set->MaxTimeLen = TmpNumber[4];
	set->MinRestSec = TmpNumber[5];
	set->MaxRestSec = TmpNumber[6];
	fclose(fp);
}

//���������ļ�
void UpdateSet(Settings * set)
{
	FILE * fp;
	int choice;
	char input[36];													//�������������
	if ((fp = fopen("Settings.txt", "w+")) == NULL)					//�������ļ�
		exit(1);
	printf("Update the settings file.\n");
	printf("MaxCustSingleLine: %4d     MaxLines: %4d\n", set->MaxCustSingleLine, set->MaxLines);
	printf("MaxSeqLen: %4d             MinTimeLen: %4d\n", set->MaxSeqLen, set->MinTimeLen);
	printf("MaxTimeLen: %4d            MinRestSec: %4d\n", set->MaxTimeLen, set->MinRestSec);
	printf("MaxRestSec: %4d\n", set->MaxRestSec);
	fprintf(fp, "[MaxCustSingleLine]");
	printf("MaxCustSingleLine��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')											//���ַ���ʵ�ֻس�����
		fprintf(fp, "%d\n", atoi(input));							//���ַ���������д���ļ���
	//free(input);
	(fp, "[MaxLines]");
	printf("MaxLines��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxSeqLen]");
	printf("MaxSeqLen��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MinTimeLen]");
	printf("MinTimeLen��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxTimeLen]");
	printf("MaxTimeLen��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MinRestSec]");
	printf("MinRestSec��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxRestSec]");
	printf("MaxRestSec��Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);

}

//��ȡָ���ļ�
void GetCmd(Cmd* input, FILE * fp)
{
	char ch;
	char GetTime[100];
	char in[100];
	char num[100][30];
	memset(GetTime, '\0', 100 * sizeof(char));
	memset(in, '\0', 100 * sizeof(char));
	memset(num, '\0', 3000 * sizeof(char));
	int i = 0;
	int j = 0;
	while ((ch = fgetc(fp)) != '\n')
	{
		if (ch == 'T')
		{
			fgetc(fp);
			while ((ch = fgetc(fp)) != ',' && j<30)
			{
				GetTime[j] = ch;
				j++;
			}
		}
		if (ch == 'N')
		{
			fgetc(fp);
			fgetc(fp);
			while ((ch = fgetc(fp)) != '\n')
			{
				if (isalpha(ch))
					in[i] = ch;
				if (isdigit(ch))
					num[i][0] = ch;
				if (ch == '|')
					i++;
			}
			break;
		}
		
		
	}
	int k = i, l = j;
	while (i + 1)
	{
		switch (in[i])
		{
			case 'G':
			{
				input->command[i] = Cmd_G;
				input->checkpt_num[i] = -1;
				break;
			}
			case 'R':
			{
				input->command[i] = Cmd_R;
				input->checkpt_num[i] = atoi(num[i]) - 1;
				break;
			}
			case 'C':
			{
				input->command[i] = Cmd_C;
				input->checkpt_num[i] = atoi(num[i]) - 1;
				break;
			}
			case 'Q':
			{
				input->command[i] = Cmd_Q;
				input->checkpt_num[i] = -1;
				break;
			}
		}
		i--;	
	}
	input->t = atoi(GetTime);
	input->command[k + 1] = -1;
	
}

//��ʼ��ָ��ṹ��
void InitCmd(Cmd * input)
{
	memset(input->command, -1, 30 * sizeof(int));
	memset(input->checkpt_num, -1, 30 * sizeof(int));
	input->t = 0;
}

//���������
void OutPutWin()
{

	printf("t = %.3d\n", TimeClock);
	//ƽ���ȴ�ʱ��
	if(sumguest != 0)
		fprintf(stdout, "Average time of waiting:%.2f\n", (float)SumWaitLen / sumguest);
	else printf("Average time of waiting:0\n");
	for (int i = 0; i < MaxCheckPts; i++)
	{
		printf("Win%d: state = %d, RestLen = %d, WinListState = %d, WinListCustCount = %d\n", i + 1, cpt[i]->state, cpt[i]->Cur_RestSec, cptq[i]->state, cptq[i]->PAmount);
		printf("Cur_Checktime = %d, Sum_Checklen = %d, Cur_Resttime = %d, Sum_Resttime = %d\n", cpt[i]->Cur_CheckLen, cpt[i]->Sum_CheckLen, cpt[i]->Cur_RestSec, cpt[i]->Sum_RestSec);
	}
	printf("Buffer: Shape = %d, CustAmount = %d\n", bfa->shape, bfa->Cur_Num);
}

//��ʼ������������ⲿ����
void InitAll()
{

	TimeClock = 1;
	counttr = 0;

	//��ȡĬ�����ã�����set
	int i = 0;

	set = (Settings*)malloc(sizeof(Settings));
	if (set == NULL)
		exit(1);
	GetSet(set);
	//��ʼ������������

	threadkey = 1;
	//��ʼ���˿������͵ȴ�ʱ��
	sumguest = 0;						
	SumWaitLen = 0;
	//��ʼ����Ϣ�����б�
	for (i = 0; i < MaxCheckPts; i++)
		RestList[i] = -1;
	//�����˿�����
	CreateList();
	//Ϊָ��ṹ�忪�ٿռ�
	if ((input = fopen("input.txt", "r")) == NULL)					//��ָ���ļ�
		exit(1);
	if ((Output = fopen("Output.txt", "w+")) == NULL)
		exit(1);
	CommandBtn = (Cmd*)malloc(sizeof(Cmd));
	if(CommandBtn == NULL)
		exit(1); 
	CommandTxt = (Cmd*)malloc(sizeof(Cmd));
	if (CommandTxt == NULL)
		exit(1);
	CommandCmd = (Cmd*)malloc(sizeof(Cmd));
	if (CommandCmd == NULL)
		exit(1);
	CommandNIS = (Cmd*)malloc(sizeof(Cmd));
	if (CommandNIS == NULL)
		exit(1);
	InitCmd(CommandBtn);
	InitCmd(CommandCmd);
	InitCmd(CommandTxt);
	InitCmd(CommandNIS);
	GetCmd(CommandTxt, input);
	//��ʼ����������
	bfa = (BufArea*)malloc(sizeof(BufArea));
	if (bfa == NULL)
		exit(1);
	for (i = 0; i < MaxCheckPts; i++)
		cptq[i] = (CheckPt_Que*)malloc(sizeof(CheckPt_Que));
	if (cptq == NULL)
		exit(1);
	for (i = 0; i < MaxCheckPts; i++)
		cpt[i] = (CheckPt*)malloc(8 * sizeof(CheckPt));
	if (cpt == NULL)
		exit(1);
	InitBuf(bfa);
	InitQue(cptq);
	Init_AllCheckPt(cpt);
	
	

}

//����ָ��
void ProcessCmd(Cmd * Command)
{
	int R_Count = 0;
	int i = 0;
	while (Command->command[i] != -1 && Command->command[i] != -1)
	{
		CurCmd = Command->command[i];
		switch (CurCmd)
		{
		case Cmd_G:
		{
			Buff_Check(bfa,set);
			ShapeJudge(bfa);
			if (bfa->state != Buf_Full && bfa->state != Buf_Closed)
			{
				Buf_Entry(bfa);
				Buff_Check(bfa, set);
				ShapeJudge(bfa);
			}
			else
				fprintf(Outputdetail,"T=  %d,�����������һ���˿��뿪\n", TimeClock);

			break;
		}
		case Cmd_R:
		{
			if (cpt[Command->checkpt_num[i]]->state == Working && RestAvailable(cpt, bfa, set, Command->checkpt_num[i]))
			{
				R_Count++;
				cpt[Command->checkpt_num[i]]->state = RestRequest;
				cpt[Command->checkpt_num[i]]->req_rest = 1;
				AddToList(cpt, Command->checkpt_num[i], R_Count);

			}
			else
			{
				//printf("Check Point %d requested for rest but failed.\n", Command->checkpt_num[i] + 1);
				fprintf(Outputdetail, "T=%3ds,%d�Ű���ڲ�������Ϣ�������Ѳ��ز����������б�\n", TimeClock, Command->checkpt_num[i] + 1);
				cpt[Command->checkpt_num[i]]->req_rest = 2;
				cpt[Command->checkpt_num[i]]->state = RestDenied;
			}
			break;
		}
		case Cmd_C:
		{
			if (cpt[Command->checkpt_num[i]]->state == Resting)
				BTWork(cpt, Command->checkpt_num[i]);
			break;
		}

		case Cmd_Q:
		{
			PreOver(cpt, bfa);
			break;
		}

		}

		i++;


	}

}

//��ȡ������ָ��
void GetCmd_Win(Cmd* input)
{
	char pause;
	char ch[100];
	char in[100];
	char num[100];
	memset(ch, '\0', 100 * sizeof(char));
	memset(in, '\0', 100 * sizeof(char));
	memset(num, '\0', 100 * sizeof(char));
	int k = 0;
	while (!kbhit())
	{
		Sleep(1000);
		break;
	}
	if ((pause = getch()) == 'p' || pause == 'P')
	{
		threadkey = 0;
		printf("<T = %3d>\n", TimeClock);
		printf("����˵����������ɺ��밴�س�����\n\n");
		printf("����ע�ͣ�\nG��һ���˿ͽ���\nRX��X�Ű����������Ϣ��XΪ��ţ�\nCX��X�Ű���ڴ���Ϣ״̬�ָ���XΪ��ţ�\nQ�������°�\n\n");
		printf("ע�⣺��������ȷ��ָ��κ������붼�ᱻ���ԣ�һ���ָ��֮�䲻��Ҫ�ӷָ���������һ���������������ָ�\n");
		printf("��������ͣ��������ָ��:");
	}
	fgets(ch, 100, stdin);
	threadkey = 1;
	int index = 0;
	int i = 0;
	int j = 0;
	puts(ch);

	while (index < 100)
	{
		if (isalpha(ch[index]))
		{
			in[i] = ch[index];
			i++;
		}
		else if (isdigit(ch[index]))
		{
			num[j] = ch[index];
			j++;
			
		}
		index++;
	}




	i = 0;
	j = 0;
	while (in[i] != '\0')
	{
		switch (in[i])
		{
		case'G':
		{
			input->command[i] = Cmd_G;
			input->checkpt_num[i] = 0;
			break;
		}
		case'R':
		{
			input->command[i] = Cmd_R;
			input->checkpt_num[i] = (int)(num[j] - '0') - 1;
			j++;
			break;
		}
		case'C':
		{
			input->command[i] = Cmd_C;
			input->checkpt_num[i] = (int)(num[j] - '0') - 1;
			j++;
			break;
		}
		case'Q':
		{
			input->command[i] = Cmd_Q;
			input->checkpt_num[i] = 0;
			break;
		}
		}


		i++;

	}
	input->command[i] = -1;

}

//������ʱ�������̬�ֲ����ĳ˿�
void CreatPassenger_NorDis(Cmd * input, int T)//����������inputΪָ��ͣ�TΪ��ǰʱ�䣬���ڲ�����ʱ��仯�ĳ˿�����
{
	int passenger, i = 0;                            //passengerΪ��ǰʱ������ĳ˿���
	double NorDis;
	NorDis = pow(E, (-1)*(T - 75)*(T - 75) / 2 / 25 / 25) / sqrt(2 * PI) / 25;
	passenger = (int)ceil(NorDis * 1800);   //����ʱ������˿�����          

	{
		input->command[i] = Cmd_G;
		input->checkpt_num[i] = -1;
	}
}

//�ļ��������
void FOutPut(FILE * fp)
{
	char ch, num[10] = { '\0' };
	int before = 0, monica = 1, i = 0;


	//��ӡʱ��
	fprintf(fp, "T=<%3d>\n", TimeClock);


	//��ӡ��������״̬
	if (cpt[0]->state == Closed)fprintf(fp, "OFFDUTY=Y\n");
	else fprintf(fp, "OFFDUTY=N\n");

	//ƽ���ȴ�ʱ��
	if(sumguest != 0)
		fprintf(fp, "Average time of waiting:%.2f\n", (float)SumWaitLen / sumguest);
	else fprintf(fp,"Average time of waiting:0\n");
	//�ܱ鰲���
	for (i = 0; i < MaxCheckPts; i++)
	{
		//��ӡ�����״̬
		fprintf(fp, "WIN%d:State=", i + 1);
		switch (cpt[i]->state) {
		case Closed:fprintf(fp, "Closed,"); break;
		case Working:fprintf(fp, "Working,"); break;
		case RestRequest:fprintf(fp, "RestRequest,"); break;
		case RestDenied:fprintf(fp, "RestDenied,"); break;
		case Resting:fprintf(fp, "Resting,"); break;
		case OffApproved:fprintf(fp, "OffApproved,"); break;
		case Off:fprintf(fp, "Off,"); break;
		default:break;
		}


		//��ӡ���������Ϣʱ��ͼƻ���Ϣʱ��
		if (cpt[i]->state == Resting)fprintf(fp, "RestLen=%d/%d,", cpt[i]->Cur_RestSec, cpt[i]->Sum_RestSec);
		else fprintf(fp, "0/0,");


		//��ӡ����ڸ���״̬
		fprintf(fp, "WinListState=");
		if (cptq[i]->Change > 0)fprintf(fp, "CUSTADDIN  ,");
		else if (cptq[i]->Change == 0)fprintf(fp, "NOTCHANGED,");
		else fprintf(fp, "CUSTLEAVE  ,");


		//��ӡ���������
		fprintf(fp, "WinListCustCount=%d\n", cptq[i]->PAmount);
	}
	fprintf(fp, "ListLines=%d\n", bfa->Cur_Num / set->MaxCustSingleLine + 1);
	fprintf(fp, "ListCustCount=%d\n", bfa->Cur_Num);
	fprintf(fp, "\n");



	//��ʼ��������Ŷ����仯��
	for (int i = 0; i < MaxCheckPts; i++)
	{
		cptq[i]->Change = 0;
	}
}

//������
void ThreadLock()
{
	while (!threadkey) {
		if (threadkey) break;
	}
}

