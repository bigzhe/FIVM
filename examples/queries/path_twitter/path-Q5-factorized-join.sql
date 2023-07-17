IMPORT DTREE FROM FILE 'path-Q5.txt';

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


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](A4) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](A2) *
	[lift<2>: RingFactorizedRelation<[2, INT]>](A1) *
	[lift<3>: RingFactorizedRelation<[3, INT]>](A3) *
	[lift<4>: RingFactorizedRelation<[4, INT]>](A6) *
	[lift<5>: RingFactorizedRelation<[5, INT]>](A5) 
)
FROM R1 NATURAL JOIN R2 NATURAL JOIN R3 NATURAL JOIN R4 NATURAL JOIN R5;


