#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"


DBConnect* database = DBConnect::GetInstance();

int main()
{
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

    cout << "++date0: ";
    (++date0).printDate();
    cout << endl;

    cout << "date0++: ";
    (date0++).printDate();
    cout << endl;

    b = date0 != date1;
    cout << "date0 != date1: " << b << endl;

    a = date0 < date1;
    cout << "date0 < date1: " << a << endl;
    /*
    date1 = date2 + date0;
    date1.printDate();
    cout << endl;
    */

    //-----------------------------------------------------------------------------------------FilmViewer
    FilmViewer fv1, fv2(100), fv3(fv1);

    cout << "FilmViewer():" << "fv1" << endl;
    cout << to_string(fv1) << endl;

    cout << "FilmViewer(int id):" << "fv2" << endl;
    int id;
    cin >> id;
    cout << to_string(fv2) << endl;

    cout << "FilmViewer(FilmViewer&):" << "fv3" << endl;
    cout << to_string(fv3) << endl;

    a = fv1 == fv2;
    cout << "date1 == date2: " << a << endl;

     
    //-----------------------------------------------------------------------------------------FilmAdmin



    //-----------------------------------------------------------------------------------------Admin



    //-----------------------------------------------------------------------------------------Viewer

    

    

}