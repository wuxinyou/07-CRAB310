VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   8115
   ClientLeft      =   225
   ClientTop       =   855
   ClientWidth     =   13545
   LinkTopic       =   "Form1"
   ScaleHeight     =   541
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   903
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame3 
      Caption         =   "Preview Mode"
      Height          =   2055
      Left            =   11760
      TabIndex        =   14
      Top             =   5400
      Width           =   1455
      Begin VB.OptionButton OptVMR9 
         Caption         =   "VMR9"
         Height          =   255
         Left            =   120
         TabIndex        =   17
         Top             =   1440
         Width           =   1095
      End
      Begin VB.OptionButton OptOFFScrean 
         Caption         =   "OFFscrean"
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Top             =   840
         Width           =   1095
      End
      Begin VB.OptionButton OptVMR7 
         Caption         =   "VMR7"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Cur channel"
      Height          =   975
      Left            =   11760
      TabIndex        =   12
      Top             =   120
      Width           =   1455
      Begin VB.Label CurCamNo 
         Caption         =   "camer1"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   480
         Width           =   975
      End
   End
   Begin VB.Frame Frame1 
      ClipControls    =   0   'False
      Height          =   3975
      Index           =   3
      Left            =   5760
      TabIndex        =   11
      Top             =   3960
      Width           =   5775
   End
   Begin VB.Frame Frame1 
      ClipControls    =   0   'False
      Height          =   3975
      Index           =   2
      Left            =   0
      TabIndex        =   10
      Top             =   3960
      Width           =   5775
   End
   Begin VB.Frame Frame1 
      ClipControls    =   0   'False
      Height          =   3975
      Index           =   1
      Left            =   5760
      TabIndex        =   9
      Top             =   0
      Width           =   5775
   End
   Begin VB.CommandButton btFreezeRec 
      Caption         =   "Pause Record"
      Height          =   375
      Left            =   11760
      TabIndex        =   8
      Top             =   3000
      Width           =   1335
   End
   Begin VB.CommandButton btOsdSet 
      Caption         =   "OSDSetting"
      Height          =   375
      Left            =   11760
      TabIndex        =   7
      Top             =   4800
      Width           =   1335
   End
   Begin VB.CommandButton btExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   11880
      TabIndex        =   6
      Top             =   7680
      Width           =   1335
   End
   Begin VB.CommandButton btRec 
      Caption         =   "Record"
      Height          =   375
      Left            =   11760
      TabIndex        =   5
      Top             =   2400
      Width           =   1335
   End
   Begin VB.CommandButton btCodecSet 
      Caption         =   "CodecSetting"
      Height          =   375
      Left            =   11760
      TabIndex        =   4
      Top             =   3600
      Width           =   1335
   End
   Begin VB.CommandButton btColorProp 
      Caption         =   "ColorSetting"
      Height          =   375
      Left            =   11760
      TabIndex        =   3
      Top             =   4200
      Width           =   1335
   End
   Begin VB.CommandButton btGetcurbuf 
      Caption         =   "GetCurBuff"
      Height          =   375
      Left            =   11760
      TabIndex        =   2
      Top             =   1800
      Width           =   1335
   End
   Begin VB.CommandButton btSnap 
      Caption         =   "Snap Pic"
      Height          =   375
      Left            =   11760
      TabIndex        =   1
      Top             =   1200
      Width           =   1335
   End
   Begin VB.Frame Frame1 
      ClipControls    =   0   'False
      Height          =   3975
      Index           =   0
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   5775
   End
   Begin VB.Menu MenuVideoSize 
      Caption         =   "VideoSize"
      Begin VB.Menu Menu768 
         Caption         =   "768*576"
      End
      Begin VB.Menu MenuD1 
         Caption         =   "720*576"
      End
      Begin VB.Menu MenuCIF 
         Caption         =   "352*288"
      End
   End
   Begin VB.Menu MenuVideoSource 
      Caption         =   "VideoSource"
      Begin VB.Menu MenuAV1 
         Caption         =   "AV1"
      End
      Begin VB.Menu MenuAV2 
         Caption         =   "AV2"
      End
      Begin VB.Menu MenuSvideo 
         Caption         =   "Svideo"
      End
   End
   Begin VB.Menu MenuVideoStand 
      Caption         =   "VideoStandard"
      Begin VB.Menu MenuPal 
         Caption         =   "PAL"
      End
      Begin VB.Menu MenuNtsc 
         Caption         =   "NTSC"
      End
   End
   Begin VB.Menu MenuDeinterlace 
      Caption         =   "Deinterlace"
      Begin VB.Menu MenuLowcpu 
         Caption         =   "Default"
      End
      Begin VB.Menu MenuStandard 
         Caption         =   "Standard"
      End
      Begin VB.Menu MenuGood 
         Caption         =   "Good"
      End
      Begin VB.Menu MenuCancel 
         Caption         =   "Cancel"
      End
   End
   Begin VB.Menu MenuDenoise 
      Caption         =   "ImageAlgorithm"
   End
   Begin VB.Menu MenuVideoEffect 
      Caption         =   "VideoEffects "
      Begin VB.Menu MenuFlipVideo 
         Caption         =   "FlipVideo"
      End
      Begin VB.Menu MenuMirrorVideo 
         Caption         =   "MirrorVideo"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public NumCard As Long
