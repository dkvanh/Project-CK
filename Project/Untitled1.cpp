#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <conio.h>

void color(int color);  
void gotoxy(int x, int y);
void drawframe();
void input();
void MENU();
void color(int color)
	{
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    }
    
void gotoxy(int x, int y)
	{
	    COORD c;
	    c.X=x;
	    c.Y=y;
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	}

void drawframe()
	{
	    int i;
	    gotoxy(10,1);
	    color(30);
	    printf("-------------------QUAN LI SINH VIEN-------------------");
	    color(10);
	    for(i=0; i<65; i++){
	        gotoxy(5+i,2);color(226);
	        printf("-");
	        gotoxy(5+i,17);
	        printf("-");
    }
    for(i=0; i<=13; i++)
		{
	        gotoxy(5,2);color(226);
	        gotoxy(4,3+i);
	        printf("||");
	        gotoxy(69,3+i);
	        printf("||");    
	    }
	for(i=3; i<= 16; i++)
		{
			gotoxy(6,i);color(176);
			printf("                                ");
		}	        
	}
    

/*----------------------------------------------------------------------------------*/
struct Ngaysinh 
	{
		int ngay;
		int thang;
		int nam;
	};
typedef struct Ngaysinh DATEE;

struct Sinhvien 
	{
		int mssv;
		char hoten[50];
		char gioitinh[10];
		DATEE ngaysinh;
	};
typedef struct Sinhvien SINHVIEN;

struct nodesinhvien 
	{
		SINHVIEN data;
		struct nodesinhvien *Next;
	};
typedef struct nodesinhvien NODEsv;

struct danhsachSV 
	{
		NODEsv *Head;
		NODEsv *Tail;
	};
typedef struct danhsachSV LISHsv; 

struct Hocphan 
	{
		char mahp[30];
		char tenhp[50];
		int sotc;
	};
typedef struct Hocphan HOCPHAN;

struct nodehocphan 
	{
		HOCPHAN data;
		struct nodehocphan *Next;
	};
typedef struct nodehocphan NODEhp;

struct danhsachHP
 	{
		NODEhp *Head;
		NODEhp *Tail;
	};
typedef struct danhsachHP LISHhp;

struct Diem 
	{
		char mahp[30];
		int mssv;
		float diemhp;
	};
typedef struct Diem DIEM;

struct nodediem 
	{
		DIEM data;
		struct nodediem *Next;
	};
typedef struct nodediem NODEd;

struct danhsachD 
	{
		NODEd *Head;
		NODEd *Tail;
	};
typedef struct danhsachD LISHd;

struct trungbinhtichluy 
	{
		int mssv;
		float cpa;
	};
typedef struct trungbinhtichluy cpa;

NODEsv *TimSV ( LISHsv lsv , int mssv ) 
	{
		for ( NODEsv *k = lsv.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->data.mssv == mssv )
					return k;
			}	
		return NULL;
	}
	
NODEhp *TimHP ( LISHhp lhp , char mahp[] ) 
	{
		int x;
		for ( NODEhp *k = lhp.Head ; k != NULL ; k = k->Next ) 
			{
				x = strcmp ( k->data.mahp , mahp );
				if ( x == 0 ) 
					return k;
			}
		return NULL;
	}
	
NODEd *TimD ( LISHd ld , int mssv , char mahp[] ) 
	{
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next) 
			{
				if (( strcmp(k->data.mahp,mahp) == 0) && (k->data.mssv == mssv ))
					return k;
			}
		return NULL;
	}	

void Nhatkythemsv ( SINHVIEN info )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Sinh vien da them :\n\n");
		fprintf(f,"MSSV      : %d\n",info.mssv);
		fprintf(f,"Ho va ten : %s\n",info.hoten);
		fprintf(f,"Gioi tinh : %s\n",info.gioitinh);
		fprintf(f,"Ngay sinh : %d/%d/%d",info.ngaysinh.ngay,info.ngaysinh.thang,info.ngaysinh.nam);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);
	}

void Nhatkythemhp ( HOCPHAN info )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Hoc phan da them :\n\n");
		fprintf(f,"Ma hoc phan : %s\n",info.mahp);
		fprintf(f,"Ten mon hoc : %s\n",info.tenhp);
		fprintf(f,"So tin chi  : %d",info.sotc);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);
	}

void Nhatkythemd ( DIEM info )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Diem hoc phan da them la :\n\n");
		fprintf(f,"MSSV        : %d\n",info.mssv);
		fprintf(f,"Ma hoc phan : %s\n",info.mahp);
		fprintf(f,"Diem        : %.1f",info.diemhp);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);		
	}

void Nhatkyxoasv ( int mssv , LISHsv lsv)
	{
		NODEsv *p = TimSV(lsv,mssv);
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Sinh vien bi xoa thong tin va toan bo diem lien quan :\n\n");
		fprintf(f,"MSSV 	 : %d\n",p->data.mssv);
		fprintf(f,"Ho va ten : %s\n",p->data.hoten);
		fprintf(f,"Gioi tinh : %s\n",p->data.gioitinh);
		fprintf(f,"Ngay sinh : %d/%d/%d",p->data.ngaysinh.ngay,p->data.ngaysinh.thang,p->data.ngaysinh.nam);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);	
	}

void Nhatkyxoahp ( char mahp[30] , LISHhp lhp)
	{
		NODEhp *p = TimHP(lhp,mahp);
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Hoc phan bi xoa thong tin va toan bo diem lien quan :\n\n");
		fprintf(f,"Ma hoc phan : %s\n",p->data.mahp);
		fprintf(f,"Ten mon hoc : %s\n",p->data.tenhp);
		fprintf(f,"So tin chi  : %d",p->data.sotc);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);	
	}

void Nhatkyxoad ( NODEd *p )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Diem hoc phan da xoa :\n\n");
		fprintf(f,"MSSV        : %d\n",p->data.mssv);
		fprintf(f,"Ma hoc phan : %s\n",p->data.mahp);
		fprintf(f,"Diem        : %.1f",p->data.diemhp);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);		
	}

void Nhatkysuasv ( NODEsv *p )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Sinh vien %d duoc sua thong tin moi :\n",p->data.mssv);
		fprintf(f,"MSSV      : %d\n",p->data.mssv);
		fprintf(f,"Ho va ten : %s\n",p->data.hoten);
		fprintf(f,"Gioi tinh : %s\n",p->data.gioitinh);
		fprintf(f,"Ngay sinh : %d/%d/%d",p->data.ngaysinh.ngay,p->data.ngaysinh.thang,p->data.ngaysinh.nam);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);		
	}

void Nhatkysuahp ( NODEhp *p )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Hoc phan %s duoc sua moi :\n",p->data.mahp);
		fprintf(f,"Ma hoc phan : %s\n",p->data.mahp);
		fprintf(f,"Ten mon hoc : %s\n",p->data.tenhp);
		fprintf(f,"So tin chi  : %d",p->data.sotc);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);				
	}

void Nhatkysuad ( NODEd *p )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Diem hoc phan %s cua sinh vien %d duoc sua moi :\n",p->data.mahp,p->data.diemhp);
		fprintf(f,"MSSV        : %d\n",p->data.mssv);
		fprintf(f,"Ma hoc phan : %s\n",p->data.mahp);
		fprintf(f,"Diem        : %.1f",p->data.diemhp);	
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);						
	}
	
