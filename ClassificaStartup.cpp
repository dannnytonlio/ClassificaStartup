#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>

struct Startup {
    int numero;
    double media;
};

bool confrontaStartup(const Startup& a, const Startup& b) {
    double moyA = std::round(a.media * 100.0) / 100.0;
    double moyB = std::round(b.media * 100.0) / 100.0;
    return moyA > moyB; 
}

bool sonoUguali(double a, double b) {
    return std::abs((std::round(a * 100.0) / 100.0) - (std::round(b * 100.0) / 100.0)) < 0.005;
}

int main() {
    const int NB_GIUDICI = 7;
    
    // STRADA RELATIVA: Cerca il file nella stessa cartella dell'eseguibile!
    const std::string nomeFile = "prova prova.txt";
    int numeroSessione = 1;

    while (true) {
        std::vector<Startup> listaStartup;
        std::ifstream file(nomeFile);
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "       📝 ELABORAZIONE FILE N° " << numeroSessione << "        " << std::endl;
        std::cout << "========================================" << std::endl;

        if (!file.is_open()) {
            std::cout << "[ERRORE DI LETTURA] Non riesco a trovare il file!" << std::endl;
            std::cout << "Ho cercato il file '" << nomeFile << "' nella cartella corrente del programma.\n";
            std::cout << "Assicurati che il file si trovi ESATTAMENTE nella stessa cartella dell'eseguibile.\n";
        } else {
            std::string linea;

            while (std::getline(file, linea)) {
                if (linea.empty()) continue;

                std::stringstream ss(linea);
                int numStartup = 0;
                char duePunti;

                if (ss >> numStartup >> duePunti && duePunti == ':') {
                    double voto;
                    int contatoreVoti = 0;
                    double sommaVoti = 0.0;

                    while (ss >> voto) {
                        if (voto < 0) voto = 0;
                        sommaVoti += voto;
                        contatoreVoti++;
                    }

                    Startup s;
                    s.numero = numStartup;
                    s.media = (contatoreVoti < NB_GIUDICI) ? 0.0 : (sommaVoti / NB_GIUDICI);
                    listaStartup.push_back(s);
                }
            }
            file.close();

            if (!listaStartup.empty()) {
                std::stable_sort(listaStartup.begin(), listaStartup.end(), confrontaStartup);

                std::cout << "\n----------------------------------------" << std::endl;
                std::cout << "             🏆 TOP 3 🏆                " << std::endl;
                std::cout << "----------------------------------------" << std::endl;

                int idx = 0;
                int totaleStartup = listaStartup.size();

                // 1° Posto - Raggruppamento ex-æquo
                if (idx < totaleStartup) {
                    double mediaCorrente = listaStartup[idx].media;
                    std::cout << "1° posto: Start-up n°" << listaStartup[idx].numero;
                    idx++;
                    while (idx < totaleStartup && sonoUguali(mediaCorrente, listaStartup[idx].media)) {
                        std::cout << ", n°" << listaStartup[idx].numero;
                        idx++;
                    }
                    std::cout << " (Media: " << std::fixed << std::setprecision(2) << mediaCorrente << ")" << std::endl;
                }

                // 2° Posto - Raggruppamento ex-æquo
                if (idx < totaleStartup) {
                    double mediaCorrente = listaStartup[idx].media;
                    std::cout << "2° posto: Start-up n°" << listaStartup[idx].numero;
                    idx++;
                    while (idx < totaleStartup && sonoUguali(mediaCorrente, listaStartup[idx].media)) {
                        std::cout << ", n°" << listaStartup[idx].numero;
                        idx++;
                    }
                    std::cout << " (Media: " << std::fixed << std::setprecision(2) << mediaCorrente << ")" << std::endl;
                }

                // 3° Posto - Raggruppamento ex-æquo
                if (idx < totaleStartup) {
                    double mediaCorrente = listaStartup[idx].media;
                    std::cout << "3° posto: Start-up n°" << listaStartup[idx].numero;
                    idx++;
                    while (idx < totaleStartup && sonoUguali(mediaCorrente, listaStartup[idx].media)) {
                        std::cout << ", n°" << listaStartup[idx].numero;
                        idx++;
                    }
                    std::cout << " (Media: " << std::fixed << std::setprecision(2) << mediaCorrente << ")" << std::endl;
                }
                std::cout << "----------------------------------------" << std::endl;
            } else {
                std::cout << "[AVVISO] Il file è vuoto o non formattato correttamente.\n";
            }
        }

        std::cout << "\nModifica il file e premi INVIO per aggiornare la classifica...";
        std::cin.clear();
        std::cin.get();
        
        numeroSessione++;
    }
    return 0;
}
