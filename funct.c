#include "airport.h"


//生成[min,max]范围的随机数
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

//从配置文件中获取配置数据
void GetSet(Settings * set)
{

	FILE * fp;
	char ch = 'a';
	int TmpNumber[20];
	int i = 0;														//计数器i，用于将读取的数字保存进临时数组
	if ((fp = fopen("Settings.txt", "r")) == NULL)					//打开配置文件
		exit(1);

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != ']')
			continue;
		fscanf(fp, "%d", TmpNumber + i);							//读取"]"符号后的数字
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

//更新配置文件
void UpdateSet(Settings * set)
{
	FILE * fp;
	int choice;
	char input[36];													//处理输入的数组
	if ((fp = fopen("Settings.txt", "w+")) == NULL)					//打开配置文件
		exit(1);
	printf("Update the settings file.\n");
	printf("MaxCustSingleLine: %4d     MaxLines: %4d\n", set->MaxCustSingleLine, set->MaxLines);
	printf("MaxSeqLen: %4d             MinTimeLen: %4d\n", set->MaxSeqLen, set->MinTimeLen);
	printf("MaxTimeLen: %4d            MinRestSec: %4d\n", set->MaxTimeLen, set->MinRestSec);
	printf("MaxRestSec: %4d\n", set->MaxRestSec);
	fprintf(fp, "[MaxCustSingleLine]");
	printf("MaxCustSingleLine（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')											//用字符串实现回车跳过
		fprintf(fp, "%d\n", atoi(input));							//将字符串中内容写入文件中
	//free(input);
	(fp, "[MaxLines]");
	printf("MaxLines（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxSeqLen]");
	printf("MaxSeqLen（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MinTimeLen]");
	printf("MinTimeLen（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxTimeLen]");
	printf("MaxTimeLen（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MinRestSec]");
	printf("MinRestSec（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);
	fprintf(fp, "[MaxRestSec]");
	printf("MaxRestSec（Press Enter to skip): \n");
	fgets(input, 36, stdin);
	if (input[0] != '\n')
		fprintf(fp, "%d\n", atoi(input));
	//free(input);

}

//读取指令文件
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

//初始化指令结构体
void InitCmd(Cmd * input)
{
	memset(input->command, -1, 30 * sizeof(int));
	memset(input->checkpt_num, -1, 30 * sizeof(int));
	input->t = 0;
}

//命令行输出
void OutPutWin()
{

	printf("t = %.3d\n", TimeClock);
	//平均等待时间
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

//初始化所有区域和外部变量
void InitAll()
{

	TimeClock = 1;
	counttr = 0;

	//读取默认配置，存入set
	int i = 0;

	set = (Settings*)malloc(sizeof(Settings));
	if (set == NULL)
		exit(1);
	GetSet(set);
	//初始化进程锁开关

	threadkey = 1;
	//初始化乘客数量和等待时间
	sumguest = 0;						
	SumWaitLen = 0;
	//初始化休息申请列表
	for (i = 0; i < MaxCheckPts; i++)
		RestList[i] = -1;
	//创建乘客链表
	CreateList();
	//为指令结构体开辟空间
	if ((input = fopen("input.txt", "r")) == NULL)					//打开指令文件
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
	//初始化各个区域
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

//处理指令
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
				fprintf(Outputdetail,"T=  %d,安检口已满，一名乘客离开\n", TimeClock);

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
				fprintf(Outputdetail, "T=%3ds,%d号安检口不满足休息条件，已驳回并加入申请列表。\n", TimeClock, Command->checkpt_num[i] + 1);
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

//读取命令行指令
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
		printf("输入说明：输入完成后请按回车键。\n\n");
		printf("命令注释：\nG：一名乘客进入\nRX：X号安检口请求休息（X为编号）\nCX：X号安检口从休息状态恢复（X为编号）\nQ：请求下班\n\n");
		printf("注意：请输入正确的指令，任何误输入都会被忽略；一秒的指令之间不需要加分隔符；请在一行内输入该秒所有指令。\n");
		printf("程序已暂停，请输入指令:");
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

//产生随时间符合正态分布部的乘客
void CreatPassenger_NorDis(Cmd * input, int T)//参数声明：input为指令集和，T为当前时间，用于产生随时间变化的乘客数量
{
	int passenger, i = 0;                            //passenger为当前时间产生的乘客数
	double NorDis;
	NorDis = pow(E, (-1)*(T - 75)*(T - 75) / 2 / 25 / 25) / sqrt(2 * PI) / 25;
	passenger = (int)ceil(NorDis * 1800);   //根据时间产生乘客数量          

	{
		input->command[i] = Cmd_G;
		input->checkpt_num[i] = -1;
	}
}

//文件周期输出
void FOutPut(FILE * fp)
{
	char ch, num[10] = { '\0' };
	int before = 0, monica = 1, i = 0;


	//打印时间
	fprintf(fp, "T=<%3d>\n", TimeClock);


	//打印机场安检状态
	if (cpt[0]->state == Closed)fprintf(fp, "OFFDUTY=Y\n");
	else fprintf(fp, "OFFDUTY=N\n");

	//平均等待时间
	if(sumguest != 0)
		fprintf(fp, "Average time of waiting:%.2f\n", (float)SumWaitLen / sumguest);
	else fprintf(fp,"Average time of waiting:0\n");
	//跑遍安检口
	for (i = 0; i < MaxCheckPts; i++)
	{
		//打印安检口状态
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


		//打印安检口已休息时间和计划休息时间
		if (cpt[i]->state == Resting)fprintf(fp, "RestLen=%d/%d,", cpt[i]->Cur_RestSec, cpt[i]->Sum_RestSec);
		else fprintf(fp, "0/0,");


		//打印安检口更新状态
		fprintf(fp, "WinListState=");
		if (cptq[i]->Change > 0)fprintf(fp, "CUSTADDIN  ,");
		else if (cptq[i]->Change == 0)fprintf(fp, "NOTCHANGED,");
		else fprintf(fp, "CUSTLEAVE  ,");


		//打印安检口人数
		fprintf(fp, "WinListCustCount=%d\n", cptq[i]->PAmount);
	}
	fprintf(fp, "ListLines=%d\n", bfa->Cur_Num / set->MaxCustSingleLine + 1);
	fprintf(fp, "ListCustCount=%d\n", bfa->Cur_Num);
	fprintf(fp, "\n");



	//初始化安检口排队区变化量
	for (int i = 0; i < MaxCheckPts; i++)
	{
		cptq[i]->Change = 0;
	}
}

//进程锁
void ThreadLock()
{
	while (!threadkey) {
		if (threadkey) break;
	}
}

