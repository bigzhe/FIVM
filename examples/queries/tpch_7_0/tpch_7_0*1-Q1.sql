IMPORT DTREE FROM FILE 'tpch_7_0*1-Q1.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM nation (
	nationkey 	 INT, 
	n_name 	 CHAR(25), 
	regionkey 	 INT, 
	n_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered1/nation.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM region (
	regionkey 	 INT, 
	r_name 	 CHAR(25), 
	r_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered1/region.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](regionkey) *
	[lift<1>: RingFactorizedRelation<[1, VARCHAR(152),CHAR(25),INT]>](n_comment,n_name,nationkey) *
	[lift<4>: RingFactorizedRelation<[4, CHAR(25),VARCHAR(152)]>](r_name,r_comment) 
)
FROM nation NATURAL JOIN region;


