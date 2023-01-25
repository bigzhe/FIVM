---------------- TYPE DEFINITIONS ---------------


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
DECLARE MAP V_locn_IIWLC1(long)[][locn: int] :=
    (V_dateid_IIW2(long)[][locn]<Local> * V_zip_LC2(long)[][locn]<Local>);

DECLARE MAP V_dateid_IIW2(long)[][locn: int] :=
  AggSum([locn],
    V_dateid_IIW1(long)[][locn, dateid]<Local>
  );

DECLARE MAP V_dateid_IIW1(long)[][locn: int, dateid: int] :=
    (V_ksn_II2(long)[][locn, dateid]<Local> * V_rain_W1(long)[][locn, dateid]<Local>);

DECLARE MAP V_ksn_II2(long)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    V_ksn_II1(long)[][locn, dateid, ksn]<Local>
  );

DECLARE MAP V_ksn_II1(long)[][locn: int, dateid: int, ksn: int] :=
    (V_inventoryunits_I1(long)[][locn, dateid, ksn]<Local> * V_subcategory_I1(long)[][ksn]<Local>);

DECLARE MAP V_inventoryunits_I1(long)[][locn: int, dateid: int, ksn: int] :=
  AggSum([locn, dateid, ksn],
    INVENTORY(locn, dateid, ksn, inventoryunits)
  );

DECLARE MAP V_subcategory_I1(long)[][ksn: int] :=
  AggSum([ksn],
    ITEM(ksn, subcategory, category, categoryCluster, prize)
  );

DECLARE MAP V_rain_W1(long)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    WEATHER(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder)
  );

DECLARE MAP V_zip_LC2(long)[][locn: int] :=
  AggSum([locn],
    V_zip_LC1(long)[][locn, zip]<Local>
  );

DECLARE MAP V_zip_LC1(long)[][locn: int, zip: int] :=
    (V_rgn_cd_L1(long)[][locn, zip]<Local> * V_population_C1(long)[][zip]<Local>);

DECLARE MAP V_rgn_cd_L1(long)[][locn: int, zip: int] :=
  AggSum([locn, zip],
    LOCATION(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)
  );

DECLARE MAP V_population_C1(long)[][zip: int] :=
  AggSum([zip],
    CENSUS(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic)
  );

DECLARE MAP TMP_SUM1(long)[][locn: int, dateid: int, ksn: int] :=
  AggSum([locn, dateid, ksn],
    (DELTA INVENTORY)(locn, dateid, ksn, inventoryunits)
  );

DECLARE MAP TMP_SUM2(long)[][locn: int, dateid: int, ksn: int] :=
    (TMP_SUM1(long)[][locn, dateid, ksn]<Local> * V_subcategory_I1(long)[][ksn]<Local>);

DECLARE MAP TMP_SUM2_PRIME(long)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    TMP_SUM2(long)[][locn, dateid, ksn]<Local>
  );

DECLARE MAP TMP_SUM3(long)[][locn: int, dateid: int] :=
    (TMP_SUM2_PRIME(long)[][locn, dateid]<Local> * V_rain_W1(long)[][locn, dateid]<Local>);

DECLARE MAP TMP_SUM3_PRIME(long)[][locn: int] :=
  AggSum([locn],
    TMP_SUM3(long)[][locn, dateid]<Local>
  );

DECLARE MAP TMP_SUM4(long)[][locn: int, zip: int] :=
  AggSum([locn, zip],
    (DELTA LOCATION)(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)
  );

DECLARE MAP TMP_SUM5(long)[][locn: int, zip: int] :=
    (TMP_SUM4(long)[][locn, zip]<Local> * V_population_C1(long)[][zip]<Local>);

DECLARE MAP TMP_SUM5_PRIME(long)[][locn: int] :=
  AggSum([locn],
    TMP_SUM5(long)[][locn, zip]<Local>
  );

DECLARE MAP TMP_SUM6(long)[][zip: int] :=
  AggSum([zip],
    (DELTA CENSUS)(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic)
  );

