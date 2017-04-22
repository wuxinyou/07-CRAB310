VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form OsdSettingDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "OSD Setting"
   ClientHeight    =   7530
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   10065
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   502
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   671
   ShowInTaskbar   =   0   'False
   Begin VB.CheckBox TextTranspar2 
      Caption         =   "Enable Transparence"
      Height          =   375
      Left            =   7080
      TabIndex        =   48
      Top             =   840
      Width           =   2295
   End
   Begin VB.TextBox TxtFontSize2 
      Height          =   285
      Left            =   8040
      TabIndex        =   42
      Text            =   "25"
      Top             =   2280
      Width           =   975
   End
   Begin VB.TextBox OsdText2 
      Height          =   285
      Left            =   8040
      TabIndex        =   41
      Text            =   "camera2"
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox OsdText1 
      Height          =   285
      Left            =   4560
      TabIndex        =   40
      Text            =   "camera1"
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox TxtFontSize1 
      Height          =   285
      Left            =   4560
      TabIndex        =   39
      Text            =   "25"
      Top             =   2280
      Width           =   975
   End
   Begin VB.TextBox TextPlaceY2 
      Height          =   285
      Left            =   8040
      TabIndex        =   38
      Text            =   "150"
      Top             =   1800
      Width           =   975
   End
   Begin VB.Frame Frame2 
      Caption         =   "TextOSD2"
      Height          =   3735
      Index           =   1
      Left            =   6720
      TabIndex        =   29
      Top             =   120
      Width           =   3255
      Begin VB.CheckBox TextOsd2 
         Caption         =   "Enable Txt2 OSD"
         Height          =   255
         Left            =   360
         TabIndex        =   46
         Top             =   360
         Width           =   2055
      End
      Begin VB.CommandButton TxtSetColor2 
         Caption         =   "ColorSetting"
         Height          =   375
         Left            =   1200
         TabIndex        =   44
         Top             =   3240
         Width           =   1215
      End
      Begin VB.TextBox TextPlaceX2 
         Height          =   285
         Left            =   1320
         TabIndex        =   36
         Text            =   "10"
         Top             =   1200
         Width           =   975
      End
      Begin VB.Label Label5 
         Caption         =   "Y："
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   34
         Top             =   1680
         Width           =   1095
      End
      Begin VB.Label Label4 
         Caption         =   "X："
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   33
         Top             =   1200
         Width           =   615
      End
      Begin VB.Label Label11 
         Caption         =   "TxtOsd:："
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   32
         Top             =   2640
         Width           =   975
      End
      Begin VB.Label Label9 
         Caption         =   "FontColor:"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   31
         Top             =   3240
         Width           =   975
      End
      Begin VB.Label Label13 
         Caption         =   "FontSize:"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   30
         Top             =   2160
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "TextOSD1"
      Height          =   3735
      Index           =   0
      Left            =   3240
      TabIndex        =   15
      Top             =   120
      Width           =   3255
      Begin VB.CheckBox TextTranspar1 
         Caption         =   "Enable Transparence"
         Height          =   375
         Left            =   240
         TabIndex        =   47
         Top             =   720
         Width           =   2295
      End
      Begin VB.CheckBox TextOsd1 
         Caption         =   "Enable Txt1 OSD"
         Height          =   255
         Left            =   240
         TabIndex        =   45
         Top             =   360
         Width           =   2055
      End
      Begin VB.CommandButton TxtSetColor1 
         Caption         =   "ColorSetting"
         Height          =   375
         Left            =   1320
         TabIndex        =   43
         Top             =   3240
         Width           =   1215
      End
      Begin VB.TextBox TextPlaceY1 
         Height          =   285
         Left            =   1320
         TabIndex        =   37
         Text            =   "100"
         Top             =   1680
         Width           =   975
      End
      Begin VB.TextBox TextPlaceX1 
         Height          =   285
         Left            =   1320
         TabIndex        =   35
         Text            =   "10"
         Top             =   1200
         Width           =   975
      End
      Begin VB.Label Label13 
         Caption         =   "FontSize:"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   28
         Top             =   2160
         Width           =   975
      End
      Begin VB.Label Label9 
         Caption         =   "FontColor:"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   25
         Top             =   3240
         Width           =   975
      End
      Begin VB.Label Label11 
         Caption         =   "TxtOsd:："
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   18
         Top             =   2640
         Width           =   975
      End
      Begin VB.Label Label4 
         Caption         =   "X："
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   17
         Top             =   1200
         Width           =   1095
      End
      Begin VB.Label Label5 
         Caption         =   "Y："
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   16
         Top             =   1680
         Width           =   1095
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "PictureOSD"
      Height          =   2775
      Left            =   120
      TabIndex        =   9
      Top             =   4080
      Width           =   6375
      Begin MSComDlg.CommonDialog ShowColorDig 
         Left            =   5640
         Top             =   360
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.TextBox PicFilePath 
         Height          =   405
         Left            =   1560
         TabIndex        =   20
         Top             =   1560
         Width           =   3015
      End
      Begin VB.CommandButton PicFiles 
         Caption         =   "Brower"
         Height          =   495
         Left            =   4800
         TabIndex        =   19
         Top             =   1440
         Width           =   1455
      End
      Begin VB.CheckBox PicOsd 
         Caption         =   "Enable Picture OSD"
         Height          =   375
         Left            =   240
         TabIndex        =   12
         Top             =   240
         Width           =   2055
      End
      Begin VB.TextBox PictruPlaceX 
         Height          =   285
         Left            =   1320
         TabIndex        =   11
         Text            =   "20"
         Top             =   720
         Width           =   975
      End
      Begin VB.TextBox PictruPlaceY 
         Height          =   285
         Left            =   1320
         TabIndex        =   10
         Text            =   "70"
         Top             =   1080
         Width           =   975
      End
      Begin VB.Label Label12 
         Caption         =   "Picture osd file"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   1440
         Width           =   1575
      End
      Begin VB.Label Label7 
         Caption         =   "X："
         Height          =   255
         Left            =   240
         TabIndex        =   14
         Top             =   720
         Width           =   1335
      End
      Begin VB.Label Label8 
         Caption         =   "Y："
         Height          =   375
         Left            =   240
         TabIndex        =   13
         Top             =   1080
         Width           =   735
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "TimeOSD"
      Height          =   3735
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   2895
      Begin VB.TextBox TimeFontSize 
         Height          =   285
         Left            =   1440
         TabIndex        =   27
         Text            =   "25"
         Top             =   2520
         Width           =   975
      End
      Begin VB.CommandButton TimeSetColor 
         Caption         =   "ColorSetting"
         Height          =   375
         Left            =   1440
         TabIndex        =   23
         Top             =   3120
         Width           =   1095
      End
      Begin VB.CheckBox TimeOsd 
         Caption         =   "Enable time osd"
         Height          =   375
         Left            =   240
         TabIndex        =   6
         Top             =   360
         Width           =   1575
      End
      Begin VB.CheckBox TimeTranspar 
         Caption         =   "Enable Transparence"
         Height          =   495
         Left            =   240
         TabIndex        =   5
         Top             =   720
         Width           =   2415
      End
      Begin VB.TextBox TimePlaceX 
         Height          =   285
         Left            =   1440
         TabIndex        =   4
         Text            =   "10"
         Top             =   1440
         Width           =   975
      End
      Begin VB.TextBox TimePlaceY 
         Height          =   285
         Left            =   1440
         TabIndex        =   3
         Text            =   "50"
         Top             =   2040
         Width           =   975
      End
      Begin VB.Label Label6 
         Caption         =   "FontSize:"
         Height          =   255
         Left            =   240
         TabIndex        =   26
         Top             =   2520
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "FontColor:"
         Height          =   375
         Left            =   240
         TabIndex        =   24
         Top             =   3000
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "X："
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   1440
         Width           =   1335
      End
      Begin VB.Label Label2 
         Caption         =   "Y： "
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   2040
         Width           =   1215
      End
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   6960
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   960
      TabIndex        =   0
      Top             =   6960
      Width           =   1215
   End
   Begin VB.Label Label10 
      Caption         =   "字体颜色："
      Height          =   375
      Left            =   360
      TabIndex        =   22
      Top             =   2640
      Width           =   975
   End
