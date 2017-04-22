// CodecSettingFrm.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "DXMediaCap.h"
#include "CodecSettingFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodecSettingFrm dialog


CCodecSettingFrm::CCodecSettingFrm(CWnd* pParent /*=NULL*/)
	: CDialog(CCodecSettingFrm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodecSettingFrm)
	m_VidStr = _T("");
	m_PicStr = _T("");
	//}}AFX_DATA_INIT
}


void CCodecSettingFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodecSettingFrm)
	DDX_Control(pDX, IDC_EDITNAME, m_ctrlEditName);
	DDX_Control(pDX, IDC_EDITADDRESS, m_ctrlEditAddress);
	DDX_Control(pDX, IDC_COMBOUINT, m_ctrlComboUint);
	DDX_Control(pDX, IDC_CAP_DIR_EDIT, m_RecEditPath);
	DDX_Control(pDX, IDC_EDIT_SNAPDIR, m_SnapEditPath);
	DDX_Text(pDX, IDC_CAP_DIR_EDIT, m_VidStr);
	DDX_Text(pDX, IDC_EDIT_SNAPDIR, m_PicStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCodecSettingFrm, CDialog)
	//{{AFX_MSG_MAP(CCodecSettingFrm)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOCODEC, OnSelchangeComboAudiocodec)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOCODEC, OnSelchangeComboVideocodec)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_SNAPDIR, OnButtonBrowseSnapdir)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_RECDIR, OnButtonBrowseRecdir)
	ON_BN_CLICKED(IDC_RADIO_XVID, OnRadioXvid)
	ON_BN_CLICKED(IDC_RADIO_DIVX, OnRadioDivx)
	ON_BN_CLICKED(IDC_RADIO_H264, OnRadioH264)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodecSettingFrm message handlers
BOOL CCodecSettingFrm::OnInitDialog() 
{
	CDialog::OnInitDialog();


//初始化保存路径

	CString StrPic; 
	GetPrivateProfileString("SystemSetting","PicPath","d:\\Pic",StrPic.GetBuffer(128),128,strIniFile);
	StrPic.ReleaseBuffer();
	PicPath=StrPic;
	
	CString StrVid; 
	GetPrivateProfileString("SystemSetting","VideoPath","d:\\Video",StrVid.GetBuffer(128),128,strIniFile);
	StrVid.ReleaseBuffer();
	VideoPath=StrVid;

	if(!SetCurrentDirectory(PicSavePath))
	{
		CreateDirectory(PicSavePath, NULL);
		
	}
	
	if(!SetCurrentDirectory(RecSavePath))
	{
		CreateDirectory(RecSavePath, NULL);
		
	}

	m_SnapEditPath.SetWindowText(PicPath);
	m_RecEditPath.SetWindowText(VideoPath);


//初始化登录记录

	m_ctrlComboUint.SetCurSel(nComboUintIndex);
	m_ctrlEditAddress.SetWindowText(address);
	m_ctrlEditName.SetWindowText(name);

	
  

	return 0;
}
void CCodecSettingFrm::OnSelchangeComboAudiocodec() 
{
	// TODO: Add your control notification handler code here
	
}

void CCodecSettingFrm::OnSelchangeComboVideocodec() 
{
	// TODO: Add your control notification handler code here
	
}

void CCodecSettingFrm::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

