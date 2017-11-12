# !/bin/sh

if [ -e index.html ]; then
    echo "File exists in directory!"
else
    `wget -O index.html youtube.com`
fi

grep data-sessionlink index.html | grep views | while read lines; do
    views=`expr "$lines" : ".*<li>\(.*\) views</li>.*"`
    echo ${views//,/}
done > view.txt 

grep data-sessionlink index.html | grep user | while read lines; do
    user=`expr "$lines" : ".*user/\([^\"]*\)\".*"`
    echo $user
done > user.txt

grep data-sessionlink index.html | grep Duration | while read lines; do
    duration=`expr "$lines" : ".*Duration: \([0-9:]*\)\..*"`
    echo $duration
done > duration.txt

grep data-sessionlink index.html | grep aria-described | while read lines; do
    title=`expr "$lines" : ".*title=\"\([^\"]*\)\" aria-describedby.*"`
    echo $title
done > title.txt #I greped aria-described because title would give me weird spaces in between some titles

`paste user.txt view.txt duration.txt title.txt > gTable.txt | sort -nr`
