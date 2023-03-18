#include <iostream>

using namespace std;

class Perform {
public:
    void show() {
        if (show0())
            playGame();
        show1();
        show2();
        show3();
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
    virtual void show1() {
        cout << "ex3 show1" << endl;
    }
    virtual void show2() {
        cout << "ex3 show2" << endl;
    }
    virtual void show3() {
        cout << "ex3 show3" << endl;
    }
};

int main()
{
    Perform *p1 = new PerformEx1();
    p1->show();
    cout << "====================" << endl;

    Perform *p2 = new PerformEx2();
    p2->show();
    cout << "====================" << endl;

    Perform *p3 = new PerformEx3();
    p3->show();
    cout << "====================" << endl;

    return 0;
}