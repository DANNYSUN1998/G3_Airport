#include "graph.h"
#include "airport.h"
 
int startwin()
{
		setinitmode(INIT_RENDERMANUAL );
		int choice;
		initgraph(1280, 720);
		setbkmode(TRANSPARENT);
		setbkcolor(EGERGBA(0,0,0,0));
		PIMAGE bk = newimage(1280,720);
		PIMAGE title1 = newimage();
		PIMAGE title2 = newimage();
		PIMAGE presskey = newimage();
		setcolor(WHITE);
		getimage(bk, "imgs\\背景.png");
		getimage(title1, "imgs\\G3 SECURITY CHECK SYSTEM.png");
		getimage(title2, "imgs\\BETA1.0.png");
		getimage(presskey, "imgs\\Press any key to start.png"); 
 		putimage(0,0,bk);
		
 		int apa = 0x00;
 		for(;apa < 0xff; delay_fps(60))
 		{
 			cleardevice();
 			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, apa); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, apa); 
 			putimage_alphatransparent(NULL, presskey, 440, 500, BLACK, apa);
 			apa += 5; 
 			if(kbhit()) break;
		}
		
		getch(); 
		for(;apa > 0x00; delay_fps(120))
		{	
			cleardevice();
			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 			putimage_alphatransparent(NULL, presskey, 440, 500, BLACK, apa);
 			apa -= 5;
		}
		delimage(presskey);
		
		//模式选择 
 		PIMAGE button1 = newimage();
 		PIMAGE button1_press = newimage();
 		getimage(button1, "imgs\\按钮1.png");
		getimage(button1_press, "imgs\\按钮1按下.png"); 
		apa = 0x00;
		setbkmode(TRANSPARENT);
		setcolor(WHITE);
		setfont(40, 0, "黑体"); 
		for(;apa < 0xff; delay_fps(120))
		{
			cleardevice();
			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 			putimage_alphablend(NULL, button1, 240, 400, apa);
 			outtextxy(266, 430, "开始安检"); 
 			putimage_alphablend(NULL, button1, 540, 400, apa);
 			outtextxy(566, 430, "维护配置"); 
 			putimage_alphablend(NULL, button1, 840, 400, apa);
 			outtextxy(866, 430, "退出程序");
 			apa+= 5;
 		}
 		
 		
 		//检测鼠标
		mouse_msg msg = {0}; 
 		for ( ; is_run(); delay_fps(60))
        {
                char str[32];
                //获取鼠标坐标，此函数不等待。若鼠标移出了窗口，那么坐标值不会更新
                //特殊情况是，你按着鼠标键不放，拖出窗口，这样坐标值会依然更新
                while (mousemsg())  msg = getmouse();
 
                //格式化输出为字符串，用于后面输出
                cleardevice();
				putimage(0,0,bk);
				putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 				putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
  				putimage_alphablend(NULL, button1, 240, 400, apa);
 				outtextxy(266, 430, "开始安检"); 
 				putimage_alphablend(NULL, button1, 540, 400, apa);
 				outtextxy(566, 430, "维护配置"); 
 				putimage_alphablend(NULL, button1, 840, 400, apa);
 				outtextxy(866, 430, "退出程序");
 				
                if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_down())
                {
                	putimage(240, 400, button1_press);
                	outtextxy(266, 430, "开始安检"); 
				}
				if(msg.x >= 540 && msg.x <= 540 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_down())
                {
                	putimage(540, 400, button1_press);
                	outtextxy(566, 430, "维护配置"); 
				}
				if(msg.x >= 840 && msg.x <= 840 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_down())
                {
                	putimage(840, 400, button1_press);
                	outtextxy(866, 430, "退出程序");
				}
				if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_up())
                {
					choice = 1;
					break;
				}
				if(msg.x >= 540 && msg.x <= 540 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_up())
                {
					choice = 2;
					break; 
				}
				if(msg.x >= 840 && msg.x <= 840 + 211 && msg.y >= 400 && msg.y <= 400 + 107 && msg.is_up())
                {
					choice = 3;
					break;
				}
        }
        apa = 0xff;
        for(;apa > 0x00; delay_fps(120))
		{
			cleardevice();
			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 			putimage_alphablend(NULL, button1, 240, 400, apa);
 			//outtextxy(266, 430, "开始安检"); 
 			putimage_alphablend(NULL, button1, 540, 400, apa);
 			//outtextxy(566, 430, "维护配置"); 
 			putimage_alphablend(NULL, button1, 840, 400, apa);
 			//outtextxy(866, 430, "退出程序");
 			apa-= 5;
 		}
 		cleardevice();
 		putimage(0,0,bk);
		putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 		putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 		delimage(button1);
 		delimage(title1);
 		delimage(title2);
 		delimage(bk);
 		return choice;
}

