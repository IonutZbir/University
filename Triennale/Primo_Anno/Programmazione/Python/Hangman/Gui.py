import platform
from tkinter import *
from tkinter import messagebox

from PIL import Image, ImageTk


class HangmanGame:
    def __init__(self):
        self.window_width = 600
        self.window_height = 600
        self.title = "Hangman Game"
        self.root = Tk()
        self.used_chr = set()
        self.buttons = set()
        self.word_to_guess = "PorcoDio"

        screen_width = self.root.winfo_screenwidth()
        screen_height = self.root.winfo_screenheight()

        x = (screen_width // 2) - (self.window_width // 2)
        y = (screen_height // 2) - (self.window_height // 2)

        resolution = f"{self.window_width}x{self.window_height}+{x}+{y}"

        self.root.geometry(resolution)
        self.root.title(self.title)
        self.root.resizable(False, False)

        os_name = platform.system()

        icon_path = ""
        if os_name == "Windows":
            icon_path = "img/hangman-game.ico"
        if os_name == "Linux":
            icon_path = "img/hangman-game.xbm"

        # self.root.iconbitmap(icon_path)

        self.menu = Frame(
            self.root, borderwidth=2, relief="solid", width=100, height=150
        )
        self.menu.grid(column=0, row=0, sticky="nsew")

        self.title_frame = Frame(
            self.root, borderwidth=2, relief="solid", width=400, height=150
        )
        self.title_frame.grid(column=1, row=0, sticky="nsew")

        self.times = Frame(
            self.root, borderwidth=2, relief="solid", width=100, height=150
        )
        self.times.grid(column=2, row=0, sticky="nsew")

        self.word = Frame(
            self.root, borderwidth=2, relief="solid", width=600, height=150
        )
        self.word.grid(column=0, row=1, columnspan=3, sticky="nsew")
        self.word_to_guess_label = Label(self.word, text=self.word_to_guess)
        self.word_to_guess_label.pack(pady=20)

        self.input_frame = Frame(self.root, width=400, height=100)
        self.input_frame.grid(column=0, row=2, columnspan=3)

        self.input_buttons = Frame(
            self.root, borderwidth=2, relief="solid", width=600, height=200
        )
        self.input_buttons.grid(column=0, row=3, columnspan=3, pady=20)

        self.input_guess = Entry(
            self.input_frame, width=48, font=("Courier", 8, "bold")
        )
        self.input_guess.grid(column=1, row=0, columnspan=2, pady=10)

        Label(
            self.input_frame, text="Used Characters", fg="black", font=("Arial", 8)
        ).grid(column=0, row=0, padx=5)

        Label(
            self.input_frame,
            text="Make a Guess..",
            fg="red",
            font=("Arial", 12, "bold"),
        ).grid(column=0, row=1, columnspan=3)

        self.buttons_per_row = 10
        i = 0
        for i, char in enumerate(range(ord("a"), ord("z") + 1)):
            button = self.create_button(chr(char))
            self.buttons.add(button)
            button.grid(
                row=i // self.buttons_per_row,
                column=i % self.buttons_per_row,
                padx=5,
                pady=5,
            )

        self.restart_button = Button(
            self.input_buttons,
            text="Restart",
            command=self.restart,
            cursor="hand2",
            borderwidth=1,
            fg="black",
            background="white",
            width=10,
            height=2,
        )
        self.restart_button.grid(
            row=i // self.buttons_per_row,
            column=(i % self.buttons_per_row) + 1,
            columnspan=5,
            padx=5,
        )

        self.title_window = Label(
            self.title_frame,
            text=self.title,
            font=("Arial", 15, "bold"),
            fg="red",
            pady=50,
            padx=50,
        )
        self.title_window.grid(row=0, column=1)

        image = Image.open("img/hangman-game.png")
        image = image.resize((80, 80))
        self.photo = ImageTk.PhotoImage(image)
        self.label_img = Label(self.title_frame, image=self.photo)
        self.label_img.grid(row=0, column=0)

    def set_state(self, st: str, widget):
        widget.config(state=st)

    def set_chr(self, char: str, text: Entry, btn: Button):
        self.set_state(NORMAL, text)
        text.insert(END, char)
        self.set_state(DISABLED, text)
        self.used_chr.add(char)
        self.set_state(DISABLED, btn)

        if char in self.word_to_guess:
            # Update the word label with the correctly guessed character
            new_word = ""
            for i in range(len(self.word_to_guess)):
                if self.word_to_guess[i] == char:
                    new_word += char
                else:
                    new_word += self.word_to_guess_label["text"][i]
            self.word_to_guess_label.config(text=new_word)

        # Add the logic to check if the game is won or lost
        if self.word_to_guess_label["text"] == self.word_to_guess:
            # Game won
            self.game_over("Congratulations! You won!")
        elif len(self.used_chr) == len(self.buttons):
            # Game lost
            self.game_over("Game over! You lost!")

    def restart(self):
        for btn in self.buttons:
            self.set_state(NORMAL, btn)
        self.input_guess.config(state=NORMAL)
        self.input_guess.delete(0, END)

    def create_button(self, char: str):
        btn = Button(
            self.input_buttons,
            text=char,
            cursor="hand2",
            borderwidth=1,
            fg="black",
            background="white",
            width=3,
            height=2,
            command=lambda ch=char: self.set_chr(ch, self.input_guess, btn),
        )
        return btn

    def game_over(self, message):
        self.input_guess.config(state=DISABLED)
        self.restart_button.config(state=NORMAL)
        for btn in self.buttons:
            self.set_state(DISABLED, btn)
        messagebox.showinfo("Game Over", message)

    def run(self):
        self.root.mainloop()


game = HangmanGame()
game.run()
