#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <math.h>
#include <bitset>


using namespace std;

int hashByDivision16(string line){
    int hashed_string;
    // åñëè ñòðîêà íåäîñòàòî÷íî äëèíàÿ, òî äîïîëíÿåì åå íóëÿìè
    if(line.length()*8<16){
        hashed_string = int(line[line.length()-2]) * 256;
    } else {
        hashed_string = int(line[line.length()-2]) * 256 + int(line[line.length()-1]);
    }
    return hashed_string;
}

int middleOfSquare(string line){
    int sumOfLine = 0;
    int hashed_line;
    for (int i = 0; i < line.length(); i++){
        sumOfLine += int(line[i]);
    }
    hashed_line = sumOfLine*sumOfLine;

    int upperBound=1;
    while(hashed_line/int(pow(2,upperBound))){
        upperBound++;
    }

    return (((1 << 16) - 1) & (hashed_line >> (upperBound-16)/2));
}

int collapseHash(string line){
 int upper=0;
 int lower=0;
 //xor íå÷åòíûõ ñ íå÷åòíûìè è ÷åòíûõ ñ ÷åòíûìè
 for(int i=0;i<line.length();i+=2){
    upper = upper ^ int(line[i]);
    if (line.length()>1) lower = lower ^ int(line[i+1]);
 }
 return upper*256 + lower;
}

int main(){

    set<int> unique_hashes;
    int total_num = 0;
    int n;

    fstream in_file;
    in_file.open("endict-small.txt",ios::in);
    if (in_file.is_open()){
        string line;
        while(getline(in_file, line)){
            n = collapseHash(line);
            unique_hashes.insert(n);
            total_num++;
        }
        in_file.close();
    }
    cout<<"total_num: "<<total_num<<" unique_hashes: "<<unique_hashes.size()<<" collisions: "<<total_num - unique_hashes.size()<<endl;
    return 0;
}