DECLARE MAP TMP_SUM7(long)[][locn: int, zip: int] :=
    (TMP_SUM6(long)[][zip]<Local> * V_rgn_cd_L1(long)[][locn, zip]<Local>);

DECLARE MAP TMP_SUM7_PRIME(long)[][locn: int] :=
  AggSum([locn],
    TMP_SUM7(long)[][locn, zip]<Local>
  );

DECLARE MAP TMP_SUM8(long)[][ksn: int] :=
  AggSum([ksn],
    (DELTA ITEM)(ksn, subcategory, category, categoryCluster, prize)
  );

DECLARE MAP TMP_SUM9(long)[][locn: int, dateid: int, ksn: int] :=
    (TMP_SUM8(long)[][ksn]<Local> * V_inventoryunits_I1(long)[][locn, dateid, ksn]<Local>);

DECLARE MAP TMP_SUM9_PRIME(long)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    TMP_SUM9(long)[][locn, dateid, ksn]<Local>
  );

DECLARE MAP TMP_SUM10(long)[][locn: int, dateid: int] :=
    (TMP_SUM9_PRIME(long)[][locn, dateid]<Local> * V_rain_W1(long)[][locn, dateid]<Local>);

DECLARE MAP TMP_SUM10_PRIME(long)[][locn: int] :=
  AggSum([locn],
    TMP_SUM10(long)[][locn, dateid]<Local>
  );

DECLARE MAP TMP_SUM11(long)[][locn: int, dateid: int] :=
  AggSum([locn, dateid],
    (DELTA WEATHER)(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder)
  );

DECLARE MAP TMP_SUM12(long)[][locn: int, dateid: int] :=
    (TMP_SUM11(long)[][locn, dateid]<Local> * V_ksn_II2(long)[][locn, dateid]<Local>);

DECLARE MAP TMP_SUM12_PRIME(long)[][locn: int] :=
  AggSum([locn],
    TMP_SUM12(long)[][locn, dateid]<Local>
  );
  
DECLARE MAP V_INVENTORY(long)[][locn: int, dateid: int, ksn: int, inventoryunits: int] := INVENTORY(locn, dateid, ksn, inventoryunits);
  
DECLARE MAP V_ITEM(long)[][ksn: int, subcategory: int, category: int, categoryCluster: int, prize: int] := ITEM(ksn, subcategory, category, categoryCluster, prize);

DECLARE MAP V_LOCATION(long)[][locn: int, zip: int, rgn_cd: int, clim_zn_nbr: int, tot_area_sq_ft: int, sell_area_sq_ft: int, avghhi: int, supertargetdistance: int, supertargetdrivetime: int, targetdistance: int, targetdrivetime: int, walmartdistance: int, walmartdrivetime: int, walmartsupercenterdistance: int, walmartsupercenterdrivetime: int] := LOCATION(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);

DECLARE MAP V_CENSUS(long)[][zip: int, population: int, white: int, asian: int, pacific: int, blackafrican: int, medianage: int, occupiedhouseunits: int, houseunits: int, families: int, households: int, husbwife: int, males: int, females: int, householdschildren: int, hispanic: int] := 
  CENSUS(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);

DECLARE MAP V_WEATHER(long)[][locn: int, dateid: int, rain: int, snow: int, maxtemp: int, mintemp: int, meanwind: int, thunder: int] := WEATHER(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);


-------------------- QUERIES --------------------
DECLARE QUERY V_locn_IIWLC1 := V_locn_IIWLC1(long)[][locn]<Local>;

DECLARE QUERY V_dateid_IIW1 := V_dateid_IIW1(long)[][locn, dateid]<Local>;

DECLARE QUERY V_ksn_II1 := V_ksn_II1(long)[][locn, dateid, ksn]<Local>;

DECLARE QUERY V_zip_LC1 := V_zip_LC1(long)[][locn, zip]<Local>;

DECLARE QUERY V_INVENTORY := V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits]<Local>;

DECLARE QUERY V_ITEM := V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize]<Local>;

