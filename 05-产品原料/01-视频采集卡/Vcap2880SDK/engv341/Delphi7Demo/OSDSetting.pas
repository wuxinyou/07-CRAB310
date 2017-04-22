unit OSDSetting;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls,strutils,IniFiles,Dialogs;

type
  TOsdSettingDlg = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label4: TLabel;
    TimeOsd: TCheckBox;
    TimeTranspar: TCheckBox;
    TimePlaceX: TEdit;
    TimePlaceY: TEdit;
    Label2: TLabel;
    TimeFontSize: TEdit;
    Label8: TLabel;
    TimeSetColor: TButton;
    GroupBox2: TGroupBox;
    Label3: TLabel;
    Label5: TLabel;
    TextOsd1: TCheckBox;
    TextTranspar1: TCheckBox;
    TextPlaceX1: TEdit;
    TextPlaceY1: TEdit;
    GroupBox5: TGroupBox;
    Label11: TLabel;
    Label6: TLabel;
    TxtFontSize1: TEdit;
    OsdText1: TEdit;
    TxtSetColor1: TButton;
    Label7: TLabel;
    GroupBox3: TGroupBox;
    Label9: TLabel;
    Label10: TLabel;
    PicOsd1: TCheckBox;
    PictPlaceX1: TEdit;
    PictPlaceY1: TEdit;
    Label12: TLabel;
    PicFilePath1: TEdit;
    PicBrowse1: TButton;
    ColorDialog1: TColorDialog;
    dlgOpen1: TOpenDialog;
    GroupBox4: TGroupBox;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    TextOsd2: TCheckBox;
    TextTranspar2: TCheckBox;
    GroupBox6: TGroupBox;
    TxtSetColor2: TButton;
    GroupBox7: TGroupBox;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    PicOsd2: TCheckBox;
    TextPlaceX2: TEdit;
    TextPlaceY2: TEdit;
    TxtFontSize2: TEdit;
    PictPlaceX2: TEdit;
    PictPlaceY2: TEdit;
    PicFilePath2: TEdit;
    OsdText2: TEdit;
    btnPicBrowse2: TButton;
    ScrTransparValue1: TScrollBar;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    ScrTransparValue2: TScrollBar;
    procedure TimeSetColorClick(Sender: TObject);
    procedure TxtSetColor1Click(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
    procedure TimePlaceXChange(Sender: TObject);
    procedure TimePlaceYChange(Sender: TObject);
    procedure TimeFontSizeChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure TxtFontSize1Change(Sender: TObject);
    procedure TextPlaceX1Change(Sender: TObject);
    procedure OsdText1Change(Sender: TObject);
    procedure TextPlaceY1Change(Sender: TObject);
    procedure PictPlaceX1Change(Sender: TObject);
    procedure PictPlaceY1Change(Sender: TObject);
    procedure PicBrowse1Click(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
    procedure PictPlaceX2Change(Sender: TObject);
    procedure PictPlaceY2Change(Sender: TObject);
    procedure TextPlaceX2Change(Sender: TObject);
    procedure TextPlaceY2Change(Sender: TObject);
    procedure TxtFontSize2Change(Sender: TObject);
    procedure OsdText2Change(Sender: TObject);
    procedure ScrTransparValue1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  OsdSettingDlg: TOsdSettingDlg;
  OpenFileDlg:Boolean ;

implementation
 uses GlobalVar,DxMediaFunction,DxMediaApi;
{$R *.dfm}

procedure TOsdSettingDlg.TimeSetColorClick(Sender: TObject);
begin
      ColorDialog1.Execute ;
      TimeColor:=ColorDialog1.Color;
end;

procedure TOsdSettingDlg.TxtSetColor1Click(Sender: TObject);
begin
      ColorDialog1.Execute ;
      TextColor[0]:=ColorDialog1.Color;
end;

procedure TOsdSettingDlg.OKBtnClick(Sender: TObject);
begin

           //设置时间osd
       If TimeOsd.Checked =True then
       begin
              if TimeTranspar.Checked=True then
              begin

                  DXSetTimeOSD( DeviceInfo[CardNo].dwChannelHandle,
                                 TimeX,
                                 TimeY,
                                 TimeFontSizeVal,
                                 PChar('Arial'),
                                 TimeColor,
                                 BackColor,
                                 True);


                 SettingIni.WriteString('OSDSetting','TimeTranspar', 'True');
              end

              else
              begin
                 DXSetTimeOSD(DeviceInfo[CardNo].dwChannelHandle,
                                 TimeX,
                                 TimeY,
                                 TimeFontSizeVal,
                                 PChar('Arial'),
                                 TimeColor,
                                 BackColor,
                                 false);
                 SettingIni.WriteString('OSDSetting','TimeTranspar', 'False');
              end;
               DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,0,0,true);
                SettingIni.WriteString('OSDSetting','TimeOsdEnable', 'True');


       end
       else
       begin
          //   DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,0,0,false);
               SettingIni.WriteString('OSDSetting','TimeOsdEnable', 'False');

       end;

        //设置第一行文本osd
       If TextOsd1.Checked = True Then
       begin
             If TextTranspar1.Checked = True Then
             begin
                   DXSetTextOSD(DeviceInfo[CardNo].dwChannelHandle,
                                 TxtPlaceX[0],
                                 TxtPlaceY[0],
                                 0,
                                 PAnsiChar(AnsiString(Osd_Txt[0])),
                                 TxtFontSizeVal[0],
                                 PChar('Arial'),
                                 TextColor[0] ,
                                 BackColor,
                                 true);

                    SettingIni.WriteString('OSDSetting','TextTranspar1', 'True')
             end
             else
             begin
                  DXSetTextOSD(DeviceInfo[CardNo].dwChannelHandle,
                                 TxtPlaceX[0],
                                 TxtPlaceY[0],
                                 0,
                                 PAnsiChar(AnsiString(Osd_Txt[0])),
                                 TxtFontSizeVal[0],
                                 PChar('Arial'),
                                 TextColor[0] ,
                                 BackColor,
                                 false);
                                 SettingIni.WriteString('OSDSetting','TextTranspar1', 'False')
             end;
              DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,1,0,true);
                SettingIni.WriteString('OSDSetting','TextOsdEnable1', 'True');
       end
       Else
       begin
        //  DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,1,0,false);
          SettingIni.WriteString('OSDSetting','TextOsdEnable1', 'False');
       End ;

         //设置第二行文本osd
       If TextOsd2.Checked = True Then
       begin
             If TextTranspar2.Checked = True Then
             begin
                   DXSetTextOSD(DeviceInfo[CardNo].dwChannelHandle,
                                 TxtPlaceX[1],
                                 TxtPlaceY[1],
                                 1,
                                 PAnsiChar(AnsiString(Osd_Txt[1])),
                                 TxtFontSizeVal[1],
                                 PChar('Arial'),
                                 TextColor[1] ,
                                 BackColor,
                                 true);
                                   SettingIni.WriteString('OSDSetting','TextTranspar2', 'True');


             end
             else
             begin
                  DXSetTextOSD(DeviceInfo[CardNo].dwChannelHandle,
                                 TxtPlaceX[1],
                                 TxtPlaceY[1],
                                 1,
                                 PAnsiChar(AnsiString(Osd_Txt[1])),
                                 TxtFontSizeVal[1],
                                 PChar('Arial'),
                                 TextColor[1] ,
                                 BackColor,
                                 false);
                                  SettingIni.WriteString('OSDSetting','TextTranspar2', 'False');
             end;
              DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,1,1,true);
              SettingIni.WriteString('OSDSetting','  TextOsdEnable2', 'True');

           end
       Else
       begin
         // DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,1,1,false);
           SettingIni.WriteString('OSDSetting','  TextOsdEnable2', 'False');
       End ;
       //设置图片osd
       if PicOsd1.Checked =True then
       begin
             if OpenFileDlg=False then
             begin
                   ShowMessage('Please select picture file');
                   Exit;
             end
             else
             begin

                    DXSetPictureOSD(DeviceInfo[CardNo].dwChannelHandle,
                                               PicPlaceX[0],
                                               PicPlaceY[0],
                                               0,
                                               PAnsiChar(AnsiString(PicOsdFile[0])),
                                               True,
                                               PicAlphaValue[0] );

                        DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,2,0,true);
             end;
       end
       else
       begin
           // DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,2,0,false );
       end;    

     

