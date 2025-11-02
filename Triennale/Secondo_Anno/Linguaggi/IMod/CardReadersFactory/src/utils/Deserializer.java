package utils;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Deserializer {
    private String path;

    public Deserializer(String path) {
        this.path = path;
    }

    public String getFileName(){
        String fileName = null;
        try {
            File file = new File(this.path);
            Scanner reader = new Scanner(file);
            String line = reader.nextLine(); 
            String[] data = line.split(":");
            if(data[0].equals("filetype")){
                fileName = new String(data[1]); 
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }    
        return fileName;
    }

    public HashMap<String, String> getData(){
        HashMap<String, String> data = new HashMap<>();
        try{
            File file = new File(this.path);
            Scanner reader = new Scanner(file);
            reader.nextLine();
            while (reader.hasNextLine()) {
                String[] line = reader.nextLine().split(":");
                String type = line[0];
                String value = line[1];
                data.put(type, value);
            }
            reader.close();
        }catch(FileNotFoundException e){
            e.printStackTrace();
        }
        return data;
    }

}
