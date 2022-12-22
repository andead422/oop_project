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

start_time = time.time()

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()
tmdb.API_KEY = secret.getapikey()

word_tags = {}


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


def popul_getter(tmdb_id):
    flag = 2
    while flag > 0:
        try:
            film_tmdb = tmdb.Movies(tmdb_id)
            return film_tmdb.info()['popularity']
        except:
            print('reconnecting...')
            # print(err)
            time.sleep(0.5)
            flag -= 1
    return 'NULL'


def rate_getter(tmdb_id):
    flag = 2
    while flag > 0:
        try:
            film_tmdb = tmdb.Movies(tmdb_id)
            return [film_tmdb.info()['vote_average'], film_tmdb.info()['vote_count']]
        except:
            print('reconnecting...')
            # print(err)
            time.sleep(0.5)
            flag -= 1
    return 'NULL'


def add_films():
    genres = []
    films = []
    films_genres = []
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
    sql_insert(
        "UPDATE rating t1 SET t1.id_film = (SELECT t2.id_film FROM film t2 WHERE t2.id_film_source = t1.id_film_source)")

    print('All films connected to rating in db ' + secret.getdb())

    sql_insert("ALTER TABLE rating DROP COLUMN id_film_source")
    sql_insert("DELETE FROM rating WHERE id_film = NULL")
    sql_insert("ALTER TABLE rating MODIFY COLUMN id_film int NOT NULL")

    sql_insert("CREATE INDEX index_id_film_r ON rating(id_film)")


def add_popul():
    film_ids = sql_select_all(
        "SELECT t1.id_film, t1.id_tmdb FROM link t1 WHERE t1.id_film IN (SELECT t2.id_film FROM film t2 WHERE t2.popularity IS NULL)")
    print(len(film_ids))
    film_ids = dict(film_ids)
    for film in list(film_ids.keys()):
        popularity = popul_getter(film_ids[film])
        if popularity != 'NULL':
            print('film: ' + str(film) + ', popularity: ' + str(popularity))
            sql_insert(f"UPDATE film SET popularity = {popularity} WHERE id_film = {film}")


def sort_tag():
    global word_tags
    all_tags = sql_select_all("SELECT * FROM tag_tmp")
    negation_tog_start = re.compile(r"^(?:in|un|im|il|ir|de|mis|a|non)(?=\w+)")
    negation_tog_end = re.compile(r"\w+less")
    negation_sep = re.compile(r"(?:not|aint|amnt|isnt|arent|havent|hasnt|hadnt|dont|didnt|wont)")
    neg_str = 'NEEEEEEEEEEEEEG'
    for tag_info in all_tags:
        word_list = tag_info[2].split(' ')
        for ii in range(len(word_list)):
            if len(word_list[ii]) >= 4:
                print('before corr: ' + word_list[ii])
                if re.search(negation_sep, word_list[ii]):
                    for jj in range(len(word_list[ii + 1:])):
                        if len(word_list[ii + 1 + jj]) >= 4:
                            word_list[ii + 1 + jj] = neg_str + word_list[ii + 1 + jj]
                            break
                    continue
                elif re.search(negation_tog_end, word_list[ii]):
                    word_list[ii] = neg_str + word_list[ii][:-4]
                else:
                    re.sub(negation_tog_start, neg_str, word_list[ii])
                print('after corr: ' + word_list[ii])
                for tag_sorted in list(word_tags.keys()):
                    match = fuzz.token_sort_ratio(word_list[ii], tag_sorted)
                    if match > 80:
                        print('match with ' + str(match) + '%: ' + word_list[ii] + ', ' + tag_sorted)
                        if tag_info[1] in list(word_tags[tag_sorted].keys()):
                            word_tags[tag_sorted][tag_info[1]].add(tag_info[0])
                        else:
                            word_tags[tag_sorted][tag_info[1]] = {tag_info[0]}
                        break
                else:
                    print('no match for ' + word_list[ii])
                    word_tags[word_list[ii]] = {tag_info[1]: {tag_info[0]}}
    print(word_tags)
    for tag in list(word_tags.keys()):
        if len(word_tags[tag]) < 3:
            word_tags.pop(tag)
        else:
            for tag_film in list(word_tags[tag].keys()):
                if len(word_tags[tag][tag_film]) < 2:
                    word_tags[tag].pop(tag_film)
            if len(word_tags[tag]) < 3:
                word_tags.pop(tag)
    print(word_tags)


