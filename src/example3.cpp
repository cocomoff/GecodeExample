#include <iostream>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace std;
using namespace Gecode;

class SampleAD : public Space {
protected:
    IntVar x1, x2, x3;

public:
    SampleAD(void) : x1(*this, IntSet({1, 2})), x2(*this, IntSet({1, 2})), x3(*this, IntSet({3})) {
        /*
        minimize f(x) = x1 + x2 + x3
        s.t. alldifferent(x1, x2, x3)
             D(x1) = D(x2) = {1, 2}
             D(x3) = {3}
        */

        // Synonyms
        IntVarArgs x = {x1, x2, x3};
        distinct(*this, x);

        // post branching
        branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    // search support
    SampleAD(SampleAD& s) : Space(s) {
        x1.update(*this, s.x1);
        x2.update(*this, s.x2);
        x3.update(*this, s.x3);
    }
    virtual Space* copy(void) {
        return new SampleAD(*this);
    }
    virtual void constrain(const Space& _b) {
        const SampleAD& b = static_cast<const SampleAD&>(_b);
        IntVar b_x1(b.x1), b_x2(b.x2), b_x3(b.x3);
        int cost = b_x1.val() + 10 * b_x2.val() + b_x3.val();
        // rel(*this, x1 + 10 * x2 + x3 > cost);
        rel(*this, x1 + 10 * x2 + x3 < cost);
    }
    // print solution
    void print(void) const {
        cout << x1 << " " << x2 << " " << x3 << endl;
    }
};

// main function
int main(int argc, char* argv[]) {
    try {
        SampleAD* m = new SampleAD;
        DFS<SampleAD> e(m);
        delete m;
    
        // search and print all solutions
        while (SampleAD* s = e.next()) {
            s->print(); delete s;
        }
    } catch (Exception e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    try {
        SampleAD* m = new SampleAD;
        BAB<SampleAD> e(m);
        delete m;
    
        // search and print all solutions
        while (SampleAD* s = e.next()) {
            s->print(); delete s;
        }
    } catch (Exception e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}