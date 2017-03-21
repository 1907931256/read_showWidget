/*plc_editor_dialog.cpp*/
#include"plc_editor_dialog.h"
#include"SysKeyboard.h"
///////////////////////////////////////////////////////////////////////////////////	NocDialog
NocDialog::NocDialog(QWidget *parent, const char *name, bool modal): QDialog(parent)
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	QString caption= codec->toUnicode("输入<清空:F1>") ;	//("输入<清空:F1>");	
    setWindowTitle(caption);

	
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
	
	QFont plc_popup_font=QFont(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	
	setFont(plc_popup_font);//标题栏
	
    pExplainLabel = new QLabel(codec->toUnicode("按下+/-切换元件类型"),this);
	pExplainLabel->setFont(plc_popup_font);	
	pExplainLabel->setGeometry(8,10,280,30);
    pExplainLabel->setFocusPolicy(Qt::NoFocus);
		
	pEStyleLabel = new QLabel("X",this);
	pEStyleLabel->setFont(plc_popup_font);
	pEStyleLabel->setGeometry(20,50,20,30);	
    pEStyleLabel->setFocusPolicy(Qt::NoFocus);

	pMExplainLabel = new QLabel("",this);
	pMExplainLabel->setFont(plc_popup_font);
	pMExplainLabel->setGeometry(140,50,100,30);	
    pMExplainLabel->setFocusPolicy(Qt::NoFocus);

		
	pLineEdit = new QLineEdit(this);
    pLineEdit->setGeometry(50,50,80,30);
    pLineEdit->setText("0");
	
	pCancelButton = new QPushButton(codec->toUnicode("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
    pCancelButton->setFocusPolicy(Qt::NoFocus);
		
	pOkButton = new QPushButton(codec->toUnicode("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
    pOkButton->setFocusPolicy(Qt::NoFocus);
	
	pLineEdit->setFocus();
	connect(this ,SIGNAL( KeyPgUpPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );
	connect(this ,SIGNAL( KeyPgDnPressedSignal(bool ) ),
                    this,SLOT(EstyleLabelSlot(bool )) );

	connect(this ,SIGNAL( KeyEscapePressedSignal() ),
					this,SLOT(CancelButtonSolt() ));
	connect(this ,SIGNAL( KeyEnterPressedSignal() ),
					this,SLOT(OkButtonSlot()) );				
	connect(this ,SIGNAL( KeyF1PressedSignal() ),
					this,SLOT(F1Slot() ));						
	connect(pLineEdit ,SIGNAL(textChanged(const QString&)),
					this,SLOT(M_Explain() ));
					
	qsEstyle[0] = QString("X");				
	qsEstyle[1] = QString("Y");
	qsEstyle[2] = QString("M");
	qsEstyle[3] = QString("C");
	qsEstyle[4] = QString("T");
	i=0;
}
NocDialog::~NocDialog()
{
	delete pExplainLabel;
	pExplainLabel = NULL;
	delete pEStyleLabel;
	pEStyleLabel= NULL;
	delete pLineEdit;
	pLineEdit= NULL;
	delete pCancelButton;
	pCancelButton= NULL;
	delete pOkButton;	
	pOkButton= NULL;	
}	
void NocDialog::F1Slot()	
{
	pLineEdit->setText("");//清空
}	
void NocDialog::CancelButtonSolt()
{
	reject();
}	
void NocDialog::OkButtonSlot()
{	
	bool ok=true;		
	QString str = pEStyleLabel->text();	
	int iNum = (pLineEdit->text()).toInt(&ok,10);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	//检查输入数据的有效性	
	if(str == QString("X"))
	{
		if(iNum < 0 || iNum >= XNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(XNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(XNUM-1);
			//pLineEdit->clear();	
			return;	
		}	
	}	
	else if(str == QString("Y"))
	{
		if(iNum < 0 || iNum >= YNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(YNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(YNUM-1);
			return;	
		}	
	}	
	else if(str == QString("M"))
	{
		if(iNum < 0 || iNum >= MNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(MNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(MNUM-1);
			return;	
		}	
	}	
	else if(str == QString("C"))
	{
		if(iNum < 0 || iNum >= CNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(CNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(CNUM-1);
			return;	
		}	
	}	
	else if(str == QString("T"))
	{
		if(iNum < 0 || iNum >= TNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(TNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(TNUM-1);
			return;	
		}	
	}		
	emit NocDialogResult(str, iNum );
	accept();
}		
void NocDialog::EstyleLabelSlot(bool bPgUp)
{
	//调整元件的类型
	if(bPgUp)
	{
		i++;	
	}	
	else
	{
		i--;	
	}	
	if(i > 4)
	{
		i = 0;	
	}	
	else if(i < 0)
	{
		i = 4;	
	}
	pEStyleLabel->setText(qsEstyle[i]);
}	

void NocDialog::M_Explain()
{	QString MExplain[15] = {"  UDP   ",
							"  MUTE  ",
							"  CLAMP ",
							"  LDP   ",
							"  ER    ",
							" Y_CLOSE",
							" Y_PRESS",
							" Y_OPEN ",
							"  X_IP  ",
							"  R_IP  ",
							"  PUMP  ",
							" C_START",
							"Y_MANUAL",
							"Y_REF_OK",
							" C_R_BSY"
							};
	int iNum = (pLineEdit->text()).toInt();

	if( pEStyleLabel->text() == QString("M") && iNum<15)
	{
		pMExplainLabel->setText(MExplain[iNum]);
	}
	else
	{
		pMExplainLabel->setText("");
	}
}

void NocDialog::keyPressEvent(QKeyEvent *event)
{	
    int key = event->key();
    int iNum = (pLineEdit->text()).toInt();

    if (key == Key_End)
    {
        emit KeyEscapePressedSignal();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        emit KeyEnterPressedSignal();
    }
    else if(key == Key_F1)	//清空
    {
        emit KeyF1PressedSignal();
    }
    else if(key == Key_Left || key == Key_Backward ||   key == Qt::Key_Minus)
    {
        emit KeyPgUpPressedSignal(true);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Right || key == Key_Forward)
    {
        emit KeyPgDnPressedSignal(false);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
}	
///////////////////////////////////////////////////////////////////////////////////////NccDialog:
NccDialog::NccDialog(QWidget *parent, const char *name, bool modal ): QDialog(parent)
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	QString caption = codec->toUnicode("输入<清空:F1>");	//("输入<清空:F1>");	
    setWindowTitle(caption);
	
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
	//QWidget::setCursor(BlankCursor);
	
	QFont plc_popup_font(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	setFont(plc_popup_font);//标题栏
    pExplainLabel = new QLabel( codec->toUnicode("按下+/-切换元件类型"),this);
	pExplainLabel->setFont(plc_popup_font);	
	pExplainLabel->setGeometry(8,10,280,30);
    pExplainLabel->setFocusPolicy(Qt::NoFocus);
		
	pEStyleLabel = new QLabel("X",this);
	pEStyleLabel->setFont(plc_popup_font);
	pEStyleLabel->setGeometry(20,50,20,30);	
    pEStyleLabel->setFocusPolicy(Qt::NoFocus);
		
	pMExplainLabel = new QLabel("",this);
	pMExplainLabel->setFont(plc_popup_font);
	pMExplainLabel->setGeometry(140,50,100,30);	
    pMExplainLabel->setFocusPolicy(Qt::NoFocus);

	pLineEdit = new QLineEdit(this);
	pLineEdit->setGeometry(50,50,80,30);	
    pLineEdit->setText("0");

	pCancelButton = new QPushButton( codec->toUnicode("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
    pCancelButton->setFocusPolicy(Qt::NoFocus);
		
	pOkButton = new QPushButton( codec->toUnicode("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
    pOkButton->setFocusPolicy(Qt::NoFocus);
		
	pLineEdit->setFocus();
	connect(this ,SIGNAL( KeyPgUpPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );
	connect(this ,SIGNAL( KeyPgDnPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );				
	connect(this ,SIGNAL( KeyEscapePressedSignal() ),
					this,SLOT(CancelButtonSolt() ));
	connect(this ,SIGNAL( KeyEnterPressedSignal() ),
					this,SLOT(OkButtonSlot()) );				
	connect(this ,SIGNAL( KeyF1PressedSignal() ),
					this,SLOT(F1Slot() ));						
	connect(pLineEdit ,SIGNAL(textChanged(const QString&)),
					this,SLOT(M_Explain() ));
					
	qsEstyle[0] = QString("X");				
	qsEstyle[1] = QString("Y");
	qsEstyle[2] = QString("M");
	qsEstyle[3] = QString("C");
	qsEstyle[4] = QString("T");
	i=0;
}
NccDialog::~NccDialog()
{
	delete pExplainLabel;
	pExplainLabel = NULL;
	delete pEStyleLabel;
	pEStyleLabel= NULL;
	delete pLineEdit;
	pLineEdit= NULL;
	delete pCancelButton;
	pCancelButton= NULL;
	delete pOkButton;	
	pOkButton= NULL;
}	
void NccDialog::F1Slot()	//清空
{
	pLineEdit->setText("");//清空
	pLineEdit->setFocus();
	
}	
void NccDialog::CancelButtonSolt()
{
	reject();
}	
void NccDialog::OkButtonSlot()
{
	bool ok=true;	
	QString str = pEStyleLabel->text();
	int iNum = (pLineEdit->text()).toInt(&ok,10);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	//检查输入数据的有效性	
	if(str == QString("X"))
	{
		if(iNum < 0 || iNum >= XNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(XNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(XNUM-1);
			return;	
		}	
	}	
	else if(str == QString("Y"))
	{
		if(iNum < 0 || iNum >= YNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(YNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(YNUM-1);
			return;	
		}	
	}	
	else if(str == QString("M"))
	{
		if(iNum < 0 || iNum >= MNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(MNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(MNUM-1);
			return;	
		}	
	}	
	else if(str == QString("C"))
	{
		if(iNum < 0 || iNum >= CNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(CNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(CNUM-1);
			return;	
		}	
	}	
	else if(str == QString("T"))
	{
		if(iNum < 0 || iNum >= TNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(TNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(TNUM-1);
			return;	
		}	
	}		
	emit NccDialogResult(str,iNum);
	accept();
}	
void NccDialog::EstyleLabelSlot(bool bPgUp)//切换元件类型
{
	//调整元件的类型
	if(bPgUp)
	{
		i++;	
	}	
	else
	{
		i--;	
	}	
	if(i > 4)
	{
		i = 0;	
	}	
	else if(i < 0)
	{
		i = 4;	
	}
	pEStyleLabel->setText(qsEstyle[i]);
}	

void NccDialog::M_Explain()
{	QString MExplain[15] = {"  UDP   ",
							"  MUTE  ",
							"  CLAMP ",
							"  LDP   ",
							"  ER    ",
							" Y_CLOSE",
							" Y_PRESS",
							" Y_OPEN ",
							"  X_IP  ",
							"  R_IP  ",
							"  PUMP  ",
							" C_START",
							"Y_MANUAL",
							"Y_REF_OK",
							" C_R_BSY"
							};
	int iNum = (pLineEdit->text()).toInt();

	if( pEStyleLabel->text() == QString("M") && iNum<15)
	{
		pMExplainLabel->setText(MExplain[iNum]);
	}
	else
	{
		pMExplainLabel->setText("");
	}
}

void NccDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int iNum = (pLineEdit->text()).toInt();

    if (key == Key_End)
    {
        emit KeyEscapePressedSignal();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        emit KeyEnterPressedSignal();
    }
    else if(key == Key_F1)
    {
        emit KeyF1PressedSignal();
    }
    else if(key == Key_Left || key == Key_Backward ||   key == Qt::Key_Minus)
    {
        emit KeyPgUpPressedSignal(true);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Right || key == Key_Forward)
    {
        emit KeyPgDnPressedSignal(false);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
}	

//////////////////////////////////////////////////////////////////////////////////////OutDialog
OutDialog::OutDialog(QWidget *parent, const char *name, bool modal): QDialog(parent )
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	QString caption("Out Input <Clear:F1>");	//("输入<清空:F1>");	
    setWindowTitle(caption);
	
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
	//QWidget::setCursor(BlankCursor);
	
	QFont plc_popup_font(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	setFont(plc_popup_font);//标题栏
    pExplainLabel = new QLabel( codec->toUnicode("按下+/-切换元件类型"),this);
	pExplainLabel->setFont(plc_popup_font);	
	pExplainLabel->setGeometry(8,10,280,30);
    pExplainLabel->setFocusPolicy(Qt::NoFocus);
		
	pEStyleLabel = new QLabel("Y",this);
	pEStyleLabel->setFont(plc_popup_font);
	pEStyleLabel->setGeometry(20,50,20,30);	
    pEStyleLabel->setFocusPolicy(Qt::NoFocus);

	pMExplainLabel = new QLabel("",this);
	pMExplainLabel->setFont(plc_popup_font);
	pMExplainLabel->setGeometry(140,50,100,30);	
    pMExplainLabel->setFocusPolicy(Qt::NoFocus);

	pLineEdit1 = new QLineEdit(this);
	pLineEdit1->setGeometry(50,50,80,30);	
    pLineEdit1->setText("0");

	pEParaLabel = new QLabel("K",this);
	pEParaLabel->setFont(plc_popup_font);
	pEParaLabel->setGeometry(140,50,20,30);	
	pEParaLabel->hide();
	
	
	pLineEdit2 = new QLineEdit(this);
	pLineEdit2->setGeometry(160,50,80,30);	
	pLineEdit2->hide();
	
	
	pCancelButton = new QPushButton( codec->toUnicode("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
    pCancelButton->setFocusPolicy(Qt::NoFocus);
	
	pOkButton = new QPushButton( codec->toUnicode("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
    pOkButton->setFocusPolicy(Qt::NoFocus);
	
	pLineEdit1->setFocus();
	connect(this ,SIGNAL( KeyPgUpPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );
	connect(this ,SIGNAL( KeyPgDnPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );				
	connect(this ,SIGNAL( KeyEscapePressedSignal() ),
					this,SLOT(CancelButtonSolt() ));
	connect(this ,SIGNAL( KeyEnterPressedSignal() ),
					this,SLOT(OkButtonSlot()) );				
	connect(this ,SIGNAL( KeyF1PressedSignal() ),
					this,SLOT(F1Slot() ));						
	connect(pLineEdit1 ,SIGNAL(textChanged(const QString&)),
					this,SLOT(M_Explain() ));
					
			
	qsEstyle[0] = QString("Y");
	qsEstyle[1] = QString("M");
	qsEstyle[2] = QString("C");
	qsEstyle[3] = QString("T");
	i=0;
}
OutDialog::~OutDialog()
{
	delete pExplainLabel;
	pExplainLabel = NULL;
	
	delete pEStyleLabel;
	pEStyleLabel= NULL;
	
	delete pEParaLabel;
	pEParaLabel= NULL;
	
	delete pLineEdit1;
	pLineEdit1= NULL;
	
	delete pLineEdit2;
	pLineEdit2= NULL;
	
	delete pCancelButton;
	pCancelButton= NULL;
	
	delete pOkButton;	
	pOkButton= NULL;
}	
void OutDialog::F1Slot()	
{
	pLineEdit1->setText("");
	pLineEdit2->setText("");
	pLineEdit1->setFocus();
}	
void OutDialog::CancelButtonSolt()
{
	reject();
}	
void OutDialog::OkButtonSlot()
{		
	bool ok=true;	
	QString str = pEStyleLabel->text();
	int iNum=(pLineEdit1->text()).toInt(&ok,10);
	int iNum2=(pLineEdit2->text()).toInt(&ok,10);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	//检查输入数据的有效性	
	if(str == QString("Y"))
	{
		if(iNum < 0 || iNum > YNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(YNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(YNUM-1);
			return;	
		}	
	}	
	else if(str == QString("M"))
	{
		if(iNum < 0 || iNum > MNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(MNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(MNUM-1);
			return;	
		}	
	}	
	else if(str == QString("C"))
	{
		if(iNum < 0 || iNum > CNUM )//|| iNum < 0 || iNum < CSET)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(CNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/	
			MESSAGEBOX_NUM(CNUM-1);
			return;	
		}	
		else if(iNum2 < 0 || iNum2 > CSET)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("计数器的设定值不在0-"))
				.arg(CSET)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(CSET);
			return;	
		}	
	}	
	else if(str == QString("T"))
	{
		if(iNum < 0 || iNum > CNUM )//|| iNum < 0 || iNum < CSET)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(TNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(TNUM-1);
			return;	
		}	
		else if(iNum2 < 0 || iNum2 > CSET)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("定时器的设定值不在0-"))
				.arg(TSET)
				.arg(codec->toUnicode("范围之内!")) );
			*/	
			MESSAGEBOX_NUM(TSET);	
			return;	
		}	
	}		
	emit OutDialogResult(str,iNum,iNum2);
	clearFocus () ;
	accept();		
}	
void OutDialog::EstyleLabelSlot(bool bPgUp)
{
	if(bPgUp)
	{
		i++;	
	}	
	else
	{
		i--;	
	}	
	if(i > 3)
	{
		i = 0;	
	}	
	else if(i < 0)
	{
		i = 3;	
	}
	pEStyleLabel->setText(qsEstyle[i]);
	if(qsEstyle[i]==QString("Y") || qsEstyle[i]==QString("M"))
	{
		pEParaLabel->hide();
		pLineEdit2->hide();	
		pLineEdit2->setText("");	
	}	
	else
	{
		pEParaLabel->show();
		pLineEdit2->show();		
	}	
	
}	

void OutDialog::M_Explain()
{	QString MExplain[15] = {"  UDP   ",
							"  MUTE  ",
							"  CLAMP ",
							"  LDP   ",
							"  ER    ",
							" Y_CLOSE",
							" Y_PRESS",
							" Y_OPEN ",
							"  X_IP  ",
							"  R_IP  ",
							"  PUMP  ",
							" C_START",
							"Y_MANUAL",
							"Y_REF_OK",
							" C_R_BSY"
							};
	int iNum = (pLineEdit1->text()).toInt();

	if( pEStyleLabel->text() == QString("M") && iNum<15)
	{
		pMExplainLabel->setText(MExplain[iNum]);
	}
	else
	{
		pMExplainLabel->setText("");
	}
}

void OutDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int iNum = (pLineEdit1->text()).toInt();
    if (key == Key_End)
    {
        emit KeyEscapePressedSignal();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        emit KeyEnterPressedSignal();
    }
    else if(key == Key_F1)
    {
        emit KeyF1PressedSignal();
    }
    else if(key == Key_Left || key == Key_Backward ||   key == Qt::Key_Minus)
    {
        emit KeyPgUpPressedSignal(true);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Right || key == Key_Forward)
    {
        emit KeyPgDnPressedSignal(false);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit1->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit1->setText(QString("%1").arg(iNum));
    }
    else
    {
//        if (pLineEdit1->hasFocus())
//            pLineEdit1->keyPressEvent(event);
//        if (pLineEdit2->hasFocus())
//            pLineEdit2->keyPressEvent(event);
    }
}	

///////////////////////////////////////////////////////////////////////////////////	SetDialog
SetDialog::SetDialog(QWidget *parent, const char *name, bool modal ): QDialog(parent)
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QString caption(tr("输入<清空:F1>"));	//("输入<清空:F1>");
    setWindowTitle(caption);
	
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
	//QWidget::setCursor(BlankCursor);
	
	QFont plc_popup_font(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	setFont(plc_popup_font);//标题栏
    pExplainLabel = new QLabel( tr("按下PgUp/PgDn切换元件类型"),this);
	pExplainLabel->setFont(plc_popup_font);	
	pExplainLabel->setGeometry(8,10,280,30);
    pExplainLabel->setFocusPolicy(Qt::NoFocus);
		
	pEStyleLabel = new QLabel("Y",this);
	pEStyleLabel->setFont(plc_popup_font);
	pEStyleLabel->setGeometry(20,50,20,30);	
    pEStyleLabel->setFocusPolicy(Qt::NoFocus);
	
	pMExplainLabel = new QLabel("",this);
	pMExplainLabel->setFont(plc_popup_font);
	pMExplainLabel->setGeometry(140,50,100,30);	
    pMExplainLabel->setFocusPolicy(Qt::NoFocus);

	pLineEdit = new QLineEdit(this);
    pLineEdit->setGeometry(50,50,80,30);
    pLineEdit->setText("0");
	
    pCancelButton = new QPushButton( tr("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
    pCancelButton->setFocusPolicy(Qt::NoFocus);
		
    pOkButton = new QPushButton( tr("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
    pOkButton->setFocusPolicy(Qt::NoFocus);
		
	pLineEdit->setFocus();
	connect(this ,SIGNAL( KeyPgUpPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );
	connect(this ,SIGNAL( KeyPgDnPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );				
	connect(this ,SIGNAL( KeyEscapePressedSignal() ),
					this,SLOT(CancelButtonSolt() ));
	connect(this ,SIGNAL( KeyEnterPressedSignal() ),
					this,SLOT(OkButtonSlot()) );				
	connect(this ,SIGNAL( KeyF1PressedSignal() ),
					this,SLOT(F1Slot() ));						
	connect(pLineEdit ,SIGNAL(textChanged(const QString&)),
					this,SLOT(M_Explain() ));
					
	qsEstyle[0] = QString("Y");				
	qsEstyle[1] = QString("M");

	i=0;
}
SetDialog::~SetDialog()
{
	delete pExplainLabel;
	pExplainLabel = NULL;
	delete pEStyleLabel;
	pEStyleLabel= NULL;
	delete pLineEdit;
	pLineEdit= NULL;
	delete pCancelButton;
	pCancelButton= NULL;
	delete pOkButton;	
	pOkButton= NULL;
}	
void SetDialog::F1Slot()	
{
	pLineEdit->setText("");
	pLineEdit->setFocus();
}	
void SetDialog::CancelButtonSolt()
{
	reject();
}	
void SetDialog::OkButtonSlot()
{
	bool ok=true;	
	QString str = pEStyleLabel->text();
	int iNum = (pLineEdit->text()).toInt(&ok,10);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	//检查输入数据的有效性	
	if(str == QString("Y"))
	{
		if(iNum < 0 || iNum >= YNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(YNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(YNUM-1);
			return;	
		}	
	}	
	else if(str == QString("M"))
	{
		if(iNum < 0 || iNum >= MNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(MNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(MNUM-1);
			return;	
		}	
	}		
	emit SetDialogResult(str,iNum);
	accept();
}	
void SetDialog::EstyleLabelSlot(bool bPgUp)
{
	//调整元件的类型
	if(bPgUp)
	{
		i++;	
	}	
	else
	{
		i--;	
	}	
	if(i > 1)
	{
		i = 0;	
	}	
	else if(i < 0)
	{
		i = 1;	
	}
	pEStyleLabel->setText(qsEstyle[i]);
	
}	
void SetDialog::M_Explain()
{	QString MExplain[15] = {"  UDP   ",
							"  MUTE  ",
							"  CLAMP ",
							"  LDP   ",
							"  ER    ",
							" Y_CLOSE",
							" Y_PRESS",
							" Y_OPEN ",
							"  X_IP  ",
							"  R_IP  ",
							"  PUMP  ",
							" C_START",
							"Y_MANUAL",
							"Y_REF_OK",
							" C_R_BSY"
							};
	int iNum = (pLineEdit->text()).toInt();

	if( pEStyleLabel->text() == QString("M") && iNum<15)
	{
		pMExplainLabel->setText(MExplain[iNum]);
	}
	else
	{
		pMExplainLabel->setText("");
	}
}

void SetDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int iNum = (pLineEdit->text()).toInt();
    if (key == Key_End)
    {
        emit KeyEscapePressedSignal();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        emit KeyEnterPressedSignal();
    }
    else if(key == Key_F1)
    {
        emit KeyF1PressedSignal();
    }
    else if(key == Key_Left || key == Key_Backward ||   key == Qt::Key_Minus)
    {
        emit KeyPgUpPressedSignal(true);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Right || key == Key_Forward)
    {
        emit KeyPgDnPressedSignal(false);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
			
}	
///////////////////////////////////////////////////////////////////////////////////	RstDialog
RstDialog::RstDialog(QWidget *parent, const char *name, bool modal): QDialog(parent)
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	QString caption("Rst Input <Clear:F1>");	//("输入<清空:F1>");	
    setWindowTitle(caption);
	
    setFocusPolicy(Qt::StrongFocus);
	setFixedSize(290,135);
	//设置窗口的背景色于父窗口的背景色一致	
//    if(this->parentWidget() != NULL)
//    {
//    	QColor parentBackColor = parentWidget()->paletteBackgroundColor();
//    	setPaletteBackgroundColor(QColor(parentBackColor.red(), parentBackColor.green(), parentBackColor.blue()) );
//    }
	//QWidget::setCursor(BlankCursor);
	
	QFont plc_popup_font(PLC_POPUP_FONT_FAMILY,PLC_POPUP_FONT_SIZE,PLC_POPUP_FONT_WEIGHT ,false);	
	setFont(plc_popup_font);//标题栏
    pExplainLabel = new QLabel( codec->toUnicode("按下+/-切换元件类型"),this);
	pExplainLabel->setFont(plc_popup_font);	
	pExplainLabel->setGeometry(8,10,280,30);
	
	pEStyleLabel = new QLabel("Y",this);
	pEStyleLabel->setFont(plc_popup_font);
	pEStyleLabel->setGeometry(20,50,20,30);	

	pMExplainLabel = new QLabel("",this);
	pMExplainLabel->setFont(plc_popup_font);
	pMExplainLabel->setGeometry(140,50,100,30);	
    pMExplainLabel->setFocusPolicy(Qt::NoFocus);
	
	pLineEdit = new QLineEdit(this);
	pLineEdit->setGeometry(50,50,80,30);	
    pLineEdit->setText("0");

	pCancelButton = new QPushButton( codec->toUnicode("取消 [Esc]"),this);
	pCancelButton->setFont(plc_popup_font);
	pCancelButton->setGeometry(20,90,100,30);	
	
	pOkButton = new QPushButton( codec->toUnicode("确定 [Enter]"),this);
	pOkButton->setFont(plc_popup_font);
	pOkButton->setGeometry(150,90,100,30);
	pLineEdit->setFocus();
	connect(this ,SIGNAL( KeyPgUpPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );
	connect(this ,SIGNAL( KeyPgDnPressedSignal(bool ) ),
					this,SLOT(EstyleLabelSlot(bool )) );				
	connect(this ,SIGNAL( KeyEscapePressedSignal() ),
					this,SLOT(CancelButtonSolt() ));
	connect(this ,SIGNAL( KeyEnterPressedSignal() ),
					this,SLOT(OkButtonSlot()) );				
	connect(this ,SIGNAL( KeyF1PressedSignal() ),
					this,SLOT(F1Slot() ));
	connect(pLineEdit ,SIGNAL(textChanged(const QString&)),
					this,SLOT(M_Explain() ));
				
	qsEstyle[0] = QString("Y");
	qsEstyle[1] = QString("M");
	qsEstyle[2] = QString("C");
	qsEstyle[3] = QString("T");
	i=0;
}
RstDialog::~RstDialog()
{
	delete pExplainLabel;
	pExplainLabel = NULL;
	delete pEStyleLabel;
	pEStyleLabel= NULL;
	delete pLineEdit;
	pLineEdit= NULL;
	delete pCancelButton;
	pCancelButton= NULL;
	delete pOkButton;	
	pOkButton= NULL;
}	
void RstDialog::F1Slot()	
{
	pLineEdit->setText("");
}	
void RstDialog::CancelButtonSolt()
{
	reject();
}	
void RstDialog::OkButtonSlot()
{
	bool ok=true;	
	QString str = pEStyleLabel->text();
	int iNum = (pLineEdit->text()).toInt(&ok,10);
    //QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	//检查输入数据的有效性	
	if(str == QString("Y"))
	{
		if(iNum < 0 || iNum > YNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(YNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(YNUM-1);
			return;	
		}	
	}	
	else if(str == QString("M"))
	{
		if(iNum < 0 || iNum >= MNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(MNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(MNUM-1);
			return;	
		}	
	}	
	else if(str == QString("C"))
	{
		if(iNum < 0 || iNum >= CNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(CNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(CNUM-1);
			return;	
		}	
	}	
	else if(str == QString("T"))
	{
		if(iNum < 0 || iNum >= TNUM)
		{
			/*
			QMessageBox::information( this,"",QString("%1%2%3")
				.arg(codec->toUnicode("元件的编号不在0-"))
				.arg(TNUM-1)
				.arg(codec->toUnicode("范围之内!")) );
			*/
			MESSAGEBOX_NUM(TNUM-1);
			return;	
		}	
	}		
	
	emit RstDialogResult(str,iNum);
	accept();
}	
void RstDialog::EstyleLabelSlot(bool bPgUp)
{
	//调整元件的类型
	if(bPgUp)
	{
		i++;	
	}	
	else
	{
		i--;	
	}	
	if(i > 3)
	{
		i = 0;	
	}	
	else if(i < 0)
	{
		i = 3;	
	}
	pEStyleLabel->setText(qsEstyle[i]);
	
}	
void RstDialog::M_Explain()
{	QString MExplain[15] = {"  UDP   ",
							"  MUTE  ",
							"  CLAMP ",
							"  LDP   ",
							"  ER    ",
							" Y_CLOSE",
							" Y_PRESS",
							" Y_OPEN ",
							"  X_IP  ",
							"  R_IP  ",
							"  PUMP  ",
							" C_START",
							"Y_MANUAL",
							"Y_REF_OK",
							" C_R_BSY"
							};
	int iNum = (pLineEdit->text()).toInt();

	if( pEStyleLabel->text() == QString("M") && iNum<15)
	{
		pMExplainLabel->setText(MExplain[iNum]);
	}
	else
	{
		pMExplainLabel->setText("");
	}
}


void RstDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int iNum = (pLineEdit->text()).toInt();
    if (key == Key_End)
    {
        emit KeyEscapePressedSignal();
    }
    else if(key == Key_Enter || key == Key_Return )
    {
        emit KeyEnterPressedSignal();
    }
    else if(key == Key_F1)
    {
        emit KeyF1PressedSignal();
    }
    else if(key == Key_Left || key == Key_Backward ||   key == Qt::Key_Minus)
    {
        emit KeyPgUpPressedSignal(true);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Right || key == Key_Forward)
    {
        emit KeyPgDnPressedSignal(false);
        pMExplainLabel->setText("");
    }
    else if(key == Key_Up && iNum < MNUM)
    {
        iNum++;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
    else if(key == Key_Down && iNum > 0)
    {
        iNum--;
        pLineEdit->setText(QString("%1").arg(iNum));
    }
}	
