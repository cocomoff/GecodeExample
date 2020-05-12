#include <iostream>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace std;
using namespace Gecode;

class SendMoreMoney : public Space {
protected:
    IntVarArray l;

public:
    SendMoreMoney(void) : l(*this, 8, 0, 9) {
        /*
        Problem: SEND + MOST = MONEY, MONEY is maximal
        Prepare 8 varaibles (s, e, n, d, m, o, t, y)
        */

        // Synonyms
        IntVar s(l[0]), e(l[1]), n(l[2]), d(l[3]), m(l[4]), o(l[5]), t(l[6]), y(l[7]);

        rel(*this, s != 0);  // no leading zeros
        rel(*this, m != 0);  // no leading zeros
        distinct(*this, l);  // all letters distinct
        
        // sum constraint
        rel(*this,   1000 * s + 100 * e + 10 * n + d
                   + 1000 * m + 100 * o + 10 * s + t == 
         10000 * m + 1000 * o + 100 * n + 10 * e + y);
        
        // post branching
        branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    // search support
    SendMoreMoney(SendMoreMoney& s) : Space(s) {
        l.update(*this, s.l);
    }
    virtual void constrain(const Space& _b) {
        const SendMoreMoney& b = static_cast<const SendMoreMoney&>(_b);
        IntVar e(l[1]), n(l[2]), m(l[4]), o(l[5]), y(l[7]);
        IntVar b_e(b.l[1]), b_n(b.l[2]), b_m(b.l[4]), b_o(b.l[5]), b_y(b.l[7]);
        int money = (10000 * b_m.val() + 1000 * b_o.val()
                    + 100 * b_n.val() + 10 * b_e.val() + b_y.val());
        rel(*this, 10000 * m + 1000 * o + 100 * n + 10 * e + y > money);
    }
    virtual Space* copy(void) {
        return new SendMoreMoney(*this);
    }
    void print(void) const { cout << l << endl; }
};

// main function
int main(int argc, char* argv[]) {
    try {
        SendMoreMoney* m = new SendMoreMoney;
        BAB<SendMoreMoney> e(m);
        delete m;
    
        // search and print all solutions
        while (SendMoreMoney* s = e.next()) {
            s->print(); delete s;
        }
    } catch (Exception e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}