#include "uiPlcEditor.h"
#include "ui_uiPlcEditor.h"
#include <QTextCodec>
#include <QTime>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include"SysKeyboard.h"
#include"sysGlobal.h"

uiPlcEditor::uiPlcEditor(QWidget *parent, QString strName, bool monitor) :
       QWidget(parent),
    ui(new Ui::uiPlcEditor)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    move(0,0);
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::BlankCursor);//不显示光标
    setStyleSheet("QDialog {background-color: white;border-width: 2px;border-radius: 5px;border-color: lightGray;}");
    //设置应用程序强制光标为WaitCursor  将光标强制编程“等待沙漏”的形状，而不是普通的箭头形状
    QApplication::setOverrideCursor(Qt::WaitCursor);

    //======初始化主界面内容========
    //从文件中读取指令并翻译成树型结构
    char cFileName[]="/plc_instruction_running.txt";
    QByteArray file1=relativePath.toUtf8();
    char* fileOne=file1.data();
    char first[100];
    strncpy(first,fileOne,99);
    strcat(first,cFileName);
    FormLadder(first);	//函数返回pRungHead
    //配置说明赋初值
    for(int i=0; i<XNUM+YNUM+MNUM ;i++)
    {
        asESign[i] =  QString ();
    }
    char cFileName2[]="/plc_element_signification_running.txt";
    QByteArray file2=relativePath.toUtf8();
    char* fileTwo=file2.data();
    char second[100];
    strncpy(second,fileTwo,99);
    strcat(second,cFileName2);
    GetElementSignifiation(second);//函数给asESign赋值

    bPaintOk = false;       //界面刷新是否结束，正在画图时不响应键盘事件
//    iButtonPage=1;			//按钮条处在第一页状态
    iDisplayTop=36;			//显示区域的顶端y坐标
    iDisplayBottom=445;     //显示区域的底端y坐标		光标的最大Ｙ坐标值为428
    iDisplayLeft=10;        //显示区域的左端x坐标
    iDisplayRight=620;		//显示区域的右端x坐标
    //iDisplayRight=1240;
    //初始光标位置在显示区域的左上角
    iCursorX = W/2+5; 				// W/2+5; ;
    iCursorY = 55; 				//55;

    iySlider = 0;
    ixFirst = -1;	//插入分支的第一点未选中
    iyFirst = -1;

    pRungTop=pRungHead;	//初始化时第一行显示的是梯级的头指针
    iRowCBIR=pRungHead->iRungRow;		//....的倒数最后一行
    pRungDraw=NULL;			//正在画的梯级为空

    inet = 0;

    //清空界面数组
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<10; j++)
        {
            cellArray[i][j].pRung =NULL;
            cellArray[i][j].pNode =NULL;
            cellArray[i][j].pElement =NULL;
        }
    }

//    setCurButton(1);
    //定义对话框
    pNocDialog = new NocDialog(this,"Noc",true);
    connect(pNocDialog,SIGNAL( NocDialogResult(QString &, int ) ),
           this,SLOT(NocButtonSlot(QString &, int )));

     pNccDialog = new NccDialog(this,"Ncc");
     connect(pNccDialog,SIGNAL( NccDialogResult(QString &, int ) ),
           this,SLOT(NccButtonSlot(QString &, int )));

    pOutDialog = new OutDialog(this,"Out");
    connect(pOutDialog,SIGNAL( OutDialogResult(QString &, int, int ) ),
           this,SLOT(OutButtonSolt(QString &, int, int )));

    pSetDialog = new SetDialog(this,"Set");
    connect(pSetDialog,SIGNAL( SetDialogResult(QString &, int ) ),
           this,SLOT(SetButtonSlot(QString &, int )));
    pRstDialog = new RstDialog(this,"Rst");
    connect(pRstDialog,SIGNAL( RstDialogResult(QString &, int ) ),
           this,SLOT(RstButtonSlot(QString &, int )));

    pMDialog = new MDialog(this,"M");
    connect( pMDialog,SIGNAL(MDialogResult(QString &)),
             this,SLOT( ModifyElementSlot(QString &) ) );

    QApplication::restoreOverrideCursor();
}

uiPlcEditor::~uiPlcEditor()
{
    delete ui;
    //释放所有的梯级
    Rung *pRung = pRungHead;
    while(pRung != NULL)
    {
        Rung *pRungTmp = pRung;
        Node *pNodeRoot = pRung->pNodeRoot;
        ReleaseNode(pNodeRoot);
        pRung = pRung->pNextRung;
        delete pRungTmp;
    }
    pRungHead = NULL;

    delete pNocDialog;
    delete pNccDialog;
    delete pOutDialog;
    delete pSetDialog;
    delete pRstDialog;
    delete pMDialog;

}

//void uiPlcEditor::setCurButton(int ncur)
//{
//    if(!bMonitor)
//    {
//        if (ncur < 1 && ncur > 2)
//        {
//            qDebug()<<"setCurButton() bad paras.";
//            return;
//        }

//        iButtonPage = ncur;
//        if (1 == iButtonPage)
//        {
//            ui->Button1->setText(tr(" -| |- "));
//            ui->Button2->setText(tr(" -|/|- "));
//            ui->Button3->setText(tr(" -( )  "));
//            ui->Button4->setText(tr(" -(S)- "));
//            ui->Button5->setText(tr(" -(R)- "));
//            ui->Button6->setText(tr("   |   "));
//            ui->Button7->setText(tr("删除元件"));
//            ui->Button8->setText(tr(" >> "));

//        }
//        else if (2 == iButtonPage)
//        {
//            ui->Button1->setText(tr("插入梯级"));
//            ui->Button2->setText(tr("删除分支"));
//            ui->Button3->setText(tr("删除梯级"));
//            ui->Button4->setText(tr(""));
//            ui->Button5->setText(tr("保存"));
//            ui->Button6->setText(tr(""));
//            ui->Button7->setText(tr("返回"));
//            ui->Button8->setText(tr(" << "));
//        }
//    }
//    else
//    {
//        ui->Button1->setText(tr(""));
//        ui->Button2->setText(tr(""));
//        ui->Button3->setText(tr(""));
//        ui->Button4->setText(tr(""));
//        ui->Button5->setText(tr(""));
//        ui->Button6->setText(tr(""));
//        ui->Button7->setText(tr(""));
//        ui->Button8->setText(tr("退出"));
//    }
//}

/*********************************************
 *function：获取每个表格中所代表单元的元件名称
 *adding:   存储在ElementName[11][10]中，使用代码表示元件名称
 *author：xu
 *date：2015/03/05
 ********************************************/
void uiPlcEditor::GetElementName()
{
    bOverflow = false;  //获取元件编码时，认为元件未越界
    bNoted = false;     //还未通知用户元件越界，此时可显示的元件可能越界
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(NULL != cellArray[i][j].pElement)
            {
                switch (cellArray[i][j].pElement->iState) {
                case 0:
                case 2:
                case 3:
                case 4:
                {
                    ElementName[i][j] = 0x0000;
                    break;
                }
                case 1:
                {
                    ElementName[i][j] = 0x1000;
                    break;
                }
                default:
                {
                    ElementName[i][j] = 0x0000;
                    break;
                }
                }
                QString type = cellArray[i][j].pElement->cName;
                if(type == QString("X"))
                    ElementName[i][j] |= 0x0100;
                else if(type == QString("Y"))
                    ElementName[i][j] |= 0x0200;
                else if(type == QString("M"))
                    ElementName[i][j] |= 0x0300;
                else if(type == QString("C"))
                    ElementName[i][j] |= 0x0400;
                else if(type == QString("T"))
                    ElementName[i][j] |= 0x0500;
                else
                    ElementName[i][j] |= 0x0000;
                //取元件编号
                ElementName[i][j] |= (unsigned short int)cellArray[i][j].pElement->iNum;
            }
            else
                ElementName[i][j] = 0x0000;
        }
    }
}

