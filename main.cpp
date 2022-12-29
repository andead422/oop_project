#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"


DBConnect* database = DBConnect::GetInstance();

int main()
{
    cout << to_string(database->getFilmGenres(4));
}