Public CardNo As Long

















Private Sub btCodecSet_Click()
' CodecDialog.Show
 Dim NumCodec As Long
 Dim VideoCodecName(0 To 125) As String
 Dim name(0 To 125) As String
 ReDim VideoCodec(125)
 Dim CurCodec As String
 Dim CurCodecNum As Long
 Dim nIndex As Long
 Dim j As Long
 
 
 CodecDialog.Show
 
 '赋值枚举类型
 Dim i As Long
 For i = 0 To 124
     VideoCodec(i).idx = 0
     VideoCodec(i).iName(i) = 0
 Next i
 
 NumCodec = 125
  
        'Enumeration the video codec in the system
         Call DXMediaCapApi.DXEnumVideoCodecs(VideoCodec(0), NumCodec)
        
         For i = 0 To NumCodec - 1
         
                 VideoCodecName(i) = StrConv(VideoCodec(i).iName, vbUnicode)
                
                CodecDialog.CombVideoCodec.AddItem (VideoCodecName(i))
               
            
               
            
         Next i
        
            CodecDialog.CombVideoCodec.ListIndex = 0
        
 
End Sub

Private Sub btColorProp_Click()
  ColorProtyDialog.Show
End Sub

Private Sub btConnect_Click()
 

End Sub

Private Sub btDisconnect_Click()
End Sub

Private Sub btExit_Click()
  '设置取消叠加时间osd
Call DXMediaFunction.StartOsd(VideoInfo(CardNo).dwChannelHandle, 0, 0, False)

If VideoInfo(CardNo).dwPrviewState = True Then

       Call DXMediaFunction.StopPrview(VideoInfo(CardNo).dwChannelHandle)

End If

If VideoInfo(CardNo).dwConnectState = True Then

     Call DXMediaFunction.DisconnectDevice(VideoInfo(CardNo).dwChannelHandle)

End If


If VideoInfo(CardNo).dwOpenDevState = 0 Then

      Call DXMediaFunction.CloseDevice(VideoInfo(CardNo).dwChannelHandle)

End If

DXMediaFunction.UnInitDevice

   End

End Sub

Private Sub btFreezeRec_Click()

If VideoInfo(CardNo).dwRecOK = True Then

  If VideoInfo(CardNo).dwFreezeOK = False Then
  
            'freeze recording
        VideoInfo(CardNo).dwFreezeOK = DXMediaFunction.FreezeRecord(VideoInfo(CardNo).dwChannelHandle, True)
        
         btFreezeRec.Caption = "Stop Freeze"
        
  
  Else
            ' stop freeze recording
          VideoInfo(CardNo).dwFreezeOK = DXMediaFunction.FreezeRecord(VideoInfo(CardNo).dwChannelHandle, False)
        
         btFreezeRec.Caption = "FreezeRec"
          VideoInfo(CardNo).dwFreezeOK = False
          
  
  
  End If
  

