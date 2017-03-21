#include"plc_MDialog.h"
#include"SysKeyboard.h"
MDialog::MDialog(QWidget *parent, const char *name, bool modal ): QDialog(parent)
{	
	QTextCodec *codec=QTextCodec::codecForName("gbk");
	QString caption= codec->toUnicode("输入<清空:F1> <Ctrl+空格切换输入法>") ;	//("输入<清空:F1>");	
    setWindowTitle(caption);
	//setPaletteBackgroundColor(lightGray);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);	
    setCursor(Qt::BlankCursor);
	
	QFont plc_popup_font=QFont(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	
    pExplainLabe = new QLabel("",this);//("",this);//(codec->toUnicode("按下+/-切换元件类型"),this);
	pExplainLabe->setFont(plc_popup_font);	
	pExplainLabe->setGeometry(8,10,280,30);
    pExplainLabe->setFocusPolicy(Qt::NoFocus);
	
	pLineEdit = new QLineEdit(this);
	pLineEdit->setGeometry(50,45,170,30);	
	
	pCancelButton = new QPushButton(codec->toUnicode("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
    pCancelButton->setFocusPolicy(Qt::NoFocus);
		
	pOkButton = new QPushButton(codec->toUnicode("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
    pOkButton->setFocusPolicy(Qt::NoFocus);
	
	pLineEdit->setFocus();
}					
MDialog::~MDialog()
{
	delete pCancelButton;
	delete pOkButton;
	delete pExplainLabe;
	delete pLineEdit;	
}	
void MDialog::keyPressEvent(QKeyEvent *event)
{
    QTextCodec *codec=QTextCodec::codecForName("gbk");
    int key = event->key();
    if (key == Key_End)
    {
        reject();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        QString str = pLineEdit->text();
        str =str.simplified();
        if(str.length() > LENGTH)
        {
            QString strT;
            strT = QString("%1%2%3").arg(codec->toUnicode("字符过长！最多支持")).arg(LENGTH).arg(codec->toUnicode("个字符"));
            //QMessageBox::information( this,"",strT,codec->toUnicode("确定"));
            MESSAGEBOX("",strT.toUtf8(),Information );
            pLineEdit->setText(str);
        }
        else
        {
            emit MDialogResult(str);
            accept();
        }//end of	if(str.length()>LENGTH)
    }
    else if(key == Key_F1)
    {
        pLineEdit->setText("");
    }
}

