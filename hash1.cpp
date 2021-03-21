#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <math.h>


using namespace std;

int get_hash_ascii(string line){
    int sum = 0;
    for (int i=0; i<line.length();i++){
        sum += int(line[i]);
    }
    return sum;
}

int polynom_hash(string key){
    unsigned int h;

    for(int i = 0; i < key.length(); i++) {
        h = h + (unsigned int)pow(key.at(i), (i+1));
    }
    return h;
}

int main(){

    set<int> unique_hashes;
    int total_num = 0;

    fstream in_file;
    in_file.open("endict.txt",ios::in);
    if (in_file.is_open()){
        string line;
        while(getline(in_file, line)){
            unique_hashes.insert(polynom_hash(line));
            total_num++;
        }
        in_file.close();
    }
    cout<<total_num<<" "<<unique_hashes.size()<<" "<<total_num - unique_hashes.size()<<endl;
    return 0;
}
