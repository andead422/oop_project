#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"

DBConnect database;

int main()
{
    // DBConnect database;
    Date dt;
    dt.printDate();
    cout << endl;
    cout << FilmViewer::getFilmsNumber();
}