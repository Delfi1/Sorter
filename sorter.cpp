#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <cstdio>

const int BUF_SIZE = 1024 * 256;

const std::vector<std::string> FIRST_NAMES = {
    "Liam", "Noah", "Oliver", "Elijah", "James", "William", "Benjamin", "Lucas", "Henry", "Theodore",
    "Jack", "Levi", "Alexander", "Owen", "Asher", "Samuel", "Leo", "Felix", "Silas", "Hudson",
    "Ezra", "Jasper", "Jude", "Rowan", "Finn", "Milo", "Arthur", "Sebastian", "Julian", "Caleb",
    "Thomas", "Gabriel", "Victor", "Olivia", "Emma", "Charlotte", "Amelia", "Sophia", "Isabella", "Mia",
    "Evelyn", "Harper", "Luna", "Camila", "Gianna", "Eliana", "Ella", "Violet", "Hazel", "Willow",
    "Lily", "Aurora", "Penelope", "Eleanor", "Clara", "Rose", "Ivy", "Alice", "Cora", "Ruby",
    "Iris", "Nora", "Genevieve", "Maeve", "Maya", "Chloe", "Avery", "Quinn", "Taylor", "Morgan",
    "Finley", "Jordan", "Cameron", "Riley", "Peyton", "Sage", "Alex", "Robin", "Logan", "Casey",
    "Reese", "Jamie", "Skyler", "Shiloh", "River", "Parker", "Emerson", "Dallas", "Phoenix", "Dakota",
    "Tatum", "Hayden", "Harley", "Marley", "Remy", "Rory", "Aspen", "Charlie", "Eden", "Wren"
};

const std::vector<std::string> LAST_NAMES = {
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez",
    "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin",
    "Lee", "Perez", "Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson",
    "Walker", "Young", "Allen", "King", "Wright", "Scott", "Torres", "Nguyen", "Hill", "Flores",
    "Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Roberts",
    "Gomez", "Phillips", "Evans", "Turner", "Diaz", "Parker", "Cruz", "Edwards", "Collins", "Reyes",
    "Stewart", "Morris", "Morales", "Murphy", "Cook", "Rogers", "Gutierrez", "Ortiz", "Morgan", "Cooper",
    "Peterson", "Bailey", "Reed", "Kelly", "Howard", "Ramos", "Kim", "Cox", "Ward", "Richardson",
    "Watson", "Brooks", "Chavez", "Wood", "James", "Bennett", "Gray", "Mendoza", "Ruiz", "Hughes",
    "Price", "Alvarez", "Castillo", "Sanders", "Patel", "Myers", "Long", "Ross", "Foster", "Jimenez"
};

const std::vector<std::string> EMAILS = {
    "cyber_ghost99", "pixel.wizard", "shadow_ninja", "quantum_coder", "cosmic.wanderer",
    "alpha_omega", "techno_vibe", "silver_fox42", "neon_rider", "digital.nomad",
    "sonic_boom", "iron_clad", "frost_bite", "phoenix_rising", "storm_bringer",
    "starlight_01", "hyper_drive", "velvet_glove", "mystic_river", "golden_eagle",
    "retro_gamer", "matrix_reloaded", "lunar_eclipse", "solar_flare", "vortex_traveler",
    "zen_master", "code_monkey", "binary_boss", "cyber_punk", "echo_location",
    "whispering_wind", "silent_assassin", "wild_card", "night_owl", "early_bird",
    "coffee_addict", "book_worm", "movie_buff", "music_lover", "globetrotter",
    "urban_explorer", "nature_lover", "beach_bum", "mountain_goat", "sky_diver",
    "deep_sea", "star_gazer", "dream_catcher", "peace_maker", "risk_taker",
    "trend_setter", "game_changer", "thought_leader", "problem_solver", "pixel_perfect",
    "bug_hunter", "data_miner", "cloud_surfer", "network_ninja", "security_guru",
    "crypto_king", "token_master", "block_chain", "web_developer", "app_designer",
    "ui_ux_pro", "qa_wizard", "devops_guy", "sysadmin_pro", "tech_savvy",
    "gadget_geek", "sci_fi_fan", "fantasy_nerd", "comic_book", "anime_lover",
    "manga_reader", "j-pop_fan", "k-pop_stan", "rock_star", "pop_diva",
    "jazz_cat", "blues_man", "hip_hop_head", "dj_remix", "sound_wave",
    "beat_maker", "lyrics_writer", "art_lover", "photo_grapher", "video_grapher",
    "content_creator", "vlogger_life", "blogger_world", "influencer_00", "social_media",
    "digital_art", "sketch_artist", "painter_pro", "sculptor_01", "creative_mind"
};

class std::vector<std::string> DOMAINS = {"@example.com", "@gmail.com", "@yahoo.com", "@outlook.com"};
int ikey = 0;

class Record {
public:
    int id; // 0
    int age; // 1
    std::string name; // 2
    std::string email; // 3
    std::string phone; // 4

    // Compare to values
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

