import csv
import pymysql
import re
import secret

# (?:a\.k\.a\.)?.+?;[A-Z]\S+(?:\)|\s\()

genres = []
films = []

conn = pymysql.connect(user=secret.getuser(), password=secret.getpass(), database=secret.getdb())
cur = conn.cursor()


def sql_insert(sql_string):
    cur.execute(sql_string)
    conn.commit()


with open('ml-25m\\movies.csv', 'r', newline='\n', encoding='UTF8') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    next(reader)
    film_info = []
    counter = 1
    validator = re.compile(r";[A-Z]\S{1,3}(( \()|(\)))")
    for row in reader:
        film_info.clear()
        film_info.append(counter)
        film_info.append(row[0])
        matches = re.search(validator, row[1])
        # re.search()
        print(row[1], matches)
        # for title in row[1].split(' ('):
        #     if ';The' in title:
        #         film_info.append('The ' + row[1].split(';')[0])
        #     elif ';A' in title:
        #         film_info.append('A ' + row[1].split(';')[0])
        #     elif ';La' in title:
        #         film_info.append('La ' + row[1].split(';')[0])
        #     elif ';Les' in title:
        #         film_info.append('Les ' + row[1].split(';')[0])
        #     else:
        #         film_info.append(row[1].split(' (')[0].replace(';', ', '))
        #
        #
        # if 'a.k.a.' not in row[1]:
        #     if ';The (' in row[1]:
        #         film_info.append('The ' + row[1].split(';')[0])
        #     elif ';A (' in row[1]:
        #         film_info.append('A ' + row[1].split(';')[0])
        #     elif ';La (' in row[1]:
        #         film_info.append('La ' + row[1].split(';')[0])
        #     elif ';Les (' in row[1]:
        #         film_info.append('Les ' + row[1].split(';')[0])
        #     else:
        #         film_info.append(row[1].split(' (')[0].replace(';', ', '))
        # else:
        #     print(row)
        #     for title in row[1].split(' ('):
        #         if ';The' in row[1].split(' (')[0]:
        #             film_info.append('The ' + row[1].split(';')[0])
        #         elif ';A' in row[1].split(' (')[0]:
        #             film_info.append('A ' + row[1].split(';')[0])
        #         elif ';La' in row[1].split(' (')[0]:
        #             film_info.append('La ' + row[1].split(';')[0])
        #     else:
        #         film_info.append(row[1].split(' (')[0].replace(';', ', '))

        # film_info.append(row[1].split('(')[0])
        # film_info.append(row[-2].split(')')[-1])
        # print(film_info)

        for genre in row[-1].split('|'):
            if not genre in genres:
                genres.append(genre)

        counter += 1

# print(', '.join(genres))
# genres_str = '("' + '"), ("'.join(sorted(genres[:-1])) + '")'
# print(genres_str)

# sql_insert('f"INSERT INTO genres (genre_name) VALUES {genres_str}"')

cur.close()
