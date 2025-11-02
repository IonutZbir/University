package services;

import models.Ristorante;

public interface Factory {

    <T> T create(String path);
}