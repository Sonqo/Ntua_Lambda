listens2Music(mia).
listens2Music(yolanda):- 
    happy(yolanda).  
happy(yolanda). 
playsAirGuitar(mia):- 
    listens2Music(mia). 
playsAirGuitar(yolanda):- 
    listens2Music(yolanda). 

is_digesting(X,Y) :- just_ate(X,Y). 
is_digesting(X,Y) :- 
    just_ate(X,Z), 
    is_digesting(Z,Y). 
just_ate(mosquito,blood(john)). 
just_ate(frog,mosquito). 
just_ate(stork,frog).

child(bridget,caroline). 
child(caroline,donna).
child(anne,bridget). 
child(bridget,caroline). 
child(caroline,donna). 
child(donna,emily).
descend(X,Y) :- child(X,Y). 
descend(X,Y) :- child(X,Z), 
    descend(Z,Y).

numeral(0). 
numeral(succ(X)) :- numeral(X).