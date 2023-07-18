#include <iostream>
#include <string>
#include "mylib.h"
#define MAX 100
using namespace std;

//===============
void box(int x, int y, int w, int h, int t_color, int b_color,string nd);
void n_box(int x, int y, int w, int h, int t_color, int b_color, string arr[], int sl);
void menu();
void thanh_sang(int x, int y, int w, int h, int b_color, string nd);


int main()
{
	//--- menu dong ----
    DisableResizeWindow();
    DisableCtrButton(0,1,0);
	menu();
	
	

	
	_getch();
}
void menu()
{   
    SetConsoleTitle(TEXT("Giai phuong trinh da thuc bang Phuong phap Day cung"));
    //SetWindowSize(180,43);
	resizeConsole(1600,800);
    
	ShowCur(0);
	//----- setting ----
	int x = 1;int y = 2;
	int x2 =1;int y2 =23;
	bool menu1 = true ;bool menu2 = false;

	int w = 35;
	int h = 2;
	int t_color = 11;
	int b_color = 1;
	int b_color_sang = 86;
	string ND1[10]= {"0.Ham sinh ma tran ngau nhien", "1.Cong 2 ma tran", "2.Tru 2 ma tran", 
                    "3.Nhan 2 ma tran ", "4.Nhan ma tran voi so thuc","5.Tinh hang cua ma tran", 
                    "6.Tinh dinh thuc cua ma tran ", "7.Tim tri rieng va vecto rieng", 
                    "8.MT nghich dao Pp phan phu dai so", "9.MT nghich dao Pp Gauss Jordan"};
	string ND2[3]= {"Nhap ma tran tu ban phim","Nhap ma tran tu tep","Quay lai"};
	int sl = 10;
	int sl2 =3;
    int oldchoice = 0,choice = 0;
    int oldchoice2 = 0,choice2 =0;
    //============= những hiển thị chính ==================//
    box(0,0,166,43,6,6,"=========================================================={CHUONG TRINH THUC HIEN CAC THAO TAC TREN MA TRAN}==========================================================");

	n_box(x, y, w, h, t_color, b_color, ND1, sl);

	//==============Ô hiển thị kết quả chương trình==========//
    box(x+36,y,w+15+70+8,sl*h+20,t_color,b_color,"");
	// ============== Menu cấp 2 ==========================//
	n_box(1,23,w,h,t_color,b_color,ND2,sl2);



	//==============ô comment=================//
	box(1,30,35,12,t_color,b_color,"");
	gotoXY(2,31);cout<<"Chuong trinh duoc dieu khien";
	gotoXY(2,32);cout<<"boi phim mui ten len xuong.";
	gotoXY(2,33);cout<<"Bam Enter de thuc hien.";
	gotoXY(2,34);cout<<"Bam Esc de thoat chuong trinh.";


	//============= Ô thực thi chương trình============//
	gotoXY(38,3);textcolor(14);
	printTex("AAAAAAAAAAAAAAAAAAAAAAAAAA");
	printTex("BBBBBBBBBBBBBBBBBBBBBBB");
	
	//=====================================================//
	bool laytoado1 = true;
	bool laytoado2 = false;
	bool kt1=false,kt2=false;
	bool ttmenu1=true ,ttmenu2 =false;
	int xp,yp,xcu,ycu;
	
	while (true)
	{
		if (laytoado1){
			xp = x; yp = y;//tọa độ thanh sáng chuyển về menu cấp 1
			xcu = xp; ycu = yp;
			kt1 = true;
			laytoado1 = false;
		}
		if (laytoado2){
			xp = x2; yp = y2;//tọa độ thanh sáng chuyển về menu cấp 2
			xcu = xp; ycu = yp;
			kt2 = true;
			laytoado2 = false;
		}
		
		
		if (kt1 == true)
		{	

			//----- Hiển thị thanh sáng ----------------//
			gotoXY(xcu, ycu);
			thanh_sang(xcu, ycu, w, h, b_color, ND1[oldchoice]);//reset thanh sang cu
			xcu = xp;ycu = yp;
			//-------------//
			thanh_sang(xp, yp, w, h, b_color_sang, ND1[choice]);
			kt1 = false;
            
		}
		if (kt2 == true)
		{	

			//----- Hiển thị thanh sáng ----------------//
			gotoXY(xcu, ycu);
			thanh_sang(xcu, ycu, w, h, b_color, ND2[oldchoice2]);//reset thanh sang cu
			xcu = xp;ycu = yp;
			//-------------//
			thanh_sang(xp, yp, w, h, b_color_sang, ND2[choice2]);
			kt2 = false;
            
		}



		//----- Bắt phím điều khiển chương trình ---- //
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32 && (ttmenu1) )  //Chuyển sang menu cấp 1
			{
				kt1 = true;// đã bấm
				c = _getch();
                oldchoice = choice;
				if (c == 72)
				{
					if(yp != y){
                        yp -= 2;
                        choice--;
                    }
					else
					{
						yp = y + h*(sl - 1);
                        choice = sl-1;
					}
				}
				else if (c == 80 )
				{
					if(yp != y + h*(sl - 1)){
                        yp += 2;choice++;
                    }
					else
					{
						yp = y;
                        choice = 0;
					}
				}
			}
			else if(c == -32 && (ttmenu2) ) {//Khi chuyển sang menu cấp 2
				kt2 = true;// đã bấm
				c = _getch();
                oldchoice2 = choice2;
				if (c == 72)
				{
					if(yp != y2){
                        yp -= 2;
                        choice2--;
                    }
					else
					{
						yp = y2 + h*(sl2 - 1);
                        choice2 = sl2-1;
					}
				}
				else if (c == 80 )
				{
					if(yp != y2 + h*(sl2 - 1)){
                        yp += 2;choice2++;
                    }
					else
					{
						yp = y2;
                        choice2 = 0;
					}
				}
			}      
			else if (c == 27){return;
            //bam esc de thoat
            }
			else if (c==13){
				laytoado2 = true;laytoado1= false;
				ttmenu1 =false;ttmenu2=true;
			}
		}
		
        
	}

}
void thanh_sang(int x,int y,int w,int h,int b_color,string nd)
{
	textcolor(b_color);
	for (int iy = y + 1;iy <= y + h - 1;iy++)
	{
		for (int ix = x + 1;ix <= x + w - 1;ix++)
		{
			gotoXY(ix, iy);cout << " ";
		}
	}
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << nd;
}
void box(int x, int y,int w,int h,int t_color,int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = y+1;iy <= y + h-1;iy++)
	{
		for (int ix = x+1;ix <= x + w-1;ix++)
		{
			gotoXY(ix, iy);cout << " ";
		}
	}
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << nd;
	//============= ve vien =============
	textcolor(1);
	SetColor(t_color);//update
	if (h <= 1 || w<=1)return;
	for (int ix = x;ix <= x + w;ix++)
	{
		gotoXY(ix, y);
		cout << char(205);
		gotoXY(ix, y + h);
		cout << char(205);
	}
	for (int iy = y;iy <= y + h;iy++)
	{
		gotoXY(x, iy);
		cout << char(186);
		gotoXY(x + w, iy);
		cout << char(186);
	}
	gotoXY(x, y);cout << char(201);
	gotoXY(x + w, y);cout << char(187);
	gotoXY(x, y + h);cout << char(200);
	gotoXY(x + w, y + h);cout << char(188);

}
void n_box(int x, int y, int w, int h, int t_color, int b_color, string ND[],int sl)
{
	for (int i = 0;i < sl;i++)
	{
		box(x, y + (i * 2), w, h, t_color, b_color, ND[i]);//i = 0 => x,y, i = 1: x,y+2
		if (i != 0)
		{
			gotoXY(x, y + (i * 2));cout << char(204);
			gotoXY(x + w, y + (i * 2));cout << char(185);
		}
	}
}