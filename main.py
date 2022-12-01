import csv
import pymysql
import re
import secret
import copy

# SELECT t1.genre_name FROM genres AS t1 JOIN film_genres AS t2 ON t1.id_genre = t2.id_genre WHERE t2.id_film = 1; выдать жанры по фильму

genres = []
films = []
films_genres = []
users = []

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


def add_movies():
    global films
    global films_genres
    with open('ml-25m/movies.csv', 'r', newline='\n', encoding='UTF8') as movies:
        reader = csv.reader(movies, delimiter=',')
        next(reader)
        film_info = []
        film_genres = []
        counter = 1
        article_checker = re.compile(r"(.+?;[ATL][^A-Z ()?!.;]{0,2})(?= \()")
        year_checker = re.compile(r"\d{4}")
        for row in reader:
            if row[-1] != '(no genres listed)':
                film_genres.clear()
                film_info.clear()
                film_genres.append(counter)
                film_info.append(counter)
                film_info.append(int(row[0]))

                article_found = re.findall(article_checker, row[1])
                if article_found:
                    film_info.append(article_found[0].split(';')[-1] + ' ' + ', '.join(article_found[0].split(';')[:-1]))
                else:
                    film_info.append(', '.join(row[1].split(' (')[0].split(';')))

                year_found = re.findall(year_checker, row[1].split('(')[-1][:4])
                if year_found:
                    film_info.append(int(year_found[0]))
                else:
                    film_info.append(0000)

                film_genres.append(row[-1].split('|'))

                films.append(copy.deepcopy(film_info))
                films_genres.append(copy.deepcopy(film_genres))

                film_str = '(' + str(film_info[0]) + ', ' + str(film_info[1]) + ', "' + str(film_info[2]) + '", ' + str(film_info[3]) + ')'
                sql_insert(f"INSERT INTO film (id_film, id_film_source, title, year) VALUES {film_str}")

                for genre in row[-1].split('|'):
                    if genre not in genres:
                        genres.append(genre)
                counter += 1

    # for film in films:
    #     film_str = '(' + str(film[0]) + ', ' + str(film[1]) + ', "' + str(film[2]) + '", ' + str(film[3]) + ')'
    #     sql_insert(f"INSERT INTO film (id_film, id_film_source, title, year) VALUES {film_str}")

    genres_str = '("' + '"), ("'.join(sorted(genres)) + '")'
    sql_insert(f"INSERT INTO genres (genre_name) VALUES {genres_str}")

    id_genres = sql_select_all('SELECT * FROM genres')
    id_genres = dict((y, x) for x, y in id_genres)

    for fg in films_genres:
        for gg in fg[1]:
            fg_str = '(' + str(fg[0]) + ', ' + str(id_genres[gg]) + ')'
            print(fg_str)
            sql_insert(f"INSERT INTO film_genres (id_film, id_genre) VALUES {fg_str}")


def add_rating():
    global films
    with open('ml-25m/ratings.csv', 'r', newline='\n', encoding='UTF8') as rating:
        reader_1 = csv.reader(rating, delimiter=',')
        next(reader_1)
        counter = 1
        for row_rating in reader_1:
            if row_rating[0] not in users:
                print(counter, row_rating[0])
                users.append([counter, row_rating[0]])
                sql_insert(f"INSERT INTO users VALUES ({counter}, {int(row_rating[0])})")
                counter += 1
            users_dict = dict((y, x) for x, y in users)
            sql_insert(f"INSERT INTO rating (id_user, id_film, rating) VALUES ({users_dict[row_rating[0]]}, {films[row_rating[1]]}, {row_rating[2]}")


def add_tags():
    with open('ml-25m/tags.csv', 'r', newline='\n', encoding='UTF8') as tags:
        reader_2 = csv.reader(tags, delimiter=',')
        next(reader_2)




add_movies()

films = dict((y, x) for x, y, a, b in films)
print(films)

# add_rating()

conn.commit()
cur.close()