End
Attribute VB_Name = "OsdSettingDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub CancelButton_Click()
   Unload Me
End Sub

Private Sub Form_Load()

    OsdSettingDialog.Top = 2500
    OsdSettingDialog.Left = 8500

    'osd color default value
    TOSDPara(CardNo).TimeColor = RGB(0, 255, 0)
    TOSDPara(CardNo).TxtColor(CardNo) = RGB(0, 255, 0)
    TOSDPara(CardNo).Backcolor = RGB(255, 255, 255)

     'osd font size default value
    TOSDPara(CardNo).TimeFontSizeVal = CLng(TimeFontSize.Text)
    TOSDPara(CardNo).TxtFontSizeVal(0) = CLng(TxtFontSize1.Text)
    TOSDPara(CardNo).TxtFontSizeVal(1) = CLng(TxtFontSize2.Text)


    TOSDPara(CardNo).TimeX = CLng(TimePlaceX.Text)
    TOSDPara(CardNo).TimeY = CLng(TimePlaceY.Text)
    TOSDPara(CardNo).TxtPlaceX(0) = CLng(TextPlaceX1.Text)
    TOSDPara(CardNo).TxtPlaceY(0) = CLng(TextPlaceY1.Text)
    TOSDPara(CardNo).TxtPlaceX(1) = CLng(TextPlaceX2.Text)
    TOSDPara(CardNo).TxtPlaceY(1) = CLng(TextPlaceY2.Text)
    
    
    TOSDPara(CardNo).Osd_Txtstring(0) = OsdText1.Text
    TOSDPara(CardNo).Osd_Txtstring(1) = OsdText2.Text

    TOSDPara(CardNo).TimeFont = "Arial"
    TOSDPara(CardNo).TxtFont(0) = "Arial"
    TOSDPara(CardNo).TxtFont(1) = "Arial"
    
    TimeTranspar.value = Checked
    TimeOsd.value = Checked
    TextOsd1.value = Checked
    TextOsd2.value = Checked
    TextTranspar1.value = Checked
    

    
 
   
   
  
