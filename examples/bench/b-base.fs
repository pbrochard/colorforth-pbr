variable cnt    1000 cnt !
variable v           1   v !

: go recursive v @ cnt @ dup * + v ! cnt @ 1- dup cnt ! if go then ;

go v @ . bye
