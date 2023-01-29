IMPORT DTREE FROM FILE 'housing.txt';


CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE TABLE HOUSE(postcode double, livingarea double, price double, nbbedrooms double, nbbathrooms double, kitchensize double, house double, flat double, unknown double, garden double, parking double)
FROM FILE './datasets/housing/House.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE TABLE SHOP(postcode double, openinghoursshop double, pricerangeshop double, sainsburys double, tesco double, ms double)
FROM FILE './datasets/housing/Shop.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE TABLE INSTITUTION(postcode double, typeeducation double, sizeinstitution double)
FROM FILE './datasets/housing/Institution.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE TABLE RESTAURANT(postcode double, openinghoursrest double, pricerangerest double)
FROM FILE './datasets/housing/Restaurant.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE TABLE DEMOGRAPHICS(postcode double, averagesalary double, crimesperyear double, unemployment double, nbhospitals double)
FROM FILE './datasets/housing/Demographics.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE TABLE TRANSPORT(postcode double, nbbuslines double, nbtrainstations double, distancecitycentre double)
FROM FILE './datasets/housing/Transport.tbl' LINE DELIMITED CSV(delimiter := '|');

SELECT SUM(
    [lift<0>: RingFactorizedRelation<[0,double]>](postcode) *
    [lift<1>: RingFactorizedRelation<[1,double,double,double,double,double,double,double,double,double,double]>](livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking) *
    [lift<11>: RingFactorizedRelation<[11,double,double,double,double,double]>](openinghoursshop, pricerangeshop, sainsburys, tesco, ms) *
    [lift<16>: RingFactorizedRelation<[16,double,double]>](typeeducation, sizeinstitution) *
    [lift<18>: RingFactorizedRelation<[18,double,double]>](openinghoursrest, pricerangerest) *    
    [lift<20>: RingFactorizedRelation<[20,double,double,double,double]>](averagesalary, crimesperyear, unemployment, nbhospitals) *
    [lift<24>: RingFactorizedRelation<[24,double,double,double]>](nbbuslines, nbtrainstations, distancecitycentre)
)
FROM HOUSE NATURAL JOIN SHOP NATURAL JOIN INSTITUTION NATURAL JOIN RESTAURANT NATURAL JOIN DEMOGRAPHICS NATURAL JOIN TRANSPORT;