void uiPlcEditor::keyPressEvent(QKeyEvent *eKey)
{
    int iKey = eKey->key();
    switch (iKey)
    {
    case Key_End:
    {
//        accept();
        break;
    }
    case Key_F1:     //"-| |-"
    {
        int ix = int(iCursorX-10)/W;
        int iy = int(iCursorY-20)/H;
        if(ix >LINE_NUM-1)
        {
            //输出元件的位置不能插入非输出元件
            QMessageBox::information( this,"","非输出元件不能位于最后一列!  " ,"确定");
            return;//ix = LINE_NUM-1;
        }
        Element *pElementCur = cellArray[iy][ix].pElement;
        if( pElementCur != NULL)
        {
            this->releaseKeyboard();
            pNocDialog->setFocus();
            pNocDialog->exec();
            this->grabKeyboard();
            update();
        }

        break;
    }
    case Key_F2:     //" -|/|- "
    {
        int ix = int(iCursorX-10)/W;
        int iy = int(iCursorY-36)/H;
        if(ix >LINE_NUM-1)
        {
            //输出元件的位置不能插入非输出元件
            QMessageBox::information( this,"","非输出元件不能位于最后一列!  ","确定" );
            return;//ix = LINE_NUM-1;
        }
        Element *pElementCur = cellArray[iy][ix].pElement;
        if( pElementCur != NULL)
        {
            this->releaseKeyboard();
            pNccDialog->setFocus();
            pNccDialog->exec();
            this->grabKeyboard();
            update();
        }
        break;
    }
    case Key_F3:     //" -( )  "
    {
        int ix = int(iCursorX-10)/W;
                int iy = int(iCursorY-36)/H;
                if(ix >LINE_NUM-1)
                {
                    ix = LINE_NUM-1;
                }
                if(ix != LINE_NUM-1)
                {
                    QMessageBox::information( this,"","输出元件只能位于插入在最后一列!  " ,"确定");//codec->toUnicode(
                    return;
                }
                Element *pElementCur = cellArray[iy][ix].pElement;
                if( pElementCur != NULL && pElementCur->cName == QString("N") )
                {
                    this->releaseKeyboard();
                    pOutDialog->setFocus();
                    pOutDialog->exec();
                    this->grabKeyboard();
                    update();
                }
                break;
    }
    case Key_F4:     //" -(S)-  "
    {
        int ix = int(iCursorX-10)/W;
               int iy = int(iCursorY-36)/H;
               if(ix >LINE_NUM-1)
               {
                   ix = LINE_NUM-1;
               }
               Element *pElementCur = cellArray[iy][ix].pElement;

               if(ix != LINE_NUM-1)
               {
                   QMessageBox::information( this,"","输出元件只能位于插入在最后一列!  ","确定" );
                   return;
               }
               if( pElementCur != NULL && pElementCur->cName == QString("N") )
               {
                   this->releaseKeyboard();
                   pSetDialog->grabKeyboard();
                   pSetDialog->setFocus();
                   pSetDialog->exec();
                   this->grabKeyboard();
                   update();
               }
               break;
    }
    case Key_F5:     //"-(R)-"
    {
        int ix = int(iCursorX-10)/W;
               int iy = int(iCursorY-36)/H;
               if(ix >LINE_NUM-1)
               {
                   ix = LINE_NUM-1;
               }
               if(ix != LINE_NUM-1)
               {
                QMessageBox::information( this,"","输出元件只能位于插入在最后一列!  ","确定");
                   MESSAGEBOX("","输出元件只能位于插入在最后一列!",Information);
                   return;
               }
               Element *pElementCur = cellArray[iy][ix].pElement;
               if( pElementCur != NULL && pElementCur->cName == QString("N") )
               {
                   this->releaseKeyboard();
                   pRstDialog->setFocus();
                   pRstDialog->exec();
                   this->grabKeyboard();
                   update();
               }
               break;
    }
    case Key_F6:     //"  |   "
    {
        InsertBranchSlot();
        break;
    }
    case Key_F7:     //插入梯级
    {
        InsertRungSlot();
        break;
    }
    case Key_F8:     //"删除元件"
    {
        DeleteElementSlot();
        break;
    }
    case Key_F9:     //"删除分支"
    {
        DeleteBranchSlot();
        break;
    }
    case Key_F10:     //删除梯级
    {
        DeleteRungSlot();
        break;
    }
    case Key_Up:
    {
        if (bPaintOk == true && iButtonPage != 0)
        {
            if(iCursorY-H < iDisplayTop)	//如果向上一一格就离开了显示区
            {
                if(iRowCBIR+1 > pRungTop->iRungRow)	//如果向上一一格就离开了现在的梯级
                {
                    //设置前一梯级为顶梯
                    if(pRungTop->pPreRung != NULL)
                    {
                        pRungTop = pRungTop->pPreRung;
                        iRowCBIR = 1;
                        update();
                    }
                }
                else
                {
                    iRowCBIR++;
                    update();
                }
            }
            else
            {
                iCursorY -= H;
                update();
            }
        }
        break;
    }
    case Key_Down:
    {
        if ( bPaintOk == true && iButtonPage != 0)
        {
            if(iCursorY+H > iDisplayBottom)	//光标要移出界面底端了,光标位置不变,页面向上滚动一行
            {
                if(iRowCBIR== 1 )	//如果光标的移动使顶层梯级发生了变化
                {
                    if(pRungTop->pNextRung != NULL)
                    {
                        pRungTop = pRungTop->pNextRung;
                        iRowCBIR = pRungTop->iRungRow;
                        update();
                    }
                }
                else
                {
                    iRowCBIR--;
                    update();
                }
            }
            else
            {
                iCursorY += H;
                update();
            }
        }
        break;
    }
    case Key_Left:
    {
        if ( bPaintOk == true )
        {
    //		if(iCursorX-H > iDisplayLeft && iCursorX < iDisplayRight-4*W)
            if(iCursorX-H > iDisplayLeft)
            {
                iCursorX = iCursorX - W;
                update();
            }
    /*		else if(iCursorX > iDisplayRight-4*W)	//由输出元件往左移
            {
                iCursorX = 442;
                update();
            }
    */
    //		pLabelCNC->setText(QString("%1").arg(iCursorX));

        }//end of if(key == Key_Left)

        break;
    }
    case Key_Right:
    {
        if ( bPaintOk == true )
        {
    /*		if(iCursorX + W > iDisplayRight-4*W)	//移到输出元件的列
            {
                iCursorX = 556;//iDisplayRight-2*W+ 14;
                update();
            }
            else
            {
                iCursorX += W;
                update();
            }
    */
            if( iCursorX + W <= ((W/2+5)+W*(LINE_NUM-1)))
            {
                iCursorX += W;
                update();
            }
    //		pLabelCNC->setText(QString("%1").arg(iCursorX));

        }//end of if(key == Key_Right)

        break;
    }
    case Key_PageUp:
    {
        if( bPaintOk == true )
        {
            //思想：以梯级为单位向上翻动
            if( iButtonPage==1 || iButtonPage ==2 )	//插入分支时iButtonPage=0翻页键不可用
            {
                int iN = 11 - (pRungTop->iRungRow - iRowCBIR);	//要翻动的行数
                Rung *pRungTmp = pRungTop;
                while(pRungTmp->pPreRung != NULL)
                {
                    if(iN - pRungTmp->iRungRow >0)	//如果再向上翻还在行数之内，继续翻
                    {
                        iN = iN - pRungTmp->iRungRow;
                    }
                    else	//(iN - pRungTmp->iRungRow <0)
                    {
                        //如果再向上翻一个梯级就翻过了一页的行数，那么当前梯级为顶梯，
                        //最顶行在梯级内的位置为倒数行数为iN
                        pRungTop = pRungTmp;
                        iRowCBIR = iN;
                        goto resultUp;
                    }
                    pRungTmp = pRungTmp->pPreRung;
                }
                //程序执行到这个地方，说明是翻到了梯级的头指针
                pRungTop = pRungHead;
                iRowCBIR = pRungTop->iRungRow;
            resultUp:
                update();
            }//end of if(iButtonPage==1 && iButtonPage ==2)
        }	//end of if (key ==  Key_PageUp)

        break;
    }
    case Key_PageDown:
    {
        if( bPaintOk == true )
        {
            if( iButtonPage==1 || iButtonPage ==2 )	//插入分支时iButtonPage=0翻页键不可用
            {
                int iN = 11 - (pRungTop->iRungRow - iRowCBIR);	//要翻动的行数
                Rung *pRungTmp = pRungTop;
                while(pRungTmp->pNextRung != NULL)
                {
                    if(iN - pRungTmp->iRungRow >0)	//如果再向下翻还在行数之内，继续翻
                    {
                        iN = iN - pRungTmp->iRungRow;
                    }
                    else	//(iN - pRungTmp->iRungRow <0)
                    {
                        //如果再向下翻一个梯级就翻过了一页的行数，那么当前梯级为顶梯，
                        //最顶行在梯级内的位置为倒数行数为iN
                        pRungTop = pRungTmp;
                        iRowCBIR = iN;
                        goto resultDn;
                    }
                    pRungTmp = pRungTmp->pNextRung;
                }
                //程序执行到这个地方，说明是翻到了梯的尾巴
                pRungTop = pRungTmp;
                iRowCBIR = pRungTop->iRungRow;
            resultDn:
                update();
            }//end of if(iButtonPage==1 && iButtonPage ==2)
        }	//end of if (key ==  Key_PageDown)

        break;
    }
    case Key_Start:         //桌面版本没用到
    {
        emit sendCmdSignal(true);
        break;
    }
    case Key_Stop:         //桌面版本没用到
    {
        emit sendCmdSignal(false);
        break;
    }
    case Key_Enter:
    case Key_Return:
    {
        break;
    }
   default:
    {
        break;
    }
    }

}

