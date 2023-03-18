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

class PerformEx1 : public Perform {
protected:
    virtual bool show0() {
        cout << "ex1 show0" << endl;
        return true;
    }
    virtual void show2() {
        cout << "ex1 show2" << endl;
    }
};

class PerformEx2 : public Perform {
protected:
    virtual void show1() {
        cout << "ex2 show1" << endl;
    }
    virtual void show2() {
        cout << "ex2 show2" << endl;
    }
};

class PerformEx3 : public Perform {
protected:
    virtual void show2() {
        cout << "ex3 show2" << endl;
    }
    virtual void show3() {
        cout << "ex3 show3" << endl;
    }
};

int main()
{
    return 0;
}