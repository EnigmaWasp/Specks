//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int Pole[4][4];
Graphics::TBitmap*MainImage;
Graphics::TBitmap*Kusok[16];
int hours,minutes,secconds;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{


}
//---------------------------------------------------------------------------


void __fastcall TForm1::LoadImage(String path)
{
MainImage->FreeImage();
MainImage->LoadFromFile(path);
Form2->b->Canvas->Draw(0,0,MainImage);
Form2->Repaint();
for(int i=0;i<16;i++)
        {
        int ty=i/4;
        int tx=i-(ty*4);
        Kusok[i]->Canvas->CopyRect(Rect(0,0,50,50),
                                   MainImage->Canvas,
                                   Rect(tx*50,ty*50,tx*50+50,ty*50+50));
        }
        Kusok[15]->Canvas->Brush->Color=clBlack;
        Kusok[15]->Canvas->FillRect(Rect(0,0,50,50));
}

void __fastcall TForm1::DrawKuski()
{
        for(int j=0;j<4;j++)
                for(int i=0;i<4;i++)
                        {
                        Canvas->Draw(i*50,j*50,Kusok[Pole[i][j]]);
                        Canvas->Brush->Style=bsClear;
                        Canvas->Pen->Width=1;
                        Canvas->Rectangle(i*50,j*50,i*50+50,j*50+50);
                        Canvas->Brush->Style=bsSolid;
                        }
}

void __fastcall TForm1::FormPaint(TObject *Sender)
{
DrawKuski();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RandomizePole()
{
randomize();
TList*l=new TList();
for(int i=0;i<16;i++)
        l->Add((void*)i);
for(int i=0;i<16;i++)
        {
        int ty=i/4;
        int tx=i-(ty*4);
        int vibor=random(l->Count);
        Pole[tx][ty]=(int)l->Items[vibor];
        l->Delete(vibor);
        }
}
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
int TX=X/50;
int TY=Y/50;
if(Pole[TX][TY]!=15)
        {
        if(TX+1<4)if(Pole[TX+1][TY]==15){Pole[TX+1][TY]=Pole[TX][TY];Pole[TX][TY]=15;}
        if(TX-1>=0)if(Pole[TX-1][TY]==15){Pole[TX-1][TY]=Pole[TX][TY];Pole[TX][TY]=15;}
        if(TY+1<4)if(Pole[TX][TY+1]==15){Pole[TX][TY+1]=Pole[TX][TY];Pole[TX][TY]=15;}
        if(TY-1<4)if(Pole[TX][TY-1]==15){Pole[TX][TY-1]=Pole[TX][TY];Pole[TX][TY]=15;}
        }
DrawKuski();
DrawTime();

if(IsVictory())
{
Timer1->Enabled=false;
String path=ExtractFilePath(Application->ExeName);
TIniFile*ini = new TIniFile(path+"\\Best.ini");
ini->WriteInteger("BestTime","Hours",hours);
ini->WriteInteger("BestTime","Minutes",minutes);
ini->WriteInteger("BestTime","Seconds",secconds);
ini->UpdateFile();
delete ini;
ShowMessage("Победа");

secconds=0;minutes=0;hours=0;
randomize();
int Kartinka=random(8)+1;
LoadImage(IntToStr(Kartinka)+".bmp");
RandomizePole();
Repaint();
}
}
//---------------------------------------------------------------------------


bool __fastcall TForm1::IsVictory()
{   int counter=0;
       for(int j=0;j<4;j++)
        for(int i=0;i<4;i++,counter++)
           if(Pole[i][j]!=counter)
                {
                return false;
                }
return true;
}
void __fastcall TForm1::N1Click(TObject *Sender)
{
secconds=0;minutes=0;hours=0;
randomize();
int Kartinka=random(8)+1;
LoadImage(IntToStr(Kartinka)+".bmp");
RandomizePole();
Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
secconds++;
if(secconds>60)
        {
        secconds=0;
        minutes++;
        if(minutes>60)
                {
                minutes=0;
                hours++;
                }
        }
DrawKuski();
DrawTime();
if(Form2->Visible)
        {
        Form2->Left=Left+Width;
        Form2->Top=Top+30;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DrawTime()
{
Canvas->Brush->Style=bsClear;
Canvas->Font->Size=15;
Canvas->Font->Color=clGreen;
Canvas->TextOutA(12,10,IntToStr(hours)+":"+IntToStr(minutes)+":"+IntToStr(secconds));       //TODO: Add your source code here
Canvas->Brush->Style=bsSolid;
}
void __fastcall TForm1::N2Click(TObject *Sender)
{
int BestH=0,BestM=0,BestS=0;
String path=ExtractFilePath(Application->ExeName);
if(FileExists(path+"\\Best.ini"))
{
TIniFile*ini = new TIniFile(path+"\\Best.ini");
BestH=ini->ReadInteger("BestTime","Hours",0);
BestM=ini->ReadInteger("BestTime","Minutes",0);
BestS=ini->ReadInteger("BestTime","Seconds",0);
delete ini;
ShowMessage("Лучшее время "+IntToStr(BestH)+":"+
IntToStr(BestM)+":"+IntToStr(BestS));
}else
{
ShowMessage("Записей не обнаружено");
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
if(N3->Checked==true)
        {
        N3->Checked=false;
        Form2->Visible=false;
        }else
        {
        N3->Checked=true;
        Form2->Visible=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
 randomize();
MainImage=new Graphics::TBitmap();
for(int i=0;i<16;i++)
        {
        Kusok[i]=new Graphics::TBitmap();
        Kusok[i]->Width=50;
        Kusok[i]->Height=50;
        }
int Kartinka=random(8)+1;
        LoadImage(IntToStr(Kartinka)+".bmp");
RandomizePole();
}
//---------------------------------------------------------------------------

