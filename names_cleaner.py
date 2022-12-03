import csv
import tmdbsimple as tmdb
import secret
from fuzzywuzzy import fuzz
from tempfile import NamedTemporaryFile
import shutil

tmdb.API_KEY = secret.getapikey()
temp_file = NamedTemporaryFile(mode='w', delete=False)
people = set()


def delete_people():
    global people
    with open('ml-25m/tags.csv', 'r') as tags_file, temp_file:
        reader = csv.reader(tags_file, delimiter=',')
        writer = csv.writer(temp_file, delimiter=',')
        writer.writerow('userId,movieId,tag')
        next(reader)
        search = tmdb.Search()
        for row_tags in reader:
            if row_tags[2].lower() not in people:
                if len(row_tags[2].split(' ')) >= 2:
                    for res in search.person(query=row_tags[2])['results']:
                        if fuzz.token_sort_ratio(res['name'], row_tags[2]) == 100:
                            print('person: ' + row_tags[2] + ', ' + res['name'])
                            people.add(row_tags[2].lower())
                            break
                    else:
                        print('not person: ' + row_tags[2])
                        writer.writerow(row_tags[0] + ',' + row_tags[1] + ',' + row_tags[2])
                else:
                    print('not person (too short): ' + row_tags[2])
                    writer.writerow(row_tags[0] + ',' + row_tags[1] + ',' + row_tags[2])
            else:
                print('person (in set): ' + row_tags[2])

    shutil.move(temp_file.name, 'ml-25m/tags_3.csv')


delete_people()