    bool operator>(const Record& b) {
        switch (ikey) {
            case 1: return this->age > b.age;
            case 2: return this->name > b.name;
            case 3: return this->email > b.email;
            case 4: return this->phone > b.phone;
            default: return this->id > b.id; // 0
        };
    }

    bool operator<(const Record& b) {
        switch (ikey) {
            case 1: return this->age < b.age;
            case 2: return this->name < b.name;
            case 3: return this->email < b.email;
            case 4: return this->phone < b.phone;
            default: return this->id < b.id; // 0
        };
    }

    // Generate random row
    Record(int id) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> ages(16, 65);
        std::uniform_int_distribution<> fns(0, FIRST_NAMES.size() - 1);
        std::uniform_int_distribution<> lns(0, LAST_NAMES.size() - 1);
        std::uniform_int_distribution<> emails(0, EMAILS.size() - 1);
        std::uniform_int_distribution<> domains(0, DOMAINS.size() - 1);
        std::uniform_int_distribution<> phone(0, 9);

        this->id = id;
        this->age = ages(rng);
        this->name = FIRST_NAMES[fns(rng)] + " " + LAST_NAMES[lns(rng)];
        this->email = EMAILS[emails(rng)] + DOMAINS[domains(rng)];

        this->phone = std::string("+7");
        for (int j = 0; j < 10; j++) {
            this->phone += std::to_string(phone(rng));
        }
    }
};

struct HeapNode {
    Record element;
    int index;
};

void swap(HeapNode* x, HeapNode* y)
{
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
}

class Heap {

    // pointer to array of elements in heap
    HeapNode* harr;

    // size of min heap
    int heap_size;

public:

    // Constructor: creates a min
    // heap of given size
    Heap(HeapNode a[], int size);

    // to heapify a subtree with
    // root at given index
    void Heapify(int);

    // to get index of left child
    // of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child
    // of node at index i
    int right(int i) { return (2 * i + 2); }

    // to get the root
    HeapNode getMin() { return harr[0]; }

    // to replace root with new node
    // x and heapify() new root
    void replaceMin(HeapNode x)
    {
        harr[0] = x;
        Heapify(0);
    }
};

Heap::Heap(HeapNode a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        Heapify(i);
        i--;
    }
}

void Heap::Heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap_size && harr[l].element < harr[i].element)
        smallest = l;

    if (r < heap_size
        && harr[r].element < harr[smallest].element)
        smallest = r;

    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        Heapify(smallest);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

FILE* openFile(char* fileName, char* mode)
{
    FILE* fp = fopen(fileName, mode);
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void mergeFiles(char* output_file, int k)
{
    FILE* in[k];
    for (int i = 0; i < k; i++) {
        char* fileName = (std::to_string(i) + ".tmp").data();
        in[i] = openFile(fileName, "r");
    }

    FILE* out = openFile(output_file, "w");

    HeapNode* harr = new HeapNode[k];
    int i;
    for (i = 0; i < k; i++) {
        if (fscanf(in[i], "%d ", &harr[i].element) != 1)
            break;

        harr[i].i = i;
    }
    Heap hp(harr, i);

    int count = 0;
    while (count != i) {
        HeapNode root = hp.getMin();
        fprintf(out, root.element.to_string().c_str());

        if (fscanf(in[root.index], "%d ", &root.element) != 1) {
            count++;
        }

        hp.replaceMin(root);
    }

    for (int i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

void createRuns(char* file, int run_size, int num)
{
    FILE* in = openFile(file, "r");

    FILE* out[num];
    char fileName[2];
    for (int i = 0; i < num; i++) {
        snprintf(fileName, sizeof(fileName), "%d", i);

        out[i] = openFile(fileName, "w");
    }

    int* arr = (int*)malloc(run_size * sizeof(int));

    bool more_input = true;
    int next_output_file = 0;

    int i;
    while (more_input) {
        for (i = 0; i < run_size; i++) {
            if (fscanf(in, "%d ", &arr[i]) != 1) {
                more_input = false;
                break;
            }
        }

        mergeSort(arr, 0, i - 1);

        for (int j = 0; j < i; j++)
            fprintf(out[next_output_file], "%d ", arr[j]);

        next_output_file++;
    }

    for (int i = 0; i < num; i++)
        fclose(out[i]);
        std::remove((std::to_string(i) + ".tmp").c_str());

    fclose(in);
}

// Status is refference to a value that can be scanned from py
int sorter(int* status, char* path, int key) {
    ikey = key;

    int num = 128;
    createRuns(path, BUF_SIZE, num);

    mergeFiles("result.txt", num);

    return 0;
}

int generator(int* status, char* path, int count) {
    char buffer[8192];
    std::ofstream out;
    out.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
    out.open(path, std::ios::binary);

    out << "id,age,name,email,phone\n";
    for (int i = 0; i < count; i++) {
        out << Record(i).to_string() << "\n";
        *status = *status + 1;
    }

    out.close();
    return 0;
}

extern "C" {
    __declspec(dllexport) int sort(int* status, char* path, int key) { return sorter(status, path, key); }
    __declspec(dllexport) int generate(int* status, char* path, int count) { return generator(status, path, count); }
}
