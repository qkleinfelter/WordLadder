copy "C:\Users\Quinn\Documents\GitHub\WordLadder\x64\Release\WordLadder.exe" "C:\Users\Quinn\Desktop\Word Ladder Testing"
cd "C:\Users\Quinn\Desktop\Word Ladder Testing"
ECHO Word Ladder Testing > output.txt
ECHO Invalid commands > output.txt
WordLadder > output.txt
WordLadder OWL.txt fool > output.txt
WordLadder OWL.txt > output.txt
WordLadder NonExistent.txt fool sage > output.txt

ECHO Non-existent word ladders > output.txt
WordLadder OWL.txt zzzzz clash > output.txt
WordLadder OWL.txt clash zzzzz > output.txt
WordLadder OWL.txt clash clash > output.txt

ECHO Some working ladders > output.txt
WordLadder OWL.txt clash clown > output.txt
WordLadder SOWPODS.txt clash clown > output.txt
WordLadder OWL.txt warm cold > output.txt
WordLadder SOWPODS.txt warm cold > output.txt
WordLadder OWL.txt ape man > output.txt
WordLadder SOWPODS.txt ape man > output.txt
WordLadder OWL.txt charge comedo > output.txt
WordLadder SOWPODS.txt charge comedo > output.txt
WordLadder OWL.txt cat dog > output.txt
WordLadder SOWPODS.txt cat dog > output.txt
WordLadder OWL.txt fool sage > output.txt
WordLadder SOWPODS.txt fool sage > output.txt
WordLadder OWL.txt atlases cabaret > output.txt
WordLadder SOWPODS.txt atlases cabaret > output.txt
WordLadder OWL.txt hate love > output.txt
WordLadder SOWPODS.txt hate love > output.txt
WordLadder OWL.txt lass male > output.txt
WordLadder SOWPODS.txt lass male > output.txt
WordLadder OWL.txt live dead > output.txt
WordLadder SOWPODS.txt live dead > output.txt

pause