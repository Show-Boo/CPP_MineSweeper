#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void load_map(char map[][8], string);
bool touch_map(char map[][8], bool is_touched[][8], int row, int col, int* touch_cnt);
void display_map(ostream& fout, char map[][8], bool is_touched[][8]);

void minesweeper(string commands, string output) {
    ifstream fin;
    ofstream fout;
    fin.open(commands);
    fout.open(output);


    const int MINE = -1;
    char map[8][8] = {};
    bool is_touched[8][8] = { false };
    int touch_cnt = 0;

    string str;
    string load_commands;
    string boardtxt;
    string displayy;
    int row;
    int col;

    while (fin >> load_commands) {
        if (load_commands == "load") {
            fin >> boardtxt;
            load_map(map, boardtxt);
            fout << "Command: load " << boardtxt << endl;
        }
        else if (load_commands == "touch") {
            fin >> row;
            fin >> col;
            fout << "Command: touch " << row << " " << col << endl;
            if (touch_map(map, is_touched, row - 1, col - 1, &touch_cnt) == false) {
                break;
            }
        }
        else if (load_commands == "display") {
            fout << "Command: display" << endl;
            for (int m = 0; m < 8; m++) {
                for (int n = 0; n < 8; n++)
                    fout << '.';
                fout << endl;
            }
            fout << endl;
        }
    }
    fout << "Game Over" << endl;
    fout << "~~~~~~~~~" << endl;
    display_map(fout, map, is_touched);
    fout << endl;
    fout << "Spaces touched: " << touch_cnt;

    fout.close();
    fin.close();
}

void load_map(char map[][8], string file) {
    ifstream fin;
    fin.open(file);
    string map_map;
    int i = 0;
    while (fin >> map_map) {
        for (int j = 0; j < 8; j++) {
            map[i][j] = map_map[j];
        }
        i++;
    }
}

bool touch_map(char map[][8], bool is_touched[][8], int row, int col, int* touch_cnt) {
    is_touched[row][col] = true;
    (*touch_cnt)++;
    if (map[row][col] == '*') {
        return false;
    }
    return true;
}

void display_map(ostream& fout, char map[][8], bool is_touched[][8]) {

    int count = 0;

    fout << "Final Board" << endl;;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (is_touched[i][j] == false && map[i][j] == '.') {
                fout << '.';
            }
            if (is_touched[i][j] == false && map[i][j] == '*') {
                fout << "@";
            }
            if (is_touched[i][j] == true && map[i][j] == '*') {
                fout << '*';
            }
            if (is_touched[i][j] == true && map[i][j] == '.') {
                for (int q = i - 1; q <= i + 1; q++) {
                    for (int w = j - 1; w <= j + 1; w++) {
                        if (q < 0 || q >= 8 || w < 0 || w >= 8) {
                            continue;
                        }
                        if (map[q][w] == '*') {
                            count++;
                        }
                    }
                }
                fout << count;
                count = 0;
            }
        }
        fout << endl;
    }

}
