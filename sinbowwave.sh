#!/bin/bash
# Cycle though colors making a sine wave on the whole display
d=0

digits=()

for i in {1..12}; do

	digits[d]=$(printf "h%02d" $i)
	((d+=1))

done

for i in {0..59}; do

	digits[d]=$(printf "m%02d" $i)

echo $(printf "%02dm" $i)
	((d+=1))

done

#now loaded into a linear array, lets map to the actual x-y layout



#step though some nice colors

while true; do  


	for color in "3f0000" "003f00" "222222"; do

		for i in {0..71}; do

		name=${digits[i]}

		ip=$(getent hosts $name | awk '{ print $1 }')

 		./udpopc $ip $color 0 59 0 25
		#sleep 1
		done < leases.lnk

		sleep 1

		# braodscast off to all

 		./udpopc 192.168.174.255 000030 0 59 0 25

		sleep 1

	done

done
