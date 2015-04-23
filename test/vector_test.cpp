#include <vector>
#include <iostream>

using namespace std;

void print_my_vec(vector<int>& myVec)
{
    for(size_t i = 0; i < myVec.size(); i++)
        cout<< myVec[i] << " ";
    cout << endl;
}

int main()
{
    vector<int> myVec(4,100);
    print_my_vec( myVec);
    myVec.insert(myVec.begin()+1, 200);
    print_my_vec( myVec);
    myVec.erase( myVec.begin()+2, myVec.begin()+4);
    print_my_vec( myVec);
    return 0;
}
