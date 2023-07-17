-------------------- SOURCES --------------------
CREATE STREAM R1 (A1 int, A2 int)
  FROM FILE './datasets/snap/R1.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R2 (A2 int, A3 int)
  FROM FILE './datasets/snap/R2.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R3 (A3 int, A4 int)
  FROM FILE './datasets/snap/R3.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R4 (A4 int, A5 int)
  FROM FILE './datasets/snap/R4.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R5 (A5 int, A6 int)
  FROM FILE './datasets/snap/R5.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R6 (A6 int, A7 int)
  FROM FILE './datasets/snap/R6.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R7 (A7 int, A8 int)
  FROM FILE './datasets/snap/R7.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R8 (A8 int, A9 int)
  FROM FILE './datasets/snap/R8.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R9 (A9 int, A10 int)
  FROM FILE './datasets/snap/R9.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R10 (A10 int, A11 int)
  FROM FILE './datasets/snap/R10.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R11 (A11 int, A12 int)
  FROM FILE './datasets/snap/R11.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R12 (A12 int, A13 int)
  FROM FILE './datasets/snap/R12.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R13 (A13 int, A14 int)
  FROM FILE './datasets/snap/R13.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R14 (A14 int, A15 int)
  FROM FILE './datasets/snap/R14.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R15 (A15 int, A16 int)
  FROM FILE './datasets/snap/R15.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R16 (A16 int, A17 int)
  FROM FILE './datasets/snap/R16.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R17 (A17 int, A18 int)
  FROM FILE './datasets/snap/R17.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R18 (A18 int, A19 int)
  FROM FILE './datasets/snap/R18.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R19 (A19 int, A20 int)
  FROM FILE './datasets/snap/R19.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R20 (A20 int, A21 int)
  FROM FILE './datasets/snap/R20.csv' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------

DECLARE MAP V_Q(long)[][] :=
  AggSum([],
    R1(A1, A2) * R2(A2, A3) * R3(A3, A4) * R4(A4, A5) * R5(A5, A6) * R6(A6, A7) * R7(A7, A8) * R8(A8, A9) * R9(A9, A10) * R10(A10, A11) * R11(A11, A12) * R12(A12, A13) * R13(A13, A14) * R14(A14, A15) * R15(A15, A16) * R16(A16, A17) * R17(A17, A18) * R18(A18, A19) * R19(A19, A20) * R20(A20, A21) * A1 * A21
  );


DECLARE MAP V_R1(long)[][A1: int, A2: int] := R1(A1, A2);
DECLARE MAP V_R2(long)[][A2: int, A3: int] := R2(A2, A3);
DECLARE MAP V_R3(long)[][A3: int, A4: int] := R3(A3, A4);
DECLARE MAP V_R4(long)[][A4: int, A5: int] := R4(A4, A5);
DECLARE MAP V_R5(long)[][A5: int, A6: int] := R5(A5, A6);
DECLARE MAP V_R6(long)[][A6: int, A7: int] := R6(A6, A7);
DECLARE MAP V_R7(long)[][A7: int, A8: int] := R7(A7, A8);
DECLARE MAP V_R8(long)[][A8: int, A9: int] := R8(A8, A9);
DECLARE MAP V_R9(long)[][A9: int, A10: int] := R9(A9, A10);
DECLARE MAP V_R10(long)[][A10: int, A11: int] := R10(A10, A11);
DECLARE MAP V_R11(long)[][A11: int, A12: int] := R11(A11, A12);
DECLARE MAP V_R12(long)[][A12: int, A13: int] := R12(A12, A13);
DECLARE MAP V_R13(long)[][A13: int, A14: int] := R13(A13, A14);
DECLARE MAP V_R14(long)[][A14: int, A15: int] := R14(A14, A15);
DECLARE MAP V_R15(long)[][A15: int, A16: int] := R15(A15, A16);
DECLARE MAP V_R16(long)[][A16: int, A17: int] := R16(A16, A17);
DECLARE MAP V_R17(long)[][A17: int, A18: int] := R17(A17, A18);
DECLARE MAP V_R18(long)[][A18: int, A19: int] := R18(A18, A19);
DECLARE MAP V_R19(long)[][A19: int, A20: int] := R19(A19, A20);
DECLARE MAP V_R20(long)[][A20: int, A21: int] := R20(A20, A21);

