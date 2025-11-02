package utils;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class ReadFromFile {
    private String file;

    public ReadFromFile(String file) {
        this.file = file;
    }

    public ArrayList<String> read() {
        ArrayList<String> data = new ArrayList<>();
        try {
            File f = new File(this.file);
            Scanner reader = new Scanner(f);
            while (reader.hasNextLine()) {
                data.add(reader.nextLine());
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println("È apparso un errore!");
            e.printStackTrace();
        }

        return data;
    }

}