End If




End Sub

Private Sub btGetcurbuf_Click()
    Dim pBuf() As Byte
    Dim nBufSize As Long
    nBufSize = 1244160
    ReDim pBuf(nBufSize) As Byte
    Dim SaveFile As String
    
    Dim ColorSpace As Long
    Dim nWidth As Long
    Dim nHeight As Long
    Dim gotBufferLen As Long
    Dim byteswidth As Long
    Dim GetBufSize As Long
    Dim GetRect As Rect
    
    SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".bmp", strPicPath + "\")
    
    If VideoInfo(CardNo).dwOpenDevState = 0 Then
             'get the cur buf address  video stream format :yuv2
             Call DXMediaCapApi.DXGetFrameBuffer(VideoInfo(CardNo).dwChannelHandle, pBuf(0), nBufSize, GetBufSize, ColorSpace, nWidth, nHeight, byteswidth, GetRect)
             
            Call DXMediaCapApi.DXSaveBMPFile(SaveFile, pBuf(0), GetBufSize, ColorSpace, nWidth, nHeight, byteswidth)
            
                SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".jpg", strPicPath + "\")
             Call DXMediaCapApi.DXSaveJPGFile(SaveFile, pBuf(0), GetBufSize, ColorSpace, nWidth, nHeight, byteswidth, 100)
             
              MsgBox ("snap ok" + SaveFile)
   End If
   
    
End Sub

Private Sub btOsdSet_Click()
OsdSettingDialog.Show
End Sub

Private Sub btRec_Click()
Dim SaveFile As String

      SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".avi", strRecPath + "\")
  If VideoInfo(CardNo).dwVideoCodecStr = "x264 Codec" Then
      
        '//set the h264 codec parameter
     VideoInfo(CardNo).dwH264para.Bitrate = 0
    VideoInfo(CardNo).dwH264para.fps = 25
    VideoInfo(CardNo).dwH264para.keyframeinterval = 110
    VideoInfo(CardNo).dwH264para.rcMode = codec_VBR
    VideoInfo(CardNo).dwH264para.Quality = 13
    SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".mp4", strRecPath + "\")
  
  End If
  
    If VideoInfo(CardNo).dwVideoCodecStr = "xvid Codec" Then
      
        '//set the xvid codec parameter
     VideoInfo(CardNo).dwH264para.Bitrate = 1280
    VideoInfo(CardNo).dwH264para.fps = 25
    VideoInfo(CardNo).dwH264para.keyframeinterval = 110
    VideoInfo(CardNo).dwH264para.rcMode = codec_VBR
    VideoInfo(CardNo).dwH264para.Quality = 4
         SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".avi", strRecPath + "\")
  
  End If
  
  

    
  

 If VideoInfo(CardNo).dwOpenDevState = 0 Then

        If VideoInfo(CardNo).dwRecOK = False Then
            
              
          
           
             VideoInfo(CardNo).dwRecOK = DXMediaFunction.StartRecord(VideoInfo(CardNo).dwChannelHandle, _
                                                                     SaveFile, _
                                                                     VideoInfo(CardNo).dwVideoCodecStr, _
                                                                    VideoInfo(CardNo).dwH264para, _
                                                                    False)
                                                            
                btRec.Caption = "Stop Rec"
                VideoInfo(CardNo).dwRecOK = True
            
            Else
            
                    DXMediaFunction.StopRecord (VideoInfo(CardNo).dwChannelHandle)
                    VideoInfo(CardNo).dwRecOK = False
                    btRec.Caption = "Record"
                      MsgBox "snap ok:  " + SaveFile
                   
            
            End If
            
            
            
End If

End Sub

Private Sub btSnap_Click()
Dim SaveFile As String




