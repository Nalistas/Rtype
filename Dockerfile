# Étape 1 : Choisir une image de base
FROM ubuntu:22.04

# Étape 2 : Installer les dépendances nécessaires
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && apt-get clean

# Étape 3 : Définir le répertoire de travail
WORKDIR /app

# Étape 4 : Copier les fichiers du projet dans le conteneur
COPY . .

# Étape 5 : Construire le projet
RUN mkdir -p build && cd build && cmake .. && cmake --build .

# Étape 6 : Définir le point d'entrée pour exécuter le programme
CMD ["build/MainTest"]