int cptq_graph()
{
	int i, j;

		
	int apa = 0xff / 60 * frame;
	
	for(i = 0; i < MaxCheckPts; i++)
	{
		for(j = 0; cptq[i]->Queue[j] != NULL; j++)
		{
			if(cptq[i]->Queue[j]->bufout_t == TimeClock)
			{
				if(j == 0)
					//putimage(924, 57 + i * 71, CurOutG->face);
					putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 957 + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame , 57 + i * 72 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, apa);
				else
					//putimage(918 - 64 * j - 1,  54 + i * 72, CurOutG->face);
					putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 951 - 60 * j + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame,  54 + i * 73 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, apa);
			
			}
			else
				if(j == 0)
					{
						if(!cptq[i]->out)
							putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 957 + (60 - 60 * 6 / set->MaxCustSingleLine)/2 , 57 + i * 72 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, 0xff);
						else
							putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 957 + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame , 57 + i * 72 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, 0xff);
					}
				else
				{
					if(!cptq[i]->out)
						putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 951 - 60 * j + (60 - 60 * 6 / set->MaxCustSingleLine)/2,  54 + i * 73 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, 0xff);
					else
						putimage_alphatransparent(NULL, cptq[i]->Queue[j]->face, 951 - 60 * j + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame,  54 + i * 73 + (60 - 60 * 6 / set->MaxCustSingleLine)/2, BLACK, 0xff);
				}
			

		}
	}
	
	
	


	
}

int inputmodeselect()
{
	PIMAGE bk = newimage(1280,720);
	PIMAGE title1 = newimage();
	PIMAGE title2 = newimage();
	PIMAGE presskey = newimage();
	PIMAGE w_choose = newimage();
	PIMAGE p_choose = newimage();
	PIMAGE button1 = newimage();
 	PIMAGE button1_press = newimage();
	
	setcolor(WHITE);
	getimage(bk, "imgs\\背景.png");
	getimage(title1, "imgs\\G3 SECURITY CHECK SYSTEM.png");
	getimage(title2, "imgs\\BETA1.0.png");
	getimage(presskey, "imgs\\Press any key to start.png"); 
	getimage(w_choose, "imgs\\待选择.png"); 
	getimage(p_choose, "imgs\\选择中.png"); 
 	getimage(button1, "imgs\\按钮1.png");
	getimage(button1_press, "imgs\\按钮1按下.png"); 
	
	
	int apa = 0x00;
	txtin = 0;
	nisin = 0;
	for(;apa < 0xff; delay_fps(120))
		{
			cleardevice();
			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 			putimage_alphablend(NULL, button1, 240, 300, apa);
 			outtextxy(266, 330, "文本输入"); 
 			putimage_alphablend(NULL, button1, 240, 450, apa);
 			outtextxy(266, 480, "正态分布"); 
 			putimage_alphablend(NULL, button1, 600, 375, apa);
 			outtextxy(666, 405, "继续"); 
 			putimage_alphatransparent(NULL, w_choose, 200, 345, BLACK, apa);
 			putimage_alphatransparent(NULL, w_choose, 200, 495, BLACK, apa);
 			
 			apa+= 5;
 		}
 				mouse_msg msg = {0}; 
 		for ( ; is_run(); delay_fps(60))
        {
                char str[32];

                //获取鼠标坐标，此函数不等待。若鼠标移出了窗口，那么坐标值不会更新
                //特殊情况是，你按着鼠标键不放，拖出窗口，这样坐标值会依然更新
				while (mousemsg())  msg = getmouse();
				
				cleardevice();
				putimage(0,0,bk);
				putimage_alphatransparent(NULL, title1, 200, 40, BLACK, 0xff); 
 				putimage_alphatransparent(NULL, title2, 800, 120, BLACK, 0xff); 
 				putimage_alphablend(NULL, button1, 240, 300, 0xff);
 				outtextxy(266, 330, "文本输入"); 
 				putimage_alphablend(NULL, button1, 240, 450, 0xff);
 				outtextxy(266, 480, "正态分布"); 
 				putimage_alphablend(NULL, button1, 600, 375, 0xff);
 				outtextxy(666, 405, "继续"); 
 				if(txtin)
 					putimage_alphatransparent(NULL, p_choose, 200, 345, BLACK, 0xff);
 				else
 					putimage_alphatransparent(NULL, w_choose, 200, 345, BLACK, 0xff);
				if(nisin)
					putimage_alphatransparent(NULL, p_choose, 200, 495, BLACK, 0xff);
				else
					putimage_alphatransparent(NULL, w_choose, 200, 495, BLACK, 0xff);
				if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 300 && msg.y <= 300 + 107 && msg.is_down())
				{
					putimage_alphatransparent(NULL, button1_press, 240, 300, BLACK, 0xff);
					outtextxy(266, 330, "文本输入"); 
				}
				if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 450 && msg.y <= 450 + 107 && msg.is_down())
                {
					putimage_alphatransparent(NULL, button1_press, 240, 450, BLACK, 0xff);
					outtextxy(266, 480, "正态分布"); 
				}
				if(msg.x >= 600 && msg.x <= 600 + 211 && msg.y >= 375 && msg.y <= 375 + 107 && msg.is_down())
				{
					putimage_alphablend(NULL, button1_press, 600, 375, apa);
 					outtextxy(666, 405, "继续"); 
				 } 
				if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 300 && msg.y <= 300 + 107 && msg.is_up())
				{
					if(!txtin) txtin = 1;
					else txtin = 0;
					msg = {0};
				}
				if(msg.x >= 240 && msg.x <= 240 + 211 && msg.y >= 450 && msg.y <= 450 + 107 && msg.is_up())
				{
					if(!nisin) nisin = 1;
					else nisin = 0;
					msg = {0};
				}
				if(msg.x >= 600 && msg.x <= 600 + 211 && msg.y >= 375 && msg.y <= 375 + 107 && msg.is_up())
 					break;
				
		}
		
		for(;apa > 0x00; delay_fps(120))
		{
			cleardevice();
			putimage(0,0,bk);
			putimage_alphatransparent(NULL, title1, 200, 40, BLACK, apa); 
 			putimage_alphatransparent(NULL, title2, 800, 120, BLACK, apa); 
 			putimage_alphablend(NULL, button1, 240, 300, apa);
 			//outtextxy(266, 330, "文本输入"); 
 			putimage_alphablend(NULL, button1, 240, 450, apa);
 			//outtextxy(266, 480, "正态分布"); 
 			putimage_alphablend(NULL, button1, 600, 375, apa);
 			//outtextxy(666, 405, "继续"); 
 			putimage_alphatransparent(NULL, p_choose, 200, 345, BLACK, apa);
 			putimage_alphatransparent(NULL, p_choose, 200, 495, BLACK, apa);
 			apa-= 5;	
 		}
 		cleardevice();
 		putimage(0,0,bk);
 		delimage(button1);
 		delimage(title1);
 		delimage(title2);
 		delimage(bk);
 		delimage(w_choose);
 		delimage(p_choose);
}

