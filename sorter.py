import heapq
import os
import random

BUF_SIZE = 1024 * 256

FIRST_NAMES = [
    "Liam",
    "Noah",
    "Oliver",
    "Elijah",
    "James",
    "William",
    "Benjamin",
    "Lucas",
    "Henry",
    "Theodore",
    "Jack",
    "Levi",
    "Alexander",
    "Owen",
    "Asher",
    "Samuel",
    "Leo",
    "Felix",
    "Silas",
    "Hudson",
    "Ezra",
    "Jasper",
    "Jude",
    "Rowan",
    "Finn",
    "Milo",
    "Arthur",
    "Sebastian",
    "Julian",
    "Caleb",
    "Thomas",
    "Gabriel",
    "Victor",
    "Olivia",
    "Emma",
    "Charlotte",
    "Amelia",
    "Sophia",
    "Isabella",
    "Mia",
    "Evelyn",
    "Harper",
    "Luna",
    "Camila",
    "Gianna",
    "Eliana",
    "Ella",
    "Violet",
    "Hazel",
    "Willow",
    "Lily",
    "Aurora",
    "Penelope",
    "Eleanor",
    "Clara",
    "Rose",
    "Ivy",
    "Alice",
    "Cora",
    "Ruby",
    "Iris",
    "Nora",
    "Genevieve",
    "Maeve",
    "Maya",
    "Chloe",
    "Avery",
    "Quinn",
    "Taylor",
    "Morgan",
    "Finley",
    "Jordan",
    "Cameron",
    "Riley",
    "Peyton",
    "Sage",
    "Alex",
    "Robin",
    "Logan",
    "Casey",
    "Reese",
    "Jamie",
    "Skyler",
    "Shiloh",
    "River",
    "Parker",
    "Emerson",
    "Dallas",
    "Phoenix",
    "Dakota",
    "Tatum",
    "Hayden",
    "Harley",
    "Marley",
    "Remy",
    "Rory",
    "Aspen",
    "Charlie",
    "Eden",
    "Wren",
]

LAST_NAMES = [
    "Smith",
    "Johnson",
    "Williams",
    "Brown",
    "Jones",
    "Garcia",
    "Miller",
    "Davis",
    "Rodriguez",
    "Martinez",
    "Hernandez",
    "Lopez",
    "Gonzalez",
    "Wilson",
    "Anderson",
    "Thomas",
    "Taylor",
    "Moore",
    "Jackson",
    "Martin",
    "Lee",
    "Perez",
    "Thompson",
    "White",
    "Harris",
    "Sanchez",
    "Clark",
    "Ramirez",
    "Lewis",
    "Robinson",
    "Walker",
    "Young",
    "Allen",
    "King",
    "Wright",
    "Scott",
    "Torres",
    "Nguyen",
    "Hill",
    "Flores",
    "Green",
    "Adams",
    "Nelson",
    "Baker",
    "Hall",
    "Rivera",
    "Campbell",
    "Mitchell",
    "Carter",
    "Roberts",
    "Gomez",
    "Phillips",
    "Evans",
    "Turner",
    "Diaz",
    "Parker",
    "Cruz",
    "Edwards",
    "Collins",
    "Reyes",
    "Stewart",
    "Morris",
    "Morales",
    "Murphy",
    "Cook",
    "Rogers",
    "Gutierrez",
    "Ortiz",
    "Morgan",
    "Cooper",
    "Peterson",
    "Bailey",
    "Reed",
    "Kelly",
    "Howard",
    "Ramos",
    "Kim",
    "Cox",
    "Ward",
    "Richardson",
    "Watson",
    "Brooks",
    "Chavez",
    "Wood",
    "James",
    "Bennett",
    "Gray",
    "Mendoza",
    "Ruiz",
    "Hughes",
    "Price",
    "Alvarez",
    "Castillo",
    "Sanders",
    "Patel",
    "Myers",
    "Long",
    "Ross",
    "Foster",
    "Jimenez",
]