DECLARE MAP TMP_R1(long)[][A1: int, A2: int] := (DELTA R1)(A1, A2);
DECLARE MAP TMP_R2(long)[][A2: int, A3: int] := (DELTA R2)(A2, A3);
DECLARE MAP TMP_R3(long)[][A3: int, A4: int] := (DELTA R3)(A3, A4);
DECLARE MAP TMP_R4(long)[][A4: int, A5: int] := (DELTA R4)(A4, A5);
DECLARE MAP TMP_R5(long)[][A5: int, A6: int] := (DELTA R5)(A5, A6);
DECLARE MAP TMP_R6(long)[][A6: int, A7: int] := (DELTA R6)(A6, A7);
DECLARE MAP TMP_R7(long)[][A7: int, A8: int] := (DELTA R7)(A7, A8);
DECLARE MAP TMP_R8(long)[][A8: int, A9: int] := (DELTA R8)(A8, A9);
DECLARE MAP TMP_R9(long)[][A9: int, A10: int] := (DELTA R9)(A9, A10);
DECLARE MAP TMP_R10(long)[][A10: int, A11: int] := (DELTA R10)(A10, A11);
DECLARE MAP TMP_R11(long)[][A11: int, A12: int] := (DELTA R11)(A11, A12);
DECLARE MAP TMP_R12(long)[][A12: int, A13: int] := (DELTA R12)(A12, A13);
DECLARE MAP TMP_R13(long)[][A13: int, A14: int] := (DELTA R13)(A13, A14);
DECLARE MAP TMP_R14(long)[][A14: int, A15: int] := (DELTA R14)(A14, A15);
DECLARE MAP TMP_R15(long)[][A15: int, A16: int] := (DELTA R15)(A15, A16);
DECLARE MAP TMP_R16(long)[][A16: int, A17: int] := (DELTA R16)(A16, A17);
DECLARE MAP TMP_R17(long)[][A17: int, A18: int] := (DELTA R17)(A17, A18);
DECLARE MAP TMP_R18(long)[][A18: int, A19: int] := (DELTA R18)(A18, A19);
DECLARE MAP TMP_R19(long)[][A19: int, A20: int] := (DELTA R19)(A19, A20);
DECLARE MAP TMP_R20(long)[][A20: int, A21: int] := (DELTA R20)(A20, A21);

