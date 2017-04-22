// TxtViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "TxtViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TxtViewerDlg dialog


TxtViewerDlg::TxtViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TxtViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TxtViewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


}


void TxtViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TxtViewerDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TxtViewerDlg, CDialog)
	//{{AFX_MSG_MAP(TxtViewerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TxtViewerDlg message handlers

void TxtViewerDlg::OpenMyFile()
{

	CString fileName=RootPath+"\\登录记录.txt";


	char* pszFileName =fileName.GetBuffer(fileName.GetLength());

	CStdioFile myFile;
	CFileException fileException;
	if(myFile.Open(pszFileName,CFile::modeRead))
	{
		//	CStdioFile file;
		CString strLine,strText;
		//	//	m_edit.GetWindowText(str);
		//	
		//	file.Open(dlg.GetPathName(),CFile::modeRead);
		
		while(myFile.ReadString(strLine))
		{
			strLine+="\r\n";
			strText+=strLine;
			
		}



		m_ctrlEdit.ReplaceSel(strText);
	//	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);

		//	myFile.SeekToEnd();
	}




	
	myFile.Close();

		//将光标移到末尾
	int len=m_ctrlEdit.GetWindowTextLength();

//	m_ctrlEdit.SetFocus();
	m_ctrlEdit.SetSel(len,len,false);

		m_ctrlEdit.LineScroll(len);
	//	UpdateData(0);
	

}




BOOL TxtViewerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetWindowText("登录记录");
	
	OpenMyFile();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