'Snap rect setting
VideoInfo(CardNo).dwSnapPicRect.Top = 0
VideoInfo(CardNo).dwSnapPicRect.Left = 0
VideoInfo(CardNo).dwSnapPicRect.Right = VideoInfo(CardNo).dwWidth
VideoInfo(CardNo).dwSnapPicRect.Bottom = VideoInfo(CardNo).dwHeight

SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".bmp", strPicPath + "\")

If VideoInfo(CardNo).dwOpenDevState = 0 Then

    Call DXMediaFunction.SnapPicture(VideoInfo(CardNo).dwChannelHandle, SaveFile, 0, VideoInfo(CardNo).dwSnapPicRect)
    
    
    'save to jpg files
    SaveFile = DXMediaCapApi.CreateCaptureFile(0, ".jpg", strPicPath + "\")
    
    Call DXMediaFunction.SnapPicture(VideoInfo(CardNo).dwChannelHandle, SaveFile, 1, VideoInfo(CardNo).dwSnapPicRect)
    
       MsgBox ("snap ok" + SaveFile)

End If
End Sub

Private Sub Form_Load()
    Dim i As Long
    Dim m_nWndNum As Long
    Dim m_nShowMode As Long
    Dim PrvWidth As Long
    Dim PrvHeight As Long
    
 

    SaveIniFile = App.Path & "\" & "VBsetting.ini"
    
 
     MenuAV1.Checked = True
     MenuPal.Checked = True
     
    ImageFlip = False
    ImageMirr = False

     
     RecEnable = False
     
     For i = 0 To 23
     
     VideoInfo(i).dwRecOK = False
     VideoInfo(i).dwOpenDevState = 1
     
     Next i
     
  
    
     '赋值通道号
        Dim Result As Long
        Dim BufferStr As String * 255
        '///////////////////read the ini value start///////////////  get the video or picture file save file path
        Result = GetPrivateProfileString("SystemSetting", "RecVideoPath", "d:\Video", BufferStr, Len(BufferStr), SaveIniFile)
       strRecPath = Left(BufferStr, Result)
       
        Result = GetPrivateProfileString("SystemSetting", "PicturePath", "d:\Pic", BufferStr, Len(BufferStr), SaveIniFile)
       strPicPath = Left(BufferStr, Result)
    
        CodecDialog.RecPath.Text = strRecPath
        CodecDialog.SnapPath.Text = strPicPath
        
        '/////////////////////get the video codec form the ini file
        
        Result = GetPrivateProfileString("SystemSetting", "VideoCodec", "x264 Codec", BufferStr, Len(BufferStr), SaveIniFile)
        
        VideoInfo(CardNo).dwVideoCodecStr = Left(BufferStr, Result)
        
  
          If VideoInfo(CardNo).dwVideoCodecStr = "x264 Codec" Then
        
                CodecDialog.obH264.value = True
        
        End If
        

        
          If VideoInfo(CardNo).dwVideoCodecStr = "DivX? 5.1.1 Codec" Then
        
                CodecDialog.obDivx.value = True
        
        End If
        
        
          If VideoInfo(CardNo).dwVideoCodecStr = "Xvid MPEG-4 Codec" Then
        
                CodecDialog.obXvid.value = True
        
        End If
        
              
      '////////////////////////////////get the preview mode form the ini file////
      
        Result = GetPrivateProfileString("SystemSetting", "PrviewMode", "VMR7", BufferStr, Len(BufferStr), SaveIniFile)
         PreviewType = Left(BufferStr, Result)
         
         If PreviewType = "VMR7" Then
                dwPreviewMode = 0
                OptVMR7.value = True
         
         End If
         
          If PreviewType = "OFFScrean" Then
                dwPreviewMode = 1
                OptOFFScrean.value = True
         
         End If
         
         
         
          If PreviewType = "VMR9" Then
                dwPreviewMode = 2
                OptVMR9.value = True
         
         End If
         
         
      
        
        
     '///////////////////////////read the ini value end ///////////////////////////
    CardNo = 0
    
    '视频参数结构赋值  standard=32 pal  standard=1 NTSC
    
   
    
    Dim j As Long
    
  
    
    '得到预览窗体的矩形区域
    Call DXMediaCapApi.GetClientRect(Frame1(j).hwnd, VideoInfo(j).dwPrvRect)
    
    VideoInfo(j).dwPrvHandle = Frame1(j).hwnd
    
   
    
    
    'init the sdk get the device num
   
    NumCard = DXMediaFunction.InitDevice
  
    '单路窗体显示
       If NumCard < 2 Then
       

                  m_nWndNum = 1
                  m_nShowMode = 1
                  '1分屏显示时预览窗体大小
                PrvWidth = Round(((Form1.ScaleWidth - 125) / m_nShowMode) / 4) * 4
                PrvHeight = Round(((Form1.ScaleHeight - 10) / m_nShowMode) / 4) * 4
                For i = 1 To 3
                
                   Frame1(i).Visible = False
                   
                   
                
                Next i
                
                 Frame1(0).Backcolor = RGB(0, 0, 255)
                  Frame1(0).BorderStyle = 0
                  
                 
             

       End If
         '4 screen preview mode
       If (NumCard > 1) And (NumCard < 5) Then
      

                  m_nWndNum = 4
                  m_nShowMode = 2
                 '4 screen preview mode  the windows size
                PrvWidth = Round(((Form1.ScaleWidth - 105) / m_nShowMode) / 4) * 4
                PrvHeight = Round(((Form1.ScaleHeight - 10) / m_nShowMode) / 4) * 4
                
                 For i = 0 To m_nWndNum - 1
                
                   Frame1(i).Visible = True
                    Frame1(i).Backcolor = RGB(0, 0, 255)
                     Frame1(i).BorderStyle = 0
                     
                
                Next i

       End If
       
       
         For i = 0 To m_nShowMode - 1
        
                For j = 0 To m_nShowMode - 1
                
                  nIndex = i * m_nShowMode + j
                  If nIndex >= m_nWndNum Then
                  
                        Exit For
                        
            
                  End If
                 Frame1(nIndex).Left = PrvWidth * j
                 Frame1(nIndex).Top = PrvHeight * i
                Frame1(nIndex).width = PrvWidth
                Frame1(nIndex).height = PrvHeight
                   

                Next j


          Next i
    
  
    If NumCard <= 0 Then
    
        MsgBox ("Init sdk False ,please check card valid?")
    
    Else
        
          If NumCard > 0 Then
                  
                     For j = 0 To NumCard - 1
                     
                       '得到预览窗体的矩形区域
                        Call DXMediaCapApi.GetClientRect(Frame1(j).hwnd, VideoInfo(j).dwPrvRect)
    
                         VideoInfo(j).dwPrvHandle = Frame1(j).hwnd
                     
                             VideoInfo(j).dwVidStandard = 32
                            VideoInfo(j).dwColorspace = 2
                            VideoInfo(j).dwWidth = 720
                            VideoInfo(j).dwHeight = 576
                            VideoInfo(j).dwFrameRate = 25
                                
                            'open device ,get the channel handle
                            VideoInfo(j).dwChannelHandle = DXMediaFunction.OpenDevice(j, VideoInfo(j).dwOpenDevState)
                         
                            If VideoInfo(j).dwOpenDevState <> 0 Then
                                      MsgBox ("Open device false")
                                      
                            End If
                            
                            VideoInfo(j).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(j).dwChannelHandle, _
                                                                                             VideoInfo(j).dwVidStandard, _
                                                                                             VideoInfo(j).dwColorspace, _
                                                                                             VideoInfo(j).dwWidth, _
                                                                                             VideoInfo(j).dwHeight, _
                                                                                              VideoInfo(j).dwFrameRate)
                            If VideoInfo(j).dwConnectState = True Then
                            
                                 VideoInfo(j).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(j).dwChannelHandle, _
                                                                                                VideoInfo(j).dwPrvHandle, _
                                                                                                VideoInfo(j).dwPrvRect, _
                                                                                                dwPreviewMode)
                                                                                            
                            
                    
                            End If
                            
                            
                             If VideoInfo(j).dwPrviewState = False Then
                             
                                     MsgBox ("Start preview false")
                             
                             End If
                     Next j
                     
                    
                      
            End If
            
             '得到个属性值的最小值，最大值，步进，默认值
   If VideoInfo(CardNo).dwConnectState = True Then
   
        For i = 0 To 4
        Call DXMediaCapApi.DXGetDisplayParaRange(VideoInfo(CardNo).dwChannelHandle, i, DeviceColor(i).MinVal, DeviceColor(i).MaxVal, DeviceColor(i).StepVal, DeviceColor(i).DefaultVal, flags)
   Next i
   
   
  
 
   
   End If
   
   
             '/////////////////get the colorproperty value form the ini file
                