End Sub

Private Sub OKButton_Click()
   '时间osd叠加设置
    If TimeOsd.value = Checked Then
        If TimeTranspar.value = Checked Then
           
              
             Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            0, _
                                            0, _
                                            "", _
                                            TOSDPara(CardNo).TimeX, _
                                            TOSDPara(CardNo).TimeY, _
                                            TOSDPara(CardNo).TimeFontSizeVal, _
                                            TOSDPara(CardNo).TimeFont, _
                                            TOSDPara(CardNo).TimeColor, _
                                            TOSDPara(CardNo).Backcolor, _
                                            1, _
                                            0)
                  
               


             

        Else
              '设置不透明叠加
               
               Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            0, _
                                            0, _
                                            "", _
                                            TOSDPara(CardNo).TimeX, _
                                            TOSDPara(CardNo).TimeY, _
                                            TOSDPara(CardNo).TimeFontSizeVal, _
                                            TOSDPara(CardNo).TimeFont, _
                                            TOSDPara(CardNo).TimeColor, _
                                            TOSDPara(CardNo).Backcolor, _
                                            0, _
                                            0)
        End If
        
        '设置叠加时间osd
             Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 0, 0, 1)


       
    Else
          '设置取消叠加时间osd
           Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 0, 0, 0)

      '  Call WritePrivateProfileString("OsdSetting", "TimeOsd", "Disable", App.Path & "\" & "setting.ini")
    End If
    
  
   

     '文本osd叠加设置
    If TextOsd1.value = Checked Then
         If TextTranspar1.value = Checked Then

               Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            1, _
                                            0, _
                                            TOSDPara(CardNo).Osd_Txtstring(0), _
                                            TOSDPara(CardNo).TxtPlaceX(0), _
                                            TOSDPara(CardNo).TxtPlaceY(0), _
                                            TOSDPara(CardNo).TxtFontSizeVal(0), _
                                             TOSDPara(CardNo).TxtFont(0), _
                                            TOSDPara(CardNo).TxtColor(0), _
                                            TOSDPara(CardNo).Backcolor, _
                                            1, _
                                            0)
        Else
              '设置不透明叠加
           '设置不透明叠加
                 Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            1, _
                                            0, _
                                            TOSDPara(CardNo).Osd_Txtstring(0), _
                                            TOSDPara(CardNo).TxtPlaceX(0), _
                                            TOSDPara(CardNo).TxtPlaceY(0), _
                                            TOSDPara(CardNo).TxtFontSizeVal(0), _
                                             TOSDPara(CardNo).TxtFont(0), _
                                            TOSDPara(CardNo).TxtColor(0), _
                                            TOSDPara(CardNo).Backcolor, _
                                            0, _
                                            0)
        End If
        '设置叠加文本osd
            Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 1, 0, 1)

    Else
       '设置取消叠加文本osd
          Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 1, 0, 0)
    End If



       '文本osd叠加设置
    If TextOsd2.value = Checked Then
         If TextTranspar2.value = Checked Then

               Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            1, _
                                            1, _
                                            TOSDPara(CardNo).Osd_Txtstring(1), _
                                            TOSDPara(CardNo).TxtPlaceX(1), _
                                            TOSDPara(CardNo).TxtPlaceY(1), _
                                            TOSDPara(CardNo).TxtFontSizeVal(1), _
                                             TOSDPara(CardNo).TxtFont(1), _
                                            TOSDPara(CardNo).TxtColor(1), _
                                            TOSDPara(CardNo).Backcolor, _
                                            1, _
                                            0)
        Else
              '设置不透明叠加
           '设置不透明叠加
                 Call DXMediaFunction.SetOSDPara(VideoInfo(CardNo).dwChannelHandle, _
                                            1, _
                                            1, _
                                            TOSDPara(CardNo).Osd_Txtstring(1), _
                                            TOSDPara(CardNo).TxtPlaceX(1), _
                                            TOSDPara(CardNo).TxtPlaceY(1), _
                                            TOSDPara(CardNo).TxtFontSizeVal(1), _
                                             TOSDPara(CardNo).TxtFont(1), _
                                            TOSDPara(CardNo).TxtColor(1), _
                                            TOSDPara(CardNo).Backcolor, _
                                            0, _
                                            0)
        End If
        '设置叠加文本osd
            Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 1, 1, 1)

    Else
       '设置取消叠加文本osd
          Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 1, 1, 0)
    End If

    
    
    
    
    