EMAILS = [
    "cyber_ghost99",
    "pixel.wizard",
    "shadow_ninja",
    "quantum_coder",
    "cosmic.wanderer",
    "alpha_omega",
    "techno_vibe",
    "silver_fox42",
    "neon_rider",
    "digital.nomad",
    "sonic_boom",
    "iron_clad",
    "frost_bite",
    "phoenix_rising",
    "storm_bringer",
    "starlight_01",
    "hyper_drive",
    "velvet_glove",
    "mystic_river",
    "golden_eagle",
    "retro_gamer",
    "matrix_reloaded",
    "lunar_eclipse",
    "solar_flare",
    "vortex_traveler",
    "zen_master",
    "code_monkey",
    "binary_boss",
    "cyber_punk",
    "echo_location",
    "whispering_wind",
    "silent_assassin",
    "wild_card",
    "night_owl",
    "early_bird",
    "coffee_addict",
    "book_worm",
    "movie_buff",
    "music_lover",
    "globetrotter",
    "urban_explorer",
    "nature_lover",
    "beach_bum",
    "mountain_goat",
    "sky_diver",
    "deep_sea",
    "star_gazer",
    "dream_catcher",
    "peace_maker",
    "risk_taker",
    "trend_setter",
    "game_changer",
    "thought_leader",
    "problem_solver",
    "pixel_perfect",
    "bug_hunter",
    "data_miner",
    "cloud_surfer",
    "network_ninja",
    "security_guru",
    "crypto_king",
    "token_master",
    "block_chain",
    "web_developer",
    "app_designer",
    "ui_ux_pro",
    "qa_wizard",
    "devops_guy",
    "sysadmin_pro",
    "tech_savvy",
    "gadget_geek",
    "sci_fi_fan",
    "fantasy_nerd",
    "comic_book",
    "anime_lover",
    "manga_reader",
    "j-pop_fan",
    "k-pop_stan",
    "rock_star",
    "pop_diva",
    "jazz_cat",
    "blues_man",
    "hip_hop_head",
    "dj_remix",
    "sound_wave",
    "beat_maker",
    "lyrics_writer",
    "art_lover",
    "photo_grapher",
    "video_grapher",
    "content_creator",
    "vlogger_life",
    "blogger_world",
    "influencer_00",
    "social_media",
    "digital_art",
    "sketch_artist",
    "painter_pro",
    "sculptor_01",
    "creative_mind",
]

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
        self.status = 0

    def generate(self, path: str, count: int):
        self.status = 0
        with open(path, "w", encoding="utf-8", buffering=8192) as file:
            file.write("id,age,name,email,phone\n")
            for i in range(count):
                record = Record()
                record.generate(i)
                file.write(str(record) + "\n")

                self.status += 1

    def split(self, path: str, key: int):
        buff = []
        chunks = []

        def sort_store():
            buff.sort(key=lambda r: r.value(key))
            path = f"./temp{len(chunks)}.txt"
            with open(path, "w", encoding="utf-8", buffering=8192) as f:
                for v in buff:
                    f.write(str(v) + "\n")

            chunks.append(path)

        with open(path, "r", encoding="utf-8") as file:
            # Skip first line
            file.readline()

            line = file.readline()
            while line:
                self.status += 1
                buff.append(Record().parse(line))

                if len(buff) > BUF_SIZE:
                    sort_store()
                    buff = []

                line = file.readline()

        if buff:
            sort_store()

        return chunks

    def sort(self, path: str, key: int):
        global ikey
        self.status = 0
        ikey = key

        chunks = self.split(path, ikey)
        heap = []
        files = []

        for tmp in chunks:
            f = open(tmp, "r", encoding="utf-8")
            line = f.readline()
            while line:
                r = Record().parse(line)
                heapq.heappush(heap, r)
                line = f.readline()
            files.append((tmp, f))

        with open("./result.txt", "w", encoding="utf-8") as out:
            out.write("id,age,name,email,phone\n")
            result = []
            while heap:
                r = heapq.heappop(heap)
                result.append(r)
            result.sort(key=lambda v: v.value(ikey))
            for v in result:
                out.write(str(v) + "\n")

        for p, f in files:
            f.close()
            os.remove(p)

    def value(self) -> int:
        return self.status
