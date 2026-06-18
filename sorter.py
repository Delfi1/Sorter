import heapq
import math
import os
import random

BUF_SIZE = 1024 * 128


def load_data(name: str) -> list[str]:
    with open(name, "r") as f:
        return [line.strip() for line in f]


FIRST_NAMES = load_data("FirstN.txt")
LAST_NAMES = load_data("LastN.txt")
EMAILS = load_data("Emails.txt")
DOMAINS = ["@example.com", "@gmail.com", "@yahoo.com", "@outlook.com"]
ikey = 0


class Record:
    def __init__(self):
        self.id: int = 0
        self.age: int = 0
        self.name: str = str()
        self.email: str = str()
        self.phone: str = str()

    def parse(self, line: str):
        data = line.split(",")
        self.id = int(data[0].strip())
        self.age = int(data[1].strip())
        self.name = data[2].strip()
        self.email = data[3].strip()
        self.phone = data[4].strip()

        return self

    # Returns value by key id
    def value(self, key: int) -> int | str:
        match key:
            case 1:
                return self.age
            case 2:
                return self.name
            case 3:
                return self.email
            case 4:
                return self.phone
            case _:
                return self.id  # 0

    def __lt__(self, other):
        global ikey

        match ikey:
            case 1:
                return self.age < other.age
            case 2:
                return self.name < other.name
            case 3:
                return self.email < other.email
            case 4:
                return self.phone < other.phone
            case _:
                return self.id < other.id

    def generate(self, id: int):
        self.id = id
        self.age = random.randint(16, 65)
        a = random.randint(0, len(FIRST_NAMES) - 1)
        b = random.randint(0, len(LAST_NAMES) - 1)
        email = random.randint(0, len(EMAILS) - 1)
        domain = random.randint(0, len(DOMAINS) - 1)

        self.name = FIRST_NAMES[a] + " " + LAST_NAMES[b]
        self.email = EMAILS[email] + DOMAINS[domain]
        self.phone = "+7"
        for _ in range(0, 10):
            self.phone += str(random.randint(0, 9))

    def __str__(self) -> str:
        result = str()
        result += str(self.id) + ","
        result += str(self.age) + ","
        result += self.name + ","
        result += self.email + ","
        result += self.phone + ","
        return result


class Sorter:
    def __init__(self):
        self.status = 0.0
        self.lines = 0

    def generate(self, path: str, count: int):
        self.status = 0.0
        with open(path, "w", encoding="utf-8", buffering=8192) as file:
            file.write("id,age,name,email,phone\n")
            for i in range(count):
                record = Record()
                record.generate(i)
                file.write(str(record) + "\n")

                self.status += 1 / count

        self.status = 1.0

    # 0-50% - create runs & sort
    def create_runs(self, input_file, run_size):
        self.lines = 0

        with open(input_file, "r") as file:
            f = file.readline()
            while f:
                f = file.readline()
                self.lines += 1

        file = open(input_file, "r")
        file.readline()  # Skip first line

        num = math.ceil(self.lines / BUF_SIZE)

        paths = [f"{i}.tmp" for i in range(num)]
        out_files = [open(p, "w", buffering=8192) for p in paths]

        more_input = True
        next = 0
        ratio = 0.5 / self.lines

        while more_input:
            data = []
            for _ in range(run_size):
                line = file.readline().strip()
                if line:
                    r = Record().parse(line)
                    data.append(r)
                else:
                    more_input = False
                    break

            data.sort()
            self.status += ratio * len(data)
            for r in data:
                out_files[next].write(str(r) + "\n")

            next += 1

        for i in range(num):
            out_files[i].close()

        file.close()
        return paths

    def merge(self, output, paths):
        heap = []
        out = open(output, "w", buffering=8192)

        files = [open(p, "r") for p in paths]
        k = len(files)
        ratio = 0.5 / self.lines

        for i in range(k):
            element = files[i].readline().strip()
            if element:
                r = Record().parse(element)
                heapq.heappush(heap, (r, i))

        while heap:
            root = heapq.heappop(heap)
            out.write(str(root[0]) + "\n")

            element = files[root[1]].readline().strip()
            if element:
                r = Record().parse(element)
                heapq.heappush(heap, (r, root[1]))

            self.status += ratio

        self.status = 1.0

        for i in range(k):
            files[i].close()
            os.remove(paths[i])
        out.close()

    def sort(self, path: str, key: int):
        global ikey
        self.status = 0.0
        ikey = key

        paths = self.create_runs(path, BUF_SIZE)
        self.merge("result.txt", paths)

    def value(self) -> float:
        return self.status
