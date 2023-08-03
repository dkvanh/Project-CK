#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

int NUM, count_ ;
const double h = 1e-9;
const int MAX_LOOP = 10000;
double left = -1000.5, right = 999.5;
double a, b, x, x_old, fa, fb, fx, eps, m, M;
FILE *fin;
FILE *fout;

typedef struct element_Of_The_Polynomial
{
    int degree;
    double coefficient;
} NODE;

typedef struct intervals_Containing_The_Solution
{
    double a;
    double b;
} ICS;

//----------------MANG LUU HAM SO----------------
NODE polynom[15];

//----------------KHOANG PHAN LY-----------------
ICS phanly[15];

//----------------KHAI BAO HAM-------------------
void color(int color);
void gotoxy(int x, int y);

//Cac ham tinh gia tri f(x), f’(x), f’’(x)
double f(double x);
double f1(double x);
double f2(double x);

//Ham kiem tra dau cua ham so
int check_sign(double x, int choose);

// ham ve khung menu
void drawframe();
//ham xu ly input
void menu_input();
//ham in bieu thuc
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



int main(){

    int hold, cnt;
    ICS local;
    //bien sd trong layer menu 1
    int Set[] = {7, 7, 7, 7, 7, 7};
    int counter = 1;
    char key;
    //bien sd trong layer menu 2
    int Set1[] = {7, 7, 7};
    int counter1 = 1;
    char key1;

    if (( fout = fopen( "output.txt", "w" )) == NULL ){
        printf("Open file output error");
    }
    else
    {
    menu_input();
    while(1){
    drawframe();
    if(counter == 1){
    Set[0] = 74;
    }
    gotoxy(40,6);
    color(Set[0]);
    printf(" 1. TIM KHOANG PHAN LY NGHIEM ");
    
    gotoxy(40,8);
    color(Set[1]);
    printf(" 2. RUT GON KHOANG PHAN LY NGHIEM ");
    
    gotoxy(40,10);
    color(Set[2]);
    printf(" 3. PHUONG PHAP DAY CUNG VOI \"N\" LAN LAP");
    
    gotoxy(40,12);
    color(Set[3]);
    printf(" 4. PHUONG PHAP DAY CUNG VOI SAI SO \"e\"");
    
    gotoxy(40,14);
    color(Set[4]);
    printf(" 5. PHUONG PHAP DAY CUNG T/M |X{n} - X{n-1}| <= e");
    
    gotoxy(40,16);
    color(Set[5]);
    printf(" 6. THOAT CHUONG TRINH");

    key = getch();
    if(key == 72 && (counter >= 2 && counter <=6)){
    counter--;

    }
    else if(key == 80 && (counter >= 1 && counter <=5)){
    counter++;

    }
    else if(key == 72 && (counter <=1)){
    counter = 6;
    }
    else if(key == 80 && (counter >= 6)){
    counter = 1;
    }
    if(key == '\r'){//enter
    if(counter == 6){
    color(7);
    system("cls");
    break;
    }
    system("cls");
    gotoxy(0,5);
    if(counter == 1){
    find_ICS(left, right);
    printf("\nKhoang phan ly: ");
    fprintf(fout, "\nKhoang phan ly: ");
    printf("\n\t\t\t+---------|-----------|-----------+");
    printf("\n\t\t\t|   STT   |     a     |     b     |");
    printf("\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t|   STT   |     a     |     b     |");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    for(cnt = 0; cnt < count_; cnt++)
    {
    if(phanly[cnt].a < 0 && phanly[cnt].b < 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else if(phanly[cnt].a > 0 && phanly[cnt].b < 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else if(phanly[cnt].a < 0 && phanly[cnt].b > 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else
    {
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    printf("\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    }
    }
    
    
    else if(counter == 2)
    {
    bisection_Method();
    printf("\nKhoang phan ly sau khi thu hep: ");
    fprintf(fout, "\nKhoang phan ly sau khi thu hep: ");
    printf("\n\t\t\t+---------|-----------|-----------+");
    printf("\n\t\t\t|   STT   |     a     |     b     |");
    printf("\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t|   STT   |     a     |     b     |");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    for(cnt = 0; cnt < count_; cnt++)
    {
    if(phanly[cnt].a < 0 && phanly[cnt].b < 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else if(phanly[cnt].a > 0 && phanly[cnt].b < 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else if(phanly[cnt].a < 0 && phanly[cnt].b > 0){
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    else
    {
    printf("\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    fprintf(fout, "\n\t\t\t|    %d    |   %.3lf   |   %.3lf   |", cnt, phanly[cnt].a, phanly[cnt].b);
    }
    printf("\n\t\t\t+---------|-----------|-----------+");
    fprintf(fout, "\n\t\t\t+---------|-----------|-----------+");
    }
    }



    else if(counter == 3)
    {
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    counter1 = 1;
    while(1){
    drawframe();
    if(counter1 == 1){
    Set1[0] = 74;
    }
    gotoxy(40,6);
    color(Set1[0]);
    printf(" 1. Khoang phan ly nhap vao tu ban phim ");
    gotoxy(40,8);
    color(Set1[1]);
    printf(" 2. Khoang phan ly da tim duoc o truoc");
    gotoxy(40,10);
    color(Set1[2]);
    printf(" 3. THOAT");

    key1 = getch();
    if(key1 == 72 && (counter1 >= 2 && counter1 <=3)){
    counter1--; 

    }
    else if(key1 == 80 && (counter1 >= 1 && counter1 <=2)){
    counter1++;

    }
    else if(key1 == 72 && (counter1 <= 1)){
    counter1 = 3;
    }
    else if(key1 == 80 && (counter1 >= 3)){ 
    counter1 = 1;
    }
    if(key1 == '\r'){
    if(counter1 == 3){
    color(7);
    system("cls");
    break;
    }
    system("cls");
    gotoxy(0,5);
    if(counter1 == 1){
    printf("Nhap khoang phan ly (a, b): ");
    printf("\na = "); scanf("%lf", &local.a);
    printf("b = "); scanf("%lf", &local.b);
    secant_Method_n(local);
    break;
    }
    if(counter1 == 2){
    hold = printICS();
    local.a = phanly[hold - 1].a;
    local.b = phanly[hold - 1].b;
    secant_Method_n(local);
    break;
    }
    key1 = getch();
    if(key1 == '\r')
    system("cls");
    }
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    if(counter1 == 1){
    Set1[0] = 74;
    }   
    if(counter1 == 2){
    Set1[1] = 74;
    }
    if(counter1 == 3){
    Set1[2] = 74;
    }
    }
    }

    else if(counter == 4)
    {
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    counter1 = 1;
    while(1){
    drawframe();
    if(counter1 == 1){
    Set1[0] = 74;
    }
    gotoxy(40,6);
    color(Set1[0]);
    printf(" 1. Khoang phan ly nhap vao tu ban phim ");
    gotoxy(40,8);
    color(Set1[1]);
    printf(" 2. Khoang phan ly da tim duoc o truoc");
    gotoxy(40,10);
    color(Set1[2]);
    printf(" 3. THOAT");

    key1 = getch();
    if(key1 == 72 && (counter1 >= 2 && counter1 <=3)){
    counter1--;

    }
    else if(key1 == 80 && (counter1 >= 1 && counter1 <=2)){
    counter1++;

    }
    else if(key1 == 72 && (counter1 <=1)){
    counter1 = 3;
    }
    else if(key1 == 80 && (counter1 >= 3)){
    counter1 = 1;
    }
    if(key1 == '\r'){
    if(counter1 == 3){
    color(7);
    system("cls");
    break;
    }
    system("cls");
    gotoxy(0,5);
    if(counter1 == 1){
    printf("Nhap khoang phan ly (a, b): ");
    printf("\na = "); scanf("%lf", &local.a);
    printf("b = "); scanf("%lf", &local.b);
    secant_Method_epsi(local);
    break;
    }
    if(counter1 == 2){
    hold = printICS();  
    local.a = phanly[hold - 1].a;
    local.b = phanly[hold - 1].b;
    secant_Method_epsi(local);
    break;
    }
    key1 = getch();
    if(key1 == '\r')
    system("cls");
    }
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    if(counter1 == 1){
    Set1[0] = 74;
    }
    if(counter1 == 2){
    Set1[1] = 74;
    }
    if(counter1 == 3){
    Set1[2] = 74;
    }
    }
    }

    else if(counter == 5)
    {
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    counter1 = 1;
    while(1){
    drawframe();
    if(counter1 == 1){
    Set1[0] = 74;
    }
    gotoxy(40,6);
    color(Set1[0]);
    printf(" 1. Khoang phan ly nhap vao tu ban phim ");
    gotoxy(40,8);
    color(Set1[1]);
    printf(" 2. Khoang phan ly da tim duoc o truoc");
    gotoxy(40,10);
    color(Set1[2]);
    printf(" 3. THOAT");

    key1 = getch();
    if(key1 == 72 && (counter1 >= 2 && counter1 <=3)){
    counter1--;

    }
    else if(key1 == 80 && (counter1 >= 1 && counter1 <=2)){
    counter1++;

    }
    else if(key1 == 72 && (counter1 <=1)){
    counter1 = 3;
    }
    else if(key1 == 80 && (counter1 >= 3)){
    counter1 = 1;
    }
    if(key1 == '\r'){
    if(counter1 == 3){
    color(7);
    system("cls");
    break;
    }
    system("cls");
    gotoxy(0,5);
    if(counter1 == 1){
    printf("Nhap khoang phan ly (a, b): ");
    printf("\na = "); scanf("%lf", &local.a);
    printf("b = "); scanf("%lf", &local.b);
    secant_Method_e(local);
    break;
    }
    if(counter1 == 2){
    hold = printICS();
    local.a = phanly[hold - 1].a;
    local.b = phanly[hold - 1].b;
    secant_Method_e(local);
    break;
    }
    key1 = getch();
    if(key1 == '\r')
    system("cls");
    }
    Set1[0] = 7;
    Set1[1] = 7;
    Set1[2] = 7;
    if(counter1 == 1){
    Set1[0] = 74;
    }
    if(counter1 == 2){
    Set1[1] = 74;
    }
    if(counter1 == 3){
    Set1[2] = 74;
    }
    }
    }

    key = getch();
    if(key == '\r')
    system("cls");
    }
    Set[0] = 7;
    Set[1] = 7;
    Set[2] = 7;
    Set[3] = 7;
    Set[4] = 7;
    Set[5] = 7;
    if(counter == 1){
    Set[0] = 74;
    }
    if(counter == 2){
    Set[1] = 74;
    }
    if(counter == 3){
    Set[2] = 74;
    }
    if(counter == 4){
    Set[3] = 74;
    }
    if(counter == 5){
    Set[4] = 74;
    }
    if(counter == 6){
    Set[5] = 74;
    }
    }
    }

    fclose(fout);
    return 1;

    }


//Nhom ham setup mau sac
void color(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawframe() {
    int i;
    gotoxy(60, 3);
    color(12);
    printf("MENU");
    color(4);
    for (i = 0; i < 63; i++) {
        gotoxy(31 + i, 2);
        putchar(205);
        printf("%c", 205);
        gotoxy(31 + i, 4);
        putchar(205);
        printf("%c", 205);
        gotoxy(31 + i, 19);
        putchar(205);
        printf("%c", 205);
    }
    for (i = 0; i <= 15; i++) {
        gotoxy(30, 2);
        gotoxy(29, 3 + i);
        putchar(186);
        printf("%c", 186);
        gotoxy(95, 3 + i);
        putchar(186);
        printf("%c", 186);
    }
    color(7);
}

//Nhom ham nhan INPUT du lieu
void menu_input() {
    int Set[] = {7, 7, 7, 7, 7};
    int counter = 1, i = 0;
    char key;

    while (1) {
        drawframe();
        if (counter == 1) {
            Set[0] = 74;
        }
        gotoxy(40, 6);
        color(Set[0]);
        printf(" 1. NHAP HAM SO TU FILE ");
        gotoxy(40, 8);
        color(Set[1]);
        printf(" 2. NHAP HAM SO TU TERMINAL ");
        gotoxy(40, 10);
        color(Set[2]);
        printf(" 3. THOAT NHAP LIEU ");

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
                color(7);
                system("cls");
                break;
            }

            system("cls");
            gotoxy(0, 5);

            if (counter == 1) {
                if ((fin = fopen("input.txt", "r")) == NULL) {
                    printf("open file error");
                } else {
                    while (!feof(fin)) {
                        fscanf(fin, "%d", &polynom[i].degree);
                        fscanf(fin, "%lf", &polynom[i].coefficient);

                        if (feof(fin)) {
                            break;
                        } else {
                            i++;
                        }
                    }

                    NUM = i;
                    fclose(fin);
                }

                display_Function();
            }

            if (counter == 2) {
                do {
                    printf("Cho biet so cac so hang cua da thuc: ");
                    scanf("%d", &NUM);

                    if (NUM <= 1) {
                        printf("\nBan da nhap sai. Vui long nhap lai voi n >1!!!");
                    }
                } while (NUM < 0);

                for (i = 0; i < NUM; i++) {
                    printf("So hang thu %d la: \n", i + 1);
                    printf("Bac: \n");
                    scanf("%d", &polynom[i].degree);
                    printf("He so: \n");
                    scanf("%lf", &polynom[i].coefficient);
                }

                display_Function();
            }

            key = getch();

            if (key == '\r') {
                system("cls");
            }
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
}

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
// Nhom ham tinh gia tri f(x), f’(x)
double f(double x) {
    int i;
    double SUM = 0;

    for (i = 0; i < NUM; i++) {
        SUM += polynom[i].coefficient * pow(x, polynom[i].degree);
    }

    return SUM;
}

double f1(double x) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

// Ham check dau cua ham so
int check_sign(double x, int choose) {
    int sign = 1;

    if (choose == 0) {
        if (f(x) < 0) {
            sign = -1;
        }
    } else if (choose == 1) {
        if (f1(x) < 0) {
            sign = -1;
        }
    }

    return sign;
}
// Nhom ham tim MIN MAX ham so tren doan
double minf(double f(double x), ICS local) {
    double x0, x_min = local.a;
    double delta = (local.b - local.a) / 100000;

    x0 = local.a;

    while (x0 < local.b) {
        if (fabs(f(x0)) < fabs(f(x_min)) && x0 < local.b) {
            x_min = x0;
        }

        x0 += delta;
    }

    if (fabs(f(x_min)) > fabs(f(local.b))) {
        return fabs(f(local.b));
    } else {
        return fabs(f(x_min));
    }
}

double maxf(double f(double x), ICS local) {
    double x0, x_max = local.a;
    double delta = (local.b - local.a) / 100000;

    x0 = local.a;

    while (x0 < local.b) {
        if ((fabs(f(x0)) > fabs(f(x_max))) && (x0 < local.b)) {
            x_max = x0;
        }

        x0 += delta;
    }

    if (fabs(f(x_max)) < fabs(f(local.b))) {
        return fabs(f(local.b));
    } else {
        return fabs(f(x_max));
    }
}

// Nhom ham tinh sai so
double sai_so_1() {
    return fabs(fx) / m;
}

double sai_so_2() {
    return (M - m) / m * fabs(x - x_old);
}
// Ham in khoang phan ly
int printICS() {
    int Set[count_];
    int counter = 1, i = 0;
    char key;

    for (i = 0; i < count_; i++) {
        Set[i] = 7;
    }

    fprintf(fout, "\n\n\t\t\t+-+-+---------------------------------------+-+-+");
    for (i = 0; i < count_; i++) {
        fprintf(fout, "\n\t\t\t| %d. Khoang phan li thu %d: (%.3lf, %.3lf) |", i+1, i+1, phanly[i].a, phanly[i].b);
    }
    fprintf(fout, "\n\t\t\t+-+-+---------------------------------------+-+-+");

    while (1) {
        drawframe();

        if (counter == 1) {
            Set[0] = 74;
        }

        for (i = 0; i < count_; i++) {
            gotoxy(40, 6 + i);
            color(Set[i]);
            printf(" %d. Khoang phan li thu %d: (%.3lf, %.3lf)", i+1, i+1, phanly[i].a, phanly[i].b);
        }

        key = getch();

        if (key == 72 && (counter >= 2 && counter <= count_)) {
            counter--;
        } else if (key == 80 && (counter >= 1 && counter <= count_ - 1)) {
            counter++;
        } else if (key == 72 && (counter <= 1)) {
            counter = count_;
        } else if (key == 80 && (counter >= count_)) {
            counter = 1;
        }

        if (key == '\r') {
            color(7);
            system("cls");
            fprintf(fout, "\nLua chon: %d\n", counter);
            return counter;
        }

        for (i = 0; i < count_; i++) {
            Set[i] = 7;
        }

        Set[counter - 1] = 74;
    }
}



// Nhom ham chinh cua de bai
void find_ICS(double temp_left, double temp_right) { // Ham tim khoang phan ly
    double check = 0, temp;
    int i, dem;
    float delta = 0.701;
    count_ = 0;

    while (temp_left <= temp_right) {
        x_old = check_sign(temp_left, 0);
        x = check_sign(temp_left + delta, 0);
        check = x * x_old;

        if (check < 0) {
            temp = temp_left;
            dem = 0;

            for (i = 0; i < 1001; i++) {
                if (check_sign(temp, 1) != check_sign(temp + delta/1001, 1)) {
                    dem++;
                }
                temp = temp + delta/1001;
            }

            if (dem == 0) {
                phanly[count_].a = temp_left;
                phanly[count_].b = temp_left + delta;
                count_++;
            } else {
                printf("Trong khoang (%.2lf, %.2lf) co it nhat %d nghiem. Moi khao sat ham so.", temp_left, temp_left + delta, dem);
                fprintf(fout, " \n\nTrong khoang (%.2lf, %.2lf) co it nhat %d nghiem. Moi khao sat ham so.", temp_left, temp_left + delta, dem);
            }
        }

        temp_left = temp_left + delta;
    }
}

int bisection_Method() { // Ham thu hep khoang phan ly bang phuong phap chia doi
    float m;
    double p, q, c, f_p, f_c;
    int i = 0, check_sign_fp, check_sign_fc;

    printf("\n\nVoi khoang phan ly nghiem (p,q) voi |p-q| <= m. Nhap vao so m: ");
    fprintf(fout, "\n\nVoi khoang phan ly nghiem (p,q) voi |p-q| <= m. Nhap vao so m: ");
    scanf("%f", &m);
    fprintf(fout, "\nm = %f", m);

    while (i < count_) {
        p = phanly[i].a;
        q = phanly[i].b;

        f_p = f(p);
        check_sign_fp = check_sign(p, 0);

        while (fabs(q-p) > m) {
            c = (p + q) / 2.0;
            f_c = f(c);
            check_sign_fc = check_sign(c, 0);

            if (check_sign_fp != check_sign_fc) {
                q = c;
            } else {
                p = c;
            }
        }

        phanly[i].a = p;
        phanly[i].b = q;
        i++;
    }
}



void secant_Method_n(ICS local) { // Ham tim nghiem voi so lan lap cho truoc
    int i, n;
    double sai_so;

    printf("Nhap so lan lap: ");
    scanf("%d", &n);
    fprintf(fout, "\n\nNhap so lan lap: ");
    fprintf(fout, "\t%d", n);

    m = minf(f1, local);
    M = maxf(f1, local);
    a = local.a;
    b = local.b;
    fa = f(a);
    fb = f(b);
    x = a - fa * (a - b) / (fa - fb);
    fx = f(x);

    if (f(x) * fa < 0) {
        b = a;
        fb = fa;
    }

    printf("\n\t\t\t\t+-+-+ Lap nghiem voi %d lam lap +-+-+", n);
    fprintf(fout, "\n\n\t\t\t\t\t+-+-+ Lap nghiem voi %d lan lap +-+-+\n", n);

    printf("\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\t\t\t| Lan lap | x_n | f(x_n) |");
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t| Lan lap | x_n | f(x_n) |");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");

    if (fx < 0) {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    } else {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    }

    i = 1;
    while (i < n) {
        x_old = x;
        x = x - fx * (x - b) / (fx - fb);
        fx = f(x);
        i++;

        printf("\n\t\t\t+---------|--------------------|---------------------+");
        fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");

        if (fx < 0) {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        } else {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        }
    }

    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");

    printf("\n\nVay nghiem x* = %.12lf", x);
    printf("\nSo lan lap: %d", i);
    printf("\n\nSai so 1: %.12lf", sai_so_1());
    printf("\nSai so 2: %.12lf", sai_so_2());
    fprintf(fout, "\n\nVay nghiem x* = %.10lf", x);
    fprintf(fout, "\nSo lan lap: %d", i);
    fprintf(fout, "\n\nSai so 1: %.12lf", sai_so_1());
    fprintf(fout, "\nSai so 2: %.12lf", sai_so_2());
}




void secant_Method_epsi(ICS local) {
    int i;
    double sai_so;
    printf("Nhap sai so \"e\" mong muon: ");
    scanf("%lf", &eps);
    fprintf(fout, "\n\nNhap sai so \"e\" mong muon: ");
    fprintf(fout, "\t%lf", eps);

    m = minf(f1, local);
    M = maxf(f1, local);
    a = local.a;
    b = local.b;
    fa = f(a);
    fb = f(b);
    x = a - fa * (a - b) / (fa - fb);
    fx = f(x);
    if (f(x) * fa < 0) {
        b = a;
        fb = fa;
    }
    sai_so = sai_so_1();
    printf("\n\t\t\t\t +-+-+ Lap nghiem theo sai so 1 +-+-+");
    fprintf(fout, "\n\n\t\t\t\t\t\t+-+-+ Lap nghiem theo sai so 1 +-+-+\n");

    printf("\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\t\t\t| Lan lap | x_n | f(x_n) |");
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t| Lan lap | x_n | f(x_n) |");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    if (fx < 0) {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    } else {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    }
    i = 1;
    while (sai_so > eps && i < MAX_LOOP) {
        x_old = x;
        x = x - fx * (x - b) / (fx - fb);
        fx = f(x);
        i++;
        sai_so = sai_so_1();
        printf("\t\t\t\n\t\t\t+---------|--------------------|---------------------+");
        fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
        if (fx < 0) {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        } else {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        }
    }
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\nVay nghiem x* = %.10lf", x);
    printf("\nSo lan lap: %d", i);
    fprintf(fout, "\n\nVay nghiem x* = %.lf", x);
    fprintf(fout, "\nSo lan lap: %d", i);

    printf("\n\n\t\t\t\t+-+-+ Lap nghiem theo sai so 2 +-+-+");
    fprintf(fout, "\n\n\t\t\t\t+-+-+ Lap nghiem theo sai so 2 +-+-+\n");

    printf("\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\t\t\t| Lan lap | x_n | f(x_n) |");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t| Lan lap | x_n | f(x_n) |");
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");

    a = local.a;
    b = local.b;
    fa = f(a);
    fb = f(b);
    x = a - fa * (a - b) / (fa - fb);
    fx = f(x);
    if (f(x) * fa < 0) {
        b = a;
        fb = fa;
    }
    sai_so = sai_so_2();
    if (fx < 0) {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    } else {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    }
    i = 1;
    while (sai_so > eps && i < MAX_LOOP) {
        x_old = x;
        x = x - fx * (x - b) / (fx - fb);
        fx = f(x);
        i++;
        sai_so = sai_so_2();
        printf("\n\t\t\t+---------|--------------------|---------------------+");
        fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
        if (fx < 0) {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        } else {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        }
    }
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\nVay nghiem x* = %.10lf", x);
    printf("\nSo lan lap: %d", i);
    fprintf(fout, "\n\nVay nghiem x* = %.lf", x);
    fprintf(fout, "\nSo lan lap: %d", i);
}

void secant_Method_e(ICS local) {
    int i;
    double sai_so;
    printf("Nhap sai so \"e\" mong muon: ");
    scanf("%lf", &eps);
    fprintf(fout, "\n\nNhap sai so \"e\" mong muon: ");
    fprintf(fout, "\t%lf", eps);

    m = minf(f1, local);
    M = maxf(f1, local);
    a = local.a;
    b = local.b;
    fa = f(a);
    fb = f(b);
    x = a - fa * (a - b) / (fa - fb);
    fx = f(x);
    if (f(x) * fa < 0) {
        b = a;
        fb = fa;
    }
    sai_so = fabs(x - a);
    printf("\n\t\t\t Lap nghiem thoa man |X{n} - X{n-1}| < %.9lf", eps);
    fprintf(fout, "\n\t\t\t+-+-+ Lap nghiem thoa man |X{n} - X{n-1}| < %lf +-+-+\n", eps);

    printf("\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\t\t\t| Lan lap | x_n | f(x_n) |");
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t| Lan lap | x_n | f(x_n) |");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");

    if (fx < 0) {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    } else {
        printf("\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, fx);
        fprintf(fout, "\n\t\t\t| 1\t | x = %.8lf | f(x) = %.8lf |", x, f(x));
    }
    i = 1;
    while (sai_so > eps && i < MAX_LOOP) {
        x_old = x;
        x = x - fx * (x - b) / (fx - fb);
        fx = f(x);
        i++;
        sai_so = fabs(x - x_old);
        printf("\n\t\t\t+---------|--------------------|---------------------+");
        fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
        if (fx < 0) {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        } else {
            printf("\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
            fprintf(fout, "\n\t\t\t| %2d\t | x = %.8lf | f(x) = %.8lf |", i, x, fx);
        }
    }
    printf("\n\t\t\t+---------|--------------------|---------------------+");
    fprintf(fout, "\n\t\t\t+---------|--------------------|---------------------+");
    printf("\n\nVay nghiem x* = %.10lf", x);
    printf("\nSo lan lap: %d", i);
    fprintf(fout, "\n\nVay nghiem x* = %.10lf", x);
    fprintf(fout, "\nSo lan lap: %d", i);
}
