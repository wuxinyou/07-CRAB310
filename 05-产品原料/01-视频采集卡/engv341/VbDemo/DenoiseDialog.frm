VERSION 5.00
Begin VB.Form DenoiseDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Denoise Setting"
   ClientHeight    =   3915
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   7005
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3915
   ScaleWidth      =   7005
   ShowInTaskbar   =   0   'False
   Begin VB.HScrollBar HScrollContract 
      Height          =   375
      Left            =   1320
      TabIndex        =   9
      Top             =   2520
      Width           =   4935
   End
   Begin VB.HScrollBar HScrollBright 
      Height          =   375
      Left            =   1320
      TabIndex        =   7
      Top             =   1800
      Width           =   4935
   End
   Begin VB.HScrollBar HScrollSharp 
      Height          =   375
      Left            =   1320
      TabIndex        =   5
      Top             =   1080
      Width           =   4935
   End
   Begin VB.HScrollBar HScrollDenoise 
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   360
      Width           =   4935
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2880
      TabIndex        =   0
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label LabelContract 
      Caption         =   "100"
      Height          =   375
      Left            =   6480
      TabIndex        =   12
      Top             =   2640
      Width           =   495
   End
   Begin VB.Label LabelBright 
      Caption         =   "100"
      Height          =   375
      Left            =   6480
      TabIndex        =   11
      Top             =   1800
      Width           =   495
   End
   Begin VB.Label LabelSharp 
      Caption         =   "100"
      Height          =   375
      Left            =   6480
      TabIndex        =   10
      Top             =   1080
      Width           =   495
   End
   Begin VB.Label Label4 
      Caption         =   "Contract£º"
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "Brightness£º"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   1800
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Sharpness£º"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   1200
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Denoise £º"
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   480
      Width           =   1215
   End
   Begin VB.Label DenoiseLabel 
      Caption         =   "100"
      Height          =   375
      Left            =   6480
      TabIndex        =   2
      Top             =   480
      Width           =   495
   End
End
Attribute VB_Name = "DenoiseDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub CancelButton_Click()
        
        Unload Me
End Sub

Private Sub Form_Load()
        
    HScrollDenoise.Max = 100
    HScrollDenoise.Min = 0
    HScrollDenoise.LargeChange = 1
    HScrollDenoise.value = 65
    DenoiseLabel.Caption = HScrollDenoise.value
    
    HScrollBright.Max = 255
    HScrollBright.Min = -255
    HScrollBright.LargeChange = 1
    HScrollBright.value = 0
    LabelBright.Caption = HScrollBright.value
    
    HScrollSharp.Max = 255
    HScrollSharp.Min = 0
    HScrollSharp.LargeChange = 1
    HScrollSharp.value = 10
    LabelSharp.Caption = HScrollSharp.value
    
    HScrollContract.Max = 100
    HScrollContract.Min = -100
    HScrollContract.LargeChange = 1
    HScrollContract.value = 20
    LabelContract.Caption = HScrollContract.value
   
    
End Sub

Private Sub HScroll1_Change()
 
  
  DenoiseLabel.Caption = HScrollDenoise.value
 
    If VideoInfo(CardNo).dwConnectState = True Then
     
            Call DXMediaCapApi.DXEnableDenoise(VideoInfo(CardNo).dwChannelHandle, HScrollDenoise.value)
     End If
     
     If HScrollDenoise.value = 0 Then
     
         DenoiseLabel.Caption = "Cancel"
     
     End If
     
   
End Sub

Private Sub HScrollBright_Change()

RateColorPara.nBrightness = HScrollBright.value
RateColorPara.nContrast = HScrollContract.value
LabelBright.Caption = HScrollBright.value
 If VideoInfo(CardNo).dwConnectState = True Then
     
            Call DXMediaCapApi.DXEnDataRaterPara(VideoInfo(CardNo).dwChannelHandle, 0, RateColorPara)
End If

End Sub

Private Sub HScrollContract_Change()

RateColorPara.nBrightness = HScrollBright.value
RateColorPara.nContrast = HScrollContract.value
 LabelContract.Caption = HScrollContract.value
 
 If VideoInfo(CardNo).dwConnectState = True Then
     
            Call DXMediaCapApi.DXEnDataRaterPara(VideoInfo(CardNo).dwChannelHandle, 0, RateColorPara)
End If
End Sub

Private Sub HScrollSharp_Change()
LabelBright.Caption = HScrollSharp.value
 If VideoInfo(CardNo).dwConnectState = True Then
     
            Call DXMediaCapApi.DXEnableDenoise(VideoInfo(CardNo).dwChannelHandle, HScrollSharp.value)
     End If

End Sub