DECLARE QUERY V_LOCATION := V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime]<Local>;

DECLARE QUERY V_CENSUS := V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic]<Local>;

DECLARE QUERY V_WEATHER := V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder]<Local>;


------------------- TRIGGERS --------------------
ON BATCH UPDATE OF INVENTORY {
  V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] += (DELTA INVENTORY)(locn, dateid, ksn, inventoryunits);

  TMP_SUM1(long)[][locn, dateid, ksn]<Local>  :=  AggSum([locn, dateid, ksn],
    (DELTA INVENTORY)(locn, dateid, ksn, inventoryunits) 
  );
  TMP_SUM2(long)[][locn, dateid, ksn] :=
    (TMP_SUM1(long)[][locn, dateid, ksn]<Local> * V_subcategory_I1(long)[][ksn]<Local>);

  TMP_SUM2_PRIME(long)[][locn, dateid] :=
    AggSum([locn, dateid],
      TMP_SUM2(long)[][locn, dateid, ksn]<Local>
    );

  TMP_SUM3(long)[][locn, dateid] :=
    (TMP_SUM2_PRIME(long)[][locn, dateid]<Local> * V_rain_W1(long)[][locn, dateid]<Local>);

  TMP_SUM3_PRIME(long)[][locn] :=
    AggSum([locn],
      TMP_SUM3(long)[][locn, dateid]<Local>
    );

  V_locn_IIWLC1(long)[][locn]<Local>  +=  
    (TMP_SUM3_PRIME(long)[][locn]<Local> * V_zip_LC2(long)[][locn]<Local>);

  V_dateid_IIW2(long)[][locn]<Local>  +=  TMP_SUM3_PRIME(long)[][locn]<Local>;
  V_dateid_IIW1(long)[][locn, dateid]<Local>  +=  TMP_SUM3(long)[][locn, dateid]<Local>;
  V_ksn_II2(long)[][locn, dateid]<Local>  +=  TMP_SUM2_PRIME(long)[][locn, dateid]<Local>;
  V_ksn_II1(long)[][locn, dateid, ksn]<Local>  +=  TMP_SUM2(long)[][locn, dateid, ksn]<Local>;
  V_inventoryunits_I1(long)[][locn, dateid, ksn]<Local>  +=  TMP_SUM1(long)[][locn, dateid, ksn]<Local>;
}

ON BATCH UPDATE OF LOCATION {
  V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] += (DELTA LOCATION)(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);

  TMP_SUM4(long)[][locn, zip]<Local>  :=  AggSum([locn, zip],
    (DELTA LOCATION)(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)
  );
  TMP_SUM5(long)[][locn, zip] :=
    (TMP_SUM4(long)[][locn, zip]<Local> * V_population_C1(long)[][zip]<Local>);
    
  TMP_SUM5_PRIME(long)[][locn] :=
    AggSum([locn],
      TMP_SUM5(long)[][locn, zip]<Local>
    );
  
  V_locn_IIWLC1(long)[][locn]<Local>  +=  
    (TMP_SUM5_PRIME(long)[][locn]<Local> * V_dateid_IIW2(long)[][locn]<Local>);

  V_zip_LC2(long)[][locn]<Local>  +=  TMP_SUM5_PRIME(long)[][locn]<Local>;
  V_zip_LC1(long)[][locn, zip]<Local>  +=  TMP_SUM5(long)[][locn, zip]<Local>;
  V_rgn_cd_L1(long)[][locn, zip]<Local>  +=  TMP_SUM4(long)[][locn, zip]<Local>;
}