int CWIN()
{
		int choice1;
		choice1 = startwin();
		switch(choice1)
		{
			case 1:
			{
				inputmodeselect();
				cleardevice();
				PIMAGE bk = newimage(1280, 720);
				getimage(bk, "imgs\\背景_改.png");
				//Sleep(500);
				putimage(0,0,bk); 
				break;
			}
			case 2:
 			{
 				Modify_Settings();
 				inputmodeselect();
				cleardevice();
				PIMAGE bk = newimage(1280, 720);
				getimage(bk, "imgs\\背景_改.png");
				Sleep(500);
				putimage(0,0,bk); 
			}
			case 3:
			{
			 		exit(0);
			}
		}

        //closegraph();
        //return 0;
}

int DWIN()
{
	
	cptq_graph();
}

int bfa_out(int pamount)
{
	Guest * ptr = CurOutG;
	int psg = 1;         //用于 判断当前操作人在原队列中的位置
	PIMAGE temp;
	int org_x = 0,org_y = 0;//平移之前坐标 
	while(ptr!=NULL)
	{
		temp = ptr->face;
		get_org_pos(org_x,org_y,psg);//获取原先坐标 
		cleardevice(ptr->face);
		
		if((psg-1)%6==0&&(psg/6)%2==0)
		{
			ptr->face = temp;
			putimage(org_x+ Wid_Bufline,org_y,ptr->face);//向右平移一步 
		}
		 else if((psg-1)%6==0&&(psg/6)%2==1)
		 {
		 	ptr->face = temp;
		 	putimage(org_x+ Wid_Bufline ,org_y,ptr->face);//向右平移一步 
		 }
		 else if(psg%6==0&&(psg/6)%2==1)
		 {
		 	ptr->face = temp;
		 	putimage(org_x,org_y-Per_Move,ptr->face);     //向上平移一步 
		 }
		 else if(psg%6==0&&(psg/6)%2==0)
		 {
		 	ptr->face = temp;
		 	putimage(org_x,org_y+Per_Move,ptr->face);     //向下平移一步 
		 }
		 else
		 {
		 	ptr->face = temp;
		 	if((psg/6)%2==0)
		 	{
		 		putimage(org_x,org_y-Per_Move,ptr->face);//向上平移一步 
			}
			else
			{
				putimage(org_x,org_y+Per_Move,ptr->face);  //向下平移一步 
			}
		 }
		 psg++;
		 ptr = ptr->next;
	} 
}

int bfa_in(int pamount)
{

	int len;//用于判断下一个人所放的列数 
	if((pamount+1)%6==0)
		len = (pamount+1)/6;
	else 
		len = pamount/6; 
	if(pamount%6==0||(pamount+1)%6==1)
	{
		if(len%2==0)
			putimage(Exit_x - (pamount/6)*Wid_Bufline,Exit_y,CurG->face);
		else
			putimage(Exit_x - (pamount/6)*Wid_Bufline,Exit_y+5*Per_Move,CurG->face);	
	}
	else
	{
		if(len%2==0)
			putimage(Exit_x - (pamount/6)*Wid_Bufline,Exit_y + (pamount%6)*Per_Move,CurG->face);
		else
			putimage(Exit_x - (pamount/6)*Wid_Bufline,Exit_y + (5-pamount%6)*Per_Move,CurG->face);
					
				
	}
}

Guest * findcust_bfa(int num)
{
	Guest * cus = CurOutG;
	int i; 
	for(i = 0; i < num + 1; i++)
	{
		cus = cus->next;
		if(cus == CurG)
			return CurG;
	}
	return cus;
}

