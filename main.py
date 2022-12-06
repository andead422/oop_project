import csv
import pymysql
import re
import secret
import copy
import tmdbsimple as tmdb
import time
from fuzzywuzzy import fuzz

# запустить эту команду до запуска кода
# LOAD DATA LOCAL INFILE "{path}" INTO TABLE rating FIELDS TERMINATED BY ',' LINES TERMINATED BY '\r\n' IGNORE 1 LINES (id_user, id_film_source, rating, @timestamp);
# загрузить файл с рейтингом в бд

# SELECT DISTINCT tag, count(tag) FROM tag_tmp GROUP BY tag ORDER BY count(tag) DESC;


genres = []
films = []
films_genres = []
tags_film = {}
actors = set()
directors = set()
actors_actual = set()
directors_actual = set()
film_actors = {}
film_directors = {}
errors_list = []
no_data_list = []

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()
tmdb.API_KEY = secret.getapikey()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


def sql_select_all(sql_string):
    cur.execute(sql_string)
    return cur.fetchall()


def sql_select_one(sql_string):
    cur.execute(sql_string)
    return cur.fetchone()


def cast_getter(tmdb_id):
    flag = 2
    while flag > 0:
        try:
            film_tmdb = tmdb.Movies(tmdb_id)
            return film_tmdb.credits()
        except:
            print('reconnecting...')
            # print(err)
            time.sleep(0.5)
            flag -= 1
    return 'NULL'


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
                    film_info.append(
                        article_found[0].split(';')[-1] + ' ' + ', '.join(article_found[0].split(';')[:-1]))
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

                film_str = '(' + str(film_info[0]) + ', ' + str(film_info[1]) + ', "' + str(film_info[2]) + '", ' + str(
                    film_info[3]) + ')'
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
    sql_insert("DELETE FROM rating WHERE id_film = NULL")
    sql_insert("ALTER TABLE rating MODIFY COLUMN id_film int NOT NULL")

    sql_insert("CREATE INDEX index_id_film_r ON rating(id_film)")


# def sort_tag():
#     global tags_film
#     with open('ml-25m/tags_first_ver.csv', 'r', newline='\n', encoding='UTF8') as tags_file:
#         fields_original = ['userId', 'movieId', 'tag']
#
#         reader = csv.DictReader(tags_file, fieldnames=fields_original)
#         next(reader)
#         for row_tags in reader:
#             for word in row_tags['tag'].split(' '):
#                 print('word: ' + word)
#                 if len(word) < 4:
#                     continue
#                 try:
#                     for tag in tags_film[row_tags['movieId']].keys():
#                         print('tag: ' + tag)
#                         if fuzz.WRatio(word, tag) >= 70:
#                             print(tag + ' + 1')
#                             tags_film[row_tags['movieId']][tag] += 1
#                             break
#                     else:
#                         print(word + ' = 1')
#                         tags_film[row_tags['movieId']][word] = 1
#                 except:
#                     tags_film[row_tags['movieId']] = {}
#                     print(word + ' = 1 (except)')
#                     tags_film[row_tags['movieId']][word] = 1


# def sort_tag():
#     tag_list = sql_select_all("SELECT DISTINCT * FROM tag_tmp;")
#     for row_tag in tag_list:


def add_cast(partitions_quan=1):
    global actors
    global film_actors
    global directors
    global film_directors
    global errors_list
    links = sql_select_all("SELECT id_film, id_tmdb FROM links")
    quan_films = len(links)
    part_no = 1
    cur_film_id = 0
    while part_no <= partitions_quan:
        while quan_films*((part_no-1)/partitions_quan) <= cur_film_id <= quan_films*(part_no/partitions_quan):
            film = links[cur_film_id]
            result = cast_getter(film[1])
            if result != 'NULL':
                if result['cast'] != [] and result['crew'] != []:
                    counter = 0
                    film_actors[film[0]] = []
                    for cast in result['cast']:
                        if counter < 5:
                            if cast['original_name'] not in actors or cast['original_name'] not in actors_actual:
                                actors_actual.add(cast['original_name'])
                            film_actors[film[0]].append(cast['original_name'])
                            counter += 1
                    for crew in result['crew']:
                        if crew['job'] == 'Director':
                            if crew['original_name'] not in directors or cast['original_name'] not in directors_actual:
                                directors_actual.add(crew['original_name'])
                            film_directors[film[0]] = crew['original_name']
                            break
                    try:
                        print('actors for ' + str(film[0]) + ': ' + str(film_actors[film[0]]))
                        print('directors for ' + str(film[0]) + ': ' + str(film_directors[film[0]]))
                    except:
                        pass
                    else:
                        no_data_list.append(film)
            else:
                errors_list.append(film)
            cur_film_id += 1
        actors_str = '("' + '"), ("'.join(sorted(actors_actual)) + '")'
        directors_str = '("' + '"), ("'.join(sorted(directors_actual)) + '")'
        sql_insert(f"INSERT INTO actors (full_name) VALUES {actors_str}")
        sql_insert(f"INSERT INTO directors (full_name) VALUES {directors_str}")
        actors = actors_actual.copy()
        directors = directors_actual.copy()
        actors_actual.clear()
        directors_actual.clear()
        print('All actors and directors added to db ' + secret.getdb())
        actors_ids = sql_select_all("SELECT * FROM actors")
        directors_ids = sql_select_all("SELECT * FROM directors")
        actors_ids = dict((y, x) for x, y in dict(actors_ids))
        directors_ids = dict((y, x) for x, y in dict(directors_ids))
        for film_ids in film_actors.keys():
            for film_cast in film_actors[film_ids]:
                sql_insert(f"INSERT INTO film_act (id_film, id_actor) VALUES ({film_ids}, {actors_ids[film_cast]})")
            if directors_ids[film_ids]:
                sql_insert(f"INSERT INTO film_dir (id_film, id_dir) VALUES ({film_ids}, {directors_ids[film_directors[film_ids]]})")
        film_actors.clear()
        film_directors.clear()
        print('iteration no. ' + str(part_no) + ' ended')
        part_no += 1


# add_films()
# add_rating()
# sort_tag()
add_cast(4)
print(no_data_list)
print(errors_list)
# print(tags_film)

# str_1 = 'historical'
# str_2 = 'hisory'
# str_1 = 'hindi'
# str_2 = 'india'
# str_1 = 'funny'
# str_2 = 'notfunny'
#
#
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
