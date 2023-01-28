IMPORT DTREE FROM FILE 'favorita.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM SALES(date int, store int, item int, unit_sales double, onpromotion int)
FROM FILE './datasets/favorita/Sales.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM OIL(date int, oilprize double)
FROM FILE './datasets/favorita/Oil.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM HOLIDAY(date int, holiday_type int, locale int, locale_id int, transferred int)
FROM FILE './datasets/favorita/Holidays.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM TRANSACTIONS(date int, store int, transactions int) 
FROM FILE './datasets/favorita/Transactions.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE STORES(store int, city int, state int, store_type int, cluster int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM ITEMS(item int, family int, itemclass int, perishable int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

SELECT SUM(
    [lift<0>: RingFactorizedRelation<[0,int]>](date) *
    [lift<1>: RingFactorizedRelation<[1,int]>](store) *
    [lift<2>: RingFactorizedRelation<[2,int,double,int]>](item, unit_sales, onpromotion) *
    [lift<5>: RingFactorizedRelation<[5,int,int,int]>](family, itemclass, perishable) *
    [lift<8>: RingFactorizedRelation<[8,int]>](transactions) *
    [lift<9>: RingFactorizedRelation<[9,int,int,int,int]>](city, state, store_type, cluster) *
    [lift<13>: RingFactorizedRelation<[13,double]>](oilprize) *
    [lift<14>: RingFactorizedRelation<[14,int,int,int,int]>](holiday_type, locale, locale_id, transferred)
)
FROM Sales NATURAL JOIN Oil NATURAL JOIN Holiday NATURAL JOIN Transactions NATURAL JOIN Stores NATURAL JOIN Items;