
# Programmation et Algorithmique II





- [Enzo Bassot](https://github.com/MrzozoGit)
- [Guilhem Duval](https://www.github.com/GuilhemDuval)

## Rédaction

### Le container list

La structure "list" permet de stocker plusieurs éléments à la suite. Elle se base sur le principe de nœud et de pointeur. Fondamentalement, une "list" est une chaîne de nœuds. Chacun est relié au nœud précédent et au nœud suivant. La "list" est dite doublement chaîné, car un nœud de départ et un nœud de fin l'encadre. Ces nœuds permettent l'accès aux éléments par le début ou la fin de la liste.

L'utilisation de pointeur facilite l'insertion et la suppression des éléments. En effet, il suffit de modifier seulement les liens entre les éléments concernés au lieu de déplacer tous les éléments au sein de la mémoire. Cela minimise donc la réallocation de mémoire.

Cependant, l'accès à des éléments au milieu de la liste est moins optimal. La position de l'élément influe sur le nombre d'opérations comme il est nécessaire de parcourir tous les nœuds depuis le début ou la fin de la "list". Stocker les liens entre chaque nœud rend aussi l'utilisation de cette structure plus lourde en mémoire.

Concrètement, une "list" est utile s'il est nécessaire d'ajouter ou de supprimer des éléments de notre ensemble, peu importe leur position. L'accès complexe à des éléments est lui plus limité.

Une "list" serait donc pratique pour suivre les adhérents d'une association parisienne. Il serait possible d'ajouter un flux imprévisible d'adhérents. Il serait aussi possible de supprimer un adhérent qui quitte l'association sans utiliser trop de ressources.

### Le container vector

Un "vector" est un autre conteneur de données. Contrairement au précédent, les éléments sont stockés de manière contiguë. Dans la mémoire, les cases associées aux éléments se suivent obligatoirement. Ainsi, lors de la création d'un vecteur, une plage est délimitée en mémoire pour un nombre d'éléments finis. Lorsque ce nombre est dépassé, il est nécessaire de déplacer tous les éléments au sein d'une plage plus large, réallouer la mémoire.

Cela implique des avantages. Il est par exemple facile d'accéder aux éléments grâce à un index de position dans la suite. Les éléments côtés à côtes, il suffit de se déplacer linéairement dans la mémoire pour retrouver notre élément. L'ajout et la suppression d'éléments à la fin sont aisés comme elle ne nécessite aucun décalage d'éléments.

Les mêmes opérations sont coûteuses au milieu de la suite pour la raison inverse. Décaler les éléments est nécessaire pour laisser de la place ou en combler. De même, dépasser la capacité maximale du "vector" n'est pas conseillé, car elle enclenche des réallocations coûteuses. Un "vector" est donc optimal lorsque son nombre d'éléments est constant ou prévisible.

Le "vector" brille concrètement lorsque nous souhaitons accéder à des éléments variés du tableau. L'ajout ou la suppression d'entrées est, elle plus limitée.

Un "vector" serait donc parfait pour gérer le stock d'une association de prêt de matériel présente sur une université. Il serait facile d'accéder aux articles rapidement. De plus, le matériel n'est pas ordonné dans la suite, même si il est bien rangé dans les locaux. Aussi, le budget de l'association limite l'ajout de stock et les étudiants en prennent soin, donc pas trop de suppressions.

### Le container deque

"Deque" est l'acronyme de "Double-ended queue". Ce conteneur est comme une forme alternative du "vector" inspiré par les "list". Comme le "vector", il est implémenté sous forme contiguë en mémoire. Cependant, au lieu d'un unique bloc, des segments contigus sont séparés dans la mémoire et reliés par des pointeurs comme dans une "list".

Cette structure apporte les avantages de la "list". Les opérations en début, mais aussi en fin de la liste sont facilitées. Son évolution est aussi plus facile, car il n'est plus nécessaire de réaliser des réallocations complètes.

Des inconvénients naissent. Contrairement au "vector", le format contiguë segmenté ne permet pas l'accès aisé aux éléments par l'incrémentation. Accéder à des éléments au milieu de la suite est aussi plus complexe. De plus, le système de pointeur consomme plus en mémoire.

Pour résumer, la "deque" se spécialise dans l'accès, l'ajout et la suppression de données aux extrémités.

Une "deque" serait donc superbe pour contrôler les retours de matériel d'un bureau des arts actuellement sur Champs-sur-Marne. Lorsque les étudiants retournent le matériel emprunté, ils seront ajoutés à la fin de la file d'attente. Les intelligents gérants supprimeront les retours en début de suite. L'association, plus populaire lors des travaux audiovisuels des IMAC, sera prête à recevoir un grand nombre de retours et à voir sa file d'attente grandir dynamiquement.

### Le container map

La "map" est une structure associative. Elle associe et stocke une clé unique et une valeur. Cette clé permet de trier l'élément dans un arbre binaire de recherche. Les règles de tri des clés et de l'arbre sont personnalisables.

Ce système ouvre donc la porte à la recherche d'éléments optimisée. La comparaison de chaque branche de l'arbre permet d'accéder à l'élément souhaité et de limiter le parcours nécessaire.

Cependant, les opérations d'insertion et de suppression sont plus coûteuses, car la structure de l'arbre est rééquilibrée à chaque fois pour garantir des temps de recherche optimaux.

La "map" est donc plus cohérente avec certains systèmes. L'accès doit être au centre et les données doivent être triées et valorisées les unes par rapport à d'autres.

Une "map" serait donc efficace pour trier le stock de 803Z. Comme le stock changera rarement, l'arbre de recherche devra rarement être équilibré. Par contre, cette méthode alternative permettra d'accéder plus rapidement à certains articles suivant leur popularité par exemple. Les possibilités de tri et de clés sont infinies et permettraient d'optimiser la récupération de données sur le matériel en stock.