void NhatkyTBtatcasv ( cpa c )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"MSSV : %d\n",c.mssv);
		fprintf(f,"CPA  : %.2f",c.cpa);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);			
	}

void Nhatkysvchuadathp ( NODEsv *p , NODEd *k )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Sinh vien co MSSV      : %d ,\t",p->data.mssv);
		fprintf(f,"ho va ten : %s\t chua dat hoc phan %s",p->data.hoten,k->data.mahp);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);						
	}

void Nhatkyhpchuadatcuasv ( NODEd *k )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Sinh vien %d chua dat hoc phan %s",k->data.mssv,k->data.mahp);	
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);			
	}

void NhatkyTBcuasv ( int mssv , float cpa )
	{
		FILE *f = fopen("C:\\Users\\Admin\\Desktop\\NHATKY.txt","a");
		fprintf(f,"Diem trung binh tich luy cua sinh vien %d la : %.2f",mssv,cpa);
		fprintf(f,"\n\n------------------------------\n\n");
		fclose(f);				
	}


void taoLISHhp ( LISHhp &lhp ) 
	{
		lhp.Head = NULL;
		lhp.Tail = NULL;
	}

NODEhp *taoNODEhp ( HOCPHAN info ) 
	{
		NODEhp *p = (NODEhp *)malloc(sizeof(NODEhp));
		p->data = info;
		p->Next = NULL;
		return p;
	}

void themNODEhpvaodau ( LISHhp &lhp , NODEhp *p ) 
	{
		if ( lhp.Head == NULL )
		lhp.Head = lhp.Tail = p;
		else
			{
				p->Next = lhp.Head;
				lhp.Head = p;
			}
	}

HOCPHAN InputHP ( LISHhp lhp ) 
	{
		HOCPHAN info;
		printf("Nhap Ma hoc phan : "); fflush(stdin);
		scanf("%s", &info.mahp);
		NODEhp *p = TimHP(lhp,info.mahp);
		while ( p != NULL ) 
			{
				printf("Ma hoc phan da ton tai, moi nhap lai!!!\n");
				printf("Nhap Ma hoc phan : "); fflush(stdin);
				scanf("%s", &info.mahp);
				p = TimHP(lhp,info.mahp);
			}
		printf("Nhap ten mon hoc : "); fflush (stdin);
		gets(info.tenhp);
		printf("Nhap so tin chi : ");
		scanf("%d", &info.sotc);
		printf("\nThem hoc phan thanh cong !!!");
		Nhatkythemhp(info);
		return info;
	}

void XoaNODEhpdau ( LISHhp &lhp ) 
	{
		if ( lhp.Head == NULL ) 
			return;
		NODEhp *p = lhp.Head;
		lhp.Head = lhp.Head->Next;
		p->Next = NULL;
		free(p);	
	}

void XoaNODEhpcuoi ( LISHhp &lhp ) 
	{
		if ( lhp.Head == NULL )
			return;
		for ( NODEhp *k = lhp.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->Next == lhp.Tail ) 
					{
						free (lhp.Tail);
						k->Next = NULL;
						lhp.Tail = k;
					}	
			}	
	}

void SuaHP ( LISHhp lhp ) 
	{
		HOCPHAN suahp;
		printf("Nhap Ma hoc phan : "); fflush(stdin); 
		gets(suahp.mahp);
		NODEhp *p = TimHP(lhp,suahp.mahp);
		if ( p == NULL ) 
			printf("Ma hoc phan khong ton tai !\n");
		else 
			{
				printf("Nhap ten mon hoc : "); fflush(stdin); gets(suahp.tenhp);
				printf("Nhap so tin chi : "); scanf("%d",&suahp.sotc);
				p->data = suahp;
				Nhatkysuahp(p);
				printf("\nSua hoc phan thanh cong!!!");
			}
 	}

void OutputHP( LISHhp lhp) 
	{
		if ( lhp.Head == NULL )
			{
				printf("Danh sach trong !!!");
				return;
			}
		for ( NODEhp *k = lhp.Head ; k != NULL ; k = k->Next) 
			{
				printf("Ma hoc phan : %s\n",k->data.mahp);
				printf("Ten mon hoc : %s\n",k->data.tenhp);
				printf("So tin chi : %d\n",k->data.sotc);
				printf("\n--------------------\n");
			}
	}

void GhiLISHhpvaofilebin ( LISHhp lhp ) 
	{
		FILE *fhp;
		fhp = fopen ("HOCPHAN.bin","wb");
		if ( fhp == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		for ( NODEhp *k = lhp.Head ; k != NULL ; k = k->Next ) 
			{
				fwrite ( &k -> data , sizeof(HOCPHAN) , 1 , fhp );
			}
		fclose(fhp);	
	}

void DocLISHhptufilebin ( LISHhp &lhp ) 
	{
		FILE *fhp;
		HOCPHAN info;
		fhp = fopen ("HOCPHAN.bin","rb");
		if( fhp == NULL ) 
			{
				printf("Error!");
				exit(1);
			} 
		while ( fread( &info, sizeof (HOCPHAN), 1, fhp) > 0 )
			{
				themNODEhpvaodau(lhp,taoNODEhp(info));
			}
		fclose(fhp);
	}		


void taoLISHsv ( LISHsv &lsv ) 
	{
		lsv.Head = NULL;
		lsv.Tail = NULL;
	}

NODEsv *taoNODEsv ( SINHVIEN info ) {
	NODEsv *p = (NODEsv *)malloc(sizeof(NODEsv));
	p->data = info;
	p->Next = NULL;
	return p;
}

void themNODEsvvaodau ( LISHsv &lsv , NODEsv *p ) 
	{
		if ( lsv.Head == NULL )
		lsv.Head = lsv.Tail = p;
		else
			{
				p->Next = lsv.Head;
				lsv.Head = p;
			}
	}
						
SINHVIEN InputSV ( LISHsv lsv ) 
	{
		SINHVIEN info;
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d", &info.mssv); 
		NODEsv *p = TimSV(lsv,info.mssv);
		while( p != NULL ) 
			{
				printf("Ma so sinh vien da ton tai ! Moi ban nhap lai !!!\n");
				printf("Nhap MSSV : "); fflush(stdin); scanf("%d", &info.mssv);
				p = TimSV(lsv,info.mssv);
			}
		printf("Nhap ho va ten sinh vien : "); fflush(stdin); gets(info.hoten); 
		printf("Nhap gioi tinh : "); gets(info.gioitinh);
		printf("Nhap ngay thang nam sinh\n"); 
		printf("\t- Ngay  : "); fflush(stdin); scanf("%d", &info.ngaysinh.ngay); 
		printf("\t- Thang : "); fflush(stdin); scanf("%d", &info.ngaysinh.thang); 
		printf("\t- Nam   : "); fflush(stdin); scanf("%d", &info.ngaysinh.nam); 
		printf("\n Them sinh vien thanh cong !!!");
		Nhatkythemsv(info);
		return info;
	}

void XoaNODEsvdau ( LISHsv &lsv ) 
	{
		if ( lsv.Head == NULL )
			return;
		NODEsv *p = lsv.Head;
		lsv.Head = lsv.Head->Next;
		p->Next = NULL;
		free(p);
	}

void XoaNODEsvcuoi ( LISHsv &lsv ) 
	{
		if ( lsv.Head == NULL )
			return;
		for ( NODEsv *k = lsv.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->Next == lsv.Tail ) 
					{
						free (lsv.Tail);
						k->Next = NULL;
						lsv.Tail = k;
					}	
			}	
	}

