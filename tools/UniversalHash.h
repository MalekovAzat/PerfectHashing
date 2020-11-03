
class UniversalHash
{
public:
    UniversalHash(int p, int m, int a, int b);
    int operator()(int key);
private:
    int p;
    int m;
    int a;
    int b;
};

