/*plc_editor_dialog.h*/
//梯形图编辑界面用到的对话框
//可以用继承来减少代码,我现在还不会,呵呵
#ifndef DIALOG_ALL
#define DIALOG_ALL

#include<qwidget.h>
#include<qdialog.h>
#include<qpushbutton.h>
#include<qlineedit.h>
#include<qlabel.h>
#include<qstring.h>
#include<qfont.h>
#include<qevent.h>
#include<qnamespace.h> 
#include<iostream>
#include <qtextcodec.h>
#include <qmessagebox.h> 

using namespace std;
#ifndef XNUM
#define XNUM 16
#define YNUM 16
#define MNUM 64
#define CNUM 16
#define TNUM 16
#define LENGTH 4
#endif

#define CSET 9999
#define TSET 9999

#include "interface_font.h"

//#define MESSAGEBOX(strTitle, strInfo, Icon) QTextCodec *codecM=QTextCodec::codecForName("gbk"); \
//	QMessageBox messagebox(codecM->toUnicode(strTitle) ,codecM->toUnicode(strInfo)                           \
//	,QMessageBox::Icon,QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton 	,this);         \
//	messagebox.setFont(MESSAGEBOX_FONT);	messagebox.exec();
#define MESSAGEBOX(strTitle, strInfo, Icon) QMessageBox messagebox(strTitle ,strInfo          \
    ,QMessageBox::Icon,QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton 	,this);         \
    messagebox.setFont(MESSAGEBOX_FONT);	messagebox.exec();


//toutf8--qt3到4增加内容
//#define MESSAGEBOX_NUM(i)		MESSAGEBOX("",QString("%1%2%3") \
//                                        .arg(tr("元件的编号不在0-")) \
//                                        .arg(i) \
//                                        .arg(tr("范围之内!")),Information );
#define MESSAGEBOX_NUM(i)		       		QMessageBox msgBox(this);\
 msgBox.setWindowTitle(QObject::tr("提示"));\
msgBox.setInformativeText(QObject::tr("元件的编号不在0-%1范围内！").arg(i));\
msgBox.setStandardButtons(QMessageBox::Ok);\
msgBox.setDefaultButton(QMessageBox::Ok);\
msgBox.setButtonText(QMessageBox::Yes, QObject::tr("确定"));\
    msgBox.setIcon(QMessageBox::Information);\
    msgBox.grabKeyboard();\
msgBox.exec();\
msgBox.releaseKeyboard();

//#define BACK_COLOR  QColor(232,232,232)	//谈出对话框的背景色
class NocDialog : public QDialog	//-||-
{
	Q_OBJECT
private:
	QLabel *pExplainLabel;
	QLabel *pEStyleLabel;
	QLabel *pMExplainLabel;
	QLineEdit *pLineEdit;
	QPushButton *pCancelButton;
	QPushButton *pOkButton;
		
	//这两个变量确定元件的类型		
	QString qsEstyle[5];
	int i;		
	
    virtual void keyPressEvent(QKeyEvent *);
public:
    NocDialog(QWidget *parent=0, const char *name = 0, bool modal = true );
	~NocDialog();		
private slots:
	void F1Slot();
	void CancelButtonSolt();
	void OkButtonSlot();
	void EstyleLabelSlot(bool iPgUp);
	void M_Explain();
signals:
	void KeyPgUpPressedSignal(bool bPgUp = true);		
	void KeyPgDnPressedSignal(bool bPgUp = false);
	void KeyEscapePressedSignal();
	void KeyEnterPressedSignal();
	void KeyF1PressedSignal();
	
	void NocDialogResult(QString &, int );
		
};	

class NccDialog : public QDialog	//-|/|-
{
	Q_OBJECT
private:
	QLabel *pExplainLabel;
	QLabel *pEStyleLabel;
	QLabel *pMExplainLabel;
	QLineEdit *pLineEdit;
	QPushButton *pCancelButton;
	QPushButton *pOkButton;
	
	//这两个变量确定元件的类型		
	QString qsEstyle[5];
	int i;
		
