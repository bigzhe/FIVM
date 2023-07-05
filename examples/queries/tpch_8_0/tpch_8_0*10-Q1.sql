IMPORT DTREE FROM FILE 'tpch_8_0*10-Q1.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM partsupp (
	partkey 	 INT, 
	suppkey 	 INT, 
	ps_availqty 	 INT, 
	ps_supplycost 	 DECIMAL, 
	ps_comment 	 VARCHAR(199)) 
FROM FILE './datasets/tpch_unordered10/partsupp.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM lineitem (
	orderkey 	 INT, 
	partkey 	 INT, 
	suppkey 	 INT, 
	l_linenumber 	 INT, 
	l_quantity 	 DECIMAL, 
	l_extendedprice 	 DECIMAL, 
	l_discount 	 DECIMAL, 
	l_tax 	 DECIMAL, 
	l_returnflag 	 CHAR(1), 
	l_linestatus 	 CHAR(1), 
	l_shipdate 	 CHAR(10), 
	l_commitdate 	 CHAR(10), 
	l_receiptdate 	 CHAR(10), 
	l_shipinstruct 	 CHAR(25), 
	l_shipmode 	 CHAR(10), 
	l_comment 	 VARCHAR(44)) 
FROM FILE './datasets/tpch_unordered10/lineitem.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](suppkey) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](partkey) *
	[lift<2>: RingFactorizedRelation<[2, INT,DECIMAL]>](orderkey,l_quantity) 
)
FROM partsupp NATURAL JOIN lineitem;


