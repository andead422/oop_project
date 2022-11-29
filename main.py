import csv
import pymysql
import secret

genres = []
films = []

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


with open('C:\\Users\\andyk\\Downloads\\ml-25m\\ml-25m\\movies.csv', 'r', newline='\n', encoding='UTF8') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    next(reader)
    film_info = []
    for row in reader:
        counter = 1
        film_info.clear()
        film_info.append(counter)
        film_info.append(row[0])
        film_info.append(row[1].split('(')[0])
        film_info.append(row[-2].split(')')[-1])
        print(film_info)

        for genre in row[-1].split('|'):
            if not genre in genres:
                genres.append(genre)
        counter += 1

# print(', '.join(genres))
# genres_str = '("' + '"), ("'.join(sorted(genres[:-1])) + '")'
# print(genres_str)

# sql_insert('f"INSERT INTO genres (genre_name) VALUES {genres_str}"')

cur.close()