	virtual void keyPressEvent(QKeyEvent *);
public:
    NccDialog(QWidget *parent=0, const char *name = 0, bool modal = true);
	~NccDialog();	
private slots:
	void F1Slot();
	void CancelButtonSolt();
	void OkButtonSlot();
	void EstyleLabelSlot(bool iPgUp);
	void M_Explain();

signals:
	void KeyPgUpPressedSignal(bool bPgUp = true);		
	void KeyPgDnPressedSignal(bool bPgUp = false);
	void KeyEscapePressedSignal();
	void KeyEnterPressedSignal();
	void KeyF1PressedSignal();
	void NccDialogResult(QString &, int );
};	

class OutDialog : public QDialog	//()
{
	Q_OBJECT
private:
	QLabel *pExplainLabel;
	QLabel *pEStyleLabel;
	QLabel *pEParaLabel;
	QLabel *pMExplainLabel;
	QLineEdit *pLineEdit1;
	QLineEdit *pLineEdit2;
	QPushButton *pCancelButton;
	QPushButton *pOkButton;
	
	//这两个变量确定元件的类型		
	QString qsEstyle[4];
	int i;
		
	virtual void keyPressEvent(QKeyEvent *);
public:
    OutDialog(QWidget *parent=0, const char *name = 0, bool modal = true );
	~OutDialog();	
private slots:
	void F1Slot();
	void CancelButtonSolt();
	void OkButtonSlot();
	void EstyleLabelSlot(bool iPgUp);
	void M_Explain();

signals:
	void KeyPgUpPressedSignal(bool bPgUp = true);		
	void KeyPgDnPressedSignal(bool bPgUp = false);
	void KeyEscapePressedSignal();
	void KeyEnterPressedSignal();
	void KeyF1PressedSignal();
	
	void OutDialogResult(QString &, int ,int);
		
};	

class SetDialog : public QDialog	//(S)
{
	Q_OBJECT
private:
	QLabel *pExplainLabel;
	QLabel *pEStyleLabel;
	QLabel *pMExplainLabel;
	QLineEdit *pLineEdit;
	QPushButton *pCancelButton;
	QPushButton *pOkButton;
	
	//这两个变量确定元件的类型		
	QString qsEstyle[2];
	int i;
		
	virtual void keyPressEvent(QKeyEvent *);
public:
    SetDialog(QWidget *parent=0, const char *name = 0, bool modal = true);
	~SetDialog();	
	
private slots:
	void F1Slot();
	void CancelButtonSolt();
	void OkButtonSlot();
	void EstyleLabelSlot(bool iPgUp);
	void M_Explain();

signals:
	void KeyPgUpPressedSignal(bool bPgUp = true);		
	void KeyPgDnPressedSignal(bool bPgUp = false);
	void KeyEscapePressedSignal();
	void KeyEnterPressedSignal();
	void KeyF1PressedSignal();
	
	void SetDialogResult(QString &, int );
		
};	

class RstDialog : public QDialog	//(R)
{
	Q_OBJECT
private:
	QLabel *pExplainLabel;
	QLabel *pEStyleLabel;
	QLabel *pMExplainLabel;
	QLineEdit *pLineEdit;
	QPushButton *pCancelButton;
	QPushButton *pOkButton;
	
	//这两个变量确定元件的类型		
	QString qsEstyle[4];
	int i;
		
	virtual void keyPressEvent(QKeyEvent *);
public:
    RstDialog(QWidget *parent=0, const char *name = 0, bool modal = true);
	~RstDialog();	
private slots:
	void F1Slot();
	void CancelButtonSolt();
	void OkButtonSlot();
	void EstyleLabelSlot(bool iPgUp);
	void M_Explain();
signals:
	void KeyPgUpPressedSignal(bool bPgUp = true);		
	void KeyPgDnPressedSignal(bool bPgUp = false);
	void KeyEscapePressedSignal();
	void KeyEnterPressedSignal();
	void KeyF1PressedSignal();
	
	void RstDialogResult(QString &, int );
		
};	

#endif
