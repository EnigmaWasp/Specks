object Form1: TForm1
  Left = 298
  Top = 153
  BorderStyle = bsDialog
  Caption = 'Пятнашки'
  ClientHeight = 200
  ClientWidth = 200
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  Position = poScreenCenter
  OnMouseDown = FormMouseDown
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Timer1: TTimer
    OnTimer = Timer1Timer
  end
  object PopupMenu1: TPopupMenu
    Left = 30
    object N1: TMenuItem
      Caption = 'Начать новую'
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = 'Рекорд'
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = 'Подсказка'
      OnClick = N3Click
    end
  end
end
