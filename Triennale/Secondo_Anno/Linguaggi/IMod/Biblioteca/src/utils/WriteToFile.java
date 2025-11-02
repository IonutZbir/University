package utils;

import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    private String file;

    public WriteToFile(String file) {
        this.file = file;
    }

    public void write(String text) {
        try {
            FileWriter myWriter = new FileWriter(this.file, true); // true: append
            myWriter.write(text);
            myWriter.close();
        } catch (IOException e) {
            System.out.println("È apparso un errore!");
            e.printStackTrace();
        }
    }
}
