; bool isSqrt(int n) {
;     for(int i = 1; n > 0; i += 2) n -= i;
;     return 0 == n;
; }

; simulate the function above

; the finite set of states
#Q = {0,binary,reject,mh_2nd_add1,add1,init,loop_start,loop_start1,loop_body,loop_body0,loop_body1,loop_body2,loop_body3,loop_body4,loop_body5,loop_body6,loop_body7,loop_body8,loop_body9,loop_body10,loop_body11,loop_add,loop_add1,loop_add2,loop_check,loop_check1,loop_check2,false_clean,false_clean1,false,false1,false2,false3,false4,false_halt,true_clean,true_clean1,true,true1,true2,true3,true_halt}

; the finite set of input symbols
#S = {1}

; the complete set of tape symbols
#G = {0,1,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {false_halt,true_halt}

; the number of tapes: tape3 used as tape2's track
#N = 3

; the transition functions

; State 0: start state
0 1__ 1__ *** binary
0 ___ ___ *** reject ; empty input

; State binary: count the input to binary number in 2nd tape(reverse)
binary 1__ 11_ r** binary
binary 1*_ 1*_ *** mh_2nd_add1
binary _*_ _*_ *** loop_start


; State mh_2nd_add1: move 2nd tape to head
mh_2nd_add1 *0_ *0_ *ll mh_2nd_add1
mh_2nd_add1 *1_ *1_ *ll mh_2nd_add1
mh_2nd_add1 *__ *__ *rr add1


; State add1: plus one
add1 *0_ *1_ r** binary
add1 *1_ *0_ *rr add1 
add1 *__ *1_ r** binary

; State loop_start: clean tape1 then will put variable i in tape1
loop_start _*_ _*_ l** loop_start1
loop_start1 0*_ _*_ l** loop_start1
loop_start1 1*_ _*_ l** loop_start1
loop_start1 _*_ _*_ r** init

; State init: init i = 1 in tape1
init _*_ 1*_ *** loop_body

; State loop_body: move to head for tape1,tape2
loop_body **_ **_ lll loop_body
loop_body *__ *__ l** loop_body
loop_body _*_ _*_ *ll loop_body
loop_body ___ ___ rrr loop_body0


; State loop_body0: align the tape1 & tape2
loop_body0 **_ **_ rrr loop_body0
loop_body0 _*_ 0*_ rrr loop_body0
loop_body0 *__ *0_ rrr loop_body0
loop_body0 ___ 00_ *** loop_body1

; State loop_body1: flip (execute sub in complement code (a positive number - a positive number will not overflow))
loop_body1 0*_ 1*_ lll loop_body1
loop_body1 1*_ 0*_ lll loop_body1
loop_body1 ___ ___ rrr loop_body2

; State: loop_body2: add 1 to variable i in tape1
loop_body2 0*_ 1*_ *** loop_body3
loop_body2 1*_ 0*_ r** loop_body2
loop_body2 _*_ 1*_ *** loop_body3

; State: loop_body3: tape1 move to head
loop_body3 0*_ 0*_ l** loop_body3
loop_body3 1*_ 1*_ l** loop_body3
loop_body3 _*_ _*_ r** loop_body4

; State: loop_body4: tape1 "add" tape2
loop_body4 00_ 00_ rrr loop_body4
loop_body4 10_ 11_ rrr loop_body4
loop_body4 01_ 01_ rrr loop_body4
loop_body4 11_ 10_ rrr loop_body5
loop_body4 ___ ___ lll loop_body8

; State: loop_body5: tag in tape3
loop_body5 **_ **1 *** loop_body6
loop_body5 ___ ___ lll loop_body8
loop_body5 *__ *__ lll loop_body8

; State: loop_body6: carry in tape2
loop_body6 *01 *11 *** loop_body7
loop_body6 *0_ *1_ *** loop_body7
loop_body6 *11 *01 *rr loop_body6
loop_body6 *1_ *0_ *rr loop_body6
loop_body6 *_1 *_1 *** loop_body7
loop_body6 *__ *__ *** loop_body7 ; ignore the _ carry (complement add)

; State: loop_body7: move to the tag and clean tag
loop_body7 *__ *__ *ll loop_body7
loop_body7 *0_ *0_ *ll loop_body7
loop_body7 *1_ *1_ *ll loop_body7
loop_body7 *01 *0_ *** loop_body4
loop_body7 *11 *1_ *** loop_body4

; State: loop_body8: move tape1 to head
loop_body8 *__ *__ l** loop_body8
loop_body8 **_ **_ l** loop_body8
loop_body8 _*_ _*_ r** loop_body9

; State: loop_body9: flip tape1
loop_body9 0*_ 1*_ r** loop_body9
loop_body9 1*_ 0*_ r** loop_body9
loop_body9 _*_ _*_ l** loop_body10

; State: loop_body10: move tape1 to head
loop_body10 **_ **_ l** loop_body10
loop_body10 _*_ _*_ r** loop_body11

; State: loop_body11: add 1 to tape1
loop_body11 0*_ 1*_ *** loop_add
loop_body11 1*_ 0*_ r** loop_body11
loop_body11 _*_ 1*_ *** loop_add

; State: loop_add: i += 2, move tape1 to second bit (+ *1)
loop_add **_ **_ l** loop_add
loop_add _*_ _*_ r** loop_add1

; State: loop_add1: move to right
loop_add1 **_ **_ r** loop_add2

; State: loop_add2: add 2
loop_add2 _*_ 1*_ *** loop_check
loop_add2 0*_ 1*_ *** loop_check
loop_add2 1*_ 0*_ r** loop_add2

; State: loop_check: check n > 0 or not, move tape2 to tail first
loop_check **_ **_ *rr loop_check
loop_check *__ *__ *ll loop_check1

; State: loop_check1: check < 0
loop_check1 *1_ *1_ *** false_clean
loop_check1 *0_ *0_ *** loop_check2

; State: loop_check2: check == 0
loop_check2 *0_ *0_ *ll loop_check2
loop_check2 *1_ *1_ *** loop_body
loop_check2 *__ *__ *** true_clean


; State: false_clean : tape1 & tape2 move to the tail
false_clean **_ **_ rrr false_clean
false_clean *__ *__ r** false_clean
false_clean _*_ _*_ *rr false_clean
false_clean ___ ___ lll false_clean1

; State: false_clean1 : clean all
false_clean1 **_ ___ lll false_clean1
false_clean1 *__ ___ l** false_clean1
false_clean1 _*_ ___ *ll false_clean1
false_clean1 ___ ___ *** false

; State: write "false"
false ___ f__ r** false1
false1 ___ a__ r** false2
false2 ___ l__ r** false3
false3 ___ s__ r** false4
false4 ___ e__ r** false_halt

; State: true_clean : tape1 & tape2 move to the tail
true_clean **_ **_ rrr true_clean
true_clean *__ *__ r** true_clean
true_clean _*_ _*_ *rr true_clean
true_clean ___ ___ lll true_clean1

; State: true_clean1 : clean all
true_clean1 **_ ___ lll true_clean1
true_clean1 *__ ___ l** true_clean1
true_clean1 _*_ ___ *ll true_clean1
true_clean1 ___ ___ *** true

; State: write "true"
true ___ t__ r** true1
true1 ___ r__ r** true2
true2 ___ u__ r** true3
true3 ___ e__ r** true_halt