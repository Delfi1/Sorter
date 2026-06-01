#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

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
            case 1: return this->age < rhs.age;
            case 2: return this->name < rhs.name;
            case 3: return this->email < rhs.email;
            case 4: return this->phone < rhs.phone;
            default: return this->id < rhs.id; // 0
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

// Status is refference to a value that can be scanned from py
int sorter(int* status, char* path, int key) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    std::ofstream temp("./temp.txt");
    std::ofstream out;

    int chunk = 0;
    std::stringstream ss;
    std::string line;
    std::vector<Record> buf;

    // Skip first (header) line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::string cell;
        Record row;

        if (std::getline(ss, cell, ',')) row.id = std::stoi(cell);
        if (std::getline(ss, cell, ',')) row.age = std::stoi(cell);
        if (std::getline(ss, cell, ',')) row.name = cell;
        if (std::getline(ss, cell, ',')) row.email = cell;
        if (std::getline(ss, cell, ',')) row.phone = cell;

        int i = 0;
        buf.push_back(row);
        *status = *status + 1;

        if (chunk == 0) {
            if (buf.size() >= 1024) {
                sort(buf.begin(), buf.end(), [key](Record &a, Record &b) {
                    return a.cmp(b, key);
                });

            }
        }

        chunk++;
    }

    file.close();
    out.close();
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
