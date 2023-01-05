#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"
#include "recommendations/python_from_cpp.hpp"

DBConnect* database = DBConnect::getInstance();

void dateInstance();
void recommendationsInstance();

int main()
{
    int choose;

    do {
        cout << "1. date class" << endl;
        cout << "2. get recommendations" << endl;

        cin >> choose;

        if (choose == 1) {
            dateInstance();
        }
        else if (choose == 2) {
            recommendationsInstance();
        } 
        else { 
            cout << "Invalid input!";
        }

    } while(choose != 1 && choose != 2);

    return 0;
}


void dateInstance() {
                //-----------------------------------------------------------------------------------------Date
            cout << "------------------------------DATE------------------------------" << endl << endl;
            Date date0, date2(23, 12, 2003);

            cout << "Date(): **using printDate()**" << endl;
            cout << "date0: ";
            date0.printDate();
            cout << endl << endl;

            cout << "Date(int, int, int): **using cout<<**" << endl;
            cout << "date2" << endl;
            cout << date2 << endl;
            
            cout << "cin >>: " << endl;
            cin >> date2;
            cout << "date2" << endl;
            cout << date2 << endl;

            Date date1(date2);
            cout << "Date(const Date&):" << endl << "date1" << endl;
            cout << date1 << endl;


            bool a = date2 == date1;
            cout << "date1 == date2: " << a << endl;

            bool b = date0 > date1;
            cout << "date0 > date1: " << b << endl;

            cout << "++date1: ";
            (++date1).printDate();
            cout << endl;

            cout << "date2++: ";
            (date2++).printDate();
            cout << endl;

            b = date0 != date1;
            cout << "date0 != date1: " << b << endl;

            a = date0 < date1;
            cout << "date0 < date1: " << a << endl;

            cout << endl;
            cout << "date2: ";
            date2.printDate();
            cout << " date0: ";
            date0.printDate();
            cout << endl;

            cout << "date2 + date0: ";
            (date2 + date0).printDate();
            cout << endl;
}

void recommendationsInstance() {
            cout << "Create new viewer:" << endl;
            Viewer viewer;
            cin >> viewer;
            cout << endl << "Created viewer: " << viewer << endl;

            viewer.rateFilms();
            
            vector<int> recomm = recomended_film(viewer.getMapRatedFilms());
            
            cout << "rec size: " << recomm.size() << endl;

            for (int ii : recomm) {
                FilmViewer temp(ii);

                if(!viewer.checkSeen(temp)) {
                    temp.printFilmInfoToRecommend();
                }
            }
}