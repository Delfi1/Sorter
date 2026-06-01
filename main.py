import ctypes
import sys
import threading
import time
import tkinter as tk
from tkinter import ttk

from sorter import Sorter
from sorter_cpp import SorterCpp

GB = 1024 * 1024 * 16

BG_COLOR = "#2b2b2b"
BTN_STYLE = {
    "font": ("Segoe UI", 11, "bold"),
    "bg": "#2563EB",
    "fg": "#FFFFFF",
    "activebackground": "#1D4ED8",
    "activeforeground": "#FFFFFF",
    "bd": 0,
    "padx": 8,
    "pady": 4,
    "cursor": "hand2",
}

LBL_STYLE = {
    "font": ("Segoe UI", 10, "bold"),
    "bg": BG_COLOR,
    "fg": "#FFFFFF",
}

SEL_STYLE = {
    "font": ("Segoe UI", 10, "bold"),
    "bg": "#475569",
    "fg": "#000000",
    "activebackground": "#334155",
    "activeforeground": "#475569",
    "bd": 0,
    "padx": 5,
    "pady": 2,
    "cursor": "hand2",
    "indicatoron": False,
}

OPT_STYLE = {
    "font": ("Segoe UI", 11),
    "bg": "#2563EB",
    "fg": "#FFFFFF",
    "activebackground": "#1D4ED8",
    "activeforeground": BG_COLOR,
    "bd": 0,
    "tearoff": 0,
}

DD_STYLE = {
    "font": ("Segoe UI", 11, "bold"),
    "bg": "#2563EB",
    "fg": "#FFFFFF",
    "activebackground": "#1D4ED8",
    "activeforeground": BG_COLOR,
    "bd": 0,
    "padx": 8,
    "pady": 4,
    "cursor": "hand2",
    "width": 4,
}

ENT_STYLE = {
    "font": ("Segoe UI", 10, "bold"),
    "bg": BG_COLOR,
    "fg": "#FFFFFF",
}


def on_closing():
    global running
    running = False


running = True
timer = None
root = tk.Tk()
root.resizable(False, False)
root.protocol("WM_DELETE_WINDOW", on_closing)
root.title("Sorting files")
root["bg"] = BG_COLOR
root.geometry("500x250")
style = ttk.Style()
style.theme_use("default")

style.configure(
    "Custom.Horizontal.TProgressbar",
    troughcolor="#2d2d3d",
    background="#00adb5",
    thickness=15,
)

lib = ctypes.CDLL("./lib.dll", winmode=0)
cpp = SorterCpp(lib)
py = Sorter()
selection = tk.StringVar(root, "C++")


def current():
    sl = selection.get().lower()
    if sl == "py":
        return py

    return cpp


group1 = tk.Frame(background=BG_COLOR)
cppBtn = tk.Radiobutton(
    group1,
    text="C++",
    variable=selection,
    value="C++",
    **SEL_STYLE,
)
cppBtn.pack(side="left", padx=5, pady=5)

pythonBtn = tk.Radiobutton(
    group1,
    text="Py",
    variable=selection,
    value="Py",
    **SEL_STYLE,
)
pythonBtn.pack(side="left", padx=5, pady=5)

group1.place(anchor="w", width=150, height=100, x=5, y=25)


def sorting_worker(sorter: Sorter | SorterCpp, path: str, key: int):
    print("Sorting!")
    sorter.sort(path, key)
    print("Success!")


def generate_worker(sorter: Sorter | SorterCpp, path: str, count: int):
    global timer
    print("Generating!")
    timer = time.perf_counter()
    sorter.generate(path, count)
    print("Success!")

    current = time.perf_counter()
    print("Exectution time: ", current - timer)
    timer = None


def sort_worker(sorter: Sorter | SorterCpp, path: str, key: int):
    global timer

    print("Sorting")
    timer = time.perf_counter()
    sorter.sort(path, key)
    print("Success!")

    current = time.perf_counter()
    print("Exectution time: ", current - timer)
    timer = None


def on_generate():
    global count_var
    thread = threading.Thread(
        target=generate_worker, args=(current(), "./file.txt", int(gb_var.get() * GB))
    )

    thread.start()


def on_sort():
    global key_var
    thread = threading.Thread(target=sort_worker, args=(current(), "./file.txt", key()))

    thread.start()


gen_btn = tk.Button(text="Generate", command=on_generate, **BTN_STYLE)
gen_btn.place(x=10, y=60)

sort_btn = tk.Button(text="Sort", command=on_sort, **BTN_STYLE)
sort_btn.place(x=120, y=60)

gb_var = tk.DoubleVar(root, 1.0)
status_text = tk.StringVar(root)
status_label = tk.Label(textvariable=status_text, **LBL_STYLE)

timer_var = tk.StringVar(root)
timer_label = tk.Label(textvariable=timer_var, **LBL_STYLE)

progress_var = tk.IntVar(root, 0)
progress = ttk.Progressbar(
    root,
    style="Custom.Horizontal.TProgressbar",
    orient="horizontal",
    length=300,
    mode="determinate",
    variable=progress_var,
)
progress.place(x=10, y=125)
status_label.place(x=10, y=155)
timer_label.place(x=10, y=175)

sort_options = ["Id", "Age", "Name", "Email", "Phone"]
selected_key = tk.StringVar(root, sort_options[0])


def key() -> int:
    v = selected_key.get()
    for i in range(len(sort_options)):
        if v == sort_options[i]:
            return i
    return 0


countEntry = tk.Entry(root, width=10, textvariable=gb_var, **ENT_STYLE)
countEntry.place(x=300, y=10)

dropdown = tk.OptionMenu(root, selected_key, *sort_options)
dropdown.config(**DD_STYLE)
dropdown["menu"].config(**OPT_STYLE)

dropdown.place(x=400, y=10)

while running:
    status_text.set(str(current().value()))
    try:
        progress_var.set(current().value() * 100 // int(gb_var.get() * GB))
    except Exception as _:
        ...

    last = timer
    if last:
        sort_btn.config(state="disabled")
        gen_btn.config(state="disabled")
        delta = time.perf_counter() - last
        timer_var.set(f"{delta:.2f}s")
    else:
        sort_btn.config(state="active")
        gen_btn.config(state="active")

    root.update()

root.destroy()
sys.exit()
