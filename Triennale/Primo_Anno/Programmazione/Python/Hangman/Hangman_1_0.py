from random_word import RandomWords
from colorama import Fore
from colorama import Style
from Gui import *


class Hangman:
    def __init__(self):
        """
        Hangman... Il gioco dell'impiccato

        """
        self.word = ""
        self.char = ""
        self.__wordIndex = ""
        self.__charUsed = []
        self.__displayChars = []
        self.__BOLD = "\033[1m"
        self.__END = "\033[0m"
        self.__MESSAGES = {
            "WIN": f"{Fore.GREEN}{self.__BOLD}You Won!{self.__END}{Style.RESET_ALL}",
            "LOSE": f"{Fore.RED}{self.__BOLD}You Lost!{self.__END}{Style.RESET_ALL}",
            "USED": f"{Fore.RED} already used...{Style.RESET_ALL}",
            "INPUT_ERROR": f"{Fore.RED}Enter only one character!{Style.RESET_ALL}",
            "WORD": f"{Fore.RED}The word to guess was:{Style.RESET_ALL}",
        }

    def __checkInput(self, char):
        """
        Controlla se char contiene soltanto un carattere

        Args:
            char (String): carattere

        Returns:
            Boolean
        """
        if char == "quit":
            exit()
        if len(char) != 1 or char == "":
            return False
        else:
            return True

    def __getIndexes(self):
        """_summary_
        Trova gli indici del carattere all'interno della parola

        Returns:
            List: List of integers
        """
        indexes, index = [], 0
        for i in range(len(self.word)):
            if self.__wordIndex[i] == self.char:
                index = self.__wordIndex.index(self.char)
                self.__wordIndex = self.__wordIndex.replace(self.char, "_", 1)
                indexes.append(index)
        return indexes

    def __insertChar(self):
        """
        Inserisce il carattere all interno di una lista, in modo da tener conto dei caratteri utilizzati
        """
        if not self.char in self.__charUsed and len(self.char) == 1:
            self.__charUsed.append(self.char)

    def __makeGuess(self):
        """
        Controlla se il carattere inserito dall'utente si trova all'interno della parola

        Returns:
            Boolean:
        """
        if self.char in self.word and self.char != "":
            return True
        else:
            return False

    def __setChar(self, char):
        """
        Imposta self.char

        Args:
            char (String): carattere inserito dall'utente da tastiera
        """
        if self.__checkInput(char):
            self.char = char
        else:
            self.char = ""
            print(self.__MESSAGES["INPUT_ERROR"])

    def __printWord(self):  # {i} {len(self.word) + len(self.word) // 2
        for char in self.__displayChars:
            print(f"{Fore.YELLOW}{char}{Style.RESET_ALL}", end=" ")

    def __printRound(self, i):
        print(
            f"Round {Fore.MAGENTA}{i}{Style.RESET_ALL} of {Fore.MAGENTA}{len(self.word) + (len(self.word) // 2)}{Style.RESET_ALL}"
        )

    def setWord(self, word):
        """
        Imposta self.word, self.__wordIndex, self.__displayChars

        Args:
            word (String): parola da indovinare
        """
        self.word = word
        self.__wordIndex = word
        self.__displayChars = ["_"] * len(word)

    def getWord(self):
        """
        Restituisce la parola da indovinare

        Returns:
            String:
        """
        return self.word

    def getChar(self):
        """
        Restituisce il carattere attuale

        Returns:
            String:
        """
        return self.char

    def playGame(self):
        """
        Esecuzione del gioco
        """
        i = 0
        while "".join(self.__displayChars) != self.word and i < len(self.word) + (
            len(self.word) // 2
        ):
            self.__setChar(input(f"{Fore.BLUE}Try to guess...{Style.RESET_ALL}\n>>"))
            print(self.getChar())
            if not (self.char in self.__charUsed):
                self.__insertChar()
                res = self.__makeGuess()
                if res:
                    indexes = self.__getIndexes()
                    for j in indexes:
                        self.__displayChars[j] = self.char
                self.__printWord()
            else:
                print(f"{Fore.CYAN}'{self.char}'" + self.__MESSAGES["USED"])
            i += 1
            self.__printRound(i)
        if "".join(self.__displayChars) == self.word:
            print(self.__MESSAGES["WIN"])
        else:
            print(self.__MESSAGES["LOSE"])
            print(
                self.__MESSAGES["WORD"]
                + f" {Fore.MAGENTA}{self.__BOLD}{self.word}{self.__END}{Style.RESET_ALL}"
            )
