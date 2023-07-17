IMPORT DTREE FROM FILE 'path-Q15.txt';

CREATE STREAM R1 (
	A1 	 INT, 
	A2 	 INT) 
FROM FILE './datasets/ego-twitter/R1.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R2 (
	A2 	 INT, 
	A3 	 INT) 
FROM FILE './datasets/ego-twitter/R2.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R3 (
	A3 	 INT, 
	A4 	 INT) 
FROM FILE './datasets/ego-twitter/R3.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R4 (
	A4 	 INT, 
	A5 	 INT) 
FROM FILE './datasets/ego-twitter/R4.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R5 (
	A5 	 INT, 
	A6 	 INT) 
FROM FILE './datasets/ego-twitter/R5.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R6 (
	A6 	 INT, 
	A7 	 INT) 
FROM FILE './datasets/ego-twitter/R6.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R7 (
	A7 	 INT, 
	A8 	 INT) 
FROM FILE './datasets/ego-twitter/R7.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R8 (
	A8 	 INT, 
	A9 	 INT) 
FROM FILE './datasets/ego-twitter/R8.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R9 (
	A9 	 INT, 
	A10 	 INT) 
FROM FILE './datasets/ego-twitter/R9.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R10 (
	A10 	 INT, 
	A11 	 INT) 
FROM FILE './datasets/ego-twitter/R10.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R11 (
	A11 	 INT, 
	A12 	 INT) 
FROM FILE './datasets/ego-twitter/R11.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R12 (
	A12 	 INT, 
	A13 	 INT) 
FROM FILE './datasets/ego-twitter/R12.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R13 (
	A13 	 INT, 
	A14 	 INT) 
FROM FILE './datasets/ego-twitter/R13.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R14 (
	A14 	 INT, 
	A15 	 INT) 
FROM FILE './datasets/ego-twitter/R14.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R15 (
	A15 	 INT, 
	A16 	 INT) 
FROM FILE './datasets/ego-twitter/R15.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	A1 * A16
)
FROM R1 NATURAL JOIN R2 NATURAL JOIN R3 NATURAL JOIN R4 NATURAL JOIN R5 NATURAL JOIN R6 NATURAL JOIN R7 NATURAL JOIN R8 NATURAL JOIN R9 NATURAL JOIN R10 NATURAL JOIN R11 NATURAL JOIN R12 NATURAL JOIN R13 NATURAL JOIN R14 NATURAL JOIN R15;


