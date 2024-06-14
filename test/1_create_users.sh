curl -X POST -H "Content-Type: application/json" -d '{"name":"root"}' http://localhost:8000/api/user
curl -X POST -H "Content-Type: application/json" -d '{"name":"ken"}' http://localhost:8000/api/user
curl -X POST -H "Content-Type: application/json" -d '{"name":"tux"}' http://localhost:8000/api/user

response=$(curl localhost:8000/api/user 2>/dev/null)

count=0

while read -r line; do
	id=$(echo "$line" | awk '{match($0, /id: ([0-9]+),/, arr); print arr[1]}')
	name=$(echo "$line" | awk '{match($0, /name: ([a-zA-Z]+),/, arr); print arr[1]}')

	echo $id $name

	if [ "$count" == 0 ] && [ "$name" != root ]; then
		echo "expected id=0 to be root, got $name"
		exit 1
	fi
	
	if [ "$count" == 1 ] && [ "$name" != ken ]; then
		echo "expected id=1 to be ken, got $name"
		exit 1
	fi
	
	if [ "$count" == 2 ] && [ "$name" != tux ]; then
		echo "expected id=2 to be tux, got $name"
		exit 1
	fi
	
	count=$((count + 1))
done <<< "$response"

if [ "$count" != 3 ]; then
	echo "expected user count to be 3, got $count"
	exit 1
fi
