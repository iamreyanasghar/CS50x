SELECT name FROM people, stars, movies WHERE movies.title = 'Toy Story' AND movies.id = stars.movie_id AND people.id = stars.person_id;
