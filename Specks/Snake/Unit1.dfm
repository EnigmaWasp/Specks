object Form1: TForm1
  Left = 221
  Top = 352
  BorderStyle = bsToolWindow
  Caption = '«мейка    ”ровень 1'
  ClientHeight = 300
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Timer1: TTimer
    Interval = 200
    OnTimer = Timer1Timer
  end
end
