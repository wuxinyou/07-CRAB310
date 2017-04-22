Attribute VB_Name = "DXMediaFunction"
'*==========================================================================*/
'*     (Copyright (C) 2013                    .               */
'*     All rights reserved. Shenzhen ZhongAn Vision                                                 */
'*          %version: 1 %                                                   */
'*                                                                          */
'* Last Update  : %date_modified: tony yu   2810482962@qq.com 7 18:08:00 2013 %                    */
'/*                                                                          */
'* Description: DXMediaCap vb Function                                              */
'*                                                                          */
'*==========================================================================*/



'////////////////////////////////////////////define function////////////////////////////

Public Type BrowseInfo
hwndOwner As Long
pIDLRoot As Long
pszDisplayName As Long
lpszTitle As Long
ulFlags As Long
lpfnCallback As Long
lParam As Long
iImage As Long
End Type

Public Const BIF_RETURNONLYFSDIRS = 1
Public Const MAX_PATH = 260
Public Const HWND_TOPMOST = -1


'定义窗体位置API
Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
'读写ini文件API
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
'文件目录浏览API
Public Declare Sub CoTaskMemFree Lib "ole32.dll" (ByVal hMem As Long)
Public Declare Function lstrcat Lib "kernel32" Alias "lstrcatA" (ByVal lpString1 As String, ByVal lpString2 As String) As Long
Public Declare Function SHBrowseForFolder Lib "shell32" (lpbi As BrowseInfo) As Long
Public Declare Function SHGetPathFromIDList Lib "shell32" (ByVal pidList As Long, ByVal lpBuffer As String) As Long

Public Function BrowseForFolder(hwndOwner As Long, sPrompt As String) As String

'定义变量
Dim iNull As Integer
Dim lpIDList As Long
Dim lResult As Long
Dim sPath As String
Dim udtBI As BrowseInfo

'初始化.....
With udtBI
.hwndOwner = hwndOwner
.lpszTitle = lstrcat(sPrompt, "")
.ulFlags = BIF_RETURNONLYFSDIRS
End With

'调用API
lpIDList = SHBrowseForFolder(udtBI)
'得到返回结果
If lpIDList Then
sPath = String$(MAX_PATH, 0)
lResult = SHGetPathFromIDList(lpIDList, sPath)
Call CoTaskMemFree(lpIDList)
iNull = InStr(sPath, vbNullChar)
If iNull Then sPath = Left$(sPath, iNull - 1)
End If
BrowseForFolder = sPath



End Function


'init the sdk funtion and get the video device number
Function InitDevice() As Long
Dim CardNum As Long
        
        Call DXInitialize
        CardNum = DXGetDeviceCount
        InitDevice = CardNum


End Function

Function UnInitDevice()

    DXUninitialize

End Function

' open the video device
Function OpenDevice(nCard As Long, OpenState As Long) As Long
Dim DeviceHandle As Long

     DeviceHandle = DXOpenDevice(nCard, OpenState)
     OpenDevice = DeviceHandle

End Function

'close the video device
Function CloseDevice(ChannelHandle As Long) As Long

    If DXCloseDevice(ChannelHandle) = 0 Then
    
        CloseDevice = True
        
    
    Else
    
        CloseDevice = False
        
    
    End If
    
    

End Function


'connect the video device
Function ConnectDevice(ChannelHandle As Long, _
                        VideoStandard As Long, _
                        ColorSpace As Long, _
                        nWidth As Long, _
                        nHeight As Long, _
                        framerate As Single) As Boolean
                      
                      
    Call DXSetVideoPara(ChannelHandle, VideoStandard, ColorSpace, nWidth, nHeight, framerate)
    If DXDeviceRun(ChannelHandle) = 0 Then
    
        ConnectDevice = True
        
    Else
    
        ConnectDevice = False
        
    End If
    
                      
End Function
' disconnect the video device
Function DisconnectDevice(ChannelHandle As Long) As Boolean

 
    If DXDeviceStop(ChannelHandle) = 0 Then
    
        DisconnectDevice = True
        
    Else
    
        DisconnectDevice = False
        
    End If
    