'     '图片osd叠加设置
'    If PicOsd.value = Checked Then
'
'              '设置透明叠加
'                Call DXSetOSD(CardNo(ChannelNo), osd_time, PicPlaceX, PicPlaceY, "", TimeFontSizeVal, "Arial", TimeColor, Backcolor, True, 0)
'
'             Call DXEnableOSD(CardNo(ChannelNo), osd_image, True)
'
'    Else
'         '设置取消叠加文本osd
'       Call DXEnableOSD(CardNo(ChannelNo), osd_image, False)
'    End If
     
End Sub

Private Sub OsdText_Change()
   TOSDPara(CardNo).Osd_Txtstring(0) = OsdText1.Text
End Sub

Private Sub OsdText2_Change()
TOSDPara(CardNo).Osd_Txtstring(1) = OsdText2.Text
End Sub

Private Sub PicFiles_Click()
    '设置叠加图片文件名
    ShowColorDig.ShowOpen
    PicFilePath.Text = ShowColorDig.FileName
    TOSDPara(CardNo).PicOsdFile = PicFilePath.Text
End Sub




Private Sub PictruPlaceX_Change()

 '叠加图片X坐标
     TOSDPara(CardNo).PicPlaceX(0) = CLng(PictruPlaceX.Text)
End Sub

Private Sub PictruPlaceY_Change()
 '叠加图片Y坐标
     TOSDPara(CardNo).PicPlaceY(0) = CLng(PictruPlaceY.Text)
End Sub

Private Sub TextPlaceX_Change()
     '叠加文本X坐标
    TOSDPara(CardNo).TxtPlaceX(0) = CLng(TextPlaceX1.Text)
End Sub

Private Sub TextPlaceY_Change()
      '叠加文本Y坐标
     TOSDPara(CardNo).TxtPlaceY(0) = CLng(TextPlaceY1.Text)
End Sub

Private Sub TimeFontSize_Change()
     '叠加时间osd字体大小
    TOSDPara(CardNo).TimeFontSizeVal = CLng(TimeFontSize.Text)
End Sub

Private Sub TimePlaceX_Change()
      '叠加时间osd X坐标
    TOSDPara(CardNo).TimeX = CLng(TimePlaceX.Text)
    
   
End Sub

Private Sub TimePlaceY_Change()
    '叠加时间osd Y坐标
     TOSDPara(CardNo).TimeY = CLng(TimePlaceY.Text)
End Sub

Private Sub TimeSetColor_Click()
'   '为对话框设置初始颜色值
'    ShowColorDig.flags = cdlCCRGBInit
'    '设置“取消”为True
'    ShowColorDig.CancelError = True
'    ShowColorDig.color = TimeColor
'    On Error GoTo ErrHandler
'    ShowColorDig.ShowColor
'    TimeColor = ShowColorDig.color
'    Exit Sub
ErrHandler:
End Sub

Private Sub TxtFontSize_Change()
   TOSDPara(CardNo).TxtFontSizeVal(0) = CLng(TxtFontSize1.Text)
End Sub

'Private Sub TxtSetColor_Click()
''为对话框设置初始颜色值
'    ShowColorDig.flags = cdlCCRGBInit
'    '设置“取消”为True
'    ShowColorDig.CancelError = True
'    ShowColorDig.color = TextColor
'    On Error GoTo ErrHandler
'    ShowColorDig.ShowColor
'    TextColor = ShowColorDig.color
'    Exit Sub
'    '按取消退出窗体
'ErrHandler:
'End Sub
