---------------- TYPE DEFINITIONS ---------------
CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

-------------------- SOURCES --------------------
CREATE STREAM SALES (date int, store int, item int, unit_sales double, onpromotion int)
  FROM FILE './datasets/favorita/Sales.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM OIL (date int, oilprize double)
  FROM FILE './datasets/favorita/Oil.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM HOLIDAY (date int, holiday_type int, locale int, locale_id int, transferred int)
  FROM FILE './datasets/favorita/Holidays.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM TRANSACTIONS (date int, store int, transactions int)
  FROM FILE './datasets/favorita/Transactions.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM STORES (store int, city int, state int, store_type int, cluster int)
  FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM ITEMS (item int, family int, itemclass int, perishable int)
  FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV (delimiter := ',');

--------------------- MAPS ----------------------
DECLARE MAP V_date_SITSOH1(RingFactorizedRelation<[0, int]>)[][] :=
AggSum([],
  (((V_store_SITS1(RingFactorizedRelation<[1, int]>)[][date]<Local> * V_oilprize_O1(RingFactorizedRelation<[13, double]>)[][date]<Local>) * V_holiday_type_H1(RingFactorizedRelation<[14, int, int, int, int]>)[][date]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](date))
);

DECLARE MAP V_store_SITS1(RingFactorizedRelation<[1, int]>)[][date: int] :=
AggSum([date],
  (((V_item_SI1(RingFactorizedRelation<[2, int, double, int]>)[][date, store]<Local> * V_transactions_T1(RingFactorizedRelation<[8, int]>)[][date, store]<Local>) * V_city_S1(RingFactorizedRelation<[9, int, int, int, int]>)[][store]<Local>) * [lift<1>: RingFactorizedRelation<[1, int]>](store))
);

DECLARE MAP V_item_SI1(RingFactorizedRelation<[2, int, double, int]>)[][date: int, store: int] :=
AggSum([date, store],
  ((V_SALES(long)[][date, store, item, unit_sales, onpromotion] * V_family_I1(RingFactorizedRelation<[5, int, int, int]>)[][item]<Local>) * [lift<2>: RingFactorizedRelation<[2, int, double, int]>](item, unit_sales, onpromotion))
);

DECLARE MAP V_family_I1(RingFactorizedRelation<[5, int, int, int]>)[][item: int] :=
AggSum([item],
  (V_ITEMS(long)[][item, family, itemclass, perishable] * [lift<5>: RingFactorizedRelation<[5, int, int, int]>](family, itemclass, perishable))
);

DECLARE MAP V_transactions_T1(RingFactorizedRelation<[8, int]>)[][date: int, store: int] :=
AggSum([date, store],
  (V_TRANSACTIONS(long)[][date, store, transactions] * [lift<8>: RingFactorizedRelation<[8, int]>](transactions))
);

DECLARE MAP V_city_S1(RingFactorizedRelation<[9, int, int, int, int]>)[][store: int] :=
AggSum([store],
  (V_STORES(long)[][store, city, state, store_type, cluster] * [lift<9>: RingFactorizedRelation<[9, int, int, int, int]>](city, state, store_type, cluster))
);

DECLARE MAP V_oilprize_O1(RingFactorizedRelation<[13, double]>)[][date: int] :=
AggSum([date],
  (V_OIL(long)[][date, oilprize] * [lift<13>: RingFactorizedRelation<[13, double]>](oilprize))
);

DECLARE MAP V_holiday_type_H1(RingFactorizedRelation<[14, int, int, int, int]>)[][date: int] :=
AggSum([date],
  (V_HOLIDAY(long)[][date, holiday_type, locale, locale_id, transferred] * [lift<14>: RingFactorizedRelation<[14, int, int, int, int]>](holiday_type, locale, locale_id, transferred))
);
  
DECLARE MAP V_SALES(long)[][date: int, store: int, item: int, unit_sales: double, onpromotion: int] :=
  SALES(date, store, item, unit_sales, onpromotion);

DECLARE MAP V_ITEMS(long)[][item: int, family: int, itemclass: int, perishable: int] := (ITEMS(item, family, itemclass, perishable));

DECLARE MAP V_TRANSACTIONS(long)[][date: int, store: int, transactions: int] := (TRANSACTIONS(date, store, transactions));

DECLARE MAP V_STORES(long)[][store: int, city: int, state: int, store_type: int, cluster: int] := (STORES(store, city, state, store_type, cluster));

DECLARE MAP V_OIL(long)[][date: int, oilprize: double] := (OIL(date, oilprize));

DECLARE MAP V_HOLIDAY(long)[][date: int, holiday_type: int, locale: int, locale_id: int, transferred: int] := (HOLIDAY(date, holiday_type, locale, locale_id, transferred));



-------------------- QUERIES --------------------
DECLARE QUERY V_date_SITSOH1 := V_date_SITSOH1(RingFactorizedRelation<[0, int]>)[][]<Local>;