int bfa_image()
{
	int formerx = Exit_x;
	int formery = Exit_y;
	int num = bfa->Cur_Num;
	int apa;
	int i, j;
	int lines= bfa->Cur_Num / set->MaxCustSingleLine + 1;
	if(!(bfa->Cur_Num%6))
		lines--;
	putimage(50,50,BFAbkg);
	apa = 0xff * frame / 60;
	Guest * outcus = PreOutG;

	int outnum = 0;
	while(frame <= 20 && outcus != CurOutG)
	{
		
		outnum++;
		if(outnum%set->MaxCustSingleLine)
		{
			if((outnum / set->MaxCustSingleLine) % 2 == 0)	
				putimage_alphatransparent(NULL, outcus->next->face, formerx - (outnum / set->MaxCustSingleLine) * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 , formery + (outnum % set->MaxCustSingleLine - 1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff - 3 * apa );
			else 
				putimage_alphatransparent(NULL, outcus->next->face, formerx - (outnum / set->MaxCustSingleLine) * Wid_Bufline +  (60 - 60 * 6 / set->MaxCustSingleLine)/2, formery + (set->MaxCustSingleLine + outnum % set->MaxCustSingleLine - 6) * Per_Move * 6/ set->MaxCustSingleLine, BLACK, 0xff - 3 * apa);
		}
		else	
		{
			if((outnum / set->MaxCustSingleLine) % 2 != 0)
				putimage_alphatransparent(NULL, outcus->next->face, Exit_x - (outnum / set->MaxCustSingleLine - 1) * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine -1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff - 3 * apa);
			else
				putimage_alphatransparent(NULL, outcus->next->face, Exit_x - (outnum / set->MaxCustSingleLine - 1) * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y, BLACK, 0xff - 3 * apa);
		
		}				
		outcus = outcus->next;
	}
	
	
	if(bfa->out)
	{
	
	if(bfa->en)
	for(i = 0; i < lines; i++)
	{
		if(!num)
			break;
		if(i%2)
			for(j = 0; j < set->MaxCustSingleLine; j++)
			{
				if(findcust_bfa(i * set->MaxCustSingleLine + j)->bufin_t == TimeClock)
				{
					if(j == set->MaxCustSingleLine - 1)
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, apa);
					else
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine - 60 + frame, BLACK, apa);		
				}
				else
				{
					if(j == set->MaxCustSingleLine - 1)
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff);	
					else
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine - 60 + frame, BLACK, 0xff);	
				}
				
				num--;
				if(!num)
					break;
			}
		else
			for(j = 0; j < set->MaxCustSingleLine; j++)
			{
				if(findcust_bfa(i * set->MaxCustSingleLine + j)->bufin_t == TimeClock)
				{
				if(j == set->MaxCustSingleLine - 1)
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine, BLACK, apa);
				else
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine + 60 - frame, BLACK, apa);
				}
				else
				{
					if(j == set->MaxCustSingleLine - 1)
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff);
					else
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine + 60 - frame, BLACK, 0xff);

				}
				num--;
				if(!num)
					break;
			}
	
	}

	if(!bfa->en)
		
	for(i = 0; i < lines; i++)
	{
		if(!num)
			break;
		if(i%2)
			for(j = 0; j < set->MaxCustSingleLine; j++)
			{
				if(j == set->MaxCustSingleLine - 1)
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff);
				else
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine - 60 + frame, BLACK, 0xff);		
				num--;
				if(!num)
					break;
			}
		else
			for(j = 0; j < set->MaxCustSingleLine; j++)
			{
				if(j == set->MaxCustSingleLine - 1)
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine, BLACK, 0xff);
				else
					putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine + 60 - frame, BLACK, 0xff);
				num--;
				if(!num)
					break;
			}
	
	}
	
	}
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
	else
		for(i = 0; i < lines; i++)
		{
		if(i%2)
			for(j = 0; j < set->MaxCustSingleLine; j++)
			{
				if(findcust_bfa(i * set->MaxCustSingleLine + j)->bufin_t != TimeClock)
					putimage_transparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine, BLACK);

				else
					if(j == set->MaxCustSingleLine - 1)
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine, BLACK, apa);
					else
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (set->MaxCustSingleLine - j-1) * Per_Move *6 / set->MaxCustSingleLine - 60 + frame, BLACK, apa);	
				num--;
				if(!num)
				break;
			}
		else
			for(j = 0; j < set->MaxCustSingleLine; j++)	
			{
				if(findcust_bfa(i * set->MaxCustSingleLine + j)->bufin_t != TimeClock)
					putimage_transparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine, BLACK);

				else
					if(j == set->MaxCustSingleLine - 1)
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2 - 60 + frame, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine, BLACK, apa);
					else
						putimage_alphatransparent(NULL, findcust_bfa(i * set->MaxCustSingleLine + j)->face, Exit_x - i * Wid_Bufline + (60 - 60 * 6 / set->MaxCustSingleLine)/2, Exit_y + (j) * Per_Move *6 / set->MaxCustSingleLine + 60 - frame, BLACK, apa);
				num--;
				if(!num)
				break;
			}
			
		}

	
	
	
	/*
	
	while(en != 0 || out != 0) 
	{
		if(out != 0)
		{
			bfa_out(pamount_b);
			out--;
			pamount_b--;
		}		xyprintf(0,400,"%d",
		if(en != 0)
		{
			bfa_in(pamount_b);
			en--;
			pamount_b++;
		}

	}
	*/
	
}		
		
