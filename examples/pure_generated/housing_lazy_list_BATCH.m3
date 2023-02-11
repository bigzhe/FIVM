---------------- TYPE DEFINITIONS ---------------
CREATE  TYPE RingRelation
FROM FILE 'ring/ring_relational_opt.hpp'
WITH PARAMETER SCHEMA (dynamic_concat);

-------------------- SOURCES --------------------
CREATE STREAM HOUSE (postcode double, livingarea double, price double, nbbedrooms double, nbbathrooms double, kitchensize double, house double, flat double, unknown double, garden double, parking double)
  FROM FILE './datasets/housing/House.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM SHOP (postcode double, openinghoursshop double, pricerangeshop double, sainsburys double, tesco double, ms double)
  FROM FILE './datasets/housing/Shop.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM INSTITUTION (postcode double, typeeducation double, sizeinstitution double)
  FROM FILE './datasets/housing/Institution.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM RESTAURANT (postcode double, openinghoursrest double, pricerangerest double)
  FROM FILE './datasets/housing/Restaurant.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM DEMOGRAPHICS (postcode double, averagesalary double, crimesperyear double, unemployment double, nbhospitals double)
  FROM FILE './datasets/housing/Demographics.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM TRANSPORT (postcode double, nbbuslines double, nbtrainstations double, distancecitycentre double)
  FROM FILE './datasets/housing/Transport.tbl' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------
DECLARE MAP V_postcode_HSIRDT1(RingRelation<[0, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double]>)[][] :=
  AggSum([],
    (((((((HOUSE(postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking) * [lift<1>: RingRelation<[1, double, double, double, double, double, double, double, double, double, double]>](livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking)) * AggSum([postcode],
      (SHOP(postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms) * [lift<11>: RingRelation<[11, double, double, double, double, double]>](openinghoursshop, pricerangeshop, sainsburys, tesco, ms))
    )) * AggSum([postcode],
      (INSTITUTION(postcode, typeeducation, sizeinstitution) * [lift<16>: RingRelation<[16, double, double]>](typeeducation, sizeinstitution))
    )) * AggSum([postcode],
      (RESTAURANT(postcode, openinghoursrest, pricerangerest) * [lift<18>: RingRelation<[18, double, double]>](openinghoursrest, pricerangerest))
    )) * AggSum([postcode],
      (DEMOGRAPHICS(postcode, averagesalary, crimesperyear, unemployment, nbhospitals) * [lift<20>: RingRelation<[20, double, double, double, double]>](averagesalary, crimesperyear, unemployment, nbhospitals))
    )) * AggSum([postcode],
      (TRANSPORT(postcode, nbbuslines, nbtrainstations, distancecitycentre) * [lift<24>: RingRelation<[24, double, double, double]>](nbbuslines, nbtrainstations, distancecitycentre))
    )) * [lift<0>: RingRelation<[0, double]>](postcode))
  );

DECLARE MAP V_HOUSE(long)[][postcode: double, livingarea: double, price: double, nbbedrooms: double, nbbathrooms: double, kitchensize: double, house: double, flat: double, unknown: double, garden: double, parking: double] :=
  HOUSE(postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking);

DECLARE MAP V_SHOP(long)[][postcode: double, openinghoursshop: double, pricerangeshop: double, sainsburys: double, tesco: double, ms: double] :=
  SHOP(postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms);

DECLARE MAP V_INSTITUTION(long)[][postcode: double, typeeducation: double, sizeinstitution: double] :=
  INSTITUTION(postcode, typeeducation, sizeinstitution);

DECLARE MAP V_RESTAURANT(long)[][postcode: double, openinghoursrest: double, pricerangerest: double] :=
  RESTAURANT(postcode, openinghoursrest, pricerangerest);

DECLARE MAP V_DEMOGRAPHICS(long)[][postcode: double, averagesalary: double, crimesperyear: double, unemployment: double, nbhospitals: double] :=
  DEMOGRAPHICS(postcode, averagesalary, crimesperyear, unemployment, nbhospitals);

DECLARE MAP V_TRANSPORT(long)[][postcode: double, nbbuslines: double, nbtrainstations: double, distancecitycentre: double] :=
  TRANSPORT(postcode, nbbuslines, nbtrainstations, distancecitycentre);




-------------------- QUERIES --------------------
DECLARE QUERY V_postcode_HSIRDT1 := V_postcode_HSIRDT1(RingRelation<[0, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double]>)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF HOUSE {
  V_HOUSE(long)[][postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking]  +=  (DELTA HOUSE)(postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking);
}

ON BATCH UPDATE OF SHOP {
  V_SHOP(long)[][postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms]  +=  (DELTA SHOP)(postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms);
}

ON BATCH UPDATE OF INSTITUTION {
  V_INSTITUTION(long)[][postcode, typeeducation, sizeinstitution]  +=  (DELTA INSTITUTION)(postcode, typeeducation, sizeinstitution);
}

ON BATCH UPDATE OF RESTAURANT {
  V_RESTAURANT(long)[][postcode, openinghoursrest, pricerangerest]  +=  (DELTA RESTAURANT)(postcode, openinghoursrest, pricerangerest);
}

ON BATCH UPDATE OF DEMOGRAPHICS {
  V_DEMOGRAPHICS(long)[][postcode, averagesalary, crimesperyear, unemployment, nbhospitals]  +=  (DELTA DEMOGRAPHICS)(postcode, averagesalary, crimesperyear, unemployment, nbhospitals);
}

ON BATCH UPDATE OF TRANSPORT {
  V_TRANSPORT(long)[][postcode, nbbuslines, nbtrainstations, distancecitycentre]  +=  (DELTA TRANSPORT)(postcode, nbbuslines, nbtrainstations, distancecitycentre);
}

ON SYSTEM READY {
  V_postcode_HSIRDT1(RingRelation<[0, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double]>)[][]<Local>  :=  AggSum([],
    (((((((V_HOUSE(long)[][postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking] * [lift<1>: RingRelation<[1, double, double, double, double, double, double, double, double, double, double]>](livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking)) * AggSum([postcode],
      (V_SHOP(long)[][postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms] * [lift<11>: RingRelation<[11, double, double, double, double, double]>](openinghoursshop, pricerangeshop, sainsburys, tesco, ms))
    )) * AggSum([postcode],
      (V_INSTITUTION(long)[][postcode, typeeducation, sizeinstitution] * [lift<16>: RingRelation<[16, double, double]>](typeeducation, sizeinstitution))
    )) * AggSum([postcode],
      (V_RESTAURANT(long)[][postcode, openinghoursrest, pricerangerest] * [lift<18>: RingRelation<[18, double, double]>](openinghoursrest, pricerangerest))
    )) * AggSum([postcode],
      (V_DEMOGRAPHICS(long)[][postcode, averagesalary, crimesperyear, unemployment, nbhospitals] * [lift<20>: RingRelation<[20, double, double, double, double]>](averagesalary, crimesperyear, unemployment, nbhospitals))
    )) * AggSum([postcode],
      (V_TRANSPORT(long)[][postcode, nbbuslines, nbtrainstations, distancecitycentre] * [lift<24>: RingRelation<[24, double, double, double]>](nbbuslines, nbtrainstations, distancecitycentre))
    )) * [lift<0>: RingRelation<[0, double]>](postcode))
  );
}