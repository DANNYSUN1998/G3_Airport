#include"airport.h"

//产生一名新乘客
void New_Guest()
{
	Guest * new1;
	new1 = (Guest *)malloc(sizeof(Guest));
	if (new1 == NULL)
		exit(1);
	CurG->next = new1;

	//初始化乘客
	new1->next = NULL;
	new1->bufin_t = 0;
	new1->bufout_t = 0;
	new1->num = 0;
	new1->cptnum = -1;
	new1->frd_count = 99;

	CurG = new1;
}

//创建一个乘客表
void CreateList()
{
	Guest * new1;
	new1 = (Guest *)malloc(sizeof(Guest));
	if (new1 == NULL)
		exit(1);
	GlistH = new1;
	CurG = new1;
	CurOutG = new1;
	OutGListH = new1;
	unfacedG = new1;
	PreOutGMark = PreOutG = new1;
	//初始化乘客
	new1->next = NULL;
	new1->bufin_t = 0;
	new1->bufout_t = 0;
	new1->num = 0;
	new1->cptnum = -1;
	new1->frd_count = 99;
}

 
 //随机调用人脸 
int GetFaceList()
{
	int i = MaxFaceNum;
	
	for(i = 0;i<MaxFaceNum;i++)
	{
		FaceList[i] = newimage(160,160);
	}
	
	
	char Adrs[30] = {"imgs\\\\face\\\\000.png"};
	
	for(i = 0;i<MaxFaceNum;i++)
	{
		if(i<=8)
		{
			itoa(i+1,&Adrs[12+2],10);
		}
		if(i>8&&i<=98)
		{
			itoa(i+1,&Adrs[11+2],10);
		}
		if(i>=99)
		{
			itoa(i+1,&Adrs[10+2],10);
		}
		strcpy(&Adrs[13+2],".png");
		getimage(FaceList[i],Adrs);
	}
} 


PIMAGE RandomFace()
{
	return FaceList[AreaRand(0, MaxFaceNum)];
}


//生成脸
void createface()
{
	while(unfacedG->next != NULL)
	{
		unfacedG->next->face = newimage(60*6/set->MaxCustSingleLine,60*6/set->MaxCustSingleLine);
		putimage(unfacedG->next->face, 0,0,60*6/set->MaxCustSingleLine,60*6/set->MaxCustSingleLine,RandomFace(), 0,0,160,160);
		//getimage(unfacedG->next->face, "imgs\\乘客.png",60*6/set->MaxCustSingleLine,60*6/set->MaxCustSingleLine);
		unfacedG = unfacedG->next;
	}
 } 
 