'               '  Result = GetPrivateProfileString("ColorProp", "Brightness", "5000", BufferStr, Len(BufferStr), SaveIniFile)
'                  ColorProtyDialog.BrightVal.Caption = Left(BufferStr, Result)
'                 ColorProtyDialog.HScrollBright.value = Val(Left(BufferStr, Result))
'
'
'                  Result = GetPrivateProfileString("ColorProp", "Contrast", "5000", BufferStr, Len(BufferStr), SaveIniFile)
'                  ColorProtyDialog.ContrastVal.Caption = Left(BufferStr, Result)
'                ColorProtyDialog.HScrollContrast.value = Val(Left(BufferStr, Result))
'
'
'                 Result = GetPrivateProfileString("ColorProp", "Saturation", "5000", BufferStr, Len(BufferStr), SaveIniFile)
'                  ColorProtyDialog.SatVal.Caption = Left(BufferStr, Result)
'                 ColorProtyDialog.HScrollSaturation.value = Val(Left(BufferStr, Result))
'
'
'                  Result = GetPrivateProfileString("ColorProp", "Hue", "5000", BufferStr, Len(BufferStr), SaveIniFile)
'                  ColorProtyDialog.HueVal.Caption = Left(BufferStr, Result)
'                ColorProtyDialog.HScrollHue.value = Val(Left(BufferStr, Result))
                
                          
    End If