void CCodecSettingFrm::OnOK() 
{
	// TODO: Add extra validation here

//保存路径设置
	m_SnapEditPath.SetWindowText(PicSavePath);
	m_RecEditPath.SetWindowText(RecSavePath);
	WritePrivateProfileString("SystemSetting","PicPath",PicPath,strIniFile); 
	WritePrivateProfileString("SystemSetting","VideoPath",VideoPath,strIniFile);

	if(!SetCurrentDirectory(PicSavePath))
	{
		CreateDirectory(PicSavePath, NULL);
		
	}
	
	if(!SetCurrentDirectory(RecSavePath))
	{
		CreateDirectory(RecSavePath, NULL);
		
	}


//登录信息设置

	
	nComboUintIndex=m_ctrlComboUint.GetCurSel();
	
	m_ctrlComboUint.GetWindowText(customsUint);
	m_ctrlEditAddress.GetWindowText(address);
	m_ctrlEditName.GetWindowText(name);

	char* pszFileName="登录记录.txt";
	CStdioFile myFile;
	CFileException fileException;

	//设置pszFileName的保存路径
	SetCurrentDirectory(RootPath);
	if(myFile.Open(pszFileName,CFile::typeText|CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite),&fileException)
	{
		myFile.SeekToEnd();
		
		CString strTime;
		CTime time;
		time = CTime::GetCurrentTime();//当前时间
		
		strTime = "登录时间: " + time.Format("%Y%m%d-%H%M%S") +"\n";
		myFile.WriteString(strTime);

		

		myFile.WriteString("海关直属:  "+customsUint+"\n");
		myFile.WriteString("登录地址:  "+address+"\n");
		myFile.WriteString("用户名  :  "+name+"\n\n");


	}


	myFile.Close();
	CDialog::OnOK();
}

void CCodecSettingFrm::OnButtonBrowseSnapdir() 
{
	// TODO: Add your control notification handler code here

			CString str;

	BROWSEINFO bi;
	
	char name[MAX_PATH];
	
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	
	bi.hwndOwner = GetSafeHwnd();
	
	bi.pszDisplayName = name;
	
	bi.lpszTitle = "Select folder";
	
	bi.ulFlags = BIF_RETURNONLYFSDIRS ;
	
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	
	if(idl == NULL)
		return;
	
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	
	str.ReleaseBuffer();
	
	PicSavePath = str;
	
//	if(str.GetAt(str.GetLength()-1) != '\\')
	//	PicSavePath += "\\";

	m_SnapEditPath.SetWindowText(PicSavePath);
	WritePrivateProfileString("SystemSetting","PicSaveParh",PicSavePath,strIniFile); 

	
}

void CCodecSettingFrm::OnButtonBrowseRecdir() 
{
	// TODO: Add your control notification handler code here
		CString str;

	BROWSEINFO bi;
	
	char name[MAX_PATH];
	
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	
	bi.hwndOwner = GetSafeHwnd();
	
	bi.pszDisplayName = name;
	
	bi.lpszTitle = "Select folder";
	
	bi.ulFlags = BIF_RETURNONLYFSDIRS ;
	
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	
	if(idl == NULL)
		return;
	
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	
	str.ReleaseBuffer();
	
	RecSavePath = str;
	
//	if(str.GetAt(str.GetLength()-1) != '\\')
	//	RecSavePath += "\\";

	m_RecEditPath.SetWindowText(RecSavePath);
	WritePrivateProfileString("SystemSetting","VideoSaveParh",RecSavePath,strIniFile); 
}

void CCodecSettingFrm::OnRadioXvid() 
{
	// TODO: Add your control notification handler code here

	//	CDlgDemoDlg::DeviceInfo[dwCard].dwVideoCodecStr="XviD MPEG-4 Codec";
	//	WritePrivateProfileString("SystemSetting","VideoCodec","XviD MPEG-4 Codec",strIniFile); 
	
}

void CCodecSettingFrm::OnRadioDivx() 
{
	// TODO: Add your control notification handler code here
	//	CDlgDemoDlg::DeviceInfo[dwCard].dwVideoCodecStr="DivX? 5.1.1 Codec";
	//	WritePrivateProfileString("SystemSetting","VideoCodec","DivX? 5.1.1 Codec",strIniFile); 

	
}

void CCodecSettingFrm::OnRadioH264() 
{
	// TODO: Add your control notification handler code here
	//	WritePrivateProfileString("SystemSetting","VideoCodec","x264 Codec",strIniFile); 
}