-------------------- QUERIES --------------------
DECLARE QUERY V_Q := V_Q(long)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF R1 {
  TMP_R1(long)[][A1, A2]<Local> := (DELTA R1)(A1, A2);
  V_R1(long)[][A1, A2]<Local> += TMP_R1(long)[][A1, A2]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    TMP_R1(long)[][A1, A2] * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R2 {
  TMP_R2(long)[][A2, A3]<Local> := (DELTA R2)(A2, A3);
  V_R2(long)[][A2, A3]<Local> += TMP_R2(long)[][A2, A3]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * TMP_R2(long)[][A2, A3] * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R3 {
  TMP_R3(long)[][A3, A4]<Local> := (DELTA R3)(A3, A4);
  V_R3(long)[][A3, A4]<Local> += TMP_R3(long)[][A3, A4]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * TMP_R3(long)[][A3, A4] * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R4 {
  TMP_R4(long)[][A4, A5]<Local> := (DELTA R4)(A4, A5);
  V_R4(long)[][A4, A5]<Local> += TMP_R4(long)[][A4, A5]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * TMP_R4(long)[][A4, A5] * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R5 {
  TMP_R5(long)[][A5, A6]<Local> := (DELTA R5)(A5, A6);
  V_R5(long)[][A5, A6]<Local> += TMP_R5(long)[][A5, A6]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * TMP_R5(long)[][A5, A6] * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R6 {
  TMP_R6(long)[][A6, A7]<Local> := (DELTA R6)(A6, A7);
  V_R6(long)[][A6, A7]<Local> += TMP_R6(long)[][A6, A7]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * TMP_R6(long)[][A6, A7] * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R7 {
  TMP_R7(long)[][A7, A8]<Local> := (DELTA R7)(A7, A8);
  V_R7(long)[][A7, A8]<Local> += TMP_R7(long)[][A7, A8]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * TMP_R7(long)[][A7, A8] * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R8 {
  TMP_R8(long)[][A8, A9]<Local> := (DELTA R8)(A8, A9);
  V_R8(long)[][A8, A9]<Local> += TMP_R8(long)[][A8, A9]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * TMP_R8(long)[][A8, A9] * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R9 {
  TMP_R9(long)[][A9, A10]<Local> := (DELTA R9)(A9, A10);
  V_R9(long)[][A9, A10]<Local> += TMP_R9(long)[][A9, A10]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * TMP_R9(long)[][A9, A10] * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R10 {
  TMP_R10(long)[][A10, A11]<Local> := (DELTA R10)(A10, A11);
  V_R10(long)[][A10, A11]<Local> += TMP_R10(long)[][A10, A11]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * TMP_R10(long)[][A10, A11] * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R11 {
  TMP_R11(long)[][A11, A12]<Local> := (DELTA R11)(A11, A12);
  V_R11(long)[][A11, A12]<Local> += TMP_R11(long)[][A11, A12]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * TMP_R11(long)[][A11, A12] * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R12 {
  TMP_R12(long)[][A12, A13]<Local> := (DELTA R12)(A12, A13);
  V_R12(long)[][A12, A13]<Local> += TMP_R12(long)[][A12, A13]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * TMP_R12(long)[][A12, A13] * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R13 {
  TMP_R13(long)[][A13, A14]<Local> := (DELTA R13)(A13, A14);
  V_R13(long)[][A13, A14]<Local> += TMP_R13(long)[][A13, A14]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * TMP_R13(long)[][A13, A14] * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R14 {
  TMP_R14(long)[][A14, A15]<Local> := (DELTA R14)(A14, A15);
  V_R14(long)[][A14, A15]<Local> += TMP_R14(long)[][A14, A15]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * TMP_R14(long)[][A14, A15] * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R15 {
  TMP_R15(long)[][A15, A16]<Local> := (DELTA R15)(A15, A16);
  V_R15(long)[][A15, A16]<Local> += TMP_R15(long)[][A15, A16]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * TMP_R15(long)[][A15, A16] * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R16 {
  TMP_R16(long)[][A16, A17]<Local> := (DELTA R16)(A16, A17);
  V_R16(long)[][A16, A17]<Local> += TMP_R16(long)[][A16, A17]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * TMP_R16(long)[][A16, A17] * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R17 {
  TMP_R17(long)[][A17, A18]<Local> := (DELTA R17)(A17, A18);
  V_R17(long)[][A17, A18]<Local> += TMP_R17(long)[][A17, A18]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * TMP_R17(long)[][A17, A18] * V_R18(A18, A19) * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R18 {
  TMP_R18(long)[][A18, A19]<Local> := (DELTA R18)(A18, A19);
  V_R18(long)[][A18, A19]<Local> += TMP_R18(long)[][A18, A19]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * TMP_R18(long)[][A18, A19] * V_R19(A19, A20) * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R19 {
  TMP_R19(long)[][A19, A20]<Local> := (DELTA R19)(A19, A20);
  V_R19(long)[][A19, A20]<Local> += TMP_R19(long)[][A19, A20]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * TMP_R19(long)[][A19, A20] * V_R20(A20, A21) * A1 * A21
  );
}
ON BATCH UPDATE OF R20 {
  TMP_R20(long)[][A20, A21]<Local> := (DELTA R20)(A20, A21);
  V_R20(long)[][A20, A21]<Local> += TMP_R20(long)[][A20, A21]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * V_R11(A11, A12) * V_R12(A12, A13) * V_R13(A13, A14) * V_R14(A14, A15) * V_R15(A15, A16) * V_R16(A16, A17) * V_R17(A17, A18) * V_R18(A18, A19) * V_R19(A19, A20) * TMP_R20(long)[][A20, A21] * A1 * A21
  );
}


ON SYSTEM READY {
  
}