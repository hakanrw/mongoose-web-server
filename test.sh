RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
RESET='\033[0m'

fail=0
total=0

for test in test/*; do
        printf "\n${YELLOW}+-------------+\n${YELLOW}running test %s\n${YELLOW}+-------------+\n\n${RESET}" $test
        ./bin/web & pid=$!
        sleep 0.5
        total=$((total + 1))
        sh "$test"
        ret=$?
        [ $ret != 0 ] && fail=$((fail + 1)) && printf "\n${RED}!-------------!\n${RED}test %s failed\n${RED}!-------------!\n\n${RESET}" $test
        [ $ret = 0 ] && printf "\n${GREEN}+-------------+\n${GREEN}test %s succeeded\n${GREEN}+-------------+\n\n${RESET}" $test
        kill $pid
        wait $pid 2>/dev/null
done

[ $fail != 0 ] && printf "\n${RED}!-------------!\n${RED}%d tests failed\n${RED}!-------------!\n\n${RESET}" $fail
[ $fail = 0 ] && printf "\n${GREEN}+-------------+\n${GREEN}%d tests succeeded\n${GREEN}+-------------+\n\n${RESET}" $total
