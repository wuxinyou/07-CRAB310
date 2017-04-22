VERSION 5.00
Begin VB.Form ColorProtyDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   3900
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5685
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   260
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   379
   ShowInTaskbar   =   0   'False
   Begin VB.Frame ColorSetting 
      Caption         =   "ColorSetting"
      Height          =   3735
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5535
      Begin VB.CommandButton OKButton 
         Caption         =   "OK"
         Height          =   375
         Left            =   720
         TabIndex        =   18
         Top             =   3120
         Width           =   1095
      End
      Begin VB.HScrollBar HScrollHue 
         Height          =   255
         Left            =   1080
         TabIndex        =   17
         Top             =   1440
         Value           =   68
         Width           =   3495
      End
      Begin VB.HScrollBar HScrollContrast 
         Height          =   255
         Left            =   1080
         TabIndex        =   16
         Top             =   960
         Value           =   64
         Width           =   3495
      End
      Begin VB.CommandButton DefaultVal 
         Caption         =   "Default"
         Height          =   375
         Left            =   3000
         TabIndex        =   15
         Top             =   3120
         Width           =   1095
      End
      Begin VB.HScrollBar HScrollBright 
         Height          =   255
         Left            =   1080
         TabIndex        =   3
         Top             =   480
         Value           =   128
         Width           =   3495
      End
      Begin VB.HScrollBar HScrollSaturation 
         Height          =   255
         Left            =   1080
         TabIndex        =   2
         Top             =   1920
         Width           =   3495
      End
      Begin VB.HScrollBar HScrollShappness 
         Height          =   255
         Left            =   1080
         TabIndex        =   1
         Top             =   2400
         Value           =   4
         Width           =   3495
      End
      Begin VB.Label Label1 
         Caption         =   "Brightness："
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   480
         Width           =   735
      End
      Begin VB.Label BrightVal 
         Caption         =   "128"
         Height          =   255
         Left            =   4680
         TabIndex        =   13
         Top             =   480
         Width           =   735
      End
      Begin VB.Label Label2 
         Caption         =   "Contract"
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   960
         Width           =   735
      End
      Begin VB.Label ContrastVal 
         Caption         =   "64"
         Height          =   375
         Left            =   4680
         TabIndex        =   11
         Top             =   960
         Width           =   735
      End
      Begin VB.Label Label3 
         Caption         =   "Saturation:"
         Height          =   375
         Left            =   120
         TabIndex        =   10
         Top             =   1440
         Width           =   975
      End
      Begin VB.Label HueVal 
         Caption         =   "68"
         Height          =   255
         Left            =   4680
         TabIndex        =   9
         Top             =   1440
         Width           =   735
      End
      Begin VB.Label Label4 
         Caption         =   "Hue:"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   1920
         Width           =   735
      End
      Begin VB.Label SatVal 
         Caption         =   "0"
         Height          =   255
         Left            =   4680
         TabIndex        =   7
         Top             =   1920
         Width           =   735
      End
      Begin VB.Label Label5 
         Caption         =   "Sharpness:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   2400
         Width           =   735
      End
      Begin VB.Label ShapVal 
         Caption         =   "4"
         Height          =   255
         Left            =   4680
         TabIndex        =   5
         Top             =   2400
         Width           =   255
      End
      Begin VB.Label NoiseVal 
         Caption         =   "10"
         Height          =   255
         Left            =   4680
         TabIndex        =   4
         Top             =   2880
         Width           =   255
      End
   End
End
Attribute VB_Name = "ColorProtyDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub DefaultVal_Click()
Dim i As Long
     If VideoInfo(CardNo).dwConnectState = True Then
        
        For i = 0 To 4
        
                   Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, i, DeviceColor(i).DefaultVal, 0)
        Next i
        HScrollBright.value = DeviceColor(0).DefaultVal
        BrightVal.Caption = CStr(HScrollBright.value)
        
         HScrollContrast.value = DeviceColor(1).DefaultVal
        ContrastVal.Caption = CStr(HScrollContrast.value)
        
        
         HScrollHue.value = DeviceColor(2).DefaultVal
        HueVal.Caption = CStr(HScrollHue.value)
        
         HScrollSaturation.value = DeviceColor(3).DefaultVal
        SatVal.Caption = CStr(HScrollSaturation.value)
        
        
          Call WritePrivateProfileString("ColorProp", "Saturation", CStr(HScrollSaturation.value), SaveIniFile)
            Call WritePrivateProfileString("ColorProp", "Brightness", CStr(HScrollBright.value), SaveIniFile)
                Call WritePrivateProfileString("ColorProp", "Contrast", CStr(HScrollContrast.value), SaveIniFile)
                  Call WritePrivateProfileString("ColorProp", "Hue", CStr(HScrollHue.value), SaveIniFile)
        
            
    End If