void uiPlcEditor::paintEvent(QPaintEvent *event)
{
    bPaintOk = false;//开始画图/在此期间不响应键盘事件
    QRect rect = event->rect();
//    QPixmap *pixmap = new QPixmap(rect.width(), rect.height(), -1, QPixmap::DefaultOptim );
    QPixmap *pixmap = new QPixmap(rect.width(), rect.height() );

//    qDebug()<<"rect.x() == "<<rect.x()<<endl;
//    qDebug()<<"rect.y()== "<<rect.y()<<endl;
//    qDebug()<<"rect.width() == "<<rect.width()<<endl;
//    qDebug()<<"rect.height()== "<<rect.height()<<endl;

    pixmap->fill(Qt::white);
    QPainter p;
    p.begin(pixmap);
    p.setFont(QFont(PAINTER_FONT_FAMILY, PAINTER_FONT_SIZE,PAINTER_FONT_WEIGHT,false));
    //p.translate(-rect.x(), -rect.y());
    //p.setClipRect(10,36,640,409);
    p.translate(80,80);//(-rect.x(), -rect.y());//若想换更大的屏，则此处应该要改，
                                                //现在是定死的数字，要改进
    p.setClipRect(10,0,700,460);
    //清空界面数组
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<LINE_NUM; j++)
        {
            cellArray[i][j].pRung =NULL;
            cellArray[i][j].pNode =NULL;
            cellArray[i][j].pElement =NULL;
        }
    }
    //计算每个梯级所在的行数和整个梯的总行数		/这样太浪费资源了！,
    int iRungRowSum = 0;
    Rung *pRungTmp1 = pRungHead;
    while(pRungTmp1 != NULL)
    {
        pRungTmp1->iRungRowNum = iRungRowSum;
        iRungRowSum += pRungTmp1->iRungRow;
        pRungTmp1 = pRungTmp1->pNextRung;
    }

    //此时梯级所在的行数正确，iRungRowSum 为整个梯型结构的总行数

    //计算顶行梯级第一行的坐标/有可能在显示区外面
    int iyd = iDisplayTop-H*(pRungTop->iRungRow - iRowCBIR);
    //画梯形图
    Rung *pRungTmp = pRungTop;

    while(pRungTmp != NULL && iyd < iDisplayBottom) //一值画到梯结束或画到显示区外
    {
        Node *pNode = pRungTmp->pNodeRoot;
        pRungDraw = pRungTmp;		//画图时的当前梯级
        p.drawLine(10,iyd-13,10,iyd+(pRungDraw->iRungRow)*H);	//画梯级的母线

        //画行号
        int iydt = iyd+30;
        int iRungRowNum = pRungDraw->iRungRowNum;
        for(int i=0; i<pRungDraw->iRungRow; i++)
        {
            QString table =( QString("%1").arg( iRungRowNum ) ).rightJustified(2,'0',false);//保证行号四个数字的宽度，不足前面补零
            QPoint p1(635,iydt);
            p.setPen(Qt::magenta);
            p.drawText(p1,table);
            p.setPen(Qt::black);
            iydt += H;
            iRungRowNum ++;
        }
        //画梯级
        DarwNode(pNode,&p,10,iyd);
        iyd = iyd + H*(pRungTmp->iRungRow);
        pRungTmp = pRungTmp->pNextRung;
    }
    /*********************************************************************
    *计算滑块的位置 / 画滚动条
    * iRowCursor = pRungC->iRungRowNum + iRowCursorInRung;
    * 其中:iRowCursor:光标所在行在整个梯的行数
    *      pRungC->iRungRowNum:光标所在梯级第一行所在整个梯的行数
    *      iRowCursorInRung(iRCIR)：光标在当前梯级的内部的行数
    ***********************************************************************/
    //得到光标位置对应的界面数组下标
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungC = cellArray[iy][ix].pRung;
    //计算iRowCursorInRung(iRCIR)：光标在当前梯级的内部的行数
    if(pRungC != NULL)
    {
        int iRCIR = 0;
        if(pRungC->iRungRow ==1)	//梯级只占一行时
        {
            iRCIR = 1;
        }
        else
        {
            int iyTmp = iy;
            while(iyTmp >=0 && cellArray[iyTmp][ix].pRung == pRungC)
            {
                iRCIR ++;
                iyTmp --;
            }
            if(iyTmp < 0)
            {
                /***********************************************************
                *此时pRungC是显示区域的最顶梯级，且只显示了iRowCBIR行
                *还要上移pRungC->iRungRow-iRowCBIR行才到达pRungC的第一行
                ************************************************************/
                iRCIR += ( pRungC->iRungRow-iRowCBIR );
            }
        }//end of else (pRungC->iRungRow ==1)
        int iRowCursor = pRungC->iRungRowNum + iRCIR;
        iySlider = int(double(iRowCursor)*420/iRungRowSum +55);
        if(iySlider > 424)	//滑块的最大坐标是426
        {
            iySlider = 424;
        }
        if(pRungC == pRungHead && iRCIR==1)	//梯级的首行，滑块在最顶上
        {
            iySlider = 36;
        }
        if(iRungRowSum <11)	//梯的总行数小于一页时不显示滑块
        {
            iySlider = -20;
        }

    }//end of if(pRungC != NULL)
    QBrush brush1(Qt::gray,Qt::SolidPattern);
    p.setBrush(brush1);
    p.drawRect(620,36,8,402);	//画滑块槽
    //p.setBrush(brush2);
    //画滑块
    p.drawRect(617,iySlider,14,14);
    //画光标
    QBrush brush2(Qt::yellow,Qt::SolidPattern);
    p.setBrush(brush2);
    p.drawRect(iCursorX,iCursorY,10,15);

    //在监控模式下，要高亮显示状态有效的状态量
    QBrush brush3(Qt::green,Qt::SolidPattern);	//高亮显示颜色
    QBrush brush4(Qt::red,Qt::SolidPattern);	//异常颜色
    if (bMonitor)
    {
        GetElementName();	//获取各单元格的元件编码
        p.setBrush(brush3);
        for ( char row=0; row<11; row++ )
        {
            for ( char col=0; col<10; col++ )
            {
                unsigned short int ElementCode = ElementName[row][col];
                switch ( ElementCode & 0x0F00 )
                {
                case 0x0000:	//该格处不存在基本元件
                    break;
                case 0x0100:	//X
                    {
                        unsigned short int ElementNumber = ( ElementCode & 0x00FF );
                        if ( ElementNumber > 16 )	//目前支持16个，超过则溢出
                        {
                            bOverflow = true;
                            p.setBrush(brush4);
                            p.drawRect(35+W*col,55+H*row,10,15);
                            p.setBrush(brush3);
                            break;
                        }
                        if ( (ElementCode & 0x1000) == 0 )	//常开触点
                        {
//                            if ( (Data_PLC.plc_input >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        else						//常闭触点
                        {
//                            if ( ((Data_PLC.plc_input >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        break;
                    }
                case 0x0200:	//Y
                    {
                        unsigned short int ElementNumber = ( ElementCode & 0x00FF );
                        if ( ElementNumber > 16 )		//目前支持16个，超过则溢出
                        {
                            bOverflow = true;
                            p.setBrush(brush4);
                            p.drawRect(35+W*col,55+H*row,10,15);
                            p.setBrush(brush3);
                            break;
                        }
                        if ( (ElementCode & 0x1000) == 0 )	//常开触点
                        {
//                            if ( (Data_PLC.plc_output >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        else						//常闭触点
                        {
//                            if ( ((Data_PLC.plc_output >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        break;
                    }
                case 0x0300:	//M，支持64个，分存于Data_PLC.plc_M和Data_PLC.plc_W
                    {
                        unsigned short int ElementNumber = ( ElementCode & 0x00FF );
                        if ( ElementNumber > 64 )	//溢出
                        {
                            bOverflow = true;
                            p.setBrush(brush4);
                            p.drawRect(35+W*col,55+H*row,10,15);
                            p.setBrush(brush3);
                            break;
                        }
                        if ( ElementNumber < 32 )	//M0--M31
                        {
                            if ( (ElementCode & 0x1000) == 0 )	//常开触点
                            {
//                                if ( (Data_PLC.plc_M >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                                {
//                                    p.drawRect(35+W*col,55+H*row,10,15);
//                                }
                            }
                            else						//常闭触点
                            {
//                                if ( ((Data_PLC.plc_M >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                                {
//                                    p.drawRect(35+W*col,55+H*row,10,15);
//                                }
                            }
                        }
                        else						//M32--M63
                        {
                            if ( (ElementCode & 0x1000) == 0 )	//常开触点
                            {
//                                if ( (Data_PLC.plc_Warning >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                                {
//                                    p.drawRect(35+W*col,55+H*row,10,15);
//                                }
                            }
                            else						//常闭触点
                            {
//                                if ( ((Data_PLC.plc_Warning >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                                {
//                                    p.drawRect(35+W*col,55+H*row,10,15);
//                                }
                            }
                        }
                        break;
                    }
                case 0x0400:	//C
                    {
                        unsigned short int ElementNumber = ( ElementCode & 0x00FF );
                        if ( ElementNumber > 16 )		//目前支持16个，超过则溢出
                        {
                            bOverflow = true;
                            p.setBrush(brush4);
                            p.drawRect(35+W*col,55+H*row,10,15);
                            p.setBrush(brush3);
                            break;
                        }
                        if ( (ElementCode & 0x1000) == 0 )	//常开触点
                        {
//                            if ( (Data_PLC.plc_C >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        else						//常闭触点
                        {
//                            if ( ((Data_PLC.plc_C >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        break;
                    }
                case 0x0500:	//T
                    {
                        unsigned short int ElementNumber = ( ElementCode & 0x00FF );
                        if ( ElementNumber > 16 )		//目前支持16个，超过则溢出
                        {
                            bOverflow = true;
                            p.setBrush(brush4);
                            p.drawRect(35+W*col,55+H*row,10,15);
                            p.setBrush(brush3);
                            break;
                        }
                        if ( (ElementCode & 0x1000) == 0 )	//常开触点
                        {
//                            if ( (Data_PLC.plc_T >> ElementNumber) & 0x00000001 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        else						//常闭触点
                        {
//                            if ( ((Data_PLC.plc_T >> ElementNumber) & 0x00000001) == 0 )	//该格处元件状态有效
//                            {
//                                p.drawRect(35+W*col,55+H*row,10,15);
//                            }
                        }
                        break;
                    }
                default:		//异常
                    break;
                }
            }
        }
    }
    //***************************************************
    //**为论文作准备,画屏幕的小网格
    //**
    p.translate(iDisplayLeft,iDisplayTop);
    p.setPen(Qt::DashDotDotLine);
    p.setPen(Qt::blue);
    if(inet == 1)
    {
        for(int i=0;i<11;i++)
        {
            p.drawLine(0,i*H,455+3*W,i*H);		//横线
        }
        for(int i=0;i<16;i++)
        {
            p.drawLine(i*W,0,i*W,408);		//竖线
        }
    }
    //p.translate(-iDisplayLeft,-iDisplayTop);

    p.end();
//    bitBlt(this, rect.x(), rect.y(), pixmap,0,0,
//                rect.width(), rect.height());
    QPainter painter(this);
    //painter.scale(1,520.0/400);
    painter.drawPixmap(rect, *pixmap, rect);

    delete pixmap;
    bPaintOk = true;

}	//end of paintEvent


//读取指令表，形成树形结构
void uiPlcEditor::FormLadder(char *cFileName)
{
    //从文件里读指令，形成树形结构
    pRungHead=ShapeLadder( cFileName);	//返回梯的树形结构的头指针

    if(pRungHead == NULL)//如果文件中没有指令，新建一个空梯级
    {
        //QTextCodec *codec=QTextCodec::codecForName("gbk");
        //QMessageBox::critical( this, "",codec->toUnicode("文件读取错误或原文件为空。"),codec->toUnicode("确定"));
        //MESSAGEBOX("","文件读取错误或原文件为空。",Critical);
        qDebug()<<tr("文件读取错误或原文件为空。");
        //新建一含有10个空元件的梯级
        Rung *pRungInsert = new Rung;
        Node *pNode = new Node(1);	//新建一空AND节点作为新梯级的根节点
        for(int i=0; i<10; i++)
        {
            Element *pElementInsert=new Element(QString("N"), 0,0,0);
            pNode->AppendLink(pElementInsert);
        }
        pNode->iNodeRow = 1;
        pNode->iNodeColumn = 10;
        pNode->pRung = pRungInsert;
        pRungInsert->pNodeRoot = pNode;
        pRungInsert->iRungRow = pNode->iNodeRow;

        pRungHead = pRungInsert;
    }
    //计算每个梯级及其所有的节点的行列数 //添加空元件，为画图作准备
    Rung *pRung = pRungHead;
    //Rung *pRung2 = pRung;		//测试
    while (pRung!=NULL)
    {
        Node *pNodeCur = pRung->pNodeRoot;
        ResizeNode(pNodeCur);	//别以为这样写多余，很有必要！ 两次ResizeNode，PoiseNode(pNodeCur)
        pNodeCur->iNodeColumn = 10;
        PoiseNode(pNodeCur);
        ResizeNode(pNodeCur);
        pNodeCur->iNodeColumn = 10;
        PoiseNode(pNodeCur);
        //Rung pRung2 = pRung;
        pRung = pRung->pNextRung;
    }
    /*************
    //测试

    Node *pNode1 = pRung2->pNodeRoot;
    DisposeNode(pNode1);
    *************/
    pRung = NULL;

}

void uiPlcEditor::GetElementSignifiation(char *cFileName)
{
    QFile fileName(cFileName);
    if( !fileName.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        QMessageBox::information( this,"","配置文件读取错误！ ",	"确定");
        return;
    }
    QTextStream fileStream( &fileName );
    //QT版本3转4不兼容处
    //fileStream.setEncoding(QTextStream::Unicode);
    fileStream.setAutoDetectUnicode(true);

    QString strTmp="";
    for(int i = 0; i<XNUM+YNUM+MNUM; i++)
    {
        if( fileStream.atEnd() )
        {
            break;
        }
        strTmp=fileStream.readLine();
        if(strTmp.left(1)=="%")
        {
            break;
        }
        asESign[i]=strTmp.left(LENGTH*2);
    }
      fileName.close();
    /*
    QTextCodec *codec=QTextCodec::codecForName("gbk")	;
    FILE *fp;
    fp = fopen(cFileName,"rb");
    if(fp == NULL)
    {
        QMessageBox::information( this,"",codec->toUnicode("输出元件含义文件读取错误！ "),codec->toUnicode("确定"));
        return;
    }

  for(int i = 0; i<XNUM+YNUM+MNUM;i++)
    {
    QChar c[LENGTH];
    if( fread( c,sizeof(QChar[LENGTH]),1,fp) != 1)
    {
        QMessageBox::information( this,"",codec->toUnicode("输出元件含义文件读取错误！ "),codec->toUnicode("确定"));
            return;
    }
    asESign[i] = QString(c,LENGTH);
  }//end of for
  fclose(fp);
  */

}

int uiPlcEditor::CheckLadder(Rung *)
{
    QTextCodec *codec=QTextCodec::codecForName("gbk")	;
    /*******************************
    *语法检查的内容包括
    *	1，梯级必须有输出
    *	2，根节点输出分支or最后
    *	不包括逻辑检查
    *******************************/
    //去掉空元件
    Rung *pRungTmp = pRungHead;
    while(pRungTmp != NULL)
    {
        Node *pNodeRoot = pRungTmp->pNodeRoot;
        RebuildNode(pNodeRoot);//删除空元件
        pNodeRoot = pRungTmp->pNodeRoot;
        if( CheckNodeAndOut(pNodeRoot) != 0)
        {
            int iWrongRungNum = pRungTmp->iRungRowNum;
            //还原
            //RebuildNode(pNodeRoot);
            pNodeRoot->iNodeColumn = LINE_NUM;
            PoiseNode(pNodeRoot);
            ResizeNode(pNodeRoot);
            pNodeRoot->iNodeColumn = LINE_NUM;
            PoiseNode(pNodeRoot);
            ResizeNode(pNodeRoot);

            //初始光标位置在显示区域的左上角
            iCursorX = W/2+5; // 10+3*W/8;
            iCursorY = 55; //20+H/2;
            ixFirst = -1;	//插入分支的第一点未选中
            iyFirst = -1;
            pRungTop=pRungTmp;	//初始化时第一行显示的是梯级的头指针
            iRowCBIR=pRungTmp->iRungRow;//....的倒数最后一行
            update();

            QString table;
            if(iWrongRungNum <LINE_NUM)
            {
                table=QString("%1%2%3%4").arg(0).arg(0).arg(0).arg( iWrongRungNum );
            }
            else if(iWrongRungNum > 9 && iWrongRungNum < 100)
            {
                table=QString("%1%2%3").arg(0).arg(0).arg( iWrongRungNum );
            }
            else if( iWrongRungNum>99 &&iWrongRungNum < 10000)
            {
                table=QString("%1%2").arg(0).arg( iWrongRungNum );
            }
            else
            {
                table=QString("%1").arg( iWrongRungNum );
            }

            QMessageBox::critical( this, "",QString("%1%2%3").arg("梯级").arg( table ).arg("语法错误 !   \n"),"确定");

//            MESSAGEBOX("",(QString("%1%2%3").arg(codec->toUnicode("梯级")).arg( table ).arg(codec->toUnicode("语法错误 !   \n"))).toUtf8(),Critical);
//            return -1;
        }
        //还原
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);

        pRungTmp=pRungTmp->pNextRung;
    }
    return 0;

}

void uiPlcEditor::DarwNode(Node *pNode, QPainter *p, int x, int y)
{
    /**************************************************************
    *画节点思想:
    * 1,用（x,y）接收函数的输入坐标（xNext，yNext）是pNode的画图起始点
    *２,根据节点的类型，和分支节点或元件确定下一个画点放入（xNext，yNext），
    *３,画分之节点（调用自己）或元件( 调用DrawElement() )
    ***************************************************************/
    NodeLink *pNodeLink = pNode->pNodeLinkSon;
    if(pNode->iNodeOperate==1)//如果为and节点
    {
        while(pNodeLink != NULL)
        {
            if(pNodeLink->pElementBlew != NULL)
            {
                if(y>=iDisplayTop && y<iDisplayBottom )	//在显示区内时画之
                {
                    DrawElement(pNodeLink->pElementBlew, p,x,y);
                }
                //计算出一个单元的画点/
                x = x + W;
                y = y;
            }	//end of if(pNodeLink->pElementBlew != NULL)
            else if(pNodeLink->pNodeBlew != NULL)
            {
                Node *pNodeTmp = pNodeLink->pNodeBlew;
                if (pNodeTmp->iNodeOperate == 2)	//or节点
                {
                    DarwNode(pNodeTmp, p,x,y);
                    x = x + W*(pNodeTmp->iNodeColumn);
                    y = y;
                }//end of	else if (pNodeTmp->iNodeOperate = 2)
            }	//end of else if(pNodeLink->pNodeBlew != NULL)
            pNodeLink = pNodeLink->pNodeLinkRight;
        }//end of while
    }//end of //如果为and节点
    else if(pNode->iNodeOperate==2)//如果为or节点
    {

        while(pNodeLink != NULL)
        {
            //画or节点的"母线	"
            /******************************************
            *or节点的第一个分支没有＂母线＂
            *其它分支根据上一分支确定分支母线的长度，
            *根据or节点的列数确定第二条母线的横坐标
            *
            *******************************************/

            p->translate(x,y);
            if(pNodeLink->pNodeLinkLeft != NULL)
            {
                NodeLink *pNodeLinkLeft = pNodeLink->pNodeLinkLeft;
                if(pNodeLinkLeft->pElementBlew != NULL)	//or的分支为元件
                {
                    int ik = (pNode->iNodeColumn)*W;
                    p->drawLine(0,-13,0,25);
                    if(x+ik<470)	// >470时就是含有输出元件的or节点了,第二条竖线不画
                    {
                        p->drawLine(ik,-13,ik,25);//此处pNode->iNodeColumn=1,这样写以防万一
                    }
                }//end of if(pNodeLinkLeft->pElement != NULL)
                else if(pNodeLinkLeft->pNodeBlew != NULL)	//or的分支为and节点
                {
                    Node *pNodeTmp = pNodeLinkLeft->pNodeBlew;
                    int ik = (pNode->iNodeColumn)*W;
                    int im = (pNodeTmp->iNodeRow-1)*H;
                    p->drawLine(0,-13-im,0,25);
                    if(x+ik<470)	// >470时就是含有输出元件的or节点了,第二条竖线不画
                    {
                        p->drawLine(ik,-13-im,ik,25);
                    }
                }	//end of else if(pNodeLinkLeft->pNodeBlew != NULL)
            }//end of if(pNode->pNodeLinkFather->pNodeLinkLeft != NULL)
            p->translate(-x,-y);


            //画分支的内容
            if(pNodeLink->pElementBlew != NULL)
            {
                if(y>=iDisplayTop && y<iDisplayBottom )	//在显示区内时画之
                {
                    DrawElement(pNodeLink->pElementBlew, p,x,y);
                }
                x = x;
                y = y + H;
            }
            else if(pNodeLink->pNodeBlew != NULL)
            {
                Node *pNodeTmp = pNodeLink->pNodeBlew;
                if(pNodeTmp->iNodeOperate == 1)
                {
                    DarwNode(pNodeTmp, p,x,y);
                    x = x;
                    y = y + H*(pNodeTmp->iNodeRow);
                }
            }	//end of else if(pNodeLink->pNodeBlew != NULL)

            pNodeLink = pNodeLink->pNodeLinkRight;
        }//end of while
    }	//end of if如果为or节点

}

void uiPlcEditor::DrawElement(Element *pElement, QPainter *p, int x, int y)
{
    QString MExplain[15] = {"  UDP   ",
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

        QTextCodec *codec=QTextCodec::codecForName("UTF-8")	;
        //定义图上元件的几个画图点的相对坐标
        QPoint p1(0,25);
        QPoint p2(W/2-5,25);
        QPoint p3(W/2+5,25);
        QPoint p4(W,25);
        QPoint p5(W/2-5,19);
        QPoint p6(W/2-5,32);
        QPoint p7(W/2+5,19);
        QPoint p8(W/2+5,32);
        QPoint p9(W/2-18,15);

        //计算画点对应的界面数组坐标
        int i = (y-36)/H;	//行
        int j = (x-10)/W;	//列

        if(j>LINE_NUM-1)
        {
            j=LINE_NUM-1;
        }
        //把当前元件的所在梯级\父节点\元件值赋给相对应得界面数组
        if(cellArray[i][j].pRung ==NULL )
        {
            for(int ix=0; ix<10 ;ix++)
            {
                cellArray[i][ix].pRung = pRungDraw;
            }
        }
        cellArray[i][j].pNode = pElement->pElementFather->pNodeLinkFather;
        cellArray[i][j].pElement =pElement;
        //画图
        p->translate(x,y);

        QString table1 = QString("%1").arg(pElement->iNum);
        QString table;
        if(pElement->cName == QString("C") || pElement->cName == QString("T"))
        {
            table = QString("%1%2").arg(pElement->cName).arg(table1.rightJustified(2,'0',false));
        }
        else if(pElement->cName == QString("M")&&pElement->iNum<15)
        {
            table = QString("%1").arg(MExplain[pElement->iNum]);
        }
        else
        {
            table = QString("%1%2").arg(pElement->cName).arg(table1.rightJustified(3,'0',false));
        }
        if(pElement->iState == 0 || pElement->iState == 1)	//非输出类元件
        {
            if(pElement->cName==QString("N"))	//空元件画横线/这就是设置空元件的一个很重要的目的
            {

                if(j<LINE_NUM-1)	//非输出元件的位置,非最后一列
                {
                    p->drawLine(p1,p4);
                }
                else	//输出元件被删除或未被添加的情况 /输出元件占三个单元格！
                {
                    p->drawLine(0,25,30,25);
                //	p->drawLine(p1,p4);
                }
                p->translate(-x,-y)	;
                return;
            }
            p->drawLine(p1,p2);
            p->drawLine(p3,p4);
            p->drawLine(p5,p6);
            p->drawLine(p7,p8);
            if(pElement->iState == 1)	//常闭触点
            {
                p->drawLine(p6,p7);
            }

            if(pElement->cName == QString("M")&&pElement->iNum<15)
            {
                p->translate(-10,0);
                p->drawText(p9,table);
                p->translate(10,0);
            }
            else
                p->drawText(p9,table);
        }
        else	//输出类元件
        {
        //	p->translate(76,0);

            //输出元件代表的意义
            QString table1;
            if(pElement->cName==QString("Y"))
            {
                table1 = asESign[XNUM+pElement->iNum];
            }
            else if(pElement->cName==QString("M"))
            {
                table1 = asESign[XNUM+YNUM+pElement->iNum];
            }
            else if(pElement->cName==QString("C"))
            {
                table1 = QString(tr("计数器"));
            }
            else if(pElement->cName==QString("T"))
            {
                table1 = QString(tr("定时器"));
            }
            p->setPen(Qt::black);
            p->drawText(-55,20,table1);//QPainter::RTL);

            //画线圈椭圆
            p->drawLine(0,25,15,25);
            p->drawEllipse(15,17,28,16);

            p->setPen(Qt::blue);
            if(pElement->iState == 3)	//set
            {
                p->drawText(36,30,QString("S"));
            }
            else if(pElement->iState == 4)	//rst
            {
                p->drawText(36,30,QString("R"));
            }
            p->setPen(Qt::black);

            if (pElement->iState == 2 && ( pElement->cName==QString("C") || pElement->cName==QString("T") ) )
            {
                QString tablex = QString("%1").arg(pElement->iPara).rightJustified(4,'0',false);
                QString table2 =QString("%1%2").arg(QString("K")).arg(tablex);

                p->setPen(Qt::blue);
                p->drawText(36,30,table2);
                p->setPen(Qt::black);
            }

            if(pElement->cName == QString("M")&&pElement->iNum<15)
            {
                p->translate(-10,0);
                p->drawText(p9,table);
                p->translate(10,0);
            }
            else
                p->drawText(p9,table);
        //	p->translate(-76,0);
        }
        p->translate(-x,-y);
}



void uiPlcEditor::whichIsActive(int buttonGroup, int num)
{
//    if (buttonGroup<0 || buttonGroup>2 || num < 0 || num > 7) //插入分支时buttonGroup==0
//    {
//        qDebug()<<"whichIsActive() bad paras.";
//        return;
//    }

//    switch (buttonGroup) {
//    case 0:
//    case 1:
//        popButton_one_slot(num);
//        break;
//    case 2:
//        popButton_two_slot(num);
//        break;
//    default:
//        break;
//    }
}

void uiPlcEditor::popButton_one_slot(int num)
{
//    qDebug()<<"1button="<<num;
//    switch (num)
//    {
//    case 0:         //"-| |-"
//    {
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-20)/H;
//        if(ix >LINE_NUM-1)
//        {
//            //输出元件的位置不能插入非输出元件
//            //QMessageBox::information( this,"",codec->toUnicode("非输出元件不能位于最后一列!  ") ,codec->toUnicode("确定"));
//            MESSAGEBOX("","非输出元件不能位于最后一列!",Information);
//            return;//ix = LINE_NUM-1;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;
//        if( pElementCur != NULL)
//        {
//            this->releaseKeyboard();
//            pNocDialog->grabKeyboard();
//            //pNocDialog->setFocus();
//            pNocDialog->exec();
//            this->grabKeyboard();
//            update();
//        }

//        break;
//    }
//    case 1:         //" -|/|- "
//    {
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-36)/H;
//        if(ix >LINE_NUM-1)
//        {
//            //输出元件的位置不能插入非输出元件
//            //QMessageBox::information( this,"",codec->toUnicode("非输出元件不能位于最后一列!  "),codec->toUnicode("确定") );
//            MESSAGEBOX("","非输出元件不能位于最后一列!",Information);
//            return;//ix = LINE_NUM-1;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;
//        if( pElementCur != NULL)
//        {
//            this->releaseKeyboard();
//            pNccDialog->grabKeyboard();
//            pNccDialog->exec();
//            this->grabKeyboard();
//            update();
//        }
//        break;
//    }
//    case 2:         //" -( )  "
//    {
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-36)/H;
//        if(ix >LINE_NUM-1)
//        {
//            ix = LINE_NUM-1;
//        }
//        if(ix != LINE_NUM-1)
//        {
//            //QMessageBox::information( this,"",codec->toUnicode("输出元件只能位于插入在最后一列!  ") ,codec->toUnicode("确定"));
//            MESSAGEBOX("","输出元件只能位于插入在最后一列!",Information);
//            return;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;
//        if( pElementCur != NULL && pElementCur->cName == QString("N") )
//        {
//            this->releaseKeyboard();
//            pOutDialog->grabKeyboard();
//            //pOutDialog->setFocus();
//            pOutDialog->exec();
//            this->grabKeyboard();
//            update();
//        }
//        break;
//    }
//    case 3:         //" -(S)-  "
//    {
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-36)/H;
//        if(ix >LINE_NUM-1)
//        {
//            ix = LINE_NUM-1;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;

//        if(ix != LINE_NUM-1)
//        {
//            //QMessageBox::information( this,"",codec->toUnicode("输出元件只能位于插入在最后一列!  "),codec->toUnicode("确定") );
//            MESSAGEBOX("","输出元件只能位于插入在最后一列!",Information);
//            return;
//        }
//        if( pElementCur != NULL && pElementCur->cName == QString("N") )
//        {
//            this->releaseKeyboard();
//            pSetDialog->grabKeyboard();

//            pSetDialog->exec();
//            this->grabKeyboard();
//            update();
//        }
//        break;
//    }
//    case 4:         //"-(R)-"
//    {
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-36)/H;
//        if(ix >LINE_NUM-1)
//        {
//            ix = LINE_NUM-1;
//        }
//        if(ix != LINE_NUM-1)
//        {
//            //QMessageBox::information( this,"",codec->toUnicode("输出元件只能位于插入在最后一列!  "),codec->toUnicode("确定"));
//            MESSAGEBOX("","输出元件只能位于插入在最后一列!",Information);
//            return;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;
//        if( pElementCur != NULL && pElementCur->cName == QString("N") )
//        {
//            this->releaseKeyboard();
//            pRstDialog->grabKeyboard();

//            pRstDialog->exec();
//            this->grabKeyboard();
//            update();
//        }
//        break;
//    }
//    case 5:         //" |   "
//        InsertBranchSlot();
//        break;
//    case 6:         //"删除元件"
//        DeleteElementSlot();
//        break;
//    case 7:         //">>"
////        setCurButton(2);
//        break;
//    default:
//        break;
//    }
}

void uiPlcEditor::popButton_two_slot(int num)
{
//    qDebug()<<"2button="<<num;
//    switch (num)
//    {
//    case 0:         //插入梯级
//        InsertRungSlot();
//        break;
//    case 1:         //删除分支
//        DeleteBranchSlot();
//        break;
//    case 2:         //删除梯级
//        DeleteRungSlot();
//        break;
//    case 3:         //"设置参数"
//    {
//        return;
//        int ix = int(iCursorX-10)/W;
//        int iy = int(iCursorY-36)/H;
//        if(ix >LINE_NUM-1)
//        {
//            ix = LINE_NUM-1;
//        }
//        Element *pElementCur = cellArray[iy][ix].pElement;

//        if(ix != LINE_NUM-1 )
//        {
//            //QMessageBox::information( this,"",codec->toUnicode("只有输出元件才可以设置参数!  ") ,codec->toUnicode("确定"));
//            MESSAGEBOX("","只有输出元件才可以设置参数!",Information);
//            return;
//        }
//        if( pElementCur != NULL && (pElementCur->cName == QString("C")||pElementCur->cName == QString("T")||pElementCur->cName == QString("N")))
//        {
//            return;
//        }
//        else if(pElementCur != NULL)
//        {
//            QString strT1 = QString("%1%2%3").arg(pElementCur->cName).arg(pElementCur->iNum).arg(tr("的参数配置!  "));
//            QString strT2;
//            if(pElementCur->cName==QString("Y"))
//            {
//                strT2 =asESign[XNUM+pElementCur->iNum];
//            }
//            else if(pElementCur->cName==QString("M"))
//            {
//                strT2 = asESign[XNUM+YNUM+pElementCur->iNum];
//            }
//            pMDialog->pExplainLabe->setText(strT1);
//            pMDialog->pLineEdit->setText(strT2);
//            pMDialog->exec();
//            update();
//        }
//        break;
//    }
//    case 4:         //"保存"
//        iButtonPage =0;
//        SaveButtonSlot();
//        update();
//        iButtonPage =2;
//        break;
//    case 5:         //"加载出厂设置"
//    {
//        return;
//        /*
//        switch( QMessageBox::warning( this, "",
//            codec->toUnicode("如果载入出厂设置，当前编辑内容将会丢失!\n载入后，若退出时不保存，则载入前最后一次保存的结果不受影响。\n是否载入?"),
//            codec->toUnicode("确定"), codec->toUnicode("取消"),0,1 ) )
//        */
//        QMessageBox mb( "",
//            tr("如果载入出厂设置，当前编辑内容将会丢失!\n载入后，若退出时不保存，则载入前最后一次保存的结果不受影响。\n是否载入?"),
//            QMessageBox::NoIcon,
//            QMessageBox::Yes,
//            QMessageBox::No| QMessageBox::Default ,QMessageBox::NoButton ,this);
//        mb.setFont(MESSAGEBOX_FONT);
//        mb.setButtonText(QMessageBox::Yes,tr("&Y确定"));
//        mb.setButtonText(QMessageBox::No,tr("&D取消"));
//        switch(mb.exec())
//        {
//            case (QMessageBox::Yes):
//            {
//                ReloadButtonSlot();
//                break;
//            }
//            case (QMessageBox::No):
//            {
//                //do nothing;
//                break;
//            }
//        }	//end of switch
//        break;
//    }
//    case 6:         //"退出"
//    {
//        QMessageBox msgBox(this);
//        msgBox.setWindowTitle(tr("您应该知道"));
//        msgBox.setText(tr("退出前请保存!"));
//        msgBox.setInformativeText(tr("是否退出？"));
//        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
//        msgBox.setDefaultButton(QMessageBox::Yes);
//        msgBox.setButtonText(QMessageBox::Yes, tr("&Y确定"));
//        msgBox.setButtonText(QMessageBox::No, tr("&D取消"));
//        msgBox.setIcon(QMessageBox::NoIcon);
//        msgBox.grabKeyboard();
//        if (QMessageBox::Yes == msgBox.exec())
//        {
////            accept();
//        }
//        this->grabKeyboard();
//        repaint();
//        break;
//    }
//    case 7:         //"<<"
////        setCurButton(1);
//        break;
//    default:
//        break;
//    }
}

void uiPlcEditor::NocButtonSlot(QString &qsEstyle, int iENum)
{
    Element *pElementInsert = new Element(qsEstyle,iENum,0,0);

    //获得光标状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungCur = cellArray[iy][ix].pRung;
    Element *pElementCur = cellArray[iy][ix].pElement;
    Node *pNodeRoot = pRungCur->pNodeRoot;
    if(pElementCur != NULL)
    {
        if(pElementCur->cName != QString("N"))
        {
            InsertElementWithInNodeBack(pElementCur, pElementInsert);
        }
        else
        {
            NodeLink *pNodeLinkCur = pElementCur->pElementFather;
            pNodeLinkCur->pElementBlew = pElementInsert;
            pElementInsert->pElementFather = pNodeLinkCur;
            delete pElementCur;
        }

        //为了保险，以防万一，三合一
        RebuildNode(pNodeRoot);
        if(pNodeRoot->iNodeColumn >LINE_NUM)		//如果梯级的列数超过LINE_NUM,取消刚才插入的元件
        {
            DeleteElementWithInNode(pElementInsert);
            RebuildNode(pNodeRoot);
            //QTextCodec *codec=QTextCodec::codecForName("gbk");
            //QMessageBox::information(this, "",codec->toUnicode("行满，不能在此处插入元件。 "),codec->toUnicode("确定"));
            MESSAGEBOX("","行满，不能在此处插入元件。",Information);
        }

        pNodeRoot->iNodeColumn = LINE_NUM;//要反复两次才不会出问题！！
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        ///*不要删掉
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*/

        update();
    }

}

void uiPlcEditor::NccButtonSlot(QString &qsEstyle, int iENum)
{
    Element *pElementInsert = new Element(qsEstyle,iENum,1,0);

    //获得光标状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungCur = cellArray[iy][ix].pRung;
    Element *pElementCur = cellArray[iy][ix].pElement;
    Node *pNodeRoot = pRungCur->pNodeRoot;
    //int iRungRowO = pRungCur->iRungRow;
    if(pElementCur != NULL)
    {
        if(pElementCur->cName != QString("N"))
        {
            InsertElementWithInNodeBack(pElementCur, pElementInsert);
        }
        else
        {
            NodeLink *pNodeLinkCur = pElementCur->pElementFather;
            pNodeLinkCur->pElementBlew = pElementInsert;
            pElementInsert->pElementFather = pNodeLinkCur;
            delete pElementCur;
        }
        //为了保险，以防万一，三合一
        RebuildNode(pNodeRoot);
        if(pNodeRoot->iNodeColumn >LINE_NUM)		//如果梯级的列数超过LINE_NUM,取消刚才插入的元件
        {
            DeleteElementWithInNode(pElementInsert);
            RebuildNode(pNodeRoot);
            //QTextCodec *codec=QTextCodec::codecForName("gbk");
            //QMessageBox::information( this, "",codec->toUnicode("行满，不能在此处插入元件。"),codec->toUnicode("确定"));
            MESSAGEBOX("","行满，不能在此处插入元件。",Information);
        }

        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        ///*不要删掉
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*/
        update();
    }

}

void uiPlcEditor::OutButtonSolt(QString &qsEstyle, int iENum, int iPara)
{
    Element *pElementInsert = new Element(qsEstyle,iENum,2,iPara);
    //获得光标状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    if(ix != LINE_NUM-1)	//输出类元件必须在每行的最后一列插入
    {
        return;
    }
    Element *pElementCur = cellArray[iy][ix].pElement;
    Node *pNodeRoot = cellArray[iy][ix].pRung->pNodeRoot;

    if(pElementCur != NULL && pElementCur->cName ==QString("N"))
    {
        InsertElementWithInNodeBack(pElementCur, pElementInsert);

        RebuildNode(pNodeRoot);

        //如果梯级的列数超过LINE_NUM,取消刚才插入的元件		*对于输出类元件这一步没有必要,这样写增加健壮性
        if(pNodeRoot->iNodeColumn >LINE_NUM)
        {
            DeleteElementWithInNode(pElementInsert);
            RebuildNode(pNodeRoot);
            //QTextCodec *codec=QTextCodec::codecForName("gbk");
            //QMessageBox::information( this, "",codec->toUnicode("行满，不能在此处插入元件。"),codec->toUnicode("确定"));
            MESSAGEBOX("","行满，不能在此处插入元件。",Information);
        }
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*不要删掉
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*/
        update();
    }

}

void uiPlcEditor::SetButtonSlot(QString &qsEstyle, int iENum)
{
    Element *pElementInsert = new Element(qsEstyle,iENum,3,0);

    //获得光标状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    if(ix != LINE_NUM-1)	//输出类元件必须在每行的最后一列插入
    {
        return	;
    }
    Element *pElementCur = cellArray[iy][ix].pElement;
    Node *pNodeRoot = cellArray[iy][ix].pRung->pNodeRoot;


    if(pElementCur != NULL && pElementCur->cName ==QString("N") )
    {
        InsertElementWithInNodeBack(pElementCur, pElementInsert);
        RebuildNode(pNodeRoot);
        //如果梯级的列数超过LINE_NUM,取消刚才插入的元件		*对于输出类元件这一步没有必要,这样写增加健壮性
        if(pNodeRoot->iNodeColumn >LINE_NUM)
        {
            DeleteElementWithInNode(pElementInsert);
            RebuildNode(pNodeRoot);
            //QTextCodec *codec=QTextCodec::codecForName("gbk");
            //QMessageBox::information( this, "",codec->toUnicode("行满，不能在此处插入元件。"),codec->toUnicode("确定"));
            MESSAGEBOX("","行满，不能在此处插入元件。",Information);
        }
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        ///*不要删掉
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*/
        update();
    }

}

void uiPlcEditor::RstButtonSlot(QString &qsEstyle, int iENum)
{
    Element *pElementInsert = new Element(qsEstyle,iENum,4,0);

    //获得光标状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    if(ix != LINE_NUM-1)	//输出类元件必须在每行的最后一列插入
    {
        return;
    }
    Element *pElementCur = cellArray[iy][ix].pElement;
    Node *pNodeRoot = cellArray[iy][ix].pRung->pNodeRoot;

    if(pElementCur != NULL && pElementCur->cName ==QString("N") )
    {
        InsertElementWithInNodeBack(pElementCur, pElementInsert);
        RebuildNode(pNodeRoot);
        //如果梯级的列数超过LINE_NUM,取消刚才插入的元件		*对于输出类元件这一步没有必要,这样写增加健壮性
        if(pNodeRoot->iNodeColumn >LINE_NUM)
        {
            DeleteElementWithInNode(pElementInsert);
            RebuildNode(pNodeRoot);
            //QTextCodec *codec=QTextCodec::codecForName("gbk");
            //QMessageBox::information( this, "",codec->toUnicode("行满，不能在此处插入元件。"),codec->toUnicode("确定"));
            MESSAGEBOX("","行满，不能在此处插入元件。",Information);
        }
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        ///*不要删掉
        pNodeRoot->iNodeColumn = LINE_NUM;
        PoiseNode(pNodeRoot);
        ResizeNode(pNodeRoot);
        //*/
        update();
    }
}

  //删除元件	删除当前位置的节件，
void uiPlcEditor::DeleteElementSlot()
{
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungCur = cellArray[iy][ix].pRung;
    Element *pElement = cellArray[iy][ix].pElement;
    if(pElement != NULL && pElement->cName != QString("N"))
    {
        if(pElement->iState == 0 || pElement->iState == 1) //非输出元件
        {
            DeleteElementWithInNode(pElement);
            Node *pNode = pRungCur->pNodeRoot;
            int iRungRowO = pRungCur->iRungRow;
            RebuildNode(pNode);	//如果发生删除元件导致多输出分支都成为一个新的梯级的情况,这个函数可以处理
            pNode = pRungCur->pNodeRoot;
            pNode->iNodeColumn = LINE_NUM;
            PoiseNode(pNode);
            ResizeNode(pNode);
            //不要删掉
            pNode->iNodeColumn = LINE_NUM;
            PoiseNode(pNode);
            ResizeNode(pNode);
            //显示相关
            if(pRungCur == pRungTop &&pRungCur->iRungRow != iRungRowO)
            {
                //如果删除元件引起显示的最顶层梯级的行数发生变化,则显示完整梯级
                iRowCBIR = pRungCur->iRungRow;
            }
        }
        else	//输出元件用空元件取代输出元件的位置
        {
            Element *pElementR = new Element(QString("N"), 0, 0, 0);
            pElement->pElementFather->pElementBlew = pElementR;
            pElementR->pElementFather = pElement->pElementFather;
            delete pElement;
            pElement = NULL;
        }
        update();
    }	//end of if pElement != NULL && pElement->cName != QString("N")

}

//删除分支，	/删除当前分枝，不包括根节点
void uiPlcEditor::DeleteBranchSlot()
{
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungCur = cellArray[iy][ix].pRung;
    Node *pNode = cellArray[iy][ix].pNode;
    int iRungRowO = pRungCur->iRungRow;
    if(pNode != NULL)
    {
        if(pNode->iNodeOperate == 1 && pNode->pNodeFather != NULL)	//如果元件的父节点为不是根节点的and节点，删除
        {
            DeleteNodeWithInNode( pNode );
            Node *pNodeR = cellArray[iy][ix].pRung->pNodeRoot;
            RebuildNode(pNodeR);
            ResizeNode(pNodeR);
            pNodeR->iNodeColumn = LINE_NUM;
            PoiseNode(pNodeR);
            ///*不要删掉
            ResizeNode(pNodeR);
            pNodeR->iNodeColumn = LINE_NUM;
            PoiseNode(pNodeR);
            //*/
            //显示相关
            if(pRungCur == pRungTop &&pRungCur->iRungRow != iRungRowO)
            {
                iRowCBIR = pRungCur->iRungRow;
            }
            update();
        }
        else if(pNode->iNodeOperate == 2)	//如果元件的父节点为or节点，删除元件即可
        {
            DeleteElementWithInNode(cellArray[iy][ix].pElement);
            Node *pNodeR = cellArray[iy][ix].pRung->pNodeRoot;
            RebuildNode(pNodeR);
            ResizeNode(pNodeR);
            pNodeR->iNodeColumn = LINE_NUM;
            ResizeNode(pNodeR);
            ///*不要删掉
            pNodeR->iNodeColumn = LINE_NUM;
            PoiseNode(pNodeR);
            ResizeNode(pNodeR);
            //*/
            //显示相关
            if(pRungCur == pRungTop &&pRungCur->iRungRow != iRungRowO)
            {
                iRowCBIR = pRungCur->iRungRow;
            }
            update();
        }
    }	//end of if(pNode != NULL)

}

//插入梯级，	/在当前梯级后插入梯级
void uiPlcEditor::InsertRungSlot()
{
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    if(cellArray[iy][ix].pElement != NULL)//空位置不能响应操作
    {
        //新建一含有LINE_NUM个空元件的梯级
        Rung *pRungInsert = new Rung;
        Node *pNode = new Node(1);	//新建一空AND节点作为新梯级的根节点
        for(int i=0; i<LINE_NUM; i++)
        {
            Element *pElementInsert=new Element(QString("N"), 0,0,0);
            pNode->AppendLink(pElementInsert);
        }
        pNode->iNodeRow = 1;
        pNode->iNodeColumn = LINE_NUM;
        pNode->pRung = pRungInsert;
        pRungInsert->pNodeRoot = pNode;
        pRungInsert->iRungRow = pNode->iNodeRow;
        //将新建的空梯级插入梯链
        Rung *pRungCur = cellArray[iy][ix].pRung;
        pRungInsert->pNextRung = pRungCur->pNextRung;
        pRungInsert->pPreRung = pRungCur;
        if(pRungCur->pNextRung != NULL)
        {
            pRungCur->pNextRung->pPreRung = pRungInsert;
        }
        pRungCur->pNextRung = pRungInsert;
        update();
    }

}

//删除梯级，	/删除当前梯级
void uiPlcEditor::DeleteRungSlot()
{
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Rung *pRungCur = cellArray[iy][ix].pRung;
    Element *pElementCur = cellArray[iy][ix].pElement;
    if(pElementCur != NULL)
    {
        //将要删除的梯级在梯链上摘下
        if(pRungCur == pRungHead)	//如果删除的是头指针	/包括删除时只剩下一个梯级时
        {
            pRungHead = pRungCur->pNextRung;
            if(pRungHead != NULL)
            {
                pRungHead->pPreRung = NULL;
            }
            else	//删除前只剩下一个梯级时
            {
                //新建一含有LINE_NUM个空元件的梯级
                Rung *pRungInsert = new Rung;
                Node *pNode = new Node(1);	//新建一空AND节点作为新梯级的根节点
                for(int i=0; i<LINE_NUM; i++)
                {
                    Element *pElementInsert=new Element(QString("N"), 0,0,0);
                    pNode->AppendLink(pElementInsert);
                }
                pNode->iNodeRow = 1;
                pNode->iNodeColumn = LINE_NUM;
                pNode->pRung = pRungInsert;
                pRungInsert->pNodeRoot = pNode;
                pRungInsert->iRungRow = pNode->iNodeRow;
                //将新建的空梯级设置为头梯级
                pRungInsert->pNextRung = NULL;
                pRungHead = pRungInsert;
            }
            //显示相关
            if(pRungCur == pRungTop)
            {
                pRungTop = pRungHead;
                iRowCBIR = pRungTop->iRungRow;
                iCursorX = W/2+5;
                iCursorY = 55;
            }
        }
        else if(pRungCur->pNextRung == NULL && pRungCur != pRungHead )	//如果删除的是尾指针
        {
            if(pRungCur->pPreRung != NULL)	//判断多余，以防万一
            {
                pRungCur->pPreRung->pNextRung = NULL;
            }
            //显示相关
            if(pRungCur == pRungTop)
            {
                pRungTop = pRungCur->pPreRung;
                iRowCBIR = pRungTop->iRungRow;
                iCursorX = W/2+5;
                iCursorY = 55;
            }
        }
        else	//非首尾梯级
        {
            Rung *pPreRung = pRungCur->pPreRung;
            Rung *pNextRung = pRungCur->pNextRung;
            pPreRung->pNextRung = pNextRung;
            pNextRung->pPreRung = pPreRung;
            //显示相关
            if(pRungCur == pRungTop)
            {
                pRungTop = pNextRung;
                iRowCBIR = pRungTop->iRungRow;
                iCursorX = W/2+5;
                iCursorY = 55;
            }
        }
        //释放空间
        ReleaseNode(pRungCur->pNodeRoot);
        delete pRungCur;
        update();
    }//end of if(pElementCur != NULL)

}
//插入一分支，	/在当前位置插入一分支
void uiPlcEditor::InsertBranchSlot()
{
    //QTextCodec *codec=QTextCodec::codecForName("gbk");
    //获得当前状态
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Element *pElementCur = cellArray[iy][ix].pElement;
    Rung *pRungCur = cellArray[iy][ix].pRung;
    //int iRungRowO = pRungCur->iRungRow;
    if(pElementCur != NULL && pElementCur->cName != QString("N") )	//空位置或空元件不能插入分支
    {
        if(ixFirst == -1 && iyFirst == -1)	//如果当前点为第一个分支点
        {
            ixFirst = ix;
            iyFirst = iy;
            //隐藏并无效其他按钮
//            pNocButton->setEnabled (false);	// 	-||-
//            pNccButton->setEnabled (false);	// 	-|/|-
//            pOutButton->setEnabled (false);	// 	( )
//            pSetButton->setEnabled (false);	// 	(S)
//            pRstButton->setEnabled (false);	//	(R）
//            //pInsertBranchButton->setEnabled (false);	//插入分支
//            pDeleteElementButton->setEnabled (false);//删除元件
//            pNextBarButton->setEnabled (false);			// >>
            //按钮条切换到插入分支的状态/此时只有插入分支按钮Escape和水平移动键有效
            iButtonPage = 0;
        }//end of //如果当前点为第一个分支点
        else if(ixFirst != -1 && iyFirst != -1)//如果当前点为第二个分支点
        {
            /***************************************************************************
            * 在 ix >= ixFirst && iy==iyFirst 的前提下
            *可以插入分支的几种情况：
            * A,ix = ixFirst  且同属于一个and节点
            * 	A.a   同属于一个and节点
            * 	A.b   同属于一个or节点
            * B,ix > ixFirst 但同属于一个and节点
            *		B.a,	ix,ixFirst同时为(不是根节点的)and的首尾分支
            *		B.b,	ix,ixFirst不同时为and的首尾分支
            *
            *
            *插入分支的思想是：
            * A:ix = ixFirst
            * 	A.a   同属于一个andF节点
            *			0, 1,如果节点andF不是根节点&&当前元件为andF节点的首子分支&& andF除了当前元件外只有空元件
      *       	新建一个与andF等宽的and节点andN 作为andF后面的分支，
      *        2,如果节点andF不是根节点&&当前元件为andF节点的非首尾子分支&&当前元件后面只有空元件
      *          具体过程见程序
      *       	跳过程序最后的Resize upDate
            *
            *     1,新建一or节点，将当前元件摘下，插入到or节点，or节点再插入一个空元件
            *     2,or节点取代当前元件的位置
            *     3,ResizeNode(NodeRoot);/(行数是否改变,修改相关的参数) update();
            * 	A.b   同属于一个or节点
            *     1,判断当前元件是否为or节点的尾分支
            *        是，否 ,将元件插入or节点时有点区别（新建一NodeLink）
            *			3,ResizeNode(NodeRoot);/(行列数是否改变,修改相关的参数) update();
            * B:ix > ixFirst但同属于一个andF节点：
            *		B.a,ix,ixFirst同时为(不是根节点的)andF的首尾分支
            *     1,获得andF的父节点orG，
            *     2,新建一与andF等宽的and节点，插入orG(要判断andF是否为orG的尾分支)
            *     3,ResizeNode(NodeRoot);/(行列数是否改变,修改相关的参数) update();
            *		B.b,	ix,ixFirst不同时为andF的首尾分支
            *		  1,新建一or1节点，新建两个and1，and2节点(and2的宽度与and1相同),and1,and2为or1的两个分支,
            * 	  2,将两个插入点之间的分支从andF中摘下插入and1，
            *		  3,将or融入到andF,
            *     4,ResizeNode(NodeRoot); update();
            *所有的ResizeNode(NodeRoot); update();放到最后执行
            *****************************************************************************/
            //前提：
            if(ix < ixFirst || iy != iyFirst)
            {
                //QMessageBox::information( this, "",codec->toUnicode("插入分支时选择元件的先后顺序错误！  \n分支的第一个点应在左边。"),codec->toUnicode("确定"));
                MESSAGEBOX("","插入分支时选择元件的先后顺序错误！  \n分支的第一个点应在左边。",Information);
                //显示并有效其它按钮
                ixFirst = -1;
                iyFirst = -1;
//                pNocButton->setEnabled (true);	// 	-||-
//                pNccButton->setEnabled (true);	// 	-|/|-
//                pOutButton->setEnabled (true);	// 	( )
//                pSetButton->setEnabled (true);	// 	(S)
//                pRstButton->setEnabled (true);	//	(R）
//                pDeleteElementButton->setEnabled (true);//删除元件
//                pNextBarButton->setEnabled (true);			// >>
                iButtonPage =1;
                return ;
            }	//end of 	if(ix <ixFirst || iy != iyFirst)
            Element *pElement1 = cellArray[iyFirst][ixFirst].pElement;
            Element *pElement2 = cellArray[iy][ix].pElement;
            Node *pNode1 = cellArray[iyFirst][ixFirst].pNode;
            Node *pNode2 = cellArray[iy][ix].pNode;
            NodeLink *pNodeLink1 = pElement1->pElementFather;
            NodeLink *pNodeLink2 = pElement2->pElementFather;
            //插入分支
            if(ix == ixFirst)//此时两个元件同为一个元件
            {
                if(pNode1->iNodeOperate == 1 )//且同属于一个and节点
                {
                    if(pNode1->pRung == NULL)	//不是根节点
                    {
                        if( pNodeLink1 == pNode1->pNodeLinkSon )	//当前元件为andF节点的首子分支
                        {
                        /****************************************************
                        * 如果节点and1不是根节点
                        *&&当前元件为and1节点的首子分支
                        *&& andF除了当前元件外只有空元件
              * 1新建一个与and1等宽的and节点andN 作为and1后面的分支，
              *	2跳到程序最后的Resize upDate
              *****************************************************/
              //判断 andF除了当前元件外是否只有空元件
                            NodeLink *pNodeLinkS = pNode1->pNodeLinkSon;
                            int i = 0;
                            while(pNodeLinkS != NULL)
                            {
                                if(pNodeLinkS->pNodeBlew != NULL)//遇到节点分支跳出
                                {
                                    i = -1;
                                    break;
                                }
                                else if(pNodeLinkS->pElementBlew != NULL && pNodeLinkS->pElementBlew->cName != QString("N"))
                                {
                                    i++;
                                    if(i > 1)
                                    {
                                        break;
                                    }
                                }
                                pNodeLinkS = pNodeLinkS->pNodeLinkRight;
                            }//end of while
                            if(i == 1) //and1除了当前元件外只有空元件
                            {
                                NodeLink *pNodeLinkToOR = pNode1->pNodeFather;
                                Node *pNodeOR = pNodeLinkToOR->pNodeLinkFather;
                                NodeLink *pNodeLinkToORR = pNodeLinkToOR->pNodeLinkRight;
                                //NodeLink *pNodeLinkLeft = pNodeLink1->pNodeLinkLeft;
                                //NodeLink *pNodeLinkRight = pNodeLink1->pNodeLinkRight;
                                //新建一与and1等宽的and节点，
                                Node *pNodeTmp = new Node(1);
                                for(int i=0; i<pNode1->iNodeColumn; i++)
                                {
                                    Element *pElementInsert=new Element(QString("N"), 0,0,100);
                                    pNodeTmp->AppendLink(pElementInsert);
                                }
                                //插入pNodeOR
                                NodeLink *pNodeLinkTmp = new NodeLink;
                                pNodeLinkTmp->pNodeLinkFather = pNodeOR;
                                pNodeLinkTmp->pNodeBlew = pNodeTmp;
                                pNodeLinkTmp->pElementBlew = NULL;
                                pNodeTmp->pNodeFather = pNodeLinkTmp;
                                pNodeLinkTmp->pNodeLinkLeft = pNodeLinkToOR;
                                pNodeLinkToOR->pNodeLinkRight =pNodeLinkTmp;
                                if(pNodeLinkToORR == NULL)
                                {
                                    pNodeLinkTmp->pNodeLinkRight = NULL;
                                }
                                else
                                {
                                    pNodeLinkToORR->pNodeLinkLeft = pNodeLinkTmp;
                                    pNodeLinkTmp->pNodeLinkRight = pNodeLinkToORR;
                                }
                                goto 	Resize;
                            }//end of if(i == 1)
                        }	//end of 当前元件为andF节点的首子分支
                        else if( pNodeLink1 != pNode1->pNodeLinkSon) ////当前元件为andF节点的非首尾子分支
                        {
                            /****************************************************
                            *如果当前元件的父节点为不是根节点的and节点pNode1
                            *且当前元件不是父节点的首尾子分支
                            *且and1中在当前元件后面只有空元件
                            *处理方法:
                            *	1新建两个and节点pNodeB1,pNodeB2,一个OR节点 pNodeORI;
                            *	2pNodeB1用来放从pNode1中摘下来的包括当前元件到最后的分支
                            *	3pNodeB2为与pNodeB1等宽的and空节点
                            *	4将pNodeB1,pNodeB2插入pNOdeORI，将pNOdeORI插入pNode1的当前元件左边分支的后面
                            *****************************************************/

                            //计算当前元件后面的空元件个数,
                            //如果返回值大于零说明既为所求，否则不是在这里要处理的情况，留给后面的程序处理
                            int i = 0;
                            NodeLink *pNodeLinkTmp = pNodeLink1->pNodeLinkRight;
                            while(pNodeLinkTmp != NULL)
                            {
                                if(pNodeLinkTmp->pNodeBlew != NULL)
                                {
                                    i= -1;
                                    break;
                                }
                                else if(pNodeLinkTmp->pElementBlew != NULL)
                                {
                                    Element *pElementTmp = pNodeLinkTmp->pElementBlew;
                                    if(pElementTmp->cName != QString("N") )
                                    {
                                        i = -1;
                                        break;
                                    }
                                    else
                                    {
                                        i++;
                                    }
                                }
                                pNodeLinkTmp = pNodeLinkTmp->pNodeLinkRight;
                            }//end of while
                            if(i>0)
                            {
                                // i就是当前元件后面的空元件的个数
                                Node *pNodeB1 = new Node(1);
                                Node *pNodeB2 = new Node(1);
                                Node *pNodeORI = new Node(2);
                                NodeLink *pNodeLinkLeft = pNodeLink1->pNodeLinkLeft;
                                //将当前元件到最后的所有分支摘下插入新建的pNodeB1节点
                                pNodeLinkTmp = pNodeLink1;
                                while(pNodeLinkTmp != NULL)
                                {
                                    pNodeB1->AppendLink(pNodeLinkTmp->pElementBlew);
                                    NodeLink *pNodeLinkT = pNodeLinkTmp;
                                    pNodeLinkTmp = pNodeLinkTmp->pNodeLinkRight;
                                    delete pNodeLinkT;
                                }
                                ResizeNode(pNodeB1);//刷新pNodeB1的行列数
                                //在 pNodeB2中插入空元件以与pNodeB1等宽
                                for(int i=0; i<pNodeB1->iNodeColumn; i++)
                                {
                                    Element *pElementTmp=new Element(QString("N"), 0,0,100);
                                    pNodeB2->AppendLink(pElementTmp);
                                }
                                ResizeNode(pNodeB2);
                                //将pNodeB1,pNodeB2插入pNOdeORI
                                pNodeORI->AppendLink(pNodeB1);
                                pNodeORI->AppendLink(pNodeB2);
                                ResizeNode(pNodeORI);
                                //将pNOdeORI插入pNode1的当前元件左边分支的后面
                                NodeLink *pNodeLinkO = new NodeLink;
                                pNodeLinkO->pNodeBlew = pNodeORI;
                                pNodeORI->pNodeFather = pNodeLinkO;
                                pNodeLinkO->pElementBlew = NULL;
                                pNodeLinkO->pNodeLinkFather = pNode1;
                                pNodeLinkO->pNodeLinkLeft = pNodeLinkLeft;
                                pNodeLinkO->pNodeLinkRight = NULL;
                                pNodeLinkLeft->pNodeLinkRight = pNodeLinkO;
                                goto 	Resize;
                            }//end of if(i>0)
                        }	//end of else if( pNodeLink1 != pNode1->pNodeLinkSon)

                    }//end of if(pNode1->pRung != NULL)	//不是根节点

                    //同属于一个and节点 除了上面两种特殊情况以外的处理方法

                    //当根节点只有一个输出元件时，插入分支时会出点问题，所以不允许插入
                    if( pNode1->pRung != NULL && pNodeLink1->pNodeLinkRight == NULL)
                    {
                        if(pNode1->pNodeLinkSon->pElementBlew != NULL)
                        {
                            Element *pElement = pNode1->pNodeLinkSon->pElementBlew;
                            if(pElement->cName == QString("N"))
                            {
                                //显示并有效其它按钮
                                ixFirst = -1;
                                iyFirst = -1;
//                                pNocButton->setEnabled (true);	// 	-||-
//                                pNccButton->setEnabled (true);	// 	-|/|-
//                                pOutButton->setEnabled (true);	// 	( )
//                                pSetButton->setEnabled (true);	// 	(S)
//                                pRstButton->setEnabled (true);	//	(R）
//                                //pInsertBranchButton->hide();	//插入分支
//                                pDeleteElementButton->setEnabled (true);//删除元件
//                                pNextBarButton->setEnabled (true);			// >>
                                iButtonPage =1;
                                return;
                            }
                        }
                    }
                    //常规处理
                    Node *pNodeTmp = new Node(2);	//新建一or节点
                    Element *pElementTmp=new Element(QString("N"), 0,0,100);
                    pNodeTmp->AppendLink(pElement1);
                    pNodeTmp->AppendLink(pElementTmp);
                    pNodeTmp->pNodeFather = pNodeLink1;
                    pNodeTmp->pRung = NULL;
                    pNodeLink1->pNodeBlew = pNodeTmp;
                    pNodeLink1->pElementBlew = NULL;
                }
                else if(pNode1->iNodeOperate == 2 )//且同属于一个or节点
                {
                    Element *pElementTmp=new Element(QString("N"), 0,0,100);
                    NodeLink *pNodeLinkTmp = new NodeLink;
                    pElementTmp->pElementFather = pNodeLinkTmp;
                    pNodeLinkTmp->pNodeBlew = NULL;
                    pNodeLinkTmp->pElementBlew = pElementTmp;
                    pNodeLinkTmp->pNodeLinkFather = pNodeLink1->pNodeLinkFather;
                    pNodeLinkTmp->pNodeLinkLeft = pNodeLink1;

                    if(pNodeLink1->pNodeLinkRight == NULL)	//当前元件为or节点的尾分支
                    {
                        pNodeLinkTmp->pNodeLinkRight = NULL;
                        pNodeLink1->pNodeLinkRight= pNodeLinkTmp;
                    }
                    else	//当前元件不是or节点的尾分支
                    {
                        //pNodeLinkTmp->pNodeLinkRight = pNodeLink1->pNodeLinkRight;
                        pNodeLink1->pNodeLinkRight->pNodeLinkLeft = pNodeLinkTmp;
                        pNodeLinkTmp->pNodeLinkRight = pNodeLink1->pNodeLinkRight;
                        pNodeLink1->pNodeLinkRight = pNodeLinkTmp;

                    }	//end of else (pNodeLink1->pNodeLinkRight == NULL)
                }	//end of else if(pNode1->iNodeOperate == 2 )

            }//end of if(ix == ixFirst)
            else if(ix > ixFirst)
            {
                if(pNode1 != pNode2 || pNode1->iNodeOperate != 1)	//元件不属于同一个and节点不处理
                {
                    //QMessageBox::information( this, "",codec->toUnicode("所选的两点之间不能插入分支！ "),codec->toUnicode("确定"));
                    MESSAGEBOX("","所选的两点之间不能插入分支！",Information);
                    //显示并有效其它按钮
                    ixFirst = -1;
                    iyFirst = -1;
//                    pNocButton->setEnabled (true);	// 	-||-
//                    pNccButton->setEnabled (true);	// 	-|/|-
//                    pOutButton->setEnabled (true);	// 	( )
//                    pSetButton->setEnabled (true);	// 	(S)
//                    pRstButton->setEnabled (true);	//	(R）
//                    //pInsertBranchButton->hide();	//插入分支
//                    pDeleteElementButton->setEnabled (true);//删除元件
//                    pNextBarButton->setEnabled (true);			// >>
                    iButtonPage =1;
                    return;
                }
                if(pNodeLink1->pNodeLinkLeft==NULL && pNodeLink2->pNodeLinkRight == NULL)
                {
                    //这种情况为：选中的两个位置为一个or节点的and分支的首尾/根节点显然不能添加分支
                    if(pNode1->pNodeFather == NULL)//这种情况下根节点显然不处理
                    {
                        //显示并有效其它按钮
                        ixFirst = -1;
                        iyFirst = -1;
//                        pNocButton->setEnabled (true);	// 	-||-
//                        pNccButton->setEnabled (true);	// 	-|/|-
//                        pOutButton->setEnabled (true);	// 	( )
//                        pSetButton->setEnabled (true);	// 	(S)
//                        pRstButton->setEnabled (true);	//	(R）
//                        pDeleteElementButton->setEnabled (true);//删除元件
//                        pNextBarButton->setEnabled (true);			// >>
                        iButtonPage =1;
                        return;
                    }
                    else
                    {
                        //1,获得andF的父节点or
                        NodeLink *pNodeLink1 = pNode1->pNodeFather;
                        Node *pNodeOR = pNodeLink1->pNodeLinkFather;
                        if(pNodeOR->iNodeOperate != 2 || pNode1->iNodeColumn != pNodeOR->iNodeColumn)	//此检查多余，以防万一
                        {
                            //显示并有效其它按钮
                            ixFirst = -1;
                            iyFirst = -1;
//                            pNocButton->setEnabled (true);	// 	-||-
//                            pNccButton->setEnabled (true);	// 	-|/|-
//                            pOutButton->setEnabled (true);	// 	( )
//                            pSetButton->setEnabled (true);	// 	(S)
//                            pRstButton->setEnabled (true);	//	(R）
//                            pDeleteElementButton->setEnabled (true);//删除元件
//                            pNextBarButton->setEnabled (true);			// >>
                            iButtonPage =1;
                            return;
                        }
                        //NodeLink *pNodeLinkLeft = pNodeLink1->pNodeLinkLeft;
                        NodeLink *pNodeLinkRight = pNodeLink1->pNodeLinkRight;

                        //新建一与andF等宽的and节点，
                        Node *pNodeTmp = new Node(1);
                        for(int i=0; i<pNode1->iNodeColumn; i++)
                        {
                            Element *pElementInsert=new Element(QString("N"), 0,0,100);
                            pNodeTmp->AppendLink(pElementInsert);
                        }

                        //插入pNodeOR
                        NodeLink *pNodeLinkTmp = new NodeLink;
                        pNodeLinkTmp->pNodeLinkFather = pNodeOR;
                        pNodeLinkTmp->pNodeBlew = pNodeTmp;
                        pNodeLinkTmp->pElementBlew = NULL;
                        pNodeTmp->pNodeFather = pNodeLinkTmp;
                        pNodeLinkTmp->pNodeLinkLeft = pNodeLink1;
                        pNodeLink1->pNodeLinkRight =pNodeLinkTmp;
                        if(pNodeLinkRight == NULL)
                        {
                            pNodeLinkTmp->pNodeLinkRight = NULL;
                        }
                        else
                        {
                            pNodeLinkRight->pNodeLinkLeft = pNodeLinkTmp;
                            pNodeLinkTmp->pNodeLinkRight = pNodeLinkRight;
                        }
                    }//end of pNode1->pNodeFather != NULL
                }//end of pNodeLink1->pNodeLinkLeft==NULL && pNodeLink2->pNodeLinkRight == NULL

                else	//ix,ixFirst不同时为andF的首尾分支
                {
                    Node *pNodeOR = new Node(2);
                    Node *pNodeB1 = new Node(1);	//用来放摘下的分支
                    Node *pNodeB2 = new Node(1);	//插入与pNodeB1等宽的空元件
                    NodeLink *pNodeLinkLeft  = pNodeLink1->pNodeLinkLeft;//这两个指针不同时为零
                    NodeLink *pNodeLinkRight = pNodeLink2->pNodeLinkRight;
                    Node *pNodeF = pNodeLink1->pNodeLinkFather;
                    //摘下分支，插入pNodeB1,
                    NodeLink *pNodeLink1x = pNodeLink1;
                    while(pNodeLink1x != pNodeLink2)
                    {
                        if(pNodeB1->pNodeLinkSon == NULL)		//摘下第一个分支时
                        {
                            pNodeB1->pNodeLinkSon = pNodeLink1x;
                            pNodeLink1x->pNodeLinkLeft = NULL;
                        }
                        else
                        {
                            pNodeB1->pNodeLinkLast->pNodeLinkRight = pNodeLink1x;
                            pNodeLink1x->pNodeLinkLeft = pNodeB1->pNodeLinkLast;
                        }
                        pNodeLink1x->pNodeLinkFather = pNodeB1;
                        //下一次循环
                        pNodeB1->pNodeLinkLast = pNodeLink1x;
                        pNodeLink1x = pNodeLink1x->pNodeLinkRight;
                    }
                    //此时pNodeLink1x = pNodeLink2;
                    pNodeLink1x->pNodeLinkFather = pNodeB1;
                    pNodeB1->pNodeLinkLast->pNodeLinkRight = pNodeLink1x;
                    pNodeLink1x->pNodeLinkLeft = pNodeB1->pNodeLinkLast;
                    pNodeLink1x->pNodeLinkRight = NULL;

                    ResizeNode(pNodeB1);
                    for(int i =0; i < pNodeB1->iNodeColumn; i++)
                    {
                        Element *pElement = new Element(QString("N"),0,0,100);
                        pNodeB2->AppendLink(pElement);
                    }
                    ResizeNode(pNodeB2);
                    //将pNodeB1,pNodeB2 插入pNodeOR
                    pNodeOR->AppendLink(pNodeB1);
                    pNodeOR->AppendLink(pNodeB2);
                    ResizeNode(pNodeOR);
                    //DisposeNode(pNodeOR);
                    //融入
                    NodeLink *pNodeLinkI = new NodeLink;
                    pNodeLinkI->pNodeBlew = pNodeOR;
                    pNodeOR->pNodeFather = pNodeLinkI;
                    pNodeLinkI->pElementBlew = NULL;
                    pNodeLinkI->pNodeLinkLeft = pNodeLinkLeft;
                    pNodeLinkI->pNodeLinkRight= pNodeLinkRight;
                    pNodeLinkI->pNodeLinkFather = pNodeF;
                    if(pNodeLinkLeft != NULL )
                    {
                        pNodeLinkLeft->pNodeLinkRight = pNodeLinkI;
                    }
                    else
                    {
                        pNodeF->pNodeLinkSon = pNodeLinkI;
                        pNodeLinkI->pNodeLinkRight = pNodeLinkRight;
                    }
                    if(pNodeLinkRight != NULL)
                    {
                        pNodeLinkRight->pNodeLinkLeft = pNodeLinkI;
                    }

                }//end of else 	pNodeLink1->pNodeLinkLeft==NULL && pNodeLink2->pNodeLinkRight == NULL
            }
            //ResizeNode,update()
            //百炼成钢
        Resize:
            DeleteAllNullElementE100(pRungCur->pNodeRoot);
            ResizeNode(pRungCur->pNodeRoot);
            pRungCur->pNodeRoot->iNodeColumn = LINE_NUM;
            PoiseNode(pRungCur->pNodeRoot);
            ResizeNode(pRungCur->pNodeRoot);	//很有必要/在输出元件上添加输出分支时
          ///*不要删掉,否则会有意外发生,
            pRungCur->pNodeRoot->iNodeColumn = LINE_NUM;
            PoiseNode(pRungCur->pNodeRoot);
            ResizeNode(pRungCur->pNodeRoot);
            //当由于插入分支引起列数大于LINE_NUM取消刚才插入的空分支.
            if(pRungCur->pNodeRoot->iNodeColumn >LINE_NUM)
            {
                RebuildNode(pRungCur->pNodeRoot);
                pRungCur->pNodeRoot->iNodeColumn = LINE_NUM;
                PoiseNode(pRungCur->pNodeRoot);
                ResizeNode(pRungCur->pNodeRoot);
                pRungCur->pNodeRoot->iNodeColumn = LINE_NUM;
                PoiseNode(pRungCur->pNodeRoot);
                ResizeNode(pRungCur->pNodeRoot);
                //QMessageBox::information( this, "",codec->toUnicode("行满，不能插入分支！  "),codec->toUnicode("确定"));
                MESSAGEBOX("","行满，不能插入分支！",Information);
            }

            //显示相关
            /*
            if( pRungCur == pRungTop && iRungRowO != pRungCur->iRungRow)
            {
                iRowCBIR = pRungCur->iRungRow;
            }
            */
            //显示并有效其它按钮
            ixFirst = -1;
            iyFirst = -1;
//            pNocButton->setEnabled (true);	// 	-||-
//            pNccButton->setEnabled (true);	// 	-|/|-
//            pOutButton->setEnabled (true);	// 	( )
//            pSetButton->setEnabled (true);	// 	(S)
//            pRstButton->setEnabled (true);	//	(R）
//            pDeleteElementButton->setEnabled (true);//删除元件
//            pNextBarButton->setEnabled (true);			// >>
            iButtonPage =1;
        }	//end of	//如果当前点为第二个分支点
        update();
    }//end of pElementCur != NULL

}
//保存，将当前的梯形图投入使用
void uiPlcEditor::SaveButtonSlot()
{

    bool bLSaved = false;
    bool bSSaved = false;
    //QTextCodec *codec=QTextCodec::codecForName("gbk")	;

    if( CheckLadder(pRungHead) == 0)//语法检查
    {
        //去掉空元件
        Rung *pRung = pRungHead;
        while(pRung != NULL)
        {
            Node *pNode = pRung->pNodeRoot;
            RebuildNode(pNode);
            pRung = pRung->pNextRung;
        }//end of while

        int i = CompileLadder(pRungHead);//实际保存梯形图过程
        pRung = pRungHead;
        while(pRung != NULL)
        {
            Node *pNode = pRung->pNodeRoot;
            RebuildNode(pNode);
            pNode->iNodeColumn = LINE_NUM;
            PoiseNode(pNode);
            ResizeNode(pNode);
            pNode->iNodeColumn = LINE_NUM;
            PoiseNode(pNode);
            pRung = pRung->pNextRung;
        }
        if (i == -1)	//翻译
        {
            QMessageBox::critical( this, "","语法错误!  ","确定" );
            bLSaved = false;
        }
        else if(i == -2)
        {
            QMessageBox::critical( this, "","文件写入错误!  ","确定" );
            bLSaved = false;
        }
        else if(i == 0)
        {
            //说明指令写入正常
            bLSaved = true;
            //把参数配置写入文件
            QFile fileName("E:/new_project/ShowWidget2/data_sourece/plc_element_signification_running.txt");
            if( ! fileName.open( QIODevice::WriteOnly | QIODevice::Text) )
            {
                QMessageBox::critical( this, "","文件写入错误!  ","确定");
                fileName.close();
                return;
            }
//            QTextStream fileStream(&fileName);
//            fileStream.setEncoding(QTextStream::Unicode);
            QTextStream fileStream( &fileName );
            //QT版本3转4不兼容处
//            fileStream.setEncoding(QTextStream::Unicode);
               fileStream.setAutoDetectUnicode(true);

            for(int i = 0; i<XNUM+YNUM+MNUM; i++)
            {
                //保证字符串的长度
                fileStream<<asESign[i]<< endl;
            }
            fileStream<<"%";
            fileName.close();
            bSSaved=true;

//            FILE *fp;
//            if((fp = fopen("E:/new_project/ShowWidget2/data_sourece/plc_element_signification_running.txt","wb"))==NULL)
//            {
//                QMessageBox::critical( this, "","文件写入错误!  ","确定" );
//                bSSaved = false;
//            }
//            else
//            {
//                for(int i = 0; i<XNUM+YNUM+MNUM; i++)
//                {
//                    bSSaved = true;

//                    QChar c[LENGTH] ;
//                    for(int j=0;j<LENGTH;j++)
//                    {
//                        c[j] = asESign[i].at(j);
//                    }
//                    if( fwrite(c,sizeof(QChar[LENGTH]),1,fp) != 1)
//                    {
//                        QMessageBox::critical( this, "","文件写入错误!  ","确定" );
//                        bSSaved = false;
//                        break;
//                    }

//                }
//            }
//            fclose(fp);

        }
    }
    else //if(CheckLadder(pRungHead) ==-1)//检查未通过不能投入应用
    {
        //do Nothing;
    }

    if(bLSaved==true && bSSaved==true)
    {
       QMessageBox::information( this, "","文件已保存。 ","确定" );
    }
    else
    {
      QMessageBox::critical( this, "","文件保存错误。 ","确定" );
    }
    update();
}

//载入机床机床出厂时梯形图到编辑界面   这个没用到
//void uiPlcEditor::ReloadButtonSlot()
//{
//    //先释放现在的所有梯级
//    Rung *pRung = pRungHead;
//    while(pRung != NULL)
//    {
//        Rung *pRungTmp = pRung;
//        Node *pNodeRoot = pRung->pNodeRoot;
//        ReleaseNode(pNodeRoot);
//        pRung = pRung->pNextRung;
//        delete pRungTmp;
//    }
//    pRungHead = NULL;

//    //刷新梯形图
//    char cFileName[]=("E:/new_project/ShowWidget2/data_sourece/plc_instruction_original.txt");
//    FormLadder(cFileName);	//函数返回pRungHead
//    char cFileName2[]=("E:/new_project/ShowWidget2/data_sourece/plc_element_signification_original.txt");
//    GetElementSignifiation(cFileName2);//函数给qESign赋值

//    //初始光标位置在显示区域的左上角
//    iCursorX = W/2+5; // 10+3*W/8;
//    iCursorY = 55; //+H/2;
//    ixFirst = -1;	//插入分支的第一点未选中
//    iyFirst = -1;
//    pRungTop=pRungHead;	//初始化时第一行显示的是梯级的头指针
//    iRowCBIR=pRungHead->iRungRow;//....的倒数最后一行

//    update();

//}

//设置参数，
void uiPlcEditor::ModifyElementSlot(QString &str)
{
    int ix = int(iCursorX-10)/W;
    int iy = int(iCursorY-36)/H;
    if(ix >LINE_NUM-1)
    {
        ix = LINE_NUM-1;
    }
    Element *pElementCur = cellArray[iy][ix].pElement;
    if(pElementCur->cName==QString("Y"))
    {
        asESign[XNUM+pElementCur->iNum] = str;
    }
    else if(pElementCur->cName==QString("M"))
    {
        asESign[XNUM+YNUM+pElementCur->iNum] = str;
    }
    update();

}

void uiPlcEditor::ChangeState()
{
    pTimer->stop();
    PLCMutex.lock();
//    memcpy(&Data_PLC, &stateData, sizeof(stu_stateData));
    PLCMutex.unlock();

//    unsigned long X_state_change = Data_PLC.plc_input ^ pre_Data_PLC.plc_input;
//    unsigned long Y_state_change = Data_PLC.plc_output ^ pre_Data_PLC.plc_output;
//    unsigned long M_state_change = Data_PLC.plc_M ^ pre_Data_PLC.plc_M;
//    unsigned long W_state_change = Data_PLC.plc_Warning ^ pre_Data_PLC.plc_Warning;
//    unsigned long C_state_change = Data_PLC.plc_C ^ pre_Data_PLC.plc_C;
//    unsigned long T_state_change = Data_PLC.plc_T ^ pre_Data_PLC.plc_T;
//    pre_Data_PLC.plc_input = Data_PLC.plc_input;
//    pre_Data_PLC.plc_output = Data_PLC.plc_output;
//    pre_Data_PLC.plc_M = Data_PLC.plc_M;
//    pre_Data_PLC.plc_Warning = Data_PLC.plc_Warning;
//    pre_Data_PLC.plc_C = Data_PLC.plc_C;
//    pre_Data_PLC.plc_T = Data_PLC.plc_T;

//    if(X_state_change || Y_state_change || M_state_change ||\
//       W_state_change || C_state_change || T_state_change)
//    {
//        update();
//    }
    if(bOverflow && ! bNoted)
    {
        //KWarning(this,tr("存在溢出元件!"));
        bNoted = true;
    }
    pTimer->start(200);
}
