IMPORT DTREE FROM FILE '1.txt';

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

CREATE STREAM COMPANY_TYPE (
	company_type_id 	 INT, 
	ct_kind 	 VARCHAR(32)) 
FROM FILE './datasets/imdb/COMPANY_TYPE.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM INFO_TYPE (
	info_type_id 	 INT, 
	it_info 	 VARCHAR(32)) 
FROM FILE './datasets/imdb/INFO_TYPE.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM MOVIE_COMPANIES (
	mc_id 	 INT, 
	movie_id 	 INT, 
	company_id 	 INT, 
	company_type_id 	 INT, 
	mc_note 	 VARCHAR(32)) 
FROM FILE './datasets/imdb/MOVIE_COMPANIES.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM MOVIE_INFO_IDX (
	mii_id 	 INT, 
	movie_id 	 INT, 
	info_type_id 	 INT, 
	mii_info 	 VARCHAR(100), 
	mii_note 	 VARCHAR(255)) 
FROM FILE './datasets/imdb/MOVIE_INFO_IDX.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(1)
FROM TITLE NATURAL JOIN COMPANY_TYPE NATURAL JOIN INFO_TYPE NATURAL JOIN MOVIE_COMPANIES NATURAL JOIN MOVIE_INFO_IDX;

-- SELECT MIN(mc.note) AS production_note,
--        MIN(t.title) AS movie_title,
--        MIN(t.production_year) AS movie_year
-- FROM company_type AS ct,
--      info_type AS it,
--      movie_companies AS mc,
--      movie_info_idx AS mi_idx,
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