End Sub

Private Sub Form_Load()
   ColorProtyDialog.ScaleMode = 3
   ColorProtyDialog.Top = 4500
   ColorProtyDialog.Left = 9500
   Dim i As Long
   Dim flags As Long
  
     '对控件状态赋值
   ColorProtyDialog.HScrollBright.Max = DeviceColor(0).MaxVal
   ColorProtyDialog.HScrollBright.Min = DeviceColor(0).MinVal
  ' ColorProtyDialog.HScrollBright.LargeChange = DeviceColor(0).StepVal
   ColorProtyDialog.HScrollContrast.Max = DeviceColor(1).MaxVal
   ColorProtyDialog.HScrollContrast.Min = DeviceColor(1).MinVal
  ' ColorProtyDialog.HScrollContrast.LargeChange = DeviceColor(1).StepVal
   ColorProtyDialog.HScrollHue.Max = DeviceColor(2).MaxVal
   ColorProtyDialog.HScrollHue.Min = DeviceColor(2).MinVal
  ' ColorProtyDialog.HScrollHue.LargeChange = DeviceColor(2).StepVal
   ColorProtyDialog.HScrollSaturation.Max = DeviceColor(3).MaxVal
   ColorProtyDialog.HScrollSaturation.Min = DeviceColor(3).MinVal
   ' ColorProtyDialog.HScrollSaturation.LargeChange = DeviceColor(3).StepVal
   ColorProtyDialog.HScrollShappness.Max = DeviceColor(4).MaxVal
   ColorProtyDialog.HScrollShappness.Min = DeviceColor(4).MinVal
  'ColorProtyDialog.HScrollShappness.LargeChange = DeviceColor(4).StepVal
   
   
   
End Sub

Private Sub HScrollBright_Change()
    BrightValue = HScrollBright.value
    BrightVal.Caption = CStr(BrightValue)
       If VideoInfo(CardNo).dwConnectState = True Then
    Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, 0, BrightValue, 0)
    Call WritePrivateProfileString("ColorProp", "Brightness", CStr(BrightValue), SaveIniFile)
    End If
End Sub

Private Sub HScrollContrast_Change()
   '设置视频属性的对比度值
   ContrastValue = HScrollContrast.value
   ContrastVal.Caption = CStr(ContrastValue)
      If VideoInfo(CardNo).dwConnectState = True Then
   Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, 1, ContrastValue, 0)
    '将对比度值写入ini配置文件
   Call WritePrivateProfileString("ColorProp", "Contrast", CStr(ContrastValue), SaveIniFile)
   End If
End Sub

Private Sub HScrollHue_Change()
    HueValue = HScrollHue.value
    HueVal.Caption = CStr(HueValue)
       If VideoInfo(CardNo).dwConnectState = True Then
    Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, 2, HueValue, 0)
    Call WritePrivateProfileString("ColorProp", "Hue", CStr(HueValue), SaveIniFile)
    End If
End Sub

Private Sub HScrollNoise_Change()
    '设置降噪滤波算法值，值越大降噪范围越大，画面越干净

End Sub

Private Sub HScrollSaturation_Change()
   SaturationValue = HScrollSaturation.value
   SatVal.Caption = CStr(SaturationValue)
      If VideoInfo(CardNo).dwConnectState = True Then
   Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, 3, SaturationValue, 0)
   Call WritePrivateProfileString("ColorProp", "Saturation", CStr(SaturationValue), SaveIniFile)
   End If
End Sub

Private Sub HScrollShappness_Change()
   ShappnessValue = HScrollShappness.value
   ShapVal.Caption = CStr(ShappnessValue)
      If VideoInfo(CardNo).dwConnectState = True Then
   Call DXMediaCapApi.DXSetDisplayPara(VideoInfo(CardNo).dwChannelHandle, 4, ShappnessValue, 0)
   Call WritePrivateProfileString("ColorProp", " Sharpness", CStr(ShappnessValue), SaveIniFile)
   End If
   
End Sub

Private Sub OKButton_Click()
      Unload Me
End Sub

