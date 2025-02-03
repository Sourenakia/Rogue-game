#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>



typedef struct{
	int color;
	char font, location, previous;
    int flag;
    int check;
}mainpixel;


typedef struct{
    mainpixel pixel[5][38][153];
    char name[40];
    char password[40];
    char email[40];
    int floor;
    int gold;
}pix;

pix cell;
int M = 0;

int Login();
int thealthy = 0, tspeed = 0, tdamage = 0;
int tir = 0, gorz = 0, khanjar = 0, asa = 0, shamshir = 0, food = 0; 

int ghadr(int x, int y){
    int a = x - y;
    if (a < 0){
        a = a * -1;
    }
    return a;
}


int Random_number(int a, int b){
    int randomnumber = rand();
    int c = b - a + 1;
    randomnumber %= c;
    printw("%d",randomnumber);
    return (randomnumber + a);
}

void update_screen(int k){
	clear();
	for(int j = 0; j < 38; j++){
		for(int i = 0; i < 153; i++){
            if(cell.pixel[k][j][i].font != '^'){
			    mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
            }
            else{
                mvprintw(j, i, ".");
            }
		}
	}
}
//------------------------------------------sehat---------------------------------------

int sehat(int y1, int x1, int y2, int x2, int k){
    if(y1 > y2){
        int temp = y2;
        y2 = y1;
        y1 = temp;
    }
    if(x1 > x2){
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    for (int j = y1; j < y2; j++){
        for (int i = x1; i < x2; i++){
            if (cell.pixel[k][j + 1][i].previous != '#' || cell.pixel[k][j][i - 1].previous != '#' ||
                cell.pixel[k][j - 1][i].previous != '#' || cell.pixel[k][j][i + 1].previous != '#'){
                    return 0;
            }
        }
    }
    return 1;
}

//------------------------------------------show----------------------------------------

int mahdood_room(int y, int x, int k){
    int m1 = y, n1 = x, m2 = y, n2 = x;
    for(int j = y; j < 37; j++){
        if(cell.pixel[k][j][x].previous == '-' || cell.pixel[k][j][x].previous == '+'){
            m2 = j;
            break;
        }
    }
    for(int j = y; j > 0; j--){
        if(cell.pixel[k][j][x].previous == '-' || cell.pixel[k][j][x].previous == '+'){
            m1 = j;
            break;
        }
    }
    for(int i = x; i < 153; i++){
        if(cell.pixel[k][y][i].previous == '|' || cell.pixel[k][y][i].previous == '+'){
            n2 = i;
            break;
        }
    }
    for(int i = x; i > 0; i--){
        if(cell.pixel[k][y][i].previous == '|' || cell.pixel[k][y][i].previous == '+'){
            n1 = i;
            break;
        }
    }
    for(int j = m1 - 1; j <= m2 + 1; j++){
        for(int i = n1 - 1; i <= n2 + 1; i++){
            if(cell.pixel[k][j][i].previous != '#' && cell.pixel[k][j][i].previous != '^')
                mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                if(cell.pixel[k][j][i].previous == '+'){
                    cell.pixel[k][j][i].check = 1;
                }
        }
    }
    move(37, 152);
}

//----------------------------------------------------rahroh--------------------------
int Rahroh_mahdood(int y, int x, int k){
    if(cell.pixel[k][y][x].previous == '#' || cell.pixel[k][y][x].previous == '+'){
        for(int j = y - 5; j <= y + 5; j++){
            for(int i = x - 5; i <= x + 5; i++){
                if(cell.pixel[k][j][i].previous == '#' || cell.pixel[k][j][i].previous == '+'){
                    if(ghadr(i + j, x + y) < 6){
                        if(sehat(y, x, j, i, k)){
                            mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                            move(37, 152);
                        }
                    }
                }
            }
        }
    }
}
//-------------------------------------------KEY----------------------------------------

int key(int y, int x, char c, int k){
    move(37, 152);
    noecho();
    mvprintw(1, 1, "                                                                         ");
    move(37, 152);
   
    if(c == '1'){
        if (cell.pixel[k][y + 1][x - 1].flag != 0 && cell.pixel[k][y + 1][x - 1].font != '|' &&
            cell.pixel[k][y + 1][x - 1].font != '-' && cell.pixel[k][y + 1][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            if (cell.pixel[k][y + 1][x - 1].previous == '+' && cell.pixel[k][y + 1][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x - 1].check = 1;
                    mahdood_room(y + 1, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y + 1;
            x = x - 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '2'){
        if (cell.pixel[k][y + 1][x].flag != 0 && cell.pixel[k][y + 1][x].font != '|' && 
            cell.pixel[k][y + 1][x].font != '-' && cell.pixel[k][y + 1][x].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            
            if (cell.pixel[k][y + 1][x].previous == '+' && cell.pixel[k][y + 1][x].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x].check = 1;
                    mahdood_room(y + 2, x, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y + 1;
            x = x;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '3'){
        if (cell.pixel[k][y + 1][x + 1].flag != 0 && cell.pixel[k][y + 1][x + 1].font != '|' && 
            cell.pixel[k][y + 1][x + 1].font != '-' && cell.pixel[k][y + 1][x + 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x + 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            if (cell.pixel[k][y + 1][x + 1].previous == '+' && cell.pixel[k][y + 1][x + 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x + 1].check = 1;
                    mahdood_room(y + 1, x + 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y + 1;
            x = x + 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '4'){
        if (cell.pixel[k][y][x - 1].flag != 0 && cell.pixel[k][y][x - 1].font != '|' && 
            cell.pixel[k][y][x - 1].font != '-' && cell.pixel[k][y][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            if (cell.pixel[k][y][x - 1].previous == '+' && cell.pixel[k][y][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y][x - 1].check = 1;
                    mahdood_room(y, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y;
            x = x - 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '6'){
        if (cell.pixel[k][y][x + 1].flag != 0 && cell.pixel[k][y][x + 1].font != '|' && 
            cell.pixel[k][y][x + 1].font != '-' && cell.pixel[k][y][x + 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y][x + 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            if (cell.pixel[k][y][x + 1].previous == '+' && cell.pixel[k][y][x + 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y][x + 1].check = 1;
                    mahdood_room(y, x + 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y;
            x = x + 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '7'){
        if (cell.pixel[k][y - 1][x - 1].flag != 0 && cell.pixel[k][y - 1][x - 1].font != '|' && 
            cell.pixel[k][y - 1][x - 1].font != '-' && cell.pixel[k][y - 1][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y - 1][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            
            if (cell.pixel[k][y - 1][x - 1].previous == '+' && cell.pixel[k][y - 1][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y - 1][x - 1].check = 1;
                    mahdood_room(y - 1, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y - 1;
            x = x - 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '8'){
        if (cell.pixel[k][y - 1][x].flag != 0 && cell.pixel[k][y - 1][x].font != '|' && 
            cell.pixel[k][y - 1][x].font != '-' && cell.pixel[k][y - 1][x].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y - 1][x].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            
            if (cell.pixel[k][y - 1][x].previous == '+' && cell.pixel[k][y - 1][x].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y - 1][x].check = 1;
                    mahdood_room(y - 2, x, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y - 1;
            x = x;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
    else if(c == '9'){
        if (cell.pixel[k][y - 1][x + 1].flag != 0 && cell.pixel[k][y - 1][x + 1].font != '|' && 
            cell.pixel[k][y - 1][x + 1].font != '-' && cell.pixel[k][y - 1][x + 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y - 1][x + 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            
            if (cell.pixel[k][y - 1][x + 1].previous == '+' && cell.pixel[k][y - 1][x + 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y - 1][x + 1].check = 1;
                    mahdood_room(y - 1, x + 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y - 1;
            x = x + 1;
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
        }
    }
//-------------------------------------------------------------------------------------- 
    
    else if (c == 27) {
        
    return 1;
   }
   
//--------------------------------------------------------------------------------------

    if(cell.pixel[k][y][x].previous == '$'){
        cell.pixel[k][y][x].previous = '.';
        cell.gold++;
        mvprintw(1, 1, "Congrayulations! You found a gold.");
    }
    if(cell.pixel[k][y][x].previous == 'B'){
        cell.pixel[k][y][x].previous = '.';
        cell.gold += 5;
        mvprintw(1, 1, "Congrayulations! You found a black gold.");
    }
    char f;
    if(cell.pixel[k][y][x].previous == 'T'){
        f = getch();
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            if(cell.pixel[k][y][x].flag == 12){
                thealthy++;
            }
            if(cell.pixel[k][y][x].flag == 13){
                tdamage++;
            }
            if(cell.pixel[k][y][x].flag == 14){
                tspeed++;
            }
      //      mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
        //    mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
       
            //f = getch();
        }
        else{
      //      key_show(y, x, f, k);
       }
    }
    if(cell.pixel[k][y][x].previous == 'g'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            gorz++;
            //f = getch();
        }
    }
    if(cell.pixel[k][y][x].previous == 't'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            tir++;
            //f = getch();
        }
    }
    if(cell.pixel[k][y][x].previous == 'a'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            asa++;
            //f = getch();
        }
    }
    if(cell.pixel[k][y][x].previous == 's'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            shamshir++;
            //f = getch();
        }
    }
    if(cell.pixel[k][y][x].previous == 'k'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            khanjar++;
            //f = getch();
        }
    }
    if(cell.pixel[k][y][x].previous == 'F'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            food++;
            //f = getch();
        }
    }
    move(37, 152);
    Rahroh_mahdood(y, x, k);
    c = getch();
    move(37, 152);
    if(cell.pixel[k][y][x].previous == '^'){
        for(int i = 0; i < 38; i++){
            for(int j = 0; j < 153; j++){
                mvprintw(i, j, " ");
            }
        }
        int yh1 = Random_number(10, 15);
        int yh2 = Random_number(25, 30);
        int xh1 = Random_number(30, 60);
        int xh2 = Random_number(90, 120);
        for(int i = xh1; i <= xh2; i++){
		    mvprintw(yh1, i, "-");
            mvprintw(yh2, i, "-");
	    }
	    for(int i = yh1 + 1; i < yh2; i++){
		    mvprintw(i, xh1, "|");
            mvprintw(i, xh2, "|");
	    }
	    for(int i = xh1 + 1; i < xh2; i++){
		    for(int j = yh1 + 1; j < yh2; j++){
			    mvprintw(j, i, ".");
		    }
    	}
        mvprintw(34, 10, "GOLd: %d", cell.gold);
        key(75, 20, c, k);
    }
    mvprintw(34, 10, "GOLD: %d", cell.gold);
    move(37, 152);
    key(y, x, c, k);
    return 1;
}

//---------------------------------------------------------------------------------------------------------

void Masir(int yv1, int xv1, int yv2, int xv2, int k){
    int x1, x2, y1, y2;
    if(cell.pixel[k][yv1][xv1 + 1].flag == 0){
        x1 = xv1 + 1;
        y1 = yv1;
    }
    else if(cell.pixel[k][yv1][xv1 - 1].flag == 0){
        x1 = xv1 - 1;
        y1 = yv1;
    }
    else if(cell.pixel[k][yv1 - 1][xv1].flag == 0){
        x1 = xv1;
        y1 = yv1 - 1;
    }
    else if(cell.pixel[k][yv1 + 1][xv1].flag == 0){
        x1 = xv1;
        y1 = yv1 + 1;
    }
    if(cell.pixel[k][yv2][xv2 + 1].flag == 0){
        x2 = xv2 + 1;
        y2 = yv2;
    }
    else if(cell.pixel[k][yv2][xv2 - 1].flag == 0){
        x2 = xv2 - 1;
        y2 = yv2;
    }
    else if(cell.pixel[k][yv2 - 1][xv2].flag == 0){
        x2 = xv2;
        y2 = yv2 - 1;
    }
    else if(cell.pixel[k][yv2 + 1][xv2].flag == 0){
        x2 = xv2;
        y2 = yv2 + 1;
    }
    if(x2 < x1){
        int temp = x1;
        x1 = x2;
        x2 = x1;
    }
    
    if(y1 > y2){
        for(int i = x1; i <= x2; i++){
            if(cell.pixel[k][y2][i].flag == 0){
                cell.pixel[k][y2][i].font = '#';
            }
        }
        for(int j = y1; j >= y2; j--){
            if(cell.pixel[k][j][x1].flag == 0){
                cell.pixel[k][j][x1].font = '#';
            }
        }    
    }
    else{
        for(int i = x1; i <= x2; i++){
            if(cell.pixel[k][y1][i].flag == 0){
                cell.pixel[k][y1][i].font = '#';
            }
        }
        for(int j = y2; j >= y1; j--){
            if(cell.pixel[k][j][x2].flag == 0){
                cell.pixel[k][j][x2].font = '#';
            }
        }
    }
}

void Masir_1(int yv1, int xv1, int yv2, int xv2, int k){
    int x1, x2, y1, y2;
    if(cell.pixel[k][yv1][xv1 + 1].flag == 0){
        x1 = xv1 + 1;
        y1 = yv1;
    }
    else if(cell.pixel[k][yv1][xv1 - 1].flag == 0){
        x1 = xv1 - 1;
        y1 = yv1;
    }
    else if(cell.pixel[k][yv1 - 1][xv1].flag == 0){
        x1 = xv1;
        y1 = yv1 - 1;
    }
    else if(cell.pixel[k][yv1 + 1][xv1].flag == 0){
        x1 = xv1;
        y1 = yv1 + 1;
    }
    if(cell.pixel[k][yv2][xv2 + 1].flag == 0){
        x2 = xv2 + 1;
        y2 = yv2;
    }
    else if(cell.pixel[k][yv2][xv2 - 1].flag == 0){
        x2 = xv2 - 1;
        y2 = yv2;
    }
    else if(cell.pixel[k][yv2 - 1][xv2].flag == 0){
        x2 = xv2;
        y2 = yv2 - 1;
    }
    else if(cell.pixel[k][yv2 + 1][xv2].flag == 0){
        x2 = xv2;
        y2 = yv2 + 1;
    }
    
    if(x1 > x2){
        for(int i = x1; i >= x2; i--){
            if (cell.pixel[k][y1][i].flag == 0){
                cell.pixel[k][y1][i].font = '#';
            }
        }
        for(int j = y1; j <= y2; j++){
            if(cell.pixel[k][j][x2].flag == 0){
                cell.pixel[k][j][x2].font = '#';
            }
        }
    }
    else{
        for(int j = y2; j >= y1; j--){
            if(cell.pixel[k][j][x1].flag == 0){
                cell.pixel[k][j][x1].font = '#';
            }
        }
        for(int i = x1; i <= x2; i++){
            if(cell.pixel[k][y2][i].flag == 0){
                cell.pixel[k][y2][i].font = '#';
            }
        }
    }
}

int jadval(int ax, int bx, int ay, int by, int k){
	for(int i = ax; i <= bx; i++){
		cell.pixel[k][ay][i].font = '-';
		cell.pixel[k][by][i].font = '-';
        cell.pixel[k][ay][i].flag = 2;
		cell.pixel[k][by][i].flag = 2;
	}
	for(int i = ay + 1; i < by; i++){
		cell.pixel[k][i][ax].font = '|';
		cell.pixel[k][i][bx].font = '|';
        cell.pixel[k][i][ax].flag = 3;
        cell.pixel[k][i][bx].flag = 3;
	}
	for(int i = ax + 1; i < bx; i++){
		for(int j = ay + 1; j < by; j++){
			cell.pixel[k][j][i].font = '.';
            cell.pixel[k][j][i].flag = 1;
		}
	}
    int randomo = Random_number(0, 2);
    for(int i = 0; i < randomo; i++){
        int ox = Random_number(ax + 2, bx - 2);
        int oy = Random_number(ay + 2, by - 2);
        cell.pixel[k][oy][ox].font = 'O';
        cell.pixel[k][oy][ox].flag = 6; 
    }
    int randomh = Random_number(0 , 8) / 8;
    if(randomh){
        int hx = Random_number(ax + 2, bx - 2);
        int hy = Random_number(ay + 2, by - 2);
        cell.pixel[k][hy][hx].font = '^';
        cell.pixel[k][hy][hx].flag = 7;
    }
    int p = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    int px1, px2, py1, py2;
    do{
        px1 = Random_number(ax + 1, bx - 1);
        px2 = Random_number(ax + 1, bx - 1);
        py1 = Random_number(ay + 1, by - 1);
        py2 = Random_number(ay + 1, by - 1);
        int random = rand() % 2;
        if((random == 1) && (p1 == 0)){
            p1 = 1;
            cell.pixel[k][ay][px1].font = '+';
            cell.pixel[k][ay][px1].flag = 5;
            cell.pixel[k][ay][px1].location = 'U';
        }
        random = rand() % 2;
        if((random == 1) && (p2 == 0)){
            p2 = 1;
            cell.pixel[k][by][px2].font = '+';
            cell.pixel[k][by][px2].flag = 5;
            cell.pixel[k][by][px2].location = 'D';
        }
        random = rand() % 2;
        if((random == 1) && (p3 == 0)){
            p3 = 1;
            cell.pixel[k][py1][ax].font = '+';
            cell.pixel[k][py1][ax].flag = 5;
            cell.pixel[k][py1][ax].location = 'L';
        }
        random = rand() % 2;
        if((random == 1) && (p4 == 0)){
            p4 = 1;
            cell.pixel[k][py2][bx].font = '+';
            cell.pixel[k][py2][bx].flag = 5;
            cell.pixel[k][py2][bx].location = 'R';
        }
        p = p1 + p2 + p3 + p4;
    } while (p != 3 && p != 4);
    /*/
    int randomm = Random_number(0 , 10) / 10;
    if(randomm){
        int mx1 = Random_number(ax + 1, bx - 1);
        int mx2 = Random_number(ax + 1, bx - 1);
        int my1 = Random_number(ay + 1, by - 1);
        int my2 = Random_number(ay + 1, by - 1);
        int zel = Random_number(1, 4); 
        if(zel == 1){
            if (cell.pixel[k][ay][px1].font == '+'){
                cell.pixel[k][ay][px1].font = 'm';
                cell.pixel[k][ay][px1].flag = 10;
            }
        }
        else if(zel == 2){
            if (cell.pixel[k][by][px2].font == '+'){
                cell.pixel[k][by][px2].font = 'm';
                cell.pixel[k][by][px2].flag = 10;
            }
        }
        else if(zel == 3){
            if (cell.pixel[k][py1][ax].font == '+'){
                cell.pixel[k][py1][ax].font = 'm';
                cell.pixel[k][py1][ax].flag = 10;
            }
        }
        else if(zel == 4){
            if (cell.pixel[k][py2][bx].font == '+'){
                cell.pixel[k][py2][bx].font = 'm';
                cell.pixel[k][py2][bx].flag = 10;
            }
        }
    }
    /*/
    for(int i = ax + 1; i < bx; i++){
		for(int j = ay + 1; j < by; j++){
			int randomg = Random_number(0, 39) / 39;
            if(randomg){
                cell.pixel[k][j][i].font = '$';
                cell.pixel[k][j][i].flag = 11;
                int randombg = Random_number(0, 9) / 9;
                if(randombg){
                    cell.pixel[k][j][i].font = 'B';
                    cell.pixel[k][j][i].flag = 12;
                }
            }
		}
	}


    for(int i = ax + 1; i < bx; i++){
		for(int j = ay + 1; j < by; j++){
			int randomt = Random_number(0, 39) / 39;
            if(randomt){
                cell.pixel[k][j][i].font = 'T';
                cell.pixel[k][j][i].flag = 12;
                int randomk = Random_number(1, 3);
                if(randomk == 1){
                    cell.pixel[k][j][i].flag = 12;
                }
                if(randomk == 2){
                    cell.pixel[k][j][i].flag = 13;
                }
                if(randomk == 3){
                    cell.pixel[k][j][i].flag = 14;
                }
            }
		}
	}
    for(int i = ax + 1; i < bx; i++){
		for(int j = ay + 1; j < by; j++){
            int randomw = Random_number(0, 39) / 39;
            if(randomw){
                int randomi = Random_number(1, 5);
                if(randomi == 1){
                    cell.pixel[k][j][i].font = 'g';
                    cell.pixel[k][j][i].flag = 15;
                }
                if(randomi == 2){
                    cell.pixel[k][j][i].font = 'k';
                    cell.pixel[k][j][i].flag = 16;
                }
                if(randomi == 3){
                    cell.pixel[k][j][i].font = 'a';
                    cell.pixel[k][j][i].flag = 17;
                }
                if(randomi == 4){
                    cell.pixel[k][j][i].font = 't';
                    cell.pixel[k][j][i].flag = 18;
                }
                if(randomi == 5){
                    cell.pixel[k][j][i].font = 's';
                    cell.pixel[k][j][i].flag = 19;
                }
            }
        }
    }
    for(int i = ax + 1; i < bx; i++){
		for(int j = ay + 1; j < by; j++){
            int randomf = Random_number(0, 39) / 39;
            if(randomf){
                int randomi = Random_number(1, 4);
                if(randomi == 1){
                    cell.pixel[k][j][i].font = 'F';
                    cell.pixel[k][j][i].flag = 15;
                }
                if(randomi == 2){
                    cell.pixel[k][j][i].font = 'F';
                    cell.pixel[k][j][i].flag = 16;
                }
                if(randomi == 3){
                    cell.pixel[k][j][i].font = 'F';
                    cell.pixel[k][j][i].flag = 17;
                }
                if(randomi == 4){
                    cell.pixel[k][j][i].font = 'F';
                    cell.pixel[k][j][i].flag = 18;
                }
            }
        }
    }
}

void Table_show(int x1, int x2, int y1, int y2, int k){
    int randomy1, randomx1, randomy2, randomx2, p = 0;
    do{
        randomy1 = Random_number(y1, y2);
        randomy2 = Random_number(y1, y2);
        randomx1 = Random_number(x1, x2);
        randomx2 = Random_number(x1, x2);
        if(randomy2 < randomy1){
            int temp = randomy1;
            randomy1 = randomy2;
            randomy2 = temp;
        }
        if(randomx2 < randomx1){
            int temp = randomx1;
            randomx1 = randomx2;
            randomx2 = temp;
        }
        if(randomx2 - randomx1 < 5 || randomy2 - randomy1 < 5){
            continue;
        }
        printw("%d %d %d %d", randomx1, randomx2, randomy1, randomy2);
        jadval(randomx1, randomx2, randomy1, randomy2, k);
        break;        
    }while (true);
}

int Rahroh_up(int a, int b, int c, int d, int e, int k){
    int m1, n1, m2, n2, p1 = 0, p2 = 0;
    for(int j = a; j < b; j++){
        for(int i = c; i < d; i++){
            if(cell.pixel[k][j][i].location == 'U'){
                m1 = j;
                n1 = i;
                p1++;
            }
        }
    }
    for(int j = a; j < b; j++){
        for(int i = d + 1; i < e; i++){
            if(cell.pixel[k][j][i].location == 'L'){
                m2 = j;
                n2 = i;
                p2++;
            }
        }
    }
    if (p1 + p2 == 2){
        Masir(m1, n1, m2, n2, k);
    }
    else if(p1 == 1){
        for(int j = a; j < b; j++){
            for(int i = d + 1; i < e; i++){
                if(cell.pixel[k][j][i].location == 'U'){
                    m2 = j;
                    n2 = i;
                    p2++;
                }
            }
        }
        Masir(m1, n1, m2, n2, k);
    }
}

int Rahoroh_right(int a, int b, int c, int d, int e, int k){
    int m1, n1, m2, n2, p1 = 0, p2 = 0;
    for(int j = a; j < b; j++){
        for(int i = c; i < d; i++){
            if(cell.pixel[k][j][i].location == 'R'){
                m1 = j;
                n1 = i;
                p1++;
            }
        }
    }
    for(int j = a; j < b; j++){
        for(int i = d + 1; i < e; i++){
            if(cell.pixel[k][j][i].location == 'L'){
                m2 = j;
                n2 = i;
                p2++;
            }
        }
    }
    if (p1 + p2 == 2){
        Masir(m1, n1, m2, n2, k);
    }
    else if(p1 == 1){
        for(int j = a; j < b; j++){
            for(int i = d + 1; i < e; i++){
                if(cell.pixel[k][j][i].location == 'U'){
                    m2 = j;
                    n2 = i;
                    p2++;
                }
            }
        }
        Masir(m1, n1, m2, n2, k);
    }
    else{
        Rahroh_up(a, b, c, d, e, k);
    }
}

int Rahroh_left(int a, int b, int c, int d, int e, int f, int g, int k){
    int m1, n1, m2, n2, p1 = 0, p2 = 0;
    for(int j = a; j < b; j++){
        for(int i = c; i < d; i++){
            if(cell.pixel[k][j][i].location == 'L'){
                m1 = j;
                n1 = i;
                p1++;
            }
        }
    }
    for(int j = b + 1; j < e; j++){
        for(int i = f; i < g; i++){
            if(cell.pixel[k][j][i].location == 'U'){
                m2 = j;
                n2 = i;
                p2++;
        }
        }
    }
    if (p1 + p2 == 2){
        Masir_1(m1, n1, m2, n2, k);
    }
    else if(p1 == 1){
        for(int j = b + 1; j < e; j++){
            for(int i = f; i < g; i++){
                if(cell.pixel[k][j][i].location == 'L'){
                    m2 = j;
                    n2 = i;
                    p2++;
                }
            }
        }
        Masir_1(m1, n1, m2, n2, k);
    }
}

int Rahroh_down(int a, int b, int c, int d, int e, int f, int g, int k){
    int m1, n1, m2, n2, p1 = 0, p2 = 0;
    for(int j = a; j < b; j++){
        for(int i = c; i < d; i++){
            if(cell.pixel[k][j][i].location == 'D'){
                m1 = j;
                n1 = i;
                p1++;
            }
        }
    }
    for(int j = b + 1; j < e; j++){
        for(int i = f; i < g; i++){
            if(cell.pixel[k][j][i].location == 'U'){
                m2 = j;
                n2 = i;
                p2++;
        }
        }
    }
    if (p1 + p2 == 2){
        Masir_1(m1, n1, m2, n2, k);
    }
    else if(p1 == 1){
        for(int j = b + 1; j < e; j++){
            for(int i = f; i < g; i++){
                if(cell.pixel[k][j][i].location == 'L'){
                    m2 = j;
                    n2 = i;
                    p2++;
                }
            }
        }
        Masir_1(m1, n1, m2, n2, k);
    }
    else{
        Rahroh_left(a, b, c, d, e, f, g, k);
    }
}

int Main_game(int k){
  /*  int i,j,l;
    for (l=0; l<=k; ++l)
      for (j=0; j<38; ++j)
        for (i=0 ; i<153; ++i){
           cell.pixel[l][j][i].font = ' ';
           cell.pixel[l][j][i].flag = 0;
        }*/
    srand(time(0));
    int tedad = Random_number(11, 18);
    if(tedad == 11 || tedad == 13){
        Table_show(4, 36, 4, 12, k);
        Table_show(38, 74, 4, 12, k);
        Table_show(76, 112, 4, 12, k);
        Table_show(114, 148, 4, 12, k);
        Table_show(4, 49, 14, 23, k);
        Table_show(51, 100, 14, 23, k);
        Table_show(102, 148, 14, 23, k);
        Table_show(4, 36, 25, 32, k);
        Table_show(38, 74, 25, 32, k);
        Table_show(76, 112, 25, 32, k);
        Table_show(114, 148, 25, 32, k);
        Rahoroh_right(4, 13, 4, 37, 75, k);
        Rahoroh_right(4, 13, 38, 75, 113, k);
        Rahoroh_right(4, 13, 76, 113, 148, k);
        Rahoroh_right(25, 33, 4, 37, 75, k);
        Rahoroh_right(25, 33, 38, 75, 113, k);
        Rahoroh_right(25, 33, 76, 113, 148, k);
        Rahroh_down(4, 13, 4, 37, 24, 4, 50, k);
        Rahroh_down(14, 24, 4, 50, 33, 4, 37, k);
        Rahroh_down(4, 13, 38, 75, 24, 51, 103, k);
        Rahroh_down(14, 24, 51, 103, 33, 38, 75, k);
        Rahroh_down(4, 13, 76, 113, 24, 102, 149, k);
        Rahroh_down(14, 24, 102, 149, 33, 114, 148, k);
    }
    else if(tedad == 12 || tedad == 14){
        Table_show(4, 36, 4, 12, k);
        Table_show(38, 74, 4, 12, k);
        Table_show(76, 112, 4, 12, k);
        Table_show(114, 148, 4, 12, k);
        Table_show(4, 36, 14, 23, k);
        Table_show(38, 74, 14, 23, k);
        Table_show(76, 112, 14, 23, k);
        Table_show(114, 148, 14, 23, k);
        Table_show(4, 36, 25, 32, k);
        Table_show(38, 74, 25, 32, k);
        Table_show(76, 112, 25, 32, k);
        Table_show(114, 148, 25, 32, k);
        Rahoroh_right(4, 13, 4, 37, 75, k);
        Rahoroh_right(4, 13, 38, 75, 113, k);
        Rahoroh_right(4, 13, 76, 113, 148, k);
        Rahoroh_right(14, 24, 4, 37, 75, k);
        Rahoroh_right(14, 24, 38, 75, 113, k);
        Rahoroh_right(14, 24, 76, 113, 148, k);
        Rahoroh_right(25, 33, 4, 37, 75, k);
        Rahoroh_right(25, 33, 38, 75, 113, k);
        Rahoroh_right(25, 33, 76, 113, 148, k);
        Rahroh_down(4, 13, 4, 37, 24, 4, 37, k);
        Rahroh_down(14, 24, 4, 37, 33, 4, 37, k);
        Rahroh_down(4, 13, 38, 75, 24, 38, 75, k);
        Rahroh_down(14, 24, 38, 75, 33, 38, 75, k);
        Rahroh_down(4, 13, 76, 113, 24, 76, 113, k);
        Rahroh_down(14, 24, 76, 113, 33, 76, 113, k);
        Rahroh_down(4, 13, 114, 149, 24, 114, 149, k);
        Rahroh_down(14, 24, 114, 149, 33, 114, 149, k);
    }
    else if(tedad == 15 || tedad == 16){
        Table_show(4, 28, 4, 12, k);
        Table_show(30, 58, 4, 12, k);
        Table_show(60, 88, 4, 12, k);
        Table_show(90, 118, 4, 12, k);
        Table_show(120, 148, 4, 12, k);
        Table_show(4, 28, 14, 23, k);
        Table_show(30, 58, 14, 23, k);
        Table_show(60, 88, 14, 23, k);
        Table_show(90, 118, 14, 23, k);
        Table_show(120, 148, 14, 23, k);
        Table_show(4, 28, 25, 32, k);
        Table_show(30, 58, 25, 32, k);
        Table_show(60, 88, 25, 32, k);
        Table_show(90, 118, 25, 32, k);
        Table_show(120, 148, 25, 32, k);
        Rahoroh_right(4, 13, 4, 29, 59, k);
        Rahoroh_right(4, 13, 30, 59, 89, k);
        Rahoroh_right(4, 13, 60, 89, 119, k);
        Rahoroh_right(4, 13, 90, 119, 149, k);
        Rahoroh_right(14, 24, 4, 29, 59, k);
        Rahoroh_right(14, 24, 30, 59, 89, k);
        Rahoroh_right(14, 24, 60, 89, 119, k);
        Rahoroh_right(14, 24, 90, 119, 149, k);
        Rahoroh_right(24, 33, 4, 29, 59, k);
        Rahoroh_right(24, 33, 30, 59, 89, k);
        Rahoroh_right(24, 33, 60, 89, 119, k);
        Rahoroh_right(24, 33, 90, 119, 149, k);
        Rahroh_down(4, 13, 4, 30, 24, 4, 30, k);
        Rahroh_down(14, 24, 4, 30, 33, 4, 30, k);
        Rahroh_down(4, 13, 30, 60, 24, 30, 60, k);
        Rahroh_down(14, 24, 30, 60, 33, 30, 60, k);
        Rahroh_down(4, 13, 60, 90, 24, 60, 90, k);
        Rahroh_down(14, 24, 60, 90, 33, 60, 90, k);
        Rahroh_down(4, 13, 90, 120, 24, 90, 120, k);
        Rahroh_down(14, 24, 90, 120, 33, 90, 120, k);
        Rahroh_down(4, 13, 120, 150, 24, 120, 150, k);
        Rahroh_down(14, 24, 120, 150, 33, 120, 150, k);
    }
    else if(tedad == 18 || tedad == 17){
        Table_show(4, 26, 4, 12, k);
        Table_show(28, 49, 4, 12, k);
        Table_show(51, 73, 4, 12, k);
        Table_show(75, 98, 4, 12, k);
        Table_show(100, 122, 4, 12, k);
        Table_show(124, 148, 4, 12, k);
        Table_show(4, 26, 14, 23, k);
        Table_show(28, 49, 14, 23, k);
        Table_show(51, 73, 14, 23, k);
        Table_show(75, 98, 14, 23, k);
        Table_show(100, 122, 14, 23, k);
        Table_show(124, 148, 14, 23, k);
        Table_show(4, 26, 25, 32, k);
        Table_show(28, 49, 25, 32, k);
        Table_show(51, 73, 25, 32, k);
        Table_show(75, 98, 25, 32, k);
        Table_show(100, 122, 25, 32, k);
        Table_show(124, 148, 25, 32, k);        
        Rahoroh_right(4, 13, 4, 27, 50, k);
        Rahoroh_right(4, 13, 28, 50, 74, k);
        Rahoroh_right(4, 13, 51, 74, 99, k);
        Rahoroh_right(4, 13, 75, 99, 123, k);
        Rahoroh_right(4, 13, 100, 123, 149, k);
        Rahoroh_right(14, 24, 4, 27, 50, k);
        Rahoroh_right(14, 24, 28, 50, 74, k);
        Rahoroh_right(14, 24, 51, 74, 99, k);
        Rahoroh_right(14, 24, 75, 99, 123, k);
        Rahoroh_right(14, 24, 100, 123, 149, k);
        Rahoroh_right(25, 33, 4, 27, 50, k);
        Rahoroh_right(25, 33, 28, 50, 74, k);
        Rahoroh_right(25, 33, 51, 74, 99, k);
        Rahoroh_right(25, 33, 75, 99, 123, k);
        Rahoroh_right(25, 33, 100, 123, 149, k);
        Rahroh_down(4, 13, 4, 27, 24, 4, 27, k);
        Rahroh_down(14, 24, 4, 27, 33, 4, 27, k);
        Rahroh_down(4, 13, 28, 50, 24, 28, 50, k);
        Rahroh_down(14, 24, 28, 50, 33, 28, 50, k);
        Rahroh_down(4, 13, 51, 74, 24, 51, 74, k);
        Rahroh_down(14, 24, 51, 74, 33, 51, 74, k);
        Rahroh_down(4, 13, 75, 99, 24, 75, 99, k);
        Rahroh_down(14, 24, 75, 99, 33, 75, 99, k);
        Rahroh_down(4, 13, 100, 123, 24, 100, 123, k);
        Rahroh_down(14, 24, 100, 123, 33, 100, 123, k);
        Rahroh_down(4, 13, 124, 148, 24, 124, 148, k);
        Rahroh_down(14, 24, 124, 148, 33, 124, 148, k);
    }
    for(int j = 0; j < 38; j++){
        for(int i = 0; i < 153; i++){
            if(cell.pixel[k][j][i].font == '+' || cell.pixel[k][j][i].flag == 10){
                if (cell.pixel[k][j + 1][i].font != '#' && cell.pixel[k][j - 1][i].font != '#' &&
                    cell.pixel[k][j][i + 1].font != '#' && cell.pixel[k][j][i - 1].font != '#'){
                        if(cell.pixel[k][j][i - 1].font == '-' && cell.pixel[k][j][i + 1].font == '-'){
                            cell.pixel[k][j][i].font = '-';
                        }
                        if(cell.pixel[k][j + 1][i].font == '|' || cell.pixel[k][j - 1][i].font == '|'){
                            cell.pixel[k][j][i].font = '|';
                        }
                }
            }
        }
    }
    for(int j = 0; j < 38; j++){
        for (int i = 0; i < 153; i++){
            if(cell.pixel[k][j][i].font == '+'){
                cell.pixel[k][j][i].check = 0;
            }
            cell.pixel[k][j][i].previous = cell.pixel[k][j][i].font;
            if(cell.pixel[k][j][i].font == '#'){
                cell.pixel[k][j][i].flag = 4;
            }
        }
    }
    //update_screen(k);
    int p = 0, m, n;
    for(int j = 13; j < 27; j++){
        for(int i = 45; i < 120; i++){
            if(cell.pixel[k][j][i].font == '.'){
                cell.pixel[k][j][i].font = '@';
                m = j;
                n = i;
                p++;
                break;
            }
        }
        if(p)
        break;
    }
    mvprintw(m, n, "@");
    move(37, 152);
    noecho();
    for(int j = 0; j < 38; j++){
        for(int i = 0; i < 153; i++){
            mvprintw(j, i, " ");
        }
    }
    mahdood_room(m, n, k);
    char c = getch();
    
    key(m , n, c, k);

    
}



int Check_password(){
    FILE *fptr;
    pix temp;
    clear();
    echo();
    attron(COLOR_PAIR(2));
    mvprintw(5, 54, "R O G U E    G A M E");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(4));
    mvprintw(6, 58, "NEW GAME!!!");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    mvprintw(10, 50, "Please enter your username:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(32, 54, "Press R to return to the previous page");
    attroff(COLOR_PAIR(3));
    int p;
    do{
        p = 1;
        fptr = (fopen("usersinfo.dat","rb"));
        mvprintw(11, 50, "                                                                  ");
        attron(COLOR_PAIR(3));
        mvscanw(11,50, "%s", temp.name);
        fread(&cell, sizeof(cell), 1, fptr);
        while(!feof(fptr) && p){
            if(!strcmp(temp.name, cell.name)){
                do
                {
                    mvprintw(32, 54, "                                                                                              ");
                    attron(COLOR_PAIR(1));
                    mvprintw(13, 50, "please enter your password:");
                    attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(3));
                    mvscanw(14, 50, "%s", temp.password);
                    attroff(COLOR_PAIR(3));
                    if(!strcmp(temp.password, cell.password)){
                        mvprintw(32, 54, "                                                                                     ");
                        mvprintw(32, 54, "Hello! %s!", cell.name);
                        mvprintw(33, 54, "Press enter to start the game!");
                        p = 0;
                /*        getch();
                           update_screen(0);
                            getch();*/
                        break;
                    }
                    mvprintw(32, 54, "INCORECT PASSWORD!!! Please try again!");
                } while (true);
            } 
            else{ 
               fread(&cell, sizeof(cell), 1, fptr);
            }
        }

        if(p){
            mvprintw(32, 54, "                                                                                     ");
            mvprintw(32, 54, "User name not found!");
        }
        fclose(fptr);
    }while(p);
    
    getch();
    return p;

}


int New_user(){
    FILE *fptr;
    pix temp;
    clear();
    echo();
    attron(COLOR_PAIR(2));
    mvprintw(5, 54, "R O G U E    G A M E");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(4));
    mvprintw(6, 58, "NEW USER!!!");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    mvprintw(10, 50, "Please enter your username:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(32, 54, "Press R to return to the previous page");
    attroff(COLOR_PAIR(3));
    int p;
    do{
        p = 1;
        fptr = (fopen("usersinfo.dat","rb+"));
        mvprintw(11, 50, "                                                                  ");
        attron(COLOR_PAIR(3));
        mvscanw(11,50, "%s", temp.name);
        fread(&cell, sizeof(cell), 1, fptr);
        while(!feof(fptr) && p){
            if(!strcmp(temp.name, cell.name)){
                attron(COLOR_PAIR(2));
                mvprintw(32, 54, "WARNING!!! The username you enterd is already taken!");
                attroff(COLOR_PAIR(2));
                p=0;
              //  break;
            } 
            else{ 
               fread(&cell, sizeof(cell), 1, fptr);
            }
        }
    }while(!p);
    fclose(fptr);
    
    mvprintw(32, 54, "                                                                  ");
    attron(COLOR_PAIR(4));
    mvprintw(32, 54, "Hello %s!!!", temp.name);
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    mvprintw(33, 54, "Press R to return to the previous page");
    attroff(COLOR_PAIR(3));
    do{
        p = 1;
        attron(COLOR_PAIR(1));
        mvprintw(13, 50, "please enter your password:");
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(3));
        mvscanw(14, 50, "%s", temp.password);
        attroff(COLOR_PAIR(3));
        if(strlen(temp.password) < 8){
            mvprintw(32, 54, "                                                                  ");
            mvprintw(33, 54, "                                                                  ");
            attron(COLOR_PAIR(2));
            mvprintw(32, 54, "WARNING!!! The password is too short.");
            attroff(COLOR_PAIR(2));
            mvprintw(14, 50, "                                                                  ");
        }
        else{
            p = 0;
        } 
    }while(p);
    do{
        int b = 0, k = 0, a = 0;
        for(int i = 0; i < strlen(temp.password); i++){
            if(temp.password[i] >= 'A' && temp.password[i] <= 'Z'){
                b++;
            }
            if(temp.password[i] >= 'a' && temp.password[i] <= 'z'){
                k++;
            }
            if(temp.password[i] >= '0' && temp.password[i] <= '9'){
                a++;
            }
        }
        if(b > 0 && k > 0 && a > 0){
            mvprintw(30, 54, "                                                                                  ");
            mvprintw(31, 54, "                                                                                  ");
            mvprintw(32, 54, "                                                                                  ");
            attron(COLOR_PAIR(4));
            mvprintw(32, 54, "Your password has been saved successfuly!");
            attroff(COLOR_PAIR(4));
            break;
        }
        if(b == 0){
            mvprintw(14, 50, "                                                                                  ");
            attron(COLOR_PAIR(2));
            mvprintw(30, 54, "INVALID PASSWORD!!! Your password must contain at least one uppercase character");
            attroff(COLOR_PAIR(2));
        }
        if(k == 0){
            mvprintw(14, 50, "                                                                                  ");
            attron(COLOR_PAIR(2));
            mvprintw(31, 54, "INVALID PASSWORD!!! Your password must contain at least one lowercase character");
            attroff(COLOR_PAIR(2));
        }
        if(a == 0){
            mvprintw(14, 50, "                                                                                  ");
            attron(COLOR_PAIR(2));
            mvprintw(32, 54, "INVALID PASSWORD!!! Your password must contain at least one number");
            attroff(COLOR_PAIR(2));
        }
        attron(COLOR_PAIR(3));
        mvscanw(14, 50, "%s", temp.password);
        attroff(COLOR_PAIR(3));
        mvprintw(30, 50, "                                                                                     ");
        mvprintw(31, 50, "                                                                                     ");
        mvprintw(32, 50, "                                                                                      ");
    }while(true);
    attron(COLOR_PAIR(1));
    mvprintw(16, 50, "Please enter your email:");
    attroff(COLOR_PAIR(1));
    do{
        int a = 0, d = 0, m;
        attron(COLOR_PAIR(3));
        mvscanw(17, 50, "%s", temp.email);
        attroff(COLOR_PAIR(3));
        mvprintw(17, 50, "                                                                                     ");
        mvprintw(30, 50, "                                                                                     ");
        mvprintw(31, 50, "                                                                                     ");
        mvprintw(32, 50, "                                                                                     ");
        if(temp.email[strlen(temp.email) - 4] != '.'){
            attron(COLOR_PAIR(2));
            mvprintw(32, 50, "WARNING!!! Invalid email!");
            attroff(COLOR_PAIR(2));
            continue;
        }
        for(int i = 0; i < strlen(temp.email); i++){
            if(temp.email[i] == '@'){
                a++;
                m = i;
            }
            if(temp.email[i] == '.'){
                d++;
            }
        }
        if(a != 1 || d != 1){
            attron(COLOR_PAIR(2));
            mvprintw(32, 50, "WARNING!!! Invalid email!");
            attroff(COLOR_PAIR(2));
            continue;
        }
        
        if(m < 3 || temp.email[m + 1] == '.'){
            attron(COLOR_PAIR(2));
            mvprintw(32, 50, "WARNING!!! Invalid email!");
            attroff(COLOR_PAIR(2));
            continue;
        }
        else{
            attron(COLOR_PAIR(4));
            mvprintw(31, 54, "Congratulations! Your registeration was succesfully completed!");
            mvprintw(32, 54, "Press any key to get back to the previous page");
            attroff(COLOR_PAIR(4));
            break;
        }
    }while(true);
    fptr = (fopen("usersinfo.dat","ab+"));
    fwrite(&temp, sizeof(cell), 1, fptr);
    fclose(fptr);
    getch();
    return 1;
}

//-----------------------------------------------------------------------------------------------------
int Settings(){
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(5, 54, "R O G U E    G A M E");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(4));
    mvprintw(6, 58, "SETTINGS MENUE!!!");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    mvprintw(11, 60, "Choose deficulty:\n");
    mvprintw(13, 65, "Easy\n");
    mvprintw(15, 65, "Normal\n");
    mvprintw(17, 65, "Hard\n");
    mvprintw(19, 60, "Choose color of hero:");
    mvprintw(21, 65, "Red\n");
    mvprintw(23, 65, "Yellow\n");
    mvprintw(25, 65, "White\n");
    mvprintw(27, 65, "Cyan\n");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(32, 54, "Use the up and down keys to move.");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(4));
    mvprintw(13, 61, "**");
    noecho();
    char c = getch();
    int number = 0;
    while(c != 10){
        if(c == 65){
            mvprintw(13 + 2 * number, 61, "  ");
            number = ((number + 7) %8);
            if(13 + 2 * number == 19){
                number--;
            }
            mvprintw(13 + 2 * number, 61, "**");
        }
        else if(c == 66){
            mvprintw(13 + 2 * number, 61, "  ");
            number = (number + 1) % 8;
            if(13 + 2 * number == 19){
                number++;
            }
            mvprintw(13 + 2 * number, 61, "**");
        }
        c = getch();
    }
    number++;
    attroff(COLOR_PAIR(4));
}
//----------------------------------------------------------------------------------------------------------
int Login(){
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(5, 54, "R O G U E    G A M E");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(4));
    mvprintw(6, 58, "LOGIN MENUE!!!");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    mvprintw(11, 60, "New game\n");
    mvprintw(13, 60, "Last game\n");
    mvprintw(15, 60, "Scoreboard\n");
    mvprintw(17, 60, "Settings\n");
    mvprintw(19, 60, "Return to the pervious page");
    mvprintw(21, 60, "Exit\n");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(32, 54, "Use the up and down keys to move.");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(4));
    mvprintw(11, 56, "**");
    noecho();
    char c = getch();
    int number = 0;
    while(c != 10){
        if(c == 65){
            mvprintw(11 + 2 * number, 56, "  ");
            number = ((number + 5) %6);
            mvprintw(11 + 2 * number, 56, "**");
        }
        else if(c == 66){
            mvprintw(11 + 2 * number, 56, "  ");
            number = (number + 1) % 6;
            mvprintw(11 + 2 * number, 56, "**");
        }
        c = getch();
    }
    number++;
    attroff(COLOR_PAIR(4));




    if(number == 1){
        //if(Check_password() == 1){
          //  Main_game(0);
        //}
    Main_game(0);
    
    pix temp;
    int p = 0;
    int b = 1;
    FILE *fptr;
    fptr = (fopen("usersinfo.dat","rb+"));
    fread(&temp, sizeof(cell), 1, fptr);
    while(!feof(fptr) && b){
        if(!strcmp(temp.name, cell.name)){
            b = 0;
        } 
        else{ 
            fread(&temp, sizeof(cell), 1, fptr);
            ++p;
        }
    }
    //--p;
    fseek(fptr,(p * sizeof(cell)), SEEK_SET);
    fwrite(&cell,sizeof(cell), 1,fptr);

    fclose(fptr); 
    
    }








    else if(number == 2){

        //Check_password();
        
        //if(Check_password() == 1){
 /*
            mvprintw(11, 50, "                                                                  ");
            attron(COLOR_PAIR(3));
            //mvscanw(11,50, "%s", tempi.name);
   */       char tempchar[40];
            strcpy(tempchar,cell.name);
            int b = 1;
            int p = 0;
            FILE *fptr;
            fptr = (fopen("usersinfo.dat","rb"));
            fread(&cell, sizeof(cell), 1, fptr);
            while(!feof(fptr) && b){
                if (!strcmp(cell.name,tempchar)){
          //          mvprintw(10,100,"%s",cell.name);
                    b = 0;
                 //   break;
                }               
                else{     
        //            mvprintw(25,100,"%s",cell.name);
                    ++p;
                    fread(&cell, sizeof(cell), 1, fptr);
                }
            }
          //  --p;
            fseek(fptr,(p * sizeof(cell)), SEEK_SET);
            fread(&cell,sizeof(cell),1,fptr);
        //    update_screen(0);
            
               for (int j=0; j < 38; ++j)
                   for(int i=0; i<153; ++i)
                        mvprintw(j , i ,"%c",cell.pixel[0][j][i].font);
      
       // }
   /**/
     //       for(int j = 0; j < 38; j++){
       //         for(int i = 0; i < 153; i++){
                    //cell.pixel[0][j][i].font = 'a';
                    //mvprintw(j, i, "%c", cell.pixel[0][j][i].font);
              //  }
      //      }
            //mvprintw(10, 10, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        
        getch();
    //}
        /*/
         int k = 0;
           int m, n;
            for(int j = 0; j < 38; j++){
                for(int i = 0; i < 153; i++){
                    if(cell.pixel[k][j][i].font == '@'){
                        m = j;
                        n = i;
                        break;
                    }
                }
            }
            update_screen(k);
            mvprintw(m,n,"@");
            char c = getch();
       key(m, n, c, k);
    //----------------------------------------- Writing... ----------------------------------------
/*
    FILE *fptr;
    pix temp;
    int p = 0;

    fptr = (fopen("usersinfo.dat","rb+"));
    fread(&temp, sizeof(cell), 1, fptr);
    while(!feof(fptr)){
        if(!strcmp(temp.name, cell.name)){
            break;
        } 
        else{ 
            fread(&temp, sizeof(cell), 1, fptr);
            ++p;
        }
    }
    fseek(fptr,(p * sizeof(cell)), SEEK_SET);
    fwrite(&cell,sizeof(cell), 1,fptr);
    fclose(fptr); 
        }
    }

*/
    }
    else if(number == 3){

    }
    else if(number == 4){
        Settings();
    }
    else if(number == 5){
        return 5;
    }
    else if(number == 6){
        return 6;
    }
    clear();
}

int main(){
    int k = 0;
    FILE *fptr;
    fptr = (fopen("usersinfo.dat","rb+"));
    if (fptr == NULL){
        fptr = (fopen("usersinfo.dat","wb"));
    }
    for(int j = 0; j < 38; j++){
        for(int i = 0; i < 153; i++){
            cell.pixel[k][j][i].flag = 0;
            cell.pixel[k][j][i].font = ' ';
            
        }
    }
    int i,j,l;
    for (l=0; l<=4; ++l)
      for (j=0; j<38; ++j)
        for (i=0 ; i<153; ++i){
           cell.pixel[l][j][i].font = ' ';
           cell.pixel[l][j][i].flag = 0;
        }
    initscr();
    while(true){
        clear();
        start_color();
        init_color(COLOR_BLACK, 100, 100, 100);
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        bkgd(COLOR_PAIR(1));
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        mvprintw(5, 54, "R O G U E    G A M E");
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(4));
        mvprintw(6, 59, "MAIN MENUE");
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(1));
        mvprintw(17, 60, "New User\n");
        mvprintw(19, 60, "Login\n");
        mvprintw(21, 60, "Play as a guest\n");
        mvprintw(23, 60, "Exit\n");
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(3));
        mvprintw(32, 54, "Use the up and down keys to move.");
        attroff(COLOR_PAIR(3));
        attron(COLOR_PAIR(4));
        mvprintw(17, 56, "**");
        noecho();
        char c = getch();
        int number = 0;
        while(c != 10){
            if(c == 65){
                mvprintw(17 + 2 * number, 56, "  ");
                number = ((number + 3) % 4);
                mvprintw(17 + 2 * number, 56, "**");
            }
            else if(c == 66){
                mvprintw(17 + 2 * number, 56, "  ");
                number = (number + 1) % 4;
                mvprintw(17 + 2 * number, 56, "**");
            }
            c = getch();
        }
        number++;
        attroff(COLOR_PAIR(4));
        if(number == 1){
            if (New_user() == 1){
                Login();
            }
        }
        else if(number == 2){
            int p = Check_password();
            //update_screen(0);
            //getch();
            int a = Login();
            if(a == 6){
                refresh();
                endwin();
                return 0;
            }
            if(a == 5){
                clear();
                continue;
            }
        }
        else if(number == 3){
            Main_game(0);
        }
        else if(number == 4){
            refresh();
            endwin();
            return 0;
        }
        getch();
        refresh();
        endwin();
    }
    return 0;
}