end;

procedure TOsdSettingDlg.TimePlaceXChange(Sender: TObject);
begin

        TimeX:=StrToInt(TimePlaceX.Text);
        SettingIni.WriteInteger('OSDSetting','TimeX',TimeX);
end;

procedure TOsdSettingDlg.TimePlaceYChange(Sender: TObject);
begin
      TimeY:=StrToInt(TimePlaceY.Text);
      SettingIni.WriteInteger('OSDSetting','TimeY',TimeY);
     
end;

procedure TOsdSettingDlg.TimeFontSizeChange(Sender: TObject);
begin
      TimeFontSizeVal:=StrToInt(TimeFontSize .Text );
      SettingIni.WriteInteger('OSDSetting','TimeFontSize',TimeFontSizeVal);

end;

procedure TOsdSettingDlg.FormCreate(Sender: TObject);
begin
      OpenFileDlg:=False;
      TimeColor:=RGB(0,255,0);
      TextColor[0]:=RGB(0,255,0);
       TextColor[1]:=RGB(0,255,0);
      BackColor:=RGB(255,255,255);
      TxtFontSizeVal[0]:=StrToInt(TxtFontSize1.Text );
      TxtFontSizeVal[1]:=StrToInt(TxtFontSize2.Text );
      Osd_Txt[0]:=OsdText1.Text ;
       Osd_Txt[1]:=OsdText2.Text ;
      TxtPlaceX[0]:=StrToInt(TextPlaceX1.Text );
      TxtPlaceY[0]:=StrToInt(TextPlaceY1.Text );
       TxtPlaceX[1]:=StrToInt(TextPlaceX2.Text );
      TxtPlaceY[1]:=StrToInt(TextPlaceY2.Text );
      TimeX:=StrToInt(TimePlaceX.Text);
      TimeY:=StrToInt(TimePlaceY.Text);
      PicPlaceX[0]:=StrToInt(PictPlaceX1.Text );
      PicPlaceY[0]:=StrToInt(PictPlaceY1.Text );
      PicPlaceX[1]:=StrToInt(PictPlaceX2.Text );
      PicPlaceY[1]:=StrToInt(PictPlaceY2.Text );
       TimeFontSizeVal:=StrToInt(TimeFontSize .Text );

       ScrTransparValue1.Max :=255;
       ScrTransparValue1.Min :=0;
        ScrTransparValue1.Position :=128;
       ScrTransparValue2.Max :=255;
       ScrTransparValue2.Min :=0;
       ScrTransparValue2.Position :=0;


       PicAlphaValue[0]:=ScrTransparValue1.Position;
    //  PicAlphaValue[1]:= Char (ScrTransparValue2.Position);

    TextOsd1.Checked :=True;
    TextOsd2.Checked :=True;
    TextTranspar1.Checked:=True;
    TextTranspar2.Checked:=True;
    TimeOsd.Checked:=True;
    TimeTranspar.Checked:=True;




