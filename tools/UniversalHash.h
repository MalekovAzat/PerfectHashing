#ifndef UNIVERSALHASH_H
#define UNIVERSALHASH_H

class UniversalHash
{
public:
    UniversalHash(int p, int m, int a, int b);
    int operator()(int key) const;
private:
    int p;
    int m;
    int a;
    int b;
};

#endif // UNIVERSALHASH_H