ON BATCH UPDATE OF CENSUS {
  V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] += (DELTA CENSUS)(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);

  TMP_SUM6(long)[][zip]<Local>  :=  AggSum([zip],
    (DELTA CENSUS)(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic)
  );
  TMP_SUM7(long)[][locn, zip] :=
    (TMP_SUM6(long)[][zip]<Local> * V_rgn_cd_L1(long)[][locn, zip]<Local>);
    
  TMP_SUM7_PRIME(long)[][locn] :=
    AggSum([locn],
      TMP_SUM7(long)[][locn, zip]<Local>
    );

  V_locn_IIWLC1(long)[][locn]<Local>  +=  
    (TMP_SUM7_PRIME(long)[][locn]<Local> * V_dateid_IIW2(long)[][locn]<Local>);

  V_zip_LC2(long)[][locn]<Local>  +=  TMP_SUM7_PRIME(long)[][locn]<Local>;
  V_zip_LC1(long)[][locn, zip]<Local>  +=  TMP_SUM7(long)[][locn, zip]<Local>;
  V_population_C1(long)[][zip]<Local>  +=  TMP_SUM6(long)[][zip]<Local>;
}

ON BATCH UPDATE OF ITEM {
  V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] += (DELTA ITEM)(ksn, subcategory, category, categoryCluster, prize);

  TMP_SUM8(long)[][ksn]<Local>  :=  AggSum([ksn],
    (DELTA ITEM)(ksn, subcategory, category, categoryCluster, prize)
  );
  TMP_SUM9(long)[][locn, dateid, ksn] :=
    (TMP_SUM8(long)[][ksn]<Local> * V_inventoryunits_I1(long)[][locn, dateid, ksn]<Local>);

  TMP_SUM9_PRIME(long)[][locn, dateid] :=
    AggSum([locn, dateid],
      TMP_SUM9(long)[][locn, dateid, ksn]<Local>
    );

  TMP_SUM10(long)[][locn, dateid] :=
    (TMP_SUM9_PRIME(long)[][locn, dateid]<Local> * V_rain_W1(long)[][locn, dateid]<Local>);
    
  TMP_SUM10_PRIME(long)[][locn] :=
    AggSum([locn],
      TMP_SUM10(long)[][locn, dateid]<Local>
    );

  V_locn_IIWLC1(long)[][locn]<Local>  +=  
    (TMP_SUM10_PRIME(long)[][locn]<Local> * V_zip_LC2(long)[][locn]<Local>);

  V_dateid_IIW2(long)[][locn]<Local>  +=  TMP_SUM10_PRIME(long)[][locn]<Local>;
  V_dateid_IIW1(long)[][locn, dateid]<Local>  +=  TMP_SUM10(long)[][locn, dateid]<Local>;
  V_ksn_II2(long)[][locn, dateid]<Local>  +=  TMP_SUM9_PRIME(long)[][locn, dateid]<Local>;
  V_ksn_II1(long)[][locn, dateid, ksn]<Local>  +=  TMP_SUM9(long)[][locn, dateid, ksn]<Local>;
  V_subcategory_I1(long)[][ksn]<Local>  +=  TMP_SUM8(long)[][ksn]<Local>;
}

ON BATCH UPDATE OF WEATHER {
  V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] += (DELTA WEATHER)(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);

  TMP_SUM11(long)[][locn, dateid]<Local>  :=  AggSum([locn, dateid],
    (DELTA WEATHER)(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder)
  );
  TMP_SUM12(long)[][locn, dateid] :=
    (TMP_SUM11(long)[][locn, dateid]<Local> * V_ksn_II2(long)[][locn, dateid]<Local>);

  TMP_SUM12_PRIME(long)[][locn] :=
    AggSum([locn],
      TMP_SUM12(long)[][locn, dateid]<Local>
    );
  
  V_locn_IIWLC1(long)[][locn]<Local>  +=  
    (TMP_SUM12_PRIME(long)[][locn]<Local> * V_zip_LC2(long)[][locn]<Local>);

  V_dateid_IIW2(long)[][locn]<Local>  +=  TMP_SUM12_PRIME(long)[][locn]<Local>;
  V_dateid_IIW1(long)[][locn, dateid]<Local>  +=  TMP_SUM12(long)[][locn, dateid]<Local>;
  V_rain_W1(long)[][locn, dateid]<Local>  +=  TMP_SUM11(long)[][locn, dateid]<Local>;
}

ON SYSTEM READY {
  
}