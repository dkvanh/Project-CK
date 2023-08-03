#include <iostream>
#include <string>
#include "mylib.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>

#define MAX 50
#define RANGE_MIN -100
#define RANGE_MAX 100

using namespace std;

struct matrix {
    double data[MAX][MAX];
    int row;
    int column;
};
typedef struct matrix maTran;
const char* input1 = "input1.txt"; // Đây là file input1
const char* input2 = "input2.txt"; // Đây là file input2
const char* outputF = "output.txt";// Đây là file output
const char* quatrinh = "quatrinh.txt";



void case0();
void case1();
void case2();
void case3();
void case4();
void case5();
void case6();
void case7();
void case8();
void case9();
//====================
maTran congHaiMaTran(maTran mt1, maTran mt2);
maTran truHaiMaTran(maTran mt1, maTran mt2);
maTran nhanHaiMaTran(maTran mt1, maTran mt2);
maTran nhanMaTranVoiSo(maTran mt, double num);
double tinhDinhThucMaTran(maTran mt);
int tinhHangMaTran(maTran mt);
//======================
maTran taomatrandonvi(int n);
maTran mtnghichdaogauss(const maTran& mat);
maTran mtppdaiso(const maTran& mat);
//===================
void nhapMaTran(maTran& A);


//===============================//
void nhapMaTranTuTep(maTran& A, const char* fileName);
void xuatMaTranRaTep(const maTran& A, const char* outputF);


//==============================//
void box(int x, int y, int w, int h, int t_color, int b_color,string nd);
void n_box(int x, int y, int w, int h, int t_color, int b_color, string arr[], int sl);
void menu();
void thanh_sang(int x, int y, int w, int h, int b_color, string nd);
void dieukhien(int choice,int choice2);
void clearscreen();

void taoMaTranNgauNhien(maTran *mt);
void hienThiMaTran(maTran mt);
int ktraHople(maTran mt1, maTran mt2);
int choice2 =0;


