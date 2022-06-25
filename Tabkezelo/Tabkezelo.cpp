#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class fuggvenyek {
public:
    int rowCount, colCount;
    vector<vector<string> > cells;
    vector<vector<string>::iterator > it;
    fuggvenyek() {
        this->rowCount = 1;
        this->colCount = 1;
        this->cells.resize(rowCount, vector<string>(colCount));
        cells[0][0] = " ";

    }
    void print()
    {
        //legszelesebb cella
        int biggest = 0;
        int seged = 0;
        for (int i = 0;i < rowCount;i++) {
            for (int j = 0; j < colCount; j++)
            {
                if (cells[i][j].length() > biggest) {
                    biggest = cells[i][j].length();
                }
            }
        }

        cout << setw(5);
        for (int i = 0; i < colCount; i++) {
            if (i == 0) {
                cout << setw(4);
                cout << "|"  << char(i + 65)  << setw(biggest);
                if (i == colCount - 1)
                {
                    cout << "|";
                }
            }
            
            else {
                
                cout << "|" << char(i + 65) << setw(biggest);
                if (i == colCount - 1)
                {
                    cout << "|";
                }
            }
            
        }
        
        cout << '\n';
        for (int i = 0; i < colCount*(biggest+1); i++) {
            cout << "-";
        }
        cout << "----";
        cout << endl;
        //cout << setw(5) << endl;
        
        for (int i = 0; i < rowCount; i++)
        {
            if (i + 1 >= 10) {
                if (i + 1 >= 100) {
                    cout << i + 1 << "|"  ;
                }
                else cout << i + 1 << " |"   ;
            }
            
            else cout << i + 1 << "  |"  ;
            //cout << "----------------------------------------------";
            //cout << endl;
            for (int j = 0; j < colCount; j++)
            {
                if (j == 0) {
                    if (cells[i][j].length() != biggest) {
                        seged = biggest+1 - cells[i][j].length();
                    }
                    else seged = 0;
                    cout << cells[i][j] << setw(seged);
                }
                else {
                    if (cells[i][j].length() != biggest) {
                        seged = biggest+1 - cells[i][j].length();
                    }
                    else seged = 0;
                    cout << "|" << cells[i][j] << setw(seged);
                }
            }
            cout << "|" << '\n';
            for (int i = 0; i < colCount*(biggest+1); i++) {
                cout << "-";
            }
            cout << "----";
            cout << endl;
            
        }
    }
    /*void beker() {
        cin.ignore();
        for (int i = 0; i < colCount; i++)
        {
            for (int j = 0; j < rowCount; j++)
            {
                cout << "Add meg a(z) " << i + 1 << ". " << j + 1 << ".elemet: ";
                getline(cin, cells[i][j]);
            }
        }
    }*/
    void delRows(int inp) {

        if (cells.size() > inp)
        {
            cells.erase(cells.begin() + inp - 1);
            rowCount--;
        }

        /*for (int i = 0; i < cells.size(); i++) {
            if (i == inp) {
                cells.erase(cells.begin() + i);
                i--;
            }
        }*/
        print();
    }
    void delCols(string inp) {
        char l = inp[0];
        int col = char(l - 65);
        cout << col;
        for (unsigned i = 0; i < cells.size(); ++i) {
            if (cells[i].size() > col) {
                cells[i].erase(cells[i].begin() + col);
            }
        }
        colCount--;
        print();
    }
    void newRows(int number) {

        int newRowCount = number;
        int oldRowCount = rowCount;
        rowCount += newRowCount;
        cells.resize(rowCount);
        for (int i = oldRowCount; i < cells.size(); i++) {
            for (int j = 0; j < colCount; j++)
            {
                cells[i].push_back("a");
            }
        }
        print();
    }
    void newCols(int number) {
        int newColCount = number;
        int oldColCount = colCount;
        colCount += newColCount;
        int i = 0;
        for (auto it : cells)
        {
            for (int j = oldColCount; j < colCount; j++) {
                string temp = "a";
                it.push_back(temp);
            }
            cells[i] = it;
            i++;
            //cout << "";
        }
        for (int i = 0; i < cells.size(); i++)
        {
            cells[i].resize(colCount);
            for (int j = oldColCount; j < colCount; j++) {
                string temp = "a";
            }
        }
        print();
    }
    void edit(int x, int y) {

        string inp;
        cout << "Adja meg az adatot amire megakarja valtoztatni: \n";
        getline(cin, inp);
        cells[y - 1][x] = inp;
        print();
    }
    void newRowsBA(int number, bool isbefore, int row) {
        /*int newRowCount = number;
        int oldRowCount = rowCount;
        rowCount += newRowCount;
        cells.resize(rowCount);*/
        vector<string> tmp(row);

        if (isbefore) {
            for (int j = 0; j < colCount; j++) {
                tmp.push_back("A");
            }
            cells.insert(cells.begin() + number, rowCount, tmp);
            rowCount += number;
            for(int i  = 1; i < rowCount; i++){
                cells[i][0] = "B";
            }
        }
        else {
            
            for (int j = 1; j < colCount; j++) {
                tmp.push_back("A");
            }
            cells.insert(cells.begin() + (number + 1), rowCount, tmp);
            rowCount += number;
            for (int i = 0; i < row; i++) {
                cells[i][0] = "B";
            }

         }


        print();


    }

    void newColsBA(int number, bool isbefore, char col) {
        
        int location = col - 'A';
        if (isbefore) {
            for (int i = 0; i < rowCount; i++) {
                cells[i].insert(cells[i].begin() + location+1, number, "L ");
            }
            colCount += col;
            for (int k = 0; k < col; k++) {
                if (k != 0) {
                    string x(1, 'A' + (k - 1));
                    cells[0][k] = "L" + x;
                }
            }
        }
        else {
            for (int i = 0; i < rowCount; i++) {
                cells[i].insert(cells[i].begin() + (location + 2), number, "L ");
            }
            colCount += col;
            for (int k = 0; k < col; k++) {
                if (k != 0) {
                    string x(1, 'A' + (k - 1));
                    cells[0][k] = "L" + x;
                }
            }
        }
        
        print();

    }
    void CSV_read(string inpfile, char sep) {
        ifstream f(inpfile);
        string sor;
        int counter = 0;
       

        if (f.is_open()) {
            while (getline(f, sor, sep)) {
                counter++;

            }
        }
        else cout << "Could not open the file\n";
        vector<string> tmp(counter);

    }

    void CSV_save(string filename, char sep) {
        ofstream out;
        out.open(filename);
        
        for (int i = 0; i < rowCount; i++)
        {
            for (int j = 0; j < colCount; j++)
            {
                out << cells[i][j] << sep;
            }
            out << "\n";
            
        }
        out.close();
    }
};
int main()
{
    fuggvenyek fv;
    string input;
    fv.print();
    while (input != "exit")
    {
        cout << "Available commands:\n";
        cout << "edit XY\n";
        cout << "add N rows/cols\n";
        cout << "delete X/Y\n";
        cout << "insert N rows/cols before/after X/Y\n";
        cout << "exit\n";
        getline(cin, input);

        if (input.find("print") != string::npos) {
            fv.print();
        }
        //edit



        if (input.find("edit") != string::npos) {
            string xstring = input.substr(5);
            string ystring = input.substr(6);
            char l = xstring[0];
            int truex = char(l - 65);

            int y = stoi(ystring);
            //cout << ystring;
            fv.edit(truex, y);
            //fv.print();
        }


        //add



        if (input.find("add") != string::npos) {
            string strnumber = input.substr(4);
            int number = stoi(strnumber);
            if (input.find("rows") != string::npos) {
                fv.newRows(number);
            }
            if (input.find("cols") != string::npos) {
                fv.newCols(number);
            }
            //fv.print();
        }


        //delete



        if (input.find("delete") != string::npos) {
            string ColOrRow = input.substr(7);

            if (isdigit(ColOrRow[0])) {
                int number = stoi(ColOrRow);

                fv.delRows(number);
            }
            else {
                fv.delCols(ColOrRow);
            }
        }


        //insert



        if (input.find("insert") != string::npos) {
            string strnumber = input.substr(7);
            string XOrY;
            char sep = ';';
            bool isbefore;
            int number = stoi(strnumber);

            if (input.find("before") != string::npos) {
                isbefore = true;
                //XOrY = input.substr(21);
                XOrY = input.back();
                if (isdigit(XOrY[0])) {
                    int col = stoi(XOrY);

                    fv.newRowsBA(number, isbefore, col);
                }
                else {
                    char col2 = XOrY[0];
                    fv.newColsBA(number, isbefore, col2);
                }
            }
            if (input.find("after") != string::npos) {
                isbefore = false;
                //XOrY = input.substr(20);
                XOrY = input.back();
                if (isdigit(XOrY[0])) {
                    int col = stoi(XOrY);
                    fv.newRowsBA(number, isbefore, col);
                }
                else {
                    char col2 = XOrY[0];
                    fv.newColsBA(number, isbefore, col2);
                }
            }


        }

        //2.feladat

        if (input.find("./prog") != string::npos) {
            char sep = ';';
            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
                words.push_back(word);
            }
            string file = words[2];
            string sep1 = words[3];
            if (input.find("-sep") != string::npos) {
                char char_array[1];
                strcpy_s(char_array, sep1.c_str());
                sep = char_array[0];
                fv.CSV_read(file, sep);
            }
            else {
                fv.CSV_read(file, sep);
            }

        }
        if (input.find("save") != string::npos) {
            char sep = ';';
            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            if (input.find("-sep") != string::npos) {
                sep = input.back();
            }
            while (getline(sstream, word, space_char)) {
               // word.erase(std::remove_if(word.begin(), word.end()), word.end());
                words.push_back(word);
            }
            string file = words[1];
            
            
            fv.CSV_save(file, sep);
        }
        
    }
    cout << "Terminated";
    return 0;
}