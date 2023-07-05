IMPORT DTREE FROM FILE 'tpch_7_0*10-Q2.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM nation (
	nationkey 	 INT, 
	n_name 	 CHAR(25), 
	regionkey 	 INT, 
	n_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered10/nation.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM region (
	regionkey 	 INT, 
	r_name 	 CHAR(25), 
	r_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered10/region.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM customer (
	custkey 	 INT, 
	c_name 	 VARCHAR(25), 
	c_address 	 VARCHAR(40), 
	nationkey 	 INT, 
	c_phone 	 CHAR(15), 
	c_acctbal 	 DECIMAL, 
	c_mktsegment 	 CHAR(10), 
	c_comment 	 VARCHAR(117)) 
FROM FILE './datasets/tpch_unordered10/customer.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](nationkey) *
	[lift<6>: RingFactorizedRelation<[6, VARCHAR(25),INT]>](c_name,custkey) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](regionkey) *
	[lift<2>: RingFactorizedRelation<[2, VARCHAR(152),CHAR(25)]>](n_comment,n_name) *
	[lift<4>: RingFactorizedRelation<[4, VARCHAR(152),CHAR(25)]>](r_comment,r_name) 
)
FROM nation NATURAL JOIN region NATURAL JOIN customer;


