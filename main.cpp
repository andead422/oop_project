#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"


DBConnect* database = DBConnect::GetInstance();

int main()
{
    //-----------------------------------------------------------------------------------------Date
    cout << "------------------------------DATE------------------------------" << endl;
    Date dt, test(23, 12, 2003);

    cout << "Date(): **using printDate()**" << endl;
    dt.printDate();
    cout << endl;

    cout << "Date(int, int, int): **using cout<<**" << endl;
    cout << test << endl;

    cin >> test;
    cout << "cin >>: " << endl;
    cout << test << endl;

    Date dt1(test);
    cout << "Date(const Date&):" << endl;
    cout << dt1 << endl;

    bool a = dt == dt1;
    cout << a << endl;

    bool b = dt > dt1;
    cout << b << endl;

    ++dt;
    dt.printDate();
    cout << endl;

    dt++;
    dt.printDate();
    cout << endl;

    b = dt != dt1;
    cout << b << endl;

    a = dt < dt1;
    cout << a << endl;
    /*
    dt1 = test + dt;
    dt1.printDate();
    cout << endl;
    */


    //-----------------------------------------------------------------------------------------FilmViewer



    //-----------------------------------------------------------------------------------------FilmAdmin



    //-----------------------------------------------------------------------------------------Admin



    //-----------------------------------------------------------------------------------------Viewer

    

    

}