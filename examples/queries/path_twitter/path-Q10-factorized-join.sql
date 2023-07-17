IMPORT DTREE FROM FILE 'path-Q10.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/RingFactorizedRelation.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

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


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](A6) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](A3) *
	[lift<2>: RingFactorizedRelation<[2, INT]>](A2) *
	[lift<3>: RingFactorizedRelation<[3, INT]>](A1) *
	[lift<4>: RingFactorizedRelation<[4, INT]>](A5) *
	[lift<5>: RingFactorizedRelation<[5, INT]>](A4) *
	[lift<6>: RingFactorizedRelation<[6, INT]>](A9) *
	[lift<7>: RingFactorizedRelation<[7, INT]>](A8) *
	[lift<8>: RingFactorizedRelation<[8, INT]>](A7) *
	[lift<9>: RingFactorizedRelation<[9, INT]>](A11) *
	[lift<10>: RingFactorizedRelation<[10, INT]>](A10) 
)
FROM R1 NATURAL JOIN R2 NATURAL JOIN R3 NATURAL JOIN R4 NATURAL JOIN R5 NATURAL JOIN R6 NATURAL JOIN R7 NATURAL JOIN R8 NATURAL JOIN R9 NATURAL JOIN R10;


