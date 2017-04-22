Attribute VB_Name = "DXMediaCapApi"
'*==========================================================================*/
'*     (Copyright (C) 2013                    .               */
'*     All rights reserved.                                                 */
'*          %version: 1 %                                                   */
'*                                                                          */
'* Last Update  : %date_modified: tony yu   yyhnet@163.com 7 18:08:00 2008 %                    */
'/*                                                                          */
'* Description: DXMediaCap vb api                                              */
'*                                                                          */
'*==========================================================================*/
'error message define






Public BrightValue As Long
Public HueValue As Long
Public ContrastValue As Long
Public SaturationValue As Long
Public ShappnessValue As Long
Public NoiseValue As Long
Public BrightDefault As Long
Public HueDefault As Long
Public ContrastDefault As Long
Public SaturationDefault As Long
Public ShappnessDefault As Long
Public strPicPath As String
Public strRecPath As String
Public SaveIniFile As String



 Enum TosdType
    osd_text = 0    ' // Overlay
    osd_time = 1       '// D3D
    osd_image = 2     ' // Offset screen
End Enum





'////////////////////////////////
    Public Type TDRateColor_Para
        nBrightness As Long  ' // 亮度增强，取值(-255到255)
        nContrast As Long   ' //对比度增强，取值(-100到100)
    End Type
    
    Public RateColorPara As TDRateColor_Para
    Enum TRcmode
    
      codec_CBR = 0
      codec_VBR = 1
    End Enum
    Enum TcodecType
        
        codec_sys = 0
        codec_x264 = 1
        codec_xvid = 2
    End Enum
    
    Public Type TVidCodecSysPara
        Bitrate As Long    ' // 码率（单位：kbps）
        keyinterval As Long  '  //关键帧间隔
    End Type
    
    
    
    Public Type TVidCodecX264Para
        fps As Long
        keyframeinterval As Long
        rcMode As Long  '   //码率控制,codec_x264：x264_CBR(恒定码率)/x264_VBR(平均码率)；  codec_xvid：xvid_CBR（(恒定码率)/xvid_VBR(平均码率)
         Maxrbps As Long  '  //VBR有效，默认值4000000,位率范围:56bps ~ 10Mbps; 单位Kbps
         Peekbps As Long   ' / /VBR有效，默认值10000000bps,位率范围:56bps ~ 10Mbps; 单位Kbps
        Quality As Long ' //codec_xvid: 1 ~ 31 (1为最小量度，压缩质量最好)
        Bitrate As Long '//码率（Kbps），默认值256，x264中为0时，编码器内部自己计算
    End Type
    
    Public Type Rect
        Left As Long
        Top As Long
        Right As Long
        Bottom As Long
    End Type
    Public PrvRect As Rect
    
 
    


Public Type VideoPara
    dwChannelHandle As Long
    dwPrvHandle As Long
    dwPrvRect As Rect
    dwSnapPicRect As Rect
    dwHeight As Long
    dwWidth As Long
    dwFrameRate As Single
    dwColorspace As Long
    dwVidStandard As Long
    dwOpenDevState As Long
    dwConnectState As Boolean
    dwPrviewState As Boolean
    dwRecOK As Boolean
    dwFreezeOK As Boolean
    dwVideoCodecStr As String
    dwH264para As TVidCodecX264Para
    
    
 End Type
 
Public VideoInfo(0 To 23) As VideoPara

Public Type Device_Color
       MinVal As Long
       MaxVal As Long
       StepVal As Long
       DefaultVal As Long
       
End Type

 Public DeviceColor(0 To 23) As Device_Color
 
Public Type DEVICE_TAG
   idx As Long
   iName(0 To 127) As Byte
End Type



Public Type TOSD_Para

        TimeX As Long
        TimeY As Long
        TxtPlaceX(0 To 23) As Long
        TxtPlaceY(0 To 23) As Long
        PicPlaceX(0 To 23) As Long
        PicPlaceY(0 To 23) As Long
        TimeFontSizeVal As Long
        TxtFontSizeVal(0 To 23) As Long
        Osd_Txtstring(0 To 23) As String
        PicOsdFile As String
        TimeFont As String
        TxtFont(0 To 23) As String
        TxtColor(0 To 23) As OLE_COLOR
        TimeColor As OLE_COLOR
        Backcolor As OLE_COLOR
        Alpha(0 To 23) As Byte
        

End Type

Public TOSDPara(0 To 23) As TOSD_Para



Public VideoCodec() As DEVICE_TAG

