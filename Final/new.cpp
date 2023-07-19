#include <conio.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>

int NUM, count_;
const double h = 1e-9;
const int MAX_LOOP = 10000;
double left = -1000.5, right = 999.5;
double a, b, x, x_old, fa, fb, fx, eps, m, M;

FILE *fin;
FILE *fout;

typedef struct element_of_The_Polynomial
{
    int degree;
    double coefficient;
} NODE; // Phan tu cua da thuc

typedef struct intervals_Containing_The_Solution
{
    double a;
    double b;
} ICS; // Khoang phan ly

//---------------MANG LUU HAM SO-----------------
NODE polynom[15];

//---------------KHOANG PHAN LY------------------
ICS phanly[15];

void color(int color);
void gotoxy(int x, int y);


//Cac am tinh gia tri f(x), f'(x), f''(x)
double f(double x);
double f1(double x);

//Ham kiem tra dau cua ham so
int check_sign(double x, int choose);

// ham ve khung menu
void drawframe();
// ham xu ly input
void menu_input();
// ham hien thi bieu thuc
void display_Function();
//ham in cac khoang phan ly
int printICS();


//Cac ham tinh sai so
double sai_so_1();
double sai_so_2();

//Nhom ham tim MIN MAX ham so
double minf(double f(double x), ICS local);
double maxf(double f(double x), ICS local);

//Tim khoang phan ly
void find_ICS(double temp_left, double temp_right);
//Chia doi khoang phan ly
int bisection_Method();
//Ham tim nghiem voi so lan lap cho truoc
void secant_Method_n(ICS local);
//Ham tim nghiem voi sai so cho truoc
void secant_Method_epsi(ICS local);
//Ham tim nghiem sai so |x_n - x_{n-1}| < eps
void secant_Method_e(ICS local);

