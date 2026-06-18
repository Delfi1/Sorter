#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <random>
//#include <cstdio>

const int BUF_SIZE = 1024 * 256;
int ikey = 0;

class Record {
public:
    int id; // 0
    int age; // 1
    std::string name; // 2
    std::string email; // 3
    std::string phone; // 4

    // Compare two values
    // Returns true if a field hihger than b
    bool cmp(Record &rhs, int key) {
        switch (key) {
            case 1: return this->age > rhs.age;
            case 2: return this->name > rhs.name;
            case 3: return this->email > rhs.email;
            case 4: return this->phone > rhs.phone;
            default: return this->id > rhs.id; // 0
        };
    }

    std::string to_string() {
        std::string result;
        result += std::to_string(this->id) + ",";
        result += std::to_string(this->age) + ",";
        result += this->name + ",";
        result += this->email + ",";
        result += this->phone + ",";

        return result;
    }

    Record() {}

    void parse(std::string line) {
        std::stringstream stream(line);
        std::string cell;
        if (std::getline(stream, cell, ',')) this->id = std::stoi(cell);
        if (std::getline(stream, cell, ',')) this->age = std::stoi(cell);
        if (std::getline(stream, cell, ',')) this->name = cell;
        if (std::getline(stream, cell, ',')) this->email = cell;
        if (std::getline(stream, cell, ',')) this->phone = cell;
    }

    const bool operator>(const Record& b) const {
        switch (ikey) {
            case 1: return this->age > b.age;
            case 2: return this->name > b.name;
            case 3: return this->email > b.email;
            case 4: return this->phone > b.phone;
            default: return this->id > b.id; // 0
        };
    }

    const bool operator<(const Record& b) const {
        switch (ikey) {
            case 1: return this->age < b.age;
            case 2: return this->name < b.name;
            case 3: return this->email < b.email;
            case 4: return this->phone < b.phone;
            default: return this->id < b.id; // 0
        };
    }

    // Generate random row
    Record(int id, std::vector<std::string> fn, std::vector<std::string> ln, std::vector<std::string> e, std::vector<std::string> d) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> ages(16, 65);
        std::uniform_int_distribution<> fns(0, fn.size() - 1);
        std::uniform_int_distribution<> lns(0, ln.size() - 1);
        std::uniform_int_distribution<> emails(0, e.size() - 1);
        std::uniform_int_distribution<> domains(0, d.size() - 1);
        std::uniform_int_distribution<> phone(0, 9);

        this->id = id;
        this->age = ages(rng);
        this->name = fn[fns(rng)] + " " + ln[lns(rng)];
        this->email = e[emails(rng)] + d[domains(rng)];

        this->phone = std::string("+7");
        for (int j = 0; j < 10; j++) {
            this->phone += std::to_string(phone(rng));
        }
    }
};

struct HeapNode {
    Record record;
    size_t file_index;

    // Сравнение для std::greater (чтобы меньшие элементы выходили первыми)
    bool operator>(const HeapNode& other) const {
        return record > other.record;
    }
};

std::vector<std::string> read_data(std::string path) {
    std::vector<std::string> result;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        result.push_back(line);
    }
    return result;
}

class Sorter {
    float* status;
    int lines;

    std::vector<std::string> first_names;
    std::vector<std::string> last_names;
    std::vector<std::string> emails;

    const std::vector<std::string> domains = {"@example.com", "@gmail.com", "@yahoo.com", "@outlook.com"};

    std::vector<std::string> create_runs(const std::string& input_file, int run_size) {
        // Count file size
        std::ifstream in(input_file);
        std::string line;
        lines = 0;

        while (std::getline(in, line)) { lines++; }
        float ratio = 0.5f / lines;

        // Write to temp files
        std::vector<std::string> paths;
        std::ifstream file(input_file);

        bool more_input = true;
        int num = std::ceil(lines / run_size);
        paths.reserve(num);
        int i = 0;

        // skip first row
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::vector<Record> data;
            data.reserve(run_size);
            for (int i = 0; i < run_size; i++) {
                Record r;
                r.parse(line);
                data.push_back(r);

                if (!std::getline(file, line)) {
                    more_input = false;
                    break;
                }
            }

            if (data.empty()) break;

            std::sort(data.begin(), data.end());
            *status = *status + ratio * data.size();

            paths.push_back(std::to_string(i) + ".tmp");
            std::ofstream out(paths[i]);
            for (Record& record : data) {
                out << record.to_string() << "\n";
            }
            out.close();

            i++;
        }

        return paths;
    }

    void merge(const std::string& output, const std::vector<std::string>& paths) {
        std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> heap;

        std::ofstream out(output, std::ios::out | std::ios::binary);
        std::vector<char> out_buf(8192);
        out.rdbuf()->pubsetbuf(out_buf.data(), out_buf.size());

        int k = paths.size();
        std::vector<std::ifstream> files(k);
        std::vector<std::vector<char>> in_bufs(k, std::vector<char>(8192));

        for (size_t i = 0; i < k; ++i) {
            files[i].open(paths[i], std::ios::in | std::ios::binary);
            files[i].rdbuf()->pubsetbuf(in_bufs[i].data(), in_bufs[i].size());

            std::string line;
            std::getline(files[i], line);
            Record r;
            r.parse(line);
            heap.push({r, i});
        }

        float ratio = 0.5f / lines;
        while (!heap.empty()) {
            HeapNode root = heap.top();
            heap.pop();

            out << root.record.to_string() << "\n";

            std::string line;
            if (std::getline(files[root.file_index], line)) {
                Record r;
                r.parse(line);
                heap.push({r, root.file_index});
            }

            *status = *status + ratio;
        }

        *status = 1.0f;

        for (auto& file : files) {
            file.close();
        }

        for (auto& path : paths) {
            std::remove(path.c_str());
        }
    }

public:
    void generate(float* status, char* path, int count) {
        char buffer[8192];
        std::ofstream out;
        out.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
        out.open(path, std::ios::binary);
        float ratio = 1.0f / count;

        out << "id,age,name,email,phone\n";
        for (int i = 0; i < count; i++) {
            out << Record(i, first_names, last_names, emails, domains).to_string() << "\n";
            *status = *status + ratio;
        }

        out.close();
        *status = 1.0f;
    }

    void sort(float* status, char* path, int key) {
        *status = 0.0f;
        this->status = status;
        ikey = key;

        std::vector<std::string> paths = create_runs(path, BUF_SIZE);
        merge(path, paths);
    }

    Sorter() {
        first_names = read_data("./FirstN.txt");
        last_names = read_data("./LastN.txt");
        emails = read_data("./Emails.txt");
    }
};

extern "C" {
    __declspec(dllexport) Sorter* init() { return new Sorter(); }
    __declspec(dllexport) void sort(Sorter* self, float* status, char* path, int key) { self->sort(status, path, key); }
    __declspec(dllexport) void generate(Sorter* self, float* status, char* path, int count) { self->generate(status, path, count); }
}
