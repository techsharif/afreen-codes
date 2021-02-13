import csv
import sys


if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

database_file = sys.argv[1]
sequence_file = sys.argv[2]

data = []


with open(database_file) as file:
    reader = csv.DictReader(file)
    for row in reader:
        data += [row]

with open(sequence_file) as file:
    dna = file.read()


map_name_hash = {}
map_hash_name = {}
count = {}


i = 0
for key in data[0].keys():
    map_name_hash[key] = str(i)
    map_hash_name[str(i)] = key
    count[str(i)] = 0
    i += 1


for key, value in map_name_hash.items():
    dnaa = dna.replace(key, value)
    previous = dnaa[0]
    cnt = 0
    for d in dnaa:
        if d == previous:
            cnt += 1
        else:
            if previous.isdigit():
                count[previous] = max(count[previous], cnt)
            cnt = 1

        previous = d

# print(count)
name = ""
val = 0
for db in data:
    name = db["name"]
    for key, value in db.items():
        if key == "name":
            continue

        h = map_name_hash[key]
        if str(count[h]) != value:
            name = ""
    if name:
        break

if name:
    print(name)
else:
    print("No match")