Public VideoDevice() As DEVICE_TAG








' init sdk resource
Declare Function DXInitialize Lib "DXMediaCap.dll" () As Long
'uninit sdk resource
Declare Function DXUninitialize Lib "DXMediaCap.dll" () As Long
'get sdk version
Declare Function DXGetDeviceCount Lib "DXMediaCap.dll" () As Long
Declare Function DXOpenDevice Lib "DXMediaCap.dll" (ByVal idx As Long, ByRef err As Long) As Long
Declare Function DXCloseDevice Lib "DXMediaCap.dll" (ByVal idx As Long) As Long

Declare Function DXDeviceRun Lib "DXMediaCap.dll" (ByVal device As Long) As Long
Declare Function DXDevicePause Lib "DXMediaCap.dll" (ByVal device As Long) As Long
Declare Function DXDeviceStop Lib "DXMediaCap.dll" (ByVal device As Long) As Long
Declare Function DXGetDeviceState Lib "DXMediaCap.dll" (ByVal device As Long, ByRef state As Long) As Long

Declare Function DXStartPreview Lib "DXMediaCap.dll" (ByVal device As Long, ByVal hwnd As Long, ByRef Rect As Rect, ByVal vmrtype As Long) As Long
Declare Function DXStopPreview Lib "DXMediaCap.dll" (ByVal device As Long) As Long
Declare Function DXFreezePreview Lib "DXMediaCap.dll" (ByVal device As Long, ByVal bFreeze As Boolean) As Long

Declare Function DXEnumVideoDevices Lib "DXMediaCap.dll" (devTags As DEVICE_TAG, ByRef Num As Long) As Long

Declare Function DXStartCapture Lib "DXMediaCap.dll" _
(ByVal device As Long, ByVal szFileName As String, ByVal saveAudio As Boolean, _
ByRef timeSize As Long, ByRef dataSize As Long, ByRef saveNotify As Long, ByVal vidRatio As Long) As Long

Declare Function DXStopCapture Lib "DXMediaCap.dll" (ByVal device As Long) As Long

Declare Function DXFreezeCaputre Lib "DXMediaCap.dll" (ByVal device As Long, ByVal bFreeze As Boolean) As Long

Declare Function DXEnableDeinterlace Lib "DXMediaCap.dll" (ByVal device As Long, ByVal deinterlace As Long) As Long


Declare Function DXEnableDenoise Lib "DXMediaCap.dll" (ByVal device As Long, ByVal denoise As Long) As Long

Declare Function DXEnableSharpen Lib "DXMediaCap.dll" (ByVal device As Long, ByVal deSharpness As Long) As Long




Declare Function DXFlipVideo Lib "DXMediaCap.dll" (ByVal device As Long, ByVal flip As Boolean) As Long


Declare Function DXMirrorVideo Lib "DXMediaCap.dll" (ByVal device As Long, ByVal mirror As Boolean) As Long


Declare Function DXGetVideoPara Lib "DXMediaCap.dll" _
(ByVal device As Long, ByRef standard As Long, ByRef ColorSpace As Long, _
ByRef width As Long, ByRef height As Long, ByRef framerate As Double) As Long


Declare Function DXSetVideoPara Lib "DXMediaCap.dll" _
(ByVal device As Long, ByVal standard As Long, ByVal ColorSpace As Long, _
ByVal width As Long, ByVal height As Long, ByVal framerate As Single) As Long


Declare Function DXGetDisplayParaRange Lib "DXMediaCap.dll" _
(ByVal device As Long, ByVal paraType As Long, ByRef pMin As Long, _
ByRef pMax As Long, ByRef pSteppingDelta As Long, ByRef pDefault As Long, ByRef pCapsFlags As Long) As Long


Declare Function DXGetDisplayPara Lib "DXMediaCap.dll" _
(ByVal device As Long, ByVal paraType As Long, ByRef value As Long, ByRef flags As Long) As Long


Declare Function DXSetDisplayPara Lib "DXMediaCap.dll" _
(ByVal device As Long, ByVal paraType As Long, ByVal value As Long, ByVal flags As Long) As Long

                            
 Declare Function DXSetVideoSource Lib "DXMediaCap.dll" (ByVal device As Long, ByVal Source As Long) As Long


Declare Function DXGetSignalPresent Lib "DXMediaCap.dll" (ByVal device As Long, ByRef signal As Long) As Long


Declare Function DXEnumVideoCodecs Lib "DXMediaCap.dll" (devTags As DEVICE_TAG, ByRef Num As Long) As Long


