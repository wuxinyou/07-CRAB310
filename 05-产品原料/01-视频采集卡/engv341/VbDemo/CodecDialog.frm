VERSION 5.00
Begin VB.Form CodecDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   4665
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6090
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4665
   ScaleWidth      =   6090
   ShowInTaskbar   =   0   'False
   Begin VB.Frame Frame3 
      Caption         =   "Video Codec Setting"
      Height          =   975
      Left            =   240
      TabIndex        =   11
      Top             =   3000
      Width           =   5655
      Begin VB.OptionButton obH264 
         Caption         =   "H264 Codec"
         Height          =   375
         Left            =   3960
         TabIndex        =   14
         Top             =   360
         Width           =   1575
      End
      Begin VB.OptionButton obDivx 
         Caption         =   "Divx Codec"
         Height          =   375
         Left            =   2040
         TabIndex        =   13
         Top             =   360
         Width           =   1575
      End
      Begin VB.OptionButton obXvid 
         Caption         =   "Xvid Codec"
         Height          =   375
         Left            =   240
         TabIndex        =   12
         Top             =   360
         Width           =   1575
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "save path setting"
      Height          =   1455
      Left            =   240
      TabIndex        =   4
      Top             =   1320
      Width           =   5655
      Begin VB.CommandButton BrowsePicture 
         Caption         =   "Brower"
         Height          =   375
         Left            =   4440
         TabIndex        =   10
         Top             =   960
         Width           =   975
      End
      Begin VB.TextBox SnapPath 
         Height          =   315
         Left            =   1440
         TabIndex        =   9
         Text            =   "d:\Pic"
         Top             =   960
         Width           =   2775
      End
      Begin VB.TextBox RecPath 
         Height          =   315
         Left            =   1440
         TabIndex        =   7
         Text            =   "d:\Video"
         Top             =   360
         Width           =   2775
      End
      Begin VB.CommandButton nBrowseRec 
         Caption         =   "Brower"
         Height          =   375
         Left            =   4440
         TabIndex        =   5
         Top             =   360
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "Picture save path"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label2 
         Caption         =   "Video Save path"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Enum the system codec infromation"
      Height          =   1095
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   5655
      Begin VB.ComboBox CombVideoCodec 
         Height          =   315
         Left            =   1440
         TabIndex        =   2
         Top             =   360
         Width           =   4095
      End
      Begin VB.Label Label1 
         Caption         =   "Video Codec"
         Height          =   495
         Left            =   240
         TabIndex        =   3
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2400
      TabIndex        =   0
      Top             =   4200
      Width           =   1215
   End
End
Attribute VB_Name = "CodecDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub BrowsePicture_Click()
Dim strResFolder As String
    Dim strLast As String
    strResFolder = BrowseForFolder(hwnd, "请选择一个目录.")
  '  If strResFolder <> "" Then
 '       strLast = Right(strResFolder, 1)
 '   If strLast <> "\" Then
  '      SnapPath.Text = strResFolder + "\"
'    Else
    SnapPath.Text = strResFolder
    strPicPath = SnapPath.Text
    
   
    
   
    
    Call WritePrivateProfileString("SystemSetting", "PicturePath", strPicPath, SaveIniFile)
End Sub

Private Sub CancelButton_Click()

       If Dir(SnapPath.Text, vbDirectory) = "" Then '文件夹不存在
         MkDir SnapPath.Text    '在应用程序根目下，创建文件夹Backup
     End If
     
      If Dir(RecPath.Text, vbDirectory) = "" Then '文件夹不存在
         MkDir RecPath.Text    '在应用程序根目下，创建文件夹Backup
     End If
    strRecPath = RecPath.Text
    strPicPath = SnapPath.Text
    Call WritePrivateProfileString("SystemSetting", "RecVideoPath", strRecPath, SaveIniFile)
    Call WritePrivateProfileString("SystemSetting", "PicturePath", strPicPath, SaveIniFile)


    If obXvid.value = True Then
             

       VideoInfo(CardNo).dwVideoCodecStr = "Xvid MPEG-4 Codec"
            
    End If

    If obDivx.value = True Then
             
          VideoInfo(CardNo).dwVideoCodecStr = "DivX? 5.1.1 Codec"
                

    End If
    If obH264.value = True Then
           
        VideoInfo(CardNo).dwVideoCodecStr = "x264 Codec"
                
    End If

    Unload Me
End Sub

Private Sub Form_Load()
obDivx.Enabled = True
End Sub

Private Sub nBrowseRec_Click()
     Dim strResFolder As String
    Dim strLast As String
    strResFolder = BrowseForFolder(hwnd, "请选择一个目录.")
  '  If strResFolder <> "" Then
       ' strLast = Right(strResFolder, 1)
   ' If strLast <> "\" Then
       ' RecPath.Text = strResFolder + "\"
  '  Else
    RecPath.Text = strResFolder
    strRecPath = RecPath.Text
 
    
     '写ini配置文件strRecPath

  Call WritePrivateProfileString("SystemSetting", "RecVideoPath", strRecPath, SaveIniFile)
  
End Sub

Private Sub obDivx_Click()
     If obDivx.value = True Then
             
          VideoInfo(CardNo).dwVideoCodecStr = "DivX? 5.1.1 Codec"
            Call WritePrivateProfileString("SystemSetting", "VideoCodec", VideoInfo(CardNo).dwVideoCodecStr, SaveIniFile)

    End If

End Sub

Private Sub obH264_Click()

     If obH264.value = True Then
 
           
        VideoInfo(CardNo).dwVideoCodecStr = "x264 Codec"
        Call WritePrivateProfileString("SystemSetting", "VideoCodec", VideoInfo(CardNo).dwVideoCodecStr, SaveIniFile)

                
    End If
End Sub

Private Sub obXvid_Click()
      If obXvid.value = True Then
             

       VideoInfo(CardNo).dwVideoCodecStr = "Xvid MPEG-4 Codec"
        Call WritePrivateProfileString("SystemSetting", "VideoCodec", VideoInfo(CardNo).dwVideoCodecStr, SaveIniFile)

            
    End If
End Sub
