#include"airport.h"
#include"graph.h"

#define BubbleIni_x 1022
#define BubbleIni_y 72
#define BubbleW 75
#define BubbleH 57
#define CheckPtIni_x 952
#define CheckPtIni_y 50
#define CheckPtWout 70
#define CheckPtHout 70
#define CheckPtWin 60
#define CheckPtHin 60
#define Gap 3

	
void Checkegefps()//按帧读条 
{
	extern int frame; 
	int count;
	int i;
	float prearc;
	float curarc;
	
	for(count=0;count<MaxCheckPts;count++)
	{
		PIMAGE temp=newimage();
		PIMAGE tempdest = newimage();
		PIMAGE temppre=newimage();
		getimage(tempdest, 957, 57+count*73,60,60);
		if((cpt[count]->state==Working||cpt[count]->state==RestDenied||cpt[count]->state==RestRequest||cpt[count]->state==OffApproved)&&cptq[count]->PAmount!=0)
		{
			
			prearc=60*(cpt[count]->Cur_CheckLen-1)/cpt[count]->Sum_CheckLen + 60/cpt[count]->Sum_CheckLen*(frame-1)/60;
			curarc=60*(cpt[count]->Cur_CheckLen-1)/cpt[count]->Sum_CheckLen + 60/cpt[count]->Sum_CheckLen*(frame-1)/60 + 1 ;
			
			
			setfillcolor(EGERGB(0,153,68));
			bar(957 , 57+count*73 , 957 + prearc , 57 + 73 * count + 60);
			getimage(temppre , 957 , 57+count*73 , prearc ,60);
			putimage(957,57+73*count,tempdest,SRCCOPY);
			if(frame%cpt[count]->Sum_CheckLen==0)
			{
				setfillcolor(EGERGB(0,153,68));
				bar(957 + prearc , 57+count*73 , 957+curarc , 57 + 73 * count + 60);
				getimage(temp,957 + prearc , 57+count*73 , 1 , 60);
				putimage(957,57+73*count,tempdest,SRCCOPY);
				putimage_alphablend(NULL , temp , 957 + prearc , 57 + count * 73 , 100 , 0 , 0 , 0 , 0 );
			}
			putimage_alphablend(NULL , temppre ,957 , 57 + 73 * count , 100 , 0 , 0 , 0 , 0 );
		}
		
		
		else if(cpt[count]->state==Resting)
		{
			prearc=60*(cpt[count]->Cur_RestSec-1)/cpt[count]->Sum_RestSec + 60/cpt[count]->Sum_RestSec*(frame-1)/60;
			curarc=60*(cpt[count]->Cur_RestSec-1)/cpt[count]->Sum_RestSec + 60/cpt[count]->Sum_RestSec*(frame-1)/60 + 1 ;
			
			setfillcolor(EGERGB(51,122,230));
			bar(957 , 57+count*73 , 957 + prearc , 57 + 73 * count + 60);
			getimage(temppre , 957 , 57+count*73 , prearc ,60);
			putimage(957,57+73*count,tempdest,SRCCOPY);
			if(frame%cpt[count]->Sum_RestSec==0)
			{
				setfillcolor(EGERGB(0,153,68));
				bar(957 + prearc , 57+count*73 , 957+curarc , 57 + 73 * count + 60);
				getimage(temp,957 + prearc , 57+count*73 , 1 , 60);
				putimage(957,57+73*count,tempdest,SRCCOPY);
				putimage_alphablend(NULL , temp , 957 + prearc , 57 + count * 73 , 100 , 0 , 0 , 0 , 0 );
			}
			putimage_alphablend(NULL , temppre ,957 , 57 + 73 * count , 100 , 0 , 0 , 0 , 0 );
		}
		delimage(temp);
		delimage(tempdest);
		delimage(temppre);
	}
	//getch();
	
}
 

