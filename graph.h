#pragma once
#ifndef _GRAPH_H_
#include<graphics.h>
#include"airport.h"

#define Exit_x 461                   //���ں����� 
#define Exit_y 59                       //����������
#define Len_BufLine 412     	           //ͨ������
#define Wid_Bufline 80                 //ͨ����� 
#define R_guest 30                     //�˿Ͱ뾶	
#define Per_Move 68                    //���� 
#define MaxFaceNum 185					//�������� 



int startwin();
int inputmodeselect();
int CWIN();
int DWIN();
int cptq_graph();
int addguest_cptq(int cpt_num);
int get_org_pos(int org_x,int org_y,int psg);//���ڻ�ȡԭ������ 
int bfa_image();
int bfa_in(int pamount);
int bfa_out(int pamount);
int SelectCmd() ;
PIMAGE RandomFace();
int GetFaceList();
void Checkegefps();
void Bubble();
void Bubblefps();
int Modify_Settings();
void Modify_SetFile();
void DetailMsg(); 
int getMsgBoxNum();




 
 extern PIMAGE BFAbkg;
 
 extern PIMAGE bkg1;
 
 extern PIMAGE FaceList[MaxFaceNum];
 
 extern int cmdnum;
 
 extern	PIMAGE CMD_R;

 extern	PIMAGE CMD_G;

 extern PIMAGE CMD_Q ;
 
 extern PIMAGE CMD_Rf;
 
 extern PIMAGE CMD_Qf;
 
 extern mouse_msg msg;
 
 extern int MsgBoxNum;
 
#endif
