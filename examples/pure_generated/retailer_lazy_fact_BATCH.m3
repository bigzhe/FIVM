---------------- TYPE DEFINITIONS ---------------
CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

-------------------- SOURCES --------------------
CREATE STREAM INVENTORY (locn int, dateid int, ksn int, inventoryunits int)
  FROM FILE './datasets/retailer/Inventory.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM LOCATION (locn int, zip int, rgn_cd int, clim_zn_nbr int, tot_area_sq_ft int, sell_area_sq_ft int, avghhi int, supertargetdistance double, supertargetdrivetime double, targetdistance double, targetdrivetime double, walmartdistance double, walmartdrivetime double, walmartsupercenterdistance double, walmartsupercenterdrivetime double)
  FROM FILE './datasets/retailer/Location.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM CENSUS (zip int, population int, white int, asian int, pacific int, blackafrican int, medianage double, occupiedhouseunits int, houseunits int, families int, households int, husbwife int, males int, females int, householdschildren int, hispanic int)
  FROM FILE './datasets/retailer/Census.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM ITEM (ksn int, subcategory byte, category byte, categoryCluster byte, prize double)
  FROM FILE './datasets/retailer/Item.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM WEATHER (locn int, dateid int, rain byte, snow byte, maxtemp int, mintemp int, meanwind double, thunder byte)
  FROM FILE './datasets/retailer/Weather.tbl' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------
DECLARE MAP V_locn_IIWLC1(RingFactorizedRelation<[0, int]>)[][] :=
  AggSum([],
    ((V_dateid_IIW1(RingFactorizedRelation<[1, int]>)[][locn]<Local> * V_zip_LC1(RingFactorizedRelation<[14, int]>)[][locn]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](locn))
  );

DECLARE MAP V_dateid_IIW1(RingFactorizedRelation<[1, int]>)[][locn: int] :=
  AggSum([locn],
    ((V_ksn_II1(RingFactorizedRelation<[2, int, int]>)[][locn, dateid]<Local> * V_rain_W1(RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>)[][locn, dateid]<Local>) * [lift<1>: RingFactorizedRelation<[1, int]>](dateid))
  );

DECLARE MAP V_ksn_II1(RingFactorizedRelation<[2, int, int]>)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    ((V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] * V_subcategory_I1(RingFactorizedRelation<[4, byte, byte, byte, double]>)[][ksn]<Local>) * [lift<2>: RingFactorizedRelation<[2, int, int]>](ksn, inventoryunits))
  );

DECLARE MAP V_subcategory_I1(RingFactorizedRelation<[4, byte, byte, byte, double]>)[][ksn: int] :=
  AggSum([ksn],
    (V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] * [lift<4>: RingFactorizedRelation<[4, byte, byte, byte, double]>](subcategory, category, categoryCluster, prize))
  );

DECLARE MAP V_rain_W1(RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    (V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] * [lift<8>: RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>](rain, snow, maxtemp, mintemp, meanwind, thunder))
  );

DECLARE MAP V_zip_LC1(RingFactorizedRelation<[14, int]>)[][locn: int] :=
  AggSum([locn],
    ((V_rgn_cd_L1(RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>)[][locn, zip]<Local> * V_population_C1(RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][zip]<Local>) * [lift<14>: RingFactorizedRelation<[14, int]>](zip))
  );

DECLARE MAP V_rgn_cd_L1(RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>)[][locn: int, zip: int] :=
  AggSum([locn, zip],
    (V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] * [lift<15>: RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>](rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime))
  );

DECLARE MAP V_population_C1(RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][zip: int] :=
  AggSum([zip],
    (V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] * [lift<28>: RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>](population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic))
  );

DECLARE MAP V_INVENTORY(long)[][locn: int, dateid: int, ksn: int, inventoryunits: int] := INVENTORY(locn, dateid, ksn, inventoryunits);

DECLARE MAP V_LOCATION(long)[][locn: int, zip: int, rgn_cd: int, clim_zn_nbr: int, tot_area_sq_ft: int, sell_area_sq_ft: int, avghhi: int, supertargetdistance: double, supertargetdrivetime: double, targetdistance: double, targetdrivetime: double, walmartdistance: double, walmartdrivetime: double, walmartsupercenterdistance: double, walmartsupercenterdrivetime: double] := LOCATION(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);

DECLARE MAP V_CENSUS(long)[][zip: int, population: int, white: int, asian: int, pacific: int, blackafrican: int, medianage: double, occupiedhouseunits: int, houseunits: int, families: int, households: int, husbwife: int, males: int, females: int, householdschildren: int, hispanic: int] := CENSUS(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);