void Bubblefps()//冒泡逐帧刷新 
{ 
	int counter;
	float per=0;
	 extern int frame; 
	PIMAGE bubble=newimage(BubbleW,BubbleH);

	for(counter=0;counter<MaxCheckPts;counter++)
	{
		
		if(cpt[counter]->req_con)//恢复工作 
		{
			getimage(bubble,"imgs//开始工作.png",0,0);
			if(frame<20)//冒出 
			{ 
				per=(frame%20)/20.0;
				PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
				putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
				//delay_ms(1);
				//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
				delimage(bubbled);
			} 
			else if(frame>=40&&frame<60)//缩回 
			{
				per=(20-frame%20)/20.0;
				PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
				putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
				//delay_ms(1);
				//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
				delimage(bubbled);
			}
			else if(frame<40&frame>=20)//间隔 
			{
				PIMAGE bubbled=newimage();
				getimage(bubbled,"imgs//开始工作.png",0,0);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,0,0,0,0,0);
				delimage(bubbled);
			}
		}
	
		
		else if((cpt[counter]->req_rest==1||cpt[counter]->req_rest==2))//申请休息 
		{
			
			getimage(bubble,"imgs//申请休息.png",0,0);
			if(frame<20)
			{
				per=(frame%20)/20.0;
				//xyprintf(200,100+10*frame,"%f",per);
				//getch();
				PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
				putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
				//delay_ms(1);
				//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
				delimage(bubbled);
			}

			else if(frame>=20&&frame<40)
			{
				per=((frame%20))/20.0;
				if(cpt[counter]->req_rest==1)
				{
					getimage(bubble,"imgs//休息申请批准.png",0,0);
					
					{	
						PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
						putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
						//delay_ms(1);
						//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
						putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
						delimage(bubbled);
					} 
				}
				else if(cpt[counter]->req_rest==2)
				{
					getimage(bubble,"imgs//休息申请驳回.png",0,0);
					PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
					putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
					//delay_ms(1);
					//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
					putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
					delimage(bubbled);
				}
			}
			else if(frame>=40&&frame<60)
			{
				if(cpt[counter]->state==Resting) 
				{
					per=((frame%20))/20.0;
					getimage(bubble,"imgs//休息.png",0,0);
					PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
					putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
					putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
					delimage(bubbled);
					//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				}
				else if(cpt[counter]->req_rest==1)
				{
					per=((frame%20))/20.0;
					getimage(bubble,"imgs//休息排队.png",0,0);
					PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
					putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
					//delay_ms(1);
					//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
					putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);	
					delimage(bubbled);
					 
				}
				else if(cpt[counter]->req_rest==2)
				{
					per=(20-(frame%20))/20.0;
					getimage(bubble,"imgs//休息申请驳回.png",0,0);
					PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
					putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
					//delay_ms(1);
					//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
					putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
					delimage(bubbled);
					
				}
				
			
					
			}
		}
	
	
		else if(cpt[counter]->torest==1)//开始休息 
		{
			if(frame<20)//冒出 
			{
				per=(frame%20)/20.0;
				getimage(bubble,"imgs//休息.png",0,0);
				PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
				putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
				//delay_ms(1);
				//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
				delimage(bubbled);
			}
		
			else if(frame>=40&&frame<60)//缩回 
			{
				float per=(20-frame%20)/20.0;
				PIMAGE bubbled=newimage(BubbleW*per,BubbleH*per);
				putimage(bubbled,0,0,BubbleW*per,BubbleH*per,bubble,0,0,BubbleW,BubbleH,SRCCOPY);
				//Sleep(1);
				//putimage(BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,bkg[counter],SRCCOPY);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH*per,0,0,0,0,0);
				delimage(bubbled);
			}
			else if(frame<40&&frame>=20)//间隔 
			{
				PIMAGE bubbled=newimage();
				getimage(bubbled,"imgs//休息.png",0,0);
				putimage_transparent(NULL,bubbled,BubbleIni_x,BubbleIni_y+counter*(CheckPtHout+Gap)-BubbleH,0,0,0,0,0);
				delimage(bubbled);
			}
		}
		
	}
	delimage(bubble);
}
