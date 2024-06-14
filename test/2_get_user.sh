http localhost:8000/api/user name=root
http localhost:8000/api/user name=ken
http localhost:8000/api/user name=tux

response=$(curl localhost:8000/api/user/2 2>/dev/null)

id=$(echo "$response" | awk '{match($0, /id: ([0-9]+),/, arr); print arr[1]}')
name=$(echo "$response" | awk '{match($0, /name: ([a-zA-Z]+),/, arr); print arr[1]}')

echo "$id" "$name"

if [ "$id" != 2 ] || [ "$name" != tux ]; then
	echo "expected user tux with id 2, got $name and $id"
fi
