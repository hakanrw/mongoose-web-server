printf "spamming users"

for i in {1..128}; do
	response=$(curl -X POST -H "Content-Type: application/json" -d '{"name":"user$i"}' http://localhost:8000/api/user -m 5 2>&1)
	
	if [ $? != 0 ]; then
		echo # newline
		echo "$response" # show error
		exit 1 # fail on no-response
	fi

	if ((i % 4 == 0)); then 
		printf . # progress bar
	fi
done

echo # newline