int main()
{
    int hold, cnt;
    ICS local; //khoang phan ly
    // Biến sử dụng trong layer menu 1
    int Set[] = {7, 7, 7, 7, 7, 7};
    int counter = 1;
    char key;
    // Biến sử dụng trong layer menu 2
    int Set1[] = {7, 7, 7};
    int counter1 = 1;
    char key1;

    if ((fout = fopen("output.txt", "w")) == NULL)
    {
        printf("Open file output ERROR");
    }
    else
    {
        menu_input();
        while (1)
        {
            drawframe();
            if (counter == 1)
            {
                Set[0] = 74;
            }

            gotoxy(40, 6);
            color(Set[0]);
            printf(" 1. TIM KHOANG PHAN LY NGHIEM ");

            gotoxy(40, 8);
            color(Set[1]);
            printf(" 2. RUT GON KHOANG PHAN LY NGHIEM ");

            gotoxy(40, 10);
            color(Set[2]);
            printf(" 3. PHUONG PHAP DAY CUNG VOI \"N\" LAN LAP ");

            gotoxy(40, 12);
            color(Set[3]);
            printf(" 4. PHUONG PHAP DAY CUNG VOI SAI SO \"e\" ");

            gotoxy(40, 14);
            color(Set[4]);
            printf(" 5. PHUONG PHAP DAY CUNG T/M |X{n} - X{n-1}| <= e ");

            gotoxy(40, 16);
            color(Set[5]);
            printf(" 6. THOAT CHUONG TRINH ");

            key = getch();
            printf("%d", key);
            if (key == 72 && (counter >= 2 && counter <= 6))
            {
                printf("%d", counter);
                counter--;
            }
            else if (key == 80 && (counter >= 1 && counter <= 5))
            {
                counter++;
                printf("%d", counter);
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
            { // carriage return = enter key
                if (counter == 6)
                {
                    color(7);
                    system("cls");
                    break;
                }
                system("cls");
                gotoxy(0, 5);
                if (counter == 1)
                {
                    find_ICS(left, right);
                    printf("\nKhoang phan ly:  ");
                    fprintf(fout, "\nKhoang phan ly:  ");
                    printf("\n\t\t\t+--------|-----------|-----------+");
                    printf("\n\t\t\t|   STT  |     a     |     b     |");
                    printf("\n\t\t\t+--------|-----------|-----------+");
                    fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    fprintf(fout, "\n\t\t\t|   STT  |     a     |     b     |");
                    fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    for(cnt = 0; cnt < count_; cnt++)
                    {
                        if(phanly[cnt].a < 0 && phanly[cnt].b < 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else if(phanly[cnt].a > 0 && phanly[cnt].b < 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else if(phanly[cnt].a < 0 && phanly[cnt].b > 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        printf("\n\t\t\t+--------|-----------|-----------+");
                        fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    }
                }

                else if (counter == 2)
                {
                    bisection_Method();
                    printf("\nKhoang phan ly sau khi thu hep:   ");
                    fprintf(fout, "Khoang phan ly sau khi thu hep:  ");
                    printf("\n\t\t\t+--------|-----------|-----------+");
                    printf("\n\t\t\t|   STT  |     a     |     b     |");
                    printf("\n\t\t\t+--------|-----------|-----------+");
                    fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    fprintf(fout, "\n\t\t\t|   STT  |     a     |     b     |");
                    fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    for(cnt = 0; cnt < count_; cnt++)
                    {
                        if(phanly[cnt].a < 0 && phanly[cnt].b < 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else if(phanly[cnt].a > 0 && phanly[cnt].b < 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else if(phanly[cnt].a < 0 && phanly[cnt].b > 0)
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        else
                        {
                            printf("\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                            fprintf(fout, "\n\t\t\t|   %d   |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
                        }
                        printf("\n\t\t\t+--------|-----------|-----------+");
                        fprintf(fout, "\n\t\t\t+--------|-----------|-----------+");
                    }
                }
                else if (counter == 3)
                {
                    // Set[2] = 74;
                    printf("\nChuong trinh 3");
                    fprintf(fout, "\nChuong trinh 3");
                }
                else if (counter == 4)
                {
                    // Set[3] = 74;
                    printf("\nChuong trinh 4");
                    fprintf(fout, "\nChuong trinh 4");
                }
                else if (counter == 5)
                {
                    // Set[4] = 74;
                    printf("\nChuong trinh 5");
                    fprintf(fout, "\nChuong trinh 5");
                }
                key = getch();
                if (key == '\r')
                {
                    system("cls");
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;
            Set[4] = 7;
            Set[5] = 7;
            if (counter == 1)
            {
                Set[0] = 74;
            }
            if (counter == 2)
            {
                Set[1] = 74;
            }
            if (counter == 3)
            {
                Set[2] = 74;
            }
            if (counter == 4)
            {
                Set[3] = 74;
            }
            if (counter == 5)
            {
                Set[4] = 74;
            }
            if (counter == 6)
            {
                Set[5] = 74;
            }
        }

        fclose(fout);
        return 1;
    }
}









// Nhom ham setup menu
// Ve mau
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// Nhay toa do
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// Ve khung
void drawframe()
{
    int i;
    gotoxy(60, 3);
    color(12);
    printf("MENU");
    color(4);
    for (i = 0; i < 63; i++)
    {
        gotoxy(31 + i, 2);
        printf("**");
        gotoxy(31 + i, 4);
        printf("**");
        gotoxy(31 + i, 19);
        printf("**");
    }
    for (i = 0; i <= 15; i++)
    {
        gotoxy(30, 2);
        gotoxy(30, 3 + i);
        printf("*");
        gotoxy(94, 3 + i);
        printf("*");
    }
    color(7);
}

void menu_input()
{
    int Set[] = {7, 7, 7, 7, 7};
    int counter = 1, i = 0;
    char key;
    while (1)
    {
        drawframe();
        if (counter == 1)
        {
            Set[0] = 74;
        }

        gotoxy(40, 6);
        color(Set[0]);
        printf("1. NHAP HAM SO TU FILE   ");
        gotoxy(40, 8);
        color(Set[1]);
        printf("2. NHAP HAM SO TU TERMINAL   ");
        gotoxy(40, 10);
        color(Set[2]);
        printf("3. THOAT NHAP LIEU  ");

        key = getch();
        printf("%d", key);
        if (key == 72 && (counter >= 2 && counter <= 3))
        {
            counter--;
        }
        else if (key == 80 && (counter >= 1 && counter <= 2))
        {
            counter++;
            printf("%d", counter);
        }
        else if (key == 72 && (counter <= 1))
        {
            counter = 3;
        }
        else if (key == 80 && (counter >= 3))
        {
            counter = 1;
        }

        if (key == '\r')
        {
            if (counter == 3)
            {
                color(7);
                system("cls");
                break;
            }
            system("cls");
            gotoxy(0, 5);
            if (counter == 1)
            {
                if ((fin = fopen("input.txt", "r")) == NULL)
                {
                    printf("Open file ERROR");
                }
                else
                {
                    while (!feof(fin))
                    {
                        fscanf(fin, "%d", &polynom[i].degree);
                        fscanf(fin, "%lf", &polynom[i].coefficient);

                        if (feof(fin))
                        break;
                        else
                        {
                            i++;
                        }
                    }
                NUM = i;
                fclose(fin);
                }
                display_Function();
            }

            if (counter == 2)
            {
                do
                {
                    printf("So cac so hang cua da thuc (The numbers of elements of the Polymial): ");
                    scanf("%d", &NUM);
                    if (NUM <= 1) printf("\nBan da nhap sai. Vui long nhap lai voi n > 1!!!");
                } while (NUM < 0);
            
            for (i = 0; i < NUM; i++)
            {
                printf("So hang thu %d la: \n", i + 1);
                printf("Bac: \n");
                scanf("%d", &polynom[i].degree);
                printf("He so: \n");
                scanf("%lf", &polynom[i].coefficient);
            }
            display_Function();
        }

            key = getch();

            if (key == '\r') 
            {
                system("cls");
            }
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        if (counter == 1)
        {
            Set[0] = 74;
        }
        if (counter == 2)
        {
            Set[1] = 74;
        }
        if (counter == 3)
        {
            Set[2] = 74;
        }
    }
}
// kkkkkkkkkkkk

void display_Function(){
    int i;
    printf("Bieu thuc: \n");
    fprintf(fout, "Bieu thuc: \n");
    for(i = 0; i < NUM; i++)
    {
        if(polynom[i].degree == 0)
        {
            printf(" %f ", polynom[i].coefficient);
            fprintf(fout, " %f ", polynom[i].coefficient);
        }
        else
        {
            printf(" %fx^%d ", polynom[i].coefficient, polynom[i].degree);
            fprintf(fout, " %fx^%d ", polynom[i].coefficient, polynom[i].degree);
        }
        if(i < NUM-1)
        {
            printf("+");
            fprintf(fout, "+");
        }
    }
}


//Nhom ham tinh gia tri f(x), f'(x)
double f(double x)
{
    int i;
    double SUM = 0;
    for(i = 0; i < NUM; i++)
    {
        SUM += polynom[i].coefficient * pow(x, polynom[i].degree);
    }
    return SUM;
}

double f1(double x)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

//Ham check dau cua ham so
int check_sign(double x, int choose)
{
    int sign = 1;
    if(choose == 0)
    {
        if(f(x) < 0)
        {
            sign = -1;
        }
        else if(choose == 1)
        if(f1(x) < 0)
        {
            sign = -1;
        }
    }
    return sign;
}



//Nhom ham chinh cua de bai
void find_ICS(double temp_left, double temp_right)         //Ham tim khoang phan ly
{
    double check = 0, temp;
    int i, dem;
    float delta = 0.701;
    count_ = 0;
    while(temp_left <= temp_right)
    {
        x_old = check_sign(temp_left, 0);
        x = check_sign(temp_left + delta, 0);
        check = x*x_old;
        if(check < 0)
        {
            temp = temp_left;
            dem = 0;
            for(i = 0; i < 1001; i++)
            {
                if(check_sign(temp, 1) != check_sign(temp + delta/1001, 1))
                {
                    dem++;
                }
                temp = temp + delta/1001;
            }
            if(dem == 0)
            {
                phanly[count_].a = temp_left;
                phanly[count_].b = temp_left + delta;
                count_++;
            }
            else
            {
                printf("\n\nTrong khoang (%.2lf, %.2lf) co it nhat %d nghiem. Moi khao sat ham so", temp_left, temp_left + delta, dem);
                fprintf(fout, "\n\nTrong khoang (%.2lf, %.2lf) co it nhat %d nghiem. Moi khao sat ham so", temp_left, temp_left + delta, dem);

            }
        }
        temp_left = temp_left + delta;
    }
}

int bisection_Method()
{
    float m;
    double p, q, c, f_p, f_c;
    int i = 0, check_sign_fp, check_sign_fc;
    printf("\n\nVoi khoang phan ly nghiem (p,q) voi |p-q| <= m. Nhap vao so m:  ");
    fprintf(fout, ("\n\nVoi khoang phan ly nghiem (p,q) voi |p-q| <= m. Nhap vao so m:  "));
    scanf("%f", &m);
    fprintf(fout, "\nm = %f", m);
    while (i < count_)
    {
        p = phanly[i].a;
        q = phanly[i].b;

        f_p = f(p);
        check_sign_fp = check_sign(p, 0);

        while(fabs(q-p) > m)
        {
            c = (p + q) / 2.0;
            f_c = f(c);
            check_sign_fc = check_sign(c, 0);
            if(check_sign_fp != check_sign_fc)
            {
                q = c;
            }
            else 
            {
                p = c;
            }
        }
        phanly[i].a = p;
        phanly[i].b = q;
        i++;
    }
}