DECLARE MAP V_ITEM(long)[][ksn: int, subcategory: byte, category: byte, categoryCluster: byte, prize: double] := ITEM(ksn, subcategory, category, categoryCluster, prize);

DECLARE MAP V_WEATHER(long)[][locn: int, dateid: int, rain: byte, snow: byte, maxtemp: int, mintemp: int, meanwind: double, thunder: byte] := WEATHER(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);

-------------------- QUERIES --------------------
DECLARE QUERY V_locn_IIWLC1 := V_locn_IIWLC1(RingFactorizedRelation<[0, int]>)[][]<Local>;

DECLARE QUERY V_dateid_IIW1 := V_dateid_IIW1(RingFactorizedRelation<[1, int]>)[][locn]<Local>;

DECLARE QUERY V_ksn_II1 := V_ksn_II1(RingFactorizedRelation<[2, int, int]>)[][locn, dateid]<Local>;

DECLARE QUERY V_subcategory_I1 := V_subcategory_I1(RingFactorizedRelation<[4, byte, byte, byte, double]>)[][ksn]<Local>;

DECLARE QUERY V_rain_W1 := V_rain_W1(RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>)[][locn, dateid]<Local>;

DECLARE QUERY V_zip_LC1 := V_zip_LC1(RingFactorizedRelation<[14, int]>)[][locn]<Local>;

DECLARE QUERY V_rgn_cd_L1 := V_rgn_cd_L1(RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>)[][locn, zip]<Local>;

DECLARE QUERY V_population_C1 := V_population_C1(RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][zip]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF INVENTORY {
  V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] += (DELTA INVENTORY)(locn, dateid, ksn, inventoryunits);
}

ON BATCH UPDATE OF LOCATION {
  V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] += (DELTA LOCATION)(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);
}

ON BATCH UPDATE OF CENSUS {
  V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] += (DELTA CENSUS)(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);
}

ON BATCH UPDATE OF ITEM {
  V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] += (DELTA ITEM)(ksn, subcategory, category, categoryCluster, prize);
}

ON BATCH UPDATE OF WEATHER {
  V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] += (DELTA WEATHER)(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);
}

ON SYSTEM READY {
  V_subcategory_I1(RingFactorizedRelation<[4, byte, byte, byte, double]>)[][ksn]<Local>  :=  AggSum([ksn],
    (V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] * [lift<4>: RingFactorizedRelation<[4, byte, byte, byte, double]>](subcategory, category, categoryCluster, prize))
  );
  V_ksn_II1(RingFactorizedRelation<[2, int, int]>)[][locn, dateid]<Local>  :=  AggSum([locn, dateid],
    ((V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] * V_subcategory_I1(RingFactorizedRelation<[4, byte, byte, byte, double]>)[][ksn]<Local>) * [lift<2>: RingFactorizedRelation<[2, int, int]>](ksn, inventoryunits))
  );
  V_rain_W1(RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>)[][locn, dateid]<Local>  :=  AggSum([locn, dateid],
    (V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] * [lift<8>: RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>](rain, snow, maxtemp, mintemp, meanwind, thunder))
  );
  V_dateid_IIW1(RingFactorizedRelation<[1, int]>)[][locn]<Local>  :=  AggSum([locn],
    ((V_ksn_II1(RingFactorizedRelation<[2, int, int]>)[][locn, dateid]<Local> * V_rain_W1(RingFactorizedRelation<[8, byte, byte, int, int, double, byte]>)[][locn, dateid]<Local>) * [lift<1>: RingFactorizedRelation<[1, int]>](dateid))
  );
  V_rgn_cd_L1(RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>)[][locn, zip]<Local>  :=  AggSum([locn, zip],
    (V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] * [lift<15>: RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>](rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime))
  );
  V_population_C1(RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][zip]<Local>  :=  AggSum([zip],
    (V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] * [lift<28>: RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>](population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic))
  );
  V_zip_LC1(RingFactorizedRelation<[14, int]>)[][locn]<Local>  :=  AggSum([locn],
    ((V_rgn_cd_L1(RingFactorizedRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>)[][locn, zip]<Local> * V_population_C1(RingFactorizedRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][zip]<Local>) * [lift<14>: RingFactorizedRelation<[14, int]>](zip))
  );
  V_locn_IIWLC1(RingFactorizedRelation<[0, int]>)[][]<Local>  :=  AggSum([],
    ((V_dateid_IIW1(RingFactorizedRelation<[1, int]>)[][locn]<Local> * V_zip_LC1(RingFactorizedRelation<[14, int]>)[][locn]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](locn))
  );
}