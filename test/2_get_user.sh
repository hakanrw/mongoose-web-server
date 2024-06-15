curl -X POST -H "Content-Type: application/json" -d '{"name":"root"}' http://localhost:8000/api/user 2>/dev/null
curl -X POST -H "Content-Type: application/json" -d '{"name":"ken"}' http://localhost:8000/api/usera 2>/dev/null
curl -X POST -H "Content-Type: application/json" -d '{"name":"tux"}' http://localhost:8000/api/user 2>/dev/null

response=$(curl localhost:8000/api/user/2 2>/dev/null)

id=$(echo "$response" | gawk '{match($0, /id: ([0-9]+),/, arr); print arr[1]}')
name=$(echo "$response" | gawk '{match($0, /name: ([a-zA-Z]+),/, arr); print arr[1]}')

echo "$id" "$name"

if [ "$id" != 2 ] || [ "$name" != tux ]; then
	echo "expected user tux with id 2, got $name and $id"
	exit 1
fi