DECLARE QUERY V_store_SITS1 := V_store_SITS1(RingFactorizedRelation<[1, int]>)[][date]<Local>;

DECLARE QUERY V_item_SI1 := V_item_SI1(RingFactorizedRelation<[2, int, double, int]>)[][date, store]<Local>;

DECLARE QUERY V_family_I1 := V_family_I1(RingFactorizedRelation<[5, int, int, int]>)[][item]<Local>;

DECLARE QUERY V_transactions_T1 := V_transactions_T1(RingFactorizedRelation<[8, int]>)[][date, store]<Local>;

DECLARE QUERY V_city_S1 := V_city_S1(RingFactorizedRelation<[9, int, int, int, int]>)[][store]<Local>;

DECLARE QUERY V_oilprize_O1 := V_oilprize_O1(RingFactorizedRelation<[13, double]>)[][date]<Local>;

DECLARE QUERY V_holiday_type_H1 := V_holiday_type_H1(RingFactorizedRelation<[14, int, int, int, int]>)[][date]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF SALES {

  V_SALES(long)[][date, store, item, unit_sales, onpromotion] += (DELTA SALES)(date, store, item, unit_sales, onpromotion);

}


ON BATCH UPDATE OF OIL {

  V_OIL(long)[][date, oilprize] += (DELTA OIL)(date, oilprize);
  
}

ON BATCH UPDATE OF HOLIDAY {
  V_HOLIDAY(long)[][date, holiday_type, locale, locale_id, transferred] += (DELTA HOLIDAY)(date, holiday_type, locale, locale_id, transferred);
  
}

ON BATCH UPDATE OF TRANSACTIONS {
  V_TRANSACTIONS(long)[][date, store, transactions] += (DELTA TRANSACTIONS)(date, store, transactions);
  
}

ON BATCH UPDATE OF STORES {
  V_STORES(long)[][store, city, state, store_type, cluster] += (DELTA STORES)(store, city, state, store_type, cluster);
  
}

ON BATCH UPDATE OF ITEMS {
  V_ITEMS(long)[][item, family, itemclass, perishable] += (DELTA ITEMS)(item, family, itemclass, perishable);
  
}

ON SYSTEM READY {
  V_family_I1(RingFactorizedRelation<[5, int, int, int]>)[][item]<Local>  :=  AggSum([item],
    (V_ITEMS(item, family, itemclass, perishable) * [lift<5>: RingFactorizedRelation<[5, int, int, int]>](family, itemclass, perishable))
  );
  V_item_SI1(RingFactorizedRelation<[2, int, double, int]>)[][date, store]<Local>  :=  AggSum([date, store],
    ((V_SALES(date, store, item, unit_sales, onpromotion) * V_family_I1(RingFactorizedRelation<[5, int, int, int]>)[][item]<Local>) * [lift<2>: RingFactorizedRelation<[2, int, double, int]>](item, unit_sales, onpromotion))
  );
  V_transactions_T1(RingFactorizedRelation<[8, int]>)[][date, store]<Local>  :=  AggSum([date, store],
    (V_TRANSACTIONS(date, store, transactions) * [lift<8>: RingFactorizedRelation<[8, int]>](transactions))
  );
  V_city_S1(RingFactorizedRelation<[9, int, int, int, int]>)[][store]<Local>  :=  AggSum([store],
    (V_STORES(store, city, state, store_type, cluster) * [lift<9>: RingFactorizedRelation<[9, int, int, int, int]>](city, state, store_type, cluster))
  );
  V_store_SITS1(RingFactorizedRelation<[1, int]>)[][date]<Local>  :=  AggSum([date],
    (((V_item_SI1(RingFactorizedRelation<[2, int, double, int]>)[][date, store]<Local> * V_transactions_T1(RingFactorizedRelation<[8, int]>)[][date, store]<Local>) * V_city_S1(RingFactorizedRelation<[9, int, int, int, int]>)[][store]<Local>) * [lift<1>: RingFactorizedRelation<[1, int]>](store))
  );
  V_oilprize_O1(RingFactorizedRelation<[13, double]>)[][date]<Local>  :=  AggSum([date],
    (V_OIL(date, oilprize) * [lift<13>: RingFactorizedRelation<[13, double]>](oilprize))
  );
  V_holiday_type_H1(RingFactorizedRelation<[14, int, int, int, int]>)[][date]<Local>  :=  AggSum([date],
    (V_HOLIDAY(date, holiday_type, locale, locale_id, transferred) * [lift<14>: RingFactorizedRelation<[14, int, int, int, int]>](holiday_type, locale, locale_id, transferred))
  );
  V_date_SITSOH1(RingFactorizedRelation<[0, int]>)[][]<Local>  :=  AggSum([],
    (((V_store_SITS1(RingFactorizedRelation<[1, int]>)[][date]<Local> * V_oilprize_O1(RingFactorizedRelation<[13, double]>)[][date]<Local>) * V_holiday_type_H1(RingFactorizedRelation<[14, int, int, int, int]>)[][date]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](date))
  );
}