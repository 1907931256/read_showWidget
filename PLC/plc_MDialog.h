#ifndef PLC_MDIALOG_H
#define PLC_MDIALOG_H

#include <qtextcodec.h>
#include<qlabel.h>
#include<qwidget.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qdialog.h>
#include<qpushbutton.h>
#include<qmessagebox.h>
#include<qcursor.h>
#include<qevent.h>
//#include<qrect.h> //？
#include<qstring.h>
#include <qnamespace.h>
#include <qfont.h>

#ifndef XNUM
#define XNUM 256
#define YNUM 256
#define MNUM 256
#define CNUM 16
#define TNUM 16
#define LENGTH 4
#endif

#include"interface_font.h"

#ifdef MESSAGEBOX
#undef MESSAGEBOX
#endif

#define MESSAGEBOX(strTitle, strInfo, Icon) QTextCodec *codecM=QTextCodec::codecForName("gbk"); \
	QMessageBox messagebox(codecM->toUnicode(strTitle) ,codecM->toUnicode(strInfo)                           \
	,QMessageBox::Icon,QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton 	,this);         \
    messagebox.setFont(QFont("wenquanyi",12,QFont::Normal,false));	messagebox.exec();
                    

class MDialog : public QDialog
{
	Q_OBJECT

public:
    explicit MDialog(QWidget *parent=0, const char *name = 0, bool modal = true );// WStyle_Customize | WStyle_NoBorder | 0x00800000);
	~MDialog();		
	QLabel *pExplainLabe;
	QLineEdit *pLineEdit;
private:	
	QPushButton *pCancelButton;
	QPushButton *pOkButton;			
	virtual void keyPressEvent(QKeyEvent *);
signals:
	void KeyF1PressedSignal();
	void MDialogResult(QString &);			
};	

#endif

