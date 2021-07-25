# c_concepts
This repository contains all the snippets for C programming concepts

# coding guidelines

* Functions -- mixed case -- get/set or accessor/mutator  can be as variables, all lowercase with '_'
* Variables and datamemebers -- all lowercase separated with '_' , class datamembers would have trailing '_'
* All types -- typedef, class, struct and aliasiing -- mixed case
* All constants -- enum, const type should be like starting with 'k', other global and static should be mixed type.
* File names -- all lower with '_' or '-' separated. -- make sure fiel names are not collided with /user/includes/
   - foo_bar.c and foo_bar.h , like that .c and .h should be used in pairing.
* All macros should be in ALL CAPS separated by '_'

* General rule
   - No abbreviation should be used. if used at all, then check if it is available in wikipedia and wordly known.
   - if there's abbreviation while naming, then ignore using capital words for abbreviated term. e.g. use SomeRpc , rather than SomeRPC.

