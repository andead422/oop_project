#  template for secret.py file, which should be located in this directory


def getuser(): # sql username
    return ''


def getpass(): # sql user pass
    return ''


def getdb(): # database name
    return ''


def getapikey(): # api key from tmdb database
    return ''


def getquery():
    return 'SELECT film.id_film, film.title, film.popularity, GROUP_CONCAT(t.genre_titles) AS genre_titles, GROUP_CONCAT(p.tag_titles) AS tag_titles, GROUP_CONCAT(s.actor_names) AS actor_names, GROUP_CONCAT(l.director_names) AS director_names, rating.avg_rate AS avg_rate, rating.marks_quantity AS marks_quantity FROM film JOIN (SELECT film_genre.id_film AS ss, GROUP_CONCAT(genre.title) AS genre_titles FROM film_genre JOIN genre ON film_genre.id_genre = genre.id_genre GROUP BY id_film) AS t ON film.id_film = t.ss JOIN (SELECT film_tag.id_film AS pp, GROUP_CONCAT(tag.title) AS tag_titles FROM film_tag JOIN tag ON film_tag.id_tag = tag.id_tag GROUP BY id_film) AS p ON film.id_film = p.pp JOIN (SELECT film_act.id_film AS kk, GROUP_CONCAT(actor.full_name) AS actor_names FROM film_act JOIN actor ON film_act.id_act = actor.id_act GROUP BY id_film) AS s ON film.id_film = s.kk  JOIN (SELECT film_dir.id_film AS nn, GROUP_CONCAT(director.full_name) AS director_names FROM film_dir JOIN director ON film_dir.id_dir = director.id_dir GROUP BY id_film) AS l  ON film.id_film = l.nn LEFT JOIN rating on film.id_film = rating.id_film GROUP BY film.id_film'