Declare Function DXSetVideoCodec Lib "DXMediaCap.dll" (ByVal device As Long, devTags As DEVICE_TAG) As Long

Declare Function DXSetAudioCodec Lib "DXMediaCap.dll" (ByVal device As Long, devTags As DEVICE_TAG) As Long







Declare Function DXSetTextOSD Lib "DXMediaCap.dll" (ByVal device As Long, _
                                                    ByVal x As Long, _
                                                    ByVal y As Long, _
                                                    ByVal TextNO As Long, _
                                                    ByVal osdText As String, _
                                                    ByVal pointSize As Long, _
                                                    ByVal faceName As String, _
                                                    ByVal color As OLE_COLOR, _
                                                    ByVal bgcolor As OLE_COLOR, _
                                                    ByVal transparent As Long) As Long
                             
 Declare Function DXSetTimeOSD Lib "DXMediaCap.dll" (ByVal device As Long, _
                                                    ByVal x As Long, _
                                                    ByVal y As Long, _
                                                    ByVal pointSize As Long, _
                                                    ByVal faceName As String, _
                                                    ByVal color As OLE_COLOR, _
                                                    ByVal bgcolor As OLE_COLOR, _
                                                    ByVal transparent As Long) As Long
                             
 Declare Function DXSetPictureOSD Lib "DXMediaCap.dll" (ByVal device As Long, _
                                                        ByVal x As Long, _
                                                        ByVal y As Long, _
                                                        ByVal PicNO As Long, _
                                                        ByVal picFileName As String, _
                                                        ByVal transparent As Boolean, _
                                                        ByVal Alpha As Byte) As Long
                                                        

Declare Function DXEnOSDDisp Lib "DXMediaCap.dll" (ByVal device As Long, ByVal OsdType As Long, ByVal OsdNo As Long, ByVal enable As Long) As Long

  






'/////////////////////////////////////////////

Declare Function DXSnapToBMPFile Lib "DXMediaCap.dll" (ByVal device As Long, ByVal szFileName As String, ByRef Rect As Rect) As Long


Declare Function DXSnapToJPGFile Lib "DXMediaCap.dll" (ByVal device As Long, ByVal szFileName As String, ByVal quilty As Long, ByRef Rect As Rect) As Long






Declare Function DXGetFrameBuffer Lib "DXMediaCap.dll" _
(ByVal device As Long, buffer As Byte, ByVal bufferLen As Long, _
ByRef gotBufferLen As Long, ByRef ColorSpace As Long, ByRef width As Long, _
ByRef height As Long, ByRef byteswidth As Long, ByRef prect As Rect) As Long

Declare Function DXSaveBMPFile Lib "DXMediaCap.dll" _
(ByVal szFileName As String, buffer As Byte, ByVal bufferLen As Long, _
ByVal ColorSpace As Long, ByVal width As Long, ByVal height As Long, ByVal byteswidth As Long) As Long




Declare Function DXSaveJPGFile Lib "DXMediaCap.dll" _
(ByVal szFileName As String, buffer As Byte, ByVal bufferLen As Long, _
ByVal ColorSpace As Long, ByVal width As Long, ByVal height As Long, ByVal byteswidth As Long, ByVal Quality As Long) As Long


Declare Function DXEnDataRaterPara Lib "DXMediaCap.dll" (ByVal device As Long, ByVal RateType As Long, ByRef pPara As TDRateColor_Para) As Long





Declare Function DXSetVideoCodecPara Lib "DXMediaCap.dll" (ByVal device As Long, ByVal codecType As TcodecType, ByRef pPara As TVidCodecX264Para) As Long


'
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias _
"GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal _
lpKeyName As Any, ByVal lpDefault As String, _
ByVal lpReturnedString As String, ByVal nSize As Long, _
ByVal lpFileName As String) As Long
'写ini文件api
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long

'消息处理api
Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long


Declare Function GetClientRect Lib "user32" (ByVal hwnd As Long, lpRect As Rect) As Long


'////////////////////////////////////////////define function////////////////////////////
'按时间创建文件名函数
Function CreateCaptureFile(nCard As Long, FileType As String, FileSavePath As String) As String
    Dim FileName As String
    Dim cur As Date
    cur = Now
    FileName = FileSavePath & Format(cur, "yyyymmdd-HHmmss") & "Cam" & Str(nCard) & FileType
    CreateCaptureFile = FileName
        
End Function




