int get_org_pos(int org_x,int org_y,int psg)//用于获取原先坐标 
{
	
	if((psg-1)%6==0&&(psg/6)%2==0)
	{
		org_x = Exit_x - (psg/6) * Wid_Bufline; 
		org_y = Exit_y; 
		return 0;
	}
	else if((psg-1)%6==0&&(psg/6)%2==1)
	{
		org_x = Exit_x - (psg/6) * Wid_Bufline;
		org_y = Exit_y + 5 * Per_Move;
		return 0;
	}
	else if(psg%6==0&&(psg/6)%2==1)
	{
		org_x = Exit_x - (psg/6 - 1) * Wid_Bufline;
		org_y = Exit_y + 5 * Per_Move;
		return 0;
	}
	else if(psg%6==0&&(psg/6)%2==0)
	{
		org_x = Exit_x - (psg/6 - 1) * Wid_Bufline;
		org_y = Exit_y;
		return 0;
	}
	else
	{
		org_x = Exit_x - (psg/6) * Wid_Bufline;
		if((psg/6)%2==0)
			org_y = Exit_y + (psg%6-1) * Per_Move;
		else
			org_y = Exit_y + 5 * Per_Move - (psg%6 - 1) * Per_Move;
			
		return 0;
	}
}	

int SelectCmd() 
{
	
		if(MsgBoxNum < 10) return 0;
		if(MsgBoxNum == 11)
		{
			
			//putimage(1040, 87 + 0 * 72,CMD_R);
			if(cpt[0]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 0;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 12)
		{
			if(cpt[1]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 1;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 13)
		{
			if(cpt[2]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 2;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 14)
		{
			if(cpt[3]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 3;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 15)
		{
			if(cpt[4]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 4;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 16)
		{
			if(cpt[5]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 5;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 17)
		{
			if(cpt[6]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 6;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		if(MsgBoxNum == 18)
		{
			if(cpt[7]->state == Resting)
			CommandBtn->command[cmdnum] = Cmd_C;
			else
			CommandBtn->command[cmdnum] = Cmd_R;
			CommandBtn->checkpt_num[cmdnum] = 7;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}
		/* 
		if(msg.x >= 60 && msg.x <= 160 && msg.y >= 650 && msg.y <= 700 && msg.is_down())
		{
			putimage(60,650,G_pressed);
			outtextxy(110,675,"G");
		}*/ 
		if(MsgBoxNum == 19)
		{
			CommandBtn->command[cmdnum] = Cmd_G;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		} 
		/* 
		if(msg.x >= 180 && msg.x <= 280 && msg.y >= 650 && msg.y <= 700 && msg.is_down())
		{
			putimage(180,650,Q_pressed);
			outtextxy(230,675,"Q");
		} */ 
		if(MsgBoxNum == 20)
		{
			CommandBtn->command[cmdnum] = Cmd_Q;
			cmdnum++;
			MsgBoxNum = 0;
			return 0;
		}	
		

	

	

}

int Modify_Settings()
{
 PIMAGE pimg = newimage(1280,720);
 getimage(pimg,"imgs//配置文件.png");
 putimage(0,0,pimg);
  
 setcolor(BLACK);
 setfontbkcolor(BLACK); 
 setfont(25, 0, "宋体");
 mouse_msg msg = {0};
 
 int k = 0;
 for ( ; is_run(); delay_fps(60))
 {
  if(k==0) 
  {
   while (mousemsg())  msg = getmouse();
  
  
   cleardevice();
   putimage(0,0,pimg);
   xyprintf(270,271+40,"%d",set->MaxCustSingleLine);
   xyprintf(640,271+40,"%d",set->MaxLines);
   xyprintf(1280-150-120,271+40,"%d",set->MaxSeqLen);
   xyprintf(360,475,"%d",set->MaxTimeLen);
   xyprintf(1280-360,475,"%d",set->MinTimeLen);
   xyprintf(360,599+40,"%d",set->MaxRestSec);
   xyprintf(1280-360,599+40,"%d",set->MinRestSec);
  
  
  
 
  
   if(msg.x >= 150 && msg.x <= 150 + 47 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up())
   {
    if(set->MaxCustSingleLine-1>=0)
    {
     set->MaxCustSingleLine--;
     Modify_SetFile();
     xyprintf(270,271+40,"%d",set->MaxCustSingleLine);
    }
    else
     k = 1;//xyprintf(270,271+40,"%d已达最小值",set->MaxCustSingleLine);
    msg = {0};
   } 
   if(msg.x >= 150+240-47 && msg.x <= 150 + 240 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up()) 
   {
    if(set->MaxCustSingleLine+1<=10)
    {
     set->MaxCustSingleLine++;
     Modify_SetFile();
     xyprintf(640,271+40,"%d",set->MaxCustSingleLine);
    }
    else
     k = 2;//xyprintf(640,271+40,"%d已达最大值",set->MaxCustSingleLine);
    msg = {0}; 
   }
   if(msg.x >= 520 && msg.x <= 520 + 47 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up())
   {
    if(set->MaxLines-1>0)
    {
     set->MaxLines--;
     Modify_SetFile();
     xyprintf(640,271+40,"%d",set->MaxLines);
    } 
    else
     k = 1;//xyprintf(640,271+40,"%d已达最小值",set->MaxLines);
    msg = {0}; 
   } 
   if(msg.x >= 520+240-47 && msg.x <= 520 + 240 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up()) 
   {
    if(set->MaxLines+1<=6)
    {
     set->MaxLines++;
     Modify_SetFile();
     xyprintf(640,271+40,"%d",set->MaxLines);
    } 
    else
     k = 2;//xyprintf(640,271+40,"%d已达最大值",set->MaxLines);
    msg = {0};
   }
   if(msg.x >= 1280-150-240 && msg.x <= 1280-150-240+47 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up()) 
   {
    if(set->MaxSeqLen-1>0)
    {
     set->MaxSeqLen--;
     Modify_SetFile();
     xyprintf(1280-150-120,271+40,"%d",set->MaxSeqLen);
    } 
    else
     k = 1;//xyprintf(1280-150-120,271+40,"%d已达最小值",set->MaxSeqLen);
    msg = {0}; 
   }
   if(msg.x >= 1280-150-47 && msg.x <= 1280-150 && msg.y >= 271 && msg.y <= 271 + 80 && msg.is_up()) 
   {
    if(set->MaxSeqLen+1<=10)
    {
     set->MaxSeqLen++;
     Modify_SetFile();
     xyprintf(1280-150-120,271+40,"%d",set->MaxSeqLen);
    } 
    else
     k = 2;//xyprintf(1280-150-120,271+40,"%d已达最大值",set->MaxSeqLen);
    msg = {0}; 
   }
   if(msg.x >= 240 && msg.x <= 240+47 && msg.y >= 435 && msg.y <= 435+80 && msg.is_up()) 
   {
    if(set->MaxTimeLen-1 > set->MinTimeLen)
    {
     set->MaxTimeLen--;
     Modify_SetFile();
     xyprintf(360,475,"%d",set->MaxTimeLen);
    }
    else
     k = 3;//xyprintf(360,475,"%d已达边界值",set->MaxTimeLen);
    msg = {0}; 
   } 
   if(msg.x >= 240+240-47 && msg.x <= 240+240 && msg.y >= 435 && msg.y <= 435+80 && msg.is_up()) 
   {
    if(set->MaxTimeLen+1<=10)
    {
     set->MaxTimeLen++;
     Modify_SetFile();
     xyprintf(360,475,"%d",set->MaxTimeLen);
    }
    else
     k = 2;//xyprintf(360,475,"%d已达最大值",set->MaxTimeLen);
    msg = {0}; 
   } 
   if(msg.x >= 1280-240-240 && msg.x <= 1280-240-240+47 && msg.y >= 435 && msg.y <= 435+80 && msg.is_up())
   {
    if(set->MinTimeLen-1>0)
    {
     set->MinTimeLen--;
     Modify_SetFile();
     xyprintf(1280-360,475,"%d",set->MinTimeLen);
    }
    else
     k = 1;//xyprintf(1280-360,475,"%d已达最小值",set->MinTimeLen);
    msg = {0}; 
   }
   if(msg.x >= 1280-240-47 && msg.x <= 1280-240 && msg.y >= 435 && msg.y <= 435+80 && msg.is_up())
   {
    if(set->MinTimeLen+1 < set->MaxTimeLen)
    {
     set->MinTimeLen++;
     Modify_SetFile();
     xyprintf(1280-360,475,"%d",set->MinTimeLen);
    }
    else
     k = 3;//xyprintf(1280-360,475,"%d已达边界值",set->MinTimeLen);
    msg = {0}; 
   }
   if(msg.x >= 240 && msg.x <= 240+47 && msg.y >= 599 && msg.y <= 599+80 && msg.is_up())
   {
    if(set->MaxRestSec-1 > set->MinRestSec)
    {
     set->MaxRestSec--;
     Modify_SetFile();
     xyprintf(360,599+40,"%d",set->MaxRestSec);
    }
    else
     k = 3;//xyprintf(360,599+40,"%d已达边界值",set->MaxRestSec);
    msg = {0};
   } 
   if(msg.x >= 240+240-47 && msg.x <= 240+240 && msg.y >= 599 && msg.y <= 599+80 && msg.is_up())
   {
    if(set->MaxRestSec+1 <= 60)
    {
     set->MaxRestSec++;
     Modify_SetFile();
     xyprintf(360,599+40,"%d",set->MaxRestSec);
    }
    else
     k = 2;//xyprintf(360,599+40,"%d已达最大值",set->MaxRestSec);
    msg = {0}; 
   }
   if(msg.x >= 1280-240-240 && msg.x <= 1280-240-240+47 && msg.y >= 599 && msg.y <= 599+80 && msg.is_up())
   {
    if(set->MinRestSec-1>0)
    {
     set->MinRestSec--;
     Modify_SetFile();
     xyprintf(1280-360,599+40,"%d",set->MinRestSec);
    }
    else
     k = 1;//xyprintf(1280-360,599+40,"%d已达最小值",set->MinRestSec);
    msg = {0}; 
   } 
   if(msg.x >= 1280-240-47 && msg.x <= 1280-240 && msg.y >= 599 && msg.y <= 599+80 && msg.is_up())
   {
    if(set->MinRestSec+1<set->MaxRestSec)
    {
     set->MinRestSec++;
     Modify_SetFile();
     xyprintf(1280-360,599+40,"%d",set->MinRestSec);
    }
    else
     k = 3;//xyprintf(1280-360,599+40,"%d已达边界值",set->MinRestSec);
    msg = {0}; 
   }
   if(msg.x >= 1173 && msg.x <= 1280 && msg.y >= 640 && msg.y <= 720 && msg.is_up()) 
   {
    msg = {0};
    break;
   }
 }
  else
 {
  cleardevice();
  putimage(0,0,pimg);
  xyprintf(270,271+40,"%d",set->MaxCustSingleLine);
  xyprintf(640,271+40,"%d",set->MaxLines);
  xyprintf(1280-150-120,271+40,"%d",set->MaxSeqLen);
  xyprintf(360,475,"%d",set->MaxTimeLen);
  xyprintf(1280-360,475,"%d",set->MinTimeLen);
  xyprintf(360,599+40,"%d",set->MaxRestSec);
  xyprintf(1280-360,599+40,"%d",set->MinRestSec);
  
   if(k==1)
   xyprintf(580,500,"已达到最小值");
  if(k==2)
   xyprintf(580,500,"已达到最大值");
  if(k==3)
   xyprintf(580,500,"已达到束缚边界");  
   
   while (mousemsg())  msg = getmouse();
   
   if(msg.is_down())
    k = 0; 
}
 }
 
 cleardevice();
  putimage(0,0,pimg);
 xyprintf(470,500,"配置过程结束，按任意键退出！"); 
 getch();
 return 0; 
} 

void Modify_SetFile()
{
	
	FILE * fptr = fopen("Settings.txt","r+");
	fprintf(fptr,"[MaxCustSingleLine]%d\n",set->MaxCustSingleLine);
	fprintf(fptr,"[MaxLines]%d\n",set->MaxLines);
	fprintf(fptr,"[MaxSeqLen]%d\n",set->MaxSeqLen);
	fprintf(fptr,"[MinTimeLen]%d\n",set->MinTimeLen);
	fprintf(fptr,"[MaxTimeLen]%d\n",set->MaxTimeLen);
	fprintf(fptr,"[MinRestSec]%d\n",set->MinRestSec);
	fprintf(fptr,"[MaxRestSec]%d\n",set->MaxRestSec);
	
	
	fclose(fptr);
	fptr = NULL;
	
	
}

int KbIn(Cmd* input)
{
	char c;
	char in[100];
	for(int k = 0; k < 100 ;k++)
		in[k] = '\0';
	char ch[100];
	int num[100];
	int i = 0;
	int index = 0; 
	int j = 0;
	xyprintf(615,650,"按下P键进入键盘输入模式。");
	if(kbhit()) c = getch();
	if(c != 'p' && c != 'P') return 0 ;
	PIMAGE grey = newimage(1280, 720); 
	PIMAGE black = newimage(1280, 300); 
	bar(0,0,1280,720, grey);
	bar(0,0,1280,300, black); 
	putimage_alphablend(NULL, grey, 0, 0, 0x7f);
	putimage_alphablend(NULL, black, 0, 210, 0xff);
	setcolor(WHITE);
	xyprintf(500, 220, "请输入指令"); 
	setfont(20,0,"黑体"); 
	xyprintf(0, 300, "提示：输入G进入乘客，RX休息安检口，CX恢复安检口，Q请求下班（回车结束，无需空隔）。"); 
	Sleep(100);
	while(!kbhit()); 
	while(1)
	{
		in[i] = getch();
		if(in[i] == '\r')
			break;
		in[i + 1] = '\0';
		if(i >= i && in[i] == '\b')
		{
			in[i - 1] = in[i] = '\0';
			i -= 2;
		}	
		putimage_alphablend(NULL, black, 0, 210, 0xff);
		setfont(40, 0, "黑体");
		xyprintf(500, 220, "请输入指令");
		setfont(20,0,"黑体");  
		xyprintf(0, 300, "提示：输入G进入乘客，RX休息安检口，CX恢复安检口，Q请求下班（回车结束，无需空隔）。"); 
		xyprintf(200, 360, "%s", in);
		i++;
	}
	for(i = 0; in[i] != '\0' && i<100; i++)
		if(in[i] != 'G' && in[i] != 'R' && in[i] != 'C' && in[i] != 'Q' && !isdigit(in[i]) && in[i] != '\r')
		{
			xyprintf(200, 480, "%s", in);
			xyprintf(600, 420, "输入有误！");
			Sleep(2000);
			return 0; 
		}
	i = 0;	

	while (index < 100)
	{
		if (isalpha(in[index]))
		{
			ch[i] = in[index];
			i++;
		}
		else if (isdigit(in[index]))
		{
			num[j] = in[index];
			j++;
			
		}
		index++;
	}




	i = 0;
	j = 0;
	while (ch[i] != '\0')
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


int getMsgBoxNum()
{
	mouse_msg msg = {0};	
		
//			
		while (mousemsg())  msg = getmouse();		
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51 && msg.y <= 51+70)
		{	
			MsgBoxNum = 1;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3 && msg.y <= 51+70+3+70)	
		{
			MsgBoxNum = 2;
			msg = {0};
			return 0;
		}
		
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3 && msg.y <= 51+70+3+70+3+70)
		{
			MsgBoxNum = 3;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70)
		{
			MsgBoxNum = 4;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70+3+70)
		{
			MsgBoxNum = 5;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70+3+70+3+70)
		{
			MsgBoxNum = 6;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3+70+3 && msg.y <=51+70+3+70+3+70+3+70+3+70+3+70+3+70)
		{
			MsgBoxNum = 7;
			msg = {0};
			return 0;
		}
		if(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3+70+3+70+3 && msg.y <=51+70+3+70+3+70+3+70+3+70+3+70+3+70+3+70)
		{
			MsgBoxNum = 8;
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 0 && msg.y <= 122 + 72 * 0 && msg.is_down() && cpt[0]->state != RestRequest && cpt[0]->state != RestDenied)
		{
			MsgBoxNum = 11; 
			msg = {0};
			return 0;
		} 
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 1 && msg.y <= 122 + 72 * 1 && msg.is_down() && cpt[1]->state != RestRequest && cpt[1]->state != RestDenied)
		{
			MsgBoxNum = 12; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 2 && msg.y <= 122 + 72 * 2 && msg.is_down() && cpt[2]->state != RestRequest && cpt[2]->state != RestDenied)
		{
			MsgBoxNum = 13; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 3 && msg.y <= 122 + 72 * 3 && msg.is_down() && cpt[3]->state != RestRequest && cpt[3]->state != RestDenied)
		{
			MsgBoxNum = 14; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 4 && msg.y <= 122 + 72 * 4 && msg.is_down() && cpt[4]->state != RestRequest && cpt[4]->state != RestDenied)
		{
			MsgBoxNum = 15; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 5 && msg.y <= 122 + 72 * 5 && msg.is_down() && cpt[5]->state != RestRequest && cpt[5]->state != RestDenied)
		{
			MsgBoxNum = 16; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 6 && msg.y <= 122 + 72 * 6 && msg.is_down() && cpt[6]->state != RestRequest && cpt[6]->state != RestDenied)
		{
			MsgBoxNum = 17; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 1040 && msg.x <= 1110 && msg.y >= 87 + 72 * 7 && msg.y <= 122 + 72 * 7 && msg.is_down() && cpt[7]->state != RestRequest && cpt[7]->state != RestDenied)
		{
			MsgBoxNum = 18; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 60 && msg.x <= 160 && msg.y >= 650 && msg.y <= 700 && msg.is_down())
		{
			MsgBoxNum = 19; 
			msg = {0};
			return 0;
		}
		if(msg.x >= 180 && msg.x <= 280 && msg.y >= 650 && msg.y <= 700 && msg.is_down() && cpt[0]->state != OffApproved)
		{
			MsgBoxNum = 20; 
			msg = {0};
			return 0;
		}
}


void DetailMsg()
{
	
	
		
	setcolor(BLACK);
	setfontbkcolor(BLACK); 
	setfont(25, 0, "宋体");
	xyprintf(50,600,"缓冲区人数%d",bfa->Cur_Num);
		
		
	if(bfa->Cur_Num==0)
		xyprintf(250,600,"当前出缓冲区无乘客");
	else 
		xyprintf(250,600,"当前出缓冲区的乘客编号%d",CurOutG->num);
			
	
	PIMAGE img = newimage();
			
	if(MsgBoxNum<10)
	{
		
			if(cptq[MsgBoxNum-1]->PAmount==0)
			{
				MsgBoxNum = 0;
				return;
			}
		
			getimage(img,"imgs//信息.png");
			putimage(1100,30,img);
			//putimage(110,400, cptq[MsgBoxNum-1]->Queue[0]->face);
			putimage_transparent(NULL,cptq[MsgBoxNum-1]->Queue[0]->face,1137,65,BLACK);
			xyprintf(1230,90,"%d",cptq[MsgBoxNum-1]->Queue[0]->num);
			xyprintf(1150,135,"%d",cpt[MsgBoxNum-1]->Cur_CheckLen);
			xyprintf(1120,155,"已安检时长"); 
//		/*
		if((cpt[MsgBoxNum-1]->Sum_CheckLen-cpt[MsgBoxNum-1]->Cur_CheckLen)==0)
		{
			float per=(3-(frame/20)%3);
			PIMAGE pic=newimage();
			PIMAGE picd=newimage(149 * per,88 * per);
			//xyprintf(100,100,"hello");
			getimage(pic,"imgs//accepted.png",0,0);
			putimage(picd,0,0,149 * per,88* per ,pic,0,0,149,88 ,SRCCOPY);
			putimage_transparent(NULL,picd,1111, 1440 - (1440- 89) * frame / 60,0,0,0,0,0);
			delimage(pic);
			delimage(picd);
		}
//*/
		
		
		if(MsgBoxNum==1)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51 && msg.y <= 51+70))
			{
				
				MsgBoxNum = 0;
				
				msg = {0};
				return; 
			}
			
			
		}
		if(MsgBoxNum==2)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3 && msg.y <= 51+70+3+70))
			{
			
				MsgBoxNum = 0;
				msg = {0};
				return; 
			}
		}
		if(MsgBoxNum==3)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3 && msg.y <= 51+70+3+70+3+70))
			{
				
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
		if(MsgBoxNum==4)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70))
			{
			
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
		if(MsgBoxNum==5)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70+3+70))
			{
				
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
		if(MsgBoxNum==6)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3 && msg.y <= 51+70+3+70+3+70+3+70+3+70+3+70))
			{
			
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
		if(MsgBoxNum==7)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3+70+3 && msg.y <=51+70+3+70+3+70+3+70+3+70+3+70+3+70)) 
			{
				
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
		if(MsgBoxNum==8)
		{
			while (mousemsg())  msg = getmouse();
			if(!(msg.x >= 951 && msg.x <= 951 + 70 && msg.y >= 51+70+3+70+3+70+3+70+3+70+3+70+3+70+3 && msg.y <=51+70+3+70+3+70+3+70+3+70+3+70+3+70+3+70))
			{
				
				MsgBoxNum = 0;
				msg = {0};
				return;
			}
		}
			delimage(img) ;
	
	}

	
			
}