End Sub

Private Sub Form_Unload(Cancel As Integer)
   If VideoInfo(CardNo).dwPrviewState = True Then

       Call DXMediaFunction.StopPrview(VideoInfo(CardNo).dwChannelHandle)

End If

If VideoInfo(CardNo).dwConnectState = True Then

     Call DXMediaFunction.DisconnectDevice(VideoInfo(CardNo).dwChannelHandle)

End If


If VideoInfo(CardNo).dwOpenDevState = 0 Then

      Call DXMediaFunction.CloseDevice(VideoInfo(CardNo).dwChannelHandle)

End If

DXMediaFunction.UnInitDevice

    
End Sub

Private Sub Frame1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Select Case Index
 Case 0

    CardNo = 0
    CurCamNo.Caption = "camera1"
Case 1
        CardNo = 1
    CurCamNo.Caption = "camera2"
Case 2
CardNo = 2
    CurCamNo.Caption = "camera3"
Case 3
    CardNo = 3
    CurCamNo.Caption = "camera4"
    
    End Select
    

End Sub

Private Sub Menu768_Click()

Menu768.Checked = True
MenuD1.Checked = False
MenuCIF.Checked = False

If VideoInfo(CardNo).dwOpenDevState = 0 Then


    If VideoInfo(CardNo).dwVidStandard = 32 Then
    
            If VideoInfo(CardNo).dwWidth <> 768 Then
            
                    If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    VideoInfo(CardNo).dwWidth = 768
                    VideoInfo(CardNo).dwHeight = 576
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
            
            
            End If
         
    
    Else
    
              If VideoInfo(CardNo).dwWidth <> 768 Then
              
                     If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    VideoInfo(CardNo).dwWidth = 768
                    VideoInfo(CardNo).dwHeight = 480
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
              
              End If
              
    
    
    End If

End If




End Sub