End Function

'set the video input  source
Private Sub SetVideoSource(ChannelHandle As Long, VidSource As Long)

     Call DXSetVideoSource(ChannelHandle, VidSource)

End Sub
' start the video preview
Function StartPrview(ChannelHandle As Long, PrvHwnd As Long, PreviewRect As Rect, PrvModel As Long) As Boolean

    If DXStartPreview(ChannelHandle, PrvHwnd, PreviewRect, PrvModel) = 0 Then
    
         StartPrview = True
       
    Else
       
         StartPrview = False
       
    
    End If
 

End Function

'stop the video preview
Function StopPrview(ChannelHandle As Long) As Boolean

   If DXStopPreview(ChannelHandle) = 0 Then
   
        StopPrview = True
    
   Else
   
     StopPrview = False
    
   
   End If
   

End Function

Function FreezePreview(ChannelHandle As Long, bFreeze As Long) As Boolean

    If DXFreezePreview(ChannelHandle, bFreeze) = 0 Then
    
            FreezePreview = True
            
    Else
    
            FreezePreview = False
            
    End If
    
    


End Function
'get the video device property value
Function GetVideoPara(ChannelHandle As Long, _
                      VideoStandard As Long, _
                      ColorSpace As Long, _
                      nWidth As Long, _
                      nHeight As Long, _
                      framerate As Double) As Boolean
                      
                      
       If DXGetVideoPara(ChannelHandle, VideoStandard, ColorSpace, nWidth, nHeight, framerate) = 0 Then
       
            GetVideoPara = True
            
       Else
            GetVideoPara = False
                   
       End If
       
                      
                       
End Function
'get the video device signal state
Function GetSignalPresent(ChannelHandle As Long, signal As Long) As Boolean

    If DXGetSignalPresent(ChannelHandle, signal) = 0 Then
        
            GetSignalPresent = True
            
    Else
            GetSignalPresent = False
            
    
    End If
    

End Function

' snap the picture
Function SnapPicture(ChannelHandle As Long, _
                    szFileName As String, _
                    PictureType As Long, _
                    SnapRect As Rect) As Boolean
                    
Dim ok As Long
ok = 1

     If PictureType = 0 Then
     
        ok = DXSnapToBMPFile(ChannelHandle, szFileName, SnapRect)
     Else
     
         ok = DXSnapToJPGFile(ChannelHandle, szFileName, 100, SnapRect)
     
     End If
    
    If ok = 0 Then
    
            SnapPicture = True
            
    
    Else
            SnapPicture = False
            
    
    End If



End Function

'record the video
Function StartRecord(ChannelHandle As Long, szFileName As String, CodecName As String, H264Para As TVidCodecX264Para, AudioRec As Boolean) As Boolean

Dim VideoCodecInfo(0 To 126) As DEVICE_TAG
Dim VidCodecName(0 To 126) As String

Dim AudioCodecInfo(0 To 126) As DEVICE_TAG
Dim AudCodecName(0 To 126) As String


Dim CodecNum As Long
Dim CurCodec As Long

