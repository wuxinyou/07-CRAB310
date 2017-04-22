// PicViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "PicViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PicViewerDlg dialog


PicViewerDlg::PicViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PicViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PicViewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PicViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PicViewerDlg)
	DDX_Control(pDX, IDC_PIC, m_ctrlPic);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_BTNPREV, m_ctrlBtnPrev);
	DDX_Control(pDX, IDC_BTNNEXT, m_ctrlBtnNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PicViewerDlg, CDialog)
	//{{AFX_MSG_MAP(PicViewerDlg)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_BTNPREV, OnBtnprev)
	ON_BN_CLICKED(IDC_BTNNEXT, OnBtnnext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PicViewerDlg message handlers

BOOL PicViewerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//初始化成员变量
	list2ItemCount=0;
	list2Index=0;
	
	// TODO: Add extra initialization here



	//刷新列表1
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, RootPath);   //CString to TCHAR
	//	TCHAR szPath[MAX_PATH] ={"C:\\CRABUserData"} ; 
	//该函数用与指定的文件名匹配的所有文件的名字填充列表框。
	int nReslt = DlgDirList(szPath , IDC_LIST1 ,NULL,DDL_EXCLUSIVE|DDL_DIRECTORY );    //只显示目录文件


	//设置按钮图标
//下一个 按钮
//	m_ctrlBtnNext.m_bIsCheckBox=true;
	m_ctrlBtnNext.SetWindowText("");   //清空按钮上的文字
	m_ctrlBtnNext.SetAlign(0);
	m_ctrlBtnNext.SetIcon(IDI_NEXTBTN2,IDI_NEXTBTN1);
	m_ctrlBtnNext.SetFlat(true);
	m_ctrlBtnNext.DrawTransparent(TRUE);
	m_ctrlBtnPrev.MoveWindow(0,200,62,80);
	
//上一个 按钮	
	m_ctrlBtnPrev.SetAlign(0);	
	m_ctrlBtnPrev.SetIcon(IDI_PREVBTN2,IDI_PREVBTN1);	
	m_ctrlBtnPrev.SetFlat(true);
	m_ctrlBtnPrev.DrawTransparent(TRUE);	
	m_ctrlBtnNext.MoveWindow(704,200,62,80);
	

	
	//设置窗体大小
	this->SetWindowText("图片浏览");
	this->MoveWindow(106,145,1074,510);
	
	m_ctrlPic.MoveWindow(0,0,768,480);
	//设置列表部件位置
	m_ctrlList1.MoveWindow(768,0,300,239);
	m_ctrlList2.MoveWindow(768,241,300,239);
	//设置列表部件的字体
	CFont font;
	font.CreatePointFont(200,"宋体");     //列表框字体的设定
	m_ctrlList1.SetFont(&font);
	m_ctrlList2.SetFont(&font);
	font.Detach();

	
	

	
	CString fileName="";
	
	CString AppPath; 
	//得到当前程序路径
	GetModuleFileName(NULL,AppPath.GetBufferSetLength(1023),1024); 
	AppPath.ReleaseBuffer(); 
	int nPos; 
	nPos = AppPath.ReverseFind('\\'); 
	AppPath = AppPath.Left(nPos); 
	//ini文件存储路径
	fileName=AppPath+"\\res\\ODLog768x480.jpg";
	if (m_ctrlPic.Load(fileName) )
		m_ctrlPic.Draw();
	
//	HBITMAP hBitmap;
//	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG480)); 
//	m_ctrlPic.SetBitmap(hBitmap); 


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PicViewerDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int index=m_ctrlList1.GetCurSel();
	m_ctrlList1.GetText(index,str);

	//获取list2的Item数目
	str.Replace("[", NULL);
	str.Replace("]", NULL);	

	PicPath=RootPath+"\\"+str+"\\Pic";	

	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, PicPath);   //CString to TCHAR

	//该函数用与指定的文件名匹配的所有文件的名字填充列表框。
	int nReslt = DlgDirList(szPath , IDC_LIST2 ,NULL,DDL_EXCLUSIVE|DDL_ARCHIVE );   //显示文件

	//填充list2后才能获取到项的数量
	list2ItemCount = m_ctrlList2.GetCount();
	list2Index=0;		//必须在重装list2后，清零list2Index，否则会记住上一个列表框的值。
	
}

void PicViewerDlg::OnDblclkList2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	list2Index=m_ctrlList2.GetCurSel();
	m_ctrlList2.GetText(list2Index,str);	
	
	m_PicFilePath=PicPath+"\\"+str;
	
	
	ShowPicture();  //显示图片
	
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);
	m_ctrlBtnNext.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	
	Invalidate();
	
	UpdateData(FALSE);
}

void PicViewerDlg::OnBtnprev() 
{
	// TODO: Add your control notification handler code here
	if(list2ItemCount==0)
		return ;
	
	CString str;
	
	if(list2Index==0)   //已经是最后一张
	{
		list2Index=list2ItemCount-1;
	}
	else
	{
		list2Index--;
	}
	
	
	m_ctrlList2.GetText(list2Index,str);
	m_ctrlList2.SetCurSel(list2Index);	
	
	m_PicFilePath=PicPath+"\\"+str;	
	
	ShowPicture();  //显示图片
	
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);
	
	m_ctrlBtnNext.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	
	Invalidate();
	
	
}

void PicViewerDlg::OnBtnnext() 
{
	// TODO: Add your control notification handler code here
		if(list2ItemCount==0)
		return ;
	
	CString str;

	if(list2Index==list2ItemCount-1)   //已经是最后一张
	{
		list2Index=0;
	}
	else
	{
		list2Index++;
	}


	m_ctrlList2.GetText(list2Index,str);
	m_ctrlList2.SetCurSel(list2Index);	

	m_PicFilePath=PicPath+"\\"+str;	
	
	ShowPicture();  //显示图片
	
		m_ctrlBtnNext.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//每次重绘前都必须设置透明。
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);

	
	Invalidate();
	
}


void PicViewerDlg::ShowPicture()
{
		if (m_ctrlPic.Load(m_PicFilePath))
		m_ctrlPic.Draw();

}
