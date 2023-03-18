#include <iostream>

using namespace std;

class Perform {
public:
    void show() {
        
    }

private:
    void playGame() {
        cout << "show0 end, have a small game" << endl;
    }

protected:
    virtual bool show0() {
        cout << "show0" << endl;
        return true;
    }
    virtual void show1() {

    }
    virtual void show2() {
        cout << "show2" << endl;
    }
    virtual void show3() {

    }
};

int main()
{
    return 0;
}