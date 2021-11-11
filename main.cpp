#include "libs.h"
#include "afd.h"
using namespace std;

int main()
{
    AFD *automata = new AFD();
    int n, is, nfs = 0;
    cin >> n >> is >> nfs;
    automata = new AFD(n, is, nfs);
    for (int i = 0; i < nfs; i++)
    {
        cin >> automata->fss[i];
    }

    int a, b;
    int size = 2 * n, count = 0;
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            cin >> n >> is >> a;
        else
        {
            cin >> n >> is >> b;
            //cout<<"{\na:"<<a<<", b:"<<b<<"}\n";
            (automata->ft)[count] = make_pair(a, b);
            count++;
        }
    }
    automata->printft();
    string t = automata->convert_re();
    cout << "Expresion regular: " << endl
         << endl
         << t << endl
         << endl;
    return 0;
}