void SuaSV ( LISHsv lsv ) 
	{
		SINHVIEN suasv;
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d", &suasv.mssv);
		NODEsv *p = TimSV(lsv,suasv.mssv);
		if ( p == NULL ) 
			printf("MSSV khong ton tai !\n");
		else 
			{
				printf("Nhap ho va ten moi : "); fflush(stdin); gets(suasv.hoten);
				printf("Nhap gioi tinh moi : "); gets(suasv.gioitinh);
				printf("Nhap ngay thang nam sinh moi :\n");
				printf("\t- Ngay  : "); fflush(stdin); scanf("%d", &suasv.ngaysinh.ngay);
				printf("\t- Thang : "); fflush(stdin); scanf("%d", &suasv.ngaysinh.thang);
				printf("\t- Nam   : "); fflush(stdin); scanf("%d", &suasv.ngaysinh.nam);
				p->data = suasv;
				Nhatkysuasv(p);
				printf("\nSua sinh vien thanh cong !!!");
			}
	}

void OutputSV ( LISHsv lsv ) 
	{
		if ( lsv.Head == NULL )
			{
				printf("Danh sach trong !!!");
				return;
			}
		for ( NODEsv *k = lsv.Head ; k != NULL ; k = k->Next ) 
			{
				printf("MSSV : %d\n",k->data.mssv);
				printf("Ho va ten : %s\n",k->data.hoten);
				printf("Gioi tinh : %s\n",k->data.gioitinh);
				printf("Ngay sinh : %d/%d/%d\n",k->data.ngaysinh.ngay,k->data.ngaysinh.thang,k->data.ngaysinh.nam);
				printf("\n--------------------\n");
			}
	}

void GhiLISHsvvaofilebin ( LISHsv lsv ) 
	{
		FILE *fsv;
		fsv = fopen ("SINHVIEN.bin","wb");
		if( fsv == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		for ( NODEsv *k = lsv.Head ; k !=NULL ; k = k->Next ) 
			{
				fwrite (&k->data,sizeof(SINHVIEN),1,fsv);
			}
		fclose(fsv);
	}

void DocLISHsvtufilebin(LISHsv &lsv) 
	{
		FILE *fsv;
		SINHVIEN info;
		fsv = fopen ("SINHVIEN.bin","rb");
		if( fsv == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		while ( fread (&info,sizeof(SINHVIEN),1,fsv) > 0 )
			{
				themNODEsvvaodau(lsv,taoNODEsv(info));
			}
		fclose(fsv);
	}

void taoLISHd ( LISHd &ld ) 
	{
		ld.Head = NULL;
		ld.Tail = NULL;
	}

NODEd *taoNODEd ( DIEM info ) 
	{
		NODEd *p = (NODEd *)malloc(sizeof(NODEd));
		p->data = info;
		p->Next = NULL;
		return p;	
	}

void themNODEdvaodau ( LISHd &ld , NODEd *p ) 
	{
		if ( ld.Head == NULL )
		ld.Head = ld.Tail = p;
		else
			{
				p->Next = ld.Head;
				ld.Head = p;
			}	
	}

float Lamtron ( float a ) 
	{
		float b = a;
		while (a>1) 
			a-=1;
	 	if(a>=0 && a<0.25) 
			b=b-a;
	 	else if(a>=0.25 && a<0.75) 
			b=b-a+0.5;
	 	else b=b-a+1;
	 	return b;
	}

bool KiemtramssvtrongLISHd ( LISHd ld , int mssv ) 
	{
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->data.mssv == mssv )
					return true;
			}
		return false;
	}
bool KiemtramahptrongLISHd ( LISHd ld , char mahp[] ) 
	{
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				if ( strcmp(k->data.mahp,mahp) == 0 )
					return true;
			}
		return false;
	}

DIEM InputD ( LISHsv lsv , LISHhp lhp , LISHd ld ) 
	{
		DIEM info;
		NODEsv *p1;
		NODEhp *p2;
		NODEd *p;
		do
			{
				printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&info.mssv);
				p1 = TimSV(lsv,info.mssv);
				while ( p1 == NULL ) 
					{
						printf("MSSV khong ton tai ! Moi nhap lai !\n");
						printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&info.mssv);
						p1 = TimSV(lsv,info.mssv);	
					}
				printf("Nhap Ma hoc phan : "); fflush(stdin); gets(info.mahp);
				p2 = TimHP(lhp,info.mahp);
				while ( p2 == NULL ) 
					{
						printf("Ma hoc phan khong ton tai ! Moi nhap lai !\n");
						printf("Nhap Ma hoc phan : "); fflush(stdin); gets(info.mahp);
						p2 = TimHP(lhp,info.mahp);
					}
				p = TimD (ld,info.mssv,info.mahp);
				if ( p != NULL )
					{
						printf("Sinh vien da co diem voi hoc phan nay !!! Moi nhap lai !!!\n");
					}
			}
		while ( p != NULL );
		printf("Nhap diem hoc phan : "); fflush(stdin); scanf("%f",&info.diemhp);
		while ((info.diemhp < 0 ) || (info.diemhp > 10 )) 
			{
				printf("Loi nhap diem ! Moi nhap lai !\n");
				printf("Nhap diem hoc phan : "); fflush(stdin); scanf("%f",&info.diemhp);	
			}
		info.diemhp = Lamtron(info.diemhp);
		printf("\nThem diem thanh cong !!!");
		Nhatkythemd(info);
		return info;
	}

void XoaNODEddau( LISHd &ld ) 
	{
		if ( ld.Head == NULL )
			return;
		NODEd *p = ld.Head;
		ld.Head = ld.Head->Next;
		p->Next = NULL;
		free(p);	
	}

void XoaNODEdcuoi ( LISHd &ld ) 
	{
		if ( ld.Head == NULL )
			return;
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->Next == ld.Tail ) 
					{
						free (ld.Tail);
						k->Next = NULL;
						ld.Tail = k;
					}	
			}		
	}

