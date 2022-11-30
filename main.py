import csv
import pymysql
import re
import secret
import copy

# ((\(a\.k\.a\.)?.+?);[A-Z][^A-Z ]+?(?=\)|\s\()

genres = []
films = []
films_genres = []

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


def sql_select_all(sql_string):
    cur.execute(sql_string)
    return cur.fetchall()


def add_movies():
    global films
    global films_genres
    with open('ml-25m/movies.csv', 'r', newline='\n', encoding='UTF8') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
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

                for genre in row[-1].split('|'):
                    if genre not in genres:
                        genres.append(genre)

                counter += 1


def add_rating():
    with open('ml-25m/ratings.csv', 'r', newline='\n', encoding='UTF8') as csvfile:
        pass


add_movies()
# print(films)
# print('\n\n\n\n\n', films_genres)
# print(genres)

for film in films:
    film_str = '(' + str(film[0]) + ', ' + str(film[1]) + ', "' + str(film[2]) + '", ' + str(film[3]) + ')'
    sql_insert(f"INSERT INTO film (id_film, id_film_source, title, year) VALUES {film_str}")

genres_str = '("' + '"), ("'.join(sorted(genres)) + '")'
sql_insert(f"INSERT INTO genres (genre_name) VALUES {genres_str}")

id_genres = sql_select_all('SELECT * FROM genres')
id_genres = dict((y, x) for x, y in id_genres)

for fg in films_genres:
    for genre in fg[1]:
        fg_str = '(' + str(fg[0]) + ', ' + str(id_genres[genre]) + ')'
        print(fg_str)
        sql_insert(f"INSERT INTO film_genres (id_film, id_genre) VALUES {fg_str}")


conn.commit()
cur.close()
