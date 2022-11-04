#include <string>
#include <vector>
#include <iostream>

using namespace std;

class RequiredVars {
public:
    RequiredVars(const char var = 0);

    static bool isCapatible(const RequiredVars& a, const RequiredVars& b);
    friend bool operator<(const RequiredVars& a, const RequiredVars& b);
protected:
    friend RequiredVars operator+(const RequiredVars& a, const RequiredVars& b);
private:
    static const size_t VARS_COUNT = 5;

    bool vars[VARS_COUNT];
};

class Formula : public RequiredVars {
public:
    bool operator==(string rawFormula) const;
    friend ostream& operator<<(ostream& out, const Formula& f);

    size_t length() const;

    Formula(const Formula& f);

    Formula();
    Formula(const char var);
    Formula(const Formula& f1, const Formula& f2);
private:
    string raw;
    string analysis;
};

string rightAns = "|||p|||q|r|||s|t|||";
// string rightAns = "|||p|q||";
void buildFormula(vector<Formula>& formulas, size_t depth = 0, size_t begin = 0);

int main() {
    vector<Formula> formulas;

    formulas.push_back(Formula('p'));
    formulas.push_back(Formula('q'));
    formulas.push_back(Formula('r'));
    formulas.push_back(Formula('s'));
    formulas.push_back(Formula('t'));

    buildFormula(formulas);

    cout << "Built " << formulas.size() << " formulas" << endl;
    for (const Formula& f : formulas) {
        // cout << f << endl;
        if (f == rightAns) {
            cout << f << endl;
        }
    }

    return 0;
}

void buildFormula(vector<Formula>& formulas, size_t depth, size_t begin) {
    if (depth > rightAns.length()) return;
    size_t fCount = formulas.size();
    cout << depth << " : " << fCount << endl;

    begin += begin;
    for (size_t ext = 0; ext < fCount; ++ext) {
        const Formula f1(formulas[ext]);

        if (f1.length() > rightAns.length()) return;

        formulas.push_back(Formula(f1, Formula()));

        for (size_t inr = 0; inr < fCount; ++inr) {
            const Formula f2(formulas[inr]);

            if (!(f1 < f2)) continue;
            formulas.push_back(Formula(f1, f2));
            // cout << "formula : " << *formulas.rbegin() << endl;
        }
    }

    buildFormula(formulas, depth + 1, fCount);
}

RequiredVars::RequiredVars(const char var) : vars{ 1, 1, 1, 1, 1 } {
    switch (var) {
    case 'p':
        vars[0] = false;
        break;
    case 'q':
        vars[1] = false;
        break;
    case 'r':
        vars[2] = false;
        break;
    case 's':
        vars[3] = false;
        break;
    case 't':
        vars[4] = false;
        break;
    default:
        break;
    }
}

bool RequiredVars::isCapatible(const RequiredVars& a, const RequiredVars& b) {
    for (size_t i = 0; i < RequiredVars::VARS_COUNT; ++i) {
        if (!a.vars[i] && !b.vars[i])
            return false;
    }

    return true;
}

bool operator<(const RequiredVars& a, const RequiredVars& b) {
    if (!RequiredVars::isCapatible(a, b)) return false;

    bool edgeIsPassed = false;
    for (size_t i = 0; i < RequiredVars::VARS_COUNT; ++i) {
        if (edgeIsPassed) {
            if (!a.vars[i])
                return false;
        } else {
            if (!b.vars[i])
                edgeIsPassed = true;
        }
    }

    return true;
}

RequiredVars operator+(const RequiredVars& a, const RequiredVars& b) {
    RequiredVars ret;
    for (size_t i = 0; i < RequiredVars::VARS_COUNT; ++i) {
        ret.vars[i] = a.vars[i] & b.vars[i];
    }

    return ret;
}

bool Formula::operator==(string rawFormula) const {
    return this->raw == rawFormula;
}

ostream& operator<<(ostream& out, const Formula& f) {
    out << f.raw << " " << f.analysis;
    return out;
}

size_t Formula::length() const {
    return this->raw.length();
}

Formula::Formula(const Formula& f) : RequiredVars(f), raw(f.raw), analysis(f.analysis) {
}

Formula::Formula() : raw(), analysis() {
}
Formula::Formula(const char var) : RequiredVars(var), raw(1, var), analysis(raw) {
}
Formula::Formula(const Formula& f1, const Formula& f2) : RequiredVars(f1 + f2), raw(), analysis() {
    raw /**/ = "|" + f1.raw /**/ + f2.raw /**/ + "|";
    analysis = "(" + f1.analysis + f2.analysis + ")";
}
