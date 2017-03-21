#ifndef UIPLCEDITOR_H
#define UIPLCEDITOR_H

#include "plc_shape_ladder.h"
#include "plc_poise_node.h"
//#include"plc_shape_ladder_test.h"//测试用
#include "plc_editor_dialog.h"
#include "plc_rebuild_node.h"
#include "plc_compile_ladder.h"
#include "plc_check_node.h"
#include "plc_MDialog.h"
//#include "globalvars.h"
#include <QDialog>
#include <QTimer>
#include <QMutex>


#ifndef MESSAGEBOX
#define MESSAGEBOX(strTitle, strInfo, Icon) QTextCodec *codecM=QTextCodec::codecForName("UTF-8"); \
    QMessageBox (codecM->toUnicode(strTitle) ,codecM->toUnicode(strInfo)                           \
    ,QMessageBox::Icon,messageboxQMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton 	,this);         \
    messagebox.setFont(QFont("wenquanyi",12,QFont::Normal,false));	messagebox.grabKeyboard(); messagebox.exec(); \
    messagebox.releaseKeyboard(); this->grabKeyboard();
//#undef MESSAGEBOX
#endif

//#define XNUM 256
//#define YNUM 256
//#define MNUM 256
//#define CNUM 16
//#define TNUM 16
//#define LENGTH 4

#define  W  60
#define  H  38
#define  LINE_NUM 10


//界面数组的结构体
struct CellArray
{
    Rung *pRung;
    Node *pNode;
    Element *pElement;
};


namespace Ui {
class uiPlcEditor;
}

class uiPlcEditor : public  QWidget
{
    Q_OBJECT
    
public:
    explicit uiPlcEditor(QWidget *parent = 0, QString strName="",bool monitor = false);
    ~uiPlcEditor();
    
private:
    Ui::uiPlcEditor *ui;
//    QPushButton *pTitle;    //显示标题
//    QPushButton *pInfo;     //右上角的时间显示
    QTimer *pTitleTimer;

    //下部按键
    //uiPopButtonGroup *popButton[2];
    //int curButtonGroup;     //当前显示的按键组合
    int iButtonPage;		//界面下面的按钮为第一页是为1,第二页为2，仅使特别的键有效0（插入分支）
//    void setCurButton(int ncur);


    //表示梯状态的变量
    Rung *pRungHead;							//树形结构的头指针
    QString asESign[XNUM+YNUM+MNUM];//输出元件代表的含义
    struct CellArray cellArray[11][10];			//界面数组
    //插入分支的第一个有效状态,界面数组的下标 // =-1表示第一个位置还未别选中
    int ixFirst;
    int iyFirst;

    //画图时要用到的成员变量
    bool bPaintOk;			//界面刷新是否结束，正在画图时不响应键盘事件
    int iDisplayTop;		//显示区域的顶端
    int iDisplayBottom;	//显示区域的底端
    int iDisplayLeft;		//显示区域的左端
    int iDisplayRight;		//显示区域的右端

    int iCursorX;				//光标现在的位置或刷新后光标应在的位置，
    int iCursorY;
    int iySlider;				//滑快的位置
    int iRowCBIR;			//刷新界面后的显示区域的最顶层在顶层梯级的倒数行数
    Rung *pRungTop;	//刷新界面后的最顶层梯级
    Rung *pRungDraw;//画图时的当前梯级

    int inet;

    bool bMonitor;  //是否包含监控
    QTimer *pTimer; //监控定时器
    QMutex PLCMutex; //互斥量
    unsigned short int ElementName[11][10];//记录元件的名称代码
    void GetElementName();  //获取每个表格中所代表单元的元件名称
    bool bOverflow;
    bool bNoted;
//    stu_stateData Data_PLC;
//    stu_stateData pre_Data_PLC;

    //对话框
    NocDialog *pNocDialog;	// 	-||-	按钮 对应的对话框
    NccDialog *pNccDialog;	// 	-|/|-	按钮 对应的对话框
    OutDialog *pOutDialog;	// 	( )	按钮 对应的对话框
    SetDialog *pSetDialog;	// 	(S)	按钮 对应的对话框
    RstDialog *pRstDialog;	//	(R）	按钮 对应的对话框
    MDialog   *pMDialog;		//设置参数


    virtual void keyPressEvent(QKeyEvent *);
     virtual void paintEvent(QPaintEvent*event);

    void FormLadder(char *cFileName);			//读取指令表，形成树形结构
    void GetElementSignifiation(char*cFileName);	//读取元件的含义
    int CheckLadder(Rung *);			//语法检查返回出错的梯级的行数，若梯级正确返回-1

    void DarwNode(Node *pNode, QPainter *p, int x, int y);	//画节点 /要调用到元件的画图函数
    void DrawElement(Element *pElement, QPainter *p, int x, int y);//画元件

signals:
    void sendCmdSignal(bool bStart);
private slots:
/*    void updateTitleSlot( );	*/			//刷新右上角的日期时间显示
    void whichIsActive(int buttonGroup, int num);
    void popButton_one_slot(int num);
    void popButton_two_slot(int num);

    void NocButtonSlot(QString &qsEstyle, int iENum);
    void NccButtonSlot(QString &qsEstyle, int iENum);
    void OutButtonSolt(QString &qsEstyle, int iENum, int iPara);
    void SetButtonSlot(QString &qsEstyle, int iENum);
    void RstButtonSlot(QString &qsEstyle, int iENum);

    void DeleteElementSlot();  	//删除当前位置的节件，//注意:把节点的最后一个不为空的元件删除后，删除节点/
    void DeleteBranchSlot();		//删除分支，	/删除当前分枝，当节点为梯级的根节点时删除梯级!
    void InsertBranchSlot();		//插入一分支，	/在当前位置插入一分支
    void InsertRungSlot();		//插入梯级，	/在当前梯级后面插入梯级
    void DeleteRungSlot();		//删除行，	/删除当前梯级  


//    void ReloadButtonSlot(); 	//载入机床正在使用的梯形图到暂存文件,/
    void ModifyElementSlot(QString &str);		//设置参数，

    void ChangeState();

public slots:
        void SaveButtonSlot();		//保存梯形图	/包含检查过程
};

#endif // UIPLCEDITOR_H
