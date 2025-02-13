#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define COLOR_GOLD 8
#define COLOR_SILVER 9
#define COLOR_BORONZE 10


typedef struct{
	int color;
	char font, location, previous;
    int flag;
    int check;
    int namayesh;
    int healthy;
    int enemyhealth;
    int number;
    int tedad;
}mainpixel;


typedef struct{
    mainpixel pixel[5][38][153];
    char name[40];
    char password[40];
    char email[40];
    int floor;
    int gold;
    int thealthy, tspeed, tdamage;
    int tir, gorz, khanjar, asa, shamshir, foodmajic, foodperfect, mainfood;
    int health, score, exp, gorosneh; 
}pix;

typedef struct{
    char name[40];
    int gold, exp, score;
}score;

int health = 100;

int Main_game(int k);

pix cell;
int M = 0;
int testkey = 0;
int herocolor = 1;
int goldx1 = 0, goldx2 = 0, goldy1 = 0, goldy2 = 0; 
int telesmx1, telesmx2, telesmy1, telesmy2;
time_t start_time;
time_t end_time;
int zarbeh = 5;
int weapon = 1;

int Login();
 

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
			    mvprintw(j, i, "%c", cell.pixel[k][j][i].previous);
            }
            else{
                mvprintw(j, i, ".");
            }
            if(cell.pixel[k][j][i].font == '@'){
                attron(COLOR_PAIR(herocolor));
                mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                attroff(COLOR_PAIR(herocolor));
                attron(COLOR_PAIR(1));
            }
		}
	}
    if (k == 3){
        attron(COLOR_PAIR(5));
        for(int j = goldy1; j <= goldy2; j++){
            for(int i = goldx1; i <= goldx2; i++){
                if(cell.pixel[3][j][i].font != '^')
                    mvprintw(j, i, "%c", cell.pixel[3][j][i].previous);
                else{
                    mvprintw(j, i, ".");
                }
            }
        }
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(1));
    }
    if (k > 0){
        attron(COLOR_PAIR(8));
        for(int j = telesmy1; j <= telesmy2; j++){
            for(int i = telesmx1; i <= telesmx2; i++){
                if(cell.pixel[k][j][i].previous != '^')
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].previous);
                else{
                    mvprintw(j, i, ".");
                }
            }
        }
        attroff(COLOR_PAIR(8));
        attron(COLOR_PAIR(1));
    }
}
//-----------------------------------------harkat hayola--------------------------------

int Harkat(int y, int x, int k){
    /*/
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
    int x1, y1;
    for (int j = m1; j < m2; j++){
        for(int i = n1; i < n2; i++){
            if (cell.pixel[k][j][i].font == '@'){
                x1 = i;
                y1 = j;
            }
        }
    }
    for(int j = m1 + 1; j < m2; j++){
        for(int i = n1 + 1; i < n2; i++){
            if (cell.pixel[k][j][i].font == 'D' || cell.pixel[k][j][i].font == 'F' || 
                cell.pixel[k][j][i].font == 'S'){
                if(x1 > i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
                else if (x1 < i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
                else if (x1 == i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
            }
        }
    }
    */
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
    int x1, y1;
    for (int j = m1; j < m2; j++){
        for(int i = n1; i < n2; i++){
            if (cell.pixel[k][j][i].font == '@'){
                x1 = i;
                y1 = j;
            }
        }
    }
    /*/
    for(int j = m1 + 1; j < m2; j++){
        for(int i = n1 + 1; i < n2; i++){
            if (cell.pixel[k][j][i].font == 'D' || cell.pixel[k][j][i].font == 'F' || 
                cell.pixel[k][j][i].font == 'S'){
                if(x1 > i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i + 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
                else if (x1 < i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i - 1].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
                else if (x1 == i){
                    if (y1 > j){
                        cell.pixel[k][j + 1][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if (y1 < j){
                        cell.pixel[k][j - 1][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                    else if(y1 == j){
                        cell.pixel[k][j][i].font = cell.pixel[k][j][i].font;
                        cell.pixel[k][j][i].font = '.';
                    }
                }
            }
        }
    }

    */

    for(int j = m1; j <= m2; j++){
        for(int i = n1; i <= n2; i++){
            if(cell.pixel[k][j][i].previous != '#' && cell.pixel[k][j][i].previous != '^'){
                mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                if(cell.pixel[k][j][i].font == '@'){
                    attron(COLOR_PAIR(herocolor));
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                    attroff(COLOR_PAIR(herocolor));
                    attron(COLOR_PAIR(1));
                }
                cell.pixel[k][j][i].namayesh = 1;
                if(cell.pixel[k][j][i].previous == '+'){
                    cell.pixel[k][j][i].check = 1;
                }
            }
            if (cell.pixel[k][j][i].previous == '^'){
                mvprintw(j, i, ".");
                cell.pixel[k][j][i].namayesh = 1;
            }
            if(cell.pixel[k][j][i].font == '@'){
                attron(COLOR_PAIR(herocolor));
                mvprintw(j, i, "%c", cell.pixel[k][j][i].previous);
                attroff(COLOR_PAIR(herocolor));
                attron(COLOR_PAIR(1));
            }
        }
    }
    if (k == 3){
        if((x <= goldx2 && x >= goldx1) && (y <= goldy2 && y >= goldy1)){
            attron(COLOR_PAIR(5));
            for(int j = goldy1; j <= goldy2; j++){
                for(int i = goldx1; i <= goldx2; i++){
                    if(cell.pixel[3][j][i].previous != '^')
                        mvprintw(j, i, "%c", cell.pixel[3][j][i].font);
                    else{
                        mvprintw(j, i, ".");
                    }
                }
            }
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(1));
        }
    }
    if (k > 0){
        attron(COLOR_PAIR(8));
        for(int j = telesmy1; j <= telesmy2; j++){
            for(int i = telesmx1; i <= telesmx2; i++){
                if(cell.pixel[k][j][i].font != '^')
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].previous);
                else{
                    mvprintw(j, i, ".");
                }
            }
        }
        attroff(COLOR_PAIR(8));
        attron(COLOR_PAIR(1));
    }
    
    move(37, 152);
}

//----------------------------------------------------rahroh--------------------------
int Rahroh_mahdood(int y, int x, int k){
    if(cell.pixel[k][y + 1][x].font == '+' || cell.pixel[k][y + 1][x].font == '#'){
        mvprintw(y + 1, x, "%c", cell.pixel[k][y + 1][x].font);
        cell.pixel[k][y + 1][x].namayesh = 1;
    }
    if(cell.pixel[k][y + 1][x + 1].font == '+' || cell.pixel[k][y + 1][x + 1].font == '#'){
        mvprintw(y + 1, x + 1, "%c", cell.pixel[k][y + 1][x + 1].font);
        cell.pixel[k][y + 1][x + 1].namayesh = 1;
    }
    if(cell.pixel[k][y + 1][x - 1].font == '+' || cell.pixel[k][y + 1][x - 1].font == '#'){
        mvprintw(y + 1, x - 1, "%c", cell.pixel[k][y + 1][x - 1].font);
        cell.pixel[k][y + 1][x - 1].namayesh = 1;
    }
    if(cell.pixel[k][y - 1][x - 1].font == '+' || cell.pixel[k][y - 1][x - 1].font == '#'){
        mvprintw(y - 1, x - 1, "%c", cell.pixel[k][y - 1][x - 1].font);
        cell.pixel[k][y - 1][x - 1].namayesh = 1;
    }
    if(cell.pixel[k][y - 1][x].font == '+' || cell.pixel[k][y - 1][x].font == '#'){
        mvprintw(y - 1, x, "%c", cell.pixel[k][y - 1][x].font);
        cell.pixel[k][y - 1][x].namayesh = 1;
    }
    if(cell.pixel[k][y - 1][x + 1].font == '+' || cell.pixel[k][y - 1][x + 1].font == '#'){
        mvprintw(y - 1, x + 1, "%c", cell.pixel[k][y - 1][x + 1].font);
        cell.pixel[k][y - 1][x + 1].namayesh = 1;
    }
    if(cell.pixel[k][y][x + 1].font == '+' || cell.pixel[k][y][x + 1].font == '#'){
        mvprintw(y, x + 1, "%c", cell.pixel[k][y][x + 1].font);
        cell.pixel[k][y][x + 1].namayesh = 1;
    }
    if(cell.pixel[k][y][x - 1].font == '+' || cell.pixel[k][y][x - 1].font == '#'){
        mvprintw(y, x - 1, "%c", cell.pixel[k][y][x - 1].font);
        cell.pixel[k][y][x - 1].namayesh = 1;
    }
    move(37, 152);
}
//----------------------------------------DFS----------------------------------------------------

