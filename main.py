import csv
import pymysql
import re
import secret

# ((\(a\.k\.a\.)?.+?);[A-Z][^A-Z ]+?(?=\)|\s\()

sss = []
genres = []
films = ['0']
films_genres = ['0']

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


with open('ml-25m/movies.csv', 'r', newline='\n', encoding='UTF8') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    next(reader)
    film_info = []
    film_genres = []
    counter = 1
    validator = re.compile(r"(.+?;[ATL][^A-Z ()?!.;]{0,2})(?= \()")
    for row in reader:
        print('bbb ', films[-1])
        print('bbb ', films_genres[-1])
        film_genres.clear()
        film_info.clear()
        film_genres.append(counter)
        film_info.append(counter)
        film_info.append(row[0])
        print('ccc ', films[-1])
        print('ccc ', films_genres[-1])
        match = re.findall(validator, row[1])
        if match:
            if match[0].split(';')[-1] not in sss:
                sss.append(match[0].split(';')[-1])
            film_info.append(match[0].split(';')[-1] + ' ' + ', '.join(match[0].split(';')[:-1]))
        else:
            film_info.append(', '.join(row[1].split(';')))

        print(film_info)
        print('aaa ', films[-1])
        print('aaa ', films_genres[-1])

        if row[-1] != '(no genres listed)':
            for genre in row[-1].split('|'):
                if genre not in genres:
                    genres.append(genre)
            film_genres.append(row[-1].split('|'))
            films.append(film_info)
            films_genres.append(film_genres)
            print(1111)
            counter += 1
        print('rrr ', films[-1])
        print('rrr ', films_genres[-1])
    
# print(films)
# print('\n\n\n\n\n', films_genres)
print(', '.join(genres))

# genres_str = '("' + '"), ("'.join(sorted(genres)) + '")'
# print(genres_str)

# sql_insert('f"INSERT INTO genres (genre_name) VALUES {genres_str}"')

cur.close()
