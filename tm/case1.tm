; the finite set of states
#Q = {0,check,mr_reject,illegal,check1,check2,mh_accept,accept,clean,accept_halt,illegal1,illegal2,illegal3,illegal4,illegal5,illegal6,illegal7,illegal8,illegal9,illegal10,illegal11,illegal12,reject_halt}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {c,_,i,l,e,g,a,b}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {accept_halt}

; the number of tapes
#N = 1

; the transition functions

; State 0: start state
0 a a * check
0 b b * mr_reject
0 _ _ * illegal ; empty input

; State check: check format a^nb^m and n,m>0
check a a r check1
check b b * mr_reject
check1 a a r check1
check1 b b r check2
check1 _ _ * mr_reject
check2 a a * mr_reject
check2 b b r check2
check2 _ _ l mh_accept

; State mh: move 1st head to the left and accpet
mh_accept a a l mh_accept
mh_accept b b l mh_accept
mh_accept _ _ r accept

; State mr: move 1st head to the right
mr_reject a a r mr_reject
mr_reject b b r mr_reject
mr_reject _ _ l clean

; State clean: clean non-empty char from right
clean a _ l clean
clean b _ l clean
clean _ _ * illegal


; State accept*: write 'c's on 1st tape
accept a c r accept
accept b c r accept
accept _ _ * accept_halt

; State illegal*: write 'illegal' on 1st tape
illegal _ i r illegal1
illegal1 _ l r illegal2
illegal2 _ l r illegal3
illegal3 _ e r illegal4
illegal4 _ g r illegal5
illegal5 _ a r illegal6
illegal6 _ l r illegal7
illegal7 _ _ r illegal8
illegal8 _ i r illegal9
illegal9 _ n r illegal10
illegal10 _ p r illegal11
illegal11 _ u r illegal12
illegal12 _ t * reject_halt