int DFSUG(char c, int damage, int m1, int m2, int n1, int n2 ,int x, int y, int k){
    int count = 0;
    
    for (int j = m1 + 1; j < m2; j++){
        for(int i = n1 + 1; i < n2; i++){
            if (cell.pixel[k][j][i].previous == c){
                if(c == 'U' || c == 'G'){
                    if (cell.pixel[k][j][i].number > 4){
                        count++;
                        break;
                    }
                }
                else if(c == 'D' || c == 'F'){
                    if (cell.pixel[k][j][i].number > 2){
                        count++;
                        break;
                    }
                }
                if (x < i){
                    if (y < j){
                        if (cell.pixel[k][j - 1][i - 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j - 1][i - 1].font != 'O' && cell.pixel[k][j - 1][i - 1].font != 'S' &&
                                cell.pixel[k][j - 1][i - 1].font != 'F' && cell.pixel[k][j - 1][i - 1].font != 'U' &&
                                cell.pixel[k][j - 1][i - 1].font != 'G' && cell.pixel[k][j - 1][i - 1].font != 'D'){
                            cell.pixel[k][j - 1][i - 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j - 1][i - 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j - 1][i - 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j - 1][i - 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                    else if (y > j){
                        if (cell.pixel[k][j + 1][i - 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j + 1][i - 1].font != 'O' && cell.pixel[k][j + 1][i + 1].font != 'S' &&
                                cell.pixel[k][j + 1][i - 1].font != 'F' && cell.pixel[k][j + 1][i + 1].font != 'U' &&
                                cell.pixel[k][j + 1][i - 1].font != 'G' && cell.pixel[k][j + 1][i - 1].font != 'D'){
                            cell.pixel[k][j + 1][i - 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j + 1][i - 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j + 1][i - 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j + 1][i - 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                    else if (y == j){
                        if (cell.pixel[k][j][i - 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j][i - 1].font != 'O' && cell.pixel[k][j][i - 1].font != 'S' &&
                                cell.pixel[k][j][i - 1].font != 'F' && cell.pixel[k][j][i - 1].font != 'U' &&
                                cell.pixel[k][j][i - 1].font != 'G' && cell.pixel[k][j][i - 1].font != 'G'){
                            cell.pixel[k][j][i - 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i - 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j][i - 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j][i - 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                }
                else if (x > i){
                    if (y > j){
                        if (cell.pixel[k][j + 1][i + 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j + 1][i + 1].font != 'O' && cell.pixel[k][j + 1][i + 1].font != 'S' &&
                                cell.pixel[k][j + 1][i + 1].font != 'F' && cell.pixel[k][j + 1][i + 1].font != 'U' &&
                                cell.pixel[k][j + 1][i + 1].font != 'G' && cell.pixel[k][j + 1][i + 1].font != 'D'){
                            cell.pixel[k][j + 1][i + 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j + 1][i + 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j + 1][i + 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j + 1][i + 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                    else if (y < j){
                        if (cell.pixel[k][j - 1][i + 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j - 1][i + 1].font != 'O' && cell.pixel[k][j - 1][i + 1].font != 'S' &&
                                cell.pixel[k][j - 1][i + 1].font != 'F' && cell.pixel[k][j - 1][i + 1].font != 'U' &&
                                cell.pixel[k][j - 1][i + 1].font != 'G' && cell.pixel[k][j - 1][i + 1].font != 'D'){
                            cell.pixel[k][j - 1][i + 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j - 1][i + 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j - 1][i + 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j - 1][i + 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                    if (y == j){
                        if (cell.pixel[k][j][i + 1].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j][i + 1].font != 'O' && cell.pixel[k][j][i + 1].font != 'S' &&
                                cell.pixel[k][j][i + 1].font != 'F' && cell.pixel[k][j][i + 1].font != 'U' &&
                                cell.pixel[k][j][i + 1].font != 'G' && cell.pixel[k][j][i + 1].font != 'D'){
                            cell.pixel[k][j][i + 1].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i + 1].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j][i + 1].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j][i + 1].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                }
                else if(x == i){
                    if (y > j){
                        if (cell.pixel[k][j + 1][i].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j + 1][i].font != 'O' && cell.pixel[k][j + 1][i].font != 'S' &&
                                cell.pixel[k][j + 1][i].font != 'F' && cell.pixel[k][j + 1][i].font != 'U' &&
                                cell.pixel[k][j + 1][i].font != 'G' && cell.pixel[k][j + 1][i].font != 'D'){
                            cell.pixel[k][j + 1][i].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j + 1][i].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j + 1][i].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j + 1][i].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        }
                    }
                    else if (y < j){
                        if (cell.pixel[k][j - 1][i].font == '@'){
                            cell.health -= damage;
                        }
                        else if(cell.pixel[k][j - 1][i].font != 'O' && cell.pixel[k][j - 1][i].font != 'S' &&
                                cell.pixel[k][j - 1][i].font != 'F' && cell.pixel[k][j - 1][i].font != 'U' &&
                                cell.pixel[k][j - 1][i].font != 'G' && cell.pixel[k][j - 1][i].font != 'D'){
                            cell.pixel[k][j - 1][i].font = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j - 1][i].previous = cell.pixel[k][j][i].previous;
                            cell.pixel[k][j][i].previous = '.';
                            cell.pixel[k][j][i].font = '.';
                            cell.pixel[k][j - 1][i].enemyhealth = cell.pixel[k][j][i].enemyhealth;
                            cell.pixel[k][j - 1][i].number = cell.pixel[k][j][i].number + 1;
                            count++;
                            break;
                        } 
                    }
                }
            }
        }
        if(count){
            break;
        }
    }
}




//-------------------------------------------------------------------------------------------------

int partab(int x, int y, int k, char c, int damage, int vahed, char h){
    if (c == '1'){

    }
    if (c == '2'){
        int p = 0;
        for (int i = 1; i <= vahed; i++){
            if (cell.pixel[k][y + i][x].font == 'S' || cell.pixel[k][y + i][x].font == 'G' || 
                cell.pixel[k][y + i][x].font == 'U' || cell.pixel[k][y + i][x].font == 'D' ||
                cell.pixel[k][y + i][x].font == 'F'){
                    cell.pixel[k][y + i][x].enemyhealth -= damage;
                    mvprintw(1, 1, "You hited!");
                    if (cell.pixel[k][y + i][x].enemyhealth <= 0){
                        cell.pixel[k][y + i][x].font = '.';
                        cell.pixel[k][y + i][x].previous = '.';        
                    }
                    p++;
                    break;
            }
            else if(cell.pixel[k][y + i][x].font == 'O' || cell.pixel[k][y + i][x].font == '-'){
                cell.pixel[k][y + i - 1][x].font = h;
                cell.pixel[k][y + i - 1][x].previous = h;
                mvprintw(y + i - 1, x, "%c", h);
                p++;
                break;
            }
        }
        if(!p){
            cell.pixel[k][y + vahed][x].font = h;
            cell.pixel[k][y + vahed][x].previous = h;
            mvprintw(y + vahed, x, "%c", h);
        }
    }
    if (c == '3'){
        
    }
    if (c == '6'){
        int p = 0;
        for (int i = 1; i <= vahed; i++){
            if (cell.pixel[k][y][x + i].font == 'S' || cell.pixel[k][y][x + i].font == 'G' || 
                cell.pixel[k][y][x + i].font == 'U' || cell.pixel[k][y][x + i].font == 'D' ||
                cell.pixel[k][y][x + i].font == 'F'){
                    cell.pixel[k][y][x + i].enemyhealth -= damage;
                    if (cell.pixel[k][y][x + i].enemyhealth <= 0){
                        cell.pixel[k][y][x + i].font = '.';
                        cell.pixel[k][y][x + i].previous = '.';
                        cell.pixel[k][y][x + i].enemyhealth = 0;        
                    }
                    mvprintw(1, 1, "You hited!");
                    p++;
                    break;
            }
            else if(cell.pixel[k][y][x + i - 1].font == 'O' || cell.pixel[k][y][x + i - 1].font == '|'){
                cell.pixel[k][y][x + i - 1].font = h;
                cell.pixel[k][y][x + i - 1].previous = h;
                mvprintw(y, x + i - 1, "%c", h);
                p++;
                break;
            }
        }
        if(!p){
            cell.pixel[k][y][x + vahed].font = h;
            cell.pixel[k][y][x + vahed].previous == h;
            mvprintw(y, x + vahed, "%c", h);
        }
    }
    if (c == '5'){
        
    }
    if (c == '4'){
        int p = 0;
        for (int i = 1; i <= vahed; i++){
            if (cell.pixel[k][y][x - i].font == 'S' || cell.pixel[k][y][x - i].font == 'G' || 
                cell.pixel[k][y][x - i].font == 'U' || cell.pixel[k][y][x - i].font == 'D' ||
                cell.pixel[k][y][x - i].font == 'F'){
                    cell.pixel[k][y][x - i].enemyhealth -= damage;
                    if (cell.pixel[k][y][x - i].enemyhealth <= 0){
                        cell.pixel[k][y][x - i].enemyhealth = 0;
                        cell.pixel[k][y][x - i].font = '.';
                        cell.pixel[k][y][x - i].previous = '.';
                    }
                    mvprintw(1, 1, "You hited!");
                    p++;
                    break;
            }
            else if(cell.pixel[k][y][x - i + 1].font == 'O' || cell.pixel[k][y][x - i + 1].font == '|'){
                cell.pixel[k][y][x - i + 1].font = h;
                cell.pixel[k][y][x - i + 1].previous == h;
                mvprintw(y, x - i + 1, "%c", h);
                p++;
                break;
            }
        }
        if(!p){
            cell.pixel[k][y][x - vahed].font = h;
            cell.pixel[k][y][x - vahed].previous == h;
            mvprintw(y, x - vahed, "%c", h);
        }
    }
    if (c == '7'){
        
    }
    if (c == '8'){
        int p = 0;
        for (int i = 1; i <= vahed; i++){
            if (cell.pixel[k][y - i][x].font == 'S' || cell.pixel[k][y - i][x].font == 'G' || 
                cell.pixel[k][y - i][x].font == 'U' || cell.pixel[k][y - i][x].font == 'D' ||
                cell.pixel[k][y - i][x].font == 'F'){
                    cell.pixel[k][y - i][x].enemyhealth -= damage;
                    if (cell.pixel[k][y - i][x].enemyhealth <= 0){
                        cell.pixel[k][y - i][x].font = '.'; 
                        cell.pixel[k][y - i][x].previous = '.'; 
                        cell.pixel[k][y - i][x].enemyhealth = 0;
                    }
                    mvprintw(1, 1, "You hited!");
                    p++;
                    break;
            }
            else if(cell.pixel[k][y - i][x].font == 'O' || cell.pixel[k][y - i][x].font == '-'){
                cell.pixel[k][y - i + 1][x].font = h;
                cell.pixel[k][y - i + 1][x].previous == h;
                mvprintw(y - i + 1, x, "%c", h);
                p++;
                break;
            }
        }
        if(!p){
            cell.pixel[k][y - vahed][x].font = h;
            cell.pixel[k][y - vahed][x].previous == h;
            mvprintw(y - vahed, x, "%c", h);
        }
    }
    if (c == '9'){

    }
}



//-------------------------------------------KEY----------------------------------------






int key(int y, int x, char c, int k){
    
    if (y < goldy2 && y > goldy2 && x < goldx2 && x > goldx1 && k == 3){
        key(y, x, c, k);
        clear();
        mvprintw (17, 70, "Y O U    W ON!!!");
        getch();
        refresh();
        endwin();
    }
    
    
    
    if (cell.health <= 0){
        return 1;
    }
    cell.health += ((cell.gorosneh - 50) * -1) / 25;
    if(cell.health > health){
        cell.health = health;
    }
    end_time = time(NULL);
    if (end_time - start_time > 1){
        cell.gorosneh++;
        start_time = time(NULL);
        end_time = time(NULL);
    }
    move(37, 152);
    noecho();
    mvprintw(1, 1, "                                                                         ");
    move(37, 152);
    if (k == 3 && (x >= goldx1 && x <= goldx2) && (y >= goldy1 && y < goldy2)){
        attron(COLOR_PAIR(5));
    }
    if (k > 0 && (x >= telesmx1 && x <= telesmx2) && (y >= telesmy1 && y < telesmy2)){
        attron(COLOR_PAIR(8));
    }
    else{
        attron(COLOR_PAIR(1));

    }




    
    int p = 0;



    if(c == '1'){
        p++;
        if (cell.pixel[k][y + 1][x - 1].flag != 0 && cell.pixel[k][y + 1][x - 1].font != '|' &&
            cell.pixel[k][y + 1][x - 1].font != '-' && cell.pixel[k][y + 1][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y + 1][x - 1].previous == '+' && cell.pixel[k][y + 1][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x - 1].check = 1;
                    mahdood_room(y + 1, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y + 1;
            x = x - 1;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y, x - 1, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '2'){
        p++;
        if (cell.pixel[k][y + 1][x].flag != 0 && cell.pixel[k][y + 1][x].font != '|' && 
            cell.pixel[k][y + 1][x].font != '-' && cell.pixel[k][y + 1][x].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y + 1][x].previous == '+' && cell.pixel[k][y + 1][x].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x].check = 1;
                    mahdood_room(y + 2, x, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y + 1;
            x = x;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y + 1, x, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '3'){
        p++;
        if (cell.pixel[k][y + 1][x + 1].flag != 0 && cell.pixel[k][y + 1][x + 1].font != '|' && 
            cell.pixel[k][y + 1][x + 1].font != '-' && cell.pixel[k][y + 1][x + 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y + 1][x + 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y + 1][x + 1].previous == '+' && cell.pixel[k][y + 1][x + 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y + 1][x + 1].check = 1;
                    mahdood_room(y + 1, x + 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y + 1;
            x = x + 1;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y, x + 1, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '4'){
        p++;
        if (cell.pixel[k][y][x - 1].flag != 0 && cell.pixel[k][y][x - 1].font != '|' && 
            cell.pixel[k][y][x - 1].font != '-' && cell.pixel[k][y][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y][x - 1].previous == '+' && cell.pixel[k][y][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y][x - 1].check = 1;
                    mahdood_room(y, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y;
            x = x - 1;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y, x - 1, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '6'){ 
        p++;
        if (cell.pixel[k][y][x + 1].flag != 0 && cell.pixel[k][y][x + 1].font != '|' && 
            cell.pixel[k][y][x + 1].font != '-' && cell.pixel[k][y][x + 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y][x + 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y][x + 1].previous == '+' && cell.pixel[k][y][x + 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y][x + 1].check = 1;
                    mahdood_room(y, x + 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y;
            x = x + 1;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y, x + 1, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '7'){
        p++;
        if (cell.pixel[k][y - 1][x - 1].flag != 0 && cell.pixel[k][y - 1][x - 1].font != '|' && 
            cell.pixel[k][y - 1][x - 1].font != '-' && cell.pixel[k][y - 1][x - 1].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y - 1][x - 1].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y - 1][x - 1].previous == '+' && cell.pixel[k][y - 1][x - 1].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y - 1][x - 1].check = 1;
                    mahdood_room(y - 1, x - 2, k);
                    mvprintw(1, 1, "New Room!");
            }
            y = y - 1;
            x = x - 1;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y, x - 1, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(4));
        }
    }
    else if(c == '8'){
        p++;
        if (cell.pixel[k][y - 1][x].flag != 0 && cell.pixel[k][y - 1][x].font != '|' && 
            cell.pixel[k][y - 1][x].font != '-' && cell.pixel[k][y - 1][x].font != 'O'){
            cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
            cell.pixel[k][y - 1][x].font = '@';
            mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
            //cell.pixel[k][y][x].namayesh = 1;
            if (cell.pixel[k][y - 1][x].previous == '+' && cell.pixel[k][y - 1][x].check == 0 && 
                cell.pixel[k][y][x].previous == '#'){
                    cell.pixel[k][y - 1][x].check = 1;
                    mahdood_room(y - 2, x, k);
                    mvprintw(1, 1, "New Room!");
            }
            
            y = y - 1;
            x = x;
            if (cell.pixel[k][y][x].namayesh == 1)
            Harkat(y - 1, x, k);
            attron(COLOR_PAIR(herocolor));
            mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
            attroff(COLOR_PAIR(herocolor));
            attron(COLOR_PAIR(1));
        }
    }
    else if(c == '9'){
        p++;
        if (cell.pixel[k][y - 1][x + 1].flag != 0 && cell.pixel[k][y - 1][x + 1].font != '|' && 
            cell.pixel[k][y - 1][x + 1].font != '-' && cell.pixel[k][y - 1][x + 1].font != 'O'){
                cell.pixel[k][y][x].font = cell.pixel[k][y][x].previous;
                cell.pixel[k][y - 1][x + 1].font = '@';
                mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
                //cell.pixel[k][y][x].namayesh = 1;
                if (cell.pixel[k][y - 1][x + 1].previous == '+' && cell.pixel[k][y - 1][x + 1].check == 0 && 
                    cell.pixel[k][y][x].previous == '#'){
                        cell.pixel[k][y - 1][x + 1].check = 1;
                        mahdood_room(y - 1, x + 2, k);
                        -//Harkat(y - 1, x + 1, y - 1, x + 2, k);
                        mvprintw(1, 1, "New Room!");
                }
                
                y = y - 1;
                x = x + 1;
                if (cell.pixel[k][y][x].namayesh == 1)
                Harkat(y, x + 1, k);
                attron(COLOR_PAIR(herocolor));
                mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
                attroff(COLOR_PAIR(herocolor));
                attron(COLOR_PAIR(1));
        }
    }
    else if(c == 'S'){
        int number = 0;
        char s;
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(5, 54, "R O G U E    G A M E");
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(4));
        mvprintw(6, 58, "SPELL MENUE!!!");
        attroff(COLOR_PAIR(4));
        mvprintw(8, 30, "Spells name:");
        mvprintw(8, 90, "Spells number:");
        mvprintw(10, 34, "Health spell");
        mvprintw(10, 94, "%d", cell.thealthy);
        mvprintw(12, 34, "Damage spell");
        mvprintw(12, 94, "%d", cell.tdamage);
        mvprintw(14, 34, "Speed spell");
        mvprintw(14, 94, "%d", cell.tspeed);
        mvprintw(33, 54, "Press R to resume the game!");    
        while(s != 'R'){
        attron(COLOR_PAIR(4));
        mvprintw(2 * number + 10, 30, "**");
        noecho();
            if(s == 65){
                mvprintw(10 + 2 * number, 30, "  ");
                number = ((number + 2) % 3);
                mvprintw(10 + 2 * number, 30, "**");
                attroff(COLOR_PAIR(4));
            }
            else if(s == 66){
                mvprintw(10 + 2 * number, 30, "  ");
                number = (number + 1) % 3;
                mvprintw(10 + 2 * number, 30, "**");
                attroff(COLOR_PAIR(4));
            }
            else if(s == '5'){
                attroff(COLOR_PAIR(4));
                if(number == 0 && cell.thealthy > 0){
                    cell.thealthy--;
                    mvprintw(10, 94, "%d", cell.thealthy);
                }
                if(number == 1 && cell.tdamage > 0){
                    cell.tdamage--;
                    mvprintw(12, 94, "%d", cell.tdamage);
                }
                if(number == 2 && cell.tspeed > 0){
                    cell.tspeed--;
                    mvprintw(14, 94, "%d", cell.tspeed);
                }
            }
            move(37, 152);
            attroff(COLOR_PAIR(4));
            s = getch();
        }
        for(int j = 0; j < 38; j++){
            for(int i = 0; i < 153; i++){
                mvprintw(j, i, " ");
                if (cell.pixel[k][j][i].namayesh == 1){
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                }
            }
        }
        c = getch();
        key(y, x, c, k);
    }
    
    else if(c == 'i'){
        int number = 0;
        char s;
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(5, 54, "R O G U E    G A M E");
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(4));
        mvprintw(6, 58, "SPELL MENUE!!!");
        attroff(COLOR_PAIR(4));
        mvprintw(8, 10, "WEAPON name:");
        mvprintw(8, 125, "Weapon number:");
        mvprintw(8, 45, "Symbol:");
        mvprintw(8, 68, "Range:");
        mvprintw(8, 95, "Damage:");
        mvprintw(10, 12, "Short-range weapon:");
        for(int i = 0; i < 153; i++){
            mvprintw(11, i, "-");
        }
        mvprintw(12, 14, "Mace");
        mvprintw(12, 127, "Owened!");

        mvprintw(14, 14, "Sword");
        if (cell.shamshir > 0){
            mvprintw(14, 127, "Owened!");
        }
        else{
            mvprintw(14, 127, "Not owened!");
        }
        for(int i = 0; i < 153; i++){
            mvprintw(15, i, "-");
        }
        
        mvprintw(18, 12, "Long-range weapon:");
        for(int i = 0; i < 153; i++){
            mvprintw(19, i, "-");
        }
        mvprintw(20, 14, "Dagger");
        mvprintw(20, 130, "%d", cell.khanjar);
        mvprintw(22, 14, "Majic Wand");
        mvprintw(22, 130, "%d", cell.asa);
        mvprintw(24, 14, "Normal Arrow");
        mvprintw(24, 130, "%d", cell.tir);
        mvprintw(12, 97, "5");
        mvprintw(14, 97, "10");
        mvprintw(20, 97, "12");
        mvprintw(22, 97, "15");
        mvprintw(24, 97, "5");
        mvprintw(12, 70, "Nearby houses");
        mvprintw(14, 70, "Nearby houses");
        mvprintw(20, 70, "5 houses");
        mvprintw(22, 70, "10 houses");
        mvprintw(24, 70, "5 houses");
        mvprintw(12, 47, "g");
        mvprintw(14, 47, "s");
        mvprintw(20, 47, "k");
        mvprintw(22, 47, "a");
        mvprintw(24, 47, "t");
        for(int i = 0; i < 153; i++){
            mvprintw(25, i, "-");
        }
        mvprintw(33, 54, "Press enter to resume the game!");
        while(s != 'R'){
            attron(COLOR_PAIR(1));
            mvprintw (32, 60, "                                                                 ");
            if(s == 'g' && weapon != 1){
                if (weapon == 0){
                    zarbeh = 5;
                    weapon = 1;
                    mvprintw(32, 60, "You got Mace succesfuly!");
                }
                else{
                    mvprintw(32, 60, "You must put your last weapon firt");
                }
            }
            if (s == 'g' && weapon == 1){
                weapon = 0;
                mvprintw(32, 60, "You put Mace succesfuly!");
            }
            if(s == 's'){
                if (cell.shamshir > 0 && weapon != 2){
                    if (weapon == 0){
                        mvprintw(12, 127, "Owened!");
                        zarbeh = 10;
                        weapon = 2;
                        mvprintw(32, 60, "You got Sword succesfuly!");
                    }
                    else{
                        mvprintw(32, 60, "You must put your last weapon firt");
                    }
                }
                else if (cell.shamshir > 0 && weapon == 2){
                    weapon = 0;
                    mvprintw(32, 60, "You put Sword succesfuly!");
                }
                else{
                    mvprintw(32, 60, "You don't have Sword!");
                }
            }
            if (s == 'k'){
                if(cell.khanjar > 0 && weapon != 3){
                    if (weapon == 0){
                        cell.khanjar--;
                        zarbeh = 12;
                        weapon = 3;
                        mvprintw(20, 130, "%d", cell.khanjar);
                        mvprintw(32, 60, "You got Dagger succesfuly!");
                    }
                    else{
                        mvprintw(32, 60, "You must put your last weapon firt");
                    }
                }
                else if (cell.khanjar > 0 && weapon == 3){
                    weapon = 0;
                    mvprintw(32, 60, "You put Dagger succesfuly!");
                }
                else{
                    mvprintw(32, 60, "You don't have Dagger!");
                }
            }
            if(s == 'a'){
                if(cell.asa > 0 && weapon != 4){
                    if (weapon == 0){
                        cell.asa--;
                        zarbeh = 15;
                        weapon = 4;
                        mvprintw(22, 130, "%d", cell.asa);
                        mvprintw(32, 60, "You got Majic Wand succesfuly!");
                    }
                    else{
                        mvprintw(32, 60, "You must put your last weapon firt");
                    }
                }
                else if (cell.asa > 0 && weapon == 4){
                    weapon = 0;
                    mvprintw(32, 60, "You put Majic Wand succesfuly!");
                }
                else{
                    mvprintw(32, 60, "You don't have Majic Wand!");
                }
            }
            if (s == 't'){
                if(cell.tir > 0 && weapon != 5){
                    if (weapon == 0){
                        cell.tir--;
                        zarbeh = 5;
                        weapon = 5;
                        mvprintw(24, 130, "%d", cell.tir);
                        mvprintw(32, 60, "You got Normal Arrow succesfuly!");
                    }
                    else{
                        mvprintw(32, 60, "You must put your last weapon firt");
                    }
                }
                else if (cell.tir > 0 && weapon == 5){
                    weapon = 0;
                    mvprintw(32, 60, "You put Normal Arrow succesfuly!");
                }

                else{
                    mvprintw(32, 60, "You don't have Normal Arrow!");
                }
            }
        move(37, 152);
        attroff(COLOR_PAIR(4));
        s = getch();
        }
        for(int j = 0; j < 38; j++){
            for(int i = 0; i < 153; i++){
                mvprintw(j, i, " ");
                if (cell.pixel[k][j][i].namayesh == 1){
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                }
            }
        }
        c = getch();
        key(y, x, c, k);
    }

    else if(c == 'E'){
        int number = 0;
        char s;
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(5, 54, "R O G U E    G A M E");
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(4));
        mvprintw(6, 58, "FOODS MENUE!!!");
        attroff(COLOR_PAIR(4));
        mvprintw(8, 30, "Fodd name:");
        mvprintw(8, 90, "food number:");
        mvprintw(10, 34, "Normal food");
        mvprintw(10, 94, "%d", cell.mainfood);
        mvprintw(12, 34, "Majic food");
        mvprintw(12, 94, "%d", cell.foodmajic);
        mvprintw(14, 34, "Perfect food");
        mvprintw(14, 94, "%d", cell.foodperfect);
        mvprintw(33, 54, "Press enter to resume the game!");
        mvprintw(32, 15, "                                                                                                                 ");
        while(s != 'R'){
        attron(COLOR_PAIR(4));
        mvprintw(2 * number + 10, 30, "**");
        noecho();
            if(s == 65){
                mvprintw(10 + 2 * number, 30, "  ");
                number = ((number + 2) % 3);
                mvprintw(10 + 2 * number, 30, "**");
                attroff(COLOR_PAIR(4));
            }
            else if(s == 66){
                mvprintw(10 + 2 * number, 30, "  ");
                number = (number + 1) % 3;
                mvprintw(10 + 2 * number, 30, "**");
                attroff(COLOR_PAIR(4));
            }
            else if(s == '5'){
                if (cell.gorosneh > 0){
                    attroff(COLOR_PAIR(4));
                    int te = 0;
                    if(number == 0 && cell.mainfood > 0){
                        te++;
                        cell.mainfood--;
                        //cell.health++;
                        mvprintw(10, 94, "%d", cell.mainfood);

                    }
                    if(number == 1 && cell.foodmajic > 0){
                        te++;
                        //cell.foodmajic--;
                        mvprintw(12, 94, "%d", cell.foodmajic);
                        cell.health++;
                        cell.foodmajic--;
                    }
                    if(number == 2 && cell.foodperfect > 0){
                        te++;
                        cell.foodperfect--;
                        cell.health++;
                        mvprintw(14, 94, "%d", cell.foodperfect);
                    }
                    if(te){
                        cell.gorosneh -= 5;
                        start_time = time(NULL);
                        if(cell.gorosneh < 0){
                            cell.gorosneh = 0;
                        }
                        if(cell.gorosneh > 100){
                            cell.gorosneh = 100;
                        }
                    }
                }
                else{
                    mvprintw(31, 60, "You are full");
                }
            }
            attron(COLOR_PAIR(1));
            mvprintw(32, 15, "                                                                                                                 ");
            mvprintw(32, 15, "Hunger level [");
            for(int i = 30; i < cell.gorosneh + 30; i++){
                mvprintw(32, i, "#");
            }
            for(int i = cell.gorosneh + 30; i < 130; i++){
                mvprintw(32, i, ".");
            }
            mvprintw(32, 130, "]");
            move(37, 152);
            attroff(COLOR_PAIR(4));
            s = getch();
        }
        for(int j = 0; j < 38; j++){
            for(int i = 0; i < 153; i++){
                mvprintw(j, i, " ");
                if (cell.pixel[k][j][i].namayesh == 1){
                    mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                }
            }
        }
        
        c = getch();
        key(y, x, c, k);
    }
//--------------------------------------------------------weapon----------------------------------------------------------
    else if (c == 32){
        if (weapon == 1){
            if (cell.pixel[k][y + 1][x + 1].font == 'D' || cell.pixel[k][y + 1][x + 1].font == 'F' || 
                cell.pixel[k][y + 1][x + 1].font == 'U' || cell.pixel[k][y + 1][x + 1].font == 'S' ||
                cell.pixel[k][y + 1][x + 1].font == 'G'){
                    if (cell.pixel[k][y + 1][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'U'){
                        cell.health -= 25;
                    }

                    cell.pixel[k][y + 1][x + 1].enemyhealth -= 5;
                    if (cell.pixel[k][y + 1][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x + 1].font = '.';
                        cell.pixel[k][y + 1][x + 1].previous = '.';
                        cell.pixel[k][y + 1][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x + 1, "%c", cell.pixel[k][y + 1][x + 1].font);
            }
            if (cell.pixel[k][y][x + 1].font == 'D' || cell.pixel[k][y][x + 1].font == 'F' || 
                cell.pixel[k][y][x + 1].font == 'U' || cell.pixel[k][y][x + 1].font == 'S' ||
                cell.pixel[k][y][x + 1].font == 'G'){
                    
                    if (cell.pixel[k][y][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y][x + 1].enemyhealth -= 5;
                    if (cell.pixel[k][y][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y][x + 1].font = '.';
                        cell.pixel[k][y][x + 1].previous = '.';
                        cell.pixel[k][y][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y, x + 1, "%c", cell.pixel[k][y][x + 1].font);
            }
            if (cell.pixel[k][y + 1][x].font == 'D' || cell.pixel[k][y + 1][x].font == 'F' || 
                cell.pixel[k][y + 1][x].font == 'U' || cell.pixel[k][y + 1][x].font == 'S' ||
                cell.pixel[k][y + 1][x].font == 'G'){
                    
                    if (cell.pixel[k][y + 1][x].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y + 1][x].enemyhealth -= 5;
                    if (cell.pixel[k][y + 1][x].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x].font = '.';
                        cell.pixel[k][y + 1][x].previous = '.';
                        cell.pixel[k][y + 1][x].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x, "%c", cell.pixel[k][y + 1][x].font);
            }
            if (cell.pixel[k][y - 1][x + 1].font == 'D' || cell.pixel[k][y - 1][x + 1].font == 'F' || 
                cell.pixel[k][y - 1][x + 1].font == 'U' || cell.pixel[k][y - 1][x + 1].font == 'S' ||
                cell.pixel[k][y - 1][x + 1].font == 'G'){
                    
                    if (cell.pixel[k][y - 1][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y - 1][x + 1].enemyhealth -= 5;
                    if (cell.pixel[k][y - 1][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x + 1].font = '.';
                        cell.pixel[k][y - 1][x + 1].previous = '.';
                        cell.pixel[k][y - 1][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x + 1, "%c", cell.pixel[k][y - 1][x + 1].font);
            }
            if (cell.pixel[k][y - 1][x - 1].font == 'D' || cell.pixel[k][y - 1][x - 1].font == 'F' || 
                cell.pixel[k][y - 1][x - 1].font == 'U' || cell.pixel[k][y - 1][x - 1].font == 'S' ||
                cell.pixel[k][y - 1][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y - 1][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y - 1][x - 1].enemyhealth -= 5;
                    if (cell.pixel[k][y - 1][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x - 1].font = '.';
                        cell.pixel[k][y - 1][x - 1].previous = '.';
                        cell.pixel[k][y - 1][x - 1].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x - 1, "%c", cell.pixel[k][y - 1][x - 1].font);
            }
            if (cell.pixel[k][y - 1][x].font == 'D' || cell.pixel[k][y - 1][x].font == 'F' || 
                cell.pixel[k][y - 1][x].font == 'U' || cell.pixel[k][y - 1][x].font == 'S' ||
                cell.pixel[k][y - 1][x].font == 'G'){
                   
                    if (cell.pixel[k][y - 1][x].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'U'){
                        cell.health -= 25;
                    }
                   
                    cell.pixel[k][y - 1][x].enemyhealth -= 5;
                    if (cell.pixel[k][y - 1][x].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x].font = '.';
                        cell.pixel[k][y - 1][x].previous = '.';
                        cell.pixel[k][y - 1][x].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x, "%c", cell.pixel[k][y - 1][x].font);
            }
            if (cell.pixel[k][y + 1][x - 1].font == 'D' || cell.pixel[k][y + 1][x - 1].font == 'F' || 
                cell.pixel[k][y + 1][x - 1].font == 'U' || cell.pixel[k][y + 1][x - 1].font == 'S' ||
                cell.pixel[k][y + 1][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y + 1][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y + 1][x - 1].enemyhealth -= 5;
                    if (cell.pixel[k][y + 1][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x - 1].font = '.';
                        cell.pixel[k][y + 1][x - 1].previous = '.';
                        cell.pixel[k][y + 1][x - 1].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x - 1, "%c", cell.pixel[k][y + 1][x - 1].font);
            }
            if (cell.pixel[k][y][x - 1].font == 'D' || cell.pixel[k][y][x - 1].font == 'F' || 
                cell.pixel[k][y][x - 1].font == 'U' || cell.pixel[k][y][x - 1].font == 'S' ||
                cell.pixel[k][y][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y][x + 1].enemyhealth -= 5;
                    if (cell.pixel[k][y][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y][x - 1].font = '.';
                        cell.pixel[k][y][x - 1].previous = '.';
                        cell.pixel[k][y][x - 1].enemyhealth = 0;
                    }
                mvprintw(y, x - 1, "%c", cell.pixel[k][y][x - 1].font);
            }
        }
        if (weapon == 2){
            if (cell.pixel[k][y + 1][x + 1].font == 'D' || cell.pixel[k][y + 1][x + 1].font == 'F' || 
                cell.pixel[k][y + 1][x + 1].font == 'U' || cell.pixel[k][y + 1][x + 1].font == 'S' ||
                cell.pixel[k][y + 1][x + 1].font == 'G'){
                    if (cell.pixel[k][y + 1][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x + 1].font == 'U'){
                        cell.health -= 25;
                    }

                    cell.pixel[k][y + 1][x + 1].enemyhealth -= 10;
                    if (cell.pixel[k][y + 1][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x + 1].font = '.';
                        cell.pixel[k][y + 1][x + 1].previous = '.';
                        cell.pixel[k][y + 1][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x + 1, "%c", cell.pixel[k][y + 1][x + 1].font);
            }
            if (cell.pixel[k][y][x + 1].font == 'D' || cell.pixel[k][y][x + 1].font == 'F' || 
                cell.pixel[k][y][x + 1].font == 'U' || cell.pixel[k][y][x + 1].font == 'S' ||
                cell.pixel[k][y][x + 1].font == 'G'){
                    
                    if (cell.pixel[k][y][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y][x + 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y][x + 1].enemyhealth -= 10;
                    if (cell.pixel[k][y][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y][x + 1].font = '.';
                        cell.pixel[k][y][x + 1].previous = '.';
                        cell.pixel[k][y][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y, x + 1, "%c", cell.pixel[k][y][x + 1].font);
            }
            if (cell.pixel[k][y + 1][x].font == 'D' || cell.pixel[k][y + 1][x].font == 'F' || 
                cell.pixel[k][y + 1][x].font == 'U' || cell.pixel[k][y + 1][x].font == 'S' ||
                cell.pixel[k][y + 1][x].font == 'G'){
                    
                    if (cell.pixel[k][y + 1][x].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y + 1][x].enemyhealth -= 10;
                    if (cell.pixel[k][y + 1][x].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x].font = '.';
                        cell.pixel[k][y + 1][x].previous = '.';
                        cell.pixel[k][y + 1][x].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x, "%c", cell.pixel[k][y + 1][x].font);
            }
            if (cell.pixel[k][y - 1][x + 1].font == 'D' || cell.pixel[k][y - 1][x + 1].font == 'F' || 
                cell.pixel[k][y - 1][x + 1].font == 'U' || cell.pixel[k][y - 1][x + 1].font == 'S' ||
                cell.pixel[k][y - 1][x + 1].font == 'G'){
                    
                    if (cell.pixel[k][y - 1][x + 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x + 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y - 1][x + 1].enemyhealth -= 10;
                    if (cell.pixel[k][y - 1][x + 1].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x + 1].font = '.';
                        cell.pixel[k][y - 1][x + 1].previous = '.';
                        cell.pixel[k][y - 1][x + 1].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x + 1, "%c", cell.pixel[k][y - 1][x + 1].font);
            }
            if (cell.pixel[k][y - 1][x - 1].font == 'D' || cell.pixel[k][y - 1][x - 1].font == 'F' || 
                cell.pixel[k][y - 1][x - 1].font == 'U' || cell.pixel[k][y - 1][x - 1].font == 'S' ||
                cell.pixel[k][y - 1][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y - 1][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y - 1][x - 1].enemyhealth -= 10;
                    if (cell.pixel[k][y - 1][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x - 1].font = '.';
                        cell.pixel[k][y - 1][x - 1].previous = '.';
                        cell.pixel[k][y - 1][x - 1].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x - 1, "%c", cell.pixel[k][y - 1][x - 1].font);
            }
            if (cell.pixel[k][y - 1][x].font == 'D' || cell.pixel[k][y - 1][x].font == 'F' || 
                cell.pixel[k][y - 1][x].font == 'U' || cell.pixel[k][y - 1][x].font == 'S' ||
                cell.pixel[k][y - 1][x].font == 'G'){
                   
                    if (cell.pixel[k][y - 1][x].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y - 1][x].font == 'U'){
                        cell.health -= 25;
                    }
                   
                    cell.pixel[k][y - 1][x].enemyhealth -= 10;
                    if (cell.pixel[k][y - 1][x].enemyhealth <= 0){
                        cell.pixel[k][y - 1][x].font = '.';
                        cell.pixel[k][y - 1][x].previous = '.';
                        cell.pixel[k][y - 1][x].enemyhealth = 0;
                    }
                    mvprintw(y - 1, x, "%c", cell.pixel[k][y - 1][x].font);
            }
            if (cell.pixel[k][y + 1][x - 1].font == 'D' || cell.pixel[k][y + 1][x - 1].font == 'F' || 
                cell.pixel[k][y + 1][x - 1].font == 'U' || cell.pixel[k][y + 1][x - 1].font == 'S' ||
                cell.pixel[k][y + 1][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y + 1][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y + 1][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y + 1][x - 1].enemyhealth -= 10;
                    if (cell.pixel[k][y + 1][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y + 1][x - 1].font = '.';
                        cell.pixel[k][y + 1][x - 1].previous = '.';
                        cell.pixel[k][y + 1][x - 1].enemyhealth = 0;
                    }
                    mvprintw(y + 1, x - 1, "%c", cell.pixel[k][y + 1][x - 1].font);
            }
            if (cell.pixel[k][y][x - 1].font == 'D' || cell.pixel[k][y][x - 1].font == 'F' || 
                cell.pixel[k][y][x - 1].font == 'U' || cell.pixel[k][y][x - 1].font == 'S' ||
                cell.pixel[k][y][x - 1].font == 'G'){
                    
                    if (cell.pixel[k][y][x - 1].font == 'D'){
                        cell.health -= 5;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'F'){
                        cell.health -= 10;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'G'){
                        cell.health -= 15;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'S'){
                        cell.health -= 20;
                    }
                    if (cell.pixel[k][y][x - 1].font == 'U'){
                        cell.health -= 25;
                    }
                    
                    cell.pixel[k][y][x + 1].enemyhealth -= 10;
                    if (cell.pixel[k][y][x - 1].enemyhealth <= 0){
                        cell.pixel[k][y][x - 1].font = '.';
                        cell.pixel[k][y][x - 1].previous = '.';
                        cell.pixel[k][y][x - 1].enemyhealth = 0;
                    }
                mvprintw(y, x - 1, "%c", cell.pixel[k][y][x - 1].font);
            }
        }
        if (weapon == 3){
            char h = getch();
            partab(x, y, k, h, 12, 5, 'k');
            c = getch();
            key(x, y, c, k);
            return 1;
        }
        if (weapon == 4){
            char h = getch();
            partab(x, y, k, h, 15, 10, 'a');
            c = getch();
            key(x, y, c, k);
            return 1;
        }
        if (weapon == 5){
            char h = getch();
            partab(x, y, k, h, 5, 5, 't');
            c = getch();
            key(x, y, c, k);
            return 1;
        }
    }

//------------------------------------------------------------------------------------------------------------------------
    if (k == 3){
        if((x <= goldx2 && x >= goldx1) && (y <= goldy2 && y >= goldy1)){
            attron(COLOR_PAIR(5));
            for(int j = goldy1; j <= goldy2; j++){
                for(int i = goldx1; i <= goldx2; i++){
                    if(cell.pixel[3][j][i].font != '^')
                        mvprintw(j, i, "%c", cell.pixel[3][j][i].font);
                    else{
                        mvprintw(j, i, ".");
                    }
                }
            }
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(1));
        }
    }
    if(p){
        int m1 = y, n1 = x, m2 = y, n2 = x;
        if (cell.pixel[k][y][x].previous != '+' && cell.pixel[k][y][x].font != '|' &&
            cell.pixel[k][y][x].font != '-' && cell.pixel[k][y][x].previous != '#'){
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
            int count = 0;
            DFSUG('D', 5, m1, m2, n1, n2, x, y, k);
            DFSUG('S', 20, m1, m2, n1, n2, x, y, k);
            DFSUG('F', 10, m1, m2, n1, n2, x, y, k);
            DFSUG('G', 15, m1, m2, n1, n2, x, y, k);
            DFSUG('U', 25, m1, m2, n1, n2, x, y, k);
        }
        attron(COLOR_PAIR(1));
        for(int j = m1; j <= m2; j++){
            for (int i = n1; i <= n2; i++){
                if (cell.pixel[k][j][i].font == '@'){
                    attron(COLOR_PAIR(herocolor));
                }
                mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                if (cell.pixel[k][j][i].font == '@'){
                    attroff(COLOR_PAIR(herocolor));
                }
            }
        }
        attroff(COLOR_PAIR(1));
    }
//-------------------------------------------------------------------------------------- 
    
    
    if(c == 27) {        
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
                cell.thealthy++;
            }
            if(cell.pixel[k][y][x].flag == 13){
                cell.tdamage++;
            }
            if(cell.pixel[k][y][x].flag == 14){
                cell.tspeed++;
            }
      //      mvprintw(y, x, "%c", cell.pixel[k][y][x].previous);
        //    mvprintw(y, x, "%c", cell.pixel[k][y][x].font);
       
            //f = getch();
        }
        else{
      //      key_show(y, x, f, k);
       }
    }

//----------------------------------------------------score---------------------------------------------------

    cell.score += 2 * cell.gold;

//--------------------------------------------------------------------------------------------------------------
    if(cell.pixel[k][y][x].previous == 't'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            if (cell.pixel[k][y][x].tedad == 1){
                cell.tir += 20;
            }
            if (cell.pixel[k][y][x].tedad == 0){
                cell.tir++;
            }
        }
    }
    if(cell.pixel[k][y][x].previous == 'a'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            if (cell.pixel[k][y][x].tedad == 1){
                cell.asa += 15;
            }
            if (cell.pixel[k][y][x].tedad == 0){
                cell.asa++;
            }
        }
    }
    if(cell.pixel[k][y][x].previous == 's'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            cell.shamshir++;
        }
    }
    if(cell.pixel[k][y][x].previous == 'k'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            cell.pixel[k][y][x].previous = '.';
            if (cell.pixel[k][y][x].tedad == 1){
                cell.khanjar += 10;
            }
            if (cell.pixel[k][y][x].tedad == 0){
                cell.khanjar++;
            }
        }
    }
    if(cell.pixel[k][y][x].previous == 'f'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            if ((cell.foodmajic + cell.foodperfect + cell.mainfood) < 6){    
                cell.pixel[k][y][x].previous = '.';
                cell.mainfood++;
            }
            else{
                mvprintw(1, 1, "You don't have enough espace in your backpack for new food");
            }
        }
    }
    if(cell.pixel[k][y][x].previous == 'm'){
        f = getch();
        move(37, 152);
        if(f == '5'){
            if((cell.foodmajic + cell.foodperfect + cell.mainfood) < 6){
                cell.pixel[k][y][x].previous = '.';
                cell.foodmajic++;
                //f = getch();
            }
            else{
                mvprintw(1, 1, "You don't have enough espace in your backpack for new food");
            }
        }
    }
    if(cell.pixel[k][y][x].previous == 'p'){
        f = getch();
        move(37, 152);
        if(f == '5' && (cell.foodmajic + cell.foodperfect + cell.mainfood) < 6){
            if ((cell.foodmajic + cell.foodperfect + cell.mainfood) < 6){
                cell.pixel[k][y][x].previous = '.';
                cell.foodperfect++;
            }
            else{
                mvprintw(1, 1, "You don't have enough espace in your backpack for new food");
            }
        }
    }
    if(cell.pixel[k][y][x].previous == '<'){
        f = getch();
        if(f == '5'){
            Main_game(k + 1);
        }
    }

    move(37, 152);
    int point = 1;
    if(c == 'M'){
        M++;
        if(M % 2){
            point = 1;
            update_screen(k);
        }
        //right
        else{
            for(int j = 0; j < 38; j++){
                for(int i = 0; i < 153; i++){
                    mvprintw(j, i, " ");
                    if (cell.pixel[k][j][i].namayesh == 1){
                        mvprintw(j, i, "%c", cell.pixel[k][j][i].font);
                        //mvprintw(j, i, "1");
                        point = 0;
                    }
                }
            }
        }
        
    }
    Rahroh_mahdood(y, x, k);
    c = getch();

    
    move(37, 152);
    if(cell.pixel[k][y][x].previous == '^'){
        attron(COLOR_PAIR(1));
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
        attroff(COLOR_PAIR(1));
        key(75, 20, c, k);
    }
    mvprintw(34, 10, "                                                   ");
    mvprintw(34, 10, "GOLD: %d", cell.gold);
    mvprintw(34, 40, "Health: %d", cell.health);
    move(37, 152);
    attroff(COLOR_PAIR(4));
    
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
                int randomi = Random_number(1, 4);
                if(randomi == 1){
                    cell.pixel[k][j][i].font = 'k';
                    cell.pixel[k][j][i].flag = 16;
                }
                if(randomi == 2){
                    cell.pixel[k][j][i].font = 'a';
                    cell.pixel[k][j][i].flag = 17;
                }
                if(randomi == 3){
                    cell.pixel[k][j][i].font = 't';
                    cell.pixel[k][j][i].flag = 18;
                }
                if(randomi == 4){
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
                    cell.pixel[k][j][i].font = 'f';
                    cell.pixel[k][j][i].flag = 15;
                }
                if(randomi == 2){
                    cell.pixel[k][j][i].font = 'm';
                    cell.pixel[k][j][i].flag = 16;
                }
                if(randomi == 3){
                    cell.pixel[k][j][i].font = 'p';
                    cell.pixel[k][j][i].flag = 17;
                }
                if(randomi == 4){
                    cell.pixel[k][j][i].font = 'f';
                    cell.pixel[k][j][i].flag = 18;
                }
            }
        }
    }
    for (int i = ax + 1; i < bx; i++){
        for (int j = ay + 1; j < by; j++){
            int random = Random_number(1, 40) / 40;
            if (random){
                int randomi = Random_number(1, 5);
                if (randomi == 1){
                    cell.pixel[k][j][i].font = 'F';
                    cell.pixel[k][j][i].flag = 30;
                    cell.pixel[k][j][i].enemyhealth = 10;
                }
                if (randomi == 2){
                    cell.pixel[k][j][i].font = 'D';
                    cell.pixel[k][j][i].flag = 31;
                    cell.pixel[k][j][i].enemyhealth = 5;
                }
                if (randomi == 3){
                    cell.pixel[k][j][i].font = 'G';
                    cell.pixel[k][j][i].flag = 32;
                    cell.pixel[k][j][i].enemyhealth = 15;
                }
                if (randomi == 4){
                    cell.pixel[k][j][i].font = 'S';
                    cell.pixel[k][j][i].flag = 33;
                    cell.pixel[k][j][i].enemyhealth = 20;
                }
                if (randomi == 5){
                    cell.pixel[k][j][i].font = 'U';
                    cell.pixel[k][j][i].flag = 34;
                    cell.pixel[k][j][i].enemyhealth = 30;
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

int gold_room(int y, int x){
    int m1, m2, n1, n2;

    for(int j = y; j < 37; j++){
        if(cell.pixel[3][j][x].previous == '-' || cell.pixel[3][j][x].previous == '+'){
            m2 = j;
            break;
        }
    }
    for(int j = y; j > 0; j--){
        if(cell.pixel[3][j][x].previous == '-' || cell.pixel[3][j][x].previous == '+'){
            m1 = j;
            break;
        }
    }
    for(int i = x; i < 153; i++){
        if(cell.pixel[3][y][i].previous == '|' || cell.pixel[3][y][i].previous == '+'){
            n2 = i;
            break;
        }
    }
    for(int i = x; i > 0; i--){
        if(cell.pixel[3][y][i].previous == '|' || cell.pixel[3][y][i].previous == '+'){
            n1 = i;
            break;
        }
    }
    for(int j = m1 + 1; j < m2; j++){
        for(int i = n1 + 1; i < n2; i++){
            int randomg = Random_number(1, 2) / 2;
            int randomt = Random_number(1, 2) / 2;
            int randomB = Random_number(1, 3) / 3;
            if(randomg){
                if(randomB){
                    cell.pixel[3][j][i].font = 'B';
                    cell.pixel[3][j][i].previous = 'B';
                    cell.pixel[3][j][i].flag = 12;
                }
                else{
                    cell.pixel[3][j][i].font = '$';
                    cell.pixel[3][j][i].previous = '$';
                    cell.pixel[3][j][i].flag = 11;
                }
            }
            else if(randomt){
                cell.pixel[3][j][i].font = '^';
                cell.pixel[3][j][i].previous = '^';
                cell.pixel[3][j][i].flag = 7;
            }
            else{
                cell.pixel[3][j][i].font = '.';
                cell.pixel[3][j][i].previous = '.';
                cell.pixel[3][j][i].flag = 0;
            }
        }
    }
    goldx1 = n1;
    goldx2 = n2;
    goldy1 = m1;
    goldy2 = m2;
}


int telesm_room(int y, int x, int k){
    int m1, m2, n1, n2;

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
    for(int j = m1 + 1; j < m2; j++){
        for(int i = n1 + 1; i < n2; i++){
            int randomt = Random_number(1, 5) / 5;
            if(!randomt){
                cell.pixel[k][j][i].font = 'T';
                cell.pixel[k][j][i].previous = 'T';
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
    telesmx1 = n1;
    telesmx2 = n2;
    telesmy1 = m1;
    telesmy2 = m2;
}


int Main_game(int k){
    for (int j = 0; j < 38; ++j){
        for(int i = 0; i < 153; ++i){
            cell.pixel[k][j][i].font = ' ';
            cell.pixel[k][j][i].check = 0;
            cell.pixel[k][j][i].flag = 0;
            cell.pixel[k][j][i].location = ' ';
            cell.pixel[k][j][i].namayesh = 0;
            cell.pixel[k][j][i].previous = ' ';
        }
    }   

    
    cell.floor = k;
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
    if (k == 3){
        do{
            int randomx = Random_number(0, 152);
            int randomy = Random_number(0, 37);
            if(cell.pixel[3][randomy][randomx].font == '.'){
                gold_room(randomy, randomx);
                break;
            }
        }while(true);
    }
    if (k > 0){
        int randomt = Random_number(1, 5) / 5;
        if(!randomt){
            telesm_room(m, n, k);
        }
    }
    mvprintw(m, n, "@");
    move(37, 152);
    noecho();
    if(k < 3){
        int m1 = m, n1 = n, m2 = m, n2 = n;
        for(int j = m; j < 37; j++){
            if(cell.pixel[k][j][n].previous == '-' || cell.pixel[k][j][n].previous == '+'){
                m2 = j;
                break;
            }
        }
        for(int j = m; j > 0; j--){
            if(cell.pixel[k][j][n].previous == '-' || cell.pixel[k][j][n].previous == '+'){
                m1 = j;
                break;
            }
        }
        for(int i = n; i < 153; i++){
            if(cell.pixel[k][m][i].previous == '|' || cell.pixel[k][m][i].previous == '+'){
                n2 = i;
                break;
            }
        }
        for(int i = n; i > 0; i--){
            if(cell.pixel[k][m][i].previous == '|' || cell.pixel[k][m][i].previous == '+'){
                n1 = i;
                break;
            }
        }
        int randomx, randomy;
        do
        {
            randomx = Random_number(0, 152);
            randomy = Random_number(0, 37);
            if (cell.pixel[k][randomy][randomx].font != '.'){
                continue;
            }
            else{
                if ((randomx < n2 && randomx > n1) && (randomy < m2 && randomy > m1)){
                    continue;
                }
                else{
                    break;
                }
            }
        } while (true);
        cell.pixel[k][randomy][randomx].font = '<';
        cell.pixel[k][randomy][randomx].previous = '<';
        cell.pixel[k][randomy][randomx].namayesh = 0;
        cell.pixel[k][randomy][randomx].flag = 20;
    }
    
    
    
    for(int j = 0; j < 38; j++){
        for(int i = 0; i < 153; i++){
            mvprintw(j, i, " ");
        }
    }
    start_time = time(NULL);
    end_time = time(NULL);
    mahdood_room(m, n, k);
    char c = getch();
    key(m , n, c, k);
        
    FILE *fptr;
    pix temp;
    int pp = 0;
    int bb = 1;
    fptr = (fopen("usersinfo.dat","rb+"));
    fread(&temp, sizeof(pix), 1, fptr);
    while(!feof(fptr) &&  bb){
        if(!strcmp(temp.name, cell.name)){
            bb = 0;;
        } 
        else{ 
            fread(&temp, sizeof(pix), 1, fptr);
            pp = pp + 1;
            }
    }
    fseek(fptr,(pp * sizeof(pix)), SEEK_SET);
    fwrite(&cell,sizeof(pix), 1,fptr);
    fclose(fptr);     
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
        mvscanw(11,50, "%s", cell.name);
        fread(&temp, sizeof(temp), 1, fptr);
        while(!feof(fptr) && p){
            if(!strcmp(temp.name, cell.name)){
                attron(COLOR_PAIR(2));
                mvprintw(32, 54, "WARNING!!! The username you enterd is already taken!");
                attroff(COLOR_PAIR(2));
                p=0;
              
            } 
            else{ 
               fread(&temp, sizeof(temp), 1, fptr);
            }
        }
    }while(!p);
    fclose(fptr);
    
    mvprintw(32, 54, "                                                                  ");
    attron(COLOR_PAIR(4));
    mvprintw(32, 54, "Hello %s!!!", cell.name);
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
        mvscanw(14, 50, "%s", cell.password);
        attroff(COLOR_PAIR(3));
        if(strlen(cell.password) < 8){
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
        for(int i = 0; i < strlen(cell.password); i++){
            if(cell.password[i] >= 'A' && cell.password[i] <= 'Z'){
                b++;
            }
            if(cell.password[i] >= 'a' && cell.password[i] <= 'z'){
                k++;
            }
            if(cell.password[i] >= '0' && cell.password[i] <= '9'){
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
        mvscanw(14, 50, "%s", cell.password);
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
        mvscanw(17, 50, "%s", cell.email);
        attroff(COLOR_PAIR(3));
        mvprintw(17, 50, "                                                                                     ");
        mvprintw(30, 50, "                                                                                     ");
        mvprintw(31, 50, "                                                                                     ");
        mvprintw(32, 50, "                                                                                     ");
        if(cell.email[strlen(cell.email) - 4] != '.'){
            attron(COLOR_PAIR(2));
            mvprintw(32, 50, "WARNING!!! Invalid email!");
            attroff(COLOR_PAIR(2));
            continue;
        }
        for(int i = 0; i < strlen(cell.email); i++){
            if(cell.email[i] == '@'){
                a++;
                m = i;
            }
            if(cell.email[i] == '.'){
                d++;
            }
        }
        if(a != 1 || d != 1){
            attron(COLOR_PAIR(2));
            mvprintw(32, 50, "WARNING!!! Invalid email!");
            attroff(COLOR_PAIR(2));
            continue;
        }
        
        if(m < 3 || cell.email[m + 1] == '.'){
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
    fwrite(&cell, sizeof(cell), 1, fptr);
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
    mvprintw(11, 60, "Choose defficulty:\n");
    mvprintw(13, 65, "Easy\n");
    mvprintw(15, 65, "Normal\n");
    mvprintw(17, 65, "Hard\n");
    mvprintw(19, 60, "Choose color of hero:");
    mvprintw(21, 65, "Blue\n");
    mvprintw(23, 65, "Gold\n");
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
    do{
        while(c != '5'){
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
        if(number == 1){
            cell.health = 100;
        }
        if(number == 2){
            cell.health = 75;
        }
        if(number == 3){
            cell.health = 50;
        }
        if(number == 5){
            herocolor = 7;
        }
        if(number == 6){
            herocolor = 5;
        }
        if(number == 7){
            herocolor = 3;
        }
        if(number == 8){
            herocolor = 4;
        }
        health = cell.health;
        c = getch();
    }while(c != 'R');
    mvprintw(33, 60, "Difficulty changed");
    mvprintw(33, 90, "%d", number);
    getch();
    attroff(COLOR_PAIR(4));
    Login();
}
//-------------------------------------------------scoreboard----------------------------------------------

int Scoreboard(){
    int i,j;
    pix temp;
    score userscore[100];
    score tempscore;
    FILE *fptr;

    int count = 0;
    fptr = (fopen("usersinfo.dat","rb"));
    
    fread(&temp, sizeof(temp), 1, fptr);
    while(!feof(fptr)){        
        userscore[count].exp = temp.exp;
        userscore[count].gold = temp.gold;
        userscore[count].score = temp.score;
        strcpy(userscore[count].name , temp.name);
        count++;       
               
        fread(&temp, sizeof(temp), 1, fptr);    
    }
    for (i = 99; i > 0 ; --i){
        for (j = 0; j < i; ++j){
            if (userscore[j].score < userscore[j+1].score){ 
                tempscore = userscore[j];
                userscore[j] = userscore[j+1];
                userscore[j+1] = tempscore;
            }
        }    
    }
    fclose(fptr);
    char s;
    int p = 0;
    int number = 0;
    do{
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(5, 54, "R O G U E    G A M E");
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(4));
        mvprintw(6, 58, "SCOREBOARD!!!");
        attroff(COLOR_PAIR(4));
        attron(A_BOLD);
        mvprintw(8, 15, "Username:");
        mvprintw(8, 50, "Gold:");
        mvprintw(8, 85, "Experience:");
        mvprintw(8, 120, "Score:");
        attroff(A_BOLD);

        attron(COLOR_PAIR(3));
        if (s == 65){
            number--;
        }
        if(s == 66){
            number++;
        }
        if(number >= 0){
            for(int i = 0; i < 10; i++){
                if(i + 10 * number < count){
                    if (i + 10 * number == 0){
                        attron(A_BOLD);
                        attron(COLOR_PAIR(5));
                        mvprintw(10, 5, "GOAT ->");
                        mvprintw((10 + i * 2), 13, "%d.", number * 10 + i + 1);
                        mvprintw(10 + i * 2, 17, "%s                               ", userscore[i + 10 * number].name);
                            if(!strcmp(userscore[i + 10 * number].name, cell.name)){
                            for(int j = 0; j < 152; j++){
                                mvprintw((9 + i * 2), j, "-");
                                mvprintw((11 + i * 2), j, "-");
                            }
                        }
                        attroff(COLOR_PAIR(5));
                        attron(COLOR_PAIR(3));
                        attroff(A_BOLD);
                    }
                    else if (i + 10 * number == 1){
                        attron(A_BOLD);
                        attron(COLOR_PAIR(7));
                        mvprintw(12, 5, "KING ->");
                        mvprintw((10 + i * 2), 13, "%d.", number * 10 + i + 1);
                        mvprintw(10 + i * 2, 17, "%s                               ", userscore[i + 10 * number].name);
                        if(!strcmp(userscore[i + 10 * number].name, cell.name)){
                            for(int j = 0; j < 152; j++){
                                mvprintw((9 + i * 2), j, "-");
                                mvprintw((11 + i * 2), j, "-");
                            }
                        }
                        attroff(COLOR_PAIR(7));
                        attron(COLOR_PAIR(3));
                        attroff(A_BOLD);
                    }
                    else if (i + 10 * number == 2){
                        attron(A_BOLD);
                        attron(COLOR_PAIR(8));
                        mvprintw(14, 5, "BOSS ->");
                        mvprintw((10 + i * 2), 13, "%d.", number * 10 + i + 1);
                        mvprintw(10 + i * 2, 17, "%s                               ", userscore[i + 10 * number].name);
                        if(!strcmp(userscore[i + 10 * number].name, cell.name)){
                            for(int j = 0; j < 152; j++){
                                mvprintw((9 + i * 2), j, "-");
                                mvprintw((11 + i * 2), j, "-");
                            }
                        }
                        attroff(COLOR_PAIR(8));
                        attron(COLOR_PAIR(3));
                        attroff(A_BOLD);
                    }
                    else{
                        mvprintw((10 + i * 2), 13, "%d.", number * 10 + i + 1);
                        mvprintw(10 + i * 2, 17, "%s                               ", userscore[i + 10 * number].name);
                        if(!strcmp(userscore[i + 10 * number].name, cell.name)){
                            for(int j = 0; j < 152; j++){
                                mvprintw((9 + i * 2), j, "-");
                                mvprintw((11 + i * 2), j, "-");
                            }
                        }
                    }
                }
                else{
                    mvprintw(10 + i * 2, 13, "                                      ");
                }
            }
            for(int i = 0; i < 10; i++){
                if(i + 10 * number < count){
                    mvprintw(10 + i * 2, 52, "%d                 ", userscore[i + 10 * number].gold);
                }
                else
                    mvprintw(10 + i * 2, 52, "                     ");
            }
            for(int i = 0; i < 10; i++){
                if(i + 10 * number < count){
                    mvprintw(10 + i * 2, 87, "%d                   ", userscore[i + 10 * number].exp);
                }
                else
                    mvprintw(10 + i * 2, 87, "                     ");
            }
            for(int i = 0; i < 10; i++){
                if(i + 10 * number < count){
                    mvprintw(10 + i * 2, 122, "%d                   ", userscore[i + 10 * number].score);
                }
                else
                    mvprintw(10 + i * 2, 122, "                     ");
            }
        }
        if(number >= count / 10){
            mvprintw(33, 50, "End of the list!");
        }
        s = getch();
    }while(s != 'R');
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));
    getch();
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
        cell.exp++;
        Main_game(0);
    
    }

    else if(number == 2){
        cell.exp++;

        int m, n;
        for (int j = 0; j < 37; j++){
            for (int i = 0; i < 153; i++){
                if (cell.pixel[cell.floor][j][i].font == '@'){
                    m = j;
                    n = i;
                }
            }
        }

        clear();

        mvprintw(m, n, "@");
        move(37, 152);
        noecho();
        
        start_time = time(NULL);
        end_time = time(NULL);

        mahdood_room(m, n, cell.floor);
        char c = getch();
        key(m , n, c, cell.floor);

        FILE *fptr;
        pix temp;
        int pp = 0;
        int bb = 1;
        fptr = (fopen("usersinfo.dat","rb+"));
        fread(&temp, sizeof(pix), 1, fptr);
        while(!feof(fptr) &&  bb){
            if(!strcmp(temp.name, cell.name)){
                bb = 0;;
            } 
            else{ 
                fread(&temp, sizeof(pix), 1, fptr);
                pp = pp + 1;
                }
        }
        fseek(fptr,(pp * sizeof(pix)), SEEK_SET);
        fwrite(&cell,sizeof(pix), 1,fptr);
        fclose(fptr);    
        return 6;    
    }

    else if(number == 3){
        Scoreboard();
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
//----------------------------------------------------------------------------------------
int main(){
    int k = 0;
    FILE *fptr;
    fptr = (fopen("usersinfo.dat","rb+"));
    if (fptr == NULL){
        fptr = (fopen("usersinfo.dat","wb"));
    }

    for (int l = 0; l <= 4; ++l)
      for (int j = 0; j < 38; ++j)
        for (int i = 0 ; i < 153; ++i){
           cell.pixel[l][j][i].font = ' ';
           cell.pixel[l][j][i].flag = 0;
           cell.pixel[l][j][i].namayesh = 0;
           cell.pixel[l][j][i].enemyhealth = 0;
           cell.pixel[l][j][i].number = 0;
           cell.pixel[l][j][i].tedad = 1;
    }
    cell.thealthy = 0, cell.tspeed = 0, cell.tdamage = 0;
    cell.tir = 0, cell.gorz = 0, cell.khanjar = 0, cell.asa = 0, cell.shamshir = 0, cell.mainfood = 0;
    cell.foodmajic = 0, cell.foodperfect = 0; 
    cell.health = 100, cell.gold = 0, cell.score = 0, cell.exp = 0;
    cell.gorosneh = 0;
    initscr();
    while(true){
        clear();
        start_color();
        init_color(COLOR_BLACK, 100, 100, 100);
        init_color(COLOR_GOLD, 1000, 843, 0);
        init_color(COLOR_SILVER, 900, 900, 900);
        init_color(COLOR_BORONZE, 804, 498, 796);
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_GOLD, COLOR_BLACK);
        init_pair(6, COLOR_SILVER, COLOR_BLACK);
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
        init_pair(8, COLOR_BORONZE, COLOR_BLACK);
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
            int a = 0;
            if (New_user() == 1){
                a = Login();
   
            }
            if (a == 6){
                char c = getch();
                do{
                clear();
                mvprintw(17, 70, "G A M E    O V E R ...");
                c = getch();
                refresh();
                }while(c != 27);
                endwin();
                return 0;
            }
        }
        else if(number == 2){
            int p = Check_password();

            int a = Login();

            if(a == 6){
                /*
                do{
                clear();
                mvprintw(17, 70, "G A M E    O V E R ...");
                c = getch();
                refresh();
                }while(c != 27);*/
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
            testkey = 1;
            Main_game(0);
            testkey = 0;
            refresh();
            endwin();
            return 0;
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