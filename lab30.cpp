#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>

using namespace std;
const int STATUS = 3;
typedef map<string, array<list<int>, STATUS>> Dep;

void print(const Dep& dep){
    for (Dep::const_iterator it = dep.begin(); it != dep.end(); it++){
    const string&dept = it->first;
    const array<list<int>, STATUS>& arr = it->second;
    cout << dept << ": Applied=" << arr[0].size() << endl;
    cout << " Admitted=" << arr[1].size() << endl;
    cout << " Enrolled=" << arr[2].size() << endl;
    }
}

void simulation(Dep& dep){
    for (int i = 1; i <= 25; i++){
        for (Dep::iterator it = dep.begin(); it != dep.end(); it++){
            array<list<int>, STATUS>& arr = it->second;
            // applied to admitted
            int move = 0;
            while(move < 2) {
                int id = arr[0].front();
                arr[0].pop_front();
                arr[1].push_back(id);
                move++;
            }
            //admitted to enrolled
            int move = 0;
            while(move < 2) {
                int id = arr[1].front();
                arr[1].pop_front();
                arr[2].push_back(id);
                move++;
            }

        }
        cout << "Interval " << i << " done" << endl;
        }
}

int main() {
    Dep dep;
    ifstream fin ("students.txt");
    if (!fin) {
        cout << "Could not open file" << endl;
    }
    string dept;
    int id;

    while (fin >> dept >> id) {
        dep[dept][0].push_back(id);
    }
    fin.close();
    
    print(dep);
    simulation(dep);
    print (dep);
    return 0;

}