#include <stdbool.h>
bool tapish(bool a,bool b,bool c){
    bool ab=a&b;
    bool bc=b&c;
    bool ac=a&c;
    bool out=ab||bc||ac;
    return out;
}