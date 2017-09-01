//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Graphics::TBitmap*BackCanvas;
Graphics::TBitmap*ZmeyaBlock[6];
Graphics::TBitmap*LevelImage;
TPoint Piton[100];//Положение змеи
TPoint MousePos;
int PitonHead;
int PitonLength;  //Длина змеи
int PitonDirect;  //Куда движется змея
enum {Right,Down,LEFT,Up};
int NumberOfEatedMouse;
int Level;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Level=1;
BackCanvas=new Graphics::TBitmap();
BackCanvas->Width =300;
BackCanvas->Height=300;
Graphics::TBitmap*temp=new Graphics::TBitmap();
temp->LoadFromFile("Zmeya.bmp");
for(int i=0;i<6;i++)
{
ZmeyaBlock[i]=new Graphics::TBitmap();
ZmeyaBlock[i]->Width=20;
ZmeyaBlock[i]->Height=20;
ZmeyaBlock[i]->Canvas->CopyRect(Rect(0,0,20,20),
                                temp->Canvas,
                                Rect(i*20,0,i*20+20,20));
ZmeyaBlock[i]->Transparent=true;
}
temp->Free();
StartPositionPiton();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
int temp=PitonHead-1;
if(temp<0)temp=PitonLength-1;
int tx=Piton[PitonHead].x;
int ty=Piton[PitonHead].y;
PitonHead=temp;
if(PitonDirect==LEFT) tx--;
if(PitonDirect==Right)tx++;
if(PitonDirect==Up)   ty--;
if(PitonDirect==Down) ty++;
if((ty>14)||(ty<0)||(tx>14)||(tx<0))
{
End();
}else{Piton[PitonHead]=Point(tx,ty);}

if(HitTest())End();
if(HitMouse())
        {
        MousePos=Point(random(15),random(15));
        Piton[PitonLength]=Piton[temp];
        NumberOfEatedMouse++;
        PitonLength++;
        if(NumberOfEatedMouse>20)
                {
                Level++;
                StartPositionPiton();
                if(Level>4)
                        {
                        Timer1->Enabled=false;
                        ShowMessage("Поздравляем, вы прошли игру 'Змейка'");
                        Close();
                        }
                }
        }
ClearBuffer();
DrawPiton();
DrawMouse();
FlipBuffer();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::StartPositionPiton()
{
Piton[0]=Point(5,1);
Piton[1]=Point(4,1);
Piton[2]=Point(3,1);
Piton[3]=Point(2,1);
Piton[4]=Point(1,1);
PitonLength=3;
PitonHead=0;
PitonDirect=Right;
MousePos=Point(random(15),random(15));
NumberOfEatedMouse=0;
if(LevelImage!=NULL)LevelImage->FreeImage();
    else LevelImage=new Graphics::TBitmap();
LevelImage->LoadFromFile(IntToStr(Level)+".bmp");
Caption="Змейка    Уровень "+IntToStr(Level);
}

void __fastcall TForm1::DrawPiton()
{
      for(int i=0;i<PitonLength;i++)
        {
        if(i!=PitonHead){
        BackCanvas->Canvas->Draw(Piton[i].x*20,Piton[i].y*20,ZmeyaBlock[4]);
        }else
        {
        BackCanvas->Canvas->Draw(Piton[i].x*20,Piton[i].y*20,ZmeyaBlock[PitonDirect]);
        }
        }
}

void __fastcall TForm1::ClearBuffer()
{
BackCanvas->Canvas->CopyRect(Rect(0,0,300,15*NumberOfEatedMouse),
                             LevelImage->Canvas,
                             Rect(0,0,300,15*NumberOfEatedMouse));
BackCanvas->Canvas->FillRect(Rect(0,15*NumberOfEatedMouse,300,300));
}

void __fastcall TForm1::FlipBuffer()
{
Canvas->Draw(0,0,BackCanvas);
}
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(PitonDirect!=Down)if(Key==VK_UP)   PitonDirect=Up;
if(PitonDirect!=Up)if(Key==VK_DOWN) PitonDirect=Down;
if(PitonDirect!=Right)if(Key==VK_LEFT) PitonDirect=LEFT;
if(PitonDirect!=LEFT)if(Key==VK_RIGHT)PitonDirect=Right;
}
//---------------------------------------------------------------------------


bool __fastcall TForm1::HitTest()
{
for(int i=0;i<PitonLength;i++)
        {
                if(PitonHead!=i)
                {
                if((Piton[PitonHead].x==Piton[i].x)&&
                   (Piton[PitonHead].y==Piton[i].y))
                        return true;
                }
        }
return false;
}

void __fastcall TForm1::End()
{
      Timer1->Enabled=false;
      ShowMessage("Конец");
      StartPositionPiton();
      Timer1->Enabled=true;

}

void __fastcall TForm1::DrawMouse()
{
BackCanvas->Canvas->Draw(MousePos.x*20,MousePos.y*20,ZmeyaBlock[5]);
}

bool __fastcall TForm1::HitMouse()
{
        int tx=Piton[PitonHead].x;
        int ty=Piton[PitonHead].y;
        if((tx==MousePos.x)&&(ty==MousePos.y))return true;
        else return false;
}