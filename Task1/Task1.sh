./removeFile.sh
touch clean.txt
touch shufList.txt 
echo "Getting words from word list"
cat ../wlist_all/wlist_match1.txt > copy.txt
echo "Shuffling words"
shuf copy.txt >> shufList.txt
echo "Filtering words, removing words that contain anything apart from the alphabets, are less than 3 or more than 15 letter in length and if two letters occur consecutively"
cat shufList.txt | grep -E "^[a-zA-Z]*$" | grep -E '^.{3,15}$' |  grep -v '\(.\)\1'> clean.txt
echo "Sorting words based on 3rd letter"
sort -k1.3 clean.txt | uniq >> finalClean.txt
echo "Checking if any duplicates are present (will not print if no duplicates are present)"
sort finalClean.txt | uniq -cd
echo "Printing the total lines in the different files"
wc -l ../wlist_all/wlist_match1.txt
wc -l shufList.txt
wc -l clean.txt
wc -l finalClean.txt