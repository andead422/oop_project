#include "date/date.hpp"
#include "film/film_viewer.hpp"
#include "film/film_admin.hpp"
#include "user/admin.hpp"
#include "user/viewer.hpp"
#include "recommendations/python_from_cpp.hpp"

DBConnect* database = DBConnect::getInstance();

void dateInstance();
void recommendationsInstance();
User* userCreation();
void viewerCase(Viewer*);
void adminCase(Administrator*);

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
    User* user;
    user = userCreation();
    
    if (user->isAdmin()) {
        adminCase(reinterpret_cast<Administrator*>(user));
    }
    else {
        viewerCase(reinterpret_cast<Viewer*>(user));
    }
}

User* userCreation() {
    User* user;

    cout << "Create new user:" << endl;
    string login;
    cin >> login;

    int admin = database->checkAdmin(login);
    switch (admin){
    case 1:
        user = new Administrator(login);
        break;
    
    case 0:
        user = new Viewer(login);
        break;

    case -1:
        int choose;
        while(1) {
            cout << "Who do you wanna be?" << endl;
            cout << "1. Admin" << endl;
            cout << "2. Viewer" << endl;

            cin >> choose;
            if (choose == 1 || choose == 2) break;

            cout <<  "Invalid input!" << endl;
        }

        if(choose == 1) {
            user = new Administrator();
            user->setLogin(login);
        }
        else {
            user = new Viewer();
            user->setLogin(login);
            cin >> *reinterpret_cast<Viewer*>(user);
        }
        break;
    }

    cout << endl << "Created user: " << endl;
    user->printInfo();
    return user;
}

void viewerCase(Viewer* viewer) {
    viewer->rateFilms();
    
    vector<int> recomm = recomended_film(viewer->getMapRatedFilms());

    for (int ii : recomm) {
        FilmViewer temp(ii);

        if(!viewer->checkSeen(temp)) {
            temp.printFilmInfoToRecommend();
        }
    }
}

void adminCase(Administrator* admin) {
    int choose;

    while(1) {

        cout << "What do you wanna do?" << endl;
        cout << "1. See user stats by id:" << endl;
        cout << "2. See user stats by login:" << endl;
        cout << "3. See film stats by id:" << endl;
        cout << "4. Relogin" << endl;
        cout << "5. Exit" << endl;

        cin >> choose;
        if(choose < 6 && choose > 0) break;

        cout << "Invalid input!!" << endl;
    }

    string login;
    int id;
    switch (choose) {
    case 1:
        cout << "Enter an id: ";
        cin >> id;

        admin->seeUserStats(id)->printInfo();
        break;
    
    case 2:
        cout << "Enter an login: ";
        cin >> login;

        admin->seeUserStats(login)->printInfo();
        break;

    case 3:
        cout << "Enter an id: ";
        cin >> id;

        admin->seeFilmStats(id).printInfo();
        break;

    case 4:
        recommendationsInstance();
        break;
    case 5:
        exit;
    }

}