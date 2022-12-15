#include <vector>
#include <string>

using std::vector;
using std::string;

class DBConnect {
    //parilka
public:
    int getGenresNumber();
    int getFilmsNumber();
    string getFilmName(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
};