Private Sub MenuAV1_Click()
 If VideoInfo(CardNo).dwConnectState = True Then
    
        '   设置视频输入端口为AV1
        Call DXMediaCapApi.DXSetVideoSource(VideoInfo(CardNo).dwChannelHandle, 1)
        MenuAV1.Checked = True
        MenuAV2.Checked = False
        MenuSvideo.Checked = False
    
    End If
End Sub

Private Sub MenuAV2_Click()
     If VideoInfo(CardNo).dwConnectState = True Then
    
        Call DXMediaCapApi.DXSetVideoSource(VideoInfo(CardNo).dwChannelHandle, 2)
        MenuAV1.Checked = False
        MenuAV2.Checked = True
        MenuSvideo.Checked = False
    
    End If
End Sub

Private Sub MenuCancel_Click()

   MenuCancel.Checked = True
   MenuGood.Checked = False
   MenuStandard.Checked = False
   MenuLowcpu.Checked = False
   Call DXMediaCapApi.DXEnableDeinterlace(VideoInfo(CardNo).dwChannelHandle, 4)

  
End Sub

Private Sub MenuCIF_Click()
Menu768.Checked = False
MenuD1.Checked = False
MenuCIF.Checked = True

If VideoInfo(CardNo).dwOpenDevState = 0 Then


    If VideoInfo(CardNo).dwVidStandard = 32 Then
    
            If VideoInfo(CardNo).dwWidth <> 352 Then
            
                    If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    VideoInfo(CardNo).dwWidth = 352
                    VideoInfo(CardNo).dwHeight = 288
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
            
            
            End If
         
    
  End If

End If


End Sub

Private Sub MenuD1_Click()
Menu768.Checked = False
MenuD1.Checked = True
MenuCIF.Checked = False

If VideoInfo(CardNo).dwOpenDevState = 0 Then


    If VideoInfo(CardNo).dwVidStandard = 32 Then
    
            If VideoInfo(CardNo).dwWidth <> 720 Then
            
                    If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    VideoInfo(CardNo).dwWidth = 720
                    VideoInfo(CardNo).dwHeight = 576
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
            
            
            End If
         
    
    Else
    
              If VideoInfo(CardNo).dwWidth <> 720 Then
              
                     If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    VideoInfo(CardNo).dwWidth = 720
                    VideoInfo(CardNo).dwHeight = 480
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
              
              End If
              
    
    
    End If

End If


End Sub

Private Sub MenuDenoise_Click()
  DenoiseDialog.Show
End Sub

Private Sub MenuDevice_Click()
   DeviceDialog.Show
End Sub

Private Sub MenuFlipVideo_Click()

   'seting the video flip
   If VideoInfo(CardNo).dwConnectState = True Then
            If ImageFlip = False Then
            
                 Call DXMediaCapApi.DXFlipVideo(VideoInfo(CardNo).dwChannelHandle, True)
                 
                 ImageFlip = True
                 
                 MenuFlipVideo.Checked = True
                 
            Else
            
                 Call DXMediaCapApi.DXFlipVideo(VideoInfo(CardNo).dwChannelHandle, False)
                 
                 ImageFlip = False
                 
                 MenuFlipVideo.Checked = False
            
            End If
    End If
End Sub

Private Sub MenuGood_Click()
   
        MenuGood.Checked = True
        
        MenuStandard.Checked = False
        MenuCancel.Checked = False
          MenuLowcpu.Checked = False
        
        
        Call DXMediaCapApi.DXEnableDeinterlace(VideoInfo(CardNo).dwChannelHandle, 2)

End Sub

Private Sub MenuLowcpu_Click()
    MenuGood.Checked = False
    
    MenuStandard.Checked = False
    MenuCancel.Checked = False
    MenuLowcpu.Checked = True
    
        
        Call DXMediaCapApi.DXEnableDeinterlace(VideoInfo(CardNo).dwChannelHandle, 0)
End Sub

