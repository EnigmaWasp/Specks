//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
b=new Graphics::TBitmap();
b->Width=200;
b->Height=200;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormPaint(TObject *Sender)
{
Canvas->Draw(0,0,b);
}
//---------------------------------------------------------------------------
