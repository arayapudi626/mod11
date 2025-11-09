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
        for (Dep::iterator it = dep.begin(); it != dep.end(); ++it){
            const string& dept = it->first;
            array<list<int>, STATUS>& arr = it->second;
            list<int> admitted;
            list<int> enrolled;

            // applied to admitted
            int moved = 0;
            while (moved < 2 && !arr[0].empty()) {
                int id = arr[0].front();
                arr[0].pop_front();
                arr[1].push_back(id);
                admitted.push_back(id);
                moved++;
            }
            // admitted to enrolled
            moved = 0;
            while (moved < 2 && !arr[1].empty()) {
                int id = arr[1].front();
                arr[1].pop_front();
                arr[2].push_back(id);
                enrolled.push_back(id);
                moved++;
            }

            if (!admitted.empty() || !enrolled.empty()){
                cout << dept << ": ";
                if (!admitted.empty()){
                    cout << "Admitted: ";
                    for (int id: admitted){
                        cout << id << " ";
                    } 
                }
                if (!enrolled.empty()){
                    cout << "Enrolled: ";
                    for (int id: enrolled){
                        cout << id << " ";
                    }
                }
                cout << endl;
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
    
    cout << "intial print: " << endl;
    print(dep);
    cout << "Simulation"
    simulation(dep);
    print (dep);
    return 0;

}