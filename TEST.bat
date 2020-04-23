cd "C:\Users\Quinn\Desktop\Word Ladder Testing"
ECHO Word Ladder Testing
ECHO Invalid commands
WordLadder
WordLadder OWL.txt fool
WordLadder OWL.txt
WordLadder NonExistent.txt fool sage

ECHO Non-existent word ladders
WordLadder OWL.txt zzzzz clash
WordLadder OWL.txt clash zzzzz
WordLadder OWL.txt clash clash

ECHO Some working ladders
WordLadder OWL.txt clash clown
WordLadder SOWPODS.txt clash clown
WordLadder OWL.txt warm cold
WordLadder SOWPODS.txt warm cold
WordLadder OWL.txt ape man
WordLadder SOWPODS.txt ape man
WordLadder OWL.txt charge comedo
WordLadder SOWPODS.txt charge comedo
WordLadder OWL.txt cat dog
WordLadder SOWPODS.txt cat dog
WordLadder OWL.txt fool sage
WordLadder SOWPODS.txt fool sage
WordLadder OWL.txt atlases cabaret
WordLadder SOWPODS.txt atlases cabaret

pause