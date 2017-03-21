/***************************
interface_font.h
定义各窗口的字体类型和大小
***************************/

//*****************************************************公用常量
#ifndef INTERFACE_FONT_H
#define INTERFACE_FONT_H

//标题栏
#define TITLE_FONT_FAMILY	"wenquanyi"
#define TITLE_FONT_SIZE	12
#define TITLE_FONT_WEIGHT QFont::Bold	
	
//列表的字体
#define LISTVIEW_FONT_FAMILY	"wenquanyi"
#define LISTVIEW_FONT_SIZE	12
#define LISTVIEW_FONT_WEIGHT QFont::Normal

//相对坐标标签
#define RELATIVE_TAG_FONT_FAMILY	"wenquanyi"
#define RELATIVE_TAG_FONT_SIZE	16
#define RELATIVE_TAG_FONT_WEIGHT QFont::Bold	

//其它标签
//包括：工件坐标 剩余量 刀具 机床坐标 单件时间 加工件数 当前运行段
#define ELSE_TAG_FONT_FAMILY	"wenquanyi"
#define ELSE_TAG_FONT_SIZE		12
#define ELSE_TAG_FONT_WEIGHT QFont::Normal
	
//messagebox的字体	
#define MESSAGEBOX_FONT_FAMILY	"wenquanyi"
#define MESSAGEBOX_FONT_SIZE		12
#define MESSAGEBOX_FONT_WEIGHT QFont::Normal
#define MESSAGEBOX_FONT QFont(MESSAGEBOX_FONT_FAMILY,MESSAGEBOX_FONT_SIZE,MESSAGEBOX_FONT_WEIGHT,false)	
	
//默认的按钮字体
#define DEFAULT_BUTTON_FONT_FAMILY	"wenquanyi"
#define DEFAULT_BUTTON_FONT_SIZE	16
#define DEFAULT_BUTTON_FONT_WEIGHT QFont::Bold
	
//默认按钮的颜色
#define DEFAULT_BUTTON_FORE_COLOR	(QColor( 255, 255, 255 ))
#define DEFAULT_BUTTON_BACK_COLOR	(QColor( 106, 110, 180 ))	

//画笔的颜色
#define PAINTER_FONT_FAMILY	"wenquanyi"
#define PAINTER_FONT_SIZE	6
#define PAINTER_FONT_WEIGHT QFont::Light
	
//*****************************************************主界面
//按钮	因为有的按钮的字太多所以各个界面不一定相同
#define BASE_BUTTON_FONT_FAMILY	"wenquanyi"
#define BASE_BUTTON_FONT_SIZE	16
#define BASE_BUTTON_FONT_WEIGHT QFont::Bold
//*****************************************************参数界面
#define PARA_BUTTON_FONT_FAMILY	"wenquanyi"
#define PARA_BUTTON_FONT_SIZE	16
#define PARA_BUTTON_FONT_WEIGHT QFont::Bold
//*************************************************刀具界面	
#define TOOL_BUTTON_FONT_FAMILY	"wenquanyi"
#define TOOL_BUTTON_FONT_SIZE	13
#define TOOL_BUTTON_FONT_WEIGHT QFont::Bold
	
#define TOOL_LABEL_FONT_FAMILY	"wenquanyi"
#define TOOL_LABEL_FONT_SIZE	12
#define TOOL_LABEL_FONT_WEIGHT QFont::Bold	
//*************************************************plc编辑界面	

#define PLCEDITOR_BUTTON_FONT_FAMILY	"wenquanyi"
#define PLCEDITOR_BUTTON_FONT_SIZE	8
#define PLCEDITOR_BUTTON_FONT_WEIGHT QFont::Bold
//*****************************************plc编辑界面弹出的对话框
#define PLC_POPUP_FONT_FAMILY  "wenquanyi"
#define PLC_POPUP_FONT_SIZE	10
#define PLC_POPUP_FONT_WEIGHT QFont::Normal		
//*****************************************************程序界面	
#define CHENGXU_BUTTON_FONT_FAMILY  "wenquanyi"
#define CHENGXU_BUTTON__FONT_SIZE	13
#define CHENGXU_BUTTON__FONT_WEIGHT QFont::Normal	
		
//*****************************************************诊断界面
#define PLC_DIAGNOSE_BUTTON_FONT_FAMILY	"wenquanyi"
#define PLC_DIAGNOSE_BUTTON_FONT_SIZE	16
#define PLC_DIAGNOSE_BUTTON_FONT_WEIGHT QFont::Bold

//*****************************************************MDI
#define MDI_BUTTON_FONT_FAMILY	"wenquanyi"
#define MDI_BUTTON_FONT_SIZE	16
#define MDI_BUTTON_FONT_WEIGHT QFont::Bold
	
#define MDI_LABEL_FONT_FAMILY	"wenquanyi"
#define MDI_LABEL_FONT_SIZE	13
#define MDI_LABEL_FONT_WEIGHT QFont::Bold
//*****************************************************坐标界面	
#define COOR_BUTTON_FONT_FAMILY  "wenquanyi"
#define COOR_BUTTON_FONT_SIZE	16
#define COOR_BUTTON_FONT_WEIGHT QFont::Normal	
	
//*****************************************************仿真界面	
#define EMLU_BUTTON_FONT_FAMILY  "wenquanyi"
#define EMLU_BUTTON_FONT_SIZE	16
#define EMLU_BUTTON_FONT_WEIGHT QFont::Normal		
	
//*****************************************************自动界面	
#define AUTO_BUTTON_FONT_FAMILY  "wenquanyi"
#define AUTO_BUTTON_FONT_SIZE	16
#define AUTO_BUTTON_FONT_WEIGHT QFont::Normal	
//*****************************************************自动界面	
#define MANU_BUTTON_FONT_FAMILY  "wenquanyi"
#define MANU_BUTTON_FONT_SIZE	16
#define MANU_BUTTON_FONT_WEIGHT QFont::Normal			
		


		
#endif 

