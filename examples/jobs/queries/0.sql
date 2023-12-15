IMPORT DTREE FROM FILE '0.txt';

CREATE TYPE RingJobs1
FROM FILE 'ring/ring_jobs_query1.hpp';

CREATE STREAM TITLE (
	movie_id 	 INT, 
	t_title 	 VARCHAR(100), 
	t_imdb_index 	 VARCHAR(12), 
	kind_id 	 INT, 
	t_production_year 	 INT, 
	imdb_id 	 INT, 
	t_phonetic_code 	 VARCHAR(5), 
	t_episode_of_id 	 INT, 
	t_season_nr 	 INT, 
	t_episode_nr 	 INT, 
	t_series_years 	 VARCHAR(49), 
	t_md5sum 	 VARCHAR(32)) 
FROM FILE './datasets/imdb/TITLE.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM MOVIE_COMPANIES (
	mc_id 	 INT, 
	movie_id 	 INT, 
	company_id 	 INT, 
	company_type_id 	 INT, 
	mc_note 	 VARCHAR(32)) 
FROM FILE './datasets/imdb/MOVIE_COMPANIES.csv' 
LINE DELIMITED CSV (delimiter := '|');

SELECT SUM([liftmoviecompanies: RingJobs1](mc_note) * 
		   [lifttitles: RingJobs1](t_production_year, t_title))
FROM TITLE NATURAL JOIN MOVIE_COMPANIES;


-- SELECT MIN(mc.note) AS production_note,
--        MIN(t.title) AS movie_title,
-- FROM movie_companies AS mc,
--      title AS t
-- WHERE ct.kind = 'production companies'
--   AND it.info = 'top 250 rank'
--   AND mc.note NOT LIKE '%(as Metro-Goldwyn-Mayer Pictures)%'
--   AND (mc.note LIKE '%(co-production)%'
--        OR mc.note LIKE '%(presents)%')
--   AND ct.id = mc.company_type_id
--   AND t.id = mc.movie_id
--   AND t.id = mi_idx.movie_id
--   AND mc.movie_id = mi_idx.movie_id
--   AND it.id = mi_idx.info_type_id;

