for i in {1..128}; do
	curl -X POST -H "Content-Type: application/json" -d '{"name":"user$i"}' http://localhost:8000/api/user -m 5 1>/dev/null 2>/dev/null

	if [ $? != 0 ]; then
		exit 1 # fail on no-response
	fi
done
