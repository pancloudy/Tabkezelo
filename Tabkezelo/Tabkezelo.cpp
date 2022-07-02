#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

using namespace std;

class fuggvenyek {
public:
    int rowCount, colCount;
    vector<vector<string> > cells;
    vector<vector<string> > alignment;
    vector<vector<string>::iterator > it;
    fuggvenyek() {
        this->rowCount = 1;
        this->colCount = 1;
        this->cells.resize(rowCount, vector<string>(colCount));
        this->alignment.resize(rowCount, vector<string>(colCount));
        cells[0][0] = " ";
        alignment[0][0] = " ";

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
                    alg();
                    if (alignment[i][j] == "right") {
                        cout << setw(seged) << cells[i][j];
                    }
                    else cout << cells[i][j] << setw(seged);
                }
                else {
                    if (cells[i][j].length() != biggest) {
                        seged = biggest+1 - cells[i][j].length();
                    }
                    else seged = 0;
                    alg();
                    if (alignment[i][j] == "right") {
                        cout << "|" << setw(seged) << cells[i][j];
                    }
                    else cout << "|" << cells[i][j] << setw(seged);
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


    void alg() {
        //alignment.resize( rowCount, vector<string>(colCount));
        alignment.resize(rowCount);
        for (int i = 0; i < cells.size(); i++)
        {
            alignment[i].resize(colCount);

        }
        for (int i = 0; i < rowCount; i++)
        {
            for (int j = 1; j < colCount; j++)
            {
                if (alignment[i][j] == "") {
                    alignment[i][j] = "left";
                   
                 }
                
            }
            

        }
    }

   
    void delRows(int inp) {

        if (cells.size() > inp)
        {
            cells.erase(cells.begin() + inp - 1);
            rowCount--;
        }
        print();
    }
    void delCols(char inp) {
        char l = inp;
        int col = char(l - 65);
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
                cells[i].push_back("");
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
                string temp = "";
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
                string temp = "";
            }
        }
        print();

    }
    void edit(int x, int y, string inp) {
        cells[y - 1][x] = inp;
        print();
    }
    void newRowsBA(int number, bool isbefore, int row) {
        vector<string> tmp(row);

        if (isbefore) {
            for (int j = 0; j < colCount; j++) {
                tmp.push_back("");
            }
            cells.insert(cells.begin() + (row-1), number, tmp);
            rowCount += number;
            
        }
        else {
            
            for (int j = 1; j < colCount; j++) {
                tmp.push_back("");
            }
            cells.insert(cells.begin() + (row), number, tmp);
            rowCount += number;
            

         }


        print();


    }

    void newColsBA(int number, bool isbefore, char col) {
        
        int location = col - 'A';
        if (isbefore) {
            for (int i = 0; i < rowCount; i++) {
                cells[i].insert(cells[i].begin() + location-1, number, "");
            }
            colCount += number;
            for (int k = 0; k < colCount; k++) {
                if (k != 0) {
                    cells[0][k] = "";
                }
            }
        }
        else {
            for (int i = 0; i < rowCount; i++) {
                cells[i].insert(cells[i].begin() + location+1, number, "");
            }
            colCount += number;
            for (int k = 0; k < colCount; k++) {
                if (k != 0) {
                    cells[0][k] = "";
                }
            }
        }
        
        print();

    }
    void CSV_read(string inpfile, char sep) {
        cells.clear();
        alignment.clear();
        vector<string> row;
        string line, word;
        int icounter = 0;
        int jcounter = 0;
        int jmax = 0;


        fstream file(inpfile, ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                jcounter = row.size();
                if (jcounter > jmax) {
                    jmax = jcounter;

                }
                row.clear();
                icounter++;
                stringstream str(line);

                while (getline(str, word, sep))
                    row.push_back(word);

                cells.push_back(row);
                jcounter++;
            }
        }
        else
            cout << "Could not open the file\n";

        rowCount += icounter-1;
        cells.resize(rowCount);
        
        colCount += jmax-1;
        for (int i = 0; i < cells.size(); i++)
        {
            cells[i].resize(colCount);

        }


        print();
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

    void Swap(int x1, int y1, int  x2, int y2) {
        string temp;
        temp = cells[y1-1][x1];
        cells[y1-1][x1] = cells[y2-1][x2];
        cells[y2-1][x2] = temp;
        print();
    }

    void RowSort(string rows, string ascod) {
        int row = stoi(rows);
        if (ascod == "asc") {
            /*for (int i = 0;i < rowCount;i++) {
                for (int j = 0;j < rowCount;i++) {

                }
            }*/

        }
        else {

        }
    }
    void ColSort(string col, string ascod) {
        if (ascod == "asc") {
            std::sort(cells.begin(), cells.end());
        }
        else {

        }
    }

    void Align(int x, int y, string direction) {
        if (direction == "left") {
            alignment[x-1][y] = "left";
        }
        else {
            alignment[x-1][y] = "right";
        }
        
    }

};
int main(int argc, char** argv)
{
    fuggvenyek fv;
    string input;
    fv.print();
    while (input != "exit")
    {
        /*cout << "Available commands:\n";
        cout << "edit XY\n";
        cout << "add N rows/cols\n";
        cout << "delete X/Y\n";
        cout << "insert N rows/cols before/after X/Y\n";
        cout << "exit\n";*/
        getline(cin, input);
        

        
        
        //edit



        if (input.find("edit") != string::npos) {
            

            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {

                words.push_back(word);
            }
            string inp = words[2];
            string ystring = input.substr(6);
            if (words.size() == 3) {
                if (isdigit(ystring[0])) {


                    string xstring = input.substr(5);

                    char l = toupper(xstring[0]);
                    int truex = char(l - 65);

                    int y = stoi(ystring);
                    fv.edit(truex, y, inp);
                }
                else cout << "error\n";
            }
            else cout << "error\n";
            //fv.print();
        }


        //add



        if (input.find("add") != string::npos) {
           

            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }

            string strnumber = input.substr(4);
            if (words.size() == 3) {
                if (isdigit(strnumber[0])) {


                    int number = stoi(strnumber);
                    if (input.find("rows") != string::npos) {
                        fv.newRows(number);
                    }
                    if (input.find("cols") != string::npos) {
                        fv.newCols(number);
                    }
                }
                else cout << "error\n";
            }
            else cout << "error\n";
        }


        //delete



        if (input.find("delete") != string::npos) {

            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }

            if (words.size() == 2) {
                string ColOrRow = input.substr(7);
                if (isdigit(ColOrRow[0])) {
                    int number = stoi(ColOrRow);

                    fv.delRows(number);
                }
                else {
                    
                    fv.delCols(toupper(ColOrRow[0]));
                }
            }
            else cout << "error\n";
        }


        //insert



        if (input.find("insert") != string::npos) {
            

            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }


            if (words.size() == 5) {
                string strnumber = input.substr(7);
                if (isdigit(strnumber[0])) {


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
                else cout << "error";
            }
            else cout << "error\n";

        }

        //2.feladat

        if (input.find("./prog") != string::npos) {
            char sep = ';';
            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }
            string file = words[1];
            if (words.size() == 2 || words.size() == 4) {
                if (input.find("-sep") != string::npos) {
                    string sep1 = words[2];
                    char char_array[1];
                    strcpy(char_array, sep1.c_str());
                    sep = char_array[0];
                    fv.CSV_read(file, sep);
                }
                else {
                    fv.CSV_read(file, sep);
                }
            }
            else cout << "error\n";

        }
        if (input.find("save") != string::npos) {
            int maxattr = 2;
            
            char sep = ';';
            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }
            if (words.size() == 2 || words.size() == 4) {
                if (input.find("-sep") != string::npos) {
                    sep = input.back();
                }
                string file = words[1];


                fv.CSV_save(file, sep);
            }
            else{

                cout << "error\n";
                
            }
            
            
        }


        //sort

        if (input.find("sort") != string::npos) {
            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {
                words.push_back(word);
            }

            string xory = words[3];
            
            if (words.size() == 3) {
                if (isdigit(xory[0])) {
                    fv.RowSort(xory, "asc");
                }
                else fv.ColSort(xory, "asc");
            }
            if (words.size() == 4) {
                string ascOrdesc = words[4];
                
                if (isdigit(xory[0])) {
                    fv.RowSort(xory, ascOrdesc);
                }
                else fv.ColSort(xory, ascOrdesc);
            }
            else cout << "error\n";
        }

        //swap

        if (input.find("swap") != string::npos) {
            

            char space_char = ' ';
            vector<string> words{};
            stringstream sstream(input);
            string word;
            while (getline(sstream, word, space_char)) {

                words.push_back(word);
            }
            string check = input.substr(6);
            string check2 = input.substr(9);
            if (words.size() == 3) {
                if (isdigit(check[0]) && isdigit(check2[0])) {


                    string xstring = input.substr(5);
                    string ystring = input.substr(6);
                    string xstring2 = input.substr(8);
                    string ystring2 = input.substr(9);

                    char l = toupper(xstring[0]);
                    char l2 = toupper(xstring2[0]);
                    int x1 = char(l - 65);
                    int x2 = char(l2 - 65);

                    int y1 = stoi(ystring);
                    int y2 = stoi(ystring2);
                    fv.Swap(x1, y1, x2, y2);

                }
                else cout << "error\n";
            }
                else cout << "error\n";
            
        }



        //align


        if (input.find("align") != string::npos) {

            if (input.find(":") != string::npos) {

            }
            else {
               


                char space_char = ' ';
                vector<string> words{};
                stringstream sstream(input);
                string word;
                while (getline(sstream, word, space_char)) {

                    words.push_back(word);
                }
                string check = input.substr(7);
                if (words.size() == 3) {
                    if (isdigit(check[0])) {


                        string xstring = input.substr(6);
                        string ystring = input.substr(7);
                        char l = toupper(xstring[0]);
                        int y = char(l - 65);

                        int x = stoi(ystring);
                        if (words[2] == "left") {
                            fv.Align(x, y, words[2]);
                            fv.print();
                        }
                        if (words[2] == "right") {
                            fv.Align(x, y, words[2]);
                            fv.print();
                        }
                        else cout << "error\n";
                    }
                    else cout << "error\n";
                }
                else cout << "error\n";
            }
            

        }

       

    }
    cout << "Terminated";
    return 0;
}