void XoaNODEd ( LISHsv &lsv , LISHhp &lhp , LISHd &ld ) 
	{
		int mssv;
		char mahp[30];
		NODEd *j;
		NODEd *p;
		if ( ld.Head == NULL ) 
			{
				printf("Danh sach diem hoc phan rong !!!\n");
				return;	
			}
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&mssv);
		if ( TimSV(lsv,mssv) == NULL )
			{
				printf("Khong ton tai MSSV!!!\n");
				return;
			}
		printf("Nhap Ma hoc phan : "); fflush (stdin); gets(mahp);
		if ( TimHP(lhp,mahp) == NULL )
			{
				printf("Khong ton tai Ma hoc phan !!!\n");
				return;
			}
		p = TimD(ld,mssv,mahp);
		if ( p == NULL ) 
			{
				printf("Khong co MSSV voi Ma hoc phan nay!\n");
				return;
			}
		Nhatkyxoad(p);
		if((ld.Head->data.mssv == p->data.mssv) && (strcmp(ld.Head->data.mahp,p->data.mahp) == 0 )) 
			{
				XoaNODEddau(ld);
				printf("\nXoa diem thanh cong !!!");
				return;
			}
		if(( ld.Tail->data.mssv == p->data.mssv) && (strcmp (ld.Tail->data.mahp,p->data.mahp) == 0 )) 
			{
				XoaNODEdcuoi(ld);
				printf("\nXoa diem thanh cong !!!");
				return;
			}
		for( NODEd *k = ld.Head ; k != NULL ; k = k->Next )
			{
				if ((k->data.mssv == p->data.mssv) && (strcmp(k->data.mahp,p->data.mahp) == 0)) 
					{
						j->Next = k->Next;
						free(k);
						printf("\nXoa diem thanh cong !!!");
						return;
					}
					j = k;			
			}
	}

void SuaD ( LISHsv lsv , LISHhp lhp , LISHd ld ) 
	{
		int mssv;
		char mahp[30];
		NODEd *p;
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&mssv);
		if ( TimSV(lsv,mssv) == NULL )
			{
				printf("Khong ton tai MSSV!!!\n");
				return;
			}
		printf("Nhap Ma hoc phan : "); fflush (stdin); gets(mahp);
		if ( TimHP(lhp,mahp) == NULL )
			{
				printf("Khong ton tai Ma hoc phan !!!\n");
				return;
			}
		p = TimD(ld,mssv,mahp);
		if ( p == NULL ) 
			{
				printf("Khong co MSSV voi Ma hoc phan nay!\n");
				return;
			}
		printf("Nhap diem hoc phan : "); fflush (stdin); scanf("%f",&p->data.diemhp);
		while ((p->data.diemhp < 0) || (p->data.diemhp > 10)) 
			{
				printf("Loi nhap diem ! Moi nhap lai !\n");
				printf("Nhap diem hoc phan : "); fflush(stdin); scanf("%f",&p->data.diemhp);	
			}
		p->data.diemhp = Lamtron(p->data.diemhp);
		Nhatkysuad(p);
		printf("\nSua diem thanh cong!!!");
	}

void OutputD ( LISHd ld ) 
	{	
		if ( ld.Head == NULL )
			{
				printf("Danh sach trong !!!");
				return;
			}
		for( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				printf("MSSV : %d\n",k->data.mssv);
				printf("Ma hoc phan : %s\n",k->data.mahp);
				printf("Diem hoc phan : %.1f\n",k->data.diemhp);
				printf("\n--------------------\n");
			}
	}

void GhiLISHdvaofilebin ( LISHd ld ) 
	{
		FILE *fd;
		fd = fopen ("DIEM.bin","wb");
		if( fd == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		for ( NODEd *k = ld.Head ; k !=NULL ; k = k->Next ) 
			{
				fwrite (&k->data,sizeof(DIEM),1,fd);
			}
		fclose(fd);
	}

void DocLISHdtufilebin( LISHd &ld ) 
	{
		FILE *fd;
		DIEM info;
		fd = fopen ("DIEM.bin","rb");
		if( fd == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		while ( fread( &info, sizeof(DIEM), 1, fd) > 0 )
			{
				themNODEdvaodau(ld,taoNODEd(info));
			}
		fclose(fd);
	}

void XoaNODEdkhibietmssv ( LISHd &ld , int mssv ) 
	{
		NODEd *j;
		if( ld.Head->data.mssv == mssv )
			XoaNODEddau(ld);
		if( ld.Tail->data.mssv == mssv )
			XoaNODEdcuoi(ld);
		for( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->data.mssv == mssv ) 
					{
						j->Next = k->Next;
						free(k);
						return;
					}
				j = k;			
			}
	}

void XoaNODEdkhibietmahp ( LISHd &ld , char mahp[] ) 
	{
		NODEd *j;
		if( strcmp(ld.Head->data.mahp,mahp) == 0 )
			XoaNODEddau(ld);
		if (strcmp(ld.Tail->data.mahp,mahp) == 0 )
			XoaNODEdcuoi(ld);
		for( NODEd *k = ld.Head ; k != NULL ; k = k->Next ) 
			{
				if (strcmp(k->data.mahp,mahp) == 0 ) 
					{
						j->Next = k->Next;
						free(k);
						return;
					}
				j = k;			
			}	
	}

void XoaNODEsv ( LISHsv &lsv , LISHd &ld ) 
	{
		int mssv;
		NODEsv *j = (NODEsv *)malloc(sizeof(NODEsv));
		if (lsv.Head == NULL) {
			printf("Danh sach sinh vien rong !!!\n");
			return;
		}	
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&mssv);
		NODEsv *p = TimSV(lsv,mssv);
		if ( p == NULL ) 
			{
				printf("MSSV khong ton tai!\n");
				return;
			}
		Nhatkyxoasv(mssv,lsv);
		while ( KiemtramssvtrongLISHd(ld,mssv) )
			XoaNODEdkhibietmssv(ld,mssv);
		if ( lsv.Head->data.mssv == mssv ) 
			{
				XoaNODEsvdau(lsv);
				printf("\nXoa sinh vien thanh cong");
				return;
			}
		if ( lsv.Tail->data.mssv == mssv )
			{
				XoaNODEsvcuoi(lsv);
				printf("\nXoa sinh vien thanh cong");
				return;
			}
		for( NODEsv *k = lsv.Head ; k != NULL ; k = k->Next ) 
			{
				if ( k->data.mssv == mssv ) 
					{
						j->Next = k->Next;
						free(k);
						printf("\nXoa sinh vien thanh cong");
						return;
					}
				j = k;				
			}
	}

void XoaNODEhp ( LISHhp &lhp , LISHd &ld ) 
	{
		int x;
		char mahp[30];
		NODEhp *p;
		NODEhp *j = (NODEhp *)malloc(sizeof(NODEhp));
		if ( lhp.Head == NULL) 
			{
				printf("Danh sach hoc phan rong !!!\n");
				return;
			}
		printf("Nhap Ma hoc phan : "); fflush(stdin); gets(mahp);
		p = TimHP(lhp,mahp);
		if( p == NULL ) 
			{
				printf("Khong ton tai ma hoc phan!\n");
				return;
			}
		Nhatkyxoahp(mahp,lhp);
		while( KiemtramahptrongLISHd(ld,mahp) )
			XoaNODEdkhibietmahp(ld,mahp);	
		if ( strcmp(lhp.Head->data.mahp,mahp) == 0 ) 
			{
				XoaNODEhpdau(lhp);
				printf("\nXoa hoc phan thanh cong !!!");
				return;
			}
		if( strcmp(lhp.Tail->data.mahp,mahp) == 0 )
			{
				XoaNODEhpcuoi(lhp);
				printf("\nXoa hoc phan thanh cong !!!");
				return;
			}
		for( NODEhp *k = lhp.Head ; k != NULL ; k = k->Next ) 
			{
				x = strcmp(k->data.mahp,mahp);
				if ( x == 0 ) 
					{
						j->Next = k->Next;
						free(k);
						printf("\nXoa hoc phan thanh cong !!!");
						return;
					}
				j = k;				
			}
	}