std::ofstream outputFile;
int main()
{
	//--- menu dong ----
    SetConsoleTitle(TEXT(" >_< Hoc lam gi cho dau to >_< "));
	resizeConsole(1600,800);
	ShowCur(0);
    DisableResizeWindow();
    DisableCtrButton(0,1,0);
    outputFile.open(quatrinh, std::ofstream::out | std::ofstream::app);
	menu();
    outputFile.close();
	
}
void menu()
{   
    
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
	string ND2[4]= {"Nhap ma tran tu ban phim","Nhap ma tran tu tep","Sinh ma tran ngau nhien","Quay lai"};
	int sl = 10;
	int sl2 =4;
    int oldchoice = 0,choice = 0;
    int oldchoice2 = 0;choice2 =0;
    //============= những hiển thị chính ==================//
    box(0,0,166,43,6,6,"=========================================================={CHUONG TRINH THUC HIEN CAC THAO TAC TREN MA TRAN}==========================================================");

	n_box(x, y, w, h, t_color, b_color, ND1, sl);

	//==============Ô hiển thị kết quả chương trình==========//
    box(x+36,y,w+15+70+8,sl*h+20,t_color,b_color,"");
	// ============== Menu cấp 2 ==========================//
	n_box(1,23,w,h,t_color,b_color,ND2,sl2);


	//==============Ô comment=================//
	box(1,33,35,9,t_color,b_color,"");
    gotoXY(2,34);cout<<"============={LUU Y}==============";
	gotoXY(2,35);cout<<"Chuong trinh duoc dieu khien";
	gotoXY(2,36);cout<<"boi phim mui ten len xuong.";
	gotoXY(2,37);cout<<"Bam Enter de thuc hien.";
	gotoXY(2,38);cout<<"Bam Esc de thoat chuong trinh.";
    gotoXY(2,39);cout<<"File nhap la input1 va input2";
    gotoXY(2,40);cout<<"File xuat la output va quatrinh";

	//=====================================================//
	bool laytoado1 = true;
	bool laytoado2 = false;
	bool kt1=false,kt2=false;
	bool ttmenu1=true ,ttmenu2 =false,confirm = false; 
	int xp,yp,xcu,ycu,xback,yback;
	
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
            else if (c==13 && ttmenu1 &&(choice ==0)){
                textcolor(14);
                case0();
            }
            else if (c==13 && ttmenu2 && (choice2==3)){//=======quay lai menu1===//
                ttmenu1 =true;ttmenu2=false;
                thanh_sang(xp, yp, w, h, b_color, ND2[choice2]);
                xp=xback;yp=yback;
                xcu=xback;ycu=yback;
                choice2=0;
                clearscreen();

            }
			else if (c==13 && ttmenu1){
				laytoado2 = true;laytoado1= false;
				ttmenu1 =false;ttmenu2=true;
                xback = xp;yback = yp;
			}
            else if (c==13 && ttmenu2 && (choice2 != 3) ){
                confirm = true;
            }
            
            

		}
        if ( confirm ){
            dieukhien(choice,choice2);
            confirm = false;
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

void dieukhien(int choice,int choice2){
    outputFile<<"=========================================================================================================================================="<<endl;
    clearscreen();
    gotoXY(38,3);textcolor(14);
    switch (choice) {
        case 1:
            case1();
            break;
        case 2:
            case2();
            break;
        case 3:
            case3();
            break;
        case 4:
            case4();
            break;
        case 5:
        case5();
            break;
        case 6:
        case6();
            break;
        case 7:
            printTex(" 7.");
            break;
        case 8:
            case8();
            break;
        case 9:
            case9();
            break;
    }
}

//============== Cac ham thuc hien cac chuc nang cua chuong trinh ============//
void taoMaTranNgauNhien(maTran *mt) {
    srand(time(NULL));

    for (int i = 0; i < mt->row; i++) {
        for (int j = 0; j < mt->column; j++) {
            mt->data[i][j] = (rand() / (double)RAND_MAX) * (RANGE_MAX - RANGE_MIN) + RANGE_MIN;
        }
    }
}

// Hàm hiển thị ma trận
void hienThiMaTran(maTran mt) {
    if ((mt.row > 12) || (mt.column > 12)){
        printTex("Ma tran vuot qua kich co hien thi");xuongdong();
    }
    else{
        printTex("");
        outputFile<< mt.column << " " << mt.row << std::endl;
        for (int i = 0; i < mt.row; i++) {
            for (int j = 0; j < mt.column; j++) {
                cout<<mt.data[i][j];daucach();
                outputFile << std::fixed << std::setprecision(4) << mt.data[i][j] << "   \t";
            }
            xuongdong();
            outputFile << std::endl;
        }
    }
    
}

void case0() {
    maTran mt1;
    printTex("Nhap kich thuoc ma tran ngau nhien: so dong - dau cach - so cot: ");
    outputFile<<"Nhap kich thuoc ma tran ngau nhien: so dong - dau cach - so cot:";
    cin>>mt1.row>>mt1.column;cout<<endl;
    outputFile<<mt1.row<<" "<<mt1.column<<endl;
    taoMaTranNgauNhien(&mt1);
    hienThiMaTran(mt1);
    xuatMaTranRaTep(mt1,outputF);
}

void case1() {   
    maTran mt1,mt2;
    if (choice2==0) {
        nhapMaTran(mt1);
        nhapMaTran(mt2);  
    }
    else if(choice2==1){
        nhapMaTranTuTep(mt1,input1);
        nhapMaTranTuTep(mt2,input2);
    }
    else if(choice2==2){
        printTex("Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: "<<endl;
        cin>>mt1.row>>mt1.column;cout<<endl;
        outputFile<<mt1.row<<" "<<mt1.column<<endl;
        taoMaTranNgauNhien(&mt1);
        printTex("Nhap kich thuoc ma tran ngau nhien thu hai : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu hai : so dong - dau cach - so cot: "<<endl;
        cin>>mt2.row>>mt2.column;cout<<endl;
        outputFile<<mt2.row<<" "<<mt2.column<<endl;
        taoMaTranNgauNhien(&mt2);
       
    }  
    printTex("Ma tran thu nhat la:");xuongdong();
    outputFile<<"Ma tran thu nhat la"<<endl;
    hienThiMaTran(mt1);
    printTex("Ma tran thu hai la:");xuongdong();
    outputFile<<"Ma tran thu hai la"<<endl;
    hienThiMaTran(mt2);
    maTran tong = congHaiMaTran(mt1, mt2);
    printTex("Ma tran tong la:");xuongdong();
    outputFile<<"Ma tran tong la"<<endl;
    hienThiMaTran(tong); 
    xuatMaTranRaTep(tong,outputF);
}

void case2() {
    maTran mt1,mt2;
    if (choice2 == 0){
        nhapMaTran(mt1);
        nhapMaTran(mt2);
    }
    else if(choice2 == 1){
        nhapMaTranTuTep(mt1,input1);
        nhapMaTranTuTep(mt2,input2);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ";
        cin>>mt1.row>>mt1.column;cout<<endl;
        outputFile<<mt1.row<<" "<<mt1.column<<endl;
        taoMaTranNgauNhien(&mt1);
        printTex("Nhap kich thuoc ma tran ngau nhien thu hai : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu hai : so dong - dau cach - so cot: ";
        cin>>mt2.row>>mt2.column;cout<<endl;
        outputFile<<mt2.row<<" "<<mt2.column<<endl;
        taoMaTranNgauNhien(&mt2);
        
    }
    printTex("Ma tran thu nhat la:");xuongdong();
    outputFile<<"Ma tran thu nhat la:"<<endl;
    hienThiMaTran(mt1);
    printTex("Ma tran thu hai la:");xuongdong();
    outputFile<<"Ma tran thu hai la:"<<endl;
    hienThiMaTran(mt2);
    maTran hieu = truHaiMaTran(mt1, mt2);
    printTex("Ma tran tru la:");xuongdong();
    outputFile<<"Ma tran tru la:"<<endl;
    hienThiMaTran(hieu);
    xuatMaTranRaTep(hieu,outputF);
}

void case3() {
    maTran mt1,mt2;
    if(choice2 == 0){
        nhapMaTran(mt1);
        nhapMaTran(mt2);
    }
    else if (choice2 == 1){
        nhapMaTranTuTep(mt1,input1);
        nhapMaTranTuTep(mt2,input2);
    }
    else if (choice2 ==2){
        printTex("Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ";
        cin>>mt1.row>>mt1.column;cout<<endl;
        outputFile<<mt1.row<<" "<<mt1.column<<endl;
        taoMaTranNgauNhien(&mt1);
        printTex("Nhap kich thuoc ma tran ngau nhien thu hai : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien thu nhat : so dong - dau cach - so cot: ";
        cin>>mt2.row>>mt2.column;cout<<endl;
        outputFile<<mt2.row<<" "<<mt2.column<<endl;
        taoMaTranNgauNhien(&mt2);
    }
    printTex("Ma tran thu nhat la:");xuongdong();
    outputFile<<"Ma tran thu nhat la:"<<endl;
    hienThiMaTran(mt1);
    printTex("Ma tran thu hai la:");xuongdong();
    outputFile<<"Ma tran thu hai la:"<<endl;
    hienThiMaTran(mt2);
    maTran tich = nhanHaiMaTran(mt1, mt2);
    printTex("Ma tran tich la:");xuongdong();
    outputFile<<"Ma tran tich la:"<<endl;
    hienThiMaTran(tich);
    xuatMaTranRaTep(tich,outputF);
}

void case4() {
    maTran mt1;
    double k;
    if (choice2 == 0){
        nhapMaTran(mt1);
    }
    else if (choice2 == 1){
        nhapMaTranTuTep(mt1,input1);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ";
        cin>>mt1.row>>mt1.column;cout<<endl;
        outputFile<<mt1.row<<" "<<mt1.column<<endl;
        taoMaTranNgauNhien(&mt1);    
    }
    printTex("Ma tran la:");xuongdong();
    outputFile<<"Ma tran la:"<<endl;
    hienThiMaTran(mt1);
    printTex("Nhap so thuc: ");
    outputFile<<"Nhap so thuc:";
    cin>>k;cout<<endl;
    outputFile<<k<<endl;
    maTran kq = nhanMaTranVoiSo(mt1, k);
    printTex("Ma tran ket qua la:");xuongdong();
    outputFile<<"Ma tran ket qua la:"<<endl;
    hienThiMaTran(kq);
    xuatMaTranRaTep(kq,outputF);
}

void case5() {
    maTran mt;
    int rank;
    if (choice2 == 0){
        nhapMaTran(mt);
        
    }
    else if (choice2 == 1){
        nhapMaTranTuTep(mt,input1);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ";
        cin>>mt.row>>mt.column;cout<<endl;
        outputFile<<mt.row<<" "<<mt.column<<endl;
        taoMaTranNgauNhien(&mt);
    }
    printTex("Ma tran la:");xuongdong();
    outputFile<<"Ma tran la:"<<endl;
    hienThiMaTran(mt);
    rank = tinhHangMaTran(mt);
    if (rank !=0){
        printTex("Hang cua ma tran la:");cout<<rank;
        outputFile<<"Hang cua ma tran la:"<<rank<<endl;
    }
}

void case6() {
    maTran mt;
    double det;
    if (choice2 == 0){
        nhapMaTran(mt);
    }
    else if (choice2 == 1){
        nhapMaTranTuTep(mt,input1);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot:";
        cin>>mt.row>>mt.column;cout<<endl;
        outputFile<<mt.row<<" "<<mt.column<<endl;
        taoMaTranNgauNhien(&mt);
    }
    printTex("Ma tran la:");xuongdong();
    outputFile<<"Ma tran la:"<<endl;
    hienThiMaTran(mt);
    det = tinhDinhThucMaTran(mt);
    if (det!= NULL){
        printTex("Dinh thuc cua ma tran la: ");cout<<det;
        outputFile<<"Dinh thuc cua ma tran la: "<<det<<endl;
    }
    
}

void case8() {
    int n;
    maTran mt;
    if (choice2 == 0){
        nhapMaTran(mt);
    }
    else if(choice2 == 1){
        nhapMaTranTuTep(mt,input1);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot:";
        cin>>mt.row>>mt.column;cout<<endl;
        outputFile<<mt.row<<" "<<mt.column<<endl;
        taoMaTranNgauNhien(&mt);
    }
    printTex("Ma tran la:");xuongdong();
    outputFile<<"Ma tran la:"<<endl;
    hienThiMaTran(mt);
    maTran kq = mtppdaiso(mt);
    printTex("Ma tran ket qua la:");xuongdong();
    outputFile<<"Ma tran ket qua la:"<<endl;
    hienThiMaTran(kq);
    xuatMaTranRaTep(kq,outputF);
}

void case9() {
    int n;
    maTran mt;
    if (choice2 == 0){
        nhapMaTran(mt);
    }
    else if(choice2 == 1){
        nhapMaTranTuTep(mt,input1);
    }
    else if(choice2 == 2){
        printTex("Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot: ");
        outputFile<<"Nhap kich thuoc ma tran ngau nhien : so dong - dau cach - so cot:";
        cin>>mt.row>>mt.column;cout<<endl;
        outputFile<<mt.row<<" "<<mt.column<<endl;
        taoMaTranNgauNhien(&mt);
    }
    printTex("Ma tran la:");xuongdong();
    outputFile<<"Ma tran la:"<<endl;
    hienThiMaTran(mt);
    maTran kq = mtnghichdaogauss(mt);
    printTex("Ma tran ket qua la:");xuongdong();
    outputFile<<"Ma tran ket qua la:"<<endl;
    hienThiMaTran(kq);
    xuatMaTranRaTep(kq,outputF);
}

// Hàm xóa màn hình thực hiện
void clearscreen(){
    box(37,2,128,40,11,1,"");
}

// Hàm kiểm tra tính hợp lệ của 2 ma trận
int ktraHople(maTran mt1, maTran mt2) {
    return (mt1.row == mt2.row && mt1.column == mt2.column);
}

// Hàm cộng 2 ma trận
maTran congHaiMaTran(maTran mt1, maTran mt2) {
    maTran ketQua;

    if (!ktraHople(mt1, mt2)) {
        printTex("Hai ma tran khong cung kich thuoc, khong the thuc hien phep cong.");
        outputFile<<"Hai ma tran khong cung kich thuoc, khong the thuc hien phep cong."<<endl;
        ketQua.row = ketQua.column = 0;
        return ketQua;
    }

    ketQua.row = mt1.row;
    ketQua.column = mt1.column;

    for (int i = 0; i < mt1.row; i++) {
        for (int j = 0; j < mt1.column; j++) {
            ketQua.data[i][j] = mt1.data[i][j] + mt2.data[i][j];
        }
    }

    return ketQua;
}

// Hàm trừ 2 ma trận
maTran truHaiMaTran(maTran mt1, maTran mt2) {
    maTran ketQua;

    if (!ktraHople(mt1, mt2)) {
        printTex("Hai ma tran khong cung kich thuoc, khong the thuc hien phep tru.\n");
        outputFile<<"Hai ma tran khong cung kich thuoc, khong the thuc hien phep tru."<<endl;
        ketQua.row = ketQua.column = 0;
        return ketQua;
    }

    ketQua.row = mt1.row;
    ketQua.column = mt1.column;

    for (int i = 0; i < mt1.row; i++) {
        for (int j = 0; j < mt1.column; j++) {
            ketQua.data[i][j] = mt1.data[i][j] - mt2.data[i][j];
        }
    }

    return ketQua;
}

// Ham nhan 2 ma tran
maTran nhanHaiMaTran(maTran mt1, maTran mt2) {
    maTran ketQua;

    if (mt1.column != mt2.row) {
        printTex("So cot cua ma tran 1 khac so dong cua ma tran 2, khong the thuc hien phep nhan.\n");
        outputFile<<"So cot cua ma tran 1 khac so dong cua ma tran 2, khong the thuc hien phep nhan."<<endl;
        ketQua.row = ketQua.column = 0;
        return ketQua;
    }

    ketQua.row = mt1.row;
    ketQua.column = mt2.column;

    for (int i = 0; i < mt1.row; i++) {
        for (int j = 0; j < mt2.column; j++) {
            ketQua.data[i][j] = 0;
            for (int k = 0; k < mt1.column; k++) {
                ketQua.data[i][j] += mt1.data[i][k] * mt2.data[k][j];
            }
        }
    }

    return ketQua;
}

// Ham nhan ma tran voi so
maTran nhanMaTranVoiSo(maTran mt, double num) {
    maTran ketQua;

    ketQua.row = mt.row;
    ketQua.column = mt.column;

    for (int i = 0; i < mt.row; i++) {
        for (int j = 0; j < mt.column; j++) {
            ketQua.data[i][j] = mt.data[i][j] * num;
        }
    }

    return ketQua;
}

// Hàm tính định thức của ma trận
double tinhDinhThucMaTran(maTran mt) {
    if ((mt.row != mt.column) || (tinhHangMaTran(mt)<mt.row )) {
        cout<<"Ma tran khong phai la ma tran vuong hoac co rank nho hon so cot,hang.\n";
        outputFile<<"Ma tran khong phai la ma tran vuong hoac co rank nho hon so cot,hang"<<endl;
        return NULL;
    }

    if (mt.row == 1) {
        return mt.data[0][0];
    } else if (mt.row == 2) {
        return mt.data[0][0] * mt.data[1][1] - mt.data[0][1] * mt.data[1][0];
    }

    double det = 0;
    maTran subMatrix;

    subMatrix.row = subMatrix.column = mt.row - 1;

    for (int k = 0; k < mt.row; k++) {
        int subi = 0;
        for (int i = 1; i < mt.row; i++) {
            int subj = 0;
            for (int j = 0; j < mt.row; j++) {
                if (j == k) {
                    continue;
                }
                subMatrix.data[subi][subj] = mt.data[i][j];
                subj++;
            }
            subi++;
        }
        det += (k % 2 == 1 ? -1.0 : 1.0) * mt.data[0][k] * tinhDinhThucMaTran(subMatrix);
    }

    return det;
}

// Hàm tính hạng của ma trận
int tinhHangMaTran(maTran mt) {
    maTran temp = mt; // Tạo một ma trận tạm để không làm thay đổi ma trận ban đầu

    int rank = 0;
    int m = mt.row;
    int n = mt.column;

    int i, j, k;
    double c;

    for (i = 0; i < m; i++) {
        // Tìm hàng không phải là hàng 0 đầu tiên trong cột i
        for (k = i; k < m; k++) {
            if (temp.data[k][i] != 0) {
                break;
            }
        }

        // Nếu không tìm thấy, chuyển sang cột tiếp theo
        if (k == m) {
            continue;
        }

        // Tăng hạng lên 1
        rank++;

        // Hoán đổi hàng k với hàng i
        for (j = 0; j < n; j++) {
            double tempVal = temp.data[i][j];
            temp.data[i][j] = temp.data[k][j];
            temp.data[k][j] = tempVal;
        }

        // Biến đổi hàng i về 1
        c = temp.data[i][i];
        for (j = 0; j < n; j++) {
            temp.data[i][j] /= c;
        }

        // Biến đổi các hàng còn lại sao cho các phần tử dưới đường chéo của cột i đều bằng 0
        for (k = 0; k < m; k++) {
            if (k != i) {
                c = temp.data[k][i];
                for (j = 0; j < n; j++) {
                    temp.data[k][j] -= c * temp.data[i][j];
                }
            }
        }
    }

    return rank;
}

// Hàm nhập ma trận bằng tay
void nhapMaTran(maTran& A) {
    printTex("Nhap kich thuoc ma tran : so dong - dau cach - so cot: ");
    outputFile<<"Nhap kich thuoc ma tran : so dong - dau cach - so cot: ";
    cin>>A.row>>A.column;cout<<endl;
    outputFile<<A.row<<" "<<A.column<<endl;
    printTex("Nhap cac phan tu cua ma tran:");xuongdong();
    outputFile<<"Nhap cac phan tu cua ma tran:"<<endl; 
    for (int i = 0; i < A.row; ++i) {
        for (int j = 0; j < A.column; ++j) {
            cin >> A.data[i][j];
        }
        xuongdong();
    }
}

// Hàm nhập ma trận từ tệp
void nhapMaTranTuTep(maTran& A, const char* fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cout << "Khong the mo file " << fileName << std::endl;
        return;
    }

    inputFile >> A.column >> A.row;

    for (int i = 0; i < A.row; ++i) {
        for (int j = 0; j < A.column; ++j) {
            inputFile >> A.data[i][j];
        }
    }

    inputFile.close();
}

// Hàm xuất ma trận ra tệp
void xuatMaTranRaTep(const maTran& A, const char* outputF) {
    std::ofstream outputFile(outputF);
    if (!outputFile) {
        std::cout << "Khong the mo file " << outputF << " de ghi" << std::endl;
        return;
    }

    outputFile << A.column << " " << A.row << std::endl;

    for (int i = 0; i < A.row; ++i) {
        for (int j = 0; j < A.column; ++j) {
            outputFile << std::fixed << std::setprecision(4) << A.data[i][j] << "   \t";
        }
        outputFile << std::endl;
    }

    outputFile.close();
    printTex("Ket qua da ghi ra file output va file quatrinh");xuongdong();
}

// Hàm tạo ma trận đơn vị
maTran taomatrandonvi(int n) {
    maTran identity;
    identity.row = identity.column = n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            identity.data[i][j] = (i == j) ? 1 : 0;
        }
    }
    return identity;
}

// Hàm tìm ma trận nghịch đảo bằng phương pháp Gauss-Jordan
maTran mtnghichdaogauss(const maTran& mat) {
    int n = mat.row;
    maTran matrix = mat;
    maTran identity = taomatrandonvi(n);

    if (mat.row != mat.column || tinhHangMaTran(mat)<mat.row ) {
        printTex("Ma tran khong kha nghich.");xuongdong();
        outputFile<<"Ma tran khong kha nghich."<<endl;
        matrix.row = matrix.column =0;
        return matrix;
    }

    for (int i = 0; i < n; ++i) {
        // Đặt phần tử chéo tại vị trí (i, i) là 1 để tạo bước biến đổi đối角 thành đơn vị
        double pivot = matrix.data[i][i];

        // Chia cả hàng hiện tại và hàng tương ứng trong ma trận đơn vị cho pivot
        for (int j = 0; j < n; ++j) {
            matrix.data[i][j] /= pivot;
            identity.data[i][j] /= pivot;
        }

        // Loại bỏ các thành phần khác không trong cột pivot (đưa thành phần này thành 0)
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = matrix.data[k][i];
                for (int j = 0; j < n; ++j) {
                    matrix.data[k][j] -= factor * matrix.data[i][j];
                    identity.data[k][j] -= factor * identity.data[i][j];
                }
            }
        }
    }

    return identity;
}

// Hàm tìm ma trận nghịch đảo bằng phương pháp Gauss-Jordan
maTran mtppdaiso(const maTran& mat) {
    int n = mat.row;
    maTran matrix = mat;
    maTran identity = taomatrandonvi(n);
    if (mat.row != mat.column || tinhHangMaTran(mat)<mat.row ) {
        printTex("Ma tran khong kha nghich.");xuongdong();
        outputFile<<"Ma tran khong kha nghich."<<endl;
        matrix.row = matrix.column =0;
        return matrix;
    }
    for (int i = 0; i < n; ++i) {
        // Đặt phần tử chéo tại vị trí (i, i) là 1 để tạo bước biến đổi đối thành đơn vị
        double pivot = matrix.data[i][i];

        // Chia cả hàng hiện tại và hàng tương ứng trong ma trận đơn vị cho pivot
        for (int j = 0; j < n; ++j) {
            matrix.data[i][j] /= pivot;
            identity.data[i][j] /= pivot;
        }

        // Loại bỏ các thành phần khác không trong cột pivot (đưa thành phần này thành 0)
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = matrix.data[k][i];
                for (int j = 0; j < n; ++j) {
                    matrix.data[k][j] -= factor * matrix.data[i][j];
                    identity.data[k][j] -= factor * identity.data[i][j];
                }
            }
        }
    }

    return identity;
}


