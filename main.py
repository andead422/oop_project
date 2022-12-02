import csv
import pymysql
import re
import secret
import copy
from fuzzywuzzy import fuzz

# запустить эту команду до запуска кода
# LOAD DATA LOCAL INFILE "{path}" INTO TABLE rating FIELDS TERMINATED BY ',' LINES TERMINATED BY '\r\n' IGNORE 1 LINES (id_user, id_film, rating, @timestamp);
# ^.+,[A-Z]\w+ [A-Z]\w+,.+$
# загрузить файл с рейтингом в бд


genres = []
films = []
films_genres = []
tags_film = {}


conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


def sql_select_all(sql_string):
    cur.execute(sql_string)
    return cur.fetchall()


def sql_select_one(sql_string):
    cur.execute(sql_string)
    return cur.fetchone()


def add_films():
    global films
    global films_genres
    with open('ml-25m/movies.csv', 'r', newline='\n', encoding='UTF8') as movies_file:
        reader = csv.reader(movies_file, delimiter=',')
        next(reader)
        film_info = []
        film_genres = []
        counter = 1
        article_checker = re.compile(r"(.+?;[ATL][^A-Z ()?!.;]{0,2})(?= \()")
        year_checker = re.compile(r"\d{4}")
        for row_film in reader:
            if row_film[-1] != '(no genres listed)':
                film_genres.clear()
                film_info.clear()
                film_genres.append(counter)
                film_info.append(counter)
                film_info.append(int(row_film[0]))

                article_found = re.findall(article_checker, row_film[1])
                if article_found:
                    film_info.append(article_found[0].split(';')[-1] + ' ' + ', '.join(article_found[0].split(';')[:-1]))
                else:
                    film_info.append(', '.join(row_film[1].split(' (')[0].split(';')))

                year_found = re.findall(year_checker, row_film[1].split('(')[-1][:4])
                if year_found:
                    film_info.append(int(year_found[0]))
                else:
                    film_info.append(0000)

                film_genres.append(row_film[-1].split('|'))

                films.append(copy.deepcopy(film_info))
                films_genres.append(copy.deepcopy(film_genres))

                film_str = '(' + str(film_info[0]) + ', ' + str(film_info[1]) + ', "' + str(film_info[2]) + '", ' + str(film_info[3]) + ')'
                sql_insert(f"INSERT INTO film (id_film, id_film_source, title, year) VALUES {film_str}")

                for genre in row_film[-1].split('|'):
                    if genre not in genres:
                        genres.append(genre)
                counter += 1
    sql_insert("CREATE UNIQUE INDEX index_id_film_source ON film(id_film_source)")

    print('All films added to db ' + secret.getdb())

    genres_str = '("' + '"), ("'.join(sorted(genres)) + '")'
    sql_insert(f"INSERT INTO genres (genre_name) VALUES {genres_str}")

    print('All genres added to db ' + secret.getdb())

    id_genres = sql_select_all('SELECT * FROM genres')
    id_genres = dict((y, x) for x, y in id_genres)

    for fg in films_genres:
        for gg in fg[1]:
            fg_str = '(' + str(fg[0]) + ', ' + str(id_genres[gg]) + ')'
            sql_insert(f"INSERT INTO film_genres (id_film, id_genre) VALUES {fg_str}")

    sql_insert("CREATE INDEX index_id_film_fg ON film_genres(id_film)")

    print('All films connected to genres in db ' + secret.getdb())


def add_rating():
    sql_insert("UPDATE rating t1 SET t1.id_film = (SELECT t2.id_film FROM film t2 WHERE t2.id_film_source = t1.id_film_source)")

    print('All films connected to rating in db ' + secret.getdb())

    sql_insert("ALTER TABLE rating DROP COLUMN id_film_source")
    sql_insert("ALTER TABLE rating MODIFY COLUMN id_film int NOT NULL;")

    sql_insert("CREATE INDEX index_id_film_r ON rating(id_film)")


def sort_tag():
    global tags_film
    with open('ml-25m/tags_first_ver.csv', 'r', newline='\n', encoding='UTF8') as tags_file:
        fields_original = ['userId', 'movieId', 'tag']

        reader = csv.DictReader(tags_file, fieldnames=fields_original)
        next(reader)

        for row_tags in reader:
            for word in row_tags['tag'].split(' '):
                print('word: ' + word)
                try:
                    for tag in tags_film[row_tags['movieId']].keys():
                        print('tag: ' + tag)
                        if fuzz.WRatio(word, tag) >= 70:
                            print(tag + ' + 1')
                            tags_film[row_tags['movieId']][tag] += 1
                            break
                    else:
                        print(word + ' = 1')
                        tags_film[row_tags['movieId']][word] = 1
                except:
                    tags_film[row_tags['movieId']] = {}
                    print(word + ' = 1 (except)')
                    tags_film[row_tags['movieId']][word] = 1


# add_films()
# add_rating()
sort_tag()
print(tags_film)

# str_1 = 'historical'
# str_2 = 'hisory'

# print(fuzz.ratio(str_1, str_2))
# print(fuzz.token_sort_ratio(str_1, str_2))
# print(fuzz.token_set_ratio(str_1, str_2))
# print(fuzz.partial_ratio(str_1, str_2))
# print(fuzz.WRatio(str_1, str_2))
# print(fuzz.UQRatio(str_1, str_2))
# print(fuzz.UWRatio(str_1, str_2))
# print(fuzz.QRatio(str_1, str_2))


conn.commit()
cur.close()