Dim AudCodecNum As Long
Dim AudCurCodec As Long
Dim i As Long
Dim ok As Long


    CodecNum = 126
    CurCodec = 0
    AudCurCodec = 0
    AudCodecNum = 126
    
    ok = 1
    
    ' enum the video codec in the system
    Call DXEnumVideoCodecs(VideoCodecInfo(0), CodecNum)
     
    ' enum the audio codec in the system
    Call DXEnumVideoCodecs(AudioCodecInfo(0), AudCodecNum)
    
    'set the current video codec
     For i = 0 To CodecNum - 1
         
                 VidCodecName(i) = StrConv(VideoCodecInfo(i).iName, vbUnicode)
               If (StrComp(VidCodecName(i), CodecName) = 1) Then
                  'set the codec type
                
                         CurCodec = i
                         Exit For
            
                End If
            
    Next i
    
    
    'set the current audio codec
     For i = 0 To AudCodecNum - 1
         
                 AudCodecName(i) = StrConv(AudioCodecInfo(i).iName, vbUnicode)
                
                  'set the codec type
                 If (StrComp(AudCodecName(i), "Microsoft ADPCM") = 1) Then
                         AudCurCodec = i
                         Exit For
            
                End If
            
    Next i
    
    
         
  
      If DXSetVideoCodec(ChannelHandle, VideoCodecInfo(CurCodec)) <> 0 Then
    
       MsgBox ("the video codec setting false")
      
    End If
    
    'set the h264 codec property value
     If (StrComp(VidCodecName(CurCodec), "x264 Codec") = 1) Then
   
        
       Call DXSetVideoCodecPara(ChannelHandle, codec_x264, H264Para)
     
     End If
     
     
      'set the xvid codec property value
        If (StrComp(VidCodecName(CurCodec), "xvid Codec") = 1) Then
          
       Call DXSetVideoCodecPara(ChannelHandle, codec_xvid, H264Para)
     
     End If
     
     ' set the audio codec
     If AudioRec = True Then
     
        If DXSetAudioCodec(ChannelHandle, AudioCodecInfo(AudCurCodec)) <> 0 Then
    
            MsgBox ("the audio codec setting false")
      
         End If
     End If
     
  
    
    If DXStartCapture(ChannelHandle, szFileName, False, 0, 0, 0, 1) = 0 Then
    
            StartRecord = True
            
    Else
    
            StartRecord = False
            
    End If
    
    


End Function


'stop the video record
Function StopRecord(ChannelHandle As Long) As Boolean

    If DXStopCapture(ChannelHandle) = 0 Then
    
            StopRecord = True
            
    Else
    
            StopRecord = False
            
    End If
    
    

End Function
' freeze the video record
Function FreezeRecord(ChannelHandle As Long, enable As Boolean) As Boolean

      If DXFreezeCaputre(ChannelHandle, enable) = 0 Then
      
              FreezeRecord = True
        
      
      Else
      
            FreezeRecord = False
            
      End If
      

End Function

'enable the video deinterlace
Function EnableDeinterlace(ChannelHandle As Long, DeintType As Long, enable As Boolean) As Boolean
Dim ok As Long

ok = 1

    ok = DXEnableDeinterlace(ChannelHandle, DeintType)
    
    If enable = False Then
    
             ok = DXEnableDeinterlace(ChannelHandle, -1)
    End If
    
    If ok = 0 Then
            EnableDeinterlace = True
            
    Else
            EnableDeinterlace = False
            
    
    End If
    
    
    
    


End Function

'set the osd property value
Function SetOSDPara(ChannelHandle As Long, _
                    OsdType As Long, _
                    OsdNo As Long, _
                    OsdFile As String, _
                    x As Long, _
                    y As Long, _
                    pointSize As Long, _
                    faceName As String, _
                    OSDcolor As OLE_COLOR, _
                    Backcolor As OLE_COLOR, _
                    transparent As Long, _
                    PicAlpha As Byte)
                    
    Dim ok As Long
    ok = 1
    Select Case OsdType
  
    Case 0
            ok = DXSetTimeOSD(ChannelHandle, x, y, pointSize, faceName, OSDcolor, Backcolor, transparent)
    Case 1
            ok = DXSetTextOSD(ChannelHandle, x, y, OsdNo, OsdFile, pointSize, faceName, OSDcolor, Backcolor, transparent)
    Case 2
            ok = DXSetPictureOSD(ChannelHandle, x, y, OsdNo, OsdFile, transparent, PicAlpha)
    
    End Select
    


     If ok = 0 Then
            SetOSDPara = True
            
     Else
     
            SetOSDPara = False
                
     End If

                    
  
  End Function
  

  'enable the osd function
  
  Function StartOsd(ChannelHandle As Long, OsdType As Long, OsdNo As Long, OSDEnable As Long)
        
        If DXEnOSDDisp(ChannelHandle, OsdType, OsdNo, OSDEnable) = 0 Then
        
               StartOsd = True
               
        Else
                StartOsd = False
        
        End If
        
  
  
  End Function


