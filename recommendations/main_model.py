import numpy as np
import pandas as pd
import ast
import sys
import os
from pymysql import connect

from sklearn.feature_extraction.text import TfidfVectorizer, CountVectorizer
from sklearn.metrics.pairwise import linear_kernel, cosine_similarity

absolute_path = os.path.dirname(__file__)
relative_path = "../secrets"
full_path = os.path.join(absolute_path, relative_path)
sys.path.insert(1, full_path)

import secret
#Не забути завантажити собі через "pip install <package_name>" всі бібліотеки
USER_LOGIN = secret.getUser()
USER_PASSWD = secret.getPass()
DB_NAME = secret.getDB()
QUERY = secret.getQuery()

#Підключення до бд
data_base = connect(host = 'localhost',
                    user = USER_LOGIN,
                    passwd = USER_PASSWD,
                    database = DB_NAME)
cur = data_base.cursor()
# query = QUERY
cur.execute(QUERY)
df_film = pd.read_sql(QUERY, data_base)
df_film['id_film'] = df_film['id_film'].astype(int)


#Створення щось по типу свого IMDB рейтингу
avg_rate = df_film['avg_rate']
marks_quantity = df_film['marks_quantity']
C = avg_rate.mean()
m = marks_quantity.quantile(0)
df_film = df_film[(df_film['marks_quantity'] >= m) & (df_film['marks_quantity'].notnull()) & (df_film['avg_rate'].notnull())]

def weighted_rating(x):
    v = x['marks_quantity']
    R = x['avg_rate']
    return ((v/(v+m) * R) + (m/(m+v) * C)) * 2


df_film['wr'] = df_film.apply(weighted_rating, axis=1)
test_ds = df_film.sort_values('wr', ascending=False).head(20)


#Закидуємо всю ключову інфу про фільм в одну колонку "суп"
df_film['soup'] = df_film['genre_titles'].str.replace(',', ' ') + df_film['actor_names'].str.replace(',', ' ') + df_film['director_names'].str.replace(',', ' ') + df_film['tag_titles'].str.replace(',',' ')
df_film['soup'] = df_film['soup'].fillna('')


#Знаходимо матрицю косинусу подібності, де i-ий рядок відповідаю i-му фільму
count = CountVectorizer(analyzer='word', ngram_range=(1, 2), min_df=0, stop_words='english')
count_matrix = count.fit_transform(df_film['soup'])
cosine_sim = cosine_similarity(count_matrix, count_matrix)

# Створюємо допоміжний pandas series, для того щоб пронумерувати айді фільмів у тому порядку, в якому вони у нас зараз розташовані в таблиці.
# Це треба для того, щоб якщо ми якось сортували(або хочемо сортувати) нашу таблицю, ми могли переіндексувати наші данні,
# так-як розташування рядків матриці косинусу подібності зумовлений лише порядком елементів в таблиці, які ми передали в функцію, а не індексами фільмів.
df_film = df_film.reset_index()
id_films = df_film['id_film']
indices = pd.Series(df_film.index, index=df_film['id_film'])

#Функція отримання косинусу подібності всіх фільмів з фільмом 'id_film'
def get_recommendations(id_film):
    idx = indices[id_film]
    return np.array(cosine_sim[idx])



#Сама рекомендаційна система. На вхід отримує кількість фільмів які юзеров оцінив. Далі по черзі на вхід отримуємо id_film(72) і film_mark(75).
def recommendation_system(string_dict_of_films):
    dict_of_films = ast.literal_eval(string_dict_of_films)
    film_count = len(dict_of_films)
    arr = np.zeros(indices.size)
    user_film_id_idx = set()
    for key, value  in dict_of_films.items():
        user_film_id = key
        user_film_id_idx.add(indices[user_film_id])
        film_score = value
        k = film_score / 5.
        arr = arr + get_recommendations(user_film_id) * k / film_count

    sim_scores = list(enumerate(arr))
    sim_scores = sorted(sim_scores, key=lambda x: x[1], reverse=True)
    sim_scores = sim_scores[0:30]
    movie_indices = {i[0] for i in sim_scores}
    movie_indices = movie_indices - user_film_id_idx
    ans = id_films.iloc[list(movie_indices)].head(5).tolist()
    s = ''.join(str(x)+" " for x in ans)
    return s