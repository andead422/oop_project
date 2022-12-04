import pymysql
import tmdbsimple as tmdb
import secret
from fuzzywuzzy import fuzz
import time


conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()
tmdb.API_KEY = secret.getapikey()
people = set()


def person_checker(name):
    search = tmdb.Search()
    for res in search.person(query=name)['results']:
        if fuzz.token_sort_ratio(res['name'], name) >= 95:
            print('person: ' + name + ', ' + res['name'])
            people.add(name.lower())
            return 1
    else:
        print('not person: ' + name)
        return 0


def delete_people_new_version():
    global people
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '%?%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '0%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '1%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '2%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '3%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '4%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '5%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '6%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '7%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '8%'")
    cur.execute("DELETE FROM tag_tmp WHERE tag LIKE '9%'")
    conn.commit()
    cur.execute("SELECT DISTINCT tag FROM tag_tmp;")
    tags = cur.fetchall()
    for tag in tags:
        if 2 <= len(tag[0].split(' ')) <= 5:
            flag = 2
            while flag > 0:
                try:
                    if person_checker(tag[0]):
                        cur.execute(f"DELETE FROM tag_tmp WHERE tag LIKE '%{tag[0]}%'")
                        conn.commit()
                    break
                except:
                    time.sleep(2)
                    print('reconnecting...')
                    flag -= 1
            else:
                print('not person (server not available): ' + tag[0])


delete_people_new_version()

print(people)

conn.commit()
cur.close()
