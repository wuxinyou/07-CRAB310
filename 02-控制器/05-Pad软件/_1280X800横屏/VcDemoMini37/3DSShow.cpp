// 3DSShow.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "3DSShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DSShow

C3DSShow::C3DSShow()
{

	m_rotateAngleX=0;
	m_rotateAngleY=0;
	m_lButtonDown=false;

//	Width=800;//GetSystemMetrics(SM_CXSCREEN);
//	Height=600;//GetSystemMetrics(SM_CYSCREEN);
//	MoveWindow(0,0,Width,Height);//窗口定位
//////////////////////////////////////////////////////////
//	glViewport(0, 0,Width,Height);// reset the viewport to new dimensions
//	glMatrixMode(GL_PROJECTION);	// set projection matrix current matrix
//	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)(Height-0),1.0f,2000.0f);
//	glMatrixMode(GL_MODELVIEW);		// set modelview matrix
//	glLoadIdentity();				// reset modelview matrix
//	glEnable(GL_TEXTURE_2D);	// 启用纹理映射(新增)
//	glShadeModel(GL_SMOOTH);
//	GLfloat light_position[] = {1.0,1.0,1.0,0.0};
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_COLOR_MATERIAL);
//////////////////////////////////////////////////////////
//	m_3ds=new CLoad3DS();
//	m_3ds_compass=new CLoad3DS();
//
//	load3dobj("data/","dipan.3ds",0);
	//	SetTimer(1,100,NULL);
}

C3DSShow::~C3DSShow()
{
}


BEGIN_MESSAGE_MAP(C3DSShow, CStatic)
	//{{AFX_MSG_MAP(C3DSShow)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DSShow message handlers


void C3DSShow::load3dobj(char* dir,char* cn,int a)
{	char	appdir[256];
	GetCurrentDirectory(256,appdir);
	SetCurrentDirectory(dir);
	m_3ds->Init(cn,a);

	//	m_3ds->Init("luopan1.3ds",1);
	//	m_3ds_compass->Init("luopan1.3ds",1);
	SetCurrentDirectory(appdir);
}


BOOL C3DSShow::Scene(int obj,float x,float h,float z,float r,int re,float size)//显示对象
{		//				 序号   ,位置x  ,高度   ,位置y  ,半径   ,角度  ,大小
	glPushAttrib(GL_CURRENT_BIT);	//保存现有颜色属实性
	glPushMatrix();//glPopMatrix();
	glTranslatef(x,h,z);	//飞机定位

	//	m_3ds->show3ds(1,0.0f,0.0f,r,size);//显示3ds模型飞机
	//	m_3ds_compass->show3ds(1,0.0f,0.0f,r,size);//显示3ds模型飞机

	glRotatef(m_rotateAngleX,1.0, 0, 0);	//整体坐标旋转
	glRotatef(m_rotateAngleY,0, 0, 1.0);	//整体坐标旋转


	glRotatef(re,0.0, 0.0, 1.0);	//飞机的旋转
	
	m_3ds->show3ds(obj,0.0f,r,0.0f,size);//显示3ds模型飞机
	
	glPopMatrix();
	glPopAttrib();//恢复前一属性
	return TRUE;
}

int C3DSShow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	return 0;
}



BOOL C3DSShow::SetWindowPixelFormat(HDC hDC)/////////////////////////
{	static PIXELFORMATDESCRIPTOR pfd =
	{	sizeof(PIXELFORMATDESCRIPTOR),	//格式描述符的大小
		1,								// 版本号
		PFD_DRAW_TO_WINDOW |			// 格式必须支持窗口
		PFD_SUPPORT_OPENGL |			// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER|PFD_STEREO_DONTCARE,// 必须支持双缓冲
		PFD_TYPE_RGBA,					// 申请 RGBA 格式
		16,								// 选定色彩深度
		0, 0, 0, 0, 0, 0,				// 忽略的色彩位
		0,								// 无Alpha缓存
		0,								// 忽略Shift Bit
		0,								// 无聚集缓存
		0, 0, 0, 0,						// 忽略聚集位
		32,								// 16位 Z-缓存 (深度缓存) 
		0,								// 无模板缓存
		0,								// 无辅助缓存
		PFD_MAIN_PLANE,					// 主绘图层
		0,								// 保留
		0, 0, 0							// 忽略层遮罩
	};
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pfd);
	if(m_GLPixelIndex==0) // Choose default
	{	m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
		sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
		{return FALSE;}
	}
	SetPixelFormat(hDC, m_GLPixelIndex, &pfd);//set pixel format to device context
	return TRUE;
}
BOOL C3DSShow::CreateViewGLContext(HDC hDC)/////////////////////
{	m_hGLContext = wglCreateContext(hDC);
	if(m_hGLContext==NULL)	return FALSE;
	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)	return FALSE;
	return TRUE;
}



