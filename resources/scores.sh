NC='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'

total=0
won=0
error=0
timeout=0
for map in ./maps/*
do
	echo "${PURPLE}TESTING FOR $map ${NC}"
	for file in ./players/*
	do
		echo "\n----->${ORANGE}TESTING FOR $file"
		echo "${YELLOW}PLAYING AGAINST $file AS P1${NC}"
		local_win=0
		for i in 1 2 3 4 5 6 7 8 9 10
		do
			echo "${CYAN}game $i${NC}"
			./filler_vm -f "$map" -p1 "$file" -p2 ./mybenzar.filler > my_trace.txt 2> err.log
			if grep -q "X: error on input" filler.trace; then
				echo "${RED}ERROR ON INPUT${NC}"
				grep -i "seed" filler.trace
				let "error++"
			fi
			if grep -q "X: timedout" filler.trace; then
				echo "${RED}TIMEDOUT${NC}"
				grep -i "seed" filler.trace
				let "timeout++"
			fi
			if grep -q "./mybenzar.filler won" filler.trace; then
				echo "${GREEN}I WON${NC}"
				let " won++"
				let "local_win++"
			fi 
			if grep -q "$file won" filler.trace; then
				echo "${RED}I LOST${NC}"
				grep -i "seed" filler.trace
			fi
			grep -i "./" filler.trace
			echo "game $i\n" >> scores.csv
			cat filler.trace >> scores.csv
			let "total++"
		done
		if [[ "$local_win" -ge 3 ]]; then
			echo "${GREEN}>>>>>won $local_win / $i games"
		else
			echo "${RED}>>>>>won $local_win / $i games"
		fi
		echo "${YELLOW}PLAYING AGAINST $file AS P2${NC}"
		local_win=0
		for i in 1 2 3 4 5 6 7 8 9 10
		do
			echo "${CYAN}game $i${NC}"
			./filler_vm -f "$map" -p2 "$file" -p1 ./mybenzar.filler > my_trace.txt 2> err.log
			if grep -q "O: error on input" filler.trace; then
				echo "${RED}ERROR ON INPUT${NC}"
				grep -i "seed" filler.trace
				let "error++"
			fi
			if grep -q "O: timedout" filler.trace; then
				echo "${RED}TIMEDOUT${NC}"
				grep -i "seed" filler.trace
				let "timeout++"
			fi
			if grep -q "./mybenzar.filler won" filler.trace; then
				echo "${GREEN}I WON${NC}"
				let " won++" 
				let "local_win++"
			fi
			if grep -q "$file won" filler.trace; then
				echo "${RED}I LOST${NC}"
				grep -i "seed" filler.trace
			fi
			grep -i "./" filler.trace
			echo "\ngame $i\n" >> scores.csv
			cat filler.trace >> scores.csv
			let "total++"
		done
		if [[ "$local_win" -ge 3 ]]; then
			echo "${GREEN}>>>>>won $local_win / $i games"
		else
			echo "${RED}>>>>>won $local_win / $i games"
		fi
	done
done
echo "${GREEN}WON $won OVER $total${NC}"
echo "${RED}$error ERRORS${NC}"