end;

procedure TOsdSettingDlg.TxtFontSize1Change(Sender: TObject);
begin
     TxtFontSizeVal[0]:=StrToInt(TxtFontSize1.Text );
     SettingIni.WriteInteger('OSDSetting','TxtFontSize0',TxtFontSizeVal[0]);

end;

procedure TOsdSettingDlg.TextPlaceX1Change(Sender: TObject);
begin
      TxtPlaceX[0]:=StrToInt(TextPlaceX1.Text );
       SettingIni.WriteInteger('OSDSetting','TxtPlaceX0',TxtPlaceX[0]);
end;

procedure TOsdSettingDlg.OsdText1Change(Sender: TObject);
begin
     Osd_Txt[0]:=OsdText1.Text ;
     SettingIni.WriteString('OSDSetting','Osd_Txt0', Osd_Txt[0]);
end;

procedure TOsdSettingDlg.TextPlaceY1Change(Sender: TObject);
begin
     TxtPlaceY[0]:=StrToInt(TextPlaceY1.Text );
     SettingIni.WriteInteger('OSDSetting','TxtPlaceY0', TxtPlaceY[0]);
end;

procedure TOsdSettingDlg.PictPlaceX1Change(Sender: TObject);
begin
      PicPlaceX[0]:=StrToInt(PictPlaceX1.Text );
      SettingIni.WriteInteger('OSDSetting','PicPlaceX0', PicPlaceX[0]);