void C3DSShow::Render()
{//////////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST);			// enable depth testing
	glClearColor(0.2714f,0.196f,0.196f,0);//设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();
	////////////////////////////////////////////////////
		glEnable(GL_TEXTURE_2D);

//		BOOL C3DSShow::Scene(int obj,float x,float h,float z,float r,int re,float size)//显示对象
//{		//				 序号   ,位置x  ,高度   ,位置y  ,半径   ,角度  ,大小

			Scene(0,0,0,-1.2,0,0,0.5f);//显示对象
			Scene(1,0,0,-1.2,0,r,0.5f);//显示对象

		glDisable(GL_TEXTURE_2D);
		r+=1;if(r>360) r=0;
	glFlush();			//更新窗口
	SwapBuffers(hDC);	//更新窗口
}

void C3DSShow::InitCWnd()
{

	HWND hWnd = GetSafeHwnd();
	hDC = ::GetDC(hWnd);
	///////////////////////////////////////////////////////
	if(SetWindowPixelFormat(hDC)==FALSE) return ;	
	if(CreateViewGLContext(hDC)==FALSE)  return ;

	r=0;
	Width=163;//GetSystemMetrics(SM_CXSCREEN);
				Height=163;//GetSystemMetrics(SM_CYSCREEN);
				MoveWindow(0,600,Width,Height);//窗口定位
				////////////////////////////////////////////////////////////
				glViewport(0, 0,Width,Height);// reset the viewport to new dimensions
				glMatrixMode(GL_PROJECTION);	// set projection matrix current matrix
				gluPerspective(28.0f,(GLfloat)Width/(GLfloat)(Height-0),1.0f,2000.0f);
				glMatrixMode(GL_MODELVIEW);		// set modelview matrix
				glLoadIdentity();				// reset modelview matrix
				glEnable(GL_TEXTURE_2D);	// 启用纹理映射(新增)
				glShadeModel(GL_SMOOTH);
				GLfloat light_position[] = {1.0,1.0,1.0,0.0};
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_COLOR_MATERIAL);
				////////////////////////////////////////////////////////////
				m_3ds=new CLoad3DS();
				m_3ds_compass=new CLoad3DS();
				
				load3dobj("data/","luopan.3ds",0);
				load3dobj("data/","dipan.3ds",1);


}



void C3DSShow::setRotateParm(GLfloat angleX, GLfloat angleY)
{
	m_rotateAngleX+=angleX;
	if(m_rotateAngleX>360)
		m_rotateAngleX=0;

	m_rotateAngleY+=angleY;
	if(m_rotateAngleY>360)
		m_rotateAngleY=0;
}



////////////////////////////////////////////Mouse Event///////////////////////////////////////////////////////////

void C3DSShow::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(m_lButtonDown)
	{		
		m_pointTerminal=point;
		int cx=m_pointTerminal.x-m_pointOrigin.x;
		int cy=m_pointTerminal.y-m_pointOrigin.y;		
		
		setRotateParm( (float)cy /20 ,(float)cx/30 );
		
		Render();	
		
	}
		
	CStatic::OnMouseMove(nFlags, point);
}




void C3DSShow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_lButtonDown=true;
	m_pointOrigin=point;

	CStatic::OnLButtonDown(nFlags, point);
}

void C3DSShow::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_lButtonDown=false;
	
	CStatic::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////end of Mouse Event//////////////////////////////////////////////////////////////