Private Sub MenuMirrorVideo_Click()
       'seting the video mirror
   If VideoInfo(CardNo).dwConnectState = True Then
            If ImageMirr = False Then
            
                 Call DXMediaCapApi.DXMirrorVideo(VideoInfo(CardNo).dwChannelHandle, True)
                 
                 ImageMirr = True
                 
                 MenuMirrorVideo.Checked = True
                 
            Else
            
                 Call DXMediaCapApi.DXMirrorVideo(VideoInfo(CardNo).dwChannelHandle, False)
                 
                 ImageMirr = False
                 
                 MenuMirrorVideo.Checked = False
            
            End If
    End If
End Sub

Private Sub MenuNtsc_Click()

       MenuPal.Checked = False
       MenuNtsc.Checked = True
       
       If VideoInfo(CardNo).dwOpenDevState = 0 Then


    If VideoInfo(CardNo).dwVidStandard <> 1 Then
    
           
                    If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                  If VideoInfo(CardNo).dwHeight > 480 Then
                  
                          VideoInfo(CardNo).dwHeight = 480
                    
                    End If
                    VideoInfo(CardNo).dwFrameRate = 30
                    VideoInfo(CardNo).dwVidStandard = 1
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
            
            
            End If
         
    
   

End If

     
End Sub

Private Sub MenuPal_Click()

      MenuPal.Checked = True
      MenuNtsc.Checked = False
      
If VideoInfo(CardNo).dwOpenDevState = 0 Then


    If VideoInfo(CardNo).dwVidStandard <> 32 Then
    
           
                    If VideoInfo(CardNo).dwPrviewState = True Then
                    
                            DXMediaFunction.StopPrview (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                    If VideoInfo(CardNo).dwConnectState = True Then
                    
                            DXMediaFunction.DisconnectDevice (VideoInfo(CardNo).dwChannelHandle)
                    
                    End If
                    
                  If VideoInfo(CardNo).dwHeight = 480 Then
                  
                           VideoInfo(CardNo).dwHeight = 576
                    
                   End If
                    VideoInfo(CardNo).dwFrameRate = 25
                    VideoInfo(CardNo).dwVidStandard = 32
                    
                     VideoInfo(CardNo).dwConnectState = DXMediaFunction.ConnectDevice(VideoInfo(CardNo).dwChannelHandle, _
                                                                                     VideoInfo(CardNo).dwVidStandard, _
                                                                                     VideoInfo(CardNo).dwColorspace, _
                                                                                     VideoInfo(CardNo).dwWidth, _
                                                                                     VideoInfo(CardNo).dwHeight, _
                                                                                      VideoInfo(CardNo).dwFrameRate)
                                   
                    VideoInfo(CardNo).dwPrviewState = DXMediaFunction.StartPrview(VideoInfo(CardNo).dwChannelHandle, _
                                                                                        VideoInfo(CardNo).dwPrvHandle, _
                                                                                        VideoInfo(CardNo).dwPrvRect, _
                                                                                        dwPreviewMode)
            
            
            End If
         
    
   

End If


    
  
End Sub

Private Sub MenuStandard_Click()

    MenuStandard.Checked = True
    MenuCancel.Checked = False
   MenuLowcpu.Checked = False
    MenuGood.Checked = False
     Call DXMediaCapApi.DXEnableDeinterlace(VideoInfo(CardNo).dwChannelHandle, 1)
      
End Sub

Private Sub MenuSvideo_Click()
    If VideoInfo(CardNo).dwConnectState = True Then
    
        Call DXMediaCapApi.DXSetVideoSource(VideoInfo(CardNo).dwChannelHandle, 3)
        MenuAV1.Checked = False
        MenuAV2.Checked = False
        MenuSvideo.Checked = True
    
    End If
End Sub

Private Sub OptOFFScrean_Click()
Call WritePrivateProfileString("SystemSetting", "PrviewMode", "OFFScrean", SaveIniFile)
End Sub

Private Sub OptVMR7_Click()
Call WritePrivateProfileString("SystemSetting", "PrviewMode", "VMR7", SaveIniFile)
End Sub

Private Sub OptVMR9_Click()
Call WritePrivateProfileString("SystemSetting", "PrviewMode", "VMR9", SaveIniFile)
End Sub
