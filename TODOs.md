CI:  
- passer plus de sanitizers sur le build Clang

IMPORTANT: Require return statement / main doit avoir return Void
IMPORTANT: Emp�cher d'avoir fn/var avec m�me nom que des keywords

ajouter exemples dans la doc doxygen des AST nodes
introduire notion de priorit� d'op�rations
commentaires pour d�tailler le parsing (surtout ce qui est attendu � la fin des fonctions)
Refactoring des passes s�mantiques (trop de r�p�titions)
Commenter ASTReader (mCurrentLine)
Trie for symbol table??
Tests pour Overload Resolution
Tests pour CallStack
Tests pour array function parameter et return type
Revoir les inclusions (surtout � la bordure TosLang/Tostitos)
friend accesseur ChildrenNodes pour ASTVisitor

Tests:
- binop entre identifiers
- binop avec call + kkchose
- variable decl dans une fonction (correct + errors)
- mise � jour du test de ASTVisitor
- Ajout commentaires dans les tests
- EOF dans d�claration de fonction

Plus tard, faire tests de syt�me:
	- tri rapide
	- multiplication de matrices
	- somme des �l�ments d'un vecteur

Faire un fuzzer pour TosLang ??

Faire un Learn X in Y minutes