end;

procedure TOsdSettingDlg.PictPlaceY1Change(Sender: TObject);
begin
      PicPlaceY[0]:=StrToInt(PictPlaceY1.Text );
      SettingIni.WriteInteger('OSDSetting','PicPlaceY0', PicPlaceY[0]);
end;

procedure TOsdSettingDlg.PicBrowse1Click(Sender: TObject);
var PicStr:string;
begin
       //打开文件目录
      dlgOpen1.Execute ;
      PicOsdFile[0]:=dlgOpen1.FileName ;
      PicFilePath1.Text := PicOsdFile[0];
      PicStr:=rightstr( PicOsdFile[0],3);
      if PicStr<> 'bmp' then
      begin
            ShowMessage('please select bmp file');
            exit;
      end;
      OpenFileDlg:=True;
end;

procedure TOsdSettingDlg.CancelBtnClick(Sender: TObject);
begin
        OsdSettingDlg.Close ;
end;

procedure TOsdSettingDlg.PictPlaceX2Change(Sender: TObject);
begin
          PicPlaceX[1]:=StrToInt(PictPlaceX2.Text );
          SettingIni.WriteInteger('OSDSetting','PicPlaceX1', PicPlaceX[1]);

end;

procedure TOsdSettingDlg.PictPlaceY2Change(Sender: TObject);
begin
             PicPlaceY[1]:=StrToInt(PictPlaceY2.Text );
             SettingIni.WriteInteger('OSDSetting','PicPlaceY1', PicPlaceY[1]);
end;

procedure TOsdSettingDlg.TextPlaceX2Change(Sender: TObject);
begin
              TxtPlaceX[1]:=StrToInt(TextPlaceX2.Text );
              SettingIni.WriteInteger('OSDSetting','TxtPlaceX1', TxtPlaceX[1]);
end;

procedure TOsdSettingDlg.TextPlaceY2Change(Sender: TObject);
begin
         TxtPlaceY[1]:=StrToInt(TextPlaceY2.Text );
      SettingIni.WriteInteger('OSDSetting','TxtPlaceY1', TxtPlaceY[1]);
end;

procedure TOsdSettingDlg.TxtFontSize2Change(Sender: TObject);
begin
           TxtFontSizeVal[1]:=StrToInt(TxtFontSize2.Text );
            SettingIni.WriteInteger('OSDSetting','  TxtFontSize1', TxtFontSizeVal[1]);
end;

procedure TOsdSettingDlg.OsdText2Change(Sender: TObject);
begin
           Osd_Txt[1]:=OsdText2.Text ;
           SettingIni.WriteString('OSDSetting','  Osd_Txt1', Osd_Txt[1]);
end;

procedure TOsdSettingDlg.ScrTransparValue1Change(Sender: TObject);
begin

                     PicAlphaValue[0]:=ScrTransparValue1.Position;
                     DXSetPictureOSD(DeviceInfo[CardNo].dwChannelHandle,
                                               PicPlaceX[0],
                                               PicPlaceY[0],
                                               0,
                                               PAnsiChar(AnsiString(PicOsdFile[0])),
                                               True,
                                               PicAlphaValue[0] );

                        DXEnOSDDisp(DeviceInfo[CardNo].dwChannelHandle,2,0,true);
end;

end.