def add_tag():
    global word_tags
    tags_list = list(word_tags.keys())
    tags_str = '("' + '"), ("'.join(sorted(tags_list)) + '")'
    sql_insert(f"INSERT INTO tag (title) VALUES {tags_str}")
    tag_dict = dict(sql_select_all("SELECT title, id_tag FROM tag"))
    film_dict = dict(sql_select_all("SELECT id_film_source, id_film FROM film"))
    for tag in tags_list:
        for film_tag in list(word_tags[tag].keys()):
            if film_tag in list(film_dict.keys()):
                print('film:', film_dict[film_tag], 'tag:', tag, 'tag_id:', tag_dict[tag], 'quantity:',
                      len(word_tags[tag][film_tag]))
                sql_insert(
                    f"INSERT INTO film_tag (id_film, id_tag, quantity) VALUES ({film_dict[film_tag]}, {tag_dict[tag]}, {len(word_tags[tag][film_tag])})")


def add_cast(partitions_quan=1):
    actors = set()
    directors = set()
    actors_actual = set()
    directors_actual = set()
    film_actors = {}
    film_directors = {}
    errors_list = []
    no_data_list = []
    links = sql_select_all("SELECT id_film, id_tmdb FROM links")
    quan_films = len(links)
    part_no = 1
    cur_film_id = 0
    while part_no <= partitions_quan:
        while quan_films * ((part_no - 1) / partitions_quan) <= cur_film_id <= quan_films * (part_no / partitions_quan):
            film = links[cur_film_id]
            result = cast_getter(film[1])
            if result != 'NULL':
                if result['cast'] != [] and result['crew'] != []:
                    counter = 0
                    film_actors[film[0]] = []
                    film_directors[film[0]] = []
                    for cast in result['cast']:
                        if counter < 5:
                            if not (cast['original_name'].replace('"', '\\"') in actors or cast[
                                'original_name'].replace('"', '\\"') in actors_actual):
                                actors_actual.add(cast['original_name'].replace('"', '\\"'))
                                actors.add(cast['original_name'].replace('"', '\\"'))
                            film_actors[film[0]].append(cast['original_name'].replace('"', '\\"'))
                            counter += 1
                    for crew in result['crew']:
                        if crew['job'] == 'Director':
                            if not (crew['original_name'].replace('"', '\\"') in directors or cast[
                                'original_name'].replace('"', '\\"') in directors_actual):
                                directors_actual.add(crew['original_name'].replace('"', '\\"'))
                                directors.add(crew['original_name'].replace('"', '\\"'))
                            film_directors[film[0]].append(crew['original_name'].replace('"', '\\"'))
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
        print(actors_str)
        print(directors_str)
        sql_insert(f"INSERT INTO actors (full_name) VALUES {actors_str}")
        sql_insert(f"INSERT INTO directors (full_name) VALUES {directors_str}")
        actors_actual.clear()
        directors_actual.clear()
        print('All actors and directors added to db ' + secret.getdb())
        actors_ids = sql_select_all("SELECT * FROM actors")
        directors_ids = sql_select_all("SELECT * FROM directors")
        actors_ids = {y: x for x, y in actors_ids}
        directors_ids = {y: x for x, y in directors_ids}
        for film_ids in film_actors.keys():
            for film_cast in film_actors[film_ids]:
                sql_insert(f"INSERT INTO film_act (id_film, id_act) VALUES ({film_ids}, {actors_ids[film_cast]})")
        for film_ids in film_directors.keys():
            for film_crew in film_directors[film_ids]:
                sql_insert(f"INSERT INTO film_dir (id_film, id_dir) VALUES ({film_ids}, {directors_ids[film_crew]})")
        film_actors.clear()
        film_directors.clear()
        print('iteration no. ' + str(part_no) + ' ended')
        print(no_data_list)
        print(errors_list)
        part_no += 1


def add_tmdb_rate():
    rate_info = sql_select_all(
        "SELECT t1.id_film, t1.id_tmdb, t2.avg_rate, t2.marks_quantity FROM link t1 WHERE t1.id_film IN (SELECT t2.id_film FROM rating t2 WHERE t2.flag = 0)")
    print(len(rate_info))
    for film_rate in rate_info:
        rate_tmdb_details = rate_getter(film_rate[1])
        sql_insert(
            f"UPDATE rating SET avg_rate = {rate_info[2] + (rate_tmdb_details[0] / 2)}, marks_quantity = {rate_info[3] + rate_tmdb_details[1]}, flag = 1 WHERE id_film = {rate_info[0]}")


# add_films()
# add_rating()
# add_cast(5)
# add_popul()
# sort_tag()
# sort_time = time.time()
# print('sort_tag time is', sort_time-start_time)
# add_tag()
add_tmdb_rate()

conn.commit()
cur.close()

# print('add time is', time.time()-sort_time)
print('exec time is', time.time() - start_time)
