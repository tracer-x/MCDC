#This shell script is written by Sangharatna Godboley. It main objective is to find the test case number when the Seq. number is 95%
export BENCHMARK=$1
let m=1
read lines words chars filename <<< $(wc $1)
echo "Total number of sequence found: $lines"
while IFS='' read -r line || [[ -n "$line" ]]; do
    z=$(bc <<<"scale=2;${m}/${lines} * 100")
    q=${z%.*}  
    if [ "$q" -eq 95 ]
    then
    echo "Percentile of found Sequence: $z"
    echo "Text read from file: $line"
    echo "Text read from file: $line" > Percentile-${BENCHMARK}.txt
    fi
    ((m = m + 1))
done < "$1"




