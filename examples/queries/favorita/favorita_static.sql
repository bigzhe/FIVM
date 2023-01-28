IMPORT DTREE FROM FILE 'favorita.txt';

CREATE TYPE RingCofactor
FROM FILE 'ring/ring_cofactor_degree1.hpp'
WITH PARAMETER SCHEMA (dynamic_min, static, dynamic_sum);

CREATE TABLE SALES(date int, store int, item int, unit_sales double, onpromotion int)
FROM FILE './datasets/favorita/Sales.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE OIL(date int, oilprize double)
FROM FILE './datasets/favorita/Oil.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE HOLIDAY(date int, holiday_type int, locale int, locale_id int, transferred int)
FROM FILE './datasets/favorita/Holidays.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE TRANSACTIONS(date int, store int, transactions int) 
FROM FILE './datasets/favorita/Transactions.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE STORES(store int, city int, state int, store_type int, cluster int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE TABLE ITEMS(item int, family int, itemclass int, perishable int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

SELECT date, store, item, unit_sales, onpromotion, family, itemclass, perishable, transactions, city, state, store_type, cluster, oilprize, holiday_type, locale, locale_id, transferred, SUM(1)
FROM Sales NATURAL JOIN Oil NATURAL JOIN Holiday NATURAL JOIN Transactions NATURAL JOIN Stores NATURAL JOIN Items
GROUP BY date, store, item, unit_sales, onpromotion, family, itemclass, perishable, transactions, city, state, store_type, cluster, oilprize, holiday_type, locale, locale_id, transferred;

-- date, store, item, unit_sales, onpromotion, family, itemclass, perishable, transactions, city, state, store_type, cluster, oilprize, holiday_type, locale, locale_id, transferred