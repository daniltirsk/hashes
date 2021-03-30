#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <math.h>
#include <bitset>


using namespace std;

int hashByDivision16(string line){
    int hashed_string;
    // если строка недостаточно длиная, то дополняем ее нулями
    if(line.length()*8<16){
        hashed_string = int(line[line.length()-2]) * 256;
    } else {
        hashed_string = int(line[line.length()-2]) * 256 + int(line[line.length()-1]);
    }
    return hashed_string;
}

int middleOfSquareASCII(string line){
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

int middleOfSquarePoly(string line){
    int hashed_line;
    unsigned int h;

    for(int i = 0; i < line.length(); i++) {
        h = h + (unsigned int)pow(line.at(i), (i+1));
    }

    hashed_line = h*h;

    int upperBound=1;
    while(hashed_line/int(pow(2,upperBound))){
        upperBound++;
    }

    return (((1 << 16) - 1) & (hashed_line >> (upperBound-16)/2));
}

int collapseHash(string line){
 int upper=0;
 int lower=0;
 //xor нечетных с нечетными и четных с четными
 for(int i=0;i<line.length();i+=2){
    upper = upper ^ int(line[i]);
    if (line.length()>1) lower = lower ^ int(line[i+1]);
 }
 return upper*256 + lower;
}

int shiftHash(string line){
    int16_t hashed_line=0;
    if(line.size()>1 && line.size()%2 == 0){
        for(int i = 0; i<line.size(); i+=2){
            hashed_line ^= (line[i]*256 + line[i+1] >> (i+1)) ^ (line[i]*256 + line[i+1] << (15-i));
        }
    } else if(line.size()>1) {
        for(int i = 0; i<line.size()-1; i+=2){
            hashed_line ^= (line[i]*256 + line[i+1] >> (i+1)) ^ (line[i]*256 + line[i+1] << (15-i));
        }
        hashed_line ^= (line[line.size()-1]*256) >> (line.size()) ^ (line[line.size()-1]*256 << (16-line.size()));
    } else {
        hashed_line ^= (line[line.size()-1]*256) >> (line.size()) ^ (line[line.size()-1]*256 << (16-line.size()));
    }
    return hashed_line;
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
            n = shiftHash(line);
            unique_hashes.insert(n);
            total_num++;
        }
        in_file.close();
    }

    cout<<"total_num: "<<total_num<<" unique_hashes: "<<unique_hashes.size()<<" collisions: "<<total_num - unique_hashes.size()<<endl;
    return 0;
}