float Quydoidiem ( float x )
	{
		if (x < 4)
		{
			return 0;
		}
		if ((x >= 4) && (x < 5))
		{
			return 1;
		}
		if ((x >= 5) && (x < 5.5))
		{
			return 1.5;
		}
		if ((x >= 5.5) && (x < 6.5))
		{
			return 2;
		}
		if ((x >= 6.5) && (x < 7))
		{
			return 2.5;
		}
		if ((x >= 7) && (x < 8))
		{
			return 3;
		}
		if ((x >= 8) && (x < 8.5))
		{
			return 3.5;
		}
		if (x >= 8.5)
		{
			return 4;
		}
	}

void Tinhtrungbinhtichluy( LISHsv lsv , LISHhp lhp , LISHd ld ) 
	{
		NODEhp *k;
		float S;
		int Stc;
		FILE *fcpa;
		cpa c;
		fcpa = fopen ("CPA.bin","wb");
		if ( fcpa == NULL ) 
			{
				printf("Error!");
				return;
			}
		printf("Diem trung binh tich luy cua cac sinh vien :\n\n");
		for ( NODEsv *i = lsv.Head ; i != NULL ; i = i->Next ) 
			{
				S = 0;
				Stc = 0;
				for ( NODEd *j = ld.Head ; j != NULL ; j = j->Next ) 
					{
						if( i->data.mssv == j->data.mssv ) 
							{
								k = TimHP(lhp,j->data.mahp);
								S += (k->data.sotc)*Quydoidiem(j->data.diemhp);
								Stc += k->data.sotc;				
							}
					}
				if( Stc == 0 )
					{
						c.mssv = i->data.mssv;
						c.cpa = Stc;
						printf("MSSV : %d\n",i->data.mssv);
						printf("CPA : %.2f\n",Stc);
						printf("\n--------------------\n");
						fwrite(&c, sizeof(cpa),1,fcpa);
						NhatkyTBtatcasv(c);
					}
				else
					{
						c.mssv = i->data.mssv;
						c.cpa = S/Stc;
						printf("MSSV : %d\n",i->data.mssv);
						printf("CPA : %.2f\n",S/Stc);
						printf("\n--------------------\n");
						fwrite(&c,sizeof(cpa),1,fcpa);
						NhatkyTBtatcasv(c);
					}
			}
		fclose(fcpa);
	}

void Danhsachsvchuadathp( LISHsv lsv , LISHhp lhp , LISHd ld ) 
	{
		int count = 0;
		NODEsv *p;
		NODEhp *j;
		char mahp[30];
		printf("Nhap Ma hoc phan : "); fflush(stdin); gets(mahp);
		j = TimHP(lhp,mahp);
		if ( j == NULL )
			{
				printf("Khong ton tai Ma hoc phan !!!\n");
				return;
			}
		if ( KiemtramahptrongLISHd(ld,mahp) == false )
			{
				printf("Khong co sinh vien hoc mon nay!!!\n");
				return;
			}
		printf("Danh sach sinh vien chua dat hoc phan %s :\n",mahp);
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next )
			{
				if ((strcmp(k->data.mahp,mahp) == 0) && (k->data.diemhp < 4)) 
					{
						count++;
						p = TimSV(lsv,k->data.mssv);
						printf("MSSV : %d\n",p->data.mssv);
						printf("Ho va ten : %s\n",p->data.hoten);
						printf("\n--------------------\n");
						Nhatkysvchuadathp(p,k);
					}
			}
		if ( count == 0 )
			printf("Khong co sinh vien nao chua dat hoc phan nay!!!\n");
	}

void Danhsachhpchuadatcuasv ( LISHsv lsv , LISHhp lhp , LISHd ld )
	{
		int count = 0;
		int mssv;
		NODEhp *p;
		NODEsv *j;
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d", &mssv);
		j = TimSV(lsv,mssv);
		if( j == NULL )
			{
				printf("Khong ton tai MSSV!!!\n");
				return;				
			}
		if ( KiemtramssvtrongLISHd(ld,mssv) == false )
			{
				printf("Sinh vien %d chua hoc mon nao !!!\n",mssv);
				return;
			}
		printf("Danh sach hoc phan sinh vien %d chua dat : \n",mssv);
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next )
			{
				if ((k->data.mssv == mssv) && (k->data.diemhp < 4))
					{
						count++;
						p = TimHP(lhp,k->data.mahp);
						printf("\n\tMa hoc phan : %s\n",k->data.mahp);
						printf("\tTen mon hoc : %s\n",p->data.tenhp);
						printf("\n\t--------------------\n");
						Nhatkyhpchuadatcuasv(k);
					}
			}
		if ( count == 0 )				
				printf("Danh sach trong!!!");
	}

void Trungbinhtichluysv ( LISHsv lsv , LISHhp lhp , LISHd ld )
	{
		NODEhp *p;
		NODEsv *j;
		float S = 0;
		int Stc = 0;
		int mssv;		
		printf("Nhap MSSV : "); fflush(stdin); scanf("%d",&mssv);
		j = TimSV(lsv,mssv);
		if( j == NULL )
			{
				printf("Khong ton tai MSSV!!!\n");
				return;				
			}
		for ( NODEd *k = ld.Head ; k != NULL ; k = k->Next )
			{
				if ( k->data.mssv == mssv ) 
					{
						p = TimHP(lhp,k->data.mahp);
						S += (p->data.sotc)*Quydoidiem(k->data.diemhp);
						Stc += p->data.sotc;
					}
			}
		if ( Stc == 0 ) 
			{
				printf("Diem trung binh tich luy cua sinh vien %d : %.2f\n",mssv,Stc);
				NhatkyTBcuasv(mssv,Stc);
			}
		else
			{
				printf("Diem trung binh tich luy cua sinh vien %d : %.2f\n",mssv,S/Stc);
				NhatkyTBcuasv(mssv,Stc);
			}
	}

void Ghitrungbinhtichluyvaofilebin( LISHsv lsv , LISHhp lhp , LISHd ld ) 
	{
		NODEhp *k;
		float S;
		int Stc;
		FILE *fcpa;
		cpa c;
		fcpa = fopen ("CPA.bin","wb");
		if ( fcpa == NULL ) 
			{
				printf("Error!");
				exit(1);
			}
		for ( NODEsv *i = lsv.Head ; i != NULL ; i = i->Next ) 
			{
				S = 0;
				Stc = 0;
				for ( NODEd *j = ld.Head ; j != NULL ; j = j->Next ) 
					{
						if( i->data.mssv == j->data.mssv ) 
							{
								k = TimHP(lhp,j->data.mahp);
								S += (k->data.sotc)*Quydoidiem(j->data.diemhp);
								Stc += k->data.sotc;				
							}
					}
				if( Stc == 0 )
					{
						c.mssv = i->data.mssv;
						c.cpa = Stc;
						fwrite(&c, sizeof(cpa),1,fcpa);
					}
				c.mssv = i->data.mssv;
				c.cpa = S/Stc;
				fwrite(&c,sizeof(cpa),1,fcpa);
			}
		fclose(fcpa);
	}

/* MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN */

int main() 
	{
		int tieptuc;
		int key0, key1, key2, key3, key4, key5, key6;
		LISHhp lhp;
		LISHd ld;
		LISHsv lsv;
		taoLISHd(ld);
		taoLISHhp(lhp);
		taoLISHsv(lsv);
		DocLISHsvtufilebin(lsv);
		DocLISHhptufilebin(lhp);
		DocLISHdtufilebin(ld);
		int Set[] = {7,7,7,7,7,7}; // default colors
		int counter = 1;
		char key;
	
		while (1) 
			{
			    MENUPOP: 
				drawframe();
				gotoxy(0,0);
				color(90);
			    if (counter == 1) 
					{
			     		 Set[0] = 20;
			    	}
			    gotoxy(10, 4);
			    color(Set[0]);
			    printf(" 1. HIEN THI DANH SACH  ");
			
			    gotoxy(10, 6);
			    color(Set[1]);
			    printf(" 2. NHAP DU LIEU ");
			
			    gotoxy(10, 8);
			    color(Set[2]);
			    printf(" 3. SUA DU LIEU ");
			
			    gotoxy(10, 10);
			    color(Set[3]);
			    printf(" 4. XOA DU LIEU");
			
			    gotoxy(10, 12);
			    color(Set[4]);
			    printf(" 5. TRUY VAN DU LIEU ");
			    
			    gotoxy(10, 14);
			    color(Set[5]);
			    printf(" 6. OUT ");
			    
			    key = getch();
			    if (key == 72 && (counter >= 2 && counter <= 6)) 
					{
				      counter--;
				    } 
				else if (key == 80 && (counter >= 1 && counter <= 5)) 
					{
				      counter++;
				    } 
				else if (key == 72 && (counter <= 1)) 
					{
				      counter = 6;
				    } 
				else if (key == 80 && (counter >= 6)) 
					{
				      counter = 1;
				    }
	
			    if (key == '\r') 
					{
				    	if (counter == 6) 
							{
						        gotoxy(0, 17);
						        break;
					    	}		
					    system("cls");
						gotoxy(0, 5);
					
					    /*1.XEM DANH SACH-------------------------------*/
			
			    		if (counter == 1) 
				  			{
					       		while (1) 
									{
							        	int Set[] = {7,7,7}; // default colors
								        int counter = 1, i = 0;
								        char key;
								        while (1) 
								  			{
								          	    gotoxy(8,2);
								    			color(26);
								   				printf("HIEN THI DANH SACH:");
								   				
								            	if (counter == 1) 
								              		Set[0] = 74;	
													  							            	
									            gotoxy(8, 4);
									            color(Set[0]);
									            printf(" 1.SINH VIEN ");
									            
									            gotoxy(8, 6);
									            color(Set[1]);
									            printf(" 2.HOC PHAN ");
									            
									            gotoxy(8, 8);
									            color(Set[2]);
									            printf(" 3.DIEM SO ");
									            
									            key = getch();
									            if (key == 72 && (counter >= 2 && counter <= 3)) 								
									            	counter--;									
									            else if (key == 80 && (counter >= 1 && counter <= 2))
									            	counter++;									
									            else if (key == 72 && (counter <= 1))
									            	counter = 3;
									            else if (key == 80 && (counter >= 3)) 
									            	counter = 1;									
			            if (key == '\r') {
			              if (counter == 3) {
			                gotoxy(0, 17);
			                color(7);
			              }
			
			              system("cls");
			              gotoxy(0, 5);
			              if (counter == 1) {
			                OutputSV(lsv);
			                break;
			              }
			
			              if (counter == 2) {
			                OutputHP(lhp);
			                break;
			              }
			
			              if (counter == 3) {
			                OutputD(ld);
			                break;
			              }
			
			              key = getch();
			              if (key == '\r')
			                system("cls");
			            }
			
			            Set[0] = 7;
			            Set[1] = 7;
			            Set[2] = 7;
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			
			            if (counter == 2) {
			              Set[1] = 74;
			            }
			
			            if (counter == 3) {
			              Set[2] = 74;
			            }
			          }
			          gotoxy(45, 20);
			          color(78);
			          printf("Ban co muon tiep tuc xem cac danh sach con lai khong");
			
			          int Set1[] = {
			            7,
			            7
			          }; // default colors
			          int counter1 = 1;
			          char key1;
			          while (1) {
			            if (counter1 == 1) {
			              Set1[0] = 74;
			            }
			            gotoxy(45, 22);
			            color(Set1[0]);
			            printf(" 1.CO  ");
			            gotoxy(52, 22);
			            color(Set1[1]);
			            printf(" 2.BACK TO MENU ");
			            key1 = getch();
			            if (key1 == 75 && (counter1 == 2)) {
			              counter1--;
			
			            } else if (key1 == 77 && (counter1 == 1)) {
			              counter1++;
			
			            } else if (key1 == 75 && (counter1 <= 1)) {
			              counter1 = 2;
			            } else if (key1 == 77 && (counter1 >= 2)) {
			              counter1 = 1;
			            }
			
			            if (key1 == '\r') {
			              if (counter1 == 2) {
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter1 == 1) {
			                system("cls");
			                break;
			              }
			              if (counter1 == 2) {
			                goto MENUPOP;
			              }
			              key1 = getch();
			              if (key1 == '\r')
			                system("cls");
			            }
			
			            Set1[0] = 7;
			            Set1[1] = 7;
			            if (counter1 == 1) {
			              Set1[0] = 74;
			            }
			
			            if (counter1 == 2) {
			              Set1[1] = 74;
			            }
			          }
			        }
			      }
			
			      /*-----------------------------------------NHAP DU LIEU------------------------------ */
			      if (counter == 2) {
			        while (1) {
			          int Set[] = {
			            7,
			            7,
			            7
			          }; // default colors
			          int counter = 1, i = 0;
			          char key;
			          while (1) {
			          	    gotoxy(8,2);
			    			color(26);
			   				 printf("NHAP DU LIEU:");
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			            gotoxy(8, 4);
			            color(Set[0]);
			            printf(" 1.SINH VIEN ");
			            gotoxy(8, 6);
			            color(Set[1]);
			            printf(" 2.HOC PHAN ");
			            gotoxy(8, 8);
			            color(Set[2]);
			            printf(" 3.DIEM SO ");
			            key = getch();
			            if (key == 72 && (counter >= 2 && counter <= 3)) {
			              counter--;
			
			            } else if (key == 80 && (counter >= 1 && counter <= 2)) {
			              counter++;
			
			            } else if (key == 72 && (counter <= 1)) {
			              counter = 3;
			            } else if (key == 80 && (counter >= 3)) {
			              counter = 1;
			            }
			
			            if (key == '\r') {
			              if (counter == 3) {
			                gotoxy(0, 17);
			                color(7);
			              }
			
			              system("cls");
			              gotoxy(0, 5);
			              if (counter == 1) {
			                NODEsv * p = taoNODEsv(InputSV(lsv));
			                themNODEsvvaodau(lsv, p);
			
			                break;
			              }
			
			              if (counter == 2) {
			                NODEhp * p = taoNODEhp(InputHP(lhp));
			                themNODEhpvaodau(lhp, p);
			                break;
			              }
			
			              if (counter == 3) {
			                NODEd * p = taoNODEd(InputD(lsv, lhp, ld));
			                themNODEdvaodau(ld, p);
			                break;
			              }
			
			              key = getch();
			              if (key == '\r')
			                system("cls");
			            }
			
			            Set[0] = 7;
			            Set[1] = 7;
			            Set[2] = 7;
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			
			            if (counter == 2) {
			              Set[1] = 74;
			            }
			
			            if (counter == 3) {
			              Set[2] = 74;
			            }
			          }
			
			          gotoxy(45, 20);
			          color(78);
			          printf("Ban co muon tiep tuc NHAP DU LIEU khong");
			
			          int Set2[] = {
			            7,
			            7
			          }; // default colors
			          int counter2 = 1;
			          char key2;
			          while (1) {
			            if (counter2 == 1) {
			              Set2[0] = 74;
			            }
			            gotoxy(45, 22);
			            color(Set2[0]);
			            printf(" 1.CO  ");
			            gotoxy(52, 22);
			            color(Set2[1]);
			            printf(" 2.BACK TO MENU ");
			            key2 = getch();
			            if (key2 == 75 && (counter2 == 2)) {
			              counter2--;
			
			            } else if (key2 == 77 && (counter2 == 1)) {
			              counter2++;
			
			            } else if (key2 == 75 && (counter2 <= 1)) {
			              counter2 = 2;
			            } else if (key2 == 77 && (counter2 >= 2)) {
			              counter2 = 1;
			            }
			
			            if (key2 == '\r') {
			              if (counter2 == 2) {
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter2 == 1) {
			                system("cls");
			                break;
			              }
			              if (counter2 == 2) {
			                goto MENUPOP;
			              }
			              key2 = getch();
			              if (key2 == '\r')
			                system("cls");
			            }
			
			            Set2[0] = 7;
			            Set2[1] = 7;
			            if (counter2 == 1) {
			              Set2[0] = 74;
			            }
			
			            if (counter2 == 2) {
			              Set2[1] = 74;
			            }
			          }
			
			        }
			      }
			
			      /*-----------------------------------------SUA DU LIEU------------------------------ */
			      if (counter == 3) {
			        while (1) {
			          int Set[] = {
			            7,
			            7,
			            7
			          }; // default colors
			          int counter = 1, i = 0;
			          char key;
			          while (1) {
			          	    gotoxy(8,2);
			    			color(26);
			   				 printf("SUA DU LIEU:");         	
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			            gotoxy(8, 4);
			            color(Set[0]);
			            printf(" 1.SINH VIEN ");
			            gotoxy(8, 6);
			            color(Set[1]);
			            printf(" 2.HOC PHAN ");
			            gotoxy(8, 8);
			            color(Set[2]);
			            printf(" 3.DIEM SO ");
			            key = getch();
			            if (key == 72 && (counter >= 2 && counter <= 3)) {
			              counter--;
			
			            } else if (key == 80 && (counter >= 1 && counter <= 2)) {
			              counter++;
			
			            } else if (key == 72 && (counter <= 1)) {
			              counter = 3;
			            } else if (key == 80 && (counter >= 3)) {
			              counter = 1;
			            }
			
			            if (key == '\r') {
			              if (counter == 3) {
			                gotoxy(0, 17);
			                color(7);
			              }
			
			              system("cls");
			              gotoxy(0, 5);
			              if (counter == 1) {
			                SuaSV(lsv);
			
			                break;
			              }
			
			              if (counter == 2) {
			                SuaHP(lhp);
			                break;
			              }
			
			              if (counter == 3) {
			                SuaD(lsv,lhp,ld);
			                break;
			              }
			
			              key = getch();
			              if (key == '\r')
			                system("cls");
			            }
			
			            Set[0] = 7;
			            Set[1] = 7;
			            Set[2] = 7;
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			
			            if (counter == 2) {
			              Set[1] = 74;
			            }
			
			            if (counter == 3) {
			              Set[2] = 74;
			            }
			          }
			
			          gotoxy(45, 20);
			          color(78);
			          printf("Ban co muon tiep tuc SUA DU LIEU khong");
			
			          int Set3[] = {
			            7,
			            7
			          }; // default colors
			          int counter3 = 1;
			          char key3;
			          while (1) {
			            if (counter3 == 1) {
			              Set3[0] = 74;
			            }
			            gotoxy(45, 22);
			            color(Set3[0]);
			            printf(" 1.CO  ");
			            gotoxy(52, 22);
			            color(Set3[1]);
			            printf(" 2.BACK TO MENU ");
			            key3 = getch();
			            if (key3 == 75 && (counter3 == 2)) {
			              counter3--;
			
			            } else if (key3 == 77 && (counter3 == 1)) {
			              counter3++;
			
			            } else if (key3 == 75 && (counter3 <= 1)) {
			              counter3 = 2;
			            } else if (key3 == 77 && (counter3 >= 2)) {
			              counter3 = 1;
			            }
			
			            if (key3 == '\r') {
			              if (counter3 == 2) {
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter3 == 1) {
			                system("cls");
			                break;
			              }
			              if (counter3 == 2) {
			                goto MENUPOP;
			              }
			              key3 = getch();
			              if (key3 == '\r')
			                system("cls");
			            }
			
			            Set3[0] = 7;
			            Set3[1] = 7;
			            if (counter3 == 1) {
			              Set3[0] = 74;
			            }
			
			            if (counter3 == 2) {
			              Set3[1] = 74;
			            }
			          }
			
			        }
			      }
			
			      /*-----------------------------------------XOA DU LIEU------------------------------ */
			      if (counter == 4) {
			        while (1) {
			          int Set[] = {
			            7,
			            7,
			            7
			          }; // default colors
			          int counter = 1, i = 0;
			          char key;
			          while (1) {
			          	    gotoxy(8,2);
			    			color(26);
			   				 printf("XOA DU LIEU:");
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			
			            gotoxy(8, 4);
			            color(Set[0]);
			            printf(" 1.SINH VIEN ");
			            gotoxy(8, 6);
			            color(Set[1]);
			            printf(" 2.HOC PHAN ");
			            gotoxy(8, 8);
			            color(Set[2]);
			            printf(" 3.DIEM SO ");
			            key = getch();
			            if (key == 72 && (counter >= 2 && counter <= 3)) {
			              counter--;
			
			            } else if (key == 80 && (counter >= 1 && counter <= 2)) {
			              counter++;
			
			            } else if (key == 72 && (counter <= 1)) {
			              counter = 3;
			            } else if (key == 80 && (counter >= 3)) {
			              counter = 1;
			            }
			            if (key == '\r') {
			              if (counter == 3) {
			                gotoxy(0, 17);
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter == 1) {
			                XoaNODEsv(lsv, ld);
			                break;
			              }
			
			              if (counter == 2) {
			                XoaNODEhp(lhp, ld);
			                break;
			              }
			
			              if (counter == 3) {
			                XoaNODEd(lsv,lhp,ld);
			                break;
			              }
			
			              key = getch();
			              if (key == '\r')
			                system("cls");
			            }
			
			            Set[0] = 7;
			            Set[1] = 7;
			            Set[2] = 7;
			            if (counter == 1) {
			              Set[0] = 74;
			            }
			
			            if (counter == 2) {
			              Set[1] = 74;
			            }
			
			            if (counter == 3) {
			              Set[2] = 74;
			            }
			          }
			          gotoxy(45, 20);
			          color(78);
			          printf("Ban co muon tiep tuc XOA DU LIEU khong");
			
			          int Set5[] = {
			            7,
			            7
			          }; // default colors
			          int counter5 = 1;
			          char key5;
			          while (1) {
			            if (counter5 == 1) {
			              Set5[0] = 74;
			            }
			            gotoxy(45, 22);
			            color(Set5[0]);
			            printf(" 1.CO  ");
			            gotoxy(52, 22);
			            color(Set5[1]);
			            printf(" 2.BACK TO MENU ");
			            key5 = getch();
			            if (key5 == 75 && (counter5 == 2)) {
			              counter5--;
			
			            } else if (key5 == 77 && (counter5 == 1)) {
			              counter5++;
			
			            } else if (key5 == 75 && (counter5 <= 1)) {
			              counter5 = 2;
			            } else if (key5 == 77 && (counter5 >= 2)) {
			              counter5 = 1;
			            }
			
			            if (key5 == '\r') {
			              if (counter5 == 2) {
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter5 == 1) {
			                system("cls");
			                break;
			              }
			              if (counter5 == 2) {
			                goto MENUPOP;
			              }
			              key5 = getch();
			              if (key5 == '\r')
			                system("cls");
			            }
			
			            Set5[0] = 7;
			            Set5[1] = 7;
			            if (counter5 == 1) {
			              Set5[0] = 74;
			            }
			
			            if (counter5 == 2) {
			              Set5[1] = 74;
			            }
			          }
			
			        }
			      }
			      if (counter == 5) {
			        while (1) {
			          int Set[] = {
			            7,
			            7,
			            7,
			            7
			          }; // default colors
			          int counter = 1, i = 0;
			          char key;
			          while (1) {
			          	    gotoxy(8,2);
			    			color(26);
			   				 printf("TRUY VAN DU LIEU CUA SINH VIEN:");
			            if (counter == 1) {
			              Set[0] = 20;
			            }
			
			            gotoxy(2, 3);
			            color(Set[0]);
			            printf(" 1. Diem trung binh tich luy cua tat ca sinh vien ");
			
			            gotoxy(2, 4);
			            color(Set[1]);
			            printf(" 2. Danh sach sinh vien khong dat hoc phan ");
			
			            gotoxy(2, 5);
			            color(Set[2]);
			            printf(" 3. Danh sach hoc phan chua dat cua sinh vien ");
			
			            gotoxy(2, 6);
			            color(Set[3]);
			            printf(" 4. Diem trung binh tich luy cua 1 sinh vien");
			            gotoxy(2, 10);
			            key = getch();
			            if (key == 72 && (counter >= 2 && counter <= 4)) {
			              counter--;
			
			            } else if (key == 80 && (counter >= 1 && counter <= 3)) {
			              counter++;
			
			            } else if (key == 72 && (counter <= 1)) {
			              counter = 4;
			            } else if (key == 80 && (counter >= 4)) {
			              counter = 1;
			            }
			
			            if (key == '\r') {
			              if (counter == 4) {
			                gotoxy(0, 17);
			                color(7);
			              }
			
			              system("cls");
			              gotoxy(0, 4);
			              if (counter == 1) {
			                Tinhtrungbinhtichluy(lsv, lhp, ld);
			                break;
			
			              }
			
			              if (counter == 2) {
			                Danhsachsvchuadathp(lsv, lhp, ld);
			                break;
			              }
			
			              if (counter == 3) {
			                Danhsachhpchuadatcuasv(lsv, lhp, ld);
			                break;
			              }
			
			              if (counter == 4) {
			                Trungbinhtichluysv(lsv, lhp, ld);
			                break;
			              }
			
			              key = getch();
			              if (key == '\r')
			                system("cls");
			            }
			
			            Set[0] = 7;
			            Set[1] = 7;
			            Set[2] = 7;
			            Set[3] = 7;
			            if (counter == 1) {
			              Set[0] = 20;
			            }
			
			            if (counter == 2) {
			              Set[1] = 20;
			            }
			
			            if (counter == 3) {
			              Set[2] = 20;
			            }
			
			            if (counter == 4) {
			              Set[3] = 20;
			            }
			          }
			          gotoxy(45, 20);
			          color(78);
			          printf("Ban co muon tiep tuc TRUY VAN DU LIEU cua sinh vien khong");
			
			          int Set5[] = {
			            7,
			            7
			          }; // default colors
			          int counter5 = 1;
			          char key5;
			          while (1) {
			            if (counter5 == 1) {
			              Set5[0] = 74;
			            }
			            gotoxy(45, 22);
			            color(Set5[0]);
			            printf(" 1.CO  ");
			            gotoxy(52, 22);
			            color(Set5[1]);
			            printf(" 2.BACK TO MENU ");
			            key5 = getch();
			            if (key5 == 75 && (counter5 == 2)) {
			              counter5--;
			
			            } else if (key5 == 77 && (counter5 == 1)) {
			              counter5++;
			
			            } else if (key5 == 75 && (counter5 <= 1)) {
			              counter5 = 2;
			            } else if (key5 == 77 && (counter5 >= 2)) {
			              counter5 = 1;
			            }
			
			            if (key5 == '\r') {
			              if (counter5 == 2) {
			                color(7);
			              }
			              system("cls");
			              gotoxy(0, 5);
			              if (counter5 == 1) {
			                system("cls");
			                break;
			              }
			              if (counter5 == 2) {
			                goto MENUPOP;
			              }
			              key5 = getch();
			              if (key5 == '\r')
			                system("cls");
			            }
			
			            Set5[0] = 7;
			            Set5[1] = 7;
			            if (counter5 == 1) {
			              Set5[0] = 74;
			            }
			
			            if (counter5 == 2) {
			              Set5[1] = 74;
			            }
			          }
			
			        }
			      }
			    }
			
			    Set[0] = 7;
			    Set[1] = 7;
			    Set[2] = 7;
			    Set[3] = 7;
			    Set[4] = 7;
			    Set[5] = 7;
			    if (counter == 1) {
			      Set[0] = 20;
			    }
			
			    if (counter == 2) {
			      Set[1] = 20;
			    }
			
			    if (counter == 3) {
			      Set[2] = 20;
			    }
			
			    if (counter == 4) {
			      Set[3] = 20;
			    }
			
			    if (counter == 5) {
			      Set[4] = 20;
			    }
			
			    if (counter == 6) {
			      Set[5] = 20;
			    }
			      GhiLISHsvvaofilebin(lsv);
			      GhiLISHhpvaofilebin(lhp);
			      GhiLISHdvaofilebin(ld);
			      Ghitrungbinhtichluyvaofilebin(lsv, lhp, ld);
			}
		}
