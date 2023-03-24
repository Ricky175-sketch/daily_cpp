#include <iostream>
#include <memory>
using namespace std;

int main()
{
    // weak_ptr<int> wp;
    // {
    //     shared_ptr<int> sp(new int(1));
    //     wp = sp;
    //     shared_ptr<int> sp_ok = wp.lock();
    // }
    // shared_ptr<int> sp_null = wp.lock();
    //
    // if (wp.expired())
    //     cout << "shared_ptr has destroyed" << endl;
    // else
    //     cout << "shared_ptr is alive" << endl;
    weak_ptr<int> wp;
    shared_ptr<int> sp_ok;
    {
        shared_ptr<int> sp(new int(1));
        wp = sp;
        sp_ok = wp.lock();
    }

    if (wp.expired())
        cout << "shared_ptr has destroyed" << endl;
    else
        cout << "shared_ptr is alive" << endl;